
#ifndef ORZ_COMPLEX_CONTROL_H_INCLUDE
#define ORZ_COMPLEX_CONTROL_H_INCLUDE

#include "orz_control.h"
#include "orz_font.h"

namespace Orz
{
	// 控件 - 文本框--------------------------------------
	class ControlText: public ControlCanvas
	{
	public:
		// 构造函数
		ControlText();

		// 创建文本控件
		bool CreateControlText(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize, const char* Text, const Color &TextColor);

		// 修改属性
		Writer& GetWriter(void);
	};

	extern ControlText error_control_text;

	// 控件 - 按钮 and 文本------------------------------------
	class ControlButtonWithWriter: public ControlButton
	{
	public:
		ControlButtonWithWriter();

		// 创建控件
		bool CreateControlButtonWithWirter(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize, const char* Text, const Color &TextColor);

		// 从文件中创建控件
		bool LoadControlButtonWithText(const char* PathName, int X, int Y, const Color &BackgroundColor, const char *FontName, int FontSize, const char* Text, const Color &TextColor);

		// 修改属性
		Writer& GetWriter(void);
	};

	extern ControlButtonWithWriter error_control_button_with_writer;


	// 控件 - 滚动条-----------------------------------------------
	class ControlScrollBar: public BaseControl
	{
	public:
		ControlScrollBar();

		// 手动创建滚动条控件
		bool CreateControlScrollBar(const char* Name, ControlDirect Direct, const Rect &ControlRect, const Color &BackgroundColorTrough, const Color &BackgroundColorBar);

		// 获取属性
		ControlButton& GetBar(void);
		float GetPercent(void);

		// 修改属性
		ControlScrollBar& ChangePercent(float Percent);
		ControlScrollBar& ChangePercentAccrodToMousePosition(void);
		ControlScrollBar& ChangeDirect(ControlDirect Direct);

	private:
		void DoDraw(void);

		// 滚动条属性
		ControlDirect control_direct;
		float control_percent;
	};

	extern ControlScrollBar error_control_scroll_bar;

	// 控件 - 列表---------------------------------------
	class ControlList: public ControlCanvas
	{
	public:
		ControlList();

		// 从文件中创建控件
		bool LoadControlList(const char* PathName, int X, int Y);

		// 创建控件
		bool CreateControlList(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize);

		// 获得属性
		float GetPercent(void);

		// 修改属性
		ControlList& ChangePercent(float Percent);

		// 列表操作
		ControlList& PushBack(const char *ControlName, const char* Text);
		ControlList& Insert(int Position, const char *ControlName, const char* Text); // 在 Position-1 和 Position 之间插入元素

	private:

		// 列表属性
		BaseFont list_font;

		int entry_height;
		float control_percent;
	};

	extern ControlList error_control_list;
}


#endif