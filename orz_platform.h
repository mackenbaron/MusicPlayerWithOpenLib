#ifndef ORZ_PLATFORM_H_INCLUDED
#define ORZ_PLATFORM_H_INCLUDED

#include <SDL.h>
#include <string>

namespace Orz
{
    class Platform
    {
	private:
		friend class Management;
		friend class Root;

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

    private:
    };
}



#endif // ORZ_PLATFORM_H_INCLUDED
