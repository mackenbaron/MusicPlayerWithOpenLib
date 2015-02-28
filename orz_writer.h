#ifndef ORZ_WRITER_H_INCLUDED
#define ORZ_WRITER_H_INCLUDED

#include "orz_font.h"
#include "orz_base_math.h"
#include <SDL_ttf.h>
#include <vector>

namespace Orz
{
    struct LineInformation
    {
        void Free()
        {
            text.clear();
            w = h =0;
        }
        LineInformation():w(0), h(0), texture(){}
        std::string text;
		BaseTexture texture;
        int w;
        int h;
    };

    class Writer
    {
    public:
        Writer();
        bool CreateWriter(const char *FontName, const char *Text, int FontSize, Color FontColor, Rect DestRect);

        // 以下操作可能需要重新渲染,略慢
        Writer& ChangeText(const char *Text);
        Writer& ChangeFontSize(int FontSize);
        Writer& ChangeTextSize(int W, int H);

		// 改变文本显示位置
		Writer& ChangeTextPosition(int X, int Y);

		// 设置透明度/可见度(0 -255)
		// ( 0 - 不可见, 255 - 不透明)
		Writer& ChangeAlpah(uint8_t Alpha);

		// 得到数据
		Writer& GetTextPosition(int &X, int &Y);
		Writer& GetTextSize(int &W, int &H);

        // 进行绘制
        void Write();
		void Write(int X, int Y);
		void Write(float PercentX, float PercentY);

    private:
		// 根据数据重新绘制纹理
		void RerenderTexture();

        // 字体
        Font font;

        // 用户想要渲染到什么地方
		Rect dest_rect;

        // 要渲染的文本
        std::string text;

        // 要渲染的每一行的文本
        std::vector<LineInformation> every_line;

        // 根据文本及字体创建的最终的文本纹理的宽高
        int text_texture_width, text_texture_height;

		// 文本透明度
		uint8_t alpha;
    };
}

#endif // ORZ_WRITER_H_INCLUDED
