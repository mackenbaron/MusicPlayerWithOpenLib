#ifndef ORZ_BASE_TEXTURE_H_INCLUDED
#define ORZ_BASE_TEXTURE_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace Orz
{
	// 警告:此类的指针使用单一控制权的方案!!!
    class BaseTexture
    {
	public:
		// 构造函数
		BaseTexture();

		// 析构函数
		~BaseTexture();

		//Loads image at specified path
		bool CreateFromFile(std::string path);

		//Creates image from font string
		bool CreateFromRenderedText(TTF_Font* font, const char* textureText, SDL_Color textColor ); // 内码:unicode 编码方式: utf-8

		// 手动创建纹理
		bool CreateTargetTexture(int width, int height);
		bool CreateLockAbleTexture(int width, int height);
		bool CreateUnlockAbleTexture(int width, int height);

		//Deallocates texture
		void Free();

		//Set color modulation
		void SetColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void SetBlendMode( SDL_BlendMode blending );

		// 设置透明度/可见度(0 -255)
		// ( 0 - 不可见, 255 - 不透明)
		void SetAlpha( Uint8 alpha );

		// 设置这个纹理为渲染目标
		void SetAsRenderTarget();

		//Renders texture at given point
		void Draw(int X, int Y);
		void Draw(int X, int Y, float Rate);

		void Render(const SDL_Rect& SourceRect, const SDL_Rect& DestRect);
		void RenderEx(const SDL_Rect& SourceRect, const SDL_Rect& DestRect, const double Angle, SDL_Point& Center, SDL_RendererFlip FlipMod);

		// 获得基本信息
		SDL_Texture* GetTexture(void);
		int GetWidth(void);
		int GetHeight(void);

		// 复制构造函数
		BaseTexture(const BaseTexture& source);

		// 复制函数
		BaseTexture& operator=(BaseTexture& source);

    private:
		// 转移控制权
		void MoveControlRightTo(BaseTexture *new_controler);
			
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
    };
}
#endif // ORZ_BASE_TEXTURE_H_INCLUDED
