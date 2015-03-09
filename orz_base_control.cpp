
#include "orz_base_control.h"
#include "orz_config.h"
#include "orz_base_public_resource.h"


namespace Orz
{
	BaseControl::BaseControl(ElementType Type):
	BaseUi(Type, 0.0f),
	last_down_time(0), last_up_time(0),
	is_last_down(0),
	in_judge_click(false), in_judge_double_click(false), in_judge_const_down(false)
	{
		//  �Ұ�ɫ����
		control_background_color.r = control_background_color.g = control_background_color.b = 200;
		control_background_color.a = 255;
	}

	BaseControl& BaseControl::ChangeBackgroundColor(const Color &BackGroundColor)
	{
		control_background_color = BackGroundColor;
		return *this;
	}


	void BaseControl::DoContact(void)
	{
		int mx, my;
		bool is_mouse_down = device.input.GetButton(KEY_MOUSE_LEFT);
		GetMousePosition(mx, my);

		if (IsShow() == false)
			return;

		// �����Ƿ���Ԫ����
		if ( 0 <= mx && mx < width && 0 <= my && my <= height)
			is_mouse_over = true;
		else
			is_mouse_over = false;

		curr_time = SDL_GetTicks();
		if(is_mouse_over) // ����ڿؼ�֮��
		{
			if(is_mouse_down)
			{
				if(is_last_down)// �ϴΰ�����,���Ҳ����
				{
					if(in_judge_const_down) // ����һ��"��������"
					{
						// ��¼���ΰ���
						last_down_time = curr_time;
						is_last_down = true;

						control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN;
					}
					else if(in_judge_click)// �����ж�"��������"
					{
						if((curr_time - last_up_time) > CLICK_DELTA_TIME) // ����"��������"��Ϣ
						{
							in_judge_click = false;
							in_judge_const_down = true;

							// ��¼���ΰ���
							last_down_time = curr_time;
							is_last_down = true;

							control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN;
						}
						else // �������жϵ���
						{
							// ��¼���ΰ���
							last_down_time = curr_time;
							is_last_down = true;

							control_message = CONTROL_MESSAGE_MOUSE_OVER;
						}

					}
					else // �����ж�"˫��"
					{
						// ��¼���ΰ���
						last_down_time = curr_time;
						is_last_down = true;

						control_message = CONTROL_MESSAGE_MOUSE_OVER;
					}
				}
				else // ��һ��û����,��ΰ�����
				{
					if(in_judge_double_click) // ����"˫��"��Ϣ
					{
						// �˳��ж�"����"/"˫��"״̬
						in_judge_click = false;
						in_judge_double_click = true;

						// ��¼���ΰ���
						last_down_time = curr_time;
						is_last_down = true;

						control_message = CONTROL_MESSAGE_MOUSE_OVER;
					}
					else // �жϵ���
					{
						// �����ж�"����"״̬
						in_judge_click = true;

						// ��¼���ΰ���
						last_down_time = curr_time;
						is_last_down = true;

						control_message = CONTROL_MESSAGE_MOUSE_OVER;
					}
				}
			}
			else
			{
				if(is_last_down) // �ϴΰ�����,���û����,�ո�һ�����ж��¼�
				{
					if(in_judge_const_down) // �˳�"��������"
					{
						// �˳��ж�״̬
						in_judge_const_down = false;

						// ��¼���ΰ���
						last_up_time = curr_time;
						is_last_down = false;

						control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN_END;// ���ͳ������½�����Ϣ
					}
					else if(in_judge_double_click)// ����"˫��"��Ϣ
					{
						// �˳��ж�״̬
						in_judge_double_click = false;

						// ��¼���ΰ���
						last_up_time = curr_time;
						is_last_down = false;

						control_message = CONTROL_MESSAGE_MOUSE_DOUBLE_CLICK;
					}
					else // �ж�"����"/"˫��"
					{
						in_judge_double_click = true;

						// ��¼���ΰ���
						last_up_time = curr_time;
						is_last_down = false;

						control_message = CONTROL_MESSAGE_MOUSE_OVER;
					}
				}
				else  // �ϴ�û����,���û����
				{
					if(in_judge_click) // �жϵ���
					{
						if(curr_time - last_down_time > DOUBLE_CLICK_DELTA_TIME) // ����"����"��Ϣ
						{
							// �˳��ж�״̬
							in_judge_click = false;
							in_judge_double_click = false;

							// ��¼���ΰ���
							last_up_time = curr_time;
							is_last_down = false;

							control_message = CONTROL_MESSAGE_MOUSE_CLICK;
						}
						else
						{
							// ��¼���ΰ���
							last_up_time = curr_time;
							is_last_down = false;

							control_message = CONTROL_MESSAGE_MOUSE_OVER;
						}
					}
					else // ʲôҲû����
					{
						// ��¼���ΰ���
						last_up_time = curr_time;
						is_last_down = false;

						control_message = CONTROL_MESSAGE_MOUSE_OVER;
					}
				}
			}
		}
		else // ����ڿؼ�֮��
		{
			if(is_last_down)
			{
				if(is_mouse_down) // ��갴��
				{
					if(in_judge_const_down||in_judge_click||in_judge_double_click) // �����ж��¼�
					{
						// ��¼���ΰ���
						last_down_time = curr_time;
						is_last_down = true;

						control_message = CONTROL_MESSAGE_MOUSE_OUT;
					}
				}
				else // ���û����
				{
					if(in_judge_const_down) // �˳�"��������"
					{
						// �˳��ж�״̬
						in_judge_const_down = false;
						in_judge_double_click = false;
						in_judge_click = false;

						// ��¼���ΰ���
						//last_up_time = curr_time;
						is_last_down = false;

						control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN_END;// ���ͳ������½�����Ϣ
					}
					else // �˳��ж�"����"/"˫��"
					{
						// �˳��ж�״̬
						in_judge_const_down = false;
						in_judge_double_click = false;
						in_judge_click = false;

						// ��¼���ΰ���
						//last_up_time = curr_time;
						is_last_down = false;

						control_message = CONTROL_MESSAGE_MOUSE_OUT;
					}

				}
			}
			else
			{
				// �˳��ж�״̬
				in_judge_const_down = false;
				in_judge_double_click = false;
				in_judge_click = false;

				is_last_down = false;

				control_message = CONTROL_MESSAGE_MOUSE_OUT;
			}
		}
		
		// Control State
		if(in_judge_click||in_judge_double_click||in_judge_const_down)
		{
			control_state = CONTROL_STATE_MOUSE_DOWN;
		}
		else
		{
			if (is_mouse_over)
			{
				control_state = CONTROL_STATE_MOUSE_OVER;
			}
			else
			{
				control_state = CONTROL_STATE_MOUSE_OUT;
			}
		}

		// Ui State
		switch(control_state)
		{
		case CONTROL_STATE_MOUSE_OUT:
			SetUiState(UI_STATE_MOUSE_OUT);
			break;
		case CONTROL_STATE_MOUSE_OVER:
			SetUiState(UI_STATE_MOUSE_OVER);
			break;
		case CONTROL_STATE_MOUSE_DOWN:
			SetUiState(UI_STATE_MOUSE_DOWN);
			break;
		default:
			SetUiState(UI_STATE_DEFAULT);
			break;
		}


		// Element State
		if (control_state != CONTROL_STATE_MOUSE_OUT)
		{
			element_state = ELEMENT_STATE_CONTACT;
		}
		else
		{
			element_state = ELEMENT_STATE_NONE;
		}


#ifdef CodeDebug
		using std::cout;
		using std::endl;
		switch(control_message)
		{
		case CONTROL_MESSAGE_MOUSE_OVER:
		case CONTROL_MESSAGE_MOUSE_OUT:
			break;
		case CONTROL_MESSAGE_FUNCTION_ERROR:
			cout<<element_name<<":ERROR!"<<endl;
			break;

		case CONTROL_MESSAGE_MOUSE_CONST_DOWN:
			cout<<element_name<<":MOUSE_CONST_DOWN"<<endl;
			break;
		case CONTROL_MESSAGE_MOUSE_CONST_DOWN_END:
			cout<<element_name<<":MOUSE_CONST_DOWN_END"<<endl;
			break;
		case CONTROL_MESSAGE_MOUSE_CLICK:
			cout<<element_name<<":MOUSE_CLICK"<<endl;
			break;
		case CONTROL_MESSAGE_MOUSE_DOUBLE_CLICK:
			cout<<element_name<<":MOUSE_DOUBLE_CLICK"<<endl;
			break;
		}
#endif
	}

	void BaseControl::DoContactReset(void)
	{
		control_message  = CONTROL_MESSAGE_MOUSE_OUT;
		control_state = CONTROL_STATE_MOUSE_OUT;

		is_mouse_over = false;
		last_down_time = 0, last_up_time = 0;
		is_last_down = false;
		in_judge_click = in_judge_double_click = in_judge_const_down = false;
		curr_time = 0, delta_time = 0;
	}

	const Color& BaseControl::GetBackgroundColor(void)
	{
		return control_background_color;
	}
}