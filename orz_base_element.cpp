
#include "orz_base_element.h"

namespace Orz
{
	BaseElement::BaseElement(int X, int Y, int Width, int Height):
	x(X), y(Y), width(Width), height(Height),
	is_show(true),
	last_down_time(0), last_up_time(0),
	is_last_down(0),
	in_judge_click(0), in_judge_double_click(0), in_judge_const_down(0)
	{

	}

	BaseElement::~BaseElement()
	{

	}

	BaseElement& BaseElement::Contact(int MouseX, int MouseY, bool IsMouseDown)
	{
		curr_time = SDL_GetTicks();
		if(IsMouseOver(MouseX, MouseY)) // ����ڿؼ�֮��
		{
			if(IsMouseDown)
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
				if(IsMouseDown) // ��갴��
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

		if(in_judge_click||in_judge_double_click||in_judge_const_down)
		{
			control_state = CONTROL_STATE_MOUSE_DOWN;
		}
		else
		{
			if (IsMouseOver(MouseX, MouseY))
			{
				control_state = CONTROL_STATE_MOUSE_OVER;
			}else
			{
				control_state = CONTROL_STATE_MOUSE_OUT;
			}
		}

	#ifdef CodeDebug
		using namespace std;
		switch(control_message)
		{
		case ELEMENT_MESSAGE_MOUSE_OVER:
		case ELEMENT_MESSAGE_MOUSE_OUT:
		case ELEMENT_MESSAGE_FUNCTION_ERROR:break;

		case ELEMENT_MESSAGE_MOUSE_CONST_DOWN:
			cout<<control_name<<":MOUSE_CONST_DOWN"<<endl;
			break;
		case ELEMENT_MESSAGE_MOUSE_CONST_DOWN_END:
			cout<<control_name<<":MOUSE_CONST_DOWN_END"<<endl;
			break;
		case ELEMENT_MESSAGE_MOUSE_CLICK:
			cout<<control_name<<":MOUSE_CLICK"<<endl;
			break;
		case ELEMENT_MESSAGE_MOUSE_DOUBLE_CLICK:
			cout<<control_name<<":MOUSE_DOUBLE_CLICK"<<endl;
			break;
		}
	#endif
		return *this;
	}

	BaseElement& BaseElement::ChangePosition(int X, int Y)
	{
		x = X;
		y = Y;
		return *this;
	}

	BaseElement& BaseElement::ChangeSize(int Width, int Height)
	{
		width = Width;
		height = Height;
		return *this;
	}

	void BaseElement::Show()
	{
		is_show = true;
	}

	void BaseElement::Hide()
	{
		is_show = false;
	}

	const std::string& BaseElement::GetName()
	{
		return control_name;
	}

	BaseElement& BaseElement::GetPosition(int &X, int &Y)
	{
		X = this->x;
		Y = this->y;
		return *this;
	}

	BaseElement& BaseElement::GetSize(int &Width, int &Height)
	{
		Width = this->width;
		Height = this->height;
		return *this;
	}

	int BaseElement::GetSizeWidth()
	{
		return width;
	}

	int BaseElement::GetSizeHeight()
	{
		return height;
	}

	bool BaseElement::IsShow()
	{
		return is_show;
	}

	ControlMessage BaseElement::GetMessage(void)
	{
		return control_message;
	}

	ControlState BaseElement::GetState(void)
	{
		return control_state;
	}

	bool BaseElement::IsMouseOver(int MouseX, int MouseY)
	{
		if((x <= MouseX) && (MouseX <= x + width) && (y <= MouseY) && (MouseY <= y + height))
			return true;
		else
			return false;
	}

	void BaseElement::Draw(void)
	{

	}

	void BaseElement::DrawFill(void)
	{

	}
}