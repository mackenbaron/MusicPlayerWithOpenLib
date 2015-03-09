
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
		//  灰白色背景
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

		// 测试是否在元素内
		if ( 0 <= mx && mx < width && 0 <= my && my <= height)
			is_mouse_over = true;
		else
			is_mouse_over = false;

		curr_time = SDL_GetTicks();
		if(is_mouse_over) // 鼠标在控件之内
		{
			if(is_mouse_down)
			{
				if(is_last_down)// 上次按下了,这次也按下
				{
					if(in_judge_const_down) // 这是一个"持续按下"
					{
						// 记录本次按键
						last_down_time = curr_time;
						is_last_down = true;

						control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN;
					}
					else if(in_judge_click)// 正在判断"持续按下"
					{
						if((curr_time - last_up_time) > CLICK_DELTA_TIME) // 发送"持续按下"消息
						{
							in_judge_click = false;
							in_judge_const_down = true;

							// 记录本次按键
							last_down_time = curr_time;
							is_last_down = true;

							control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN;
						}
						else // 还是在判断单击
						{
							// 记录本次按键
							last_down_time = curr_time;
							is_last_down = true;

							control_message = CONTROL_MESSAGE_MOUSE_OVER;
						}

					}
					else // 正在判断"双击"
					{
						// 记录本次按键
						last_down_time = curr_time;
						is_last_down = true;

						control_message = CONTROL_MESSAGE_MOUSE_OVER;
					}
				}
				else // 上一次没按下,这次按下了
				{
					if(in_judge_double_click) // 发送"双击"消息
					{
						// 退出判断"单击"/"双击"状态
						in_judge_click = false;
						in_judge_double_click = true;

						// 记录本次按键
						last_down_time = curr_time;
						is_last_down = true;

						control_message = CONTROL_MESSAGE_MOUSE_OVER;
					}
					else // 判断单击
					{
						// 进入判断"单击"状态
						in_judge_click = true;

						// 记录本次按键
						last_down_time = curr_time;
						is_last_down = true;

						control_message = CONTROL_MESSAGE_MOUSE_OVER;
					}
				}
			}
			else
			{
				if(is_last_down) // 上次按下了,这次没按下,刚刚一定在判断事件
				{
					if(in_judge_const_down) // 退出"持续按下"
					{
						// 退出判断状态
						in_judge_const_down = false;

						// 记录本次按键
						last_up_time = curr_time;
						is_last_down = false;

						control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN_END;// 发送持续按下结束消息
					}
					else if(in_judge_double_click)// 发送"双击"消息
					{
						// 退出判断状态
						in_judge_double_click = false;

						// 记录本次按键
						last_up_time = curr_time;
						is_last_down = false;

						control_message = CONTROL_MESSAGE_MOUSE_DOUBLE_CLICK;
					}
					else // 判断"单击"/"双击"
					{
						in_judge_double_click = true;

						// 记录本次按键
						last_up_time = curr_time;
						is_last_down = false;

						control_message = CONTROL_MESSAGE_MOUSE_OVER;
					}
				}
				else  // 上次没按下,这次没按下
				{
					if(in_judge_click) // 判断单击
					{
						if(curr_time - last_down_time > DOUBLE_CLICK_DELTA_TIME) // 发送"单击"消息
						{
							// 退出判断状态
							in_judge_click = false;
							in_judge_double_click = false;

							// 记录本次按键
							last_up_time = curr_time;
							is_last_down = false;

							control_message = CONTROL_MESSAGE_MOUSE_CLICK;
						}
						else
						{
							// 记录本次按键
							last_up_time = curr_time;
							is_last_down = false;

							control_message = CONTROL_MESSAGE_MOUSE_OVER;
						}
					}
					else // 什么也没发生
					{
						// 记录本次按键
						last_up_time = curr_time;
						is_last_down = false;

						control_message = CONTROL_MESSAGE_MOUSE_OVER;
					}
				}
			}
		}
		else // 鼠标在控件之外
		{
			if(is_last_down)
			{
				if(is_mouse_down) // 鼠标按下
				{
					if(in_judge_const_down||in_judge_click||in_judge_double_click) // 正在判断事件
					{
						// 记录本次按键
						last_down_time = curr_time;
						is_last_down = true;

						control_message = CONTROL_MESSAGE_MOUSE_OUT;
					}
				}
				else // 鼠标没按下
				{
					if(in_judge_const_down) // 退出"持续按下"
					{
						// 退出判断状态
						in_judge_const_down = false;
						in_judge_double_click = false;
						in_judge_click = false;

						// 记录本次按键
						//last_up_time = curr_time;
						is_last_down = false;

						control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN_END;// 发送持续按下结束消息
					}
					else // 退出判断"单击"/"双击"
					{
						// 退出判断状态
						in_judge_const_down = false;
						in_judge_double_click = false;
						in_judge_click = false;

						// 记录本次按键
						//last_up_time = curr_time;
						is_last_down = false;

						control_message = CONTROL_MESSAGE_MOUSE_OUT;
					}

				}
			}
			else
			{
				// 退出判断状态
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