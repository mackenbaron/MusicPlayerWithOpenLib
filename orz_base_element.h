#ifndef ORZ_BASE_ELEMENT_H_INCLUDED
#define ORZ_BASE_ELEMENT_H_INCLUDED

#include <string>
#include <vector>
#include "orz_base_math.h"
#include "orz_base_private_math.h"

namespace Orz
{
	const int CLICK_DELTA_TIME = 250;
	const int DOUBLE_CLICK_DELTA_TIME = 150;

	//
	//                       ____________  发送"单击"消息
	//                      |
	//                     \|/
	//        _____
	//_______|     |___________________
	//
	//       |________|
	//           |
	//           |
	//           |
	//       CLICK_DELTA_TIME
	//-------------------------------------------------------------
	//
	//
	//
	//                   ________ DOUBLE_CLICK_DELTA_TIME
	//                  |
	//          _____  \|/  _____
	//_________|     |_____|     |_____________
	//
	//                          /|\
	//                           |
	//                           |
	//                        发送"双击"消息
	//
	//----------------------------------------------------------
	//                   ____________________________ 持续发送"持续按键"消息
	//                  ||||||||||||||||||||||
	//                  ||||||||||||||||||||||
	//          _____________________________
	//_________|                             |_______________
	//
	//         |________|                   /|\
	//             |                         |
	//             |                         |
	//             |                         |_____________发送"持续按键结束"消息
	//        CLICK_DELTA_TIME
	//

	// 基础元素类
	class BaseElement
	{
	private:
		void ContactResetSub(BaseElement *element);
		void ContactSub(BaseElement *element, int MouseX, int MouseY, bool IsMouseDown);
		void ChangePositionSub(BaseElement *element, int X, int Y);
		void ChangeSizeSub(BaseElement *element, int Width, int Height);
		void ChangeAlphaSub(BaseElement *element, uint8_t Alpha);
		void ChangeRenderStyleSub(BaseElement *element, ElementRenderStyle RenderStyle);
		void DrawSub(BaseElement *element);
		void GetAbsoluteParentDrawRectSub(BaseElement *element, Rect &AbsoluteRect);
		BaseElement* GetChildElementSub(BaseElement *element, const char *SearchName);

		// 改变元素属性, 需要被继承的方法
		virtual void DoContactReset(void);
		virtual void DoContact(int MouseX, int MouseY, bool IsMouseDown);
		virtual void DoChangePosition(int X, int Y);
		virtual void DoChangeSize(int Width, int Height);
		virtual void DoChangeAlpha(uint8_t Alpha);
		virtual void DoChangeRenderStyle(ElementRenderStyle RenderStyle);
		virtual void DoDraw(void);

		// 获取操作
		void DoGetAbsoluteParentDrawRect(Rect &AbsoluteRect);
		virtual BaseElement* DoGetChildElement(const char *SearchName);

	public:
		// 构造函数
		BaseElement(ElementType Type, int X, int Y, int Width, int Height, float Distance);

		// 析构函数
		~BaseElement();

		// 改变元素属性
		BaseElement& ContactReset(void);
		BaseElement& Contact(int MouseX, int MouseY, bool IsMouseDown);
		BaseElement& ChangePosition(int X, int Y);
		BaseElement& ChangeSize(int Width, int Height);
		BaseElement& ChangeAlpha(uint8_t Alpha);
		BaseElement& ChangeRenderStyle(ElementRenderStyle RenderStyle);
		BaseElement& Show(void);
		BaseElement& Hide(void);
		BaseElement& Draw(void);

		// 获取元素属性
		const std::string& GetName();
		ElementMessage GetMessage(void);
		ElementState GetState(void);
		BaseElement& GetPosition(int &X, int &Y);
		BaseElement& GetSize(int &Width, int &Height);
		int GetSizeWidth();
		int GetSizeHeight();
		BaseElement& GetSizeWidth(int &Width);
		BaseElement& GetSizeHeight(int &Height);
		BaseElement& GetAbsolutePosition(int &X, int &Y);
		BaseElement& GetAbsoluteParentDrawRect(Rect &AbsoluteRect);
		bool IsShow();

		// 树的操作
		BaseElement& GetChildElement(int Position);
		BaseElement& GetChildElement(const char *SearchName);
		int GetChildrenSize();
		BaseElement& AddChildElement(BaseElement* NewChildElement);
		BaseElement& DeleteChildElement();

		// 元素名字
		std::string element_name;

		// 元素类型
		const ElementType element_type;

		// 位置信息
		int x, y, width, height;
		float precent_x, precent_y;
		float distance;

		// 是否显示
		bool is_show;

		// 透明度
		uint8_t element_alpha;

		// 绘制方式
		ElementRenderStyle element_render_style;

		// 处理/记录事件
		// 当前控件消息&状态
		ElementMessage element_message;
		ElementState element_state;
		bool is_mouse_over;
		unsigned int last_down_time, last_up_time; //  最后一次单击/双击控件的时间
		bool is_last_down; // 上次是否按下
		bool in_judge_click, in_judge_double_click, in_judge_const_down; // 是否在判断鼠标事件之内
		unsigned int curr_time, delta_time; // 当前时间/推移时间

		BaseElement *parent;
		std::vector<BaseElement*> children;
	};
}

#endif