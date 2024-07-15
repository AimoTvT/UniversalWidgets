/**
 * Copyright: Aimo_皑墨
 * Open Source Date: Jun 27, 2023
 * BiLiBiLi (哔哩哔哩) address: https://space.bilibili.com/146962867
 * Open source address(Git): https://github.com/AimoTvT/WidgetExpansions
 * We welcome the contributions of powerful movers and movers to join this plugin
 * Build powerful plugins together!!
 *
 * 版权所有权: Aimo_皑墨
 * 开源时间: 2023年6月27日
 * BiLiBiLi(哔哩哔哩)地址: https://space.bilibili.com/146962867
 * 开源地址(Git): https://github.com/AimoTvT/WidgetExpansions
 * 欢迎有实力的大佬/萌新加入本插件的贡献
 * 一起打造强大的插件!!!
 */
#pragma once

#include "CoreMinimal.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"

#include "SelectScrollBox.generated.h"

/** *
 * 
 */
UCLASS()
class WIDGETEXPANSIONS_API USelectScrollBox : public UScrollBox
{
	GENERATED_BODY()
	
public:

	/** * 识别的ID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Variable")
	FString ID;

	/** * 识别的UID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Variable")
	TArray<FString> IDs;

	/** * 识别的UID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Variable")
	TArray<FText> Texts;

	/** * 反向选着 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Variable")
	bool ReverseSelect = false;

	/** * 是否可以重复触发 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Variable")
	bool bRepeatedIndex = true;

	/** * 选择索引 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Variable")
	int SelectIndex = 0;

	/** * 按键大小,垂直设置高度,水平设置最小宽度 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Variable")
	float ButttonSize = 60;

	/** * 样式填充 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Appearance")
	FMargin StylePadding;

	/** * 默认样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Appearance")
	FButtonStyle DefaultStyle;

	/** * 选择样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Appearance")
	FButtonStyle SelectStyle;


	/** * 字体填充 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Appearance")
	FMargin FontInfoPadding;

	/** * 文字样式 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Appearance")
	FSlateFontInfo SlateFontInfo;

	/** * 默认文字颜色 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Appearance")
	FSlateColor DefaultFontInfoColor;

	/** * 选着文字颜色 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectScrollBox|Appearance")
	FSlateColor SelectFontInfoColor;

	/** * 尺寸框组 */
	UPROPERTY(BlueprintReadWrite, Category = "SelectScrollBox|Variable")
	TArray<TObjectPtr<USizeBox>> SizeBoxWidgets;


public:

	/** * * 委托宏2个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnIDClickedEvent, const FString&, OnID, const FString&, SelectID);

	/** * * 委托宏2个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnIDHoverEvent, const FString&, OnID, const FString&, SelectID);

	/** * * 触发的委托变量 */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnIDClickedEvent OnClickedSelect;

	/** * * 触发的委托变量 */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnIDHoverEvent OnHoverSelect;



protected:
	/** * Function called after the underlying SWidget is constructed. */
	virtual void OnWidgetRebuilt() override;

	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void NativeConstruct();

public:

	/* * 按下的委托 */
	UFUNCTION(BlueprintCallable, Category = "SelectScrollBox|Function")
	void OnClickedID_Event(const FString& OnID);

	/* * 触摸的委托 */
	UFUNCTION(BlueprintCallable, Category = "SelectScrollBox|Function")
	void OnHoveredID_Event(const FString& OnID);

	/* * 设置索引显示,是否委托 */
	UFUNCTION(BlueprintCallable, Category = "SelectScrollBox|Function")
	void SetSelectIndex(int Index, bool bDelegate = false);

	/* * 初始化按钮 */
	UFUNCTION(BlueprintCallable, Category = "SelectScrollBox|Function")
	void InitButton();

	/* * 初始化数据 */
	UFUNCTION(BlueprintCallable, Category = "SelectScrollBox|Function")
	void InitData(TArray<FString> InIDs, TArray<FText> InTexts);

	/* * 设置选择ID */
	UFUNCTION(BlueprintCallable, Category = "SelectScrollBox|Function")
	void SetSelectID(const FString& OnID, bool bDelegate = false);

};
