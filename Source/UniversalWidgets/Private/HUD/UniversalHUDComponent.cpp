// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/UniversalHUDComponent.h"

// Sets default values for this component's properties
UUniversalHUDComponent::UUniversalHUDComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUniversalHUDComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (GetOwner())
	{
		HUD = Cast<AHUD>(GetOwner());
	}
	
}


// Called every frame
void UUniversalHUDComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUniversalHUDComponent::InitWidget(TSubclassOf<UUniversalHUDWidget> InUniversalHUDWidgetClass)
{
	if (!InUniversalHUDWidgetClass)
	{
		InUniversalHUDWidgetClass = UUniversalHUDWidget::StaticClass();
	}
	UniversalHUDWidget = CreateWidget<UUniversalHUDWidget>(GetWorld(), InUniversalHUDWidgetClass);
	if (UniversalHUDWidget)
	{
		UniversalHUDWidget->SetUniversalHUDComponent(this);
		UniversalHUDWidget->AddToViewport(2);
	}
}

