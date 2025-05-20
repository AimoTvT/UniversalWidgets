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
#include "Components/WidgetSwitcher.h"
#include "EnhancedWidgetSwitcher.generated.h"

/**
 * 
 */
UCLASS()
class UNIVERSALWIDGETS_API UEnhancedWidgetSwitcher : public UWidgetSwitcher
{
	GENERATED_BODY()

public:

	/** * 持有设备空间索引 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnhancedWidgetSwitcher|Variable")
	uint8 RemoveModeIndex = 0;

	/** * * 委托宏1个输入 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoveChild,const UPanelSlot*, InSlot);

	/** * * 通讯委托,多播,通讯 */
	UPROPERTY(BlueprintAssignable, Category = "EnhancedWidgetSwitcher|On")
	FOnRemoveChild OnRemoveChild;

public:
	virtual void OnSlotRemoved(UPanelSlot* InSlot) override;
	
};
