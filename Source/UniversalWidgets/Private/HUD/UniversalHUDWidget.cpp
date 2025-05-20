// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/UniversalHUDWidget.h"
#include "HUD/UniversalHUDSubsystem.h"
#include "HUD/UniversalHUDComponent.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "FunctionLibrary/UniversalBaseFunctionLibrary.h"

TSharedRef<SWidget> UUniversalHUDWidget::RebuildWidget()
{
	CommonActivatableWidgetSwitcher = WidgetTree->ConstructWidget<UCommonActivatableWidgetSwitcher>(UCommonActivatableWidgetSwitcher::StaticClass(), FName(TEXT("CommonActivatableWidgetSwitcher")));
	if (CommonActivatableWidgetSwitcher)
	{
		MainCanvasPanelWidget = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), FName(TEXT("MainCanvasPanelWidget")));
		if (MainCanvasPanelWidget)
		{
			UPanelSlot* PanelSlot = CommonActivatableWidgetSwitcher->AddChild(MainCanvasPanelWidget);

			UICanvasPanelWidget = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), FName(TEXT("UICanvasPanelWidget")));
			if (UICanvasPanelWidget)
			{
				PanelSlot = MainCanvasPanelWidget->AddChild(UICanvasPanelWidget);
				if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PanelSlot))
				{
					CanvasPanelSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
					CanvasPanelSlot->SetPosition(FVector2D(0.0f, 0.0f));
					CanvasPanelSlot->SetSize(FVector2D(0.0f, 0.0f));
					CanvasPanelSlot->SetZOrder(0);
				}
			}

			PlayerCommonActivatableWidgetStack = WidgetTree->ConstructWidget<UCommonActivatableWidgetStack>(UCommonActivatableWidgetStack::StaticClass(), FName(TEXT("PlayerCommonActivatableWidgetStack")));
			if (PlayerCommonActivatableWidgetStack)
			{
				PanelSlot = MainCanvasPanelWidget->AddChild(PlayerCommonActivatableWidgetStack);
				if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PanelSlot))
				{
					CanvasPanelSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
					CanvasPanelSlot->SetPosition(FVector2D(0.0f, 0.0f));
					CanvasPanelSlot->SetSize(FVector2D(0.0f, 0.0f));
					CanvasPanelSlot->SetZOrder(10);
				}
			}

			SystemCommonActivatableWidgetStack = WidgetTree->ConstructWidget<UCommonActivatableWidgetStack>(UCommonActivatableWidgetStack::StaticClass(), FName(TEXT("SystemCommonActivatableWidgetStack")));
			if (SystemCommonActivatableWidgetStack)
			{
				PanelSlot = MainCanvasPanelWidget->AddChild(SystemCommonActivatableWidgetStack);
				if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PanelSlot))
				{
					CanvasPanelSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
					CanvasPanelSlot->SetPosition(FVector2D(0.0f, 0.0f));
					CanvasPanelSlot->SetSize(FVector2D(0.0f, 0.0f));
					CanvasPanelSlot->SetZOrder(20);
				}
			}
		}
		// 将根控件添加到 UserWidget 中
		WidgetTree->RootWidget = CommonActivatableWidgetSwitcher;
	}
	return Super::RebuildWidget();
}

void UUniversalHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (PlayerCommonActivatableWidgetStack)
	{
		PlayerDelegateHandle = PlayerCommonActivatableWidgetStack->OnDisplayedWidgetChanged().AddUObject(this, &UUniversalHUDWidget::PlayerOnActivatable);
	}
	if (SystemCommonActivatableWidgetStack)
	{
		SystemDelegateHandle = SystemCommonActivatableWidgetStack->OnDisplayedWidgetChanged().AddUObject(this, &UUniversalHUDWidget::SystemOnActivatable);
	}
}

