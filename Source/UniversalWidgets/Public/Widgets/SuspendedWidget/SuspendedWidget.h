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
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Widgets/CommonUIs/Images/EnhancedCommonLazyImage.h"

#include "SuspendedWidget.generated.h"

/** *
 *
 */
UCLASS()
class UNIVERSALWIDGETS_API USuspendedWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** * 水平框控件 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
	TObjectPtr<UHorizontalBox> HorizontalBoxWidget;

	/** * 图像空间 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
	TObjectPtr<UEnhancedCommonLazyImage> EnhancedCommonLazyImageWidget;

	/** * 文字控件 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Aimo|Variable")
	TObjectPtr<UTextBlock> TextBlockWidget;



	/** * 三维位置 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FVector Location = FVector(0.0f, 0.0f, 40.0f);

	/** * 三维位置终点位置 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FVector EndLocation = FVector(0.0f, 0.0f, 40.0f);

	/** * 视口偏移 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FVector2D Offset = FVector2D(0.0f, 0.0f);

	/** * 视口偏移 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
	bool bPlayerViewportRelative = false;

	/** *  */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	uint8 RemoveAnim = 0;

	/** * 最小距离大小, 建议 0.01 - 1 之间 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
	float MinDistanceSize = 0.5f;

	/** * 动画速度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aimo|Variable")
	float AnimTimer = 0.5f;

	/** * 销毁时间 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	float DestructTimer = 2.2f;

	/** * 临时销毁时间 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	float TDestructTimer = 2.2f;

	/** * 销毁定时器 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FTimerHandle DestructTimerHandle;


public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeConstruct() override;

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void Init(const FText& InText, float InTimer = 2.2f, const FVector& InLocation = FVector(0.0f, 0.0f, 0.0f), const FVector& InEndLocation = FVector(0.0f, 0.0f, 220.0f), TSoftObjectPtr<UObject> InSoftObjectPtr = nullptr, const FVector2D& InImageSize = FVector2D(50.0f, 50.0f));

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void InitOffset(FText InText, float InTimer = 2.2f, FVector InLocation = FVector(0.0f, 0.0f, 0.0f), FVector InOffsetLocation = FVector(0.0f, 0.0f, 220.0f), TSoftObjectPtr<UObject> InSoftObjectPtr = nullptr, FVector2D InImageSize = FVector2D(50.0f, 50.0f));

	/** * 设置位置定时器 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void TimerHandleLocation(float InDeltaTime = 0.0f);

	/** * 设置图像 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SetImageSoftObjectPtr(TSoftObjectPtr<UObject> InSoftObjectPtr, FVector2D InImageSize = FVector2D(50.0f, 50.0f));

	/** * 添加销毁时间 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void AddDestructTimer(float Timer, bool bSet = false);

	/** * 销毁定时器 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void NativeDestructTimerHandle();

	/** * 赛选动画 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SuspendedPlayAnimation(const FString& String);

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SetTextBlockSize(float InSize = 24.0f);

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void SetTextBlockColors(FSlateColor InColorAndOpacity, FLinearColor InLinearColor, int InOutlineSize = 2);
	

};
