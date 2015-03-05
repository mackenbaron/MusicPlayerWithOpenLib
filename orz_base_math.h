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

	enum ControlMessage
	{
		CONTROL_MESSAGE_FUNCTION_ERROR,

		CONTROL_MESSAGE_MOUSE_OUT,	// 鼠标在控件外
		CONTROL_MESSAGE_MOUSE_OVER,	// 鼠标在控件内
		CONTROL_MESSAGE_MOUSE_CONST_DOWN,	// 鼠标在控件内|持续按下
		CONTROL_MESSAGE_MOUSE_CONST_DOWN_END,// 鼠标在控件内|持续按下结束消息
		CONTROL_MESSAGE_MOUSE_CLICK,		// 鼠标在控件内|单击
		CONTROL_MESSAGE_MOUSE_DOUBLE_CLICK	// 鼠标在控件内|双击
	};

	enum ControlState
	{
		CONTROL_STATE_MOUSE_OVER,
		CONTROL_STATE_MOUSE_OUT,
		CONTROL_STATE_MOUSE_DOWN
	};

	// 此值与读取的文件有关联,这里写什么,文件里就跟着来,必须亲自注明数值!!!
	// 每一组设置一个默认 例如 Control
	enum SpriteState
	{
		SPRITE_STATE_DEFAULT = 0,

		SPRITE_STATE_CONTROL_MOUSE_OUT	= SPRITE_STATE_DEFAULT, // 为 0
		SPRITE_STATE_CONTROL_MOUSE_OVER	= 1,
		SPRITE_STATE_CONTROL_MOUSE_DOWN	= 2,

	};


	enum ElementRenderStyle
	{
		ELEMENT_RENDER_STYLE_FULL,	// 铺满
		ELEMENT_RENDER_STYLE_FILL	// 填充
	};

	enum ControlBackgroundStyle
	{
		SOLID_COLOR, // 纯色
		TEXTURE // 图片背景
	};

	enum InputKeyCode
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
