#ifndef ORZ_BASE_CONTROL_H_INCLUDED
#define ORZ_BASE_CONTROL_H_INCLUDED

#include "orz_base_math.h"
#include "orz_base_element.h"

namespace Orz
{
    //
    //                       ____________  发送"单击"消息
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
    //                        发送"双击"消息
    //
    //----------------------------------------------------------
    //                   ____________________________ 持续发送"持续按键"消息
    //                  ||||||||||||||||||||||
    //                  ||||||||||||||||||||||
    //          _____________________________
    //_________|                             |_______________
    //
    //         |________|                   /|\
    //             |                         |
    //             |                         |
    //             |                         |_____________发送"持续按键结束"消息
    //        CLICK_DELTA_TIME
    //

	// 基础控件类 - 纯虚类
    class BaseControl: public BaseElement
    {
    public:
		// 构造函数
		BaseControl(ElementType Type, int X, int Y, int Width, int Height, ControlBackgroundStyle BackgroundStyle);

		// 析构函数
        virtual ~BaseControl()=0;

		// 获取当前控件状态
		ControlMessage GetMessage(void);
		ControlState GetState(void);

		// 设置当前状态
		virtual BaseControl& Contact(int MouseX, int MouseY, bool IsMouseDown);

		// 绘制
		virtual void DoDraw(void);

		// 背景样式
		ControlBackgroundStyle background_style;

		// 当前控件消息&状态
		ControlMessage control_message;
		ControlState control_state;
    };
}

#endif // ORZ_CONTROL_H_INCLUDED
