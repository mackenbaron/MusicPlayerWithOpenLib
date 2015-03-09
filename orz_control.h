#ifndef ORZ_CONTROL_H_INCLUDED
#define ORZ_CONTROL_H_INCLUDED

#include "orz_base_control.h"
#include "orz_sprite.h"
#include "orz_writer.h"
#include <string>

#define CONTROL_BAR_OCCUPY_CONTROL_LIST_PERCENT (0.08) // 0.0 ~ 1.0

namespace Orz
{
	// �ؼ� - ���� - û�л����κζ���-------------------------------
	class ControlVirtual: public BaseControl
	{
	public:
		ControlVirtual();

		bool CreateControlVirtual(const char *ControlName, const Rect &ControlRect);

	private:
	};

	extern ControlVirtual error_control_virtual;

	// �ؼ� - ���� - ����������Ϊ����������ı�------------------------------
	class ControlCanvas: public BaseControl
	{
	public:
		ControlCanvas();

		// �����ı��ؼ�
		bool CreateControlCanvas(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor);

	private:
		// ����
		void DoDraw();
	};

	extern ControlCanvas error_control_canvas;

	// �ؼ� - ��ť - ������������ն��ı�----------------------------------
	class ControlButton: public BaseControl
	{
	public:
		ControlButton();

		// �����ؼ�
		bool CreateControlButton(const char *ControlName, const Rect &ControlRect, const Color &BackgroundColor);

	private:
		void DoDraw();
	};

	extern ControlButton error_control_button;
}
#endif