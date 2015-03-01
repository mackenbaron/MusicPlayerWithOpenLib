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

	// �����ظ�!!!!
	enum ControlState
	{
		CONTROL_MOUSE_OUT=0,
		CONTROL_MOUSE_OVER=1,
		CONTROL_MOUSE_DOWN=2
	};
	// ��������,���ֶ���!!!
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

		MOUSE_OVER,  // ����ڿؼ���
		MOUSE_OUT,   // ����ڿؼ���
		MOUSE_CONST_DOWN,    // ����ڿؼ���|��������
		MOUSE_CONST_DOWN_END,     // ����ڿؼ���|�������½�����Ϣ
		MOUSE_CLICK,      // ����ڿؼ���|����
		MOUSE_DOUBLE_CLICK // ����ڿؼ���|˫��
	};

	enum ControlBackgroundStyle
	{
		SOLID_COLOR, // ��ɫ
		TEXTURE // ͼƬ����
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
