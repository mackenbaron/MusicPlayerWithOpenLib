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

    private:
    };
}



#endif // ORZ_PLATFORM_H_INCLUDED
