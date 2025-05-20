/**
 * Copyright: Aimo_皑墨
 * Open Source Date: Jun 27, 2023
 * BiLiBiLi (哔哩哔哩) address: https://space.bilibili.com/146962867
 * Open source address(Git): https://github.com/AimoTvT/UniversalWidgets
 * We welcome the contributions of powerful movers and movers to join this plugin
 * Build powerful plugins together!!
 *
 * 版权所有权: Aimo_皑墨
 * 开源时间: 2023年6月27日
 * BiLiBiLi(哔哩哔哩)地址: https://space.bilibili.com/146962867
 * 开源地址(Git): https://github.com/AimoTvT/UniversalWidgets
 * 欢迎有实力的大佬/萌新加入本插件的贡献
 * 一起打造强大的插件!!!
 */


#include "Widgets/SuspendedWidget/SuspendedWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Animation/WidgetAnimation.h"
#include "FunctionLibrary/UniversalWidgetFunctionLibrary.h"


void USuspendedWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (Location != EndLocation)
	{
		TimerHandleLocation(InDeltaTime);
	}
}


void USuspendedWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SuspendedPlayAnimation(TEXT("Play"));  /** * 播放开始动画 */
}

void USuspendedWidget::Init(const FText& InText, float InTimer, const FVector& InLocation, const FVector& InEndLocation, TSoftObjectPtr<UObject> InSoftObjectPtr, const FVector2D& InImageSize)
{
	Location = InLocation;
	EndLocation = InEndLocation;
	AddDestructTimer(InTimer, true);
	SetImageSoftObjectPtr(InSoftObjectPtr, InImageSize);
	if (TextBlockWidget)
	{
		TextBlockWidget->SetText(InText);
	}
	if (GetWorld() && GetWorld()->GetFirstPlayerController() && GetWorld()->GetFirstPlayerController()->PlayerCameraManager)
	{
		float Size = FVector::Distance(Location, GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation()); /** * 计算摄像机和目标的距离 */
		Size = 1 - FMath::Clamp(Size * 0.22 * 0.001, 0.0, 1 - MinDistanceSize);
		SetRenderTransform(FWidgetTransform{ {0.0f, 0.0f},{Size,Size},{0.0f, 0.0f},0.0f }); /** * 设置变换 */
	}
}

void USuspendedWidget::InitOffset(FText InText, float InTimer, FVector InLocation, FVector InOffsetLocation, TSoftObjectPtr<UObject> InSoftObjectPtr, FVector2D InImageSize)
{
	Init(InText, InTimer, InLocation, InOffsetLocation + InLocation, InSoftObjectPtr, InImageSize);
}

