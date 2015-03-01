
#include "orz_animate.h"
#include "orz_base_time.h"
#include "orz_log.h"
#include "orz_option.h"
#include "orz_base_public_resource.h"

namespace Orz
{
	Animate::Animate():
	name(""),
	width(0),
	height(0),
	is_loop(0), is_show(0),
	total_time(0), curr_time(0), total_frame(0), curr_frame(0), begin_time(0)
	{
	}

	Animate::Animate(const char *NamePath)
	{
		LoadAnimate(NamePath);
	}

	Animate::~Animate()
	{
	}

	Animate& Animate::Contact(void)
	{
		curr_time = GetTickTime();
		return *this;
	}

	void Animate::ContactReset(void)
	{
		begin_time = 0;
	}

	void Animate::SetAlpha(int Alpha)
	{
		image.SetAlpha(Alpha);
	}

    void Animate::Draw(int x, int y, float scale)
    {
        curr_frame = total_frame * ((curr_time - begin_time) % total_time) / total_time;

        source_rect.x = width * curr_frame;
        source_rect.y = 0;
        source_rect.w = width;
        source_rect.h = height;

        dest_rect.x = x;
        dest_rect.y = y;
        dest_rect.w = scale * width;
        dest_rect.h = scale * height;

        SDL_RenderCopy(sdl.render, image.GetTexture(), &source_rect, &dest_rect);
    }

	void Animate::Draw(Rect &DestRect)
	{
		float scale;
		if((float)DestRect.w/DestRect.h > (float)width/height)
		{
			scale = (float)DestRect.h/height;
			dest_rect.y = DestRect.y;

			dest_rect.x = DestRect.x + (DestRect.w - scale * width)/2;
		}
		else
		{
			scale = (float)DestRect.w/width;
			dest_rect.x = DestRect.x;

			dest_rect.y = DestRect.y + (DestRect.h - scale * height)/2;
		}

		dest_rect.w = scale * width;
		dest_rect.h = scale * height;

		curr_frame = total_frame * ((curr_time - begin_time) % total_time) / total_time;

		source_rect.x = width * curr_frame;
		source_rect.y = 0;
		source_rect.w = width;
		source_rect.h = height;

		SDL_RenderCopy(sdl.render, image.GetTexture(), &source_rect, &dest_rect);

		#ifdef CodeDebug
			SDL_SetRenderDrawColor(sdl.render, 255, 10, 20, 0xFF );		
			SDL_RenderDrawRect(sdl.render, &DestRect);
		#endif
	}

	void Animate::DrawFill(Rect &DestRect)
	{
		//float scale;
		//if((float)DestRect.w/DestRect.h < (float)width/height)
		//{
		//	scale = (float)DestRect.h/height;
		//	dest_rect.y = DestRect.y;

		//	dest_rect.x = DestRect.x + (DestRect.w - scale * width)/2;
		//}
		//else
		//{
		//	scale = (float)DestRect.w/width;
		//	dest_rect.x = DestRect.x;

		//	dest_rect.y = DestRect.y + (DestRect.h - scale * height)/2;
		//}

		//dest_rect.w = scale * width;
		//dest_rect.h = scale * height;

		//curr_frame = total_frame * ((curr_time - begin_time) % total_time) / total_time;

		//source_rect.x = width * curr_frame;
		//source_rect.y = 0;
		//source_rect.w = width;
		//source_rect.h = height;

		//SDL_RenderCopy(sdl.render, image.GetTexture(), &source_rect, &dest_rect);

		//#ifdef CodeDebug
		//SDL_SetRenderDrawColor(sdl.render, 255, 10, 20, 0xFF );		
		//SDL_RenderDrawRect(sdl.render, &DestRect);
		//#endif

		float scale;
		curr_frame = total_frame * ((curr_time - begin_time) % total_time) / total_time;
		source_rect.x = width * curr_frame;
		source_rect.y = 0;

		if((float)DestRect.w/DestRect.h < (float)width/height)
		{
			scale = (float)height/DestRect.h;

			source_rect.w = DestRect.w * scale;
			source_rect.h = height;

			source_rect.x += (width - DestRect.w * scale) * 0.5;
		}
		else
		{
			scale = (float)width/DestRect.w;

			source_rect.w = width;
			source_rect.h = DestRect.h * scale;

			source_rect.y += (height - DestRect.h * scale) * 0.5;
		}


		SDL_RenderCopy(sdl.render, image.GetTexture(), &source_rect, &DestRect);

		#ifdef CodeDebug
		SDL_SetRenderDrawColor(sdl.render, 255, 10, 20, 0xFF );		
		SDL_RenderDrawRect(sdl.render, &DestRect);
		#endif
	}

