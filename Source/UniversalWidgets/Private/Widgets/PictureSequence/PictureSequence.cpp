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


#include "Widgets/PictureSequence/PictureSequence.h"
#include "Blueprint/WidgetTree.h"

bool UPictureSequence::Initialize()
{
	bool bInit = Super::Initialize();
	if (WidgetTree->RootWidget)
	{
		return bInit;
	}
	ImageWidget = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), FName(TEXT("ImageWidget")));
	if (ImageWidget)
	{
		// 将根控件添加到 UserWidget 中
		WidgetTree->RootWidget = ImageWidget;
	}
	return bInit;
}

void UPictureSequence::InitWidget(TArray<UTexture2D*> OTexture2Ds, float OFramesPerSecond, int OTexture2DsIndex)
{
	FramesPerSecond = OFramesPerSecond;
	Texture2DsIndex = OTexture2DsIndex;
	Texture2Ds = OTexture2Ds;
	if (Texture2Ds.Num())
	{
		GetWorld()->GetTimerManager().SetTimer(FPSTimerHandle, this, &UPictureSequence::OnFPSTimerHandle, 1 / FramesPerSecond, true);
	}
}

void UPictureSequence::OnFPSTimerHandle()
{
	if (ImageWidget && Texture2Ds[Texture2DsIndex])
	{
		ImageWidget->SetBrushFromTexture(Texture2Ds[Texture2DsIndex],true);
	}
	if (bPictureEndRem && Texture2DsIndex + 1 == Texture2Ds.Num())
	{
		RemoveFromParent(); /** * 从父类移除 */
	}
	else
	{
		Texture2DsIndex = (Texture2DsIndex + 1) % Texture2Ds.Num();
	}
}
