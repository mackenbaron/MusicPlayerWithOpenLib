
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

			case SDL_DROPFILE:
				{
					// 获取数据
					drag_and_open_file_path_list.push_back(event.drop.file);

					// 释放空间( SDL 指明这是必须的)
					SDL_free(event.drop.file);
				}

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

	bool Platform::IsHaveFileRequireOpen()
	{
		if (drag_and_open_file_path_list.empty())
			return false;

		return true;
	}

	int Platform::NumberOfFilePathThatRequireOpen()
	{
		return drag_and_open_file_path_list.size();
	}

	void Platform::GetPathOfFileThatRequireOpen(std::string &FilePath)
	{
		if (drag_and_open_file_path_list.empty())
			return;

		FilePath = drag_and_open_file_path_list.back();
		drag_and_open_file_path_list.pop_back();
	}

}
