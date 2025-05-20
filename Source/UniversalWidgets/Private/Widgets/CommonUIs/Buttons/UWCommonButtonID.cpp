// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonUIs/Buttons/UWCommonButtonID.h"

UUWCommonButtonID::UUWCommonButtonID()
{
	// 加载蓝图类
	static ConstructorHelpers::FClassFinder<UCommonButtonStyle> BP_CommonButtonStyle(TEXT("/Script/Engine.Blueprint'/UniversalWidgets/Widgets/CommonUIs/Buttons/Styles/DefaultCommonButtonStyle.DefaultCommonButtonStyle_C'"));
	if (BP_CommonButtonStyle.Succeeded())
	{
		SetStyle(BP_CommonButtonStyle.Class);
	}
}

void UUWCommonButtonID::SetID(const FString& InID)
{
	ID = InID;
}

void UUWCommonButtonID::BindClicked(const FScriptDelegate& ScriptDelegate)
{
	if (ScriptDelegate.IsBound())
	{
		OnButtonBaseClicked.Add(ScriptDelegate);
	}
}
void UUWCommonButtonID::BindHovered(const FScriptDelegate& ScriptDelegate)
{
	if (ScriptDelegate.IsBound())
	{
		OnButtonBaseHovered.Add(ScriptDelegate);
	}
}