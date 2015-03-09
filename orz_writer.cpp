

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
			// 得到大小
			Font.GetTextSizeUTF8(line_text.c_str(), width, height);

			// 绘制
			Font.CreateTextUTF8(line_text.c_str(), line_text_color);

			// 控制权转移
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
			error_out("Writer::CreateWriter - 创建字体失败");
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

			// 重新渲染
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
		// 防止宽度过窄
		if(width < font.font_size)
			width = font.font_size;

        // 清除空间
		Free();
        text_texture_total_width = text_texture_total_height = 0;

		// 实验用
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

        // 逐字节检查,并计算行数
        while(*p)
        {
            c_temp[0] = *p;
            digit = 0;
            magic_number = 0x80; // 即10000000

            // 检查类型
            // 0xxxxxxx ASCII 型
            // 110xxxxx 10xxxxxx 型
			// 1110xxxx 10xxxxxx 10xxxxxx 型
            // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx 型
            // 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 型
            // 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 型
            while(magic_number & c_temp[0])
            {
                // 后移一位
                magic_number /=2 ;
                digit++;
            }

            // 非 ASCII
            if(digit)
            {
				// 补位
                for(int i = 1; i < digit;i++)
                {
                    c_temp[i] = p[i];
                }
                c_temp[digit] = 0;

                // 得到大小
                TTF_SizeUTF8(font.font, c_temp, &word_width, &word_height);
                if(word_height > temp_line->height)
                    temp_line->height = word_height;

                // 新的一行
                if( word_width + temp_line->width > width)
                {
					if (!temp_line->line_text.empty())
					{
						// 添加一行
						BaseElement::ChildrenPushBack(temp_line);

						// 修改文本大小
						if(temp_line->width > text_texture_total_width)
							text_texture_total_width = temp_line->width;
						text_texture_total_height += temp_line->height;

						// 把相关数据重置为 0
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
				if ((!isprint(c_temp[0]))) // 特殊字符检测
				{
					if (c_temp[0] != '\n')
					{
						c_temp[0] = '?'; // 转变为可见字符
					}
				}

                // 得到大小
                TTF_SizeUTF8(font.font, c_temp, &word_width, &word_height);
                if(word_height > temp_line->height)
                    temp_line->height = word_height;

				// 换行,新的一行
                if(c_temp[0] == '\n')
                {
					if (!temp_line->line_text.empty())
					{
						// 添加一行
						temp_line->line_text[temp_line->line_text.size() - 1] = ' ';
						BaseElement::ChildrenPushBack(temp_line);

						// 修改文本大小
						if(temp_line->width > text_texture_total_width)
							text_texture_total_width = temp_line->width;
						text_texture_total_height += temp_line->height;

						// 指向下一个字符并把相关数据重置为0
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
							// 新的一行
							BaseElement::ChildrenPushBack(temp_line);

							// 修改文本大小
							if(temp_line->width > text_texture_total_width)
								text_texture_total_width = temp_line->width;
							text_texture_total_height += temp_line->height;

							// 把相关数据重置为 0
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

        // 最后把最后一行也添加到数据中
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
            // 渲染每一行文本
            font.CreateTextUTF8(((LineText&)Children(i)).line_text.c_str(),  ((LineText&)Children(i)).line_text_color);
			((LineText&)Children(i)).image = font.image;
			((LineText&)Children(i)).ChangePosition(0, height);
            height += ((LineText&)Children(i)).height;
		}
    }

    void Writer::DoDraw()
    {
		// 自动换行,不裁剪
		// 自动换行,进行裁剪
		// 自动换行,左右居中
		// 自动换行,居中

		#ifdef CodeDebug
			// 画出线条来 文本外边框
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







