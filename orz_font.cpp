
#include "orz_font.h"
#include "orz_log.h"
#include "orz_base_public_resource.h"

namespace Orz
{
    Font::Font():font(0)
    {
        Free();
    }

    Font::~Font()
    {
        Free();
    }

    void Font::Free()
    {
		if (font)
		{
			TTF_CloseFont(font);
			font = NULL;
		}
    }

    bool Font::CreateFont(const char* FontName, int FontSize)
    {
        Free();
        font = TTF_OpenFont(FontName, FontSize);
        font_name = FontName;
        font_size = FontSize;
        if(font == NULL)
        {
            error_out("Font::CreateFont - ´´½¨×ÖÌåÊ§°Ü!");
            return false;
        }

        return true;
    }

	void Font::ChangeFontSize(int FontSize)
	{
		CreateFont(font_name.c_str(), FontSize);
	}

	bool Font::CreateText(const char* Text, const Color& c)
	{
		if(!font)
		{
			return false;
		}

		return image.CreateFromRenderedText(font, Text, c);
	}

    inline Texture* Font::GetTexture()
    {
        return image.GetTexture();
    }
}
