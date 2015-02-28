#ifndef ORZ_FONT_H_INCLUDED
#define ORZ_FONT_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include "orz_base_math.h"
#include "orz_base_texture.h"
#include <string>

namespace Orz
{
    struct Font
    {
    public:
        Font();
        ~Font();
        void Free();

        // ��������
        bool CreateFont(const char *FontName, int FontSize);
        void ChangeFontSize(int FontSize);

        // ����UTF8�����ı�
        bool CreateText(const char* Text, const Color& c); // ����:unicode ���뷽ʽ: utf-8
        inline Texture* GetTexture();

        // ������Ϣ
        TTF_Font *font;
        std::string font_name;
        BaseTexture image;
        int width, height;
        int font_size;
		Color font_color;
    };
}


#endif // ORZ_FONT_H_INCLUDED
