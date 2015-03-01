
#include "orz_base_public_resource.h"
#include "orz_device.h"
#include "orz_base_time.h"

namespace Orz
{

	// 初始化
	bool Device::Init()
	{
		wheel_delta = 0;

		return true;
	}

	// 触发输入
	void Device::Contact(KEY_CODE which_key, bool is_input_down)
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

	void Device::ContactWheel(int mouse_wheel)
	{
		wheel_delta = mouse_wheel;
	}

	// 获取输入
	bool Device::GetButton(KEY_CODE which_key)
	{
		if((KEY_MIN<which_key)&&(which_key<KEY_MAX))
		{
			return button[which_key].is_button_down;
		}
		else
			return false;
	}

	int Device::GetMouseWheel()
	{
		return wheel_delta;
	}

	void Device::ClearRender()
	{
		sdl.ClearRender();
	}

	void Device::ClearRender(uint8_t r, uint8_t g, uint8_t b)
	{
		sdl.ClearRender(r, g, b);
	}

	void Device::DrawPoint(const Color &c, int x, int y){sdl.DrawPoint(c, x, y);}
	void Device::DrawPoint(uint8_t r, uint8_t g, uint8_t b, int x, int y){sdl.DrawPoint(r, g, b, x, y);}

	void Device::DrawLine(const SDL_Color &c, int x1, int y1, int x2, int y2){sdl.DrawLine(c, x1, y1, x2, y2);}
	void Device::DrawLine(uint8_t r, uint8_t g, uint8_t b, int x1, int y1, int x2, int y2){sdl.DrawLine(r, g, b, x1, y1, x2, y2);}

	void Device::Present(void){sdl.Present();}
}
