
#include "orz_base_device_input.h"
#include "orz_base_time.h"
#include "orz_base_math.h"
#include "orz_base_public_resource.h"

namespace Orz
{
	// 初始化
	bool _DeviceInput::Init()
	{
		wheel_delta = 0;

		return true;
	}

	// 触发输入
	void _DeviceInput::Contact(InputKeyCode which_key, bool is_input_down)
	{
		button[which_key].Contact(is_input_down);
	}

	void _DeviceInput::ContactWheel(int mouse_wheel)
	{
		wheel_delta = mouse_wheel;
	}

	// 获取输入
	bool _DeviceInput::GetButton(InputKeyCode which_key)
	{
		if((KEY_MIN<which_key)&&(which_key<KEY_MAX))
		{
			return button[which_key].is_button_down;
		}
		else
			return false;
	}

	int _DeviceInput::GetMouseWheel()
	{
		return wheel_delta;
	}

	ControlMessage _DeviceInput::GetButtonMessage(InputKeyCode which_key)
	{
		return button[which_key].control_message;
	}

	void InputButton::Contact(bool IsButtonDown)
	{
		is_button_down = IsButtonDown;

		unsigned long curr_time;
		curr_time = SDL_GetTicks();

		if(is_button_down) // 按下
		{
			if(is_last_down)// 上次按下了,这次也按下
			{
				// 不干任何事
			}
			else // 上一次没按下,这次按下了
			{
				sign_start_time = curr_time;
			}

			is_last_down = true;
			control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN;
		}
		else // 没按下
		{
			if(is_last_down) // 上次按下了,这次没按下,判断信号
			{
				// 这次是长按?
				if (curr_time - sign_start_time > SHORT_SIGN_DELTA_TIME)
				{
					is_last_short_sign = false;
					control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN_END;
				}
				else // 不是长按. 那是单击,双击?
				{
					if(is_last_short_sign) // 上次是否是短信号?
					{
						// 单击,双击?
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
					else // 上次是长信号,这次短信号,一点是单击
					{
						is_last_short_sign = true;
						control_message = CONTROL_MESSAGE_MOUSE_CLICK;
					}
				}

				is_last_down = false;
				sign_end_time = curr_time;
			}
			else  // 上次没按下,这次没按下
			{
				control_message = CONTROL_MESSAGE_MOUSE_OVER;
			}

			is_last_down = false;
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


#ifdef CodeDebug
		using std::cout;
		using std::endl;
		InputKeyCode element_name(KEY_MAX);
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

}