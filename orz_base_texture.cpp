
#include "orz_base_texture.h"
#include "orz_base_public_resource.h"
#include <SDL_image.h>

namespace Orz
{
	BaseTexture::BaseTexture():
	texture(NULL),
	texture_width(0), texture_height(0)
	{
		
	}

	BaseTexture::BaseTexture(const BaseTexture& Source)
	{
		const_cast<BaseTexture&>(Source).MoveControlRightTo(this);
	}

	BaseTexture& BaseTexture::operator=(BaseTexture& Source)
	{
		Source.MoveControlRightTo(this);
		return *this;
	}

	void BaseTexture::Free(void)
	{
		if (texture)
		{
			SDL_DestroyTexture(texture);
			texture = NULL;
		}

		texture_width = 0;
		texture_height = 0;
	}

	BaseTexture::~BaseTexture()
	{
		Free();
	}

	bool BaseTexture::LoadromFile(const char* FilePath)
	{
		bool success(true);
		
		// 清除已经存在的纹理
		Free();

		// 加载纹理
		SDL_Surface *new_surface = IMG_Load(FilePath);

		if (new_surface == NULL)
		{
			error_out("BaseTexture::LoadromFile - 无法从\""+std::string(FilePath)+"\"读取纹理");
			success = false;
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(device.display.render, new_surface);

			if (texture == NULL)
			{
				error_out("BaseTexture::LoadromFile - 无法用表面创建纹理");
				success = false;
			}
			else
			{
				texture_width = new_surface->w;
				texture_height = new_surface->h;
			}

			// 释放表面
			SDL_FreeSurface(new_surface);
		}

		return success;
	}

	bool BaseTexture::LoadFromTextUTF8(TTF_Font* Font, const char* Text, SDL_Color Color)
	{
		bool success(true);

		// 清除已经存在的纹理
		Free();

		SDL_Surface *new_surface = TTF_RenderUTF8_Blended(Font, Text, Color);

		if (new_surface == NULL)
		{
			error_out("BaseTexture::LoadFromTextUTF8 - 用\""+std::string(Text)+"\"创建文字表面");
			success = false;
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(device.display.render, new_surface);

			if (texture == NULL)
			{
				error_out("BaseTexture::LoadFromTextUTF8 - 无法用表面创建纹理");
				success = false;
			}
			else
			{
				texture_width = new_surface->w;
				texture_height = new_surface->h;
			}

			// 释放表面
			SDL_FreeSurface(new_surface);
		}

		return success;
	}

	bool BaseTexture::CreateTargetAbleTexture(int Width, int Height)
	{
		bool success(true);

		// 释放已经存在的纹理
		Free();

		texture = SDL_CreateTexture( device.display.render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width, Height );
		if( texture == NULL )
		{
			error_out("BaseTexture::CreateTargetAbleTexture - 无法创建纹理");
			success = false;
		}
		else
		{
			texture_width = Width;
			texture_height = Height;
		}

		return success;
	}

	bool BaseTexture::CreateLockAbleTexture(int Width, int Height)
	{
		bool success(true);

		// 释放已经存在的纹理
		Free();

		texture = SDL_CreateTexture( device.display.render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, Width, Height );
		if( texture == NULL )
		{
			error_out("BaseTexture::CreateLockAbleTexture - 无法创建纹理");
			success = false;
		}
		else
		{
			texture_width = Width;
			texture_height = Height;
		}

		return success;
	}

	bool BaseTexture::CreateUnlockAbleTexture(int Width, int Height)
	{
		bool success(true);

		// 释放已经存在的纹理
		Free();

		texture = SDL_CreateTexture( device.display.render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, Width, Height );
		if( texture == NULL )
		{
			error_out("BaseTexture::CreateUnlockAbleTexture - 无法创建纹理");
			success = false;
		}
		else
		{
			texture_width = Width;
			texture_height = Height;
		}

		return success;
	}

	void BaseTexture::ChangeAsRenderTarget()
	{
		if(SDL_SetRenderTarget(device.display.render, texture) != 0)
		{
			error_out( "BaseTexture::SetAsRenderTarget - 无法重定向渲染目标!");
		}
	}

	BaseTexture& BaseTexture::ChangeAlpha(uint8_t Alpha)
	{
		SDL_SetTextureAlphaMod(texture, Alpha);
		return *this;
	}

	BaseTexture& BaseTexture::ChangeColorModulation(Uint8 red, Uint8 green, Uint8 blue)
	{
		SDL_SetTextureColorMod( texture, red, green, blue );
		return *this;
	}

	BaseTexture& BaseTexture::ChangeBlendMode(SDL_BlendMode blending)
	{
		SDL_SetTextureBlendMode( texture, blending );
		return *this;
	}

	BaseTexture& BaseTexture::GetSize(int &Width, int &Height)
	{
		Width = texture_width;
		Height = texture_height;
		return *this;
	}

	BaseTexture& BaseTexture::GetSizeWidth(int &Width)
	{
		Width = texture_width;
		return *this;
	}

	BaseTexture& BaseTexture::GetSizeHeight(int &Height)
	{
		Height = texture_height;
		return *this;
	}

	void BaseTexture::Render(int X, int Y)
	{
		SDL_Rect ts = {0,0,texture_width, texture_height};
		SDL_Rect td = {X,Y,texture_width, texture_height};

		SDL_RenderCopy( device.display.render, texture, &ts, &td);
	}

	void BaseTexture::Render(int X, int Y, float Scale)
	{
		SDL_Rect ts = {0,0,texture_width, texture_height};
		SDL_Rect td = {X,Y,texture_width*Scale, texture_height*Scale};

		SDL_RenderCopy( device.display.render, texture, &ts, &td);
	}

	void BaseTexture::Render(const SDL_Rect& SourceRect, const SDL_Rect& DestRect)
	{
		SDL_RenderCopy( device.display.render, texture, &SourceRect, &DestRect);
		//SDL_RenderCopy( device.display.render, texture, NULL, &DestRect);
	}

	void BaseTexture::RenderEx(const SDL_Rect& SourceRect, const SDL_Rect& DestRect, const double Angle, SDL_Point& Center, SDL_RendererFlip FlipMod)
	{
		SDL_RenderCopyEx(device.display.render, texture,
			&SourceRect, &DestRect,
			Angle, &Center, FlipMod);
	}

	void BaseTexture::MoveControlRightTo(BaseTexture *new_controler)
	{
		if(new_controler != this)
		{
			// 清空原有数据
			new_controler->Free();

			// 传递数据
			new_controler->texture = this->texture;
			new_controler->texture_width = this->texture_width ;
			new_controler->texture_height = this->texture_height;

			// 清除控制权
			this->texture = NULL;
			Free();
		}
	}

	int BaseTexture::GetWidth(void)
	{
		return texture_width;
	}

	int BaseTexture::GetHeight(void)
	{
		return texture_height;
	}


}