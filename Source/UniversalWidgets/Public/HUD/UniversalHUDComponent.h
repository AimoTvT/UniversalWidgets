// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HUD/UniversalHUDWidget.h"
#include "GameFramework/HUD.h"

#include "UniversalHUDComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNIVERSALWIDGETS_API UUniversalHUDComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUniversalHUDComponent();

	/** *  */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	TObjectPtr<AHUD> HUD;

	/** *  */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	TObjectPtr<UUniversalHUDWidget> UniversalHUDWidget;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitWidget(TSubclassOf<UUniversalHUDWidget> InUniversalHUDWidgetClass);

	

		
};
