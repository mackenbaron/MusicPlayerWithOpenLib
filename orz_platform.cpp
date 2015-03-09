
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
		// �����¼�
		device.input.ContactWheel(0);

		// �����¼�
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{

			// �����¼�
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					break;
				default: break;
				}break;


			// ����¼�
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
					// ��ȡ����
					drag_and_open_file_path_list.push_back(ConvertTextFromeUTF8oGBKT(event.drop.file));

					// �ͷſռ�( SDL ָ�����Ǳ����)
					SDL_free(event.drop.file);
				}

			// �����¼�
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
		// �������óɹ����ط� 0 ֵ
		if (SetCurrentDirectoryA(FilePath.c_str()) == 0)
		{
			Orz::error_out("Platform::SetPathOfThisProgramGBK:δ�ɹ����ô˳���ĵ�ǰ�ļ�·��");
			std::cout<<"windows������Ϣ:"<<GetLastError()<<std::endl;
			return false;
		}

		return true;
	}

	bool _Platform::GetPathOfThisProgramGBK(std::string &FilePath)
	{
		// ��ȡ�˳�����ļ�·��
		bool succeed(true);
		char this_program_path[MAX_PATH];

		// ����ֵ���ַ�������, ���� 0 ��ζ��ʧ��
		DWORD result = GetModuleFileNameA(NULL, this_program_path, MAX_PATH);

		if (result == 0)
		{
			Orz::error_out("Platform::GetPathOfThisProgramGBK:δ�ɹ���ô˳�����ļ�·��");
			std::cout<<"windows������Ϣ:"<<GetLastError()<<std::endl;
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
		// �������óɹ����ط� 0 ֵ
		if (SetDllDirectoryA(FilePath.c_str()) == 0)
		{
			Orz::error_out("Platform::SetPathOfDLLGBK - δ�ɹ����ô˳���� DLL �ļ�·��");
			std::cout<<"windows������Ϣ:"<<GetLastError()<<std::endl;
			return false;
		}

		return true;
	}

}
