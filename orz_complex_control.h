
#ifndef ORZ_COMPLEX_CONTROL_H_INCLUDE
#define ORZ_COMPLEX_CONTROL_H_INCLUDE

#include "orz_control.h"
#include "orz_font.h"

namespace Orz
{
	// �ؼ� - �ı���--------------------------------------
	class ControlText: public ControlCanvas
	{
	public:
		// ���캯��
		ControlText();

		// �����ı��ؼ�
		bool CreateControlText(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize, const char* Text, const Color &TextColor);

		// �޸�����
		Writer& GetWriter(void);
	};

	extern ControlText error_control_text;

	// �ؼ� - ��ť and �ı�------------------------------------
	class ControlButtonWithWriter: public ControlButton
	{
	public:
		ControlButtonWithWriter();

		// �����ؼ�
		bool CreateControlButtonWithWirter(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize, const char* Text, const Color &TextColor);

		// ���ļ��д����ؼ�
		bool LoadControlButtonWithText(const char* PathName, int X, int Y, const Color &BackgroundColor, const char *FontName, int FontSize, const char* Text, const Color &TextColor);

		// �޸�����
		Writer& GetWriter(void);
	};

	extern ControlButtonWithWriter error_control_button_with_writer;


	// �ؼ� - ������-----------------------------------------------
	class ControlScrollBar: public BaseControl
	{
	public:
		ControlScrollBar();

		// �ֶ������������ؼ�
		bool CreateControlScrollBar(const char* Name, ControlDirect Direct, const Rect &ControlRect, const Color &BackgroundColorTrough, const Color &BackgroundColorBar);

		// ��ȡ����
		ControlButton& GetBar(void);
		float GetPercent(void);

		// �޸�����
		ControlScrollBar& ChangePercent(float Percent);
		ControlScrollBar& ChangePercentAccrodToMousePosition(void);
		ControlScrollBar& ChangeDirect(ControlDirect Direct);

	private:
		void DoDraw(void);

		// ����������
		ControlDirect control_direct;
		float control_percent;
	};

	extern ControlScrollBar error_control_scroll_bar;

	// �ؼ� - �б�---------------------------------------
	class ControlList: public ControlCanvas
	{
	public:
		ControlList();

		// ���ļ��д����ؼ�
		bool LoadControlList(const char* PathName, int X, int Y);

		// �����ؼ�
		bool CreateControlList(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize);

		// �������
		float GetPercent(void);

		// �޸�����
		ControlList& ChangePercent(float Percent);

		// �б����
		ControlList& PushBack(const char *ControlName, const char* Text);
		ControlList& Insert(int Position, const char *ControlName, const char* Text); // �� Position-1 �� Position ֮�����Ԫ��

	private:

		// �б�����
		BaseFont list_font;

		int entry_height;
		float control_percent;
	};

	extern ControlList error_control_list;
}


#endif