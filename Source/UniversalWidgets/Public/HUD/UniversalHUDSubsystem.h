// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HUD/UniversalHUDComponent.h"
#include "HUD/UniversalHUDWidget.h"

#include "UniversalHUDSubsystem.generated.h"

/** * HUD子系统,控制HUD整体
    *
	*/
UCLASS()
class UNIVERSALWIDGETS_API UUniversalHUDSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	static UUniversalHUDSubsystem* Get();

	/** *  */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	TMap<TObjectPtr<APlayerController>, TObjectPtr<UUniversalHUDComponent>> UniversalHUDComponents;

	/** *  */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	TSubclassOf<UUniversalHUDWidget> DefaultUniversalHUDWidgetClass = UUniversalHUDWidget::StaticClass();

	/** *  */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	TArray<TObjectPtr<UWidget>> ControlWidgets;

protected:


public:

	// 必须覆盖的生命周期方法
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** *  */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	UUniversalHUDComponent* AddPlayerController(APlayerController* InPlayerController, TSubclassOf<UUniversalHUDWidget> InUniversalHUDWidgetClass = nullptr);

	/** * 添加堆栈UI */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	bool AddWidgetStackInternal(APlayerController* TargetPlayerController, UCommonActivatableWidget* ActivatableWidget, bool bSystem = false);

	/** * 添加堆栈UI */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	UCommonActivatableWidget* AddClassWidgetStackInternal(APlayerController* TargetPlayerController, TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass, bool bSystem = false);

	/** *
		* ZOrderClassIndex 0 = 建议伤害数值类,1 = 建议路标类,2 = 建议玩家状态类,3 = 建议聊天类,2 = 2000, 上下浮动-1000~+1000
		* ZOrder 小浮动偏移
		*/
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	UCanvasPanelSlot* AddWidgetCanvasPanelInternal(APlayerController* TargetPlayerController, UWidget* InWidget, uint8 ZOrderClassIndex = 2, int ZOrder = 0);

	/** *
		* ZOrderClassIndex 0 = 建议伤害数值类,1 = 建议路标类,2 = 建议玩家状态类,3 = 建议聊天类,2 = 2000, 上下浮动-1000~+1000
		* ZOrder 小浮动偏移
		*/
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	UWidget* AddClassWidgetCanvasPanelInternal(APlayerController* TargetPlayerController, TSubclassOf<UWidget> WidgetClass, uint8 ZOrderClassIndex = 2, int ZOrder = 0);

	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	void AddControlWidget(APlayerController* InPlayerController, UWidget* ControlWidget, bool bGameAndUI = false, EMouseLockMode InMouseLockMode = EMouseLockMode::DoNotLock, const bool bFlushInput = false);


	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	void RemoveControlWidget(APlayerController* InPlayerController, UWidget* ControlWidget);

};
