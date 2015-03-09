#ifndef ORZ_PLATFORM_H_INCLUDED
#define ORZ_PLATFORM_H_INCLUDED

#include <SDL.h>
#include <string>
#include <vector>

namespace Orz
{
    class _Platform
    {
	private:
		friend class _Manager;

		// ƽ̨��ʼ��
        bool Init();

    public:

		// ��������
        bool CreateWindow(const std::string &WindowName, int Width, int Height);
		bool CreateFullscreenWindow(const std::string &WindowName, int Width, int Height);

		// ����ϵͳ�¼�
        void DealSystemMessage(SDL_Event &event);

		// ��ȡ���ڴ�С
		void GetWindowSize(int &w, int &h);

		// ��ȡ���λ��
		void GetMousePosition(int &x, int &y);

		// �Ƿ����ļ�Ҫ��
		bool IsHaveFileRequireOpen();
		int NumberOfFilePathThatRequireOpen();

		// ���Ҫ�򿪵��ļ�
		void GetPathOfFileThatRequireOpen(std::string &FilePath);

		// ����Ӧ�ó���·����ǰ·��
		bool SetCurrentPathOfThisProgramGBK(std::string &FilePath);

		// ��ȡӦ�ó���·��
		bool GetPathOfThisProgramGBK(std::string &FilePath);

		// ���� DLL �ļ�·��
		bool SetPathOfDLLGBK(std::string &FilePath);

    private:
		// Ҫ�򿪵��ļ�
		std::vector<std::string> drag_and_open_file_path_list;
    };
}



#endif // ORZ_PLATFORM_H_INCLUDED
