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
#include "Components/Button.h"
#include "IDButton.generated.h"

/** *
 * 带有ID的按钮,重写了委托
 */
UCLASS()
class UNIVERSALWIDGETS_API UIDButton : public UButton
{
	GENERATED_BODY()
	
public:

	/** * 控件ID */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (ExposeOnSpawn), Category = "IDButton|Variable")
	FString ID;

	/** * * 委托宏1个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClickedIDEvent, const FString&, ID);

	/** * * 委托宏1个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonHoverIDEvent, const FString&, ID);

	/** * * 点击委托ID */
	UPROPERTY(BlueprintAssignable, Category = "IDButton|On")
	FOnButtonClickedIDEvent OnClickedID;

	/** * * 悬浮委托ID */
	UPROPERTY(BlueprintAssignable, Category = "IDButton|On")
	FOnButtonHoverIDEvent OnHoveredID;

protected:
	/** * 构造底层widget后调用的函数. */
	virtual void OnWidgetRebuilt() override;

	/** * 按钮点击后的委托 */
	UFUNCTION(BlueprintCallable, Category = "IDButton|Function")
	virtual void OnClickedID_Event();

	/** * 按钮悬浮的委托 */
	UFUNCTION(BlueprintCallable, Category = "IDButton|Function")
	virtual void OnHoveredID_Event();

};
