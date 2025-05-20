// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonUIs/Buttons/UWCommonButtonIDText.h"

UUWCommonButtonIDText::UUWCommonButtonIDText()
{
	static ConstructorHelpers::FClassFinder<UCommonTextStyle> BP_CommonTextStyle(TEXT("/Script/Engine.Blueprint'/UniversalWidgets/Widgets/CommonUIs/Buttons/Styles/DefaultCommonButtonTextStyle.DefaultCommonButtonTextStyle_C'"));
	if (BP_CommonTextStyle.Succeeded())
	{
		if (CommonTextBlockWidget)
		{
			CommonTextBlockWidget->SetStyle(BP_CommonTextStyle.Class);
		}
	}
}

void UUWCommonButtonIDText::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (CommonTextBlockWidget)
	{
		CommonTextBlockWidget->SetText(Text);
		CommonTextBlockWidget->SetStyle(TextStyle);
		CommonTextBlockWidget->SetColorAndOpacity(TextColorAndOpacity);
	}
	return;
}

void UUWCommonButtonIDText::SetTextStyle(TSubclassOf<UCommonTextStyle> InTextStyle)
{
	if (CommonTextBlockWidget)
	{
		CommonTextBlockWidget->SetStyle(TextStyle);
	}
}

void UUWCommonButtonIDText::SetTextColorAndOpacity(FSlateColor InColorAndOpacity)
{
	TextColorAndOpacity = InColorAndOpacity;
	if (CommonTextBlockWidget)
	{
		CommonTextBlockWidget->SetColorAndOpacity(InColorAndOpacity);
	}
}

void UUWCommonButtonIDText::SetText(const FText& InText)
{
	Text = InText;
	if (CommonTextBlockWidget)
	{
		CommonTextBlockWidget->SetText(InText);
	}
}
