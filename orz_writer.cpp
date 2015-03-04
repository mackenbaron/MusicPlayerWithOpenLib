

#include "orz_writer.h"
#include "orz_log.h"
#include "orz_base_public_resource.h"

namespace Orz
{
    Writer::Writer()
    {
		alpha = 255;
    }

    bool Writer::CreateWriter(const char *FontName, const char *Text, int FontSize, Color FontColor, Rect DestRect)
	{
		if(!font.CreateFont(FontName, FontSize))
		{
			return false;
		}

		text = Text;

		// ��ֹ�����С����
        if(font.font_size < 0)
            font.font_size = 32;
        else
            font.font_size = FontSize;
		font.font_color = FontColor;
		dest_rect = DestRect;

		RerenderTexture();

		return true;
    }

    Writer& Writer::ChangeText(const char *Text)
    {
		text = Text;

        RerenderTexture();
        return *this;
	}

    Writer& Writer::ChangeFontSize(int FontSize)
    {
        if(FontSize!=font.font_size)
		{
			// ��ֹ�����С
			if(FontSize <= 0)
				font.font_size = 32;
			else
				font.font_size = FontSize;

			font.ChangeFontSize(font.font_size);

			// ������Ⱦ
			RerenderTexture();
		}
        return *this;
    }

    Writer& Writer::ChangeTextSize(int W, int H)
    {
		dest_rect.h = H;

        if(dest_rect.w != W)
        {
            dest_rect.w = W;
            RerenderTexture();
        }

        return *this;
    }

