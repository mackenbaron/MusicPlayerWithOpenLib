#ifndef ORZ_CONTROL_H_INCLUDED
#define ORZ_CONTROL_H_INCLUDED

#include "orz_base_control.h"
#include "orz_sprite.h"
#include <string>

#define CONTROL_BAR_OCCUPY_CONTROL_LIST_PERCENT (0.08) // 0.0 ~ 1.0

namespace Orz
{
	// 控件 - 文本框 - 背景为纯色
	class ControlText: public BaseControl
	{
	public:
		// 构造函数
		ControlText();
		
		// 创建文本控件
		bool CreateControlText(const char *ControlName, int X, int Y, int Width, int Height, const char *FontName, int FontSize, const char *Text, Color &TextColor, Color &BackgroundColor);

		// 修改属性
		ControlText& ChangeText(std::string& Text);
		ControlText& ChangePosition(int X, int Y);
		ControlText& ChangeSize(int Width, int Height);
		ControlText& ChangeBackgroundColor(Color BackGroundColor);

		// 设置透明度/可见度(0 -255)
		// ( 0 - 不可见, 255 - 不透明)
		ControlText& ChangeAlpha(uint8_t Alpha);
		ControlText& ChangeTextAlpha(uint8_t Alpha);

		// 没有背景
		ControlText& ChangeToNoBackground();

		// 有纯色的背景
		ControlText& ChangeToUseColorBackground();

		// 绘制
		void Draw();
		void Draw(int X, int Y);

	private:
		// 禁止复制
		ControlText(const ControlText& source);
		ControlText& operator=(const ControlText& source);

		// 写手
		Writer text_writer;

		// 背景透明
		bool is_transparent;

		// 背景颜色
		Color background_color;

		// 控件透明度
		uint8_t control_alpha;
	};

	// 控件 - 按钮
	class ControlButton: public BaseControl
	{
	public:
		ControlButton();

		// 创建纯色为背景的控件
		bool CreateControlButton(int X, int Y, int Width, int Height, Color BackgroundColor);
		
		// 创建动画为背景的控件
		bool CreateControlButton(int X, int Y, int Width, int Height, Sprite &BackgroundSprite);

		// 从文件中创建控件
		bool LoadControlButton(const char* PathName, int X, int Y);

		// 活动 - 判断控件状态
		ControlButton& Contact(int MouseX, int MouseY, bool IsMouseDown);

		// 修改属性
		ControlButton& ChangeText(std::string& Text);
		ControlButton& ChangePosition(int X, int Y);
		ControlButton& ChangeSize(int Width, int Height);
		ControlButton& ChangeBackgroundColor(Color BackGroundColor);
		ControlButton& ChangeBackgroundSprite(Sprite &BackgroundSprite);
		ControlButton& ChangeAlpha(uint8_t Alpha);
		ControlButton& ChangeTextAlpha(uint8_t Alpha);
		ControlButton& ChangeBackgroundAlpha(uint8_t Alpha);
		ControlButton& ChangeToUseSolidColorBackground();
		ControlButton& ChangeToUseSpriteBackground();

		// 绘制
		void Draw();
		void DrawFill();

	private:
		// 禁止复制
		ControlButton(const ControlButton& source);
		ControlButton& operator=(const ControlButton& source);

		// 写手
		Writer text_writer;

		// 文本显示否
		bool is_show_text;

		// 背景
		bool is_solid_color_background;
		Color background_color;
		Sprite background_sprite;
		uint8_t control_alpha;
	};

	// 控件 - 滚动条
	class ControlBar: public BaseControl
	{
	public:
		ControlBar();
		
		// 从文件中创建滚动条控件
		bool LoadControlBar(const char* PathName, int X, int Y);

		// 手动创建滚动条控件
		bool CreateControlBar(const char* Name, ControlDirect Direct, Rect &TroughRect, int BarWidth, int BarHeight, float CenterX, float CenterY, Color &BackgroundColorTrough, Color &BackgroundColorBar);

		// 活动 - 判断控件状态
		ControlBar& Contact(int MouseX, int MouseY, bool IsMouseDown);

		// 获得滚动条状态
		float GetPercent(void);

		// 修改滚动条属性
		ControlBar& ChangePercent(float Percent);
		ControlBar& ChangePercent(int MouseX, int MouseY);
		ControlBar& ChangeDirect(ControlDirect Direct);

		// 修改通用属性
		ControlBar& ChangePosition(int X, int Y);
		ControlBar& ChangeSize(int Width, int Height);
		ControlBar& ChangeBackgroundColor(Color& BackGroundColorTrough, Color& BackGroundColorbar);
		ControlBar& ChangeBackgroundSprite(Sprite &BackgroundTrough, Sprite &BackgroundBar);
		ControlBar& ChangeAlpha(uint8_t Alpha);
		ControlBar& ChangeToUseSolidColorBackground();
		ControlBar& ChangeToUseSpriteBackground();

		// 绘制
		void Draw();
		void DrawFill();

	private:

		// 禁止复制
		ControlBar(const ControlBar& source);
		ControlBar& operator=(const ControlBar& source);

		// 背景 存储两个精灵
		Color background_color_trough, background_color_bar;
		Sprite background_sprite_bar; // 控制点
		Sprite background_sprite_trough; // 滑槽

		// 滚动条属性
		ControlDirect control_direct;
		float percent;
		int bar_width;
		int bar_height;
		float center_x, center_y;

		// 属性
		bool is_solid_color_background;
		uint8_t control_alpha;

	};

	// 控件 - 列表
	class ControlList: public BaseControl
	{
	public:
		ControlList();
		~ControlList();

		// 从文件中创建控件
		bool LoadControlList(const char* PathName, int X, int Y);

		// 活动 - 判断控件状态
		ControlList& Contact(int MouseX, int MouseY, bool IsMouseDown);

		// 获得属性
		float GetPercent(void);
		ControlBar& GetControlBar();

		// 修改属性
		ControlList& ChangePercent(float Percent);
		ControlList& ChangePercent(int MouseX, int MouseY);
		ControlList& ChangePosition(int X, int Y);
		ControlList& ChangeSize(int Width, int Height);
		ControlList& ChangeBackgroundColor(Color& BackGroundColor);
		ControlList& ChangeBackgroundSprite(Sprite& BackgroundSprite);
		ControlList& ChangeAlpha(uint8_t Alpha);
		ControlList& ChangeToUseSolidColorBackground();
		ControlList& ChangeToUseSpriteBackground();

		// 列表操作
		ControlList& PushBack(const char *ControlName, const char* Text);
		ControlList& PushBack(ControlText* Entry);
		ControlList& Insert(int Position, const char *ControlName, const char* Text); // 在 Position-1 和 Position 之间插入元素
		ControlList& Insert(int Position, ControlText* Entry); // 在 Position-1 和 Position 之间插入元素
		ControlList& Delete(int Position);
		ControlText* GetControlText(int Position);
		bool IsAnyControlTextHaveMessage();
		int GetPositionOfControlTextThatHaveMessage();
		ControlText* GetControlTextThatHaveMessage();

		// 绘制
		void Draw();
		void DrawFill();

	private:
		// 禁止复制
		ControlList(const ControlList& source);
		ControlList& operator=(const ControlList& source);

		// 滑动条
		ControlBar control_bar;
		Color background_color;
		Sprite background_sprite;

		// 列表属性
		std::vector<ControlText*> list;
		int entry_height;
		float control_bar_occupy_percent;
		bool is_any_control_text_have_message;
		int position_of_control_text_that_have_message;
		
		// 属性
		bool is_solid_color_background;
		uint8_t control_alpha;
	};
}
#endif