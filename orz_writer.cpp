

#include "orz_writer.h"
#include "orz_log.h"
#include "orz_base_public_resource.h"

namespace Orz
{
	LineText::LineText():
	BaseUi(ELEMENT_TYPE_UI_ONE_LINE_WRITER, 0.0f)
	{
	}

	LineText& LineText::ChangeTextUTF8(BaseFont &Font, const char *Text)
	{
		line_text = Text;
		ReloadTexture(Font);
		return *this;
	}

	LineText& LineText::ChangeColor(BaseFont &Font, const Color &NewColor)
	{
		line_text_color = NewColor;
		ReloadTexture(Font);
		return *this;
	}

	void LineText::DoDraw(void)
	{
		int sw(0);
		image.GetSizeWidth(sw);
		if (sw > 0)
		{
			image.Render(x, y, (float)width/sw);
		}
	}

	void LineText::ReloadTexture(BaseFont &Font)
	{
		if (line_text.empty() == false)
		{
			// �õ���С
			Font.GetTextSizeUTF8(line_text.c_str(), width, height);

			// ����
			Font.CreateTextUTF8(line_text.c_str(), line_text_color);

			// ����Ȩת��
			image = Font.image;
		}

	}

	void LineText::DoChangeAlpha(unsigned char Alpha)
	{
		image.ChangeAlpha(Alpha);
	}

	void LineText::DoFree()
	{
		line_text.clear();
	}

	LineText& LineText::GetText(std::string& ReceiveText)
	{
		ReceiveText = line_text;
		return *this;
	}

    Writer::Writer():
	BaseUi(ELEMENT_TYPE_UI_WRITER, 0.0f)
    {
    }

    bool Writer::CreateWriter(const char *FontName, const char *Text, int FontSize, Color FontColor, Rect DestRect)
	{
		bool success(true);

		if(!font.CreateFont(FontName, FontSize))
		{
			error_out("Writer::CreateWriter - ��������ʧ��");
			success = false;
		}
		else
		{
			Free();
			text_texture_total_width = text_texture_total_height = 0;

			writer_text = Text;
			font.font_size = FontSize;
			writer_color = FontColor;

			x = DestRect.x;
			y = DestRect.y;
			width = DestRect.w;
			height = DestRect.h;
		}

		ReloadTexture();

		return success;
    }

    Writer& Writer::ChangeTextUTF8(const char *Text)
    {
		writer_text = Text;

        ReloadTexture();
        return *this;
	}

	Writer& Writer::ChangeTextColor(const Color &NewColor)
	{
		for(int i = 0; i < ChildrenSize(); i++)
		{
			if (Children(i).element_type == ELEMENT_TYPE_UI_ONE_LINE_WRITER)
			{
				((LineText&)Children(i)).ChangeColor(font, NewColor);
			}
		}
		return *this;
	}

    Writer& Writer::ChangeFontSize(int FontSize)
    {
        if(FontSize!=font.font_size)
		{
			font.font_size = FontSize;

			font.ChangeFontSize(font.font_size);

			// ������Ⱦ
			ReloadTexture();
		}
        return *this;
    }

	Writer& Writer::ChangeTextCenterPosition(float PrecentX, int PrecentY)
	{
		int render_x = 0;
		int render_y = height * PrecentY - text_texture_total_height/2;
		for (int i = 0; i < ChildrenSize(); i++)
		{
			if (Children(i).element_type == ELEMENT_TYPE_UI_ONE_LINE_WRITER)
			{
				render_x = width * PrecentX - Children(i).width/2;
				Children(i).ChangePosition(render_x, render_y);
				render_y += Children(i).height;
			}
		}
		return *this;
	}

	Writer& Writer::GetText(std::string& ReceiveText)
	{
		ReceiveText = writer_text;
		return *this;
	}

