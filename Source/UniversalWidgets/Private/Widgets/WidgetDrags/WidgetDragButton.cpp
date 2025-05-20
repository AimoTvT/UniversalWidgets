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


#include "Widgets/WidgetDrags/WidgetDragButton.h" /** * 拖拽按钮控件头文件 */
#include "Blueprint/WidgetLayoutLibrary.h" /** * 控件函数头文件 */
#include "Components/CanvasPanelSlot.h" /** * 画布头文件 */



bool UWidgetDragButton::OnDragWidget(UWidget* Widget, bool bDrag)
{
	if (bDrag) /** * 是否拖拽 */
	{
		if (GetWorld() && Widget) /** * 判断传入的控件是否存在 */
		{
			DragWidget = Widget; /** * 储存控件值 */
			TimerDragPosition();
			GetWorld()->GetTimerManager().SetTimer(DragTimerHandle, this, &UWidgetDragButton::TimerDragPosition, 0.01f, true); /** * 初始化设置定时器 */
			return true;
		}
		else
		{
			if (GetWorld() && DragTimerHandle.IsValid())
			{
				GetWorld()->GetTimerManager().ClearTimer(DragTimerHandle); /** * 清除定时器 */
			}
			return false;
		}
	}
	else
	{
		Widget = nullptr; /** * 设置控件值 */
		if (DragTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(DragTimerHandle); /** * 清除定时器 */
		}
		return true;
	}
}

void UWidgetDragButton::TimerDragPosition()
{
	if (GetWorld() && DragWidget) /** * 世界和拖拽控件是否存在 */
	{
		FVector2D TDragPosition;
		TDragPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()); /** * 拖拽位置 = 获取鼠标的位置 */
		TDragPosition = TDragPosition * UWidgetLayoutLibrary::GetViewportScale(this); /** * 拖拽X位置*视口倍数 */
		UUserWidget* UserWidget = Cast<UUserWidget>(DragWidget); /** * 转换用户控件 */
		if (UserWidget)
		{
			DragPosition = TDragPosition;
			UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(DragWidget); /** * 转换为控件 */
			if (CanvasPanelSlot)
			{
				CanvasPanelSlot->SetPosition(TDragPosition); /** * 设置控件在位置 */
			}
			else
			{
				UserWidget->SetPositionInViewport(TDragPosition); /** * 设置用户控件的位置 */
			}
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(DragTimerHandle); /** * 清除定时器 */
	}
}