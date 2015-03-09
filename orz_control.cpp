
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

	void ControlCanvas::DoDraw()
	{
		SDL_Rect real_draw_rect = { x, y, width, height };
		if(element_alpha == 255)
		{
			device.display.DrawFillRect(GetBackgroundColor(), real_draw_rect);
		}
		else
		{
			device.display.DrawAlphaSolidColor(GetBackgroundColor(), element_alpha, real_draw_rect);
		}


#ifdef CodeDebug
		Rect out_rect = {x -1, y -1, width+1, height +1};
		device.display.DrawOutlineRect(RedColor, out_rect);
#endif
		
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

	void ControlButton::DoDraw()
	{
		Rect real_draw_rect = { x, y, width, height };
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
			device.display.DrawFillRect(real_draw_color, real_draw_rect);
		}
		else
		{
			device.display.DrawAlphaSolidColor(real_draw_color, element_alpha, real_draw_rect);
		}

#ifdef CodeDebug
		Rect out_rect = {x -1, y -1, width+1, height +1};
		device.display.DrawOutlineRect(RedColor, out_rect);
#endif
	}

	// 滚动条控件-----------------------------------------------------------------
	ControlScrollBar::ControlScrollBar():
	BaseControl(ELEMENT_TYPE_UI_CONTROL_SCROLL_BAR),
	control_direct(CONTROL_DIRECT_UP_DOWN),
	control_percent(0.0f)
	{
		ControlButton* new_control_button = new ControlButton;
		ChildrenPushBack(new_control_button);
	}

	bool ControlScrollBar::CreateControlScrollBar(const char* Name, ControlDirect Direct, const Rect &ControlRect, const Color &BackgroundColorTrough, const Color &BackgroundColorBar)
	{
		element_name = Name;
		
		control_direct = Direct;
		
		ChangePosition(ControlRect.x, ControlRect.y);
		ChangeSize(ControlRect.w, ControlRect.h);
		ChangeBackgroundColor(BackgroundColorTrough);

		GetBar().ChangeBackgroundColor(BackgroundColorBar).ChangePosition(0,0).ChangeSize(width, height);

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
		int mx, my;
		GetMousePosition(mx, my);
		if (control_direct == CONTROL_DIRECT_UP_DOWN)
		{
			if (my < 0)
			{
				control_percent = 0.0f;
			}
			else if (my > height)
			{
				control_percent = 1.0f;
			}
			else
			{
				control_percent = (float)my/height;
			}

			GetBar().ChangePosition( 0, height * control_percent);
		} 
		else
		{
			if (mx < 0)
			{
				control_percent = 0.0f;
			}
			else if (mx > width)
			{
				control_percent = 1.0f;
			}
			else
			{
				control_percent = (float)mx/width;
			}

			GetBar().ChangePosition( width*control_percent, 0);
		}

		return *this;
	}

	ControlScrollBar& ControlScrollBar::ChangeDirect(ControlDirect Direct)
	{
		control_direct = Direct;
		return *this;
	}

	float ControlScrollBar::GetPercent(void)
	{
		return control_percent;
	}

	ControlButton& ControlScrollBar::GetBar(void)
	{
		if (ChildrenEmpty())
			return error_control_button;

		if (Children(0).element_type == ELEMENT_TYPE_UI_CONTROL_BUTTON)
			return ((ControlButton&)Children(0));
		else
			return error_control_button;
	}

	void ControlScrollBar::DoDraw(void)
	{
		SDL_Rect real_draw_rect = { x, y, width, height };
		if(element_alpha == 255)
		{
			device.display.DrawFillRect(GetBackgroundColor(), real_draw_rect);
		}
		else
		{
			device.display.DrawAlphaSolidColor(GetBackgroundColor(), element_alpha, real_draw_rect);
		}

#ifdef CodeDebug
		Rect out_rect = {x -1, y -1, width+1, height +1};
		device.display.DrawOutlineRect(RedColor, out_rect);
#endif
	}

}