    void Writer::ReloadTexture()
    {
		// ��ֹ��ȹ�խ
		if(width < font.font_size)
			width = font.font_size;

        // ����ռ�
		Free();
        text_texture_total_width = text_texture_total_height = 0;

		// ʵ����
        //const char _array[] = {
        //        0xE4, 0xB8, 0x96,
        //        0xE7, 0x95, 0x8C,
        //        0x21,48,49,50,51,52,53,54,55,56,0}, *p = _array;

		const char *p = writer_text.c_str();

        int word_width = 0, word_height = 0, digit = 0;
        unsigned char magic_number;
        char c_temp[16] = {0} ;
        LineText *temp_line = new LineText;

		temp_line->ChangeColor(font, writer_color);

        // ���ֽڼ��,����������
        while(*p)
        {
            c_temp[0] = *p;
            digit = 0;
            magic_number = 0x80; // ��10000000

            // �������
            // 0xxxxxxx ASCII ��
            // 110xxxxx 10xxxxxx ��
			// 1110xxxx 10xxxxxx 10xxxxxx ��
            // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx ��
            // 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx ��
            // 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx ��
            while(magic_number & c_temp[0])
            {
                // ����һλ
                magic_number /=2 ;
                digit++;
            }

            // �� ASCII
            if(digit)
            {
				// ��λ
                for(int i = 1; i < digit;i++)
                {
                    c_temp[i] = p[i];
                }
                c_temp[digit] = 0;

                // �õ���С
                TTF_SizeUTF8(font.font, c_temp, &word_width, &word_height);
                if(word_height > temp_line->height)
                    temp_line->height = word_height;

                // �µ�һ��
                if( word_width + temp_line->width > width)
                {
					if (!temp_line->line_text.empty())
					{
						// ���һ��
						BaseElement::ChildrenPushBack(temp_line);

						// �޸��ı���С
						if(temp_line->width > text_texture_total_width)
							text_texture_total_width = temp_line->width;
						text_texture_total_height += temp_line->height;

						// �������������Ϊ 0
						temp_line = new LineText;
					}
                }
                else
                {
                    p += digit;
                    temp_line->line_text += c_temp;
                    temp_line->width += word_width;
                }
            }
            else // ASCII
            {
				c_temp[1] = 0;
				if ((!isprint(c_temp[0]))) // �����ַ����
				{
					if (c_temp[0] != '\n')
					{
						c_temp[0] = '?'; // ת��Ϊ�ɼ��ַ�
					}
				}

                // �õ���С
                TTF_SizeUTF8(font.font, c_temp, &word_width, &word_height);
                if(word_height > temp_line->height)
                    temp_line->height = word_height;

				// ����,�µ�һ��
                if(c_temp[0] == '\n')
                {
					if (!temp_line->line_text.empty())
					{
						// ���һ��
						temp_line->line_text[temp_line->line_text.size() - 1] = ' ';
						BaseElement::ChildrenPushBack(temp_line);

						// �޸��ı���С
						if(temp_line->width > text_texture_total_width)
							text_texture_total_width = temp_line->width;
						text_texture_total_height += temp_line->height;

						// ָ����һ���ַ����������������Ϊ0
						p++;
						temp_line = new LineText;
					}
                }
                else
                {
                    if( word_width + temp_line->width > width)
					{
						if (!temp_line->line_text.empty())
						{
							// �µ�һ��
							BaseElement::ChildrenPushBack(temp_line);

							// �޸��ı���С
							if(temp_line->width > text_texture_total_width)
								text_texture_total_width = temp_line->width;
							text_texture_total_height += temp_line->height;

							// �������������Ϊ 0
							temp_line = new LineText;
						}
                    }
                    else
                    {
                        p++;
                        temp_line->line_text += c_temp;
                        temp_line->width += word_width;
                    }
                }// end \n
            }// end ASCII
        }// end while

        // �������һ��Ҳ��ӵ�������
		if (!temp_line->line_text.empty())
		{
			BaseElement::ChildrenPushBack(temp_line);

			if(temp_line->width > text_texture_total_width)
				text_texture_total_width = temp_line->width;
			text_texture_total_height += temp_line->height;
		}
		this;
		int height=0;
        for(int i = 0; i < ChildrenSize(); i++)
        {
            // ��Ⱦÿһ���ı�
            font.CreateTextUTF8(((LineText&)Children(i)).line_text.c_str(),  ((LineText&)Children(i)).line_text_color);
			((LineText&)Children(i)).image = font.image;
			((LineText&)Children(i)).ChangePosition(0, height);
            height += ((LineText&)Children(i)).height;
		}
    }

    void Writer::DoDraw()
    {
		// �Զ�����,���ü�
		// �Զ�����,���вü�
		// �Զ�����,���Ҿ���
		// �Զ�����,����

		#ifdef CodeDebug
			// ���������� �ı���߿�
			Rect dest_rect = {x, y, width, height};
			device.display.DrawOutlineRect(RedColor, dest_rect);
		#endif
    }

	void Writer::DoChangeSize(int Width, int Height)
	{
		width = Width;
		height = Height;
		ReloadTexture();
	}

}