void USuspendedWidget::TimerHandleLocation(float InDeltaTime) /** * 定时器0.2秒设置三维到屏幕位置 */
{
	DestructTimer -= InDeltaTime;
	if (Location != EndLocation)
	{
		FVector2D OffsetT;
		Location = FMath::VInterpTo(Location, EndLocation, InDeltaTime, AnimTimer);
		if (UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetOwningPlayer(), Location, OffsetT, bPlayerViewportRelative))
		{
			if (GetVisibility() != ESlateVisibility::HitTestInvisible)
			{
				SetVisibility(ESlateVisibility::HitTestInvisible);
			}
			OffsetT = (OffsetT + GetDesiredSize() * -0.5 + Offset) * UWidgetLayoutLibrary::GetViewportScale(this);
			SetPositionInViewport(OffsetT);/** * 计算完整偏移,并设置位置 */
		}
		else
		{
			if (GetVisibility() != ESlateVisibility::Hidden)
			{
				SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
	if (DestructTimer <= 2.0f)
	{
		SuspendedPlayAnimation(TEXT("Remove"));
		if (DestructTimer <= 0.0f)
		{
			if (GetWorld()->GetTimerManager().IsTimerActive(DestructTimerHandle))
			{
				GetWorld()->GetTimerManager().ClearTimer(DestructTimerHandle);
			}
			RemoveFromParent(); /** * 从父类移除 */
		}
	}
}

void USuspendedWidget::SetImageSoftObjectPtr(TSoftObjectPtr<UObject> InSoftObjectPtr, FVector2D InImageSize) /** * 设置图像 */
{
	EnhancedCommonLazyImageWidget->SetMaxImageSize(InImageSize, false);
	EnhancedCommonLazyImageWidget->SetBrushFromLazyDisplayAsset(InSoftObjectPtr);
}

void USuspendedWidget::AddDestructTimer(float Timer, bool bSet) /** * 添加销毁时间 */
{
	if (bSet)
	{
		DestructTimer = Timer;
	}
	else
	{
		DestructTimer += Timer;
	}
	TDestructTimer = DestructTimer;
	if (!GetWorld()->GetTimerManager().IsTimerActive(DestructTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(DestructTimerHandle, this, &USuspendedWidget::NativeDestructTimerHandle, 0.2f, true); /** * 启动设置定时器 */
	}
	if (DestructTimer <= 2.0f)
	{
		if (RemoveAnim != 1)
		{
			SuspendedPlayAnimation(TEXT("Remove"));
		}
		if (DestructTimer <= 0.0f)
		{
			if (GetWorld()->GetTimerManager().IsTimerActive(DestructTimerHandle))
			{
				GetWorld()->GetTimerManager().ClearTimer(DestructTimerHandle);
			}
			RemoveFromParent(); /** * 从父类移除 */
		}
	}
}

void USuspendedWidget::NativeDestructTimerHandle()
{
	TDestructTimer -= 0.2;
	if (TDestructTimer < DestructTimer)
	{
		TimerHandleLocation(DestructTimer - TDestructTimer);
	}
	TDestructTimer = DestructTimer;
}

void USuspendedWidget::SuspendedPlayAnimation(const FString& String)
{
	UObject* Object;
	FObjectProperty* ObjectProperty = nullptr;
	UWidgetAnimation* WidgetAnimation = nullptr;
	if (String == TEXT("Remove")) /** * 判断是否销毁 */
	{
		if (DestructTimer < 1.8)
		{
			return;
		}
		RemoveAnim = 1;
		ObjectProperty = FindFProperty<FObjectProperty>(GetClass(), TEXT("JianBianXianShiAnimation")); //Object指针类型变量
		if (ObjectProperty == nullptr)
		{
			return;
		}
		Object = Cast<UWidgetAnimation>(ObjectProperty->GetObjectPropertyValue_InContainer(this)); //转换Object类型
		if (Object)
		{
			WidgetAnimation = Cast<UWidgetAnimation>(Object);
			if (WidgetAnimation)
			{
				PlayAnimation(WidgetAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward);
			}
		}
		return;
	}
	if (String == TEXT("Play")) /** * 判断是否开始 */
	{
		RemoveAnim = 2;		
		if (ObjectProperty == nullptr)
		{
			return;
		}
		ObjectProperty = FindFProperty<FObjectProperty>(GetClass(), TEXT("BianDaAnimation")); //Object指针类型变量
		Object = Cast<UWidgetAnimation>(ObjectProperty->GetObjectPropertyValue_InContainer(this)); //转换Object类型
		if (Object)
		{
			WidgetAnimation = Cast<UWidgetAnimation>(Object);
			if (WidgetAnimation)
			{
				PlayAnimation(WidgetAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward);
			}
		}
		return;
	}
}

void USuspendedWidget::SetTextBlockSize(float InSize)
{
	UUniversalWidgetFunctionLibrary::SetTextBlockSize(TextBlockWidget, InSize);
}

void USuspendedWidget::SetTextBlockColors(FSlateColor InColorAndOpacity, FLinearColor InLinearColor, int InOutlineSize)
{
	UUniversalWidgetFunctionLibrary::SetTextBlockColors(TextBlockWidget, InColorAndOpacity, InLinearColor, InOutlineSize);
}
