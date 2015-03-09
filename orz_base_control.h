#ifndef ORZ_BASE_CONTROL_H_INCLUDED
#define ORZ_BASE_CONTROL_H_INCLUDED

#include "orz_base_math.h"
#include "orz_base_ui.h"

#define WRITER_DISTANCE -1000.0f
#define SPRITE_DISTANCE -500.0f

namespace Orz
{
	// �����ؼ��� - ������
    class BaseControl: public BaseUi
    {
    public:
		// ���캯��
		BaseControl(ElementType Type);

		// �޸�����
		BaseControl& ChangeBackgroundColor(const Color &BackGroundColor);

		// ��ȡ����
		const Color& GetBackgroundColor(void);
		ControlMessage GetControlMessage(void);
		ControlState GetControlState(void);
	
	private:

		// DoContact ������------------------------------------------------------------------
		//																					|
		//                       ____________  ����"����"��Ϣ								|
		//                      |															|
		//                     \|/															|
		//        _____																		|
		//_______|     |___________________													|
		//																					|
		//       |________|																	|
		//           |																		|
		//           |																		|
		//           |																		|
		//       CLICK_DELTA_TIME															|
		//-------------------------------------------------------------						|
		//																					|
		//																					|
		//																					|
		//                   ________ DOUBLE_CLICK_DELTA_TIME								|
		//                  |																|
		//          _____  \|/  _____														|
		//_________|     |_____|     |_____________											|
		//																					|
		//                          /|\														|
		//                           |														|
		//                           |														|
		//                        ����"˫��"��Ϣ												|
		//																					|
		//----------------------------------------------------------						|
		//                   ____________________________ ��������"��������"��Ϣ				|
		//                  ||||||||||||||||||||||											|
		//                  ||||||||||||||||||||||											|
		//          _____________________________											|
		//_________|                             |_______________							|
		//																					|
		//         |________|                   /|\											|
		//             |                         |											|
		//             |                         |											|
		//             |                         |_____________����"������������"��Ϣ		|
		//        CLICK_DELTA_TIME															|
		// ________________________________________________________________________________	|
		virtual void DoContact(void);
		virtual void DoContactReset(void);

		// ������ɫ
		Color control_background_color;

		// ��Ϣ and ״̬
		ControlMessage control_message;
		ControlState control_state;

		// DoContact ��¼����Ϣ
		unsigned int last_down_time, last_up_time; //  ���һ�ε���/˫���ؼ���ʱ��
		bool is_last_down; // �ϴ��Ƿ���
		bool in_judge_click, in_judge_double_click, in_judge_const_down; // �Ƿ����ж�����¼�֮��
		unsigned int curr_time, delta_time; // ��ǰʱ��/����ʱ��
		bool is_mouse_over;
    };
}

#endif // ORZ_CONTROL_H_INCLUDED
