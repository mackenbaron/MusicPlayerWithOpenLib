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

		// �޸�����
		LineText& ChangeTextUTF8(BaseFont &Font, const char *Text);		// �˲�����Ҫ������Ⱦ����
		LineText& ChangeColor(BaseFont &Font, const Color &NewColor);	// �˲�����Ҫ������Ⱦ����
		
		// ��ȡ����
		LineText& GetText(std::string& ReceiveText);

		// �ͷű��е�����
		void DoFree();

	private:
		friend class Writer;

		// ����
		void DoDraw(void);
		void DoChangeAlpha(unsigned char Alpha);

		// �����������´�������
		void ReloadTexture(BaseFont &Font);

		// ��һ�е�����
		std::string line_text;
		Color line_text_color;
		BaseTexture image;
	};

    class Writer: public BaseUi
    {
    public:
        Writer();
        bool CreateWriter(const char *FontName, const char *Text, int FontSize, Color FontColor, Rect DestRect);

		// �ı�����
		Writer& ChangeTextCenterPosition(float PrecentX, int PrecentY);
		Writer& ChangeFontSize(int FontSize);		// �˲�����Ҫ������Ⱦ����
        Writer& ChangeTextUTF8(const char *Text);	// �˲�����Ҫ������Ⱦ����
		Writer& ChangeTextColor(const Color &NewColor);	// �˲�����Ҫ������Ⱦ����

		// �õ�����
		Writer& GetText(std::string& ReceiveText);

    private:
		// �����������»�������
		void ReloadTexture();

		void DoChangeSize(int Width, int Height);
		void DoDraw();

        // ����
        BaseFont font;

        // Ҫ��Ⱦ���ı�
        std::string writer_text;

		// ��ɫ
		Color writer_color;

        // �����ı������崴�������յ��ı�����Ŀ��
        int text_texture_total_width, text_texture_total_height;
    };
}

#endif // ORZ_WRITER_H_INCLUDED
