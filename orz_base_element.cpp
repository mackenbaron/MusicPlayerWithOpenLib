
#include "orz_base_element.h"
#include "orz_config.h"
#include "orz_base_private_resource.h"

#ifdef CodeDebug
#include <iostream>
#endif

namespace Orz
{
	BaseElement::BaseElement(ElementType Type, int X, int Y, int Width, int Height, float Distance):
	element_type(Type),
	x(X), y(Y), width(Width), height(Height),
	distance(Distance),
	is_show(true),
	element_alpha(255),
	last_down_time(0), last_up_time(0),
	is_last_down(0),
	in_judge_click(0), in_judge_double_click(0), in_judge_const_down(0),
	parent(NULL)
	{
		ContactReset();
	}

	BaseElement::~BaseElement()
	{

	}

	void BaseElement::DoContactReset(void)
	{
		element_message = ELEMENT_MESSAGE_MOUSE_OUT;
		element_state = ELEMENT_STATE_MOUSE_OUT;
		is_mouse_over = false;

		last_down_time = 0, last_up_time = 0;
		is_last_down = false;
		in_judge_click = in_judge_double_click = in_judge_const_down = false;
		curr_time = 0, delta_time = 0;
	}

	void BaseElement::DoContact(int MouseX, int MouseY, bool IsMouseDown)
	{
		if (is_show==false)
		{
			DoContactReset();
			return;
		}

		// 测试是否在元素内
		if ( 0 <= MouseX && MouseX < width && 0 <= MouseY && MouseY <= height)
			is_mouse_over = true;
		else
			is_mouse_over = false;

		curr_time = SDL_GetTicks();
		if(is_mouse_over) // 鼠标在控件之内
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

						element_message = ELEMENT_MESSAGE_MOUSE_CONST_DOWN;
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

							element_message = ELEMENT_MESSAGE_MOUSE_CONST_DOWN;
						}
						else // 还是在判断单击
						{
							// 记录本次按键
							last_down_time = curr_time;
							is_last_down = true;

							element_message = ELEMENT_MESSAGE_MOUSE_OVER;
						}

					}
					else // 正在判断"双击"
					{
						// 记录本次按键
						last_down_time = curr_time;
						is_last_down = true;

						element_message = ELEMENT_MESSAGE_MOUSE_OVER;
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

						element_message = ELEMENT_MESSAGE_MOUSE_OVER;
					}
					else // 判断单击
					{
						// 进入判断"单击"状态
						in_judge_click = true;

						// 记录本次按键
						last_down_time = curr_time;
						is_last_down = true;

						element_message = ELEMENT_MESSAGE_MOUSE_OVER;
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

						element_message = ELEMENT_MESSAGE_MOUSE_CONST_DOWN_END;// 发送持续按下结束消息
					}
					else if(in_judge_double_click)// 发送"双击"消息
					{
						// 退出判断状态
						in_judge_double_click = false;

						// 记录本次按键
						last_up_time = curr_time;
						is_last_down = false;

						element_message = ELEMENT_MESSAGE_MOUSE_DOUBLE_CLICK;
					}
					else // 判断"单击"/"双击"
					{
						in_judge_double_click = true;

						// 记录本次按键
						last_up_time = curr_time;
						is_last_down = false;

						element_message = ELEMENT_MESSAGE_MOUSE_OVER;
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

							element_message = ELEMENT_MESSAGE_MOUSE_CLICK;
						}
						else
						{
							// 记录本次按键
							last_up_time = curr_time;
							is_last_down = false;

							element_message = ELEMENT_MESSAGE_MOUSE_OVER;
						}
					}
					else // 什么也没发生
					{
						// 记录本次按键
						last_up_time = curr_time;
						is_last_down = false;

						element_message = ELEMENT_MESSAGE_MOUSE_OVER;
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

						element_message = ELEMENT_MESSAGE_MOUSE_OUT;
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

						element_message = ELEMENT_MESSAGE_MOUSE_CONST_DOWN_END;// 发送持续按下结束消息
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

						element_message = ELEMENT_MESSAGE_MOUSE_OUT;
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

				element_message = ELEMENT_MESSAGE_MOUSE_OUT;
			}
		}

		if(in_judge_click||in_judge_double_click||in_judge_const_down)
		{
			element_state = ELEMENT_STATE_MOUSE_DOWN;
		}
		else
		{
			if (is_mouse_over)
			{
				element_state = ELEMENT_STATE_MOUSE_OVER;
			}
			else
			{
				element_state = ELEMENT_STATE_MOUSE_OUT;
			}
		}

	#ifdef CodeDebug
		using namespace std;
		switch(element_message)
		{
		case ELEMENT_MESSAGE_MOUSE_OVER:
		case ELEMENT_MESSAGE_MOUSE_OUT:
			break;
		case ELEMENT_MESSAGE_FUNCTION_ERROR:
			cout<<element_name<<":ERROR!"<<endl;
			break;

		case ELEMENT_MESSAGE_MOUSE_CONST_DOWN:
			cout<<element_name<<":MOUSE_CONST_DOWN"<<endl;
			break;
		case ELEMENT_MESSAGE_MOUSE_CONST_DOWN_END:
			cout<<element_name<<":MOUSE_CONST_DOWN_END"<<endl;
			break;
		case ELEMENT_MESSAGE_MOUSE_CLICK:
			cout<<element_name<<":MOUSE_CLICK"<<endl;
			break;
		case ELEMENT_MESSAGE_MOUSE_DOUBLE_CLICK:
			cout<<element_name<<":MOUSE_DOUBLE_CLICK"<<endl;
			break;
		}
	#endif
	}

	void BaseElement::DoChangePosition(int X, int Y)
	{
		x = X;
		y = Y;
	}

	void BaseElement::DoChangeSize(int Width, int Height)
	{
		width = Width;
		height = Height;
	}

	void BaseElement::DoChangeAlpha(uint8_t Alpha)
	{
		element_alpha = Alpha;
	}

	void BaseElement::DoChangeRenderStyle(ElementRenderStyle RenderStyle)
	{
		element_render_style = RenderStyle;
	}

	void BaseElement::DoDraw(void)
	{

	}

	void BaseElement::DoGetAbsoluteParentDrawRect(Rect &AbsoluteRect)
	{
		// 两个矩形相减
		// 这个矩形减去子节点的矩形
		int this_x1 = x, this_y1 = y, this_x2 = x + width,  this_y2 = y + height;
		int last_x1 = AbsoluteRect.x, last_y1 = AbsoluteRect.y,
			last_x2 = AbsoluteRect.x + AbsoluteRect.w, last_y2 = AbsoluteRect.y + AbsoluteRect.h;

		// 处理左右两边
		if (last_x1 < this_x1)
		{
			last_x1 = this_x1;
		}

		if (this_x2 < last_x2)
		{
			last_x2 = this_x2;
		}

		// 要绘制图形在元素之外
		if (last_x2 < last_x1)
		{
			AbsoluteRect.w = 0;
			AbsoluteRect.h = 0;
		}
		else
		{
			AbsoluteRect.x = last_x1;
			AbsoluteRect.w = last_x2 - last_x1;

			if (last_y1 < this_y1)
			{
				last_y1 = this_y1;
			}

			if (this_y2 < last_y2)
			{
				last_y2 = this_y2;
			}

			if (last_y2 < last_y1)
			{
				AbsoluteRect.w = 0;
				AbsoluteRect.h = 0;
			}
			else
			{
				AbsoluteRect.y = last_y1;
				AbsoluteRect.h = last_y2 - last_y1;
			}
		}
	}

	BaseElement* BaseElement::DoGetChildElement(const char *SearchName)
	{
		if (element_name == SearchName)
			return this;
		else
			return NULL;
	}

	void BaseElement::ContactResetSub(BaseElement *element)
	{
		if (element)
		{
			// 自己
			element->DoContactReset();

			// 子节点
			for (int i = 0; i < children.size(); i++)
			{
				children[i]->ContactResetSub(children[i]);
			}
		}
	}

	void BaseElement::ContactSub(BaseElement *element, int MouseX, int MouseY, bool IsMouseDown)
	{
		if (element)
		{
			// 子节点
			for (int i = 0; i < children.size(); i++)
			{
				children[i]->ContactSub(children[i], MouseX - x, MouseY - y, IsMouseDown);
				if (children[i]->GetState() != ELEMENT_STATE_MOUSE_OVER)
				{
					// 已经找到有消息的节点,停止递归
					return;
				}
			}

			// 自己
			element->DoContact(MouseX - x, MouseY - y, IsMouseDown);
		}
	}

	void BaseElement::ChangePositionSub(BaseElement *element, int X, int Y)
	{
		if (element)
		{
			// 自己
			element->DoChangePosition(X, Y);
		}
	}

	void BaseElement::ChangeSizeSub(BaseElement *element, int Width, int Height)
	{
		if (element)
		{
			// 自己
			float scale_w = (float)width/ Width,scale_h = (float)height/Height;
			element->DoChangeSize(Width, Height);

			// 子节点
			int ew, eh;
			for (int i = 0; i < children.size(); i++)
			{
				children[i]->GetSize(ew, eh).ChangeSizeSub(children[i], Width*scale_w, Height*scale_h);
			}
		}
	}

	void BaseElement::ChangeAlphaSub(BaseElement *element, uint8_t Alpha)
	{
		if (element)
		{
			// 自己
			element->DoChangeAlpha(Alpha);

			// 子节点
			for (int i = 0; i < children.size(); i++)
			{
				children[i]->ChangeAlphaSub(children[i], Alpha);
			}
		}
	}

	void BaseElement::ChangeRenderStyleSub(BaseElement *element, ElementRenderStyle RenderStyle)
	{
		if (element)
		{
			// 自己
			element->DoChangeRenderStyle(RenderStyle);

			// 子节点
			for (int i = 0; i < children.size(); i++)
			{
				children[i]->ChangeRenderStyleSub(children[i], RenderStyle);
			}
		}
	}

	void BaseElement::GetAbsoluteParentDrawRectSub(BaseElement *element, Rect &AbsoluteRect)
	{
		if (element)
		{
			element->DoGetAbsoluteParentDrawRect(AbsoluteRect);
			GetAbsoluteParentDrawRectSub(element->parent, AbsoluteRect);
		}
	}

	void BaseElement::DrawSub(BaseElement *element)
	{
		if (element)
		{
			// 自己
			element->DoDraw();

			// 子节点
			for (int i = 0; i < children.size(); i++)
			{
				children[i]->DrawSub(children[i]);
			}
		}
	}

	BaseElement* BaseElement::GetChildElementSub(BaseElement *element, const char *SearchName)
	{
		BaseElement* temp = NULL;

		if (element)
		{
			// 自己
			temp = element->DoGetChildElement(SearchName);

			if (temp == NULL)
			{
				// 继续搜索子节点
				for (int i = 0; i < children.size(); i++)
				{
					temp = children[i]->GetChildElementSub(children[i], SearchName);
					if (temp != NULL)
					{
						break;
					}
				}
			}
		}

		return temp;
	}

	BaseElement& BaseElement::Show()
	{
		is_show = true;
		return *this;
	}

	BaseElement& BaseElement::Hide()
	{
		is_show = false;
		return *this;
	}

	BaseElement& BaseElement::Draw(void)
	{
		DrawSub(this);
		return *this;
	}

	BaseElement& BaseElement::ContactReset(void)
	{
		ContactResetSub(this);
		return *this;
	}

	BaseElement& BaseElement::Contact(int MouseX, int MouseY, bool IsMouseDown)
	{
		ContactSub(this, MouseX, MouseY, IsMouseDown);
		return *this;
	}

	BaseElement& BaseElement::ChangePosition(int X, int Y)
	{
		ChangePositionSub(this, X, Y);
		return *this;
	}

	BaseElement& BaseElement::ChangeSize(int Width, int Height)
	{
		ChangeSizeSub(this, Width, Height);
		return *this;
	}

	BaseElement& BaseElement::ChangeAlpha(uint8_t Alpha)
	{
		ChangeAlphaSub(this, Alpha);
		return *this;
	}

	BaseElement& BaseElement::ChangeRenderStyle(ElementRenderStyle RenderStyle)
	{
		ChangeRenderStyleSub(this, RenderStyle);
		return *this;
	}

	// 获取元素属性------------------------------------------------------
	const std::string& BaseElement::GetName()
	{
		return element_name;
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

	BaseElement& BaseElement::GetSizeWidth(int &Width)
	{
		Width = this->width;
		return *this;
	}

	int BaseElement::GetSizeHeight()
	{
		return height;
	}

	BaseElement& BaseElement::GetSizeHeight(int &Height)
	{
		Height = this->height;
		return *this;
	}

	ElementMessage BaseElement::GetMessage(void)
	{
		return element_message;
	}

	ElementState BaseElement::GetState(void)
	{
		return element_state;
	}

	BaseElement& BaseElement::GetAbsolutePosition(int &X, int &Y)
	{
		if (this)
		{
			BaseElement *temp = parent;
			X = x;
			Y = y;
			int temp_x, temp_y;
			while (temp)
			{
				temp->GetPosition(temp_x, temp_y);
				X += temp_x;
				Y += temp_y;
				temp = temp->parent;
			}
		}

		return *this;
	}

	BaseElement& BaseElement::GetAbsoluteParentDrawRect(Rect &AbsoluteRect)
	{
		if (parent)
		{
			AbsoluteRect.x = parent->x;
			AbsoluteRect.y = parent->y;
			AbsoluteRect.w = parent->width;
			AbsoluteRect.h = parent->height;

			if (parent->parent)
			{
				GetAbsoluteParentDrawRectSub(parent, AbsoluteRect);
			}
		}

		return *this;
	}

	bool BaseElement::IsShow()
	{
		return is_show;
	}

	BaseElement& BaseElement::GetChildElement(int Position)
	{
		if (0 <= Position && Position < children.size())
		{
			return *children[Position];
		}
		else
		{
			return error_element;
		}
	}

	BaseElement& BaseElement::GetChildElement(const char *SearchName)
	{
		BaseElement *temp = GetChildElementSub(this, SearchName);

		if (temp != NULL)
			return *this;
		else
			return error_element;
	}

	int BaseElement::GetChildrenSize()
	{
		return children.size();
	}

	BaseElement& BaseElement::AddChildElement(BaseElement* NewChildElement)
	{
		int i(0);

		for (i = 0; i < children.size(); i++)
		{
			if (NewChildElement->distance < children[i]->distance)
				break;
		}

		children.insert(children.begin() + i, NewChildElement);

		return *this;
	}

}