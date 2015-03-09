#ifndef ORZ_BASE_CONTROL_H_INCLUDED
#define ORZ_BASE_CONTROL_H_INCLUDED

#include "orz_base_math.h"
#include "orz_base_ui.h"

#define WRITER_DISTANCE -1000.0f
#define SPRITE_DISTANCE -500.0f

namespace Orz
{
	// 基础控件类 - 纯虚类
    class BaseControl: public BaseUi
    {
    public:
		// 构造函数
		BaseControl(ElementType Type);

		// 修改属性
		BaseControl& ChangeBackgroundColor(const Color &BackGroundColor);

		// 获取属性
		const Color& GetBackgroundColor(void);
		ControlMessage GetControlMessage(void);
		ControlState GetControlState(void);
	
	private:

		// DoContact 函数中------------------------------------------------------------------
		//																					|
		//                       ____________  发送"单击"消息								|
		//                      |															|
		//                     \|/															|
		//        _____																		|
		//_______|     |___________________													|
		//																					|
		//       |________|																	|
		//           |																		|
		//           |																		|
		//           |																		|
		//       CLICK_DELTA_TIME															|
		//-------------------------------------------------------------						|
		//																					|
		//																					|
		//																					|
		//                   ________ DOUBLE_CLICK_DELTA_TIME								|
		//                  |																|
		//          _____  \|/  _____														|
		//_________|     |_____|     |_____________											|
		//																					|
		//                          /|\														|
		//                           |														|
		//                           |														|
		//                        发送"双击"消息												|
		//																					|
		//----------------------------------------------------------						|
		//                   ____________________________ 持续发送"持续按键"消息				|
		//                  ||||||||||||||||||||||											|
		//                  ||||||||||||||||||||||											|
		//          _____________________________											|
		//_________|                             |_______________							|
		//																					|
		//         |________|                   /|\											|
		//             |                         |											|
		//             |                         |											|
		//             |                         |_____________发送"持续按键结束"消息		|
		//        CLICK_DELTA_TIME															|
		// ________________________________________________________________________________	|
		virtual void DoContact(void);
		virtual void DoContactReset(void);

		// 背景颜色
		Color control_background_color;

		// 消息 and 状态
		ControlMessage control_message;
		ControlState control_state;

		// DoContact 记录用消息
		unsigned int last_down_time, last_up_time; //  最后一次单击/双击控件的时间
		bool is_last_down; // 上次是否按下
		bool in_judge_click, in_judge_double_click, in_judge_const_down; // 是否在判断鼠标事件之内
		unsigned int curr_time, delta_time; // 当前时间/推移时间
		bool is_mouse_over;
    };
}

#endif // ORZ_CONTROL_H_INCLUDED
