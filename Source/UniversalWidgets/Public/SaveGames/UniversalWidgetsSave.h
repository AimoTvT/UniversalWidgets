// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "Config/UniversalStruct.h"

#include "UniversalWidgetsSave.generated.h"

/**
 * 
 */
UCLASS()
class UNIVERSALWIDGETS_API UUniversalWidgetsSave : public USaveGame
{
	GENERATED_BODY()
	

public:



	/** *  */
	UPROPERTY(BlueprintReadWrite, Category = "UniversalWidgetsSave")
	TArray<FStringImageData> StringImageDatas;

	/** *  */
	UPROPERTY(BlueprintReadWrite, Category = "UniversalWidgetsSave")
	int ing;


public:


};
