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

		// 平台初始化
        bool Init();

    public:

		// 创建窗口
        bool CreateWindow(const std::string &WindowName, int Width, int Height);
		bool CreateFullscreenWindow(const std::string &WindowName, int Width, int Height);

		// 处理系统事件
        void DealSystemMessage(SDL_Event &event);

		// 获取窗口大小
		void GetWindowSize(int &w, int &h);

		// 获取鼠标位置
		void GetMousePosition(int &x, int &y);

		// 是否有文件要打开
		bool IsHaveFileRequireOpen();
		int NumberOfFilePathThatRequireOpen();

		// 获得要打开的文件
		void GetPathOfFileThatRequireOpen(std::string &FilePath);

		// 设置应用程序路径当前路径
		bool SetCurrentPathOfThisProgramGBK(std::string &FilePath);

		// 获取应用程序路径
		bool GetPathOfThisProgramGBK(std::string &FilePath);

		// 设置 DLL 文件路径
		bool SetPathOfDLLGBK(std::string &FilePath);

    private:
		// 要打开的文件
		std::vector<std::string> drag_and_open_file_path_list;
    };
}



#endif // ORZ_PLATFORM_H_INCLUDED
