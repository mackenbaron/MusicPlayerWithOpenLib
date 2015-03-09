#ifndef ORZ_WRITER_H_INCLUDED
#define ORZ_WRITER_H_INCLUDED

#include "orz_font.h"
#include "orz_base_math.h"
#include "orz_base_ui.h"
#include <vector>

namespace Orz
{
	struct LineText: public BaseUi
	{
	public:
		LineText();

		// 修改属性
		LineText& ChangeTextUTF8(BaseFont &Font, const char *Text);		// 此操作需要重新渲染纹理
		LineText& ChangeColor(BaseFont &Font, const Color &NewColor);	// 此操作需要重新渲染纹理
		
		// 获取属性
		LineText& GetText(std::string& ReceiveText);

		// 释放本行的内容
		void DoFree();

	private:
		friend class Writer;

		// 绘制
		void DoDraw(void);
		void DoChangeAlpha(unsigned char Alpha);

		// 根据数据重新创建纹理
		void ReloadTexture(BaseFont &Font);

		// 这一行的文字
		std::string line_text;
		Color line_text_color;
		BaseTexture image;
	};

    class Writer: public BaseUi
    {
    public:
        Writer();
        bool CreateWriter(const char *FontName, const char *Text, int FontSize, Color FontColor, Rect DestRect);

		// 改变属性
		Writer& ChangeTextCenterPosition(float PrecentX, int PrecentY);
		Writer& ChangeFontSize(int FontSize);		// 此操作需要重新渲染纹理
        Writer& ChangeTextUTF8(const char *Text);	// 此操作需要重新渲染纹理
		Writer& ChangeTextColor(const Color &NewColor);	// 此操作需要重新渲染纹理

		// 得到数据
		Writer& GetText(std::string& ReceiveText);

    private:
		// 根据数据重新绘制纹理
		void ReloadTexture();

		void DoChangeSize(int Width, int Height);
		void DoDraw();

        // 字体
        BaseFont font;

        // 要渲染的文本
        std::string writer_text;

		// 颜色
		Color writer_color;

        // 根据文本及字体创建的最终的文本纹理的宽高
        int text_texture_total_width, text_texture_total_height;
    };
}

#endif // ORZ_WRITER_H_INCLUDED
