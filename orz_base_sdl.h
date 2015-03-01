
#ifndef ORZ_SDL_H_INCLUDED
#define ORZ_SDL_H_INCLUDED

#include <SDL.h>
#include <string>
#include "orz_base_texture.h"

namespace Orz
{
    struct BaseSDL
    {
    public:
		friend class Platform;
		~BaseSDL();

		// 初始化
		bool Init(void);

        // 创建窗口
        bool CreateWindow(const std::string &WindowName, int Width, int Height);

        // 创建全屏窗口
        bool CreateFullscreenWindow(const std::string &WindowName, int Width, int Height);

		// 设置渲染器颜色
		void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        // 绘制
        void ClearRender();
        void ClearRender(const SDL_Color &c);
        void ClearRender(Uint8 r, Uint8 g, Uint8 b);

        void DrawPoint(const SDL_Color &c, int x, int y);
        void DrawPoint(Uint8 r, Uint8 g, Uint8 b, int x, int y);

        void DrawLine(const SDL_Color &c, int x1, int y1, int x2, int y2);
        void DrawLine(Uint8 r, Uint8 g, Uint8 b, int x1, int y1, int x2, int y2);

		void DrawFillRect(const SDL_Color &c, SDL_Rect &fill_rect);
		void DrawOutlineRect(const SDL_Color &c, SDL_Rect &outline_rect);

		// 特殊绘制方案
		// 绘制透明的纯色背景
		void DrawAlphaSolidColor(SDL_Color &c, Uint8 alpha,SDL_Rect &dest_rect);

		// 设置视口
		void SetViewport(SDL_Rect &ViewportRect);
		void SetViewportToDefault();

		// 呈现画面
        void Present(void);
        // 渲染器
        SDL_Renderer *render;
	private:
        // SDL 窗口
        SDL_Window *window;

		// 特殊绘制方案纯色背景用到的纹理
		BaseTexture solid_color_texture;
    };
}

#endif // ORZ_SDL_H_INCLUDED
