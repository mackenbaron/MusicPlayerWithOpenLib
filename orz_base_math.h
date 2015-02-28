#ifndef ORZ_BASE_MATH_H_INCLUDED
#define ORZ_BASE_MATH_H_INCLUDED

#include <SDL.h>

namespace Orz
{
    enum FlipMod
    {
        FLIP_NONE = SDL_FLIP_NONE,
        FLIP_LEFT_RIGHT = SDL_FLIP_HORIZONTAL,
        FLIP_TOP_DOWN = SDL_FLIP_VERTICAL
	};

	enum ControlDirect
	{
		CONTROL_DIRECT_UP_DOWN,
		CONTROL_DIRECT_LEFT_RIGHT
	};

	// 不能重复!!!!
	enum ControlState
	{
		CONTROL_MOUSE_OUT=0,
		CONTROL_MOUSE_OVER=1,
		CONTROL_MOUSE_DOWN=2
	};
	// 紧跟上面,保持队形!!!
	enum SpriteState
	{
		CONTROL_BUTTON_MOUSE_OUT=CONTROL_MOUSE_OUT,
		CONTROL_BUTTON_MOUSE_OVER=CONTROL_MOUSE_OVER,
		CONTROL_BUTTON_MOUSE_DOWN=CONTROL_MOUSE_DOWN,

		CONTROL_BAR_MOUSE_OUT = CONTROL_MOUSE_OUT,
		CONTROL_BAR_MOUSE_OVER = CONTROL_MOUSE_OVER,
		CONTROL_BAR_MOUSE_DOWN = CONTROL_MOUSE_DOWN
	};

	enum ControlMessage
	{
		FUNCTION_ERROR,

		MOUSE_OVER,  // 鼠标在控件内
		MOUSE_OUT,   // 鼠标在控件外
		MOUSE_CONST_DOWN,    // 鼠标在控件内|持续按下
		MOUSE_CONST_DOWN_END,     // 鼠标在控件内|持续按下结束消息
		MOUSE_CLICK,      // 鼠标在控件内|单击
		MOUSE_DOUBLE_CLICK // 鼠标在控件内|双击
	};

	enum ControlBackgroundStyle
	{
		SOLID_COLOR, // 纯色
		TEXTURE // 图片背景
	};

	struct MusicTimeTable
	{
		unsigned int hour, minute, second, millisecond;
		unsigned int GetTotalTimeBySecond()
		{
			return hour*3600 + minute*60 + second;
		}

		MusicTimeTable& SetTimeBySecond(unsigned int Second)
		{
			hour = Second / 3600;
			Second -= hour * 3600;

			minute = Second / 60;
			Second -= minute * 60;

			second = Second;

			return *this;
		}
	};

    typedef SDL_Rect Rect;
    typedef SDL_Point Point;
    typedef SDL_Color Color; // r g b a
    typedef SDL_Texture Texture;
    typedef SDL_Renderer Renderer;
}

#endif // ORZ_BASE_MATH_H_INCLUDED
