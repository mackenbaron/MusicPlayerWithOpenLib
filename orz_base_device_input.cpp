
#include "orz_base_device_input.h"
#include "orz_base_time.h"

namespace Orz
{
	// 初始化
	bool _DeviceInput::Init()
	{
		wheel_delta = 0;

		return true;
	}

	// 触发输入
	void _DeviceInput::Contact(InputKeyCode which_key, bool is_input_down)
	{
		button[which_key].is_button_down = is_input_down;
		button[which_key].last_time = GetTickTime();
		//if(is_input_down)
		//{
		//	switch(which_key)
		//	{
		//	default: break;
		//	}
		//}
		//else
		//{
		//	switch(which_key)
		//	{
		//	default: break;
		//	}
		//}
	}

	void _DeviceInput::ContactWheel(int mouse_wheel)
	{
		wheel_delta = mouse_wheel;
	}

	// 获取输入
	bool _DeviceInput::GetButton(InputKeyCode which_key)
	{
		if((KEY_MIN<which_key)&&(which_key<KEY_MAX))
		{
			return button[which_key].is_button_down;
		}
		else
			return false;
	}

	int _DeviceInput::GetMouseWheel()
	{
		return wheel_delta;
	}
}