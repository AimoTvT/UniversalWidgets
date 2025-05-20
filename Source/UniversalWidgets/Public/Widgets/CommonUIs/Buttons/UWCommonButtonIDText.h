// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CommonUIs/Buttons/UWCommonButtonID.h"
#include "Components/Overlay.h"
#include "Components/Button.h"
#include "CommonTextBlock.h"

#include "UWCommonButtonIDText.generated.h"

/**
 * 
 */
UCLASS()
class UNIVERSALWIDGETS_API UUWCommonButtonIDText : public UUWCommonButtonID
{
	GENERATED_BODY()

public:
	UUWCommonButtonIDText();
	/** * 文字控件 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonButton")
	TObjectPtr<UCommonTextBlock> CommonTextBlockWidget;

	/** * 文本 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "CommonButton")
	FText Text;

	/** References the Text style asset that defines a style in multiple sizes */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Style, meta = (ExposeOnSpawn = true))
	TSubclassOf<UCommonTextStyle> TextStyle;

	/** *  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Style)
	FSlateColor TextColorAndOpacity = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));


protected:
	virtual void NativePreConstruct() override;

public:

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "PictureSequence|Function")
	virtual void SetText(const FText& InText);

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "PictureSequence|Function")
	virtual void SetTextStyle(TSubclassOf<UCommonTextStyle> InTextStyle);

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "PictureSequence|Function")
	virtual void SetTextColorAndOpacity(FSlateColor InColorAndOpacity);


};
