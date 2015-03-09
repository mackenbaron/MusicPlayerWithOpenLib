
#include "orz_base_element.h"
#include "orz_config.h"
#include "orz_base_public_resource.h"

#ifdef CodeDebug
	#include <iostream>
#endif

namespace Orz
{
	// ������
	ElementError error_element;

	// -----------------------
	BaseElement::BaseElement(ElementType Type, int X, int Y, int Width, int Height, float Distance):
	element_type(Type),
	x(X), y(Y), width(Width), height(Height),
	distance(Distance),
	is_show(true),
	element_alpha(255),
	element_render_style(ELEMENT_RENDER_STYLE_ADAPT),
	parent(NULL)
	{
		// ��Ҫ�������������Լ��ķ���,��������ɵ��ô��麯���Ĵ���!!!
	}

	BaseElement::~BaseElement()
	{

	}

	void BaseElement::DoFree(void)
	{
		for (int i = 0; i < children.size(); i++)
		{
			delete children[i];
			children[i] = NULL;
		}
		children.clear();
	}

	void BaseElement::DoChangePosition(int X, int Y)
	{
		x = X;
		y = Y;
	}

	void BaseElement::DoChangePositionAaccordToParent(float PrecentX, float PrecentY)
	{
		if (parent)
		{
			int parent_x, parent_y, parent_w, parent_h;
			parent->GetPosition(parent_x, parent_y).GetSize(parent_w, parent_h);
			x = (parent_w - width) * PrecentX + width;
			y = (parent_h - height) * PrecentY + height;
		}
	}

	void BaseElement::DoChangeSize(float Scale)
	{
		width *= Scale;
		height *= Scale;
	}

	void BaseElement::DoChangeSize(float ScaleWidth, float ScaleHeight)
	{
		width *= ScaleWidth;
		height *= ScaleHeight;
	}

	void BaseElement::DoChangeSize(int Width, int Height)
	{
		width = Width;
		height = Height;
	}

	void BaseElement::DoChangeAlpha(unsigned char Alpha)
	{
		element_alpha = Alpha;
	}

	void BaseElement::DoChangeRenderStyle(ElementRenderStyle RenderStyle)
	{
		element_render_style = RenderStyle;
	}

