// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonLazyImage.h"
#include "EnhancedCommonLazyImage.generated.h"

/**
 * 高级通用惰性图像
 */
UCLASS()
class UNIVERSALWIDGETS_API UEnhancedCommonLazyImage : public UCommonLazyImage
{
	GENERATED_BODY()

public:

	/** * 图像匹配大小,如果小于最大大小,那么就补充上 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced")
	bool bImageMatchSize = true;

	/** * 最大图像大小 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced")
	FVector2D MaxImageSize = FVector2D(32.0f, 32.0f);
	


public:
	virtual void SetBrush(const FSlateBrush& InBrush) override;
	virtual void SetBrushFromAsset(USlateBrushAsset* Asset) override;
	virtual void SetBrushFromTexture(UTexture2D* Texture, bool bMatchSize = false) override;
	virtual void SetBrushFromTextureDynamic(UTexture2DDynamic* Texture, bool bMatchSize = false) override;
	virtual void SetBrushFromMaterial(UMaterialInterface* Material) override;

	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void SetMaxImageSize(FVector2D InMaxImageSize = FVector2D(32.0f, 32.0f), bool bUpdate = true);

	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void UpdateMatchSize(bool bMatchSize = false);


protected:
	virtual void OnWidgetRebuilt() override;


};
