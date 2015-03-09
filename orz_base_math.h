#ifndef ORZ_BASE_MATH_H_INCLUDED
#define ORZ_BASE_MATH_H_INCLUDED

#include <SDL.h>

namespace Orz
{
	enum ControlDirect
	{
		CONTROL_DIRECT_UP_DOWN,
		CONTROL_DIRECT_LEFT_RIGHT
	};

	enum ControlMessage
	{
		CONTROL_MESSAGE_FUNCTION_ERROR,			

		CONTROL_MESSAGE_MOUSE_OUT,				// ����ڿؼ���
		CONTROL_MESSAGE_MOUSE_OVER,				// ����ڿؼ���
		CONTROL_MESSAGE_MOUSE_CONST_DOWN,		// ����ڿؼ��� with ������
		CONTROL_MESSAGE_MOUSE_CONST_DOWN_END,	// ����ڿؼ��� with ����������
		CONTROL_MESSAGE_MOUSE_CLICK,			// ����ڿؼ��� with ����
		CONTROL_MESSAGE_MOUSE_DOUBLE_CLICK		// ����ڿؼ��� with ˫��
	};

	enum ControlState
	{
		CONTROL_STATE_MOUSE_OVER,
		CONTROL_STATE_MOUSE_OUT,
		CONTROL_STATE_MOUSE_DOWN
	};

	enum UiMessage
	{
		UI_MESSAGE_FUNCTION_ERROR
	};

	// ��ֵ���ȡ���ļ�˳���й���,����дʲô,�ļ���͸�����.
	// ��������ע��ÿһ����ֵ!!!
	// ÿһ������һ��Ĭ�� ���� Control
	enum UiState
	{
		UI_STATE_DEFAULT = 0,

		UI_STATE_MOUSE_OVER = UI_STATE_DEFAULT,
		UI_STATE_MOUSE_OUT = 1,
		UI_STATE_MOUSE_DOWN = 2
	};

	enum ElementType
	{
		ELEMENT_TYPE_BASE, // base, ʵ�ʲ�������
		ELEMENT_TYPE_ROOT,
		ELEMENT_TYPE_ERROR,

		ELEMENT_TYPE_TEXTURE,

		ELEMENT_TYPE_BASE_UI, // base, ʵ�ʲ�������
		ELEMENT_TYPE_UI_ANIMATE,
		ELEMENT_TYPE_UI_ANIMATE_SPRITE,
		ELEMENT_TYPE_UI_ONE_LINE_WRITER,
		ELEMENT_TYPE_UI_WRITER,

		ELEMENT_TYPE_BASE_UI_CONTROL, // base, ʵ�ʲ�������
		ELEMENT_TYPE_UI_CONTROL_VIRTUAL,
		ELEMENT_TYPE_UI_CONTROL_CANVAS,
		ELEMENT_TYPE_UI_CONTROL_TEXT,
		ELEMENT_TYPE_UI_CONTROL_BUTTON,
		ELEMENT_TYPE_UI_CONTROL_SCROLL_BAR,
		ELEMENT_TYPE_UI_CONTROL_LIST,
	};

	enum ElementMessage
	{
		ELEMENT_MESSAGE_ERROR
	};

	enum ElementState
	{
		ELEMENT_STATE_ERROR,
		ELEMENT_STATE_NONE,
		ELEMENT_STATE_CONTACT
	};

	enum ElementRenderStyle
	{
		ELEMENT_RENDER_STYLE_ADAPT,	// ��Ӧ
		ELEMENT_RENDER_STYLE_FILL,	// ���
		ELEMENT_RENDER_STYLE_FULL	// ����
	};

	enum FlipMode
	{
		FLIP_MODE_NONE = SDL_FLIP_NONE,
		FLIP_MODE_LEFT_RIGHT = SDL_FLIP_HORIZONTAL,
		FLIP_MODE_TOP_DOWN = SDL_FLIP_VERTICAL
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
