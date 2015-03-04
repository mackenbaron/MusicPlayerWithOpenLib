#ifndef ORZ_BASE_ELEMENT_H_INCLUDED
#define ORZ_BASE_ELEMENT_H_INCLUDED

#include <string>
#include "orz_base_math.h"

namespace Orz
{
	const int CLICK_DELTA_TIME = 150;
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

	// �����ؼ��� - ������
	class BaseElement
	{
	public:
		// ���캯��
		BaseElement(int X, int Y, int Width, int Height);

		// ��������
		virtual ~BaseElement()=0;

		// �ı�ؼ�λ��
		virtual BaseElement& ChangePosition(int X, int Y);
		virtual BaseElement& ChangeSize(int Width, int Height);

		// ��ȡ�ؼ�λ����Ϣ
		const std::string& GetName();
		BaseElement& GetPosition(int &x, int &y);
		BaseElement& GetSize(int &width, int &height);
		virtual int GetSizeWidth();
		virtual int GetSizeHeight();
		bool IsShow();

		// ��ʾ/����
		void Show(void);
		void Hide(void);

		// � - �жϿؼ�״̬
		virtual BaseElement& Contact(int MouseX, int MouseY, bool IsMouseDown);

		// ��ȡ��ǰ�ؼ�״̬
		ControlMessage GetMessage(void);
		ControlState GetState(void);

		// �ж�����Ƿ��ڿؼ���
		bool IsMouseOver(int MouseX, int MouseY);

		// ����
		virtual void Draw(void);
		virtual void DrawFill(void);

		// �ؼ�����
		std::string control_name;

		// λ����Ϣ
		int x, y, width, height;

		// �Ƿ���ʾ
		bool is_show;

		// ��ǰ�ؼ���Ϣ&״̬
		ControlMessage control_message;
		ControlState control_state;

		// ����/��¼�¼�
		unsigned int last_down_time, last_up_time; //  ���һ�ε���/˫���ؼ���ʱ��
		bool is_last_down; // �ϴ��Ƿ���
		bool in_judge_click, in_judge_double_click, in_judge_const_down; // �Ƿ����ж�����¼�֮��
		unsigned int curr_time, delta_time; // ��ǰʱ��/����ʱ��
	};

}

#endif