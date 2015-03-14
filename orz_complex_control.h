
#ifndef ORZ_COMPLEX_CONTROL_H_INCLUDE
#define ORZ_COMPLEX_CONTROL_H_INCLUDE

#include "orz_control.h"
#include "orz_font.h"

namespace Orz
{
	// �ؼ� - �ı���--------------------------------------
	class ControlText: public BaseControl
	{
	public:
		// ���캯��
		ControlText();

		// �����ı��ؼ�
		bool CreateControlText(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize, const char* Text, const Color &TextColor);

		// �޸�����
		Writer& GetWriter(void);

	private:
		void DoDraw(const Rect& DrawRect);
	};

	extern ControlText error_control_text;

	// �ؼ� - ��ť and �ı�------------------------------------
	class ControlButtonWithWriter: public ControlButton
	{
	public:
		ControlButtonWithWriter();

		// �����ؼ�
		bool CreateControlButtonWithWirter(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize, const char* Text, const Color &TextColor);

		// �޸�����
		Writer& GetWriter(void);
	};

	extern ControlButtonWithWriter error_control_button_with_writer;


	class ControlScrollBarWithColor: public BaseControl
	{
	public:
		ControlScrollBarWithColor();

		// �ֶ������������ؼ�
		bool CreateControlScrollBarWithColor(const char* Name, ControlDirect Direct, const Rect &ControlRect, const Color &BackgroundColorTrough, const Color &BackgroundColorBar);

		// ��ȡ����
		ControlButton& GetBar(void);
		ControlScrollBarWithColor& GetPercent(float &Percent);

		// �޸�����
		ControlScrollBarWithColor& ChangePercent(float Percent);
		ControlScrollBarWithColor& ChangePercentAccrodToMousePosition(void);
		ControlScrollBarWithColor& ChangeDirect(ControlDirect Direct);

	private:
		void DoDraw(const Rect& DrawRect);

		// ����������
		ControlDirect control_direct;
		float control_percent;
	};

	extern ControlScrollBarWithColor error_control_scroll_bar_with_color;

	// �ؼ� - �б�---------------------------------------
	class ControlList: public ControlCanvas
	{
	public:
		ControlList();

		// ���ļ��д����ؼ�
		bool LoadControlList(const char* PathName, int X, int Y);

		// �����ؼ�
		bool CreateControlList(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, int EntryHeight, const char *FontName, int FontSize);

		// �������
		ControlList& GetPercent(float &Percent);
		ControlList& GetContentSize(int &Size);

		// �޸�����
		ControlList& ChangePercent(float Percent);

		// �б����
		ControlList& PushBackControlText(const char *ControlName, const char* Text);
		ControlList& Insert(int Position, const char *ControlName, const char* Text); // �� Position-1 �� Position ֮�����Ԫ��

	private:
		void DoDraw(const Rect& DrawRect);
		void DoContact();
		// �б�����
		BaseFont list_font;

		int entry_height;
		float control_percent;
	};

	extern ControlList error_control_list;
}


#endif