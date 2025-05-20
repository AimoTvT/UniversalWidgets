// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/UniversalHUDSubsystem.h"
#include "GameFramework/HUD.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

UUniversalHUDSubsystem* UUniversalHUDSubsystem::Get()
{
	// 保存有效值
	static TWeakObjectPtr<UUniversalHUDSubsystem> UniversalHUDSubsystemPtr;

	// 双重校验锁模式
	if (!UniversalHUDSubsystemPtr.IsValid() && GWorld && GWorld->GetGameInstance())
	{
		UniversalHUDSubsystemPtr = GWorld->GetGameInstance()->GetSubsystem<UUniversalHUDSubsystem>();
	}
	return UniversalHUDSubsystemPtr.Get();
}



void UUniversalHUDSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUniversalHUDSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

UUniversalHUDComponent* UUniversalHUDSubsystem::AddPlayerController(APlayerController* InPlayerController, TSubclassOf<UUniversalHUDWidget> InUniversalHUDWidgetClass)
{
	if (InPlayerController && InPlayerController->IsLocalPlayerController())
	{
		if (!UniversalHUDComponents.FindRef(InPlayerController))
		{
			if (AHUD* HUDPtr = InPlayerController->GetHUD())
			{
				UUniversalHUDComponent* UniversalHUDComponent = NewObject<UUniversalHUDComponent>(HUDPtr, TEXT("UniversalHUDComponent"));
				if (UniversalHUDComponent)
				{
					UniversalHUDComponent->RegisterComponent();
					UniversalHUDComponent->InitWidget(InUniversalHUDWidgetClass);
					return UniversalHUDComponents.Add(InPlayerController, UniversalHUDComponent);
				}
			}
		}
	}
	return nullptr;
}

bool UUniversalHUDSubsystem::AddWidgetStackInternal(APlayerController* TargetPlayerController, UCommonActivatableWidget* ActivatableWidget, bool bSystem)
{
	if (!TargetPlayerController && !UniversalHUDComponents.IsEmpty())
	{
		TargetPlayerController = UniversalHUDComponents.begin()->Key;
	}
	if (TargetPlayerController && TargetPlayerController->IsLocalPlayerController())
	{
		if (UUniversalHUDComponent* UniversalHUDComponent = UniversalHUDComponents.FindRef(TargetPlayerController); UniversalHUDComponent->UniversalHUDWidget)
		{
			return UniversalHUDComponent->UniversalHUDWidget->AddWidgetStackInternal(ActivatableWidget, bSystem);
		}
		if (UUniversalHUDComponent* UniversalHUDComponent = AddPlayerController(TargetPlayerController))
		{
			return UniversalHUDComponent->UniversalHUDWidget->AddWidgetStackInternal(ActivatableWidget, bSystem);
		}
	}
	return false;
}

UCommonActivatableWidget* UUniversalHUDSubsystem::AddClassWidgetStackInternal(APlayerController* TargetPlayerController, TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass, bool bSystem)
{
	if (!TargetPlayerController && !UniversalHUDComponents.IsEmpty())
	{
		TargetPlayerController = UniversalHUDComponents.begin()->Key;
	}
	if (TargetPlayerController && TargetPlayerController->IsLocalPlayerController())
	{
		if (UUniversalHUDComponent* UniversalHUDComponent = UniversalHUDComponents.FindRef(TargetPlayerController); UniversalHUDComponent->UniversalHUDWidget)
		{
			return UniversalHUDComponent->UniversalHUDWidget->AddClassWidgetStackInternal(ActivatableWidgetClass, bSystem);
		}
		if (UUniversalHUDComponent* UniversalHUDComponent = AddPlayerController(TargetPlayerController))
		{
			return UniversalHUDComponent->UniversalHUDWidget->AddClassWidgetStackInternal(ActivatableWidgetClass, bSystem);
		}
	}
	return nullptr;
}

