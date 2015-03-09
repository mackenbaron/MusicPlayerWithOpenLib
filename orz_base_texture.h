
#ifndef _ORZ_BASE_TEXTURE_H_INCLUDED
#define _ORZ_BASE_TEXTURE_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>

namespace Orz
{
	class BaseTexture
	{
	public:
		// 构造函数
		BaseTexture();

		// 析构函数
		~BaseTexture();

		// 复制构造函数
		BaseTexture(const BaseTexture& Source);

		// 复制函数
		BaseTexture& operator=(BaseTexture& Source);

		// 释放纹理
		void Free(void);

		// 加载纹理
		bool LoadromFile(const char* FilePath);
		bool LoadFromTextUTF8(TTF_Font* Font, const char* Text, SDL_Color Color);

		// 手动创建纹理
		bool CreateTargetAbleTexture(int Width, int Height);
		bool CreateLockAbleTexture(int Width, int Height);
		bool CreateUnlockAbleTexture(int Width, int Height);

		// 设置这个纹理为渲染目标,必须是由 CreateTargetAbleTexture 函数创建的纹理才行
		void ChangeAsRenderTarget();

		// 改变透明度
		BaseTexture& ChangeAlpha(uint8_t Alpha); // 0 - 255 ( 0 - 不可见, 255 - 不透明)
		BaseTexture& ChangeColorModulation( Uint8 red, Uint8 green, Uint8 blue );
		BaseTexture& ChangeBlendMode( SDL_BlendMode blending );

		// 获取大小
		int GetWidth(void);
		int GetHeight(void);
		BaseTexture& GetSizeWidth(int &Width);
		BaseTexture& GetSizeHeight(int &Height);
		BaseTexture& GetSize(int &Width, int &Height);

		// 绘制
		void Render(int X, int Y);
		void Render(int X, int Y, float Scale);
		void Render(const SDL_Rect& SourceRect, const SDL_Rect& DestRect);
		void RenderEx(const SDL_Rect& SourceRect, const SDL_Rect& DestRect, const double Angle, SDL_Point& Center, SDL_RendererFlip FlipMod);

	private:
		// 转移控制权
		void MoveControlRightTo(BaseTexture *new_controler);
		SDL_Texture* texture;
		int texture_width, texture_height;
	};
}

#endif