void UUniversalHUDWidget::NativeDestruct()
{
	Super::NativeConstruct();
	if (PlayerCommonActivatableWidgetStack)
	{
		PlayerCommonActivatableWidgetStack->OnDisplayedWidgetChanged().Remove(PlayerDelegateHandle);
	}
	if (SystemCommonActivatableWidgetStack)
	{
		SystemCommonActivatableWidgetStack->OnDisplayedWidgetChanged().Remove(SystemDelegateHandle);
	}
}

void UUniversalHUDWidget::PlayerOnActivatable(UCommonActivatableWidget* ActivatableCommonActivatableWidget)
{
	SetPlayerCommonActivatableWidget(ActivatableCommonActivatableWidget);
}

void UUniversalHUDWidget::SystemOnActivatable(UCommonActivatableWidget* ActivatableCommonActivatableWidget)
{
	SetSystemCommonActivatableWidget(ActivatableCommonActivatableWidget);
}

void UUniversalHUDWidget::UpdateInputMode()
{
	if (PlayerCommonActivatableWidget || SystemCommonActivatableWidget)
	{
		UUniversalBaseFunctionLibrary::SetInputModeAndMouse(true, GetOwningPlayer());
	}
	else
	{
		UUniversalBaseFunctionLibrary::SetInputModeAndMouse(false, GetOwningPlayer());
	}
}

void UUniversalHUDWidget::SetPlayerCommonActivatableWidget(UCommonActivatableWidget* InPlayerCommonActivatableWidget)
{
	if (PlayerCommonActivatableWidget != InPlayerCommonActivatableWidget)
	{
		if (PlayerCommonActivatableWidget)
		{
			PlayerCommonActivatableWidget->OnDeactivated().Remove(PlayerDelegateHandle);
			if (UUniversalHUDSubsystem::Get())
			{
				UUniversalHUDSubsystem::Get()->RemoveControlWidget(GetOwningPlayer(), PlayerCommonActivatableWidget);
			}
		}
		PlayerCommonActivatableWidget = InPlayerCommonActivatableWidget;
		if (PlayerCommonActivatableWidget)
		{
			if (UUniversalHUDSubsystem::Get())
			{
				UUniversalHUDSubsystem::Get()->AddControlWidget(GetOwningPlayer(), PlayerCommonActivatableWidget);
			}
		}
	}
}

void UUniversalHUDWidget::SetSystemCommonActivatableWidget(UCommonActivatableWidget* InSystemCommonActivatableWidget)
{
	if (SystemCommonActivatableWidget != InSystemCommonActivatableWidget)
	{
		if (SystemCommonActivatableWidget)
		{
			SystemCommonActivatableWidget->OnDeactivated().Remove(SystemDelegateHandle); 
			if (UUniversalHUDSubsystem::Get())
			{
				UUniversalHUDSubsystem::Get()->RemoveControlWidget(GetOwningPlayer(), SystemCommonActivatableWidget);
			}
		}
		SystemCommonActivatableWidget = InSystemCommonActivatableWidget;
		if (SystemCommonActivatableWidget)
		{
			if (UUniversalHUDSubsystem::Get())
			{
				UUniversalHUDSubsystem::Get()->AddControlWidget(GetOwningPlayer(), SystemCommonActivatableWidget);
			}
		}
	}
}

void UUniversalHUDWidget::SetUniversalHUDComponent(UUniversalHUDComponent* InUniversalHUDComponent)
{
	if (UniversalHUDComponent != InUniversalHUDComponent)
	{
		UniversalHUDComponent = InUniversalHUDComponent;
	}
}

bool UUniversalHUDWidget::AddWidgetStackInternal(UCommonActivatableWidget* ActivatableWidget, bool bSystem)
{
	if (!ActivatableWidget || !SystemCommonActivatableWidgetStack)
	{
		return false;
	}
	if (bSystem)
	{
		SystemCommonActivatableWidgetStack->AddWidgetInstance(*ActivatableWidget);
		if (SystemCommonActivatableWidgetStack->GetActiveWidget() == ActivatableWidget)
		{
			SetSystemCommonActivatableWidget(ActivatableWidget);
		}
		return true;
	}
	else
	{
		PlayerCommonActivatableWidgetStack->AddWidgetInstance(*ActivatableWidget);
		if (PlayerCommonActivatableWidgetStack->GetActiveWidget() == ActivatableWidget)
		{
			SetPlayerCommonActivatableWidget(ActivatableWidget);
		}
		return true;
	}
}

