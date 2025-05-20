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
#include "Components/HorizontalBox.h"
#include "Widgets/CommonUIs/Buttons/UWCommonButtonIDText.h"

#include "SelectHorizontalBox.generated.h"

/** *
 * 
 */
UCLASS()
class UNIVERSALWIDGETS_API USelectHorizontalBox : public UHorizontalBox
{
	GENERATED_BODY()

public:
	USelectHorizontalBox();

	/** * 识别的UID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Variable")
	FString ID;

	/** * ID组 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Variable") 
	TArray<FString> IDs;

	/** * 文字组 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Variable")
	TArray<FText> Texts;

	/** * 选择索引 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectHorizontalBox|Variable")
	int SelectIndex;

	/** *  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "SelectScrollBox|Appearance")
	TSubclassOf<UUWCommonButtonIDText> UUWCommonButtonIDTextClass;

	/** * 样式填充 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectScrollBox|Appearance")
	FMargin StylePadding;

	/** * 默认样式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "SelectScrollBox|Appearance")
	TSubclassOf<UCommonButtonStyle> DefaultButtonStyle;

	/** * 选择样式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "SelectScrollBox|Appearance")
	TSubclassOf<UCommonButtonStyle> SelectButtonStyle;

	/** * 默认样式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "SelectScrollBox|Appearance")
	TSubclassOf<UCommonTextStyle> DefaultTextStyle;

	/** * 选择样式 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "SelectScrollBox|Appearance")
	TSubclassOf<UCommonTextStyle> SelectTextStyle;

	/** * 按钮控件组 */
	UPROPERTY(BlueprintReadWrite, Category = "SelectHorizontalBox|Variable")
	TArray<TObjectPtr<UUWCommonButtonIDText>> UWCommonButtonIDTextWidgets;

	/** * * 委托宏2个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnClickedIDEvent, const FString&, OnID, const FString&, SelectID);

	/** * * 委托宏2个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHoverIDEvent, const FString&, OnID, const FString&, SelectID);

	/** * * 点击选着 */
	UPROPERTY(BlueprintAssignable, Category = "SelectHorizontalBox|On")
	FOnClickedIDEvent OnClickedSelect;

	/** * * 悬浮选择 */
	UPROPERTY(BlueprintAssignable, Category = "SelectHorizontalBox|On")
	FOnHoverIDEvent OnHoverSelect;

protected:
	/** * Function called after the underlying SWidget is constructed. */
	virtual void OnWidgetRebuilt() override;

	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void NativeConstruct();

public:

	/* * 按下的委托 */
	UFUNCTION(BlueprintCallable, Category = "SelectScrollBox|Function")
	void OnClickedID_Event(UCommonButtonBase* InCommonButtonBase);

	/* * 触摸的委托 */
	UFUNCTION(BlueprintCallable, Category = "SelectScrollBox|Function")
	void OnHoveredID_Event(UCommonButtonBase* InCommonButtonBase);

	/* * 设置索引显示,是否委托 */
	UFUNCTION(BlueprintCallable, Category = "SelectHorizontalBox|Function")
	void SetSelectIndex(int Index, bool bDelegate = false);

	/* * 初始化按钮 */
	UFUNCTION(BlueprintCallable, Category = "SelectHorizontalBox|Function")
	void InitButton();

	/* * 初始化数据 */
	UFUNCTION(BlueprintCallable, Category = "SelectHorizontalBox|Function")
	void InitData(TArray<FString> InIDs, TArray<FText> InTexts);

	/* * 设置选择ID */
	UFUNCTION(BlueprintCallable, Category = "SelectHorizontalBox|Function")
	void SetSelectID(const FString& OnID, bool bDelegate = false);

};
