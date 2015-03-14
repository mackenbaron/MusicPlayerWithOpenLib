
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
	deep_distance(Distance),
	is_show(true),
	is_clip(false),
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

	void BaseElement::DoGetAbsoluteClipDrawRect(Rect &AbsoluteRect)
	{
		// �����������
		// �˽ڵ��ȥ���������ľ���

		if (AbsoluteRect.w == 0 || AbsoluteRect.h == 0)
		{
			return;
		}

		int this_x1 = x,
			this_y1 = y,
			this_x2 = x + width,
			this_y2 = y + height;

		int last_x1 = AbsoluteRect.x + x,
			last_y1 = AbsoluteRect.y + y,
			last_x2 = AbsoluteRect.x + x + AbsoluteRect.w,
			last_y2 = AbsoluteRect.y + y + AbsoluteRect.h;

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
		if (last_x2 <= last_x1)
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

			if (last_y2 <= last_y1)
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
				if (element->children[i]->GetElementState() == ELEMENT_STATE_CONTACT)
				{
					// �Ѿ��ҵ�����Ϣ�Ľڵ�,ֹͣ�ݹ�
					return;
				}
			}

			// �Լ�
			element->DoContact();

			//for (int i = element->children.size() - 1; i >= 0; i--)
			//{
			//	element->ContactSub(element->children[i]);
			//	if (element->children[i]->GetElementState() == ELEMENT_STATE_CONTACT)
			//	{
			//		// �Ѿ��ҵ�����Ϣ�Ľڵ�,ֹͣ�ݹ�
			//		return;
			//	}
			//}

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

	void BaseElement::GetAbsoluteClipDrawRectSub(BaseElement *element, Rect &AbsoluteRect)
	{
		if (element)
		{
			AbsoluteRect.x = element->x;
			AbsoluteRect.y = element->y;
			AbsoluteRect.w = element->width;
			AbsoluteRect.h = element->height;

			BaseElement *temp = element->parent;
			while (temp)
			{
				temp->DoGetAbsoluteClipDrawRect(AbsoluteRect);
				temp = temp->parent;
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

	void BaseElement::DrawSub(BaseElement *element, Rect& DrawRect)
	{
		if (element)
		{
			if (element->IsShow())
			{
				DrawRect.x += element->x;
				DrawRect.y += element->y;
				DrawRect.w = element->width;
				DrawRect.h = element->height;

				if (element->IsClip())
				{
					Rect clip_rect;
					element->GetAbsoluteClipDrawRect(clip_rect);
					device.display.SetClip(clip_rect);
					
					if (DrawRect.w > 0 && DrawRect.h >0)
					{
						// �Լ�
						element->DoDraw(DrawRect);

						//// �ӽڵ�
						//for (int i = 0; i < element->children.size(); i++)
						//{
						//	Rect SubDrawRect = DrawRect;
						//	element->DrawSub(element->children[i], SubDrawRect);
						//}

						// �ӽڵ�
						for (int i = element->children.size() - 1; i >= 0 ; i--)
						{
							Rect sub_rect = {DrawRect.x + element->children[i]->x,
							DrawRect.y + element->children[i]->y,
							element->children[i]->width,
							element->children[i]->height};

							// �ӽڵ㲻�ھ�����
							if (sub_rect.x + sub_rect.w <= DrawRect.x
								||sub_rect.y + sub_rect.h <= DrawRect.y
								||DrawRect.x + element->width <= sub_rect.x
								||DrawRect.y + element->height <= sub_rect.y
								)
								continue;

							Rect sub_real_draw_rect = DrawRect;
							element->DrawSub(element->children[i], sub_real_draw_rect);
						}
					}
					device.display.SetClipToNull();
#ifdef CodeDebug
					// ������߿�������
					device.display.DrawOutlineRect(OriginColor, clip_rect);
					//Rect in_rect = {clip_rect.x+1, clip_rect.y+1, clip_rect.w+1, clip_rect.h+1};
					//device.display.DrawOutlineRect(OriginColor, in_rect);
#endif
				}
				else
				{
					// �Լ�
					element->DoDraw(DrawRect);

					//// �ӽڵ�
					//for (int i = 0; i < element->children.size(); i++)
					//{
					//	Rect SubDrawRect = DrawRect;
					//	element->DrawSub(element->children[i], SubDrawRect);
					//}

					// �ӽڵ�
					for (int i = element->children.size() - 1; i >= 0 ; i--)
					{
						Rect SubDrawRect = DrawRect;
						element->DrawSub(element->children[i], SubDrawRect);
					}

#ifdef CodeDebug
					// ������߿�������
					device.display.DrawOutlineRect(GreenColor, DrawRect);
#endif
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
		BaseElement* temp = NULL;
		if (element)
		{
			for (int i = 0; i < element->children.size(); i++)
			{
				temp = element->SearchChildThatHaveContactSub(element->children[i]);
				if (temp != NULL)
				{
					break;
				}
			}

			// �Լ�
			if (temp == NULL)
			{
				temp = element->DoSearchChildThatHaveContact();
			}
		}
		return temp;
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
		Rect AbsoluteRect = {x, y, width, height};
		DrawSub(this, AbsoluteRect);
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
		if (this)
		{
			DoChangeSize(Width, Height);
		}

		return *this;
	}

	BaseElement& BaseElement::ChangeSize(float Scale)
	{
		ChangeSizeSub(this, Scale);
		return *this;
	}

	BaseElement& BaseElement::ChangeDistance(float Distance)
	{
		if (this)
		{
			deep_distance = Distance;

			if (parent)
			{
				for (int i = 0; i < parent->children.size(); i++)
				{

					if (parent->children[i] == this)
					{
						BaseElement *temp_parent = parent;
						temp_parent->ChildrenErease(i);
						temp_parent->ChildrenPushBack(this);
						break;
					}
				}
			}
		}
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

	ElementMessage BaseElement::GetElementMessage(void)
	{
		return element_message;
	}

	ElementState BaseElement::GetElementState(void)
	{
		return element_state;
	}

	BaseElement& BaseElement::GetAbsolutePosition(int &X, int &Y)
	{
		if (this)
		{
			X = this->x;
			Y = this->y;

			BaseElement *temp = this->parent;
			while (temp)
			{
				X += temp->x;
				Y += temp->y;
				temp = temp->parent;
			}
		}

		return *this;
	}

	BaseElement& BaseElement::GetAbsoluteClipDrawRect(Rect &AbsoluteRect)
	{
		GetAbsoluteClipDrawRectSub(this, AbsoluteRect);
	
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
			return *temp;
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
			return *temp;
		else
			return error_element;
	}

	BaseElement& BaseElement::ChildrenPushBack(BaseElement* NewChildElement)
	{
		int i(0);

		for (i = 0; i < children.size(); i++)
		{
			if (NewChildElement->deep_distance > children[i]->deep_distance)
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
			children[Position]->parent = NULL;
			children.erase(children.begin() + Position);
		}

		return *this;
	}

	bool BaseElement::IsClip()
	{
		return is_clip;
	}

	BaseElement& BaseElement::ChangeToClip()
	{
		if (this)
		{
			this->is_clip = true;
		}
		return *this;
	}

	BaseElement& BaseElement::ChangeToNoClip()
	{
		if (this)
		{
			this->is_clip = false;
		}
		return *this;
	}

}