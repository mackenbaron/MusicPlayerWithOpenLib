#ifndef ORZ_BASE_CONTROL_H_INCLUDED
#define ORZ_BASE_CONTROL_H_INCLUDED

#include "orz_base_math.h"
#include "orz_base_element.h"

namespace Orz
{
    //
    //                       ____________  ����"����"��Ϣ
    //                      |
    //                     \|/
    //        _____
    //_______|     |___________________
    //
    //       |________|
    //           |
    //           |
    //           |
    //       CLICK_DELTA_TIME
    //-------------------------------------------------------------
    //
    //
    //
    //                   ________ DOUBLE_CLICK_DELTA_TIME
    //                  |
    //          _____  \|/  _____
    //_________|     |_____|     |_____________
    //
    //                          /|\
    //                           |
    //                           |
    //                        ����"˫��"��Ϣ
    //
    //----------------------------------------------------------
    //                   ____________________________ ��������"��������"��Ϣ
    //                  ||||||||||||||||||||||
    //                  ||||||||||||||||||||||
    //          _____________________________
    //_________|                             |_______________
    //
    //         |________|                   /|\
    //             |                         |
    //             |                         |
    //             |                         |_____________����"������������"��Ϣ
    //        CLICK_DELTA_TIME
    //

	// �����ؼ��� - ������
    class BaseControl: public BaseElement
    {
    public:
		// ���캯��
		BaseControl(ElementType Type, int X, int Y, int Width, int Height, ControlBackgroundStyle BackgroundStyle);

		// ��������
        virtual ~BaseControl()=0;

		// ��ȡ��ǰ�ؼ�״̬
		ControlMessage GetMessage(void);
		ControlState GetState(void);

		// ���õ�ǰ״̬
		virtual BaseControl& Contact(int MouseX, int MouseY, bool IsMouseDown);

		// ����
		virtual void DoDraw(void);

		// ������ʽ
		ControlBackgroundStyle background_style;

		// ��ǰ�ؼ���Ϣ&״̬
		ControlMessage control_message;
		ControlState control_state;
    };
}

#endif // ORZ_CONTROL_H_INCLUDED
