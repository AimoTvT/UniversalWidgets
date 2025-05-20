// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BackgroundImage/BackgroundImage.h"
#include "FunctionLibrary/UniversalBaseFunctionLibrary.h"
#include "Subsystems/UniversalWidgetsSubsystem.h"

void UBackgroundImage::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	if (!IsDesignTime())
	{
		NativeConstruct();
	}
}

void UBackgroundImage::NativeConstruct()
{
	InitBackground();
}

void UBackgroundImage::InitBackground()
{
	if (Name.IsValid() && UUniversalWidgetsSubsystem::Get())
	{
		UUniversalWidgetsSave* UniversalWidgetsSave = UUniversalWidgetsSubsystem::Get()->GetUniversalWidgetsSave(0);
		if (UniversalWidgetsSave)
		{
			for (size_t i = 0; i < UniversalWidgetsSave->StringImageDatas.Num(); i++)
			{
				if (UniversalWidgetsSave->StringImageDatas[i].Name == Name && UniversalWidgetsSave->StringImageDatas[i].ImageString.Len())
				{
					FSlateBrush TSlateBrush = GetBrush();
					TSoftObjectPtr<UObject> SoftObject = TSoftObjectPtr<UObject>(FSoftObjectPath(UniversalWidgetsSave->StringImageDatas[i].ImageString));
					if (SoftObject.IsNull() == false)
					{
						TSlateBrush.DrawAs = UniversalWidgetsSave->StringImageDatas[i].DrawAs;
						TSlateBrush.Tiling = UniversalWidgetsSave->StringImageDatas[i].Tiling;
						TSlateBrush.ImageSize = UniversalWidgetsSave->StringImageDatas[i].ImageSize;
						TSlateBrush.Margin = UniversalWidgetsSave->StringImageDatas[i].Margin;
						TSlateBrush.TintColor = UniversalWidgetsSave->StringImageDatas[i].TintColor;
						TSlateBrush.OutlineSettings.CornerRadii.X = UniversalWidgetsSave->StringImageDatas[i].CornerRadii.Left;
						TSlateBrush.OutlineSettings.CornerRadii.Y = UniversalWidgetsSave->StringImageDatas[i].CornerRadii.Top;
						TSlateBrush.OutlineSettings.CornerRadii.Z = UniversalWidgetsSave->StringImageDatas[i].CornerRadii.Right;
						TSlateBrush.OutlineSettings.CornerRadii.W = UniversalWidgetsSave->StringImageDatas[i].CornerRadii.Bottom;
						TSlateBrush.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
						if (SoftObject.IsValid())
						{
							TSlateBrush.SetResourceObject(SoftObject.Get());
							SetBrush(TSlateBrush);
							return;
						}
						else
						{
							SetBrush(TSlateBrush);
							AsyncBrushFromSoftObjectPtr(SoftObject);
							return;
						}
					}
					return;
				}
			}
		}
	}
}


void UBackgroundImage::AsyncBrushFromSoftObjectPtr(const TSoftObjectPtr<UObject>& InSoftObjectPtr)
{
	TWeakObjectPtr<UBackgroundImage> WeakThis(this); // using weak ptr in case 'this' has gone out of scope by the time this lambda is called
	RequestAsyncLoad(InSoftObjectPtr,
		[WeakThis, InSoftObjectPtr]() {
			if (UBackgroundImage* StrongThis = WeakThis.Get())
			{
				ensureMsgf(InSoftObjectPtr.Get(), TEXT("Failed to load %s"), *InSoftObjectPtr.ToSoftObjectPath().ToString());
				StrongThis->SetBrushFromResourceObject(InSoftObjectPtr.Get());
				return;
			}
		}
	);
}

bool UBackgroundImage::SetBrushFromSoftPath(const FString& Path)
{
	TSoftObjectPtr<UObject> SoftObject = TSoftObjectPtr<UObject>(FSoftObjectPath(Path));
	if (SoftObject.IsNull() == false)
	{
		if (SoftObject.IsValid())
		{
			return SetBrushFromResourceObject(SoftObject.Get());
		}
		AsyncBrushFromSoftObjectPtr(SoftObject);
		return true;
	}
	return false;
}

bool UBackgroundImage::SetBrushFromSoftObjectPtr(const TSoftObjectPtr<UObject>& InSoftObjectPtr)
{
	if (InSoftObjectPtr.IsNull())
	{
		return false;
	}
	if (InSoftObjectPtr.IsValid())
	{
		return SetBrushFromResourceObject(InSoftObjectPtr.Get());
	}
	AsyncBrushFromSoftObjectPtr(InSoftObjectPtr);
	return true;
}

bool UBackgroundImage::SetBrushFromResourceObject(UObject* Object)
{
	if (Object)
	{
		if (Cast<UTexture>(Object) || Cast<UMaterialInterface>(Object))
		{
			SetBrushResourceObject(Object);
			return true;
		}
	}
	return false;
}