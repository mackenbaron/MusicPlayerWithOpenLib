
#include "orz_control.h"
#include "orz_base_time.h"
#include "orz_log.h"
#include "orz_base_public_resource.h"
#include <string>

namespace Orz
{
	// 错误处理
	ControlVirtual error_control_virtual;
	ControlCanvas error_control_canvas;
	ControlButton error_control_button;

	// 控件 - 虚拟 - 没有绘制任何东西----------------------------------------------------
	ControlVirtual::ControlVirtual():
	BaseControl(ELEMENT_TYPE_UI_CONTROL_VIRTUAL)
	{

	}

	bool ControlVirtual::CreateControlVirtual(const char *ControlName, const Rect &ControlRect)
	{
		element_name = ControlName;

		ChangePosition(ControlRect.x, ControlRect.y);
		ChangeSize(ControlRect.w, ControlRect.h);

		return true;
	}

	// 控件 - 画布 - 背景不会因为鼠标的情况而改变-----------------------------------
	ControlCanvas::ControlCanvas():
	BaseControl(ELEMENT_TYPE_UI_CONTROL_CANVAS)
	{

	}

	bool ControlCanvas::CreateControlCanvas(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor)
	{
		element_name = ControlName;
		ChangePosition(ControlRect.x, ControlRect.y);
		ChangeSize(ControlRect.w, ControlRect.h);
		ChangeBackgroundColor(BackgroundColor);

		return true;
	}

	void ControlCanvas::DoDraw(const Rect& DrawRect)
	{
		if(element_alpha == 255)
		{
			device.display.DrawFillRect(GetBackgroundColor(), DrawRect);
		}
		else
		{
			device.display.DrawAlphaFillRect(GetBackgroundColor(), element_alpha, DrawRect);
		}
	}

	// 控件 - 按钮 - 背景因鼠标的清空而改变----------------------------------
	ControlButton::ControlButton():
	BaseControl(ELEMENT_TYPE_UI_CONTROL_BUTTON)
	{

	}

	bool ControlButton::CreateControlButton(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor)
	{
		element_name = ControlName;

		ChangePosition(ControlRect.x, ControlRect.y);
		ChangeSize(ControlRect.w, ControlRect.h);
		ChangeBackgroundColor(BackgroundColor);

		return true;
	}

	void ControlButton::DoDraw(const Rect& DrawRect)
	{
		Color real_draw_color;

		switch(GetUiState())
		{
		case UI_STATE_MOUSE_OUT:
			real_draw_color = GetBackgroundColor();
			break;

		case UI_STATE_MOUSE_OVER:
			real_draw_color = GetBackgroundColor();
			real_draw_color.r = GetBackgroundColor().r * 0.8;
			real_draw_color.g = GetBackgroundColor().g * 0.8;
			real_draw_color.b = GetBackgroundColor().b * 0.8;
			break;

		case UI_STATE_MOUSE_DOWN:
			real_draw_color.r = GetBackgroundColor().r * 0.5;
			real_draw_color.g = GetBackgroundColor().g * 0.5;
			real_draw_color.b = GetBackgroundColor().b * 0.5;
			break;
		}

		if(element_alpha == 255)
		{
			device.display.DrawFillRect(real_draw_color, DrawRect);
		}
		else
		{
			device.display.DrawAlphaFillRect(real_draw_color, element_alpha, DrawRect);
		}
	}

	// 控件 - 滚动条----------------------------------------------------------
	ControlScrollBar::ControlScrollBar():
	BaseControl(ELEMENT_TYPE_UI_CONTROL_SCROLL_BAR),
		control_direct(CONTROL_DIRECT_UP_DOWN),
		control_percent(0.0f)
	{
		ControlVirtual* new_control_virtual = new ControlVirtual;
		ChildrenPushBack(new_control_virtual);
	}

	bool ControlScrollBar::CreateControlScrollBar(const char* Name, ControlDirect Direct, const Rect &BarRect, const Rect &TroughRect)
	{
		element_name = Name;

		control_direct = Direct;

		ChangePosition(TroughRect.x, TroughRect.y);
		ChangeSize(TroughRect.w, TroughRect.h);

		GetBar().ChangePosition(BarRect.x, BarRect.y)
			.ChangeSize(BarRect.w, BarRect.h);

		return true;
	}

	ControlScrollBar& ControlScrollBar::ChangePercent(float Percent)
	{
		if (Percent < .0f)
			control_percent = 0.0;
		else if (Percent > 1.0f)
			control_percent = 1.0;
		else
			control_percent = Percent; 

		return *this;
	}

	ControlScrollBar& ControlScrollBar::ChangePercentAccrodToMousePosition(void)
	{
		int mx, my, bar_width, bar_height;
		GetMousePosition(mx, my);
		GetBar().GetSize(bar_width, bar_height);
		if (control_direct == CONTROL_DIRECT_UP_DOWN)
		{
			if (my < bar_height/2)
			{
				control_percent = 0.0f;
			}
			else if (my > height - bar_height/2)
			{
				control_percent = 1.0f;
			}
			else
			{
				control_percent = (float)(my-bar_height/2)/(height-bar_height);
			}
		} 
		else
		{
			if (mx < bar_width/2)
			{
				control_percent = 0.0f;
			}
			else if (mx > width - bar_width/2)
			{
				control_percent = 1.0f;
			}
			else
			{
				control_percent = (float)(mx-bar_width/2)/(width-bar_width);
			}
		}

		return *this;
	}

	ControlScrollBar& ControlScrollBar::ChangeDirect(ControlDirect Direct)
	{
		control_direct = Direct;
		return *this;
	}

	ControlScrollBar& ControlScrollBar::GetPercent(float &Percent)
	{
		Percent = control_percent;
		return *this;
	}

	ControlButton& ControlScrollBar::GetBar(void)
	{
		if (ChildrenEmpty())
			return error_control_button;

		if (Children(0).element_type == ELEMENT_TYPE_UI_CONTROL_VIRTUAL)
			return ((ControlButton&)Children(0));
		else
			return error_control_button;
	}

	void ControlScrollBar::DoDraw(const Rect& DrawRect)
	{
		// 设置 Bar 的位置
		int bar_width, bar_height;
		GetBar().GetSize(bar_width, bar_height);
		if (control_direct == CONTROL_DIRECT_UP_DOWN)
		{
			GetBar().ChangePosition((width - bar_width)/2, (height - bar_height)*control_percent);
		}
		else
		{
			GetBar().ChangePosition((width - bar_width)*control_percent, (height-bar_height)/2);
		}
	}
}