    void Writer::RerenderTexture()
    {
		// ��ֹ�������
		if(dest_rect.w < font.font_size)
			dest_rect.w = font.font_size;

        // ָ���ַ�����ͷ
        every_line.clear();
        text_texture_width = text_texture_height = 0;

		// ʵ����
        //const char _array[] = {
        //        0xE4, 0xB8, 0x96,
        //        0xE7, 0x95, 0x8C,
        //        0x21,48,49,50,51,52,53,54,55,56,0}, *p = _array;
		const char *p = text.c_str();

        int w = 0, h = 0, digit = 0;
        unsigned char magic_number;
        char c_temp[16] = {0} ;
        LineInformation line_temp;

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
                for(int i = 1; i < digit;i++)
                {
                    c_temp[i] = p[i];
                }

                c_temp[digit] = 0;

                // �õ���С
                TTF_SizeUTF8(font.font, (char*)c_temp, &w, &h);
                if(h > line_temp.h)
                    line_temp.h = h;

                // �µ�һ��
                if( w + line_temp.w > dest_rect.w)
                {
                    // ���һ��
					if (line_temp.text[0])
					{
						every_line.push_back(line_temp);

						// �޸��ı���С
						if(line_temp.w > text_texture_width)
							text_texture_width = line_temp.w;
						text_texture_height += line_temp.h;

						// �������������Ϊ 0
						line_temp.Free();
					}
                }
                else
                {
                    p += digit;
                    line_temp.text += (char*)c_temp;
                    line_temp.w += w;
                }
            }
            else // ASCII
            {
				c_temp[1] = 0;
				if ((!isprint(c_temp[0]))) // �����ַ����
					if (c_temp[0] == '\n')
					{
						c_temp[0] = ' ';
					} 
					else
					{
						c_temp[0] = '?';
					}

                // �õ���С
                TTF_SizeUTF8(font.font, (char*)c_temp, &w, &h);
                if(h > line_temp.h)
                    line_temp.h = h;

				// ����,�µ�һ��
                if(c_temp[0] == '\n')
                {
                    // ���һ��
					line_temp.text[line_temp.text.size() - 1] = ' ';
                    every_line.push_back(line_temp);

                    // �޸��ı���С
                    if(line_temp.w > text_texture_width)
                        text_texture_width = line_temp.w;
                    text_texture_height += line_temp.h;

                    // ָ����һ���ַ����������������Ϊ0
                    p++;
                    line_temp.Free();
                }
                else
                {
					// �µ�һ��
                    if( w + line_temp.w > dest_rect.w)
					{
						if (line_temp.text[0])
						{
							every_line.push_back(line_temp);

							// �޸��ı���С
							if(line_temp.w > text_texture_width)
								text_texture_width = line_temp.w;
							text_texture_height += line_temp.h;

							// �������������Ϊ 0
							line_temp.Free();
						}
                    }
                    else
                    {
                        p++;
                        line_temp.text += (char*)c_temp;
                        line_temp.w += w;
                    }
                }// end \n

            }// end ASCII
        }// end while

        // �������һ��Ҳ��ӵ�������
		if (!line_temp.text.empty())
		{
			every_line.push_back(line_temp);
			if(line_temp.w > text_texture_width)
				text_texture_width = line_temp.w;
			text_texture_height += line_temp.h;
		}

        int height=0;
        for(int i = 0; i < every_line.size(); i++)
        {
            // ��Ⱦÿһ���ı�
            font.CreateText(every_line[i].text.c_str(), font.font_color);
			every_line[i].texture = font.image;
            height += every_line[i].h;
        }

        // �ض�����ȾĿ��
        //SDL_SetRenderTarget(sdl.render, NULL);
    }

	Writer& Writer::ChangeTextPosition(int X, int Y)
	{
        dest_rect.x = X;
        dest_rect.y = Y;

		return *this;
	}

	Writer& Writer::ChangeAlpah(uint8_t Alpha)
	{
		alpha = Alpha;

		// ����͸����
		for(int i = 0; i < every_line.size(); i++)
		{
			every_line[i].texture.SetAlpha(alpha);
		}

		return *this;
	}

	Writer& Writer::GetTextPosition(int &X, int &Y)
	{
		X = dest_rect.x;
		Y = dest_rect.y;
		return *this;
	}

	Writer& Writer::GetTextSize(int &W, int &H)
	{
		W = dest_rect.w;
		H = dest_rect.h;
		return *this;
	}

    void Writer::Write()
    {
		int render_point_y = dest_rect.y;
		int render_point_x = 0;

		// �Զ�����,���ü�
		for(int i = 0; i < every_line.size(); i++)
		{
			every_line[i].texture.Draw(dest_rect.x, render_point_y);
			render_point_y += every_line[i].h;
		}
		
		//// �Զ�����,���вü�
		//for(int i = 0; i < every_line.size(); i++)
		//{
		//	if(render_point_y + every_line[i].h <= dest_rect.y + dest_rect.h)
		//	{
		//		every_line[i].texture.Draw(dest_rect.x, render_point_y);
		//		render_point_y += every_line[i].h;
		//	}
		//	else // ����
		//	{
		//		Rect dest_clip_rect = {dest_rect.x, render_point_y, every_line[i].texture.GetWidth(),  dest_rect.y + dest_rect.h - render_point_y};
		//		Rect source_clip_rect = {0, 0, dest_clip_rect.w, dest_clip_rect.h};
		//		SDL_RenderCopy(sdl.render, every_line[i].texture.GetTexture(), &source_clip_rect, &dest_clip_rect);

		//		// ����֮���˳�ѭ��
		//		break;
		//	}
		//}

		//// �Զ�����,���Ҿ���
		//for(int i = 0; i < every_line.size(); i++)
		//{
		//	render_point_x = (dest_rect.w - every_line[i].w)/2 + dest_rect.x;
		//	if(render_point_y + every_line[i].h <= dest_rect.y + dest_rect.h)
		//	{
		//		every_line[i].texture.Draw(render_point_x, render_point_y);
		//		render_point_y += every_line[i].h;
		//	}
		//	else // ����
		//	{
		//		Rect dest_clip_rect = {render_point_x, render_point_y, every_line[i].texture.GetWidth(),  dest_rect.y + dest_rect.h - render_point_y};
		//		Rect source_clip_rect = {0, 0, dest_clip_rect.w, dest_clip_rect.h};
		//		SDL_RenderCopy(sdl.render, every_line[i].texture.GetTexture(), &source_clip_rect, &dest_clip_rect);

		//		// ����֮���˳�ѭ��
		//		break;
		//	}
		//}

		//// �Զ�����,����(������, ����)
		//if(dest_rect.h > text_texture_height)
		//{
		//	render_point_y = (dest_rect.h - text_texture_height)/2 + dest_rect.y;
		//	for(int i = 0; i < every_line.size(); i++)
		//	{
		//		render_point_x = (dest_rect.w - every_line[i].w)/2 + dest_rect.x;
		//		every_line[i].texture.Draw(render_point_x, render_point_y);
		//		render_point_y += every_line[i].h;
		//	}
		//}
		//else
		//{
		//	int i = 0;
		//	render_point_y = (dest_rect.h - text_texture_height)/2 + dest_rect.y;
		//	for(; i < every_line.size(); i++)
		//	{
		//		if(render_point_y + every_line[i].h > dest_rect .y)
		//		{
		//			if(render_point_y + every_line[i].h > dest_rect.y + dest_rect .h)
		//			{
		//				render_point_x = (dest_rect.w - every_line[i].w)/2 + dest_rect.x;
		//				Rect dest_clip_rect = {render_point_x, dest_rect.y, every_line[i].texture.GetWidth(), dest_rect.h};
		//				Rect source_clip_rect = {0, dest_rect.y - render_point_y, dest_clip_rect.w, dest_clip_rect.h};
		//				SDL_RenderCopy(sdl.render, every_line[i].texture.GetTexture(), &source_clip_rect, &dest_clip_rect);

		//				// ����֮���˳�ѭ��
		//				break;
		//			}
		//			else
		//			{
		//				render_point_x = (dest_rect.w - every_line[i].w)/2 + dest_rect.x;
		//				Rect dest_clip_rect = {render_point_x, dest_rect.y, every_line[i].texture.GetWidth(), render_point_y + every_line[i].h - dest_rect.y};
		//				Rect source_clip_rect = {0, dest_rect.y - render_point_y, dest_clip_rect.w, dest_clip_rect.h};
		//				SDL_RenderCopy(sdl.render, every_line[i].texture.GetTexture(), &source_clip_rect, &dest_clip_rect);
		//			
		//				// �����,��һ��
		//				i++;
		//				render_point_y += every_line[i].h;

		//				for(; i < every_line.size(); i++)
		//				{
		//					render_point_x = (dest_rect.w - every_line[i].w)/2 + dest_rect.x;
		//					if(render_point_y + every_line[i].h <= dest_rect.y + dest_rect.h)
		//					{
		//						every_line[i].texture.Draw(render_point_x, render_point_y);
		//						render_point_y += every_line[i].h;
		//					}
		//					else // ����
		//					{
		//						Rect dest_clip_rect = {render_point_x, render_point_y, every_line[i].texture.GetWidth(),  dest_rect.y + dest_rect.h - render_point_y};
		//						Rect source_clip_rect = {0, 0, dest_clip_rect.w, dest_clip_rect.h};
		//						SDL_RenderCopy(sdl.render, every_line[i].texture.GetTexture(), &source_clip_rect, &dest_clip_rect);

		//						// ����֮���˳�ѭ��
		//						break;
		//					}
		//				}
		//			}
		//			break;
		//		}
		//		render_point_y += every_line[i].h;
		//	}
		//}

		//// �Զ�����,����
		//sdl.SetViewport(dest_rect);
		//Rect virtual_dest_rect = {0,0, dest_rect.w, dest_rect.h};
		//render_point_y = (virtual_dest_rect.h - text_texture_height)/2 + virtual_dest_rect.y;
		//for(int i = 0; i < every_line.size(); i++)
		//{
		//	render_point_x = (virtual_dest_rect.w - every_line[i].w)/2 + virtual_dest_rect.x;
		//	every_line[i].texture.Draw(render_point_x, render_point_y);
		//	render_point_y += every_line[i].h;
		//}
		//// ���û�Ĭ���ӵ�
		//sdl.SetViewportToDefault();

		#ifdef CodeDebug
			// ���������� �ı���߿�
			device.display.DrawOutlineRect(RedColor, dest_rect);
		#endif
    }

	void Writer::Write(int X, int Y)
	{

		int render_point_y = Y;
		int render_point_x = 0;

		// �Զ�����,���ü�
		for(int i = 0; i < every_line.size(); i++)
		{
			every_line[i].texture.Draw(X, render_point_y);
			render_point_y += every_line[i].h;
		}

		#ifdef CodeDebug
			// ���������� �ı���߿�
			Rect outline_rect = {X, Y,dest_rect.w , dest_rect.h};
			device.display.DrawOutlineRect(RedColor, outline_rect);
		#endif
	}

	void Writer::Write(float PercentX, float PercentY)
	{
		int render_point_y = dest_rect.y + dest_rect.h * PercentY;
		int render_point_x = dest_rect.x + (dest_rect.w- text_texture_width) * PercentX ;

		// �Զ�����,���ü�
		for(int i = 0; i < every_line.size(); i++)
		{
			every_line[i].texture.Draw(render_point_x, render_point_y);
			render_point_y += every_line[i].h;
		}
	}

}







