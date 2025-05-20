// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonUIs/Buttons/UWCommonButtonImageText.h"

void UUWCommonButtonImageText::NativePreConstruct()
{
	Super::NativePreConstruct();
	SetLazyObject(SoftImageResource);
}

void UUWCommonButtonImageText::SetLazyObject(const TSoftObjectPtr<UObject>& InLazyObject, bool bMatchTextureSize)
{
	if (EnhancedCommonLazyImageWidget)
	{
		EnhancedCommonLazyImageWidget->bImageMatchSize = bImageMatchSize;
		if (SoftImageResource.IsNull())
		{
			EnhancedCommonLazyImageWidget->SetMaxImageSize(FVector2D(2.0f), true);
			EnhancedCommonLazyImageWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			EnhancedCommonLazyImageWidget->SetVisibility(ESlateVisibility::Visible);
			EnhancedCommonLazyImageWidget->SetMaxImageSize(MaxImageSize, false);
			EnhancedCommonLazyImageWidget->SetBrushFromLazyDisplayAsset(SoftImageResource, bMatchTextureSize);
		}
	}
}
