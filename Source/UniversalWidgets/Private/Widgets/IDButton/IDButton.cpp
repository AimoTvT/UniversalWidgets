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


#include "Widgets/IDButton/IDButton.h"


void UIDButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt(); 
	if (IsDesignTime() == false)
	{
		OnClicked.AddDynamic(this, &UIDButton::OnClickedID_Event);
		OnHovered.AddDynamic(this, &UIDButton::OnHoveredID_Event);
	}
	return;
}
void UIDButton::OnClickedID_Event()
{
	OnClickedID.Broadcast(ID);
}

void UIDButton::OnHoveredID_Event()
{
	OnHoveredID.Broadcast(ID);
}


