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

        // ���²���������Ҫ������Ⱦ,����
        Writer& ChangeText(const char *Text);
        Writer& ChangeFontSize(int FontSize);
        Writer& ChangeTextSize(int W, int H);

		// �ı��ı���ʾλ��
		Writer& ChangeTextPosition(int X, int Y);

		// ����͸����/�ɼ���(0 -255)
		// ( 0 - ���ɼ�, 255 - ��͸��)
		Writer& ChangeAlpah(uint8_t Alpha);

		// �õ�����
		Writer& GetTextPosition(int &X, int &Y);
		Writer& GetTextSize(int &W, int &H);

        // ���л���
        void Write();
		void Write(int X, int Y);
		void Write(float PercentX, float PercentY);

    private:
		// �����������»�������
		void RerenderTexture();

        // ����
        Font font;

        // �û���Ҫ��Ⱦ��ʲô�ط�
		Rect dest_rect;

        // Ҫ��Ⱦ���ı�
        std::string text;

        // Ҫ��Ⱦ��ÿһ�е��ı�
        std::vector<LineInformation> every_line;

        // �����ı������崴�������յ��ı�����Ŀ��
        int text_texture_width, text_texture_height;

		// �ı�͸����
		uint8_t alpha;
    };
}

#endif // ORZ_WRITER_H_INCLUDED
