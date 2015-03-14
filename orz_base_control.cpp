
#include "orz_base_control.h"
#include "orz_config.h"
#include "orz_base_public_resource.h"


namespace Orz
{
	BaseControl::BaseControl(ElementType Type):
	BaseUi(Type, 0.0f),
	sign_start_time(0), sign_end_time(0),
	is_last_down(false), is_last_short_sign(false)
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

		unsigned long curr_time;
		curr_time = SDL_GetTicks();

		if(is_mouse_over) // ����ڿؼ�֮��
		{
			if(is_mouse_down) // ����
			{
				if(is_last_down)// �ϴΰ�����,���Ҳ����
				{
					// �����κ���
				}
				else // ��һ��û����,��ΰ�����
				{
					sign_start_time = curr_time;
				}

				is_last_down = true;
				control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN;
			}
			else // û����
			{
				if(is_last_down) // �ϴΰ�����,���û����,�ж��ź�
				{
					// ����ǳ���?
					if (curr_time - sign_start_time > SHORT_SIGN_DELTA_TIME)
					{
						is_last_short_sign = false;
						control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN_END;
					}
					else // ���ǳ���. ���ǵ���,˫��?
					{
						if(is_last_short_sign) // �ϴ��Ƿ��Ƕ��ź�?
						{
							// ����,˫��?
							if (sign_start_time - sign_end_time < DOUBLE_CLICK_DELTA_TIME)
							{
								is_last_short_sign = true;
								control_message = CONTROL_MESSAGE_MOUSE_DOUBLE_CLICK;
							}
							else
							{
								is_last_short_sign = true;
								control_message = CONTROL_MESSAGE_MOUSE_CLICK;
							}
						}
						else // �ϴ��ǳ��ź�,��ζ��ź�,һ���ǵ���
						{
							is_last_short_sign = true;
							control_message = CONTROL_MESSAGE_MOUSE_CLICK;
						}
					}

					is_last_down = false;
					sign_end_time = curr_time;
				}
				else  // �ϴ�û����,���û����
				{
					control_message = CONTROL_MESSAGE_MOUSE_OVER;
				}

				is_last_down = false;
			}
		}
		else // ����ڿؼ�֮��
		{
			if(is_last_down)// �ϴ���갴����
			{
				if(is_mouse_down) // �ϴ���갴����, ������Ҳ����
				{
					is_last_down = true;
					control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN;
				}
				else // �ϴΰ�����,���û����,�ж��ź�
				{
					// ����ǳ���?
					if (curr_time - sign_start_time > SHORT_SIGN_DELTA_TIME)
					{
						is_last_short_sign = false;
						control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN_END;
					}
					else // ���ǳ���. ���ǵ���,˫��?
					{
						if(is_last_short_sign) // �ϴ��Ƿ��Ƕ��ź�?
						{
							// ����,˫��?
							if (sign_start_time - sign_end_time < DOUBLE_CLICK_DELTA_TIME)
							{
								is_last_short_sign = true;
								control_message = CONTROL_MESSAGE_MOUSE_DOUBLE_CLICK;
							}
							else
							{
								is_last_short_sign = true;
								control_message = CONTROL_MESSAGE_MOUSE_CLICK;
							}
						}
						else // �ϴ��ǳ��ź�,��ζ��ź�,һ���ǵ���
						{
							is_last_short_sign = true;
							control_message = CONTROL_MESSAGE_MOUSE_CLICK;
						}
					}

					is_last_down = false;
					sign_end_time = curr_time;
				}
			}
			else // �ϴ����û����,ûʲô������
			{
				is_last_down = false;
				control_message = CONTROL_MESSAGE_MOUSE_OUT;
			}
		}

		// Control State
		switch(control_message)
		{
		case CONTROL_MESSAGE_FUNCTION_ERROR:
		case CONTROL_MESSAGE_MOUSE_OUT:
			control_state = CONTROL_STATE_MOUSE_OUT;
			break;

		case CONTROL_MESSAGE_MOUSE_OVER:
		case CONTROL_MESSAGE_MOUSE_CONST_DOWN_END:
			control_state = CONTROL_STATE_MOUSE_OVER;
			break;

		case CONTROL_MESSAGE_MOUSE_CONST_DOWN:
		case CONTROL_MESSAGE_MOUSE_CLICK:
		case CONTROL_MESSAGE_MOUSE_DOUBLE_CLICK:
			control_state = CONTROL_STATE_MOUSE_DOWN;
			break;

		default:
			control_state = CONTROL_STATE_MOUSE_OUT;
			break;
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
		if (control_state == CONTROL_STATE_MOUSE_DOWN)
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
			break;
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

		sign_start_time = sign_end_time = 0;
		is_last_down = is_last_short_sign =false;
	}

	const Color& BaseControl::GetBackgroundColor(void)
	{
		return control_background_color;
	}

	ControlMessage BaseControl::GetControlMessage(void)
	{
		return control_message;
	}

	ControlState BaseControl::GetControlState(void)
	{
		return control_state;
	}

}