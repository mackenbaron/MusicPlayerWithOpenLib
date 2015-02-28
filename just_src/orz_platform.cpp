
#include "orz_platform.h"
#include "orz_base_public_resource.h"

namespace Orz
{
	bool Platform::Init()
	{
		return true;
	}

	bool Platform::CreateWindow(const std::string &WindowName, int Width, int Height)
	{
		return sdl.CreateWindow(WindowName, Width, Height);
	}

	bool Platform::CreateFullscreenWindow(const std::string &WindowName, int Width, int Height)
	{
		return sdl.CreateFullscreenWindow(WindowName, Width, Height);
	}

	void Platform::DealSystemMessage(SDL_Event &event)
	{
		// 消灭事件
		device.ContactWheel(0);

		// 激活事件
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{

			// 键盘事件
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					break;
				default: break;
				}break;


			// 鼠标事件
			case SDL_MOUSEBUTTONDOWN:
				{
					if(event.button.button == SDL_BUTTON_LEFT)
						device.Contact(KEY_MOUSE_LEFT, true);

				}break;

			case SDL_MOUSEBUTTONUP:
				{
					if(event.button.button == SDL_BUTTON_LEFT)
						device.Contact(KEY_MOUSE_LEFT, false);
				}break;

			case SDL_MOUSEWHEEL:
				{
					device.ContactWheel(event.wheel.y);
				}break;

			// 其他事件
			default:
				{
				}break;
			}
		}
	}

	void Platform::GetMousePosition(int &x, int &y)
	{
		SDL_GetMouseState(&x, &y);
	}

	void Platform::GetWindowSize(int &w, int &h)
	{
		SDL_GetWindowSize(sdl.window, &w, &h);
	}

}
