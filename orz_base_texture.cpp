
#include "orz_base_texture.h"

#include <SDL_image.h>
#include "orz_log.h"
#include "orz_option.h"
#include "orz_base_public_resource.h"

namespace Orz
{
	BaseTexture::BaseTexture()
	{
		mTexture = NULL;
		Free();
	}

	BaseTexture::BaseTexture(const BaseTexture& source)
	{
		const_cast<BaseTexture&>(source).MoveControlRightTo(this);
	}

	BaseTexture::~BaseTexture()
	{
		//Deallocate
		Free();
	}

	bool BaseTexture::CreateFromFile(std::string path)
	{
		bool success = true;

		//Get rid of preexisting texture
		Free();

		//The final texture
		SDL_Texture* newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
		if( loadedSurface == NULL )
		{
			std::string err = "无法读取纹理\""+path+"\"";
			error_out(err);
			success = false;
		}
		else
		{
			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface( sdl.render, loadedSurface );
			if( newTexture == NULL )
			{
				std::string err = "无法从\""+path+"\"创建纹理! ";
				error_out(err);
				success = false;
			}
			else
			{
				//Get image dimensions
				mWidth = loadedSurface->w;
				mHeight = loadedSurface->h;
			}

			//Get rid of old loaded surface
			SDL_FreeSurface( loadedSurface );
		}

		SetBlendMode(SDL_BLENDMODE_NONE);

		//Return success
		mTexture = newTexture;
		return success;
	}

	bool BaseTexture::CreateFromRenderedText(TTF_Font* font, const char* textureText, SDL_Color textColor )
	{
		//Get rid of preexisting texture
		Free();

		// case 1
		SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, textureText, textColor);

		// case 2
		//SDL_Color text_background_color_key = {TextColorKeyR, TextColorKeyG, TextColorKeyB, 0xFF};
		//SDL_Surface* textSurface = TTF_RenderUTF8_Shaded(font, textureText, textColor, text_background_color_key);

		// case 3
		//SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, textureText, textColor);

		if( textSurface == NULL )
		{
			long address;
			char buff[255];
			sprintf(buff, "%p 文本:[%s]", &address, textureText);
			error_out("BaseTexture::CreateFromRenderedText -- 无法用文字"+std::string(textureText)+"获得表面(surface)\n目标纹理地址:" + buff);
		}
		else
		{
			// case 2
			// 设置颜色值
			//if(SDL_SetColorKey(textSurface, SDL_TRUE, SDL_MapRGB(textSurface->format, TextColorKeyR, TextColorKeyG, TextColorKeyB)) != 0)
			//{
			//	error_out("BaseTexture::CreateFromRenderedText - 无法设置颜色值");
			//}

			//Create texture from surface pixels
			mTexture = SDL_CreateTextureFromSurface( sdl.render, textSurface );

			if( mTexture == NULL )
			{
				error_out("BaseTexture::CreateFromRenderedText -- 无法用表面(surfac)创建纹理(texture)");
			}
			else
			{
				//Get image dimensions
				mWidth = textSurface->w;
				mHeight = textSurface->h;
			}

			//Get rid of old surface
			SDL_FreeSurface( textSurface );
		}

		//Return success
		return mTexture != NULL;
	}

	bool BaseTexture::CreateTargetTexture(int width, int height)
	{
		//Free();

		//Create uninitialized texture
		mTexture = SDL_CreateTexture( sdl.render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height );
		if( mTexture == NULL )
		{
			printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			mWidth = width;
			mHeight = height;
		}

		return mTexture != NULL;
	}

	bool BaseTexture::CreateLockAbleTexture(int width, int height)
	{
		Free();

		//Create uninitialized texture
		mTexture = SDL_CreateTexture( sdl.render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height );
		if( mTexture == NULL )
		{
			printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			mWidth = width;
			mHeight = height;
		}

		return mTexture != NULL;
	}

	bool BaseTexture::CreateUnlockAbleTexture(int width, int height)
	{
		Free();

		//Create uninitialized texture
		mTexture = SDL_CreateTexture( sdl.render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height );
		if( mTexture == NULL )
		{
			printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			mWidth = width;
			mHeight = height;
		}

		return mTexture != NULL;
	}

	void BaseTexture::MoveControlRightTo(BaseTexture *new_controler)
	{
		if(new_controler != this)
		{
			// 传递数据
			new_controler->mTexture = mTexture;
			new_controler->mWidth = mWidth;
			new_controler->mHeight = mHeight;

			// 清除控制权
			mTexture = NULL;
			Free();
		}
	}

	void BaseTexture::Free()
	{
		//Free texture if it exists
		if( mTexture != NULL )
		{
			SDL_DestroyTexture( mTexture );
		}

		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}

	void BaseTexture::SetColor( Uint8 red, Uint8 green, Uint8 blue )
	{
		//Modulate texture rgb
		SDL_SetTextureColorMod( mTexture, red, green, blue );
	}

	void BaseTexture::SetBlendMode( SDL_BlendMode blending )
	{
		//Set blending function
		SDL_SetTextureBlendMode( mTexture, blending );
	}

	void BaseTexture::SetAlpha( Uint8 alpha )
	{
		//Modulate texture alpha
		SDL_SetTextureAlphaMod( mTexture, alpha );
	}

	void BaseTexture::SetAsRenderTarget()
	{
		if (mTexture)
		{
			if(SDL_SetRenderTarget(sdl.render, mTexture) != 0)
			{
				long address;
				char buff[16];
				sprintf(buff, "%p", &address);
				error_out( "BaseTexture::SetAsRenderTarget - 无法重定向渲染目标!\n"+std::string("目标纹理地址:") + buff);
			}
		}

	}

	void BaseTexture::Draw(int X, int Y)
	{
		SDL_Rect ts = {0,0,mWidth, mHeight};
		SDL_Rect td = {X,Y,mWidth, mHeight};

		//Render to screen
		SDL_RenderCopy( sdl.render, mTexture, &ts, &td);
	}

	void BaseTexture::Draw(int X, int Y, float Rate)
	{
		SDL_Rect ts = {0,0,mWidth, mHeight};
		SDL_Rect td = {X,Y,mWidth*Rate, mHeight*Rate};

		//Render to screen
		SDL_RenderCopy( sdl.render, mTexture, &ts, &td);
	}


	SDL_Texture* BaseTexture::GetTexture(void){return mTexture;}
	int BaseTexture::GetWidth(void){return mWidth;}
	int BaseTexture::GetHeight(void){return mHeight;}

	// 复制函数
	BaseTexture& BaseTexture::operator=(BaseTexture& source)
	{
		source.MoveControlRightTo(this);
		return *this;
	}

}




