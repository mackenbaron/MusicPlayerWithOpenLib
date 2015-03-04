#ifndef ORZ_MANAGEMENT_H_INCLUDED
#define ORZ_MANAGEMENT_H_INCLUDED


#include "orz_animate.h"
#include "orz_writer.h"
#include "orz_base_RBTree.h"
#include "orz_control.h"

namespace Orz
{
	class BaseElement
	{

	private:
		Rect size;
		float distance;
	};

	class _Manager
	{
	public:
		_Manager();

		// 开始运行程序
		void Go(bool (*_CreateScene)(), void (*_UpdateScene)());

		// 退出场景
		void QuitScene();

		// 动画
		virtual Animate* CreateAnimate(KeyType Name, const char *NamePath);
		virtual Animate& GetAnimate(KeyType Name);

		// 书写者
		virtual Writer* CreateWriter(KeyType Name, std::string FontName, std::string Text, int FontSize, Color FontColor, Rect DestRect);
		virtual Writer& GetWriter(KeyType Name);

		// 创建控件
		virtual ControlText* CreateControlText(KeyType Name, const char *ControlName, int X, int Y, int Width, int Height, const char *FontName, int FontSize, const char *Text, Color &TextColor, Color &BackgroundColor);
		virtual ControlButton* CreateControlButton(KeyType Name, const char* PathName, int X, int Y);
		virtual ControlBar* CreateControlBar(KeyType Name, const char* PathName, int X, int Y);
		virtual ControlList* CreateControlList(KeyType Name, const char* PathName, int X, int Y);

		// 得到控件
		virtual ControlText& GetControlText(KeyType Name);
		virtual ControlButton& GetControlButton(KeyType Name);
		virtual ControlBar& GetControlBar(KeyType Name);
		virtual ControlList& GetControlList(KeyType Name);

	private:
		// 绘图
		void PresentScene();
		void UpdateDebugScene();

		// 用于标识循环
		bool is_loop;

		// 错误处理
		Animate error_animate;
		Writer error_writer;
		ControlText error_control_text;
		ControlButton error_control_button;
		ControlBar error_control_bar;
		ControlList error_control_list;

		// 红黑树
		RBTree rb_tree;
	};
}

#endif