	void BaseElement::DoGetAbsoluteDrawRect(Rect &AbsoluteRect)
	{
		if (parent)
		{
			// �����������
			// ������μ�ȥ�ӽڵ�ľ���
			int this_x1 = parent->x, this_y1 = parent->y, 
				this_x2 = parent->x + parent->width,  this_y2 = parent->y + parent->height;
			int last_x1 = AbsoluteRect.x, last_y1 = AbsoluteRect.y,
				last_x2 = AbsoluteRect.x + AbsoluteRect.w, last_y2 = AbsoluteRect.y + AbsoluteRect.h;

			// ������������
			if (last_x1 < this_x1)
			{
				last_x1 = this_x1;
			}

			if (this_x2 < last_x2)
			{
				last_x2 = this_x2;
			}

			// Ҫ����ͼ����Ԫ��֮��
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
		else
		{
			// û�и��ڵ�,����ԭ��
		}
	}

	BaseElement* BaseElement::DoSearchChildren(const char *SearchName)
	{
		if (element_name == SearchName)
			return this;
		else
			return NULL;
	}

	BaseElement* BaseElement::DoSearchChildThatHaveContact(void)
	{
		if (element_state == ELEMENT_STATE_CONTACT)
		{
			return this;
		}
		else
		{
			return NULL;
		}
	}

	void BaseElement::DoGetMousePosition(int &MouseX, int &MouseY)
	{
		if (parent)
		{
			MouseX -= x;
			MouseY -= y;
		}
		else
		{
			platform.GetMousePosition(MouseX, MouseY);
		}
	}

	void BaseElement::FreeSub(BaseElement *element)
	{
		if (element)
		{
			// �ӽڵ�
			for (int i = 0; i < element->children.size(); i++)
			{
				element->FreeSub(children[i]);
			}

			// �Լ�
			element->DoFree();
		}
	}

	void BaseElement::ContactResetSub(BaseElement *element)
	{
		if (element)
		{
			// �Լ�
			element->DoContactReset();

			// �ӽڵ�
			for (int i = 0; i < element->children.size(); i++)
			{
				element->ContactResetSub(element->children[i]);
			}
		}
	}

	void BaseElement::ContactSub(BaseElement *element)
	{
		if (element)
		{
			// �ӽڵ�
			for (int i = 0; i < element->children.size(); i++)
			{
				element->ContactSub(element->children[i]);

				if (element->children[i]->GetState() == ELEMENT_STATE_CONTACT)
				{
					// �Ѿ��ҵ�����Ϣ�Ľڵ�,ֹͣ�ݹ�
					return;
				}				
			}

			// �Լ�
			element->DoContact();
		}
	}

	void BaseElement::ChangePositionSub(BaseElement *element, int X, int Y)
	{
		if (element)
		{
			// �Լ�
			element->DoChangePosition(X, Y);
		}
	}

	void BaseElement::ChangePositionAaccordToParent(BaseElement *element, float PrecentX, float PrecentY)
	{
		if (element)
		{
			// �Լ�
			element->DoChangePositionAaccordToParent(PrecentX, PrecentY);
		}
	}

	void BaseElement::ChangeSizeSub(BaseElement *element, float ScaleWidth, float ScaleHeight)
	{
		if (element)
		{
			// �Լ�
			element->DoChangeSize(ScaleWidth, ScaleHeight);

			// �ӽڵ�
			for (int i = 0; i < element->children.size(); i++)
			{
				element->ChangeSizeSub(element->children[i], ScaleWidth, ScaleHeight);
			}
		}
	}

	void BaseElement::ChangeSizeSub(BaseElement *element, float Scale)
	{
		if (element)
		{
			// �Լ�
			element->DoChangeSize(Scale);

			// �ӽڵ�
			for (int i = 0; i < element->children.size(); i++)
			{
				element->ChangeSizeSub(element->children[i], Scale);
			}
		}
	}

	void BaseElement::ChangeAlphaSub(BaseElement *element, uint8_t Alpha)
	{
		if (element)
		{
			// �Լ�
			element->DoChangeAlpha(Alpha);

			// �ӽڵ�
			for (int i = 0; i < element->children.size(); i++)
			{
				element->ChangeAlphaSub(element->children[i], Alpha);
			}
		}
	}

	void BaseElement::ChangeRenderStyleSub(BaseElement *element, ElementRenderStyle RenderStyle)
	{
		if (element)
		{
			// �Լ�
			element->DoChangeRenderStyle(RenderStyle);

			// �ӽڵ�
			for (int i = 0; i < element->children.size(); i++)
			{
				element->ChangeRenderStyleSub(element->children[i], RenderStyle);
			}
		}
	}

	void BaseElement::GetAbsoluteDrawRectSub(BaseElement *element, Rect &AbsoluteRect)
	{
		if (element)
		{
			// �Լ�
			element->DoGetAbsoluteDrawRect(AbsoluteRect);

			// ����
			if (element->parent)
			{
				element->GetAbsoluteDrawRectSub(element->parent, AbsoluteRect);
			}
		}
	}

	void BaseElement::GetMousePositionSub(BaseElement *element, int &MouseX, int &MouseY)
	{
		if (element)
		{
			// ����
			if (element->parent)
			{
				element->parent->GetMousePosition(MouseX, MouseY);
			}

			// ����
			element->DoGetMousePosition(MouseX, MouseY);
		}
	}

	void BaseElement::DrawSub(BaseElement *element)
	{
		if (element)
		{
			if (element->IsShow())
			{
				// �Լ�
				element->DoDraw();

				// �ӽڵ�
				for (int i = 0; i < element->children.size(); i++)
				{
					Rect absolute_draw_rect;
					element->GetAbsoluteDrawRect(absolute_draw_rect);
					device.display.SetViewport(absolute_draw_rect);
					element->DrawSub(element->children[i]);
					device.display.SetViewportToDefault();
				}
			}
		}
	}

	BaseElement* BaseElement::SearchChildrenSub(BaseElement *element, const char *SearchName)
	{
		BaseElement* temp = NULL;

		if (element)
		{
			// �Լ�
			temp = element->DoSearchChildren(SearchName);

			if (temp == NULL)
			{
				// ���������ӽڵ�
				for (int i = 0; i < element->children.size(); i++)
				{
					temp = element->SearchChildrenSub(element->children[i], SearchName);
					if (temp != NULL)
					{
						break;
					}
				}
			}
		}

		return temp;
	}

	BaseElement* BaseElement::SearchChildThatHaveContactSub(BaseElement *element)
	{
		BaseElement* temp;
		if (element)
		{
			// �Լ�
			temp = element->DoSearchChildThatHaveContact();

			if (temp == NULL)
			{
				for (int i = 0; i < element->children.size(); i++)
				{
					temp = element->SearchChildThatHaveContactSub(element->children[i]);
					if (temp != NULL)
					{
						break;
					}
				}
			}
		}
		return this;
	}

	BaseElement& BaseElement::Free(void)
	{
		FreeSub(this);
		return *this;
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

	BaseElement& BaseElement::Contact()
	{
		ContactSub(this);
		return *this;
	}

	BaseElement& BaseElement::ChangePosition(int X, int Y)
	{
		ChangePositionSub(this, X, Y);
		return *this;
	}

	BaseElement& BaseElement::ChangePositionAaccordToParent(float PrecentX, float PrecentY)
	{
		ChangePositionAaccordToParent(this, PrecentX, PrecentY);
		return *this;
	}

	BaseElement& BaseElement::ChangeSize(float ScaleWidth, float ScaleHeight)
	{
		ChangeSizeSub(this, ScaleWidth, ScaleHeight);
		return *this;
	}

	BaseElement& BaseElement::ChangeSize(int Width, int Height)
	{
		DoChangeSize(Width, Height);

		return *this;
	}

	BaseElement& BaseElement::ChangeSize(float Scale)
	{
		ChangeSizeSub(this, Scale);
		return *this;
	}

	BaseElement& BaseElement::ChangeDistance(float Distance)
	{
		distance = Distance;
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

	// ��ȡԪ������------------------------------------------------------
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

	BaseElement& BaseElement::GetAbsoluteDrawRect(Rect &AbsoluteRect)
	{
		if (this)
		{
			AbsoluteRect.x = x;
			AbsoluteRect.y = y;
			AbsoluteRect.w = width;
			AbsoluteRect.h = height;
		}
		GetAbsoluteDrawRectSub(this, AbsoluteRect);
	
		return *this;
	}

	BaseElement& BaseElement::GetMousePosition(int &MouseX, int &MouseY)
	{
		GetMousePositionSub(this, MouseX, MouseY);
		return *this;
	}

	bool BaseElement::IsShow()
	{
		return is_show;
	}

	bool BaseElement::ChildrenEmpty(void)
	{
		return children.empty();
	}

	int BaseElement::ChildrenSize()
	{
		return children.size();
	}

	BaseElement& BaseElement::Children(int Position)
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

	BaseElement& BaseElement::SearchChildren(const char *SearchName)
	{
		BaseElement *temp = SearchChildrenSub(this, SearchName);

		if (temp != NULL)
			return *this;
		else
		{
#ifdef CodeDebug
			error_out("û���ҵ�"+std::string(SearchName));
#endif
			return error_element;
		}
	}

	BaseElement& BaseElement::SearchChildThatHaveContact(void)
	{
		BaseElement *temp = SearchChildThatHaveContactSub(this);

		if (temp != NULL)
			return *this;
		else
			return error_element;
	}

	BaseElement& BaseElement::ChildrenPushBack(BaseElement* NewChildElement)
	{
		int i(0);

		for (i = 0; i < children.size(); i++)
		{
			if (NewChildElement->distance < children[i]->distance)
				break;
		}
		NewChildElement->parent = this;
		children.insert(children.begin() + i, NewChildElement);

		return *this;
	}

	BaseElement& BaseElement::ChildrenInsert(int Position, BaseElement* NewChildElement)
	{
		if ((0 <= Position)&&(Position <= ChildrenSize()))
		{
			NewChildElement->parent = this;
			children.insert(children.begin() + Position, NewChildElement);
		}
		return *this;
	}

	BaseElement& BaseElement::ChildrenErease(int Position)
	{
		if (0 <= Position && Position < children.size())
		{
			children[Position]->Free();
			delete children[Position];

			children.erase(children.begin() + Position);
		}

		return *this;
	}

}