// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CommonUIs/Buttons/UWCommonButtonIDText.h"
#include "Widgets/CommonUIs/Images/EnhancedCommonLazyImage.h"
#include "UWCommonButtonImageText.generated.h"

/**
 * 
 */
UCLASS()
class UNIVERSALWIDGETS_API UUWCommonButtonImageText : public UUWCommonButtonIDText
{
	GENERATED_BODY()

public:

	/** * 高级通用惰性图像 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonButton")
	TObjectPtr<UEnhancedCommonLazyImage> EnhancedCommonLazyImageWidget;

	/** * 图像匹配大小,如果小于最大大小,那么就补充上 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced")
	bool bImageMatchSize = true;

	/** * 最大图像大小 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced")
	FVector2D MaxImageSize = FVector2D(32.0f, 32.0f);

	/** *  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced", meta = (DisplayThumbnail = true, AllowedClasses = "/Script/Engine.Texture,/Script/Engine.MaterialInterface,/Script/Engine.SlateTextureAtlasInterface", DisallowedClasses = "/Script/MediaAssets.MediaTexture"))
	TSoftObjectPtr<UObject> SoftImageResource;


protected:

public:
	virtual void NativePreConstruct() override;

	/**  */
	UFUNCTION(BlueprintCallable, Category = LazyImage)
	virtual void SetLazyObject(const TSoftObjectPtr<UObject>& InLazyObject, bool bMatchTextureSize = false);

};
