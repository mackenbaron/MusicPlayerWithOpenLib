#ifndef ORZ_CONTROL_H_INCLUDED
#define ORZ_CONTROL_H_INCLUDED

#include "orz_base_control.h"
#include "orz_sprite.h"
#include <string>

#define CONTROL_BAR_OCCUPY_CONTROL_LIST_PERCENT (0.08) // 0.0 ~ 1.0

namespace Orz
{
	// �ؼ� - �ı��� - ����Ϊ��ɫ
	class ControlText: public BaseControl
	{
	public:
		// ���캯��
		ControlText();
		
		// �����ı��ؼ�
		bool CreateControlText(const char *ControlName, int X, int Y, int Width, int Height, const char *FontName, int FontSize, const char *Text, Color &TextColor, Color &BackgroundColor);

		// �޸�����
		ControlText& ChangeText(std::string& Text);
		ControlText& ChangePosition(int X, int Y);
		ControlText& ChangeSize(int Width, int Height);
		ControlText& ChangeBackgroundColor(Color BackGroundColor);

		// ����͸����/�ɼ���(0 -255)
		// ( 0 - ���ɼ�, 255 - ��͸��)
		ControlText& ChangeAlpha(uint8_t Alpha);
		ControlText& ChangeTextAlpha(uint8_t Alpha);

		// û�б���
		ControlText& ChangeToNoBackground();

		// �д�ɫ�ı���
		ControlText& ChangeToUseColorBackground();

		// ����
		void Draw();
		void Draw(int X, int Y);

	private:
		// ��ֹ����
		ControlText(const ControlText& source);
		ControlText& operator=(const ControlText& source);

		// д��
		Writer text_writer;

		// ����͸��
		bool is_transparent;

		// ������ɫ
		Color background_color;

		// �ؼ�͸����
		uint8_t control_alpha;
	};

	// �ؼ� - ��ť
	class ControlButton: public BaseControl
	{
	public:
		ControlButton();

		// ������ɫΪ�����Ŀؼ�
		bool CreateControlButton(int X, int Y, int Width, int Height, Color BackgroundColor);
		
		// ��������Ϊ�����Ŀؼ�
		bool CreateControlButton(int X, int Y, int Width, int Height, Sprite &BackgroundSprite);

		// ���ļ��д����ؼ�
		bool LoadControlButton(const char* PathName, int X, int Y);

		// � - �жϿؼ�״̬
		ControlButton& Contact(int MouseX, int MouseY, bool IsMouseDown);

		// �޸�����
		ControlButton& ChangeText(std::string& Text);
		ControlButton& ChangePosition(int X, int Y);
		ControlButton& ChangeSize(int Width, int Height);
		ControlButton& ChangeBackgroundColor(Color BackGroundColor);
		ControlButton& ChangeBackgroundSprite(Sprite &BackgroundSprite);
		ControlButton& ChangeAlpha(uint8_t Alpha);
		ControlButton& ChangeTextAlpha(uint8_t Alpha);
		ControlButton& ChangeBackgroundAlpha(uint8_t Alpha);
		ControlButton& ChangeToUseSolidColorBackground();
		ControlButton& ChangeToUseSpriteBackground();

		// ����
		void Draw();
		void DrawFill();

	private:
		// ��ֹ����
		ControlButton(const ControlButton& source);
		ControlButton& operator=(const ControlButton& source);

		// д��
		Writer text_writer;

		// �ı���ʾ��
		bool is_show_text;

		// ����
		bool is_solid_color_background;
		Color background_color;
		Sprite background_sprite;
		uint8_t control_alpha;
	};

	// �ؼ� - ������
	class ControlBar: public BaseControl
	{
	public:
		ControlBar();
		
		// ���ļ��д����������ؼ�
		bool LoadControlBar(const char* PathName, int X, int Y);

