
#ifndef ORZ_BASE_DEVICE_INPUT_H_INCLUDED
#define ORZ_BASE_DEVICE_INPUT_H_INCLUDED

#include "orz_base_math.h"

namespace Orz
{
	struct InputButton
	{
		InputButton():is_button_down(0), last_time(0) {};

		bool is_button_down;
		unsigned int last_time;
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

	private:
		int mouse_x, mouse_y;
		InputButton button[KEY_MAX + 1];
		int wheel_delta;
	};
}

#endif