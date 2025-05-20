// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonUIs/Selects/Wheels/CommonSelectWheelSector.h"
#include "FunctionLibrary/UniversalBaseFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>

void UCommonSelectWheelSector::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (IsDesignTime())
	{
		UpdateColorAndOpacity();
		SetSectorAngle(SectorAngle);
		SetSectorAngleProgress(SectorAngleProgress);
	}
	else
	{
		BPOnSelect(bSelect, SelectWheelDataStructs.MaxTime, SelectTimer);
	}
}

bool UCommonSelectWheelSector::IsAllowTrigger()
{
	return bTrigger;
}

void UCommonSelectWheelSector::OnTrigger()
{
	UGameplayStatics::PlaySound2D(this, Cast<USoundBase>(PressedSlateSoundOverride.GetResourceObject()), 1.0f, 1.0f, 0.0f, nullptr, GetOwningPlayer());
}

void UCommonSelectWheelSector::OnSelect_Event()
{
	if (bSelect)
	{
		if (SelectTimer < SelectWheelDataStructs.MaxTime)
		{
			SelectTimer += 0.1f;
			if (SelectTimer >= SelectWheelDataStructs.MaxTime)
			{
				SetTrigger(true);
			}
		}
	}
	else
	{
		SelectTimer -= 0.1f;
		if (SelectTimer <= 0.0f)
		{
			SelectTimer = 0.0f;
			if (GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(SelectTimerHandle))
			{
				GetWorld()->GetTimerManager().ClearTimer(SelectTimerHandle);
			}
		}
		SetTrigger(false);
	}
	BPOnSelect(bSelect, SelectWheelDataStructs.MaxTime, SelectTimer);
}

void UCommonSelectWheelSector::BPOnSelect_Implementation(bool InSelect, float InMaxTimer, float InTimer)
{
}

void UCommonSelectWheelSector::SetSelect(bool InbSelect)
{
	if (bSelect != InbSelect)
	{
		bSelect = InbSelect;
		if (bSelect)
		{
			UGameplayStatics::PlaySound2D(this, Cast<USoundBase>(HoveredSlateSoundOverride.GetResourceObject()), 1.0f, 1.0f, 0.0f, nullptr, GetOwningPlayer());
		}
		BPSetSelect(bSelect);
		if (SelectWheelDataStructs.MaxTime > 0)
		{
			if (bSelect && GetWorld() && !GetWorld()->GetTimerManager().IsTimerActive(SelectTimerHandle))
			{
				GetWorld()->GetTimerManager().SetTimer(SelectTimerHandle, this, &UCommonSelectWheelSector::OnSelect_Event, 0.1f, true);
			}
		}
		else
		{
			SetTrigger(bSelect);
			BPOnSelect(bSelect, SelectWheelDataStructs.MaxTime, SelectTimer);
		}
	}
}

void UCommonSelectWheelSector::BPSetSelect_Implementation(bool InbSelect)
{
	UpdateColorAndOpacity();
}

void UCommonSelectWheelSector::SetTrigger(bool InbTrigger)
{
	if (bTrigger != InbTrigger)
	{
		bTrigger = InbTrigger;
		BPSetTrigger(InbTrigger);
	}
}

void UCommonSelectWheelSector::BPSetTrigger_Implementation(bool InbTrigger)
{
}

void UCommonSelectWheelSector::SetSlotAngle(float InAngle)
{
	SetSectorAngle((InAngle / 360.0f * -1.0f) + 0.25f);
	CanvasPanelWidget->SetRenderTransformAngle(InAngle);
	if (WidgetSlotSizeBoxWidget)
	{
		WidgetSlotSizeBoxWidget->SetRenderTransformAngle(InAngle * -1.0f);
	}
	if (ProgressCommonLazyImageWidget)
	{
		if (UMaterialInstanceDynamic* MaterialInstanceDynamic = ProgressCommonLazyImageWidget->GetDynamicMaterial())
		{
			MaterialInstanceDynamic->SetScalarParameterValue(TEXT("StreamerRotation"), InAngle / 360.0f - 0.5f);
		}
	}
	BPSetSlotAngle(InAngle);
}

void UCommonSelectWheelSector::BPSetSlotAngle_Implementation(float InAngle)
{
}

