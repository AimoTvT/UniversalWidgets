// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Components/SizeBox.h"
#include "Components/CanvasPanel.h"
#include "CommonLazyImage.h"
#include "Widgets/CommonUIs/Selects/Wheels/CommonSelectWheel.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"


#include "CommonSelectWheelSector.generated.h"

/**
 * 
 */
UCLASS()
class UNIVERSALWIDGETS_API UCommonSelectWheelSector : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
	/** * 尺寸框控件 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonSelectWheel")
	TObjectPtr<USizeBox> SizeBoxWidget;

	/** * 控件 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonSelectWheel")
	TObjectPtr<UCanvasPanel> CanvasPanelWidget;

	/** *  */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonSelectWheel")
	TObjectPtr<UCommonLazyImage> CommonLazyImageWidget;

	/** *  */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonSelectWheel")
	TObjectPtr<UCommonLazyImage> ProgressCommonLazyImageWidget;

	/** * 控件插槽尺寸框控件 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonSelectWheel")
	TObjectPtr<USizeBox> WidgetSlotSizeBoxWidget;

	/** * 控件插槽尺寸框控件 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonSelectWheel")
	TObjectPtr<USizeBox> SlotSizeBoxWidget;

	/** *  */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonSelectWheel")
	TObjectPtr<UCommonLazyImage> SlotCommonLazyImageWidget;

	/** *  */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonSelectWheel")
	TObjectPtr<UCommonTextBlock> SlotCommonTextBlockWidget;


	/**
	 * 按下声音
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound, meta = (DisplayName = "Pressed Sound Override"))
	FSlateSound PressedSlateSoundOverride;

	/**
	 * 悬浮声音
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound, meta = (DisplayName = "Hovered Sound Override"))
	FSlateSound HoveredSlateSoundOverride;

	/** * 空控件 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "CommonSelectWheel")
	bool bNoWidget = true;

	/** * 选择 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "CommonSelectWheel")
	bool bSelect = false;

	/** * 触发 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "CommonSelectWheel")
	bool bTrigger = false;

	/** * 扇形索引 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "CommonSelectWheel")
	int SectorIndex = 0;

	/** * 选择时间时间 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "CommonSelectWheel")
	float SelectTimer = 0.0f;

	/** * 扇形角度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "CommonSelectWheel")
	float SectorAngle = 0.25f;

	/** * 扇形角度Y偏移 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "CommonSelectWheel")
	float SectorAngleYOffset1 = 0.25f;


	/** * 扇形角度Y偏移 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "CommonSelectWheel")
	float SectorAngleYOffset = 20.0f;

	/** * 扇形角度进度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "CommonSelectWheel")
	float SectorAngleProgress = 0.25f;

	/** * 扇形角度偏移进度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "CommonSelectWheel")
	float SectorAngleProgressMultiple = 1.0f;

	/** * 选择轮盘数据 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "CommonButton")
	FSelectWheelDataStruct SelectWheelDataStructs;



	/** * 时间句柄 */
	UPROPERTY(BlueprintReadWrite, Category = "CommonSelectWheel")
	FTimerHandle SelectTimerHandle;

	
protected:

	virtual void NativePreConstruct() override;

public:

	/** * 是否允许触发 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual bool IsAllowTrigger();

	/** * 触发 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void OnTrigger();

	/** * 触发选择事件 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void OnSelect_Event();

	/** * 蓝图触发选择事件 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CommonSelect|Function")
	void BPOnSelect(bool InSelect, float InMaxTimer, float InTimer);

	/** * 设置选择 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void SetSelect(bool InbSelect);

	/** * 蓝图设置选择 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CommonSelect|Function")
	void BPSetSelect(bool InbSelect);

	/** * 设置触发 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void SetTrigger(bool InbTrigger);

	/** * 蓝图设置触发 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CommonSelect|Function")
	void BPSetTrigger(bool InbTrigger);

	/** * 设置插槽角度 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void SetSlotAngle(float InAngle);

	/** * 蓝图设置插槽角度 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CommonSelect|Function")
	void BPSetSlotAngle(float InAngle);

	/** * 设置扇形角度 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void SetSectorAngle(float InSectorAngle = 0.25f);

	/** * 设置扇形角度角度 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void SetSectorAngleProgress(float InSectorAngleProgress = 0.25f);

	/** * 更新颜色 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void UpdateColorAndOpacity();

	/** * 设置选择轮盘数据 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void SetSelectWheelDataStructs(const FSelectWheelDataStruct& InSelectWheelDataStructs, int InSectorIndex);
	


	/** * */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void SetSoftResource(const TSoftObjectPtr<UObject>& InSoftResource);

	/** * */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CommonSelect|Function")
	FText BPGetText();

	/** * */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void SetText(const FText& InText);

	/** * */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void SetTextColor(FLinearColor InColorAndOpacity);

	/** * */
	UFUNCTION(BlueprintCallable, Category = "CommonSelect|Function")
	virtual void SetImageColor(FLinearColor InColorAndOpacity);


};
