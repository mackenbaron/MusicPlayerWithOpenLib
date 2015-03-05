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
	//                       ____________  ����"����"��Ϣ
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
	//                        ����"˫��"��Ϣ
	//
	//----------------------------------------------------------
	//                   ____________________________ ��������"��������"��Ϣ
	//                  ||||||||||||||||||||||
	//                  ||||||||||||||||||||||
	//          _____________________________
	//_________|                             |_______________
	//
	//         |________|                   /|\
	//             |                         |
	//             |                         |
	//             |                         |_____________����"������������"��Ϣ
	//        CLICK_DELTA_TIME
	//

	// ����Ԫ����
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

		// �ı�Ԫ������, ��Ҫ���̳еķ���
		virtual void DoContactReset(void);
		virtual void DoContact(int MouseX, int MouseY, bool IsMouseDown);
		virtual void DoChangePosition(int X, int Y);
		virtual void DoChangeSize(int Width, int Height);
		virtual void DoChangeAlpha(uint8_t Alpha);
		virtual void DoChangeRenderStyle(ElementRenderStyle RenderStyle);
		virtual void DoDraw(void);

		// ��ȡ����
		void DoGetAbsoluteParentDrawRect(Rect &AbsoluteRect);
		virtual BaseElement* DoGetChildElement(const char *SearchName);

	public:
		// ���캯��
		BaseElement(ElementType Type, int X, int Y, int Width, int Height, float Distance);

		// ��������
		~BaseElement();

		// �ı�Ԫ������
		BaseElement& ContactReset(void);
		BaseElement& Contact(int MouseX, int MouseY, bool IsMouseDown);
		BaseElement& ChangePosition(int X, int Y);
		BaseElement& ChangeSize(int Width, int Height);
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
		BaseElement& GetAbsoluteParentDrawRect(Rect &AbsoluteRect);
		bool IsShow();

		// ���Ĳ���
		BaseElement& GetChildElement(int Position);
		BaseElement& GetChildElement(const char *SearchName);
		int GetChildrenSize();
		BaseElement& AddChildElement(BaseElement* NewChildElement);
		BaseElement& DeleteChildElement();

		// Ԫ������
		std::string element_name;

		// Ԫ������
		const ElementType element_type;

		// λ����Ϣ
		int x, y, width, height;
		float precent_x, precent_y;
		float distance;

		// �Ƿ���ʾ
		bool is_show;

		// ͸����
		uint8_t element_alpha;

		// ���Ʒ�ʽ
		ElementRenderStyle element_render_style;

		// ����/��¼�¼�
		// ��ǰ�ؼ���Ϣ&״̬
		ElementMessage element_message;
		ElementState element_state;
		bool is_mouse_over;
		unsigned int last_down_time, last_up_time; //  ���һ�ε���/˫���ؼ���ʱ��
		bool is_last_down; // �ϴ��Ƿ���
		bool in_judge_click, in_judge_double_click, in_judge_const_down; // �Ƿ����ж�����¼�֮��
		unsigned int curr_time, delta_time; // ��ǰʱ��/����ʱ��

		BaseElement *parent;
		std::vector<BaseElement*> children;
	};
}

#endif