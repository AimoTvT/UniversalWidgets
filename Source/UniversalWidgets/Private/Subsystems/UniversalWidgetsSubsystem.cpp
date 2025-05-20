// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/UniversalWidgetsSubsystem.h"
#include "Kismet/GameplayStatics.h"

UUniversalWidgetsSubsystem* UUniversalWidgetsSubsystem::Get()
{
	// 保存有效值
	static TWeakObjectPtr<UUniversalWidgetsSubsystem> UniversalWidgetsSubsystemPtr;

	// 双重校验锁模式
	if (!UniversalWidgetsSubsystemPtr.IsValid() && GWorld && GWorld->GetGameInstance())
	{
		UniversalWidgetsSubsystemPtr = GWorld->GetGameInstance()->GetSubsystem<UUniversalWidgetsSubsystem>();
	}
	return UniversalWidgetsSubsystemPtr.Get();
}


void UUniversalWidgetsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUniversalWidgetsSubsystem::Deinitialize()
{
	Super::Deinitialize();
}


UUniversalWidgetsSave* UUniversalWidgetsSubsystem::GetUniversalWidgetsSave(int32 UserIndex)
{
	if (MyUniversalWidgetsSave)
	{
		return MyUniversalWidgetsSave;
	}
	if (UGameplayStatics::DoesSaveGameExist(UniversalWidgetsSaveName, UserIndex))
	{
		USaveGame* LoadSaveGame = UGameplayStatics::LoadGameFromSlot(UniversalWidgetsSaveName, UserIndex);
		if (LoadSaveGame)
		{
			MyUniversalWidgetsSave = Cast<UUniversalWidgetsSave>(LoadSaveGame);
			if (MyUniversalWidgetsSave)
			{
				MyUniversalWidgetsSave->AddToRoot();
				return MyUniversalWidgetsSave;
			}
			else
			{
				LoadSaveGame->RemoveFromRoot();
				LoadSaveGame->ConditionalBeginDestroy();
			}
			UGameplayStatics::DeleteGameInSlot(UniversalWidgetsSaveName, UserIndex);
		}
	}
	USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(UUniversalWidgetsSave::StaticClass());
	if (SaveGame)
	{
		UGameplayStatics::SaveGameToSlot(SaveGame, UniversalWidgetsSaveName, UserIndex);
		MyUniversalWidgetsSave = Cast<UUniversalWidgetsSave>(SaveGame);
		if (MyUniversalWidgetsSave)
		{
			MyUniversalWidgetsSave->AddToRoot();
		}
		else
		{
			SaveGame->RemoveFromRoot();
			SaveGame->ConditionalBeginDestroy();
		}
	}
	return MyUniversalWidgetsSave;
}

bool UUniversalWidgetsSubsystem::SaveUniversalWidgetsSave(UUniversalWidgetsSave* InSettingSave, int32 UserIndex)
{
	if (InSettingSave)
	{
		return UGameplayStatics::SaveGameToSlot(InSettingSave, UniversalWidgetsSaveName, UserIndex);
	}
	return false;
}