void UCommonSelectWheelSector::SetSectorAngle(float InSectorAngle)
{
	if (SectorAngle != InSectorAngle)
	{
		SectorAngle = InSectorAngle;
	}
	if (CommonLazyImageWidget)
	{
		if (UMaterialInstanceDynamic* MaterialInstanceDynamic = CommonLazyImageWidget->GetDynamicMaterial())
		{
			MaterialInstanceDynamic->SetScalarParameterValue(TEXT("Angle"), SectorAngle);
		}
	}
	if (ProgressCommonLazyImageWidget)
	{
		if (UMaterialInstanceDynamic* MaterialInstanceDynamic = ProgressCommonLazyImageWidget->GetDynamicMaterial())
		{
			MaterialInstanceDynamic->SetScalarParameterValue(TEXT("Angle"), SectorAngle);
		}
	}
	if (WidgetSlotSizeBoxWidget)
	{
		float Y = (FMath::Abs(UUniversalBaseFunctionLibrary::GetClampIndex(SectorAngle + 0.25f, 0.0f, 0.5f)) - 0.5f) * SectorAngleYOffset * 2.0f;
		WidgetSlotSizeBoxWidget->SetRenderTranslation(FVector2D(0.0f, Y));
	}
}

void UCommonSelectWheelSector::SetSectorAngleProgress(float InSectorAngleProgress)
{
	if (SectorAngleProgress != InSectorAngleProgress)
	{
		SectorAngleProgress = InSectorAngleProgress;
	}
	if (WidgetSlotSizeBoxWidget)
	{
		float Size = FMath::Clamp(200 * (SectorAngleProgress / 0.2f), 50.0f, 200.0f);
		WidgetSlotSizeBoxWidget->SetWidthOverride(Size);
		WidgetSlotSizeBoxWidget->SetHeightOverride(Size);
	}
	if (CommonLazyImageWidget)
	{
		if (UMaterialInstanceDynamic* MaterialInstanceDynamic = CommonLazyImageWidget->GetDynamicMaterial())
		{
			MaterialInstanceDynamic->SetScalarParameterValue(TEXT("AngleProgress"), SectorAngleProgress * SectorAngleProgressMultiple);
		}
	}
	if (ProgressCommonLazyImageWidget)
	{
		if (UMaterialInstanceDynamic* MaterialInstanceDynamic = ProgressCommonLazyImageWidget->GetDynamicMaterial())
		{
			MaterialInstanceDynamic->SetScalarParameterValue(TEXT("AngleProgress"), SectorAngleProgress * SectorAngleProgressMultiple);
		}
	}
}

void UCommonSelectWheelSector::UpdateColorAndOpacity()
{
	SetTextColor(bSelect ? SelectWheelDataStructs.SelectTextColor : SelectWheelDataStructs.DefaultTextColor);
	SetImageColor(bSelect ? SelectWheelDataStructs.SelectImageColor : SelectWheelDataStructs.DefaultImageColor);
}

void UCommonSelectWheelSector::SetSelectWheelDataStructs(const FSelectWheelDataStruct& InSelectWheelDataStructs, int InSectorIndex)
{
	SectorIndex = InSectorIndex;
	SelectWheelDataStructs = InSelectWheelDataStructs;
	UpdateColorAndOpacity();
	SetText(BPGetText());
	if (SlotCommonLazyImageWidget)
	{
		SlotCommonLazyImageWidget->SetColorAndOpacity(SelectWheelDataStructs.ImageResourceColor);
	}
	SetSoftResource(SelectWheelDataStructs.SoftImageResource);

}

void UCommonSelectWheelSector::SetSoftResource(const TSoftObjectPtr<UObject>& InSoftResource)
{
	if (SlotCommonLazyImageWidget && !InSoftResource.IsNull())
	{
		SlotCommonLazyImageWidget->SetBrushFromLazyDisplayAsset(InSoftResource, true);
	}
}

FText UCommonSelectWheelSector::BPGetText_Implementation()
{
	return SelectWheelDataStructs.Name;
}

void UCommonSelectWheelSector::SetText(const FText& InText)
{
	if (SlotCommonTextBlockWidget)
	{
		SlotCommonTextBlockWidget->SetText(InText);
	}
}

void UCommonSelectWheelSector::SetTextColor(FLinearColor InColorAndOpacity)
{
	if (SlotCommonTextBlockWidget)
	{
		SlotCommonTextBlockWidget->SetColorAndOpacity(FSlateColor(InColorAndOpacity));
	}
}


void UCommonSelectWheelSector::SetImageColor(FLinearColor InColorAndOpacity)
{
	if (CommonLazyImageWidget)
	{
		CommonLazyImageWidget->SetColorAndOpacity(InColorAndOpacity);
	}
}