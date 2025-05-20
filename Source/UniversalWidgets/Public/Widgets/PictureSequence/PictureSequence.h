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

#include "PictureSequence.generated.h"

/** *
 *
 */
UCLASS()
class UNIVERSALWIDGETS_API UPictureSequence : public UUserWidget
{
	GENERATED_BODY()

public:

	/** * 图像控件 */
	UPROPERTY(BlueprintReadOnly, Category = "PictureSequence|Variable")
	TObjectPtr<UImage> ImageWidget;

	/** * 每秒帧数(切换图片的速度,越大越好) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PictureSequence|Variable")
	float FramesPerSecond = 25.0f;

	/** * 图片组的索引 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PictureSequence|Variable")
	int Texture2DsIndex = 0;

	/** * 图片组序列 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PictureSequence|Variable")
	TArray<TObjectPtr<UTexture2D>> Texture2Ds;

	/** * 切换图片的定时器 */
	UPROPERTY(BlueprintReadWrite, Category = "PictureSequence|Variable")
	FTimerHandle FPSTimerHandle; 

	/** * 切换图片的定时器 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PictureSequence|Variable")
	bool bPictureEndRem = false; 

public:
	virtual bool Initialize() override;

public:

	/** * 初始化控件 */
	UFUNCTION(BlueprintCallable, Category = "PictureSequence|Function")
	virtual void InitWidget(TArray<UTexture2D*> OTexture2Ds, float OFramesPerSecond = 25.0f, int OTexture2DsIndex = 0);

	/** * 切换图片的定时器调用的函数 */
	UFUNCTION(BlueprintCallable, Category = "PictureSequence|Function")
	virtual void OnFPSTimerHandle();

};
