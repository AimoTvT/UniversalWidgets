// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Components/CanvasPanel.h"
#include "CommonActivatableWidget.h"
#include "CommonActivatableWidgetSwitcher.h"
#include "Widgets/CommonActivatableWidgetContainer.h"


#include "UniversalHUDWidget.generated.h"


class UUniversalHUDSubsystem;
class UUniversalHUDComponent;

/** * 
	* HUD用户控件,控制HUD整体
	* CommonActivatableWidgetSwitcher = 通用激活切换器, 0 = 主要画布控件, 1 = 列如拍摄模式(需要添加,并切换)
	* MainCanvasPanelWidget =主要画布控件, 0 = UI画布控件,1 = 玩家堆栈,2 = 系统堆栈
	* UICanvasPanelWidget = UI画布控件, 0 = 建议伤害数值类,1 = 建议路标类,2 = 建议玩家状态类,3 = 建议聊天类
	* PlayerCommonActivatableWidgetStack = 玩家堆栈,玩家的设置/互动类
	* SystemCommonActivatableWidgetStack = 系统堆栈,系统提示/选择类
	*/
UCLASS()
class UNIVERSALWIDGETS_API UUniversalHUDWidget : public UCommonUserWidget
{
	GENERATED_BODY()
public:

	/** * 万能HUD组件 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	TObjectPtr<UUniversalHUDComponent> UniversalHUDComponent;

	/** * 通用激活切换器 */
	UPROPERTY(BlueprintReadOnly, Category = "Aimo|Variable")
	TObjectPtr<UCommonActivatableWidgetSwitcher> CommonActivatableWidgetSwitcher;

	/** * 主要画布控件 */
	UPROPERTY(BlueprintReadOnly, Category = "Aimo|Variable")
	TObjectPtr<UCanvasPanel> MainCanvasPanelWidget;

	/** * UI画布控件 */
	UPROPERTY(BlueprintReadOnly, Category = "Aimo|Variable")
	TObjectPtr<UCanvasPanel> UICanvasPanelWidget;

	/** * 玩家堆栈 */
	UPROPERTY(BlueprintReadOnly, Category = "Aimo|Variable")
	TObjectPtr<UCommonActivatableWidgetStack> PlayerCommonActivatableWidgetStack;


	UPROPERTY(BlueprintReadOnly, Category = "Aimo|Variable")
	TObjectPtr<UCommonActivatableWidget> PlayerCommonActivatableWidget;

	FDelegateHandle PlayerDelegateHandle;

	/** * 系统堆栈 */
	UPROPERTY(BlueprintReadOnly, Category = "Aimo|Variable")
	TObjectPtr<UCommonActivatableWidgetStack> SystemCommonActivatableWidgetStack;


	UPROPERTY(BlueprintReadOnly, Category = "Aimo|Variable")
	TObjectPtr<UCommonActivatableWidget> SystemCommonActivatableWidget;

	FDelegateHandle SystemDelegateHandle;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

public:

	virtual void PlayerOnActivatable(UCommonActivatableWidget* ActivatableCommonActivatableWidget);

	virtual void SystemOnActivatable(UCommonActivatableWidget* ActivatableCommonActivatableWidget);


	/** *  */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	virtual void UpdateInputMode();

	void SetPlayerCommonActivatableWidget(UCommonActivatableWidget* InPlayerCommonActivatableWidget);
	void SetSystemCommonActivatableWidget(UCommonActivatableWidget* InSystemCommonActivatableWidget);

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	void SetUniversalHUDComponent(UUniversalHUDComponent* InUniversalHUDComponent);

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	bool AddWidgetStackInternal(UCommonActivatableWidget* ActivatableWidget, bool bSystem = false);

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	UCommonActivatableWidget* AddClassWidgetStackInternal(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass, bool bSystem = false);



	/** * UICanvasPanelWidget = UI画布控件, 0 = 建议伤害数值类,1 = 建议路标类,2 = 建议玩家状态类,3 = 建议聊天类
		* ZOrderClassIndex,2 = 2000, 上下浮动-1000~+1000
		* ZOrder 小浮动偏移
		*/
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	UCanvasPanelSlot* AddWidgetCanvasPanelInternal(UWidget* InWidget, uint8 ZOrderClassIndex = 2, int ZOrder = 0);
	UCanvasPanelSlot* NativeAddWidgetCanvasPanelInternal(UWidget* InWidget, uint8 ZOrderClassIndex = 2, int ZOrder = 0, FAnchors InAnchors = FAnchors(0.0f, 1.0f), FVector2D InPosition = FVector2D(0.0f, 0.0f), FVector2D InSize = FVector2D(0.0f, 0.0f));

	/** * UICanvasPanelWidget = UI画布控件, 0 = 建议伤害数值类,1 = 建议路标类,2 = 建议玩家状态类,3 = 建议聊天类
		* ZOrderClassIndex,2 = 2000, 上下浮动-1000~+1000
		* ZOrder 小浮动偏移
		*/
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	UWidget* AddClassWidgetCanvasPanelInternal(TSubclassOf<UWidget> WidgetClass, uint8 ZOrderClassIndex = 2, int ZOrder = 0);
	UWidget* NativeAddClassWidgetCanvasPanelInternal(TSubclassOf<UWidget> WidgetClass, uint8 ZOrderClassIndex = 2, int ZOrder = 0, FAnchors InAnchors = FAnchors(0.0f, 1.0f), FVector2D InPosition = FVector2D(0.0f, 0.0f), FVector2D InSize = FVector2D(0.0f, 0.0f));

};
