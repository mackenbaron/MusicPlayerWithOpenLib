#ifndef ORZ_BASE_ELEMENT_H_INCLUDED
#define ORZ_BASE_ELEMENT_H_INCLUDED

#include <string>
#include <vector>
#include "orz_base_math.h"
#include "orz_log.h"

namespace Orz
{
	const int CLICK_DELTA_TIME = 250;
	const int DOUBLE_CLICK_DELTA_TIME = 150;

	// 基础元素类 - 纯虚类
	class BaseElement
	{
	private:
		void FreeSub(BaseElement *element);
		void ContactResetSub(BaseElement *element);
		void ContactSub(BaseElement *element);
		void ChangePositionSub(BaseElement *element, int X, int Y);
		void ChangePositionAaccordToParent(BaseElement *element, float PrecentX, float PrecentY);
		void ChangeSizeSub(BaseElement *element, float Scale);
		void ChangeSizeSub(BaseElement *element, float ScaleWidth, float ScaleHeight);
		void ChangeAlphaSub(BaseElement *element, uint8_t Alpha);
		void ChangeRenderStyleSub(BaseElement *element, ElementRenderStyle RenderStyle);
		void DrawSub(BaseElement *element);

		void GetMousePositionSub(BaseElement *element, int &MouseX, int &MouseY);
		void GetAbsoluteDrawRectSub(BaseElement *element, Rect &AbsoluteRect);
		BaseElement* SearchChildThatHaveContactSub(BaseElement *element);
		BaseElement* SearchChildrenSub(BaseElement *element, const char *SearchName);

		// 改变元素属性, 需要被继承的方法
		virtual void DoFree(void);
		virtual void DoContactReset(void)=0;
		virtual void DoContact(void)=0;
		virtual void DoChangePosition(int X, int Y);
		virtual void DoChangePositionAaccordToParent(float PrecentX, float PrecentY);
		virtual void DoChangeSize(int Width, int Height);
		virtual void DoChangeSize(float ScaleWidth, float ScaleHeight);
		virtual void DoChangeSize(float Scale);
		virtual void DoChangeAlpha(unsigned char Alpha);
		virtual void DoChangeRenderStyle(ElementRenderStyle RenderStyle);
		virtual void DoDraw(void)=0;

		// 获取操作
		virtual void DoGetMousePosition(int &MouseX, int &MouseY);
		virtual void DoGetAbsoluteDrawRect(Rect &AbsoluteRect);
		virtual BaseElement* DoSearchChildThatHaveContact(void);
		virtual BaseElement* DoSearchChildren(const char *SearchName);

	public:
		// 禁止复制
		BaseElement(const BaseElement& source);
		BaseElement& operator=(const BaseElement& source);

		// 构造函数
		BaseElement(ElementType Type, int X, int Y, int Width, int Height, float Distance);

		// 析构函数 虚函数
		virtual ~BaseElement();

		// 改变元素属性
		BaseElement& Free(void);
		BaseElement& ContactReset(void);
		BaseElement& Contact(void);
		BaseElement& ChangePosition(int X, int Y);
		BaseElement& ChangePositionAaccordToParent(float PrecentX, float PrecentY);
		BaseElement& ChangeSize(int Width, int Height);
		BaseElement& ChangeSize(float Scale);
		BaseElement& ChangeSize(float ScaleWidth, float ScaleHeight); // 不要没条件地里调用此函数,否则每次循环都会缩小画面
		BaseElement& ChangeDistance(float Distance);
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
		BaseElement& GetAbsoluteDrawRect(Rect &AbsoluteRect);
		BaseElement& GetMousePosition(int &MouseX, int &MouseY);
		BaseElement& SearchChildThatHaveContact(void);
		bool IsShow();

		// 树的操作
		int ChildrenSize();
		bool ChildrenEmpty(void);
		BaseElement& Children(int Position);
		BaseElement& SearchChildren(const char *SearchName);
		BaseElement& ChildrenPushBack(BaseElement* NewChildElement);

		//        _________________在这插入
		//       |                               *即在 Position-1 和 Position 之间插入元素
		// __0__  __1__  __2__
		//          |_______________这是 Position
		BaseElement& ChildrenInsert(int Position, BaseElement* NewChildElement);
		BaseElement& ChildrenErease(int Position);

		// 元素名字
		std::string element_name;

		// 元素类型
		const ElementType element_type;

		// 位置信息
		int x, y, width, height;
		float distance;


		// 透明度
		unsigned char element_alpha;

		// 绘制方式
		ElementRenderStyle element_render_style;

		// 记录元素消息and状态
		ElementMessage element_message;
		ElementState element_state;

		// 树数据
		BaseElement *parent;
	private:
		std::vector<BaseElement*> children;

		// 是否显示
		bool is_show;
	};

	class ElementError: public BaseElement
	{
	public:
		ElementError():BaseElement(ELEMENT_TYPE_ERROR, 0, 0, 0, 0, 0.0f){error_out("ElementError: - ElementError()");}
	private:
		void DoContact(){error_out("ElementError: - DoContact()");}
		void DoContactReset(){error_out("ElementError: - DoContactReset()");}
		void DoDraw(){error_out("ElementError: - DoDraw()");}
	};

	extern ElementError error_element;
}

#endif