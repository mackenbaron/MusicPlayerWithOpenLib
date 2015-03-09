
#include "orz_platform.h"
#include "orz_base_public_resource.h"
//#include "orz_base_private_resource.h"

#include <Windows.h>
#undef CreateWindow

namespace Orz
{
	bool _Platform::Init()
	{
		return true;
	}

	bool _Platform::CreateWindow(const std::string &WindowName, int Width, int Height)
	{
		return device.display.CreateWindow(WindowName, Width, Height);
	}

	bool _Platform::CreateFullscreenWindow(const std::string &WindowName, int Width, int Height)
	{
		return device.display.CreateFullscreenWindow(WindowName, Width, Height);
	}

	void _Platform::DealSystemMessage(SDL_Event &event)
	{
		// 消灭事件
		device.input.ContactWheel(0);

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
						device.input.Contact(KEY_MOUSE_LEFT, true);

				}break;

			case SDL_MOUSEBUTTONUP:
				{
					if(event.button.button == SDL_BUTTON_LEFT)
						device.input.Contact(KEY_MOUSE_LEFT, false);
				}break;

			case SDL_MOUSEWHEEL:
				{
					device.input.ContactWheel(event.wheel.y);
				}break;

			case SDL_DROPFILE:
				{
					// 获取数据
					drag_and_open_file_path_list.push_back(ConvertTextFromeUTF8oGBKT(event.drop.file));

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

	void _Platform::GetMousePosition(int &x, int &y)
	{
		SDL_GetMouseState(&x, &y);
	}

	void _Platform::GetWindowSize(int &w, int &h)
	{
		SDL_GetWindowSize(device.display.window, &w, &h);
	}

	bool _Platform::IsHaveFileRequireOpen()
	{
		if (drag_and_open_file_path_list.empty())
			return false;

		return true;
	}

	int _Platform::NumberOfFilePathThatRequireOpen()
	{
		return drag_and_open_file_path_list.size();
	}

	void _Platform::GetPathOfFileThatRequireOpen(std::string &FilePath)
	{
		if (drag_and_open_file_path_list.empty())
			return;

		FilePath = drag_and_open_file_path_list.back();
		drag_and_open_file_path_list.pop_back();
	}

	bool _Platform::SetCurrentPathOfThisProgramGBK(std::string &FilePath)
	{
		// 函数调用成功返回非 0 值
		if (SetCurrentDirectoryA(FilePath.c_str()) == 0)
		{
			Orz::error_out("Platform::SetPathOfThisProgramGBK:未成功设置此程序的当前文件路径");
			std::cout<<"windows错误消息:"<<GetLastError()<<std::endl;
			return false;
		}

		return true;
	}

	bool _Platform::GetPathOfThisProgramGBK(std::string &FilePath)
	{
		// 获取此程序的文件路径
		bool succeed(true);
		char this_program_path[MAX_PATH];

		// 返回值是字符串长度, 返回 0 意味着失败
		DWORD result = GetModuleFileNameA(NULL, this_program_path, MAX_PATH);

		if (result == 0)
		{
			Orz::error_out("Platform::GetPathOfThisProgramGBK:未成功获得此程序的文件路径");
			std::cout<<"windows错误消息:"<<GetLastError()<<std::endl;
			succeed = false;
		}
		else
		{
			int index = 0;
			int last_slash_position = 0;

			for (index = 0; index < result && this_program_path[index]; index++)
			{
				if (this_program_path[index] == '\\')
				{
					last_slash_position = index;
				}
			}

			this_program_path[last_slash_position + 1] = 0;

			FilePath = this_program_path;
		}

		return succeed;
	}

	bool _Platform::SetPathOfDLLGBK(std::string &FilePath)
	{
		// 函数调用成功返回非 0 值
		if (SetDllDirectoryA(FilePath.c_str()) == 0)
		{
			Orz::error_out("Platform::SetPathOfDLLGBK - 未成功设置此程序的 DLL 文件路径");
			std::cout<<"windows错误消息:"<<GetLastError()<<std::endl;
			return false;
		}

		return true;
	}

}
