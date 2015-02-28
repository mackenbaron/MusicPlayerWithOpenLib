
#include "orz_base_control.h"
#include "orz_option.h"

#ifdef CodeDebug
#include <iostream>
#endif

namespace Orz
{
	BaseControl::BaseControl(int X, int Y, int Width, int Height, ControlBackgroundStyle BackgroundStyle):
	x(X), y(Y), width(Width), height(Height),
	background_style(BackgroundStyle), is_show(true),
	last_down_time(0), last_up_time(0),
	is_last_down(0),
	in_judge_click(0), in_judge_double_click(0), in_judge_const_down(0)
	{

	}

	BaseControl::~BaseControl()
	{

	}

	BaseControl& BaseControl::Contact(int MouseX, int MouseY, bool IsMouseDown)
	{
		curr_time = SDL_GetTicks();
		if(IsMouseOver(MouseX, MouseY)) // 鼠标在控件之内
		{
			if(IsMouseDown)
			{
				if(is_last_down)// 上次按下了,这次也按下
				{
					if(in_judge_const_down) // 这是一个"持续按下"
					{
						// 记录本次按键
						last_down_time = curr_time;
						is_last_down = true;

						control_message = MOUSE_CONST_DOWN;
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

							control_message = MOUSE_CONST_DOWN;
						}
						else // 还是在判断单击
						{
							// 记录本次按键
							last_down_time = curr_time;
							is_last_down = true;

							control_message = MOUSE_OVER;
						}

					}
					else // 正在判断"双击"
					{
						// 记录本次按键
						last_down_time = curr_time;
						is_last_down = true;

						control_message = MOUSE_OVER;
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

						control_message = MOUSE_OVER;
					}
					else // 判断单击
					{
						// 进入判断"单击"状态
						in_judge_click = true;

						// 记录本次按键
						last_down_time = curr_time;
						is_last_down = true;

						control_message = MOUSE_OVER;
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

						control_message = MOUSE_CONST_DOWN_END;// 发送持续按下结束消息
					}
					else if(in_judge_double_click)// 发送"双击"消息
					{
						// 退出判断状态
						in_judge_double_click = false;

						// 记录本次按键
						last_up_time = curr_time;
						is_last_down = false;

						control_message = MOUSE_DOUBLE_CLICK;
					}
					else // 判断"单击"/"双击"
					{
						in_judge_double_click = true;

						// 记录本次按键
						last_up_time = curr_time;
						is_last_down = false;

						control_message = MOUSE_OVER;
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

							control_message = MOUSE_CLICK;
						}
						else
						{
							// 记录本次按键
							last_up_time = curr_time;
							is_last_down = false;

							control_message = MOUSE_OVER;
						}
					}
					else // 什么也没发生
					{
						// 记录本次按键
						last_up_time = curr_time;
						is_last_down = false;

						control_message = MOUSE_OVER;
					}
				}
			}
		}
		else // 鼠标在控件之外
		{
			if(is_last_down)
			{
				if(IsMouseDown) // 鼠标按下
				{
					if(in_judge_const_down||in_judge_click||in_judge_double_click) // 正在判断事件
					{
						// 记录本次按键
						last_down_time = curr_time;
						is_last_down = true;

						control_message = MOUSE_OUT;
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

						control_message = MOUSE_CONST_DOWN_END;// 发送持续按下结束消息
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

						control_message = MOUSE_OUT;
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

				control_message = MOUSE_OUT;
			}
		}

		if(in_judge_click||in_judge_double_click||in_judge_const_down)
		{
			control_state = CONTROL_MOUSE_DOWN;
		}
		else
		{
			if (IsMouseOver(MouseX, MouseY))
			{
				control_state = CONTROL_MOUSE_OVER;
			}else
			{
				control_state = CONTROL_MOUSE_OUT;
			}
		}

#ifdef CodeDebug
		using namespace std;
		switch(control_message)
		{
		case MOUSE_OVER:
		case MOUSE_OUT:
		case FUNCTION_ERROR:break;

		case MOUSE_CONST_DOWN:
			cout<<control_name<<":MOUSE_CONST_DOWN"<<endl;
			break;
		case MOUSE_CONST_DOWN_END:
			cout<<control_name<<":MOUSE_CONST_DOWN_END"<<endl;
			break;
		case MOUSE_CLICK:
			cout<<control_name<<":MOUSE_CLICK"<<endl;
			break;
		case MOUSE_DOUBLE_CLICK:
			cout<<control_name<<":MOUSE_DOUBLE_CLICK"<<endl;
			break;
		}
#endif
		return *this;
	}

	BaseControl& BaseControl::ChangePosition(int X, int Y)
	{
		x = X;
		y = Y;
		return *this;
	}

	BaseControl& BaseControl::ChangeSize(int Width, int Height)
	{
		width = Width;
		height = Height;
		return *this;
	}

	void BaseControl::Show()
	{
		is_show = true;
	}

	void BaseControl::Hide()
	{
		is_show = false;
	}

	const char* BaseControl::GetName()
	{
		return control_name.c_str();
	}

	BaseControl& BaseControl::GetPosition(int &X, int &Y)
	{
		X = this->x;
		Y = this->y;
		return *this;
	}

	BaseControl& BaseControl::GetSize(int &Width, int &Height)
	{
		Width = this->width;
		Height = this->height;
		return *this;
	}

	int BaseControl::GetSizeWidth()
	{
		return width;
	}

	int BaseControl::GetSizeHeight()
	{
		return height;
	}

	bool BaseControl::IsShow()
	{
		return is_show;
	}

	ControlMessage BaseControl::GetMessage(void)
	{
		return control_message;
	}

	ControlState BaseControl::GetState(void)
	{
		return control_state;
	}

	bool BaseControl::IsMouseOver(int MouseX, int MouseY)
	{
		if((x <= MouseX) && (MouseX <= x + width) && (y <= MouseY) && (MouseY <= y + height))
			return true;
		else
			return false;
	}

	void BaseControl::Draw(void)
	{

	}

	void BaseControl::DrawFill(void)
	{

	}
}