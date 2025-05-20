// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"

#include "BackgroundImage.generated.h"

/**
 * 背景图片,支持自定义的
 */
UCLASS()
class UNIVERSALWIDGETS_API UBackgroundImage : public UImage
{
	GENERATED_BODY()
	

public:

	/** *  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBackgroundImage|Variable")
	FName Name;



public:


	virtual void OnWidgetRebuilt() override;

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "BackgroundImage|Function")
	virtual void NativeConstruct();

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "BackgroundImage|Function")
	virtual void InitBackground();

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "BackgroundImage|Function")
	virtual void AsyncBrushFromSoftObjectPtr(const TSoftObjectPtr<UObject>& InSoftObjectPtr);

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "BackgroundImage|Function")
	virtual bool SetBrushFromSoftPath(const FString& Path);

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "BackgroundImage|Function")
	virtual bool SetBrushFromSoftObjectPtr(const TSoftObjectPtr<UObject>& InSoftObjectPtr);
	
	/** *  */
	UFUNCTION(BlueprintCallable, Category = "BackgroundImage|Function")
	virtual bool SetBrushFromResourceObject(UObject* Object);

};
