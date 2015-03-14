
#ifndef ORZ_BASE_DEVICE_INPUT_H_INCLUDED
#define ORZ_BASE_DEVICE_INPUT_H_INCLUDED

#include "orz_base_math.h"

namespace Orz
{
	struct InputButton
	{
		InputButton():is_button_down(0),
		sign_start_time(0), sign_end_time(0),
		is_last_down(0), is_last_short_sign(true),
		is_mouse_over(false)
		{};

		void Contact(bool IsButtonDown);

		bool is_button_down;

		// 消息 and 状态
		ControlMessage control_message;
		ControlState control_state;

		// DoContact 记录用消息
		unsigned long sign_start_time, sign_end_time;
		bool is_last_down, is_last_short_sign;
		bool is_mouse_over;
	};

	class _DeviceInput
	{
	private:
		friend class _Platform;
		friend class _Device;

		// 设备初始化
		bool Init();

		// 从计算机获取输入
		void Contact(InputKeyCode which_key, bool is_input_down);
		void ContactWheel(int mouse_wheel);

	public:

		// 用户获取输入
		bool GetButton(InputKeyCode which_key);
		int GetMouseWheel();
		ControlMessage GetButtonMessage(InputKeyCode which_key);

	private:
		int mouse_x, mouse_y;
		InputButton button[KEY_MAX + 1];
		int wheel_delta;
	};
}

#endif