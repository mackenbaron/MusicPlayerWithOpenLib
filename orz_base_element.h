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

	// ����Ԫ���� - ������
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

		// �ı�Ԫ������, ��Ҫ���̳еķ���
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

		// ��ȡ����
		virtual void DoGetMousePosition(int &MouseX, int &MouseY);
		virtual void DoGetAbsoluteDrawRect(Rect &AbsoluteRect);
		virtual BaseElement* DoSearchChildThatHaveContact(void);
		virtual BaseElement* DoSearchChildren(const char *SearchName);

	public:
		// ��ֹ����
		BaseElement(const BaseElement& source);
		BaseElement& operator=(const BaseElement& source);

		// ���캯��
		BaseElement(ElementType Type, int X, int Y, int Width, int Height, float Distance);

		// �������� �麯��
		virtual ~BaseElement();

		// �ı�Ԫ������
		BaseElement& Free(void);
		BaseElement& ContactReset(void);
		BaseElement& Contact(void);
		BaseElement& ChangePosition(int X, int Y);
		BaseElement& ChangePositionAaccordToParent(float PrecentX, float PrecentY);
		BaseElement& ChangeSize(int Width, int Height);
		BaseElement& ChangeSize(float Scale);
		BaseElement& ChangeSize(float ScaleWidth, float ScaleHeight); // ��Ҫû����������ô˺���,����ÿ��ѭ��������С����
		BaseElement& ChangeDistance(float Distance);
		BaseElement& ChangeAlpha(uint8_t Alpha);
		BaseElement& ChangeRenderStyle(ElementRenderStyle RenderStyle);
		BaseElement& Show(void);
		BaseElement& Hide(void);
		BaseElement& Draw(void);

		// ��ȡԪ������
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

		// ���Ĳ���
		int ChildrenSize();
		bool ChildrenEmpty(void);
		BaseElement& Children(int Position);
		BaseElement& SearchChildren(const char *SearchName);
		BaseElement& ChildrenPushBack(BaseElement* NewChildElement);

		//        _________________�������
		//       |                               *���� Position-1 �� Position ֮�����Ԫ��
		// __0__  __1__  __2__
		//          |_______________���� Position
		BaseElement& ChildrenInsert(int Position, BaseElement* NewChildElement);
		BaseElement& ChildrenErease(int Position);

		// Ԫ������
		std::string element_name;

		// Ԫ������
		const ElementType element_type;

		// λ����Ϣ
		int x, y, width, height;
		float distance;


		// ͸����
		unsigned char element_alpha;

		// ���Ʒ�ʽ
		ElementRenderStyle element_render_style;

		// ��¼Ԫ����Ϣand״̬
		ElementMessage element_message;
		ElementState element_state;

		// ������
		BaseElement *parent;
	private:
		std::vector<BaseElement*> children;

		// �Ƿ���ʾ
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