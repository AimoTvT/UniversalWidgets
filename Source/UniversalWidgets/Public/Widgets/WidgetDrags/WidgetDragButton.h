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


#include "WidgetDragButton.generated.h"


/** *
 *	拖拽按钮
 */
UCLASS(config = EditorPerProjectUserSettings, meta = (DisplayName = "WidgetDragButton")) /** * 设置在用户控件编辑器里显示的名字 */
class UNIVERSALWIDGETS_API UWidgetDragButton : public UButton
{
	GENERATED_BODY()

public:

	/** * 拖拽的控件 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	TObjectPtr<UWidget> DragWidget;

	/** * 拖拽的位置 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FVector2D DragPosition = FVector2D(0.0f);

	/** * 拖拽的位置偏移 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FVector2D DragPositionOffset = FVector2D(0.0f);

	/** * 拖拽的定时器 */
	UPROPERTY(BlueprintReadWrite, Category = "Aimo|Variable")
	FTimerHandle DragTimerHandle;

protected:
	

public:



	/** * 触发拖拽并传入控件 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	bool OnDragWidget(UWidget* Widget, bool bDrag);

	/** * 定时器调用的事件,修改控件的位置 */
	UFUNCTION(BlueprintCallable, Category = "Aimo|Function")
	void TimerDragPosition();

};
