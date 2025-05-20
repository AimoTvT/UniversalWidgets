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
#include "Components/Image.h"

#include "EnhancedImage.generated.h"

/** *
 * 高级图像,自定义大小,和适应图片大小
 */
UCLASS()
class UNIVERSALWIDGETS_API UEnhancedImage : public UImage
{
	GENERATED_BODY()

public:

	/** * 最大图像大小 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedImage|Variable")
	FVector2D MaxImageSize = FVector2D(32.0f, 32.0f);

	/** * 图像比例 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedImage|Variable")
	bool bImageSizeMax = true;


	/** * *  */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAsyncObject, const TSoftObjectPtr<UObject>&, InSoftObjectPtr, bool, bLoad);

	/** * *  */
	UPROPERTY(BlueprintAssignable, Category = "SpaceItemComponent|On")
	FOnAsyncObject OnAsyncObject;
	
public:

	/** * 设置最大图像大小 */
	UFUNCTION(BlueprintCallable, Category = "EnhancedImage|Function")
	virtual void SetMaxImageSize(const FVector2D& MaxSize);

	/** * 异步样式软Object增强 */
	UFUNCTION(BlueprintCallable, Category = "EnhancedImage|Function")
	virtual void AsyncBrushFromSoftObjectPtr(const TSoftObjectPtr<UObject>& InSoftObjectPtr);

	/** * 设置样式软路径 */
	UFUNCTION(BlueprintCallable, Category = "EnhancedImage|Function")
	virtual void SetBrushFromSoftPath(const FString& Path, const FVector2D& MaxSize = FVector2D(0.0f, 0.0f));

	/** * 设置样式软Object */
	UFUNCTION(BlueprintCallable, Category = "EnhancedImage|Function")
	virtual void SetBrushFromSoftObjectPtr(const TSoftObjectPtr<UObject>& InSoftObjectPtr, const FVector2D& MaxSize = FVector2D(0.0f, 0.0f));

	/** * 设置样式资源Object */
	UFUNCTION(BlueprintCallable, Category = "EnhancedImage|Function")
	virtual void SetBrushFromResourceObject(UObject* Object);

	


}; 
