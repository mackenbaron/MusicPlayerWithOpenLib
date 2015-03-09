
#ifndef _ORZ_BASE_TEXTURE_H_INCLUDED
#define _ORZ_BASE_TEXTURE_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>

namespace Orz
{
	class BaseTexture
	{
	public:
		// ���캯��
		BaseTexture();

		// ��������
		~BaseTexture();

		// ���ƹ��캯��
		BaseTexture(const BaseTexture& Source);

		// ���ƺ���
		BaseTexture& operator=(BaseTexture& Source);

		// �ͷ�����
		void Free(void);

		// ��������
		bool LoadromFile(const char* FilePath);
		bool LoadFromTextUTF8(TTF_Font* Font, const char* Text, SDL_Color Color);

		// �ֶ���������
		bool CreateTargetAbleTexture(int Width, int Height);
		bool CreateLockAbleTexture(int Width, int Height);
		bool CreateUnlockAbleTexture(int Width, int Height);

		// �����������Ϊ��ȾĿ��,�������� CreateTargetAbleTexture �����������������
		void ChangeAsRenderTarget();

		// �ı�͸����
		BaseTexture& ChangeAlpha(uint8_t Alpha); // 0 - 255 ( 0 - ���ɼ�, 255 - ��͸��)
		BaseTexture& ChangeColorModulation( Uint8 red, Uint8 green, Uint8 blue );
		BaseTexture& ChangeBlendMode( SDL_BlendMode blending );

		// ��ȡ��С
		int GetWidth(void);
		int GetHeight(void);
		BaseTexture& GetSizeWidth(int &Width);
		BaseTexture& GetSizeHeight(int &Height);
		BaseTexture& GetSize(int &Width, int &Height);

		// ����
		void Render(int X, int Y);
		void Render(int X, int Y, float Scale);
		void Render(const SDL_Rect& SourceRect, const SDL_Rect& DestRect);
		void RenderEx(const SDL_Rect& SourceRect, const SDL_Rect& DestRect, const double Angle, SDL_Point& Center, SDL_RendererFlip FlipMod);

	private:
		// ת�ƿ���Ȩ
		void MoveControlRightTo(BaseTexture *new_controler);
		SDL_Texture* texture;
		int texture_width, texture_height;
	};
}

#endif