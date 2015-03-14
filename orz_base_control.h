#ifndef ORZ_BASE_CONTROL_H_INCLUDED
#define ORZ_BASE_CONTROL_H_INCLUDED

#include "orz_base_math.h"
#include "orz_base_ui.h"

#define WRITER_DISTANCE 1000.0f
#define SPRITE_DISTANCE 500.0f

namespace Orz
{
	//const long SHORT_SIGN_DELTA_TIME = 150;
	//const long DOUBLE_CLICK_DELTA_TIME = 150;

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
	

		// DoContact 函数中---------------------------------------------------------------	|
		// 六种理想信号:																	  	|
		// 1.短信号     2.长信号															  	|
		// 3.短,短型号  3.长,长信号													      	|
		// 2.短,长信号  4.长,短信号													      	|
		//																				  	|
		// 其他信号: 信号发送间隔等														  	|
		//																				  	|
		//																				  	|
		//          ________															  	|
		//_________|        |______________________________  单击						  	|
		//																				  	|
		//          _____________________________										  	|
		//_________|                             |_________  长按						  	|
		//																				  	|
		//          _______           _______											  	|
		//_________|       |_________|       |_____________	 两次单击					  	|
		//																				  	|
		//          _______       _______												  	|
		//_________|       |_____|       |_________________  双击						  	|
		//																				  	|
		//                 |_____|				  										  	|
		//                    |						  									  	|
		//                    |	__DOUBLE_CLICK_DELTA_TIME								  	|
		//																				  	|
		//              __________________短信号时间 SHORT_SIGN_TIME						  	|
		//          ___|___ 															  	|
		//         |       |															  	|
		//          _______																  	|
		//_________|       |_________________________    短信号						      	|
		//																				  	|
		//          _____________________________										  	|
		//_________|                             |___    长信号 (时间超过短信号的就是长信号)	|
		// 																				  	|
		//          _______																  	|
		//_________|       |_________________________    短信号						   		|
		// ________________________________________________________________________________	|

		void DoContactReset(void); // 注意使用本函数!
		void DoContact(void);

	private:
		// 背景颜色
		Color control_background_color;

		// 消息 and 状态
		ControlMessage control_message;
		ControlState control_state;

		// DoContact 记录用消息
		unsigned long sign_start_time, sign_end_time;
		bool is_last_down, is_last_short_sign;
		bool is_mouse_over;
    };
}

#endif // ORZ_CONTROL_H_INCLUDED
