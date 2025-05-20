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


#include "Widgets/SelectHorizontalBox/SelectHorizontalBox.h"
#include "Widgets/IDButton/IDButton.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBoxSlot.h"


USelectHorizontalBox::USelectHorizontalBox()
{
	// 加载蓝图类
	static ConstructorHelpers::FClassFinder<UUWCommonButtonIDText> BP_CommonButtonIDTextClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/UniversalWidgets/Widgets/CommonUIs/Buttons/WBP_UWCommonButtonIDText.WBP_UWCommonButtonIDText_C'"));
	if (BP_CommonButtonIDTextClass.Succeeded())
	{
		UUWCommonButtonIDTextClass = BP_CommonButtonIDTextClass.Class;
	}
	// 加载蓝图类
	static ConstructorHelpers::FClassFinder<UCommonButtonStyle> BP_CommonButtonStyle(TEXT("/Script/Engine.Blueprint'/UniversalWidgets/Widgets/CommonUIs/Buttons/Styles/DefaultCommonButtonStyle.DefaultCommonButtonStyle_C'"));
	if (BP_CommonButtonStyle.Succeeded())
	{
		DefaultButtonStyle = BP_CommonButtonStyle.Class;
		SelectButtonStyle = BP_CommonButtonStyle.Class;
	}
	static ConstructorHelpers::FClassFinder<UCommonTextStyle> BP_CommonTextStyle(TEXT("/Script/Engine.Blueprint'/UniversalWidgets/Widgets/CommonUIs/Buttons/Styles/DefaultCommonButtonTextStyle.DefaultCommonButtonTextStyle_C'"));
	if (BP_CommonTextStyle.Succeeded())
	{
		DefaultTextStyle = BP_CommonTextStyle.Class;
		SelectTextStyle = BP_CommonTextStyle.Class;
	}
}

void USelectHorizontalBox::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	if (!IsDesignTime())
	{
		NativeConstruct();
	}
}

//void USelectHorizontalBox::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
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

void USelectHorizontalBox::NativeConstruct()
{
	InitButton();
}


void USelectHorizontalBox::OnClickedID_Event(UCommonButtonBase* InCommonButtonBase)
{
	UUWCommonButtonIDText* UWCommonButtonIDText = Cast<UUWCommonButtonIDText>(InCommonButtonBase);
	if (UWCommonButtonIDText)
	{
		FString ButtonID = UWCommonButtonIDText->ID;
		if (SelectIndex != IDs.Find(UWCommonButtonIDText->ID))
		{
			OnClickedSelect.Broadcast(ID, ButtonID);
			SetSelectIndex(IDs.Find(ButtonID));
		}
	}
}

void USelectHorizontalBox::OnHoveredID_Event(UCommonButtonBase* InCommonButtonBase)
{
	UUWCommonButtonIDText* UWCommonButtonIDText = Cast<UUWCommonButtonIDText>(InCommonButtonBase);
	if (UWCommonButtonIDText)
	{
		OnHoverSelect.Broadcast(ID, UWCommonButtonIDText->ID);
	}
}

void USelectHorizontalBox::SetSelectIndex(int Index, bool bDelegate)
{
	if (bDelegate && IDs.IsValidIndex(Index))
	{
		OnClickedSelect.Broadcast(ID, IDs[Index]);
	}
	if (Index != -1 && SelectIndex != Index)
	{
		if (UWCommonButtonIDTextWidgets.IsValidIndex(SelectIndex))
		{
			UWCommonButtonIDTextWidgets[SelectIndex]->SetStyle(DefaultButtonStyle);
		}
		if (UWCommonButtonIDTextWidgets.IsValidIndex(Index))
		{
			UWCommonButtonIDTextWidgets[Index]->SetStyle(SelectButtonStyle);
		}
		SelectIndex = Index;
	}
}

void USelectHorizontalBox::InitButton()
{
	for (size_t i = 0; i < UWCommonButtonIDTextWidgets.Num(); i++)
	{
		UWCommonButtonIDTextWidgets[i]->RemoveFromParent();
	}
	UWCommonButtonIDTextWidgets.Empty();
	for (size_t i = 0; i < IDs.Num(); i++)
	{
		UUWCommonButtonIDText* UWCommonButtonIDText = CreateWidget<UUWCommonButtonIDText>(GetOwningPlayer(), UUWCommonButtonIDTextClass);
		if (UWCommonButtonIDText == nullptr)
		{
			return;
		}
		UWCommonButtonIDText->SetID(IDs[i]);
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, TEXT("OnClickedID_Event"));
		UWCommonButtonIDText->BindClicked(ScriptDelegate);
		ScriptDelegate.BindUFunction(this, TEXT("OnHoveredID_Event"));
		UWCommonButtonIDText->BindHovered(ScriptDelegate);
		UWCommonButtonIDText->SetStyle(SelectIndex == i ? SelectButtonStyle : DefaultButtonStyle);
		UWCommonButtonIDText->SetText(Texts.IsValidIndex(i) ? Texts[i] : FText());
		UWCommonButtonIDText->SetTextStyle(SelectIndex == i ? SelectTextStyle : DefaultTextStyle);
		UWCommonButtonIDTextWidgets.Add(UWCommonButtonIDText);
		UPanelSlot* PanelSlot = AddChild(UWCommonButtonIDText);
		if (PanelSlot)
		{
			UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(PanelSlot);
			if (HorizontalBoxSlot)
			{
				HorizontalBoxSlot->SetPadding(StylePadding);
				HorizontalBoxSlot->SetSize(FSlateChildSize());
			}
		}
	}
}

void USelectHorizontalBox::InitData(TArray<FString> InIDs, TArray<FText> InTexts)
{
	IDs = InIDs;
	Texts = InTexts;
	InitButton();
}

void USelectHorizontalBox::SetSelectID(const FString& OnID, bool bDelegate)
{
	if (bDelegate && IDs.Find(OnID) != -1)
	{
		OnClickedSelect.Broadcast(ID, OnID);
	}
	SetSelectIndex(IDs.Find(OnID));
}
