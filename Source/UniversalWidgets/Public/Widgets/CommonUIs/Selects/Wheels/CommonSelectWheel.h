// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CommonUIs/Selects/CommonSelectBase.h"
#include "Components/SizeBox.h"
#include "Components/CanvasPanel.h"
#include "CommonLazyImage.h"
#include "Config/UniversalWidgetsStruct.h"

#include "CommonSelectWheel.generated.h"

class UCommonSelectWheelSector;

/**
 * 
 */
UCLASS()
class UNIVERSALWIDGETS_API UCommonSelectWheel : public UCommonSelectBase
{
	GENERATED_BODY()
public:
	UCommonSelectWheel();

	/** * 尺寸框控件 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonSelectWheel")
	TObjectPtr<USizeBox> SizeBoxWidget;

	/** * 控件 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonSelectWheel")
	TObjectPtr<UCanvasPanel> CanvasPanelWidget;

	/** * 尺寸框控件 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonSelectWheel")
	TObjectPtr<USizeBox> WidgetSlotSizeBoxWidget;

	/** * 通用图像 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "CommonSelectWheel")
	TObjectPtr<UCommonLazyImage> CommonLazyImageWidget;



	/** * 最大扇形数量,尽量不要小于2或大于8,建议4或8 */
	UPROPERTY(BlueprintReadOnly, Category = "CommonSelectWheel")
	int MaxSectorNum = 8;

	/** * 扇形数量 */
	UPROPERTY(BlueprintReadOnly, Category = "CommonSelectWheel")
	int SectorNum = 0;

	/** * 页面索引 */
	UPROPERTY(BlueprintReadOnly, Category = "CommonSelectWheel")
	int PageIndex = 0;

	/** * 中心距离倍数 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "CommonSelectWheel")
	float CenterDistanceMultiple = 0.3f;

	/** * 选择索引 */
	UPROPERTY(BlueprintReadOnly, Category = "CommonSelectWheel")
	int SelectIndex = -1;

	/** * 通用输入模式 */
	UPROPERTY(BlueprintReadOnly, Category = "CommonSelectWheel")
	ECommonInputType CommonInputType = ECommonInputType::MouseAndKeyboard;

	/** * 允许选择空 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CommonSelectWheel")
	bool bAllowSelectNull = false;

	/** * 输入键X */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CommonSelectWheel")
	FKey InputKeyX = TEXT("Gamepad_RightX");

	/** * 输入键Y */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CommonSelectWheel")
	FKey InputKeyY = TEXT("Gamepad_RightY");

	/** * 盒子选择索引 */
	TMap<FSelectWheelDataStruct*, int> BoxSelectWheelDataStructs;


	/** * 选择扇形数据组 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CommonSelectWheel")
	TArray<FSelectWheelDataStruct> DefaultSelectWheelDataStructs;

	/** * 选择扇形数据组指针 */
	UPROPERTY(BlueprintReadWrite, Category = "CommonSelectWheel")
	TArray<FSelectWheelDataStruct> SelectWheelDataStructs;
	
	/** * 选择控件 */
	UPROPERTY(BlueprintReadWrite, Category = "CommonSelectWheel")
	TArray<TObjectPtr<UCommonSelectWheelSector>> CommonSelectWheelSectorWidgets;

	/** *  默认选择扇形数据 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CommonSelectWheel")
	FSelectWheelDataStruct DefaultSelectWheelDataStruct = FSelectWheelDataStruct(0);

	/** *  取消选择扇形数据 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CommonSelectWheel")
	FSelectWheelDataStruct CanceltSelectWheelDataStruct = FSelectWheelDataStruct(0);

	/** *  上次选择扇形数据 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CommonSelectWheel")
	FSelectWheelDataStruct LastSelectWheelDataStruct = FSelectWheelDataStruct(TEXT("LastSelect"), FText::FromString(TEXT("LastSelect")), 255);

	/** *  上一页选择扇形数据 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CommonSelectWheel")
	FSelectWheelDataStruct PageUpSelectWheelDataStruct = FSelectWheelDataStruct(TEXT("PageUp"), FText::FromString(TEXT("PageDown")), 255);

	/** *  下一页选择扇形数据 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CommonSelectWheel")
	FSelectWheelDataStruct PageDownSelectWheelDataStruct = FSelectWheelDataStruct(TEXT("PageDown"), FText::FromString(TEXT("PageDown")), 0);


	/** * 更新时间句柄 */
	UPROPERTY(BlueprintReadWrite, Category = "CommonSelectWheel")
	FTimerHandle UpdateTimerHandle;


