
#include "orz_complex_control.h"
#include "orz_base_public_resource.h"

namespace Orz
{
	ControlText error_control_text;
	ControlButtonWithWriter error_control_button_with_writer;
	ControlScrollBar error_control_scroll_bar;
	ControlList error_control_list;

	//  文本控件------------------------------------------------------------------
	ControlText::ControlText()
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

		GetWriter().CreateWriter(FontName, Text, FontSize, TextColor, ControlRect);

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
		GetWriter().CreateWriter(FontName, Text, FontSize, TextColor, ControlRect);

		return true;
	}

	bool ControlButtonWithWriter::LoadControlButtonWithText(const char* PathName, int X, int Y, const Color &BackgroundColor, const char *FontName, int FontSize, const char* Text, const Color &TextColor)
	{
		bool succed = true;
		FILE *fp;
		fp = fopen(PathName, "r");
		Rect writer_rect = {X, Y};

		if(fp != NULL)
		{
			char buff[255];
			char var[255];

			// 读取类型
			fgets(buff, 254, fp);
			for(int i=0; buff[i]&&i<254; i++)
			{
				if(buff[i] == '\"')
				{
					char* p = buff+i+1;
					int j = 0;
					for(; p[j]&&p[j]!='\"';j++)
					{
						var[j] = p[j];
					}
					var[j] = 0;

					break;
				}
			}

			// 验证类型
			if (std::string("button") == var)
			{
				// 读取名称
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '\"')
					{
						char* p = buff+i+1;
						int j = 0;
						for(; p[j]&&p[j]!='\"';j++)
						{
							var[j] = p[j];
						}
						var[j] = 0;

						break;
					}
				}
				element_name = var;

				// 设置位置
				x = X;
				y = Y;

				// 读取位置
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%d", &width);
					}
				}
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%d", &height);
					}
				}

			}else
			{
				error_out("ControlButton::LoadControlButton - \""+string(PathName)+"\"类型出错! - 非button!类型控件");
				succed = false;
			}
		}
		else
		{
			error_out("ControlButton::LoadControlButton - 打开\""+string(PathName)+"\"文件出错!");
			succed = false;
		}

		ChangeBackgroundColor(BackgroundColor);

		// 创建写手
		writer_rect.w = width;
		writer_rect.h = height;
		GetWriter().CreateWriter(FontName, Text, FontSize, TextColor, writer_rect);

		fclose(fp);
		return succed;
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

	// 控件 - 列表--------------------------------------------------------------
	ControlList::ControlList()
	{
	}

	bool ControlList::CreateControlList(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize)
	{
		ChangePosition(ControlRect.x, ControlRect.y);
		ChangeSize(ControlRect.w, ControlRect.h);
		ChangeBackgroundColor(BackgroundColor);
		
		list_font.CreateFont(FontName, FontSize);

		return true;
	}

	float ControlList::GetPercent(void)
	{
		return control_percent;
	}

	ControlList& ControlList::ChangePercent(float Percent)
	{
		control_percent = Percent;
		return *this;
	}

	ControlList& ControlList::PushBack(const char *ControlName, const char* Text)
	{
		Color entry_text_background_color = {0,0,0,0};
		Color entry_text_color = {255,255,255,0};

		ControlText* new_control_text = new ControlText;
		Rect new_control_rect = {0, ChildrenSize()*entry_height, width, entry_height};
		new_control_text->CreateControlText(ControlName, new_control_rect, entry_text_background_color, list_font.font_name.c_str(), list_font.font_size, Text, entry_text_color);
		ChildrenPushBack(new_control_text);

		return *this;
	}


	ControlList& ControlList::Insert(int Position, const char *ControlName, const char* Text)
	{
		Color entry_text_background_color = {0,0,0,0};
		Color entry_text_color = {255,255,255,0};

		ControlText* new_control_text = new ControlText;
		Rect new_control_rect = {0, Position*entry_height, width, entry_height};
		new_control_text->CreateControlText(ControlName, new_control_rect, entry_text_background_color, list_font.font_name.c_str(), list_font.font_size, Text, entry_text_color);
		ChildrenInsert(Position, new_control_text);


		for(int i=Position+1; i < ChildrenSize(); ++i)
		{
			Children(i).ChangePosition(0, i * entry_height);
		}

		return *this;
	}
}