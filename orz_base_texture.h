#ifndef ORZ_BASE_TEXTURE_H_INCLUDED
#define ORZ_BASE_TEXTURE_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace Orz
{
	// ����:�����ָ��ʹ�õ�һ����Ȩ�ķ���!!!
    class BaseTexture
    {
	public:
		// ���캯��
		BaseTexture();

		// ��������
		~BaseTexture();

		//Loads image at specified path
		bool CreateFromFile(std::string path);

		//Creates image from font string
		bool CreateFromRenderedText(TTF_Font* font, const char* textureText, SDL_Color textColor ); // ����:unicode ���뷽ʽ: utf-8

		// �ֶ���������
		bool CreateTargetTexture(int width, int height);
		bool CreateLockAbleTexture(int width, int height);
		bool CreateUnlockAbleTexture(int width, int height);

		//Deallocates texture
		void Free();

		//Set color modulation
		void SetColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void SetBlendMode( SDL_BlendMode blending );

		// ����͸����/�ɼ���(0 -255)
		// ( 0 - ���ɼ�, 255 - ��͸��)
		void SetAlpha( Uint8 alpha );

		// �����������Ϊ��ȾĿ��
		void SetAsRenderTarget();

		//Renders texture at given point
		void Draw(int X, int Y);
		void Draw(int X, int Y, float Rate);

		void Render(const SDL_Rect& SourceRect, const SDL_Rect& DestRect);
		void RenderEx(const SDL_Rect& SourceRect, const SDL_Rect& DestRect, const double Angle, SDL_Point& Center, SDL_RendererFlip FlipMod);

		// ��û�����Ϣ
		SDL_Texture* GetTexture(void);
		int GetWidth(void);
		int GetHeight(void);

		// ���ƹ��캯��
		BaseTexture(const BaseTexture& source);

		// ���ƺ���
		BaseTexture& operator=(BaseTexture& source);

    private:
		// ת�ƿ���Ȩ
		void MoveControlRightTo(BaseTexture *new_controler);
			
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
    };
}
#endif // ORZ_BASE_TEXTURE_H_INCLUDED