	/**
	 * 取消的按下声音
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound, meta = (DisplayName = "Pressed Sound Override"))
	FSlateSound CanceltPressedSlateSoundOverride;

	/**
	 * 取消的悬浮的声音
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound, meta = (DisplayName = "Hovered Sound Override"))
	FSlateSound CanceltHoveredSlateSoundOverride;


	/** * *  */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectData, UCommonSelectWheel*, InCommonSelectWheel, const FSelectWheelDataStruct&, InSelectWheelDataStruct);

	/** * *  */
	UPROPERTY(BlueprintAssignable, Category = "CommonSelectWheel|On")
	FOnSelectData OnSelectData;


protected:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	virtual FReply NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;

	virtual FReply NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;


	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
public:

	virtual void SetVisibility(ESlateVisibility InVisibility) override;



	/** * 获取选择轮盘数据组 */
	UFUNCTION(BlueprintPure, Category = "SelectWheelDataStruct")
	static const TArray<FSelectWheelDataStruct>& GetSelectWheelDataArrayStruct(const FSelectWheelDataStruct& SelectWheelDataStructRef)
	{
		return SelectWheelDataStructRef.SelectWheelDataStructs;
	}

	/** * 设置选择轮盘数据组 */
	UFUNCTION(BlueprintCallable, Category = "SelectWheelDataStruct")
	static void SetSelectWheelDataArrayStruct(UPARAM(ref) FSelectWheelDataStruct& SelectWheelDataStructRef, const TArray<FSelectWheelDataStruct>& InSelectWheelDataStructs)
	{
		SelectWheelDataStructRef.SelectWheelDataStructs = InSelectWheelDataStructs;
	}

	/** * 寻找选择轮盘数据 */
	UFUNCTION(BlueprintCallable, Category = "SelectWheelDataStruct")
	static bool FindSelectWheelDataStruct(const TArray<FSelectWheelDataStruct>& InSelectWheelDataStructs, FSelectWheelDataStruct& SelectWheelDataStructRef, FName FindID)
	{
		return FSelectWheelDataStruct::FindRef(InSelectWheelDataStructs, SelectWheelDataStructRef, FindID);
	}

	/** * 更新位置事件 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelectWheel|Function")
	virtual void UpdatePosition_Event();

	/** * 通用输入标志 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelectWheel|Function")
	virtual void CommonInputType_Event(ECommonInputType InCommonInputType);

	/** * 设置选择位置 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelectWheel|Function")
	virtual int SetSelectPosition(FVector2D InPosition);
	/** * 设置选择轴 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelectWheel|Function")
	virtual int SetSelectAxis(FVector2D InAxis);

	/** * 设置选择轴索引 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelectWheel|Function")
	virtual int GetSelectAxisIndex(FVector2D InPosition);

	/** * 设置选择索引 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelectWheel|Function")
	virtual int SetSelectIndex(int InSelectIndex);

	/** * 蓝图设置选择索引 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ItemActor|Function")
	void BPSetSelectIndex(int OldSelectIndex, UCommonSelectWheelSector* OldCommonSelectWheelSector, int NewSelectIndex, UCommonSelectWheelSector* NewCommonSelectWheelSector);


	/** * 触控选择索引 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelectWheel|Function")
	virtual bool TriggerSelectIndex(int InSelectIndex);

	/** * 设置默认选择轮盘数据 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelectWheel|Function")
	virtual void SetDefaultSelectWheelDataStructsData(const TArray<FSelectWheelDataStruct>& InSelectWheelDataStructs, int InMaxSectorNum = 8);

	/** * 设置选择轮盘数据 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelectWheel|Function")
	virtual void SetSelectWheelDataStructsData(const TArray<FSelectWheelDataStruct>& InSelectWheelDataStructs, int InMaxSectorNum = 8, int PlayIndex = 0);

	/** * 设置页索引 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelectWheel|Function")
	virtual void SetPageIndex(int InPageIndex = 0, int InMaxSectorNum = 8);

	/** * 生成索引轮盘扇型控件 */
	UFUNCTION(BlueprintCallable, Category = "CommonSelectWheel|Function")
	virtual UCommonSelectWheelSector* SpawnSelectWheelSectorWidget(const FSelectWheelDataStruct& InSelectWheelDataStruct, float InSectorAngle);
	
}; 