		// �ֶ������������ؼ�
		bool CreateControlBar(const char* Name, ControlDirect Direct, Rect &TroughRect, int BarWidth, int BarHeight, float CenterX, float CenterY, Color &BackgroundColorTrough, Color &BackgroundColorBar);

		// � - �жϿؼ�״̬
		ControlBar& Contact(int MouseX, int MouseY, bool IsMouseDown);

		// ��ù�����״̬
		float GetPercent(void);

		// �޸Ĺ���������
		ControlBar& ChangePercent(float Percent);
		ControlBar& ChangePercent(int MouseX, int MouseY);
		ControlBar& ChangeDirect(ControlDirect Direct);

		// �޸�ͨ������
		ControlBar& ChangePosition(int X, int Y);
		ControlBar& ChangeSize(int Width, int Height);
		ControlBar& ChangeBackgroundColor(Color& BackGroundColorTrough, Color& BackGroundColorbar);
		ControlBar& ChangeBackgroundSprite(Sprite &BackgroundTrough, Sprite &BackgroundBar);
		ControlBar& ChangeAlpha(uint8_t Alpha);
		ControlBar& ChangeToUseSolidColorBackground();
		ControlBar& ChangeToUseSpriteBackground();

		// ����
		void Draw();
		void DrawFill();

	private:

		// ��ֹ����
		ControlBar(const ControlBar& source);
		ControlBar& operator=(const ControlBar& source);

		// ���� �洢��������
		Color background_color_trough, background_color_bar;
		Sprite background_sprite_bar; // ���Ƶ�
		Sprite background_sprite_trough; // ����

		// ����������
		ControlDirect control_direct;
		float percent;
		int bar_width;
		int bar_height;
		float center_x, center_y;

		// ����
		bool is_solid_color_background;
		uint8_t control_alpha;

	};

	// �ؼ� - �б�
	class ControlList: public BaseControl
	{
	public:
		ControlList();
		~ControlList();

		// ���ļ��д����ؼ�
		bool LoadControlList(const char* PathName, int X, int Y);

		// � - �жϿؼ�״̬
		ControlList& Contact(int MouseX, int MouseY, bool IsMouseDown);

		// �������
		float GetPercent(void);
		ControlBar& GetControlBar();

		// �޸�����
		ControlList& ChangePercent(float Percent);
		ControlList& ChangePercent(int MouseX, int MouseY);
		ControlList& ChangePosition(int X, int Y);
		ControlList& ChangeSize(int Width, int Height);
		ControlList& ChangeBackgroundColor(Color& BackGroundColor);
		ControlList& ChangeBackgroundSprite(Sprite& BackgroundSprite);
		ControlList& ChangeAlpha(uint8_t Alpha);
		ControlList& ChangeToUseSolidColorBackground();
		ControlList& ChangeToUseSpriteBackground();

		// �б����
		ControlList& PushBack(const char *ControlName, const char* Text);
		ControlList& PushBack(ControlText* Entry);
		ControlList& Insert(int Position, const char *ControlName, const char* Text); // �� Position-1 �� Position ֮�����Ԫ��
		ControlList& Insert(int Position, ControlText* Entry); // �� Position-1 �� Position ֮�����Ԫ��
		ControlList& Delete(int Position);
		ControlText* GetControlText(int Position);
		bool IsAnyControlTextHaveMessage();
		int GetPositionOfControlTextThatHaveMessage();
		ControlText* GetControlTextThatHaveMessage();

		// ����
		void Draw();
		void DrawFill();

	private:
		// ��ֹ����
		ControlList(const ControlList& source);
		ControlList& operator=(const ControlList& source);

		// ������
		ControlBar control_bar;
		Color background_color;
		Sprite background_sprite;

		// �б�����
		std::vector<ControlText*> list;
		int entry_height;
		float control_bar_occupy_percent;
		bool is_any_control_text_have_message;
		int position_of_control_text_that_have_message;
		
		// ����
		bool is_solid_color_background;
		uint8_t control_alpha;
	};
}
#endif