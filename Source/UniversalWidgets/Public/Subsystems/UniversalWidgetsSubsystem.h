// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveGames/UniversalWidgetsSave.h"

#include "UniversalWidgetsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UNIVERSALWIDGETS_API UUniversalWidgetsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

public:

	static UUniversalWidgetsSubsystem* Get();

	/** *  */
	UPROPERTY(BlueprintReadWrite, Category = "UniversalWidgetsSubsystem")
	TObjectPtr<UUniversalWidgetsSave> MyUniversalWidgetsSave;
	
	/** *  */
	UPROPERTY(BlueprintReadWrite, Category = "UniversalWidgetsSubsystem")
	FString UniversalWidgetsSaveName = TEXT("UniversalWidgetsSave");

	


public:

	// 必须覆盖的生命周期方法
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "UniversalWidgetsSubsystem|Function")
	UUniversalWidgetsSave* GetUniversalWidgetsSave(int32 UserIndex);

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "UniversalWidgetsSubsystem|Function")
	bool SaveUniversalWidgetsSave(UUniversalWidgetsSave* InSettingSave, int32 UserIndex);



};
