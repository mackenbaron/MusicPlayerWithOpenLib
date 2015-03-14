
#include "orz_complex_control.h"
#include "orz_base_public_resource.h"

namespace Orz
{
	ControlText error_control_text;
	ControlButtonWithWriter error_control_button_with_writer;
	ControlScrollBarWithColor error_control_scroll_bar_with_color;
	ControlList error_control_list;

	//  文本控件------------------------------------------------------------------
	ControlText::ControlText():
	BaseControl(ELEMENT_TYPE_UI_CONTROL_TEXT)
	{
		// 插入写手
		Writer* new_writer = new Writer;
		new_writer->ChangeDistance(WRITER_DISTANCE);
		ChildrenPushBack(new_writer);
	}

	bool ControlText::CreateControlText(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize, const char* Text, const Color &TextColor)
	{
		element_name = ControlName;

		ChangePosition(ControlRect.x, ControlRect.y);
		ChangeSize(ControlRect.w, ControlRect.h);
		ChangeBackgroundColor(BackgroundColor);

		Rect writer_rect = {0,0, ControlRect.w, ControlRect.h};
		GetWriter().CreateWriter("ControlText's Writer" , FontName, Text, FontSize, TextColor, writer_rect);

		return true;
	}

	Writer& ControlText::GetWriter(void)
	{
		if (ChildrenEmpty())
			return error_writer;

		if (Children(0).element_type == ELEMENT_TYPE_UI_WRITER)
			return ((Writer&)Children(0));
		else
			return error_writer;
	}

	void ControlText::DoDraw(const Rect& DrawRect)
	{
			if(element_alpha == 255)
			{
				device.display.DrawFillRect(GetBackgroundColor(), DrawRect);
			}
			else
			{
				device.display.DrawAlphaFillRect(GetBackgroundColor(), element_alpha, DrawRect);
			}
#ifdef CodeDebug
		// 画出线条来 文本外边框
			device.display.DrawOutlineRect(RedColor, DrawRect);
#endif
	}

	// 控件 - 按钮和文本 ----------------------------------------------
	ControlButtonWithWriter::ControlButtonWithWriter()
	{
		// 插入写手
		Writer* new_writer = new Writer;
		new_writer->ChangeDistance(WRITER_DISTANCE);
		ChildrenPushBack(new_writer);
	}

	bool ControlButtonWithWriter::CreateControlButtonWithWirter(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize, const char* Text, const Color &TextColor)
	{
		element_name = ControlName;

		ChangePosition(ControlRect.x, ControlRect.y);
		ChangeSize(ControlRect.w, ControlRect.h);
		ChangeBackgroundColor(BackgroundColor);

		// 创建写手
		GetWriter().CreateWriter("ControlButtonWithWriter's Wirter", FontName, Text, FontSize, TextColor, ControlRect);

		return true;
	}

	Writer& ControlButtonWithWriter::GetWriter(void)
	{
		if (ChildrenEmpty())
			return error_writer;

		if (Children(0).element_type == ELEMENT_TYPE_UI_WRITER)
			return ((Writer&)Children(0));
		else
			return error_writer;
	}

	// 滚动条控件-----------------------------------------------------------------
	ControlScrollBarWithColor::ControlScrollBarWithColor():
	BaseControl(ELEMENT_TYPE_UI_CONTROL_SCROLL_BAR),
		control_direct(CONTROL_DIRECT_UP_DOWN),
		control_percent(0.0f)
	{
		ControlButton* new_control_button = new ControlButton;
		ChildrenPushBack(new_control_button);
	}

	bool ControlScrollBarWithColor::CreateControlScrollBarWithColor(const char* Name, ControlDirect Direct, const Rect &ControlRect, const Color &BackgroundColorTrough, const Color &BackgroundColorBar)
	{
		element_name = Name;

		control_direct = Direct;

		ChangePosition(ControlRect.x, ControlRect.y);
		ChangeSize(ControlRect.w, ControlRect.h);
		ChangeBackgroundColor(BackgroundColorTrough);

		GetBar().ChangeBackgroundColor(BackgroundColorBar).ChangePosition(0,0).ChangeSize(width, height);

		return true;
	}

	ControlScrollBarWithColor& ControlScrollBarWithColor::ChangePercent(float Percent)
	{
		if (Percent < .0f)
			control_percent = 0.0;
		else if (Percent > 1.0f)
			control_percent = 1.0;
		else
			control_percent = Percent; 

		return *this;
	}

	ControlScrollBarWithColor& ControlScrollBarWithColor::ChangePercentAccrodToMousePosition(void)
	{
		int mx, my, bar_width, bar_height;
		GetMousePosition(mx, my);
		GetBar().GetSize(bar_width, bar_height);
		if (control_direct == CONTROL_DIRECT_UP_DOWN)
		{
			if (my < bar_height/2)
			{
				control_percent = 0.0f;
			}
			else if (my > height - bar_height/2)
			{
				control_percent = 1.0f;
			}
			else
			{
				control_percent = (float)(my-bar_height/2)/(height-bar_height);
			}
		} 
		else
		{
			if (mx < bar_width/2)
			{
				control_percent = 0.0f;
			}
			else if (mx > width - bar_width/2)
			{
				control_percent = 1.0f;
			}
			else
			{
				control_percent = (float)(mx-bar_width/2)/(width-bar_width);
			}
		}

		return *this;
	}

	ControlScrollBarWithColor& ControlScrollBarWithColor::ChangeDirect(ControlDirect Direct)
	{
		control_direct = Direct;
		return *this;
	}

	ControlScrollBarWithColor& ControlScrollBarWithColor::GetPercent(float &Percent)
	{
		Percent = control_percent;
		return *this;
	}

