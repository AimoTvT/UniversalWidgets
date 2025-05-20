// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonUIs/Selects/Bars/CommonSelectBarBase.h"
#include "Components/HorizontalBoxSlot.h"

void UCommonSelectBarBase::NativePreConstruct()
{
	Super::NativePreConstruct();
	SetSelectStripPercentage(SelectStripPercentage);
}

void UCommonSelectBarBase::SetSelectStripPercentage(float InPercentage)
{
	SelectStripPercentage = InPercentage;
	if (CommonTextBlockWidget)
	{
		if (UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(CommonTextBlockWidget->Slot))
		{
			FSlateChildSize SlateChildSize;
			SlateChildSize.Value = 1.0f - SelectStripPercentage;
			SlateChildSize.SizeRule = ESlateSizeRule::Type::Fill;
			HorizontalBoxSlot->SetSize(SlateChildSize);
		}
	}
	if (SelectSizeBoxWidget)
	{
		if (UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(SelectSizeBoxWidget->Slot))
		{
			FSlateChildSize SlateChildSize;
			SlateChildSize.Value = SelectStripPercentage;
			SlateChildSize.SizeRule = ESlateSizeRule::Type::Fill;
			HorizontalBoxSlot->SetSize(SlateChildSize);
		}
	}
}

