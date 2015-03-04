
#include "orz_base_sdl.h"
#include "orz_log.h"
#include <SDL_image.h>
#include <string>

// ������Ʒ���������
#define SOLID_TEXTURE_SIZE 1

namespace Orz
{
	// ��������
	BaseSDL::~BaseSDL()
	{
		// ������Ⱦ��
		SDL_DestroyRenderer(render);
		render = 0;

		// ���ٴ���
		SDL_DestroyWindow(window);
		window = 0;

		// �˳�
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();

	}

	bool BaseSDL::Init(void)
	{
		bool result(true);

		// ��ʼ�� SDL
		if(SDL_Init(SDL_INIT_VIDEO))
		{
			error_out("��ʼ�� SDL_Init ʧ��!");
			result = false;
		}
		else
		{
			//Set texture filtering to linear
			SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
		}

		return result;
	}

	// ��������
	bool BaseSDL::CreateWindow(const std::string &WindowName, int Width, int Height)
	{
		bool succeed(true);

		// ��������
		window = SDL_CreateWindow(WindowName.c_str(),
						SDL_WINDOWPOS_UNDEFINED,    // ���ڵ�X����
						SDL_WINDOWPOS_UNDEFINED,    // ���ڵ�Y����
						Width, Height,
						NULL);//SDL_WINDOW_SHOWN);//|SDL_WINDOW_FULLSCREEN //BORDERLESS);     // ����Ϊ�ޱ߿򴰿ڡ�ȫ��


		// ����Ƿ�ɹ�
		if(window == NULL)
		{
			error_out("BaseSDL::CreateWindow - ��������ʧ��!");
			succeed =  false;
		}

		succeed = DoTheThingsAfterCreateWindow();

		return succeed;
	}

	// ��������
	bool BaseSDL::CreateFullscreenWindow(const std::string &WindowName, int Width, int Height)
	{
		bool succeed(true);

		// ��������
		window = SDL_CreateWindow(WindowName.c_str(),
						SDL_WINDOWPOS_UNDEFINED,    // ���ڵ�X����
						SDL_WINDOWPOS_UNDEFINED,    // ���ڵ�Y����
						Width, Height,
						SDL_WINDOW_FULLSCREEN);     // ����Ϊ�ޱ߿򴰿ڡ�ȫ��


		// ����Ƿ�ɹ�
		if(window == NULL)
		{
			error_out("BaseSDL::CreateFullscreenWindow - ��������ʧ��!");
			succeed = false;
		}

		succeed = DoTheThingsAfterCreateWindow();

		return succeed;
	}

	void BaseSDL::ClearRender()
	{
		SDL_SetRenderDrawColor(render, 0xF1, 0x5A, 0x22, 0xFF );
		SDL_RenderClear(render);
	}

	void BaseSDL::ClearRender(const SDL_Color &c)
	{
		SDL_SetRenderDrawColor(render, c.r, c.g, c.b,0xFF);
		SDL_RenderClear(render);
	}

	void BaseSDL::ClearRender(Uint8 r, Uint8 g, Uint8 b)
	{
		SDL_SetRenderDrawColor(render, r, g, b, 0xFF );
		SDL_RenderClear(render);
	}

	void BaseSDL::DrawPoint(const SDL_Color &c, int x, int y)
	{
		SDL_SetRenderDrawColor(render, c.r, c.g, c.b,0xFF);
		SDL_RenderDrawPoint(render, x, y);
	}

	void BaseSDL::DrawPoint(Uint8 r, Uint8 g, Uint8 b, int x, int y)
	{
		SDL_SetRenderDrawColor(render, r, g, b,0xFF);
		SDL_RenderDrawPoint(render, x, y);
	}

	void BaseSDL::DrawLine(const SDL_Color &c, int x1, int y1, int x2, int y2)
	{
		SDL_SetRenderDrawColor(render, c.r, c.g, c.b,0xFF);
		SDL_RenderDrawLine(render, x1, y1, x2, y2);
	}

	void BaseSDL::DrawLine(Uint8 r, Uint8 g, Uint8 b, int x1, int y1, int x2, int y2)
	{
		SDL_SetRenderDrawColor(render, r, g, b, 0xFF );
		SDL_RenderDrawLine(render, x1, y1, x2, y2);
	}

	void BaseSDL::DrawFillRect(const SDL_Color &c, SDL_Rect &fill_rect)
	{
		SDL_SetRenderDrawColor(render, c.r, c.g, c.b, c.a);
		SDL_RenderFillRect( render, &fill_rect );
	}

	void BaseSDL::DrawOutlineRect(const SDL_Color &c, SDL_Rect &outline_rect)
	{
		SDL_SetRenderDrawColor(render, c.r, c.g, c.b, c.a);
		SDL_RenderDrawRect( render, &outline_rect );
	}

	void BaseSDL::DrawAlphaSolidColor(SDL_Color &c, Uint8 alpha,SDL_Rect &dest_rect)
	{
		// �����ȾĿ��
		solid_color_texture.SetAsRenderTarget();

		// ��Ⱦ��Ӧ��ɫ
		SDL_SetRenderDrawColor(render, c.r, c.g, c.b, c.a);
		SDL_RenderDrawPoint(render,0,0);

		// ��ȾĿ��תΪĬ��
		SDL_SetRenderTarget(render, NULL);
		SDL_Rect source_rect = {0, 0, SOLID_TEXTURE_SIZE, SOLID_TEXTURE_SIZE};
		solid_color_texture.SetAlpha(alpha);
		SDL_RenderCopy(render, solid_color_texture.GetTexture(), &source_rect, &dest_rect);
	}

	void BaseSDL::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		SDL_SetRenderDrawColor(render, r, g, b, a);
	}

	void BaseSDL::SetViewport(SDL_Rect &ViewportRect)
	{
		SDL_RenderSetViewport(render, &ViewportRect);
	}

	void BaseSDL::SetViewportToDefault()
	{
		SDL_RenderSetViewport(render, NULL);
	}

	void BaseSDL::Present(void)
	{
		SDL_RenderPresent(render);
	}

	bool BaseSDL::DoTheThingsAfterCreateWindow()
	{
		// ��ʼ����Ⱦ��
		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		// ��ʼ����Ⱦ����ɫ
		SDL_SetRenderDrawColor(render, 0XFF, 0XF, 0XF, 0XFF);

		// �������ƹ����õ�����
		solid_color_texture.CreateTargetTexture(SOLID_TEXTURE_SIZE, SOLID_TEXTURE_SIZE);
		solid_color_texture.SetBlendMode(SDL_BLENDMODE_BLEND);

		// ��ʼ��SDLͼƬ֧��
		IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

		// ��ʼ��TTF
		if(TTF_Init() == -1)
		{
			error_out("��ʼ�� TTF_Init ʧ��!");
			return false;
		}

		// ��SDL�Ĵ�����ק���ļ�����
		SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

		return true;
	}

}










