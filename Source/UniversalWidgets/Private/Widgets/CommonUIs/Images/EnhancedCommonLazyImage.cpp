// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonUIs/Images/EnhancedCommonLazyImage.h"
#include "Engine/Texture2DDynamic.h"
#include "TextureCompiler.h"
#include "FunctionLibrary/UniversalBaseFunctionLibrary.h"
#include "Slate/SlateBrushAsset.h"



void UEnhancedCommonLazyImage::SetBrush(const FSlateBrush& InBrush)
{
	Super::SetBrush(InBrush);
	if (UObject* Object = InBrush.GetResourceObject())
	{
		FVector2D DesiredSize = MaxImageSize;
		if (UTexture2DDynamic* AsDynamicTexture = Cast<UTexture2DDynamic>(Object))
		{
			DesiredSize.X = AsDynamicTexture->SizeX;
			DesiredSize.Y = AsDynamicTexture->SizeY;
			DesiredSize = UUniversalBaseFunctionLibrary::ClampProportional(DesiredSize.X, DesiredSize.Y, MaxImageSize.X, MaxImageSize.Y, bImageMatchSize);
		}
		else if (UTexture2D* AsTexture2D = Cast<UTexture2D>(Object))
		{
			DesiredSize.X = AsTexture2D->GetSizeX();
			DesiredSize.Y = AsTexture2D->GetSizeY();
			DesiredSize = UUniversalBaseFunctionLibrary::ClampProportional(DesiredSize.X, DesiredSize.Y, MaxImageSize.X, MaxImageSize.Y, bImageMatchSize);
		}
		SetDesiredSizeOverride(DesiredSize);
	}
	else
	{
		SetDesiredSizeOverride(MaxImageSize);
	}
}

void UEnhancedCommonLazyImage::SetBrushFromAsset(USlateBrushAsset* Asset)
{
	Super::SetBrushFromAsset(Asset);
	if (UObject* Object = Asset ? Asset->Brush.GetResourceObject() : nullptr)
	{
		FVector2D DesiredSize = MaxImageSize;
		if (UTexture2DDynamic* AsDynamicTexture = Cast<UTexture2DDynamic>(Object))
		{
			DesiredSize.X = AsDynamicTexture->SizeX;
			DesiredSize.Y = AsDynamicTexture->SizeY;
			DesiredSize = UUniversalBaseFunctionLibrary::ClampProportional(DesiredSize.X, DesiredSize.Y, MaxImageSize.X, MaxImageSize.Y, bImageMatchSize);
		}
		else if (UTexture2D* AsTexture2D = Cast<UTexture2D>(Object))
		{
			DesiredSize.X = AsTexture2D->GetSizeX();
			DesiredSize.Y = AsTexture2D->GetSizeY();
			DesiredSize = UUniversalBaseFunctionLibrary::ClampProportional(DesiredSize.X, DesiredSize.Y, MaxImageSize.X, MaxImageSize.Y, bImageMatchSize);
		}
		SetDesiredSizeOverride(DesiredSize);
	}
	else
	{
		SetDesiredSizeOverride(MaxImageSize);
	}
}

void UEnhancedCommonLazyImage::SetBrushFromTexture(UTexture2D* Texture, bool bMatchSize /*= false*/)
{
	Super::SetBrushFromTexture(Texture, bMatchSize);
	if (Texture)
	{
		FVector2D DesiredSize;
		DesiredSize.X = Texture->GetSizeX();
		DesiredSize.Y = Texture->GetSizeY();
		DesiredSize = UUniversalBaseFunctionLibrary::ClampProportional(DesiredSize.X, DesiredSize.Y, MaxImageSize.X, MaxImageSize.Y, bMatchSize);
		SetDesiredSizeOverride(DesiredSize);
	}
	else
	{
		SetDesiredSizeOverride(MaxImageSize);
	}
}

void UEnhancedCommonLazyImage::SetBrushFromTextureDynamic(UTexture2DDynamic* Texture, bool bMatchSize /*= false*/)
{
	Super::SetBrushFromTextureDynamic(Texture, bMatchSize);
	if (Texture)
	{
		FVector2D DesiredSize;
		DesiredSize.X = Texture->SizeX;
		DesiredSize.Y = Texture->SizeY;
		DesiredSize = UUniversalBaseFunctionLibrary::ClampProportional(DesiredSize.X, DesiredSize.Y, MaxImageSize.X, MaxImageSize.Y, bMatchSize);
		SetDesiredSizeOverride(DesiredSize);
	}
	else
	{
		SetDesiredSizeOverride(MaxImageSize);
	}
}

void UEnhancedCommonLazyImage::SetBrushFromMaterial(UMaterialInterface* Material)
{
	Super::SetBrushFromMaterial(Material);
	SetDesiredSizeOverride(MaxImageSize);
}

void UEnhancedCommonLazyImage::SetMaxImageSize(FVector2D InMaxImageSize, bool bUpdate)
{
	if (MaxImageSize != InMaxImageSize)
	{
		MaxImageSize = InMaxImageSize;
		if (bUpdate)
		{
			UpdateMatchSize(true);
		}
	}
}

void UEnhancedCommonLazyImage::UpdateMatchSize(bool bMatchSize)
{
	if (UObject* Object = GetBrush().GetResourceObject())
	{
		FVector2D DesiredSize = MaxImageSize;
		if (UTexture2DDynamic* AsDynamicTexture = Cast<UTexture2DDynamic>(Object))
		{
			DesiredSize.X = AsDynamicTexture->SizeX;
			DesiredSize.Y = AsDynamicTexture->SizeY;
			DesiredSize = UUniversalBaseFunctionLibrary::ClampProportional(DesiredSize.X, DesiredSize.Y, MaxImageSize.X, MaxImageSize.Y, bImageMatchSize);
		}
		else if (UTexture2D* AsTexture2D = Cast<UTexture2D>(Object))
		{
			DesiredSize.X = AsTexture2D->GetSizeX();
			DesiredSize.Y = AsTexture2D->GetSizeY();
			DesiredSize = UUniversalBaseFunctionLibrary::ClampProportional(DesiredSize.X, DesiredSize.Y, MaxImageSize.X, MaxImageSize.Y, bImageMatchSize);
		}
		SetDesiredSizeOverride(DesiredSize);
	}
	else
	{
		SetDesiredSizeOverride(MaxImageSize);
	}
}

void UEnhancedCommonLazyImage::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	UpdateMatchSize(bImageMatchSize);
}
