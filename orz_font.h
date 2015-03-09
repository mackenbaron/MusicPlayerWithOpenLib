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

        // 创建字体
        bool CreateFont(const char *FontName, int FontSize);
        void ChangeFontSize(int FontSize);

        // 根据UTF8创建文本
        bool CreateTextUTF8(const char* Text, const Color& c); // 内码:unicode 编码方式: utf-8
		void GetTextSizeUTF8(const char *Text, int &Width, int &Height);

        // 字体信息
        TTF_Font *font;
        std::string font_name;
        BaseTexture image;
        int width, height;
        int font_size;
    };
}


#endif // ORZ_FONT_H_INCLUDED
