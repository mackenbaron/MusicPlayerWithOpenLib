
#ifndef ORZ_COMPLEX_CONTROL_H_INCLUDE
#define ORZ_COMPLEX_CONTROL_H_INCLUDE

#include "orz_control.h"
#include "orz_font.h"

namespace Orz
{
	// 控件 - 文本框--------------------------------------
	class ControlText: public BaseControl
	{
	public:
		// 构造函数
		ControlText();

		// 创建文本控件
		bool CreateControlText(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize, const char* Text, const Color &TextColor);

		// 修改属性
		Writer& GetWriter(void);

	private:
		void DoDraw(const Rect& DrawRect);
	};

	extern ControlText error_control_text;

	// 控件 - 按钮 and 文本------------------------------------
	class ControlButtonWithWriter: public ControlButton
	{
	public:
		ControlButtonWithWriter();

		// 创建控件
		bool CreateControlButtonWithWirter(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize, const char* Text, const Color &TextColor);

		// 修改属性
		Writer& GetWriter(void);
	};

	extern ControlButtonWithWriter error_control_button_with_writer;


	class ControlScrollBarWithColor: public BaseControl
	{
	public:
		ControlScrollBarWithColor();

		// 手动创建滚动条控件
		bool CreateControlScrollBarWithColor(const char* Name, ControlDirect Direct, const Rect &ControlRect, const Color &BackgroundColorTrough, const Color &BackgroundColorBar);

		// 获取属性
		ControlButton& GetBar(void);
		ControlScrollBarWithColor& GetPercent(float &Percent);

		// 修改属性
		ControlScrollBarWithColor& ChangePercent(float Percent);
		ControlScrollBarWithColor& ChangePercentAccrodToMousePosition(void);
		ControlScrollBarWithColor& ChangeDirect(ControlDirect Direct);

	private:
		void DoDraw(const Rect& DrawRect);

		// 滚动条属性
		ControlDirect control_direct;
		float control_percent;
	};

	extern ControlScrollBarWithColor error_control_scroll_bar_with_color;

	// 控件 - 列表---------------------------------------
	class ControlList: public ControlCanvas
	{
	public:
		ControlList();

		// 从文件中创建控件
		bool LoadControlList(const char* PathName, int X, int Y);

		// 创建控件
		bool CreateControlList(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, int EntryHeight, const char *FontName, int FontSize);

		// 获得属性
		ControlList& GetPercent(float &Percent);
		ControlList& GetContentSize(int &Size);

		// 修改属性
		ControlList& ChangePercent(float Percent);

		// 列表操作
		ControlList& PushBackControlText(const char *ControlName, const char* Text);
		ControlList& Insert(int Position, const char *ControlName, const char* Text); // 在 Position-1 和 Position 之间插入元素

	private:
		void DoDraw(const Rect& DrawRect);
		void DoContact();
		// 列表属性
		BaseFont list_font;

		int entry_height;
		float control_percent;
	};

	extern ControlList error_control_list;
}


#endif