
#ifndef ORZ_BASE_SDL_H_INCLUDED
#define ORZ_BASE_SDL_H_INCLUDED

#include <SDL.h>
#include <string>
#include "orz_base_texture.h"

namespace Orz
{
    class BaseSDL
    {
		friend class _Manager;
		friend class _Platform;
		friend class _Device;
		friend class BaseTexture;

		// ��ʼ��
		bool Init(void);

	public:
		~BaseSDL();

        // ��������
        bool CreateWindow(const std::string &WindowName, int Width, int Height);

        // ����ȫ������
        bool CreateFullscreenWindow(const std::string &WindowName, int Width, int Height);

		// ������Ⱦ����ɫ
		void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        // ����
        void ClearRender();
        void ClearRender(const SDL_Color &c);
        void ClearRender(Uint8 r, Uint8 g, Uint8 b);

        void DrawPoint(const SDL_Color &c, int x, int y);
        void DrawPoint(Uint8 r, Uint8 g, Uint8 b, int x, int y);

        void DrawLine(const SDL_Color &c, int x1, int y1, int x2, int y2);
        void DrawLine(Uint8 r, Uint8 g, Uint8 b, int x1, int y1, int x2, int y2);

		void DrawFillRect(const SDL_Color &c, SDL_Rect &fill_rect);
		void DrawOutlineRect(const SDL_Color &c, SDL_Rect &outline_rect);

		// ������Ʒ���
		// ����͸���Ĵ�ɫ����
		void DrawAlphaSolidColor(const SDL_Color &c, Uint8 alpha,SDL_Rect &dest_rect);

		// �����ӿ�
		void SetViewport(const SDL_Rect &ViewportRect);
		void SetViewportToDefault(void);

	private:

        // ��Ⱦ��
		SDL_Renderer *render;

		// ���ֻ���
		void Present(void);
		bool DoTheThingsAfterCreateWindow();

        // SDL ����
        SDL_Window *window;

		// ������Ʒ�����ɫ�����õ�������
		BaseTexture solid_color_texture;
    };
}

#endif // ORZ_SDL_H_INCLUDED
