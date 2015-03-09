
#include "orz_font.h"
#include "orz_log.h"
#include "orz_base_public_resource.h"

namespace Orz
{
    BaseFont::BaseFont():font(0)
    {
        Free();
    }

    BaseFont::~BaseFont()
    {
        Free();
    }

    void BaseFont::Free()
    {
		if (font)
		{
			TTF_CloseFont(font);
			font = NULL;
		}
    }

    bool BaseFont::CreateFont(const char* FontName, int FontSize)
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

	void BaseFont::ChangeFontSize(int FontSize)
	{
		CreateFont(font_name.c_str(), FontSize);
	}

	bool BaseFont::CreateTextUTF8(const char* Text, const Color& c)
	{
		return image.LoadFromTextUTF8(font, Text, c);
	}

	void BaseFont::GetTextSizeUTF8(const char *Text, int &Width, int &Height)
	{
		TTF_SizeUTF8(font, Text, &Width, &Height);
	}

}
