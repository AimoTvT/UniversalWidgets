// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Components/Overlay.h"
#include "Components/Button.h"
#include "CommonTextBlock.h"

#include "UWCommonButtonID.generated.h"

/**
 * 
 */
UCLASS()
class UNIVERSALWIDGETS_API UUWCommonButtonID : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UUWCommonButtonID();

	/** * ID */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "CommonButton")
	FString ID;



public:
	/** *  */
	UFUNCTION(BlueprintCallable, Category = "PictureSequence|Function")
	virtual void SetID(const FString& InID);

	/** *  */
	virtual void BindClicked(const FScriptDelegate& ScriptDelegate);


	/** *  */
	virtual void BindHovered(const FScriptDelegate& ScriptDelegate);

};
