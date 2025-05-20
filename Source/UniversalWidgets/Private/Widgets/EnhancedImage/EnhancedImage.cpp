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


#include "Widgets/EnhancedImage/EnhancedImage.h"

#include "FunctionLibrary/UniversalBaseFunctionLibrary.h"
#include "FunctionLibrary/UniversalWidgetFunctionLibrary.h"



void UEnhancedImage::SetMaxImageSize(const FVector2D& MaxSize)
{
	MaxImageSize = MaxSize;
	SetBrushFromResourceObject(GetBrush().GetResourceObject());
}

void UEnhancedImage::AsyncBrushFromSoftObjectPtr(const TSoftObjectPtr<UObject>& InSoftObjectPtr)
{
	if (!InSoftObjectPtr.IsNull())
	{
		TWeakObjectPtr<UEnhancedImage> WeakThis(this); // using weak ptr in case 'this' has gone out of scope by the time this lambda is called
		RequestAsyncLoad(InSoftObjectPtr,
			[WeakThis, InSoftObjectPtr]() {
				if (UEnhancedImage* StrongThis = WeakThis.Get())
				{
					ensureMsgf(InSoftObjectPtr.Get(), TEXT("Failed to load %s"), *InSoftObjectPtr.ToSoftObjectPath().ToString());
					StrongThis->SetBrushFromResourceObject(InSoftObjectPtr.Get());
					StrongThis->OnAsyncObject.Broadcast(InSoftObjectPtr, true);
					return;
				}
			}
		);
	}
}

void UEnhancedImage::SetBrushFromSoftPath(const FString& Path, const FVector2D& MaxSize)
{
	if (MaxSize.X != 0.0f)
	{
		MaxImageSize = MaxSize;
	}
	TSoftObjectPtr<UObject> SoftObject = TSoftObjectPtr<UObject>(FSoftObjectPath(Path));
	if (SoftObject.IsNull() == false)
	{
		if (SoftObject.IsValid())
		{
			SetBrushFromResourceObject(SoftObject.Get());
			return;
		}
		AsyncBrushFromSoftObjectPtr(SoftObject);
	}
	return;
}

void UEnhancedImage::SetBrushFromSoftObjectPtr(const TSoftObjectPtr<UObject>& InSoftObjectPtr, const FVector2D& MaxSize)
{
	if (MaxSize.X != 0.0f)
	{
		MaxImageSize = MaxSize;
	}
	if (InSoftObjectPtr.IsNull())
	{
		OnAsyncObject.Broadcast(InSoftObjectPtr, false);
		return;
	}
	if (InSoftObjectPtr.IsValid())
	{
		SetBrushFromResourceObject(InSoftObjectPtr.Get());
		return;
	}
	AsyncBrushFromSoftObjectPtr(InSoftObjectPtr);
	return;
}

void UEnhancedImage::SetBrushFromResourceObject(UObject* Object)
{
	if (Object)
	{
		UTexture2D* Texture2D = Cast<UTexture2D>(Object);
		if (Texture2D && MaxImageSize.X != 0.0f)
		{
			SetBrushResourceObject(Object);
			FVector2D Size;
			Size.X = Texture2D->GetSizeX();
			Size.Y = Texture2D->GetSizeY();
			Size = UUniversalBaseFunctionLibrary::ClampProportional(Size.X, Size.Y, MaxImageSize.X, MaxImageSize.Y);
			if (bImageSizeMax && Size.X < MaxImageSize.X && Size.Y < MaxImageSize.Y)
			{
				Size = Size * (MaxImageSize / Size);
			}
			FSlateBrush SlateBrush = GetBrush();
			SlateBrush.SetImageSize(Size);
			SetBrush(SlateBrush);
			UUniversalWidgetFunctionLibrary::SetWidgetSize(this, Size);
			return;
		}
		if (Cast<UTexture>(Object) || Cast<UMaterialInterface>(Object))
		{
			SetBrushResourceObject(Object);
		}
		if (MaxImageSize.X != 0.0f)
		{
			FSlateBrush SlateBrush = GetBrush();
			SlateBrush.SetImageSize(MaxImageSize);
			SetBrush(SlateBrush);
			UUniversalWidgetFunctionLibrary::SetWidgetSize(this, MaxImageSize);
		}
	}
}