UCanvasPanelSlot* UUniversalHUDSubsystem::AddWidgetCanvasPanelInternal(APlayerController* TargetPlayerController, UWidget* InWidget, uint8 ZOrderClassIndex, int ZOrder)
{
	if (!TargetPlayerController && !UniversalHUDComponents.IsEmpty())
	{
		TargetPlayerController = UniversalHUDComponents.begin()->Key;
	}
	if (TargetPlayerController && TargetPlayerController->IsLocalPlayerController())
	{
		if (UUniversalHUDComponent* UniversalHUDComponent = UniversalHUDComponents.FindRef(TargetPlayerController); UniversalHUDComponent->UniversalHUDWidget)
		{
			return UniversalHUDComponent->UniversalHUDWidget->AddWidgetCanvasPanelInternal(InWidget, ZOrderClassIndex, ZOrder);
		}
		if (UUniversalHUDComponent* UniversalHUDComponent = AddPlayerController(TargetPlayerController))
		{
			return UniversalHUDComponent->UniversalHUDWidget->AddWidgetCanvasPanelInternal(InWidget, ZOrderClassIndex, ZOrder);
		}
	}
	return nullptr;
}

UWidget* UUniversalHUDSubsystem::AddClassWidgetCanvasPanelInternal(APlayerController* TargetPlayerController, TSubclassOf<UWidget> WidgetClass, uint8 ZOrderClassIndex, int ZOrder)
{
	if (!TargetPlayerController && !UniversalHUDComponents.IsEmpty())
	{
		TargetPlayerController = UniversalHUDComponents.begin()->Key;
	}
	if (TargetPlayerController && TargetPlayerController->IsLocalPlayerController())
	{
		if (UUniversalHUDComponent* UniversalHUDComponent = UniversalHUDComponents.FindRef(TargetPlayerController); UniversalHUDComponent->UniversalHUDWidget)
		{
			return UniversalHUDComponent->UniversalHUDWidget->AddClassWidgetCanvasPanelInternal(WidgetClass, ZOrderClassIndex, ZOrder);
		}
		if (UUniversalHUDComponent* UniversalHUDComponent = AddPlayerController(TargetPlayerController))
		{
			return UniversalHUDComponent->UniversalHUDWidget->AddClassWidgetCanvasPanelInternal(WidgetClass, ZOrderClassIndex, ZOrder);
		}
	}
	return nullptr;
}



void UUniversalHUDSubsystem::AddControlWidget(APlayerController* InPlayerController, UWidget* ControlWidget, bool bGameAndUI, EMouseLockMode InMouseLockMode, const bool bFlushInput)
{
	if (!ControlWidget || ControlWidgets.Find(ControlWidget) != -1)
	{
		return;
	}
	if (!InPlayerController && GWorld)
	{
		InPlayerController = GWorld->GetFirstPlayerController();
	}
	if (InPlayerController)
	{
		ControlWidgets.Add(ControlWidget);
		InPlayerController->bShowMouseCursor++;
		if (bGameAndUI)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(InPlayerController, ControlWidget, InMouseLockMode, false, bFlushInput);
		}
		else
		{
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(InPlayerController, ControlWidget, InMouseLockMode, true);
		}
	}
}

void UUniversalHUDSubsystem::RemoveControlWidget(APlayerController* InPlayerController, UWidget* ControlWidget)
{
	if (!ControlWidget || ControlWidgets.Find(ControlWidget) == -1)
	{
		return;
	}
	if (!InPlayerController && GWorld)
	{
		InPlayerController = GWorld->GetFirstPlayerController();
	}
	if (InPlayerController)
	{
		ControlWidgets.Remove(ControlWidget);
		InPlayerController->bShowMouseCursor = ControlWidgets.Num();
		if (InPlayerController->bShowMouseCursor == 0)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(InPlayerController);
			return;
		}
		else
		{
			for (size_t i = ControlWidgets.Num() - 1; i < 0; i--)
			{
				if (ControlWidgets[i])
				{
					ControlWidgets[i]->SetUserFocus(InPlayerController);
				}
			}
		}
	}
}