	ControlButton& ControlScrollBarWithColor::GetBar(void)
	{
		if (ChildrenEmpty())
			return error_control_button;

		if (Children(0).element_type == ELEMENT_TYPE_UI_CONTROL_BUTTON)
			return ((ControlButton&)Children(0));
		else
			return error_control_button;
	}

	void ControlScrollBarWithColor::DoDraw(const Rect& DrawRect)
	{
		if(element_alpha == 255)
		{
			device.display.DrawFillRect(GetBackgroundColor(), DrawRect);
		}
		else
		{
			device.display.DrawAlphaFillRect(GetBackgroundColor(), element_alpha, DrawRect);
		}

		// 设置 Bar 的位置
		int bar_width, bar_height;
		GetBar().GetSize(bar_width, bar_height);
		if (control_direct == CONTROL_DIRECT_UP_DOWN)
		{
			GetBar().ChangePosition((width - bar_width)/2, (height - bar_height)*control_percent);
		}
		else
		{
			GetBar().ChangePosition((width - bar_width)*control_percent, (height - bar_height)/2);
		}

	}

	// 控件 - 列表--------------------------------------------------------------
	ControlList::ControlList():
	control_percent(0.0f)
	{
	}

	bool ControlList::CreateControlList(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, int EntryHeight, const char *FontName, int FontSize)
	{
		element_name = ControlName;
		ChangePosition(ControlRect.x, ControlRect.y);
		ChangeSize(ControlRect.w, ControlRect.h);
		ChangeBackgroundColor(BackgroundColor);
		
		entry_height = EntryHeight;

		list_font.CreateFont(FontName, FontSize);

		return true;
	}

	ControlList& ControlList::GetPercent(float &Percent)
	{
		Percent = control_percent;
		return *this;
	}

	ControlList& ControlList::GetContentSize(int &Size)
	{
		Size = entry_height * ChildrenSize();
		return *this;
	}

	ControlList& ControlList::ChangePercent(float Percent)
	{
		control_percent = Percent;
		return *this;
	}

	ControlList& ControlList::PushBackControlText(const char *ControlName, const char* Text)
	{
		Color entry_text_background_color1 = {0x33, 0xa3, 0xdc,0};
		Color entry_text_background_color2 = {0x7b, 0xbf, 0xea,0};
		Color entry_text_color = {255,255,255,0};
		Rect new_control_rect = {0, 0, width, entry_height};

		//Writer* new_writer = new Writer;
		//new_writer->CreateWriter(ControlName, list_font.font_name.c_str(), Text, list_font.font_size, entry_text_color, new_control_rect);
		//ChildrenPushBack(new_writer);

		ControlText *new_control_text = new ControlText;
		if (ChildrenSize()%2)
		{
			new_control_text->CreateControlText(
				ControlName, new_control_rect,
				entry_text_background_color1,
				list_font.font_name.c_str(), list_font.font_size, Text, entry_text_color);
		}
		else
		{
			new_control_text->CreateControlText(
				ControlName, new_control_rect,
				entry_text_background_color2,
				list_font.font_name.c_str(), list_font.font_size, Text, entry_text_color);
		}
		new_control_text->ChangeToClip();
		new_control_text->parent = this;
		ChildrenPushBack(new_control_text);

		return *this;
	}


	ControlList& ControlList::Insert(int Position, const char *ControlName, const char* Text)
	{
		Color entry_text_background_color1 = {0x33, 0xa3, 0xdc,0};
		Color entry_text_background_color2 = {0x7b, 0xbf, 0xea,0};
		Color entry_text_color = {255,255,255,0};
		Rect new_control_rect = {0, 0, width, entry_height};

		//Writer* new_writer = new Writer;
		//Rect new_control_rect = {0, 0, width, entry_height};
		//new_writer->CreateWriter(ControlName, list_font.font_name.c_str(), Text, list_font.font_size, entry_text_color, new_control_rect);
		//ChildrenInsert(Position, new_writer);

		ControlText *new_control_text = new ControlText;
		if (ChildrenSize()%2)
		{
			new_control_text->CreateControlText(
				ControlName, new_control_rect,
				entry_text_background_color1,
				list_font.font_name.c_str(), list_font.font_size, Text, entry_text_color);
		}
		else
		{
			new_control_text->CreateControlText(
				ControlName, new_control_rect,
				entry_text_background_color2,
				list_font.font_name.c_str(), list_font.font_size, Text, entry_text_color);
		}
		new_control_text->ChangeToClip();
		new_control_text->parent = this;
		ChildrenInsert(Position, new_control_text);

		for(int i=Position+1; i < ChildrenSize(); ++i)
		{
			Children(i).ChangePosition(0, i * entry_height);
		}

		return *this;
	}

	void ControlList::DoDraw(const Rect& DrawRect)
	{
		if(element_alpha == 255)
		{
			device.display.DrawFillRect(GetBackgroundColor(), DrawRect);
		}
		else
		{
			device.display.DrawAlphaFillRect(GetBackgroundColor(), element_alpha, DrawRect);
		}

	}

	void ControlList::DoContact()
	{
		BaseControl::DoContact();

		ChangeToClip();

		int total_entry_height = ChildrenSize() * entry_height;
		if (total_entry_height > height)
		{
			for (int i = 0; i < ChildrenSize(); i++)
			{
				if (Children(i).element_type == ELEMENT_TYPE_UI_CONTROL_TEXT)
				{
					Children(i).ChangePosition(0, -(total_entry_height - height)*control_percent + i*entry_height);
				}
			}
		}
		else
		{
			for (int i = 0; i < ChildrenSize(); i++)
			{
				if (Children(i).element_type == ELEMENT_TYPE_UI_CONTROL_TEXT)
				{
					Children(i).ChangePosition(0, i*entry_height);
				}
			}
		}

	}

}