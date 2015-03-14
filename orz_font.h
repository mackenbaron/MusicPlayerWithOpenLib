#ifndef ORZ_FONT_H_INCLUDED
#define ORZ_FONT_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include "orz_base_math.h"
#include "orz_base_texture.h"
#include <string>

namespace Orz
{
    struct BaseFont
    {
    public:
        BaseFont();
        ~BaseFont();
        void Free();

        // ��������
        bool CreateFont(const char *FontName, int FontSize);
        void ChangeFontSize(int FontSize);

        // ����UTF8�����ı�
        bool CreateTextUTF8(const char* Text, const Color& c); // ����:unicode ���뷽ʽ: utf-8
		void GetTextSizeUTF8(const char *Text, int &Width, int &Height);

        // ������Ϣ
        TTF_Font *font;
        std::string font_name;
        BaseTexture image;
        int width, height;
        int font_size;
    };
}


#endif // ORZ_FONT_H_INCLUDED