    void Animate::DrawEx(int x, int y, float scale, float angle, Point *center, FlipMod flip_mod)
    {
        curr_frame = total_frame * ((curr_time - begin_time) % total_time) / total_time;

        source_rect.x = width * curr_frame;
        source_rect.y = 0;
        source_rect.w = width;
        source_rect.h = height;

        dest_rect.x = x;
        dest_rect.y = y;
        dest_rect.w = scale * width;
        dest_rect.h = scale * height;

        if(center)
            SDL_RenderCopyEx(sdl.render, image.GetTexture(), &source_rect, &dest_rect, angle, center, (SDL_RendererFlip)flip_mod);
        else
        {
            Point temp_center = {width/2, height/2};
            SDL_RenderCopyEx(sdl.render, image.GetTexture(), &source_rect, &dest_rect, angle, &temp_center, (SDL_RendererFlip)flip_mod);
        }
    }

	void Animate::DrawEx(int x, int y, float width_scale, float height_scale, float angle, Point *center)
	{
		curr_frame = total_frame * ((curr_time - begin_time) % total_time) / total_time;

		source_rect.x = width * curr_frame;
		source_rect.y = 0;
		source_rect.w = width;
		source_rect.h = height;

		dest_rect.x = x;
		dest_rect.y = y;
		dest_rect.w = width_scale * width;
		dest_rect.h = height_scale * height;

		SDL_RenderCopyEx(sdl.render, image.GetTexture(), &source_rect, &dest_rect, angle, center, SDL_FLIP_NONE);

	}

    bool Animate::LoadAnimate(const char* NamePath)
    {
        FILE *fp;

        fp = fopen(NamePath, "r");

        if(fp == NULL)
        {
            error_out("Animate::LoadAnimate - 打开文件\""+std::string(NamePath)+"\"出错!");
            return false;
        }

        char buff[255];
        char var[255];

        // 读取名称
        fgets(buff, 254, fp);
        for(int i=0; buff[i]&&i<254; i++)
        {
            if(buff[i] == '\"')
            {
                char* p = buff+i+1;
                int j = 0;
                for(; p[j]&&p[j]!='\"';j++)
                {
                    var[j] = p[j];
                }
                var[j] = 0;

                break;
            }
        }
        name = var;


        // 读取纹理路径
        fgets(buff, 254, fp);
        for(int i=0; buff[i]&&i<254; i++)
        {
            if(buff[i] == '\"')
            {
                char* p = buff+i+1;
                int j = 0;
                for(; p[j]&&p[j]!='\"';j++)
                {
                    var[j] = p[j];
                }
                var[j] = 0;

                break;
            }
        }

        if(!image.CreateFromFile(var))
        {
            error_out("BaseTexture::LoadFromFile - 创建纹理失败!");
            return false;
        }


        // 读取总帧数
        fgets(buff, 254, fp);
        for(int i=0; buff[i]&&i<254; i++)
        {
            if(buff[i] == '=')
            {
                sscanf(buff + i + 1, "%ld", &total_frame);
            }
        }
        // 确定宽高
        width = image.GetWidth()/total_frame;
        height = image.GetHeight();



        // 读取总时间
        fgets(buff, 254, fp);
        for(int i=0; buff[i]&&i<254; i++)
        {
            if(buff[i] == '=')
            {
                sscanf(buff + i + 1, "%ld", &total_time);
                if(total_time == 0)
                {
                    total_time = 1000;
                    std::string err = "错误!:"+name + "的播放时间为 0 (可能发生除零错误),错误, 已修改为1000ms!";
                    error_out(err);
                }
                break;
            }
        }

        fclose(fp);
        return true;
    }
    void Animate::SetBlendModeToAlpha()
    {
        image.SetBlendMode(SDL_BLENDMODE_BLEND);
    }
    void Animate::SetBlendModeToNone()
    {
        image.SetBlendMode(SDL_BLENDMODE_NONE);
    }
    void Animate::SetBlendModeToAdd()
    {
        image.SetBlendMode(SDL_BLENDMODE_ADD);
    }
    void Animate::SetBlendModeToMod()
    {
        image.SetBlendMode(SDL_BLENDMODE_MOD);
    }
}
