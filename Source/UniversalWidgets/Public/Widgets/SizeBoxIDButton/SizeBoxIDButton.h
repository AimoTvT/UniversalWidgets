/**
 * Copyright: Aimo_皑墨
 * Open Source Date: Jun 27, 2023
 * BiLiBiLi (哔哩哔哩) address: https://space.bilibili.com/146962867
 * Open source address(Git): https://github.com/AimoTvT/UniversalWidgets
 * We welcome the contributions of powerful movers and movers to join this plugin
 * Build powerful plugins together!!
 *
 * 版权所有权: Aimo_皑墨
 * 开源时间: 2023年6月27日
 * BiLiBiLi(哔哩哔哩)地址: https://space.bilibili.com/146962867
 * 开源地址(Git): https://github.com/AimoTvT/UniversalWidgets
 * 欢迎有实力的大佬/萌新加入本插件的贡献
 * 一起打造强大的插件!!!
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/SizeBox.h"
#include "Components/Button.h"

#include "SizeBoxIDButton.generated.h"

/** *
 * 可以自定义大小的ID按钮
 */
UCLASS()
class UNIVERSALWIDGETS_API USizeBoxIDButton : public USizeBox
{
	GENERATED_BODY()

public:


	/** * 按钮控件 */
	UPROPERTY(BlueprintReadOnly, Category = "SizeBoxIDButton|Variable")
	TObjectPtr<UButton> ButtonWidget;

	/** * 识别的ID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn), Category = "SelectHorizontalBox|Variable")
	FString ID;

	/** * 按钮默认样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Appearance")
	FButtonStyle ButtonStyle;


	/** * 委托宏2个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickedIDEvent, const FString&, OnID);

	/** * 委托宏2个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHoverIDEvent, const FString&, OnID);

	/** * 触发的委托变量 */
	UPROPERTY(BlueprintAssignable, Category = "SizeBoxIDButton|On")
	FOnClickedIDEvent OnClickedID;

	/** * 触发的委托变量 */
	UPROPERTY(BlueprintAssignable, Category = "SizeBoxIDButton|On")
	FOnHoverIDEvent OnHoverID;

protected:
	/** * Function called after the underlying SWidget is constructed. */
	virtual void OnWidgetRebuilt() override;

	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void NativeConstruct();

public:


	/** * 点击_事件 */
	UFUNCTION(BlueprintCallable, Category = "SizeBoxIDButton|Function")
	void OnClickedID_Event();

	/** * 悬浮_事件 */
	UFUNCTION(BlueprintCallable, Category = "SizeBoxIDButton|Function")
	void OnHoveredID_Event();

	/** * 设置ID */
	UFUNCTION(BlueprintCallable, Category = "SizeBoxIDButton|Function")
	void SetID(const FString& InID);

	/** * 设置按钮样式 */
	UFUNCTION(BlueprintCallable, Category = "SizeBoxIDButton|Function")
	void SetButtonStyle(const FButtonStyle& InButtonStyle);

	/** * 绑定按键委托 */
	UFUNCTION(BlueprintCallable, Category = "SizeBoxIDButton|Function")
	void BindScriptDelegate(UObject* InObject, const FName& InFunctionName, bool bClicked = true);

};
