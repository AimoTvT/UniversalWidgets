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


#include "Widgets/SizeBoxIDButton/SizeBoxIDButton.h"



void USizeBoxIDButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	if (!IsDesignTime())
	{
		NativeConstruct();
	}
}

//void USizeBoxIDButton::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
//{
//	Super::PostEditChangeProperty(PropertyChangedEvent);
//	if (PropertyChangedEvent.ChangeType != EPropertyChangeType::Interactive)
//	{
//		TSharedPtr<SWidget> SafeWidget = GetCachedWidget();
//		if (SafeWidget.IsValid())
//		{
//			// Re-Run execute PreConstruct when we get a post edit property change, to do something
//			// akin to running Sync Properties, so users don't have to recompile to see updates.
//			NativePreConstruct();
//		}
//	}
//}

void USizeBoxIDButton::NativeConstruct()
{
	if (ButtonWidget == nullptr)
	{
		ButtonWidget = NewObject<UButton>(this);
		ButtonWidget->OnClicked.AddDynamic(this, &USizeBoxIDButton::OnClickedID_Event);
		ButtonWidget->OnHovered.AddDynamic(this, &USizeBoxIDButton::OnHoveredID_Event);
		ButtonWidget->SetStyle(ButtonStyle);
		ClearChildren();
		AddChild(ButtonWidget);
	}
	
}

void USizeBoxIDButton::OnClickedID_Event()
{
	OnClickedID.Broadcast(ID);
}

void USizeBoxIDButton::OnHoveredID_Event()
{
	OnHoverID.Broadcast(ID);
}

void USizeBoxIDButton::SetID(const FString& InID)
{
	ID = InID;
}

void USizeBoxIDButton::SetButtonStyle(const FButtonStyle& InButtonStyle)
{
	ButtonStyle = InButtonStyle;
	if (ButtonWidget)
	{
		ButtonWidget->SetStyle(ButtonStyle);
	}
}

void USizeBoxIDButton::BindScriptDelegate(UObject* InObject, const FName& InFunctionName, bool bClicked)
{
	if (InObject)
	{
		FScriptDelegate ScriptDelegate; //建立对接变量
		ScriptDelegate.BindUFunction(InObject, InFunctionName); //对接变量绑定函数
		if (bClicked)
		{
			OnClickedID.Add(ScriptDelegate);
		}
		else
		{
			OnHoverID.Add(ScriptDelegate);
		}
	}
}