UCommonActivatableWidget* UUniversalHUDWidget::AddClassWidgetStackInternal(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass, bool bSystem)
{
	if (!ActivatableWidgetClass || !SystemCommonActivatableWidgetStack)
	{
		return nullptr;
	}
	if (bSystem)
	{
		UCommonActivatableWidget* CommonActivatableWidget = SystemCommonActivatableWidgetStack->AddWidget(ActivatableWidgetClass);
		if (CommonActivatableWidget)
		{
			if (UUniversalHUDSubsystem::Get())
			{
				UUniversalHUDSubsystem::Get()->AddControlWidget(GetOwningPlayer(), CommonActivatableWidget);
			}
			if (SystemCommonActivatableWidgetStack->GetActiveWidget() == CommonActivatableWidget)
			{
				SetSystemCommonActivatableWidget(CommonActivatableWidget);
			}
		}
		return CommonActivatableWidget;
	}
	else
	{
		UCommonActivatableWidget* CommonActivatableWidget = PlayerCommonActivatableWidgetStack->AddWidget(ActivatableWidgetClass);
		if (CommonActivatableWidget)
		{
			if (UUniversalHUDSubsystem::Get())
			{
				UUniversalHUDSubsystem::Get()->AddControlWidget(nullptr, CommonActivatableWidget);
			}
			if (SystemCommonActivatableWidgetStack->GetActiveWidget() == CommonActivatableWidget)
			{
				SetPlayerCommonActivatableWidget(CommonActivatableWidget);
			}
		}
		return CommonActivatableWidget;
	}
}

UCanvasPanelSlot* UUniversalHUDWidget::AddWidgetCanvasPanelInternal(UWidget* InWidget, uint8 ZOrderClassIndex, int ZOrder)
{
	return NativeAddWidgetCanvasPanelInternal(InWidget, ZOrderClassIndex, ZOrder);
}

UCanvasPanelSlot* UUniversalHUDWidget::NativeAddWidgetCanvasPanelInternal(UWidget* InWidget, uint8 ZOrderClassIndex, int ZOrder, FAnchors InAnchors, FVector2D InPosition, FVector2D InSize)
{
	if (InWidget)
	{
		UPanelSlot* PanelSlot = UICanvasPanelWidget->AddChild(InWidget);
		if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PanelSlot))
		{
			CanvasPanelSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
			CanvasPanelSlot->SetPosition(FVector2D(0.0f, 0.0f));
			CanvasPanelSlot->SetSize(FVector2D(0.0f, 0.0f));
			CanvasPanelSlot->SetZOrder(ZOrderClassIndex * 1000 + ZOrder);
			return CanvasPanelSlot;
		}
	}
	return nullptr;
}

UWidget* UUniversalHUDWidget::AddClassWidgetCanvasPanelInternal(TSubclassOf<UWidget> WidgetClass, uint8 ZOrderClassIndex, int ZOrder)
{
	return NativeAddClassWidgetCanvasPanelInternal(WidgetClass, ZOrderClassIndex, ZOrder);
}

UWidget* UUniversalHUDWidget::NativeAddClassWidgetCanvasPanelInternal(TSubclassOf<UWidget> WidgetClass, uint8 ZOrderClassIndex, int ZOrder, FAnchors InAnchors, FVector2D InPosition, FVector2D InSize)
{
	if (!WidgetClass)
	{
		return nullptr;
	}
	UWidget* Widget = WidgetTree->ConstructWidget<UWidget>(WidgetClass);
	if (Widget)
	{
		NativeAddWidgetCanvasPanelInternal(Widget, ZOrderClassIndex, ZOrder, InAnchors, InPosition, InSize);
	}
	return Widget;
}