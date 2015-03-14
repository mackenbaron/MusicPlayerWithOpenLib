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
		LineText& ChangeTextPositionPercent(float PercentX, float PercentY);
		
		// ��ȡ����
		LineText& GetText(std::string& ReceiveText);

		// �ͷű��е�����
		void DoFree();

	private:
		friend class Writer;

		// ����
		void DoDraw(const Rect& DrawRect);
		void DoChangeAlpha(unsigned char Alpha);

		// �����������´�������
		void ReloadTexture(BaseFont &Font);

		// ��һ�е�����
		std::string line_text;
		Color line_text_color;
		BaseTexture image;

		// ����λ��
		float text_percent_x, text_percent_y;
	};

    class Writer: public BaseUi
    {
    public:
        Writer();
        bool CreateWriter(const char *WriterName, const char *FontName, const char *Text, int FontSize, Color FontColor, Rect DestRect);

		// �ı�����
		Writer& ChangeTextCenterPosition(float PrecentX, float PrecentY);
		Writer& ChangeFontSize(int FontSize);		// �˲�����Ҫ������Ⱦ����
        Writer& ChangeTextUTF8(const char *Text);	// �˲�����Ҫ������Ⱦ����
		Writer& ChangeTextColor(const Color &NewColor);	// �˲�����Ҫ������Ⱦ����

		// �õ�����
		Writer& GetText(std::string& ReceiveText);

    private:
		// �����������»�������
		void ReloadTexture();

		void DoChangeSize(int Width, int Height);
		void DoDraw(const Rect& DrawRect);
		
        // ����
        BaseFont font;

        // Ҫ��Ⱦ���ı�
        std::string writer_text;

		// ��ɫ
		Color writer_color;
		float writer_text_center_x;
		float writer_text_center_y;

        // �����ı������崴�������յ��ı�����Ŀ��
        int text_texture_total_width, text_texture_total_height;
    };
}

#endif // ORZ_WRITER_H_INCLUDED
