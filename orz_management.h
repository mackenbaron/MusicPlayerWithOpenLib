#ifndef ORZ_MANAGEMENT_H_INCLUDED
#define ORZ_MANAGEMENT_H_INCLUDED


#include "orz_animate.h"
#include "orz_writer.h"
#include "orz_base_RBTree.h"
#include "orz_control.h"
#include "orz_complex_control.h"
#include "orz_base_public_resource.h"

namespace Orz
{
	class ElementRoot: public BaseElement
	{
	public:
		ElementRoot();
		void DoContact();
		void DoContactReset();
		void DoDraw();
	};

	class _Manager
	{
	public:
		_Manager();

		// 开始运行程序
		void Go(bool (*_CreateScene)(), void (*_UpdateScene)());

		// 退出场景
		void QuitScene();

		// 创建
		Animate* CreateAnimate(KeyType Name, const char *NamePath, const Rect &AnimateRect);
		Sprite* CreateSprite(KeyType Name, const char *NamePath, const Rect &SpriteRect);
		Writer* CreateWriter(KeyType Name, std::string FontName, std::string Text, int FontSize, Color FontColor, Rect DestRect);
		ControlText* CreateControlText(KeyType Name, const char *ControlName, const Rect &ControlRect, Color &BackgroundColor, const char *FontName, int FontSize, const char *Text, Color &TextColor);
		ControlButton* CreateControlButton(KeyType Name, const char* ControlName, const Rect &ControlRect, const Color &BackgroundColor);
		ControlScrollBar* CreateControlScrollBar(KeyType Name, const char* ControlName, ControlDirect Direct, const Rect &ControlRect, const Color &BackgroundColorTrough, const Color &BackgroundColorBar);
		ControlList* CreateControlList(KeyType Name, const char* ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize);

		// 获取
		BaseElement& GerRoot();
		bool IsHaveElementThatHaveContact();
		BaseElement& GetElementThatHaveContact();
		Animate& GetAnimate(KeyType Name);
		Writer& GetWriter(KeyType Name);
		ControlText& GetControlText(KeyType Name);
		ControlButtonWithWriter& GetControlButton(KeyType Name);
		ControlScrollBar& GetControlBar(KeyType Name);
		ControlList& GetControlList(KeyType Name);

	private:
		// 绘图
		void PresentScene();
		void UpdateDebugScene();

		// 用于标识循环
		bool is_loop;

		// 红黑树
		RBTree rb_tree;
		
		// 元素根节点
		ElementRoot element_root;
		bool is_have_element_that_have_contact;
		BaseElement* element_that_have_contact;
		// 错误处理函数
	};
}

#endif