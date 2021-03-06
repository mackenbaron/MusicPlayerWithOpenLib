#ifndef ORZ_CONTROL_H_INCLUDED
#define ORZ_CONTROL_H_INCLUDED

#include "orz_base_control.h"
#include "orz_sprite.h"
#include "orz_writer.h"
#include <string>

#define CONTROL_BAR_OCCUPY_CONTROL_LIST_PERCENT (0.08) // 0.0 ~ 1.0

namespace Orz
{
	// 控件 - 虚拟 - 没有绘制任何东西-------------------------------
	class ControlVirtual: public BaseControl
	{
	public:
		ControlVirtual();

		bool CreateControlVirtual(const char *ControlName, const Rect &ControlRect);

	private:
	};

	extern ControlVirtual error_control_virtual;

	// 控件 - 画布 - 背景不会因为鼠标的情况而改变------------------------------
	class ControlCanvas: public BaseControl
	{
	public:
		ControlCanvas();

		// 创建文本控件
		bool CreateControlCanvas(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor);

	private:
		// 绘制
		void DoDraw(const Rect& DrawRect);
	};

	extern ControlCanvas error_control_canvas;

	// 控件 - 按钮 - 背景因鼠标的清空而改变----------------------------------
	class ControlButton: public BaseControl
	{
	public:
		ControlButton();

		// 创建控件
		bool CreateControlButton(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor);

	private:
		void DoDraw(const Rect& DrawRect);
	};

	extern ControlButton error_control_button;


	// 控件 - 滚动条-----------------------------------------------
	class ControlScrollBar: public BaseControl
	{
	public:
		ControlScrollBar();

		// 手动创建滚动条控件
		bool CreateControlScrollBar(const char* Name, ControlDirect Direct, const Rect &BarRect, const Rect &TroughRect);

		// 获取属性
		ControlButton& GetBar(void);
		ControlScrollBar& GetPercent(float &Percent);

		// 修改属性
		ControlScrollBar& ChangePercent(float Percent);
		ControlScrollBar& ChangePercentAccrodToMousePosition(void);
		ControlScrollBar& ChangeDirect(ControlDirect Direct);

	private:
		void DoDraw(const Rect& DrawRect);

		// 滚动条属性
		ControlDirect control_direct;
		float control_percent;
	};

}
#endif