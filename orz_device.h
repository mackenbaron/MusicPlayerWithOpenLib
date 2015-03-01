
#ifndef ORZ_DEVICE_H_INCLUDED
#define ORZ_DEVICE_H_INCLUDED

#include "orz_base_math.h"
#include "orz_base_zplay.h"

namespace Orz
{
	enum KEY_CODE
	{
		KEY_MIN = 0,
		KEY_MOUSE_LEFT,
		KEY_MOUSE_MIDDLE,
		KEY_MOUSE_RIGHT,

		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,

		KEY_LSHIFT,
		KEY_RSHIFT,

		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,

		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,

		KEY_MAX
	};

	struct InputButton
	{
		InputButton():is_button_down(0), last_time(0) {};

		bool is_button_down;
		unsigned int last_time;
	};

	class Device
	{
	private:
		friend class Management;
		friend class Root;

		// 设备初始化
		bool Init();

	public:
		// 获取输入
		void Contact(KEY_CODE which_key, bool is_input_down);
		void ContactWheel(int mouse_wheel);
		bool GetButton(KEY_CODE which_key);
		int GetMouseWheel();

		// 呈现图像
		void ClearRender();
		void ClearRender(uint8_t r, uint8_t g, uint8_t b);

		void DrawPoint(const Color &c, int x, int y);
		void DrawPoint(uint8_t r, uint8_t g, uint8_t b, int x, int y);

		void DrawLine(const SDL_Color &c, int x1, int y1, int x2, int y2);
		void DrawLine(uint8_t r, uint8_t g, uint8_t b, int x1, int y1, int x2, int y2);

		void Present(void);

		// 音频设备
		BaseZPlay sound;

	private:
		int mouse_x, mouse_y;
		InputButton button[KEY_MAX + 1];
		int wheel_delta;
	};
}

#endif