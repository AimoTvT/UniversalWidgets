// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CommonUIs/Buttons/UWCommonButtonImageText.h"
#include "Components/HorizontalBox.h"
#include "Components/SizeBox.h"
#include "CommonTextBlock.h"
#include "CommonSelectBarBase.generated.h"

/**
 * 
 */
UCLASS()
class UNIVERSALWIDGETS_API UCommonSelectBarBase : public UUWCommonButtonImageText
{
	GENERATED_BODY()
public:

	/** *  */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonSelectStrip")
	TObjectPtr<UHorizontalBox> HorizontalBoxWidget;

	/** *  */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonSelectStrip")
	TObjectPtr<USizeBox> SelectSizeBoxWidget;

	/** * 选择条形占比 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true, UIMin = "0", UIMax = "1"), Category = "CommonSelectWheel")
	float SelectStripPercentage = 0.5f;

	/** * 描述 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "CommonButton")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UUserWidget> SoftUserWidgetClass;

protected:

	virtual void NativePreConstruct() override;

public:

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void SetSelectStripPercentage(float InPercentage);
	
};
