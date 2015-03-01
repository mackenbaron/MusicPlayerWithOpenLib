#ifndef ORZ_ROOT_H_INCLUDED
#define ORZ_ROOT_H_INCLUDED

#include "orz_animate.h"
#include "orz_writer.h"
#include "orz_base_RBTree.h"
#include "orz_control.h"

namespace Orz
{
    class Root
    {
    public:
        Root();

        // ��ʼ��
        virtual bool CreateScene();

        // ����ͼ��
        virtual void UpdateScene();

        // �˳�����
        void QuitScene();

        // ����
        virtual void Go();

        // ��ͼ
        void ShowScene();

        // ����
        Animate* CreateAnimate(KeyType Name, const char *NamePath);
        Animate& GetAnimate(KeyType Name);

        // ��д��
        Writer* CreateWriter(KeyType Name, std::string FontName, std::string Text, int FontSize, Color FontColor, Rect DestRect);
        Writer& GetWriter(KeyType Name);

		// �����ؼ�
		ControlText* CreateControlText(KeyType Name, const char *ControlName, int X, int Y, int Width, int Height, const char *FontName, int FontSize, const char *Text, Color &TextColor, Color &BackgroundColor);
		ControlButton* CreateControlButton(KeyType Name, const char* PathName, int X, int Y);
		ControlBar* CreateControlBar(KeyType Name, const char* PathName, int X, int Y);
		ControlList* CreateControlList(KeyType Name, const char* PathName, int X, int Y);

		// �õ��ؼ�
		ControlText& GetControlText(KeyType Name);
		ControlButton& GetControlButton(KeyType Name);
		ControlBar& GetControlBar(KeyType Name);
		ControlList& GetControlList(KeyType Name);
		

	private:
		friend class Management;

        // ���ڱ�ʶѭ��
        bool is_loop;

		// ������
        Animate error_animate;
		Writer error_writer;
		ControlText error_control_text;
		ControlButton error_control_button;
		ControlBar error_control_bar;
		ControlList error_control_list;

		// �����
        RBTree rb_tree;
    };
}
#endif // ORZ_ROOT_H_INCLUDED
