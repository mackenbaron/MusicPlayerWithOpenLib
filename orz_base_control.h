#ifndef ORZ_BASE_CONTROL_H_INCLUDED
#define ORZ_BASE_CONTROL_H_INCLUDED

#include "orz_base_math.h"
#include "orz_base_ui.h"

#define WRITER_DISTANCE 1000.0f
#define SPRITE_DISTANCE 500.0f

namespace Orz
{
	//const long SHORT_SIGN_DELTA_TIME = 150;
	//const long DOUBLE_CLICK_DELTA_TIME = 150;

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
	

		// DoContact ������---------------------------------------------------------------	|
		// ���������ź�:																	  	|
		// 1.���ź�     2.���ź�															  	|
		// 3.��,���ͺ�  3.��,���ź�													      	|
		// 2.��,���ź�  4.��,���ź�													      	|
		//																				  	|
		// �����ź�: �źŷ��ͼ����														  	|
		//																				  	|
		//																				  	|
		//          ________															  	|
		//_________|        |______________________________  ����						  	|
		//																				  	|
		//          _____________________________										  	|
		//_________|                             |_________  ����						  	|
		//																				  	|
		//          _______           _______											  	|
		//_________|       |_________|       |_____________	 ���ε���					  	|
		//																				  	|
		//          _______       _______												  	|
		//_________|       |_____|       |_________________  ˫��						  	|
		//																				  	|
		//                 |_____|				  										  	|
		//                    |						  									  	|
		//                    |	__DOUBLE_CLICK_DELTA_TIME								  	|
		//																				  	|
		//              __________________���ź�ʱ�� SHORT_SIGN_TIME						  	|
		//          ___|___ 															  	|
		//         |       |															  	|
		//          _______																  	|
		//_________|       |_________________________    ���ź�						      	|
		//																				  	|
		//          _____________________________										  	|
		//_________|                             |___    ���ź� (ʱ�䳬�����źŵľ��ǳ��ź�)	|
		// 																				  	|
		//          _______																  	|
		//_________|       |_________________________    ���ź�						   		|
		// ________________________________________________________________________________	|

		void DoContactReset(void); // ע��ʹ�ñ�����!
		void DoContact(void);

	private:
		// ������ɫ
		Color control_background_color;

		// ��Ϣ and ״̬
		ControlMessage control_message;
		ControlState control_state;

		// DoContact ��¼����Ϣ
		unsigned long sign_start_time, sign_end_time;
		bool is_last_down, is_last_short_sign;
		bool is_mouse_over;
    };
}

#endif // ORZ_CONTROL_H_INCLUDED
