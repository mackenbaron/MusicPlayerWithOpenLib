#ifndef ORZ_MANAGEMENT_H_INCLUDED
#define ORZ_MANAGEMENT_H_INCLUDED


#include "orz_animate.h"
#include "orz_writer.h"
#include "orz_base_RBTree.h"
#include "orz_control.h"

namespace Orz
{
	class BaseElement
	{

	private:
		Rect size;
		float distance;
	};

	class _Manager
	{
	public:
		_Manager();

		// ��ʼ���г���
		void Go(bool (*_CreateScene)(), void (*_UpdateScene)());

		// �˳�����
		void QuitScene();

		// ����
		virtual Animate* CreateAnimate(KeyType Name, const char *NamePath);
		virtual Animate& GetAnimate(KeyType Name);

		// ��д��
		virtual Writer* CreateWriter(KeyType Name, std::string FontName, std::string Text, int FontSize, Color FontColor, Rect DestRect);
		virtual Writer& GetWriter(KeyType Name);

		// �����ؼ�
		virtual ControlText* CreateControlText(KeyType Name, const char *ControlName, int X, int Y, int Width, int Height, const char *FontName, int FontSize, const char *Text, Color &TextColor, Color &BackgroundColor);
		virtual ControlButton* CreateControlButton(KeyType Name, const char* PathName, int X, int Y);
		virtual ControlBar* CreateControlBar(KeyType Name, const char* PathName, int X, int Y);
		virtual ControlList* CreateControlList(KeyType Name, const char* PathName, int X, int Y);

		// �õ��ؼ�
		virtual ControlText& GetControlText(KeyType Name);
		virtual ControlButton& GetControlButton(KeyType Name);
		virtual ControlBar& GetControlBar(KeyType Name);
		virtual ControlList& GetControlList(KeyType Name);

	private:
		// ��ͼ
		void PresentScene();
		void UpdateDebugScene();

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

#endif