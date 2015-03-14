
#include "orz_animate.h"
#include "orz_base_time.h"
#include "orz_log.h"
#include "orz_base_public_resource.h"

namespace Orz
{
	Animate::Animate():
	BaseUi(ELEMENT_TYPE_UI_ANIMATE, 0.0f),
	is_use_angle_and_center_to_draw(false),
	is_loop(true),
	total_time(0), total_frame(0), curr_frame(0), begin_time(0),
	solo_frame_width(0), solo_frame_height(0),
	animate_angle(0.0f), animate_flip_mode(FLIP_MODE_NONE)
	{
		animate_center.x = 0.5f;
		animate_center.y = 0.5f;
	}

	void Animate::DoContact(void)
	{
	}

	void Animate::DoContactReset(void)
	{
		begin_time = 0;
	}

	void Animate::DoChangeAlpha(uint8_t Alpha)
	{
		image.ChangeAlpha(Alpha);
	}

    bool Animate::LoadAnimate(const char *AnimateName, const char* NamePath, const Rect &AnimateRect)
    {
		bool success(true);
		element_name = AnimateName;
        FILE *fp;

        fp = fopen(NamePath, "r");

        if(fp == NULL)
        {
            error_out("Animate::LoadAnimate - 打开文件\""+std::string(NamePath)+"\"出错!");
            success = false;
        }
		else
		{
			char buff[255];
			char var[255];

			// 读取纹理路径
			if (fgets(buff, 254, fp) == NULL)
			{
				error_out("Animate::LoadAnimate - 打开文件\""+std::string(NamePath)+"\"出错!");
				success = false;
			}
			else
			{
				// 获取纹理路径
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

				// 读取纹理
				if(!image.LoadromFile(var))
				{
					error_out("BaseTexture::LoadFromFile - 创建纹理失败!");
				}

				// 读取总帧数
				if (fgets(buff, 254, fp) == NULL)
				{
					// 就只有1帧
					total_frame = 1;
					total_time = 1000;
				} 
				else
				{

					for(int i=0; buff[i]&&i<254; i++)
					{
						if(buff[i] == '=')
						{
							sscanf(buff + i + 1, "%ld", &total_frame);
						}
					}

					// 读取总时间
					if (fgets(buff, 254, fp) == NULL)
					{
						error_out("Animate::LoadAnimate - 打开文件\""+std::string(NamePath)+"\"出错!");
						success = false;
					}
					else
					{
						for(int i=0; buff[i]&&i<254; i++)
						{
							if(buff[i] == '=')
							{
								sscanf(buff + i + 1, "%ld", &total_time);
								if(total_time == 0)
								{
									total_time = 1000;
									std::string err = "错误!:"+element_name+ "的播放时间为 0 (可能发生除零错误),错误, 已修改为1000ms!";
									error_out(err);
								}
								break;
							}
						}
					}// end 读取总时间

				}// end 读取总帧数

				// 根据帧数确定宽高
				if (total_frame != 0)
				{
					solo_frame_width = image.GetWidth()/total_frame;
					solo_frame_height = image.GetHeight();
				}
				else
				{
					width = image.GetWidth();
				}
				height = image.GetHeight();

			}// end 读取纹理路径
		}// end fopen

		ChangePosition(AnimateRect.x, AnimateRect.y);
		ChangeSize(AnimateRect.w, AnimateRect.h);

        fclose(fp);
        return true;
    }

    Animate& Animate::ChangeBlendModeToNone()
    {
		image.ChangeBlendMode(SDL_BLENDMODE_NONE);
		return *this;
    }

    Animate& Animate::ChangeBlendModeToAlpha()
    {
		image.ChangeBlendMode(SDL_BLENDMODE_BLEND);
		return *this;
    }

    Animate& Animate::ChangeBlendModeToAdd()
    {
		image.ChangeBlendMode(SDL_BLENDMODE_ADD);
		return *this;
    }

    Animate& Animate::ChangeBlendModeToMod()
    {
		image.ChangeBlendMode(SDL_BLENDMODE_MOD);
		return *this;
    }

	Animate& Animate::ChangeToEnableAdvanceAttribute()
	{
		is_use_angle_and_center_to_draw = true;
		return *this;
	}

	Animate& Animate::ChangeToDisableAdvanceAttribute()
	{
		is_use_angle_and_center_to_draw = false;
		return *this;
	}

	Animate& Animate::ChangeAngle(float Angle)
	{
		animate_angle = Angle;
		return *this;
	}

	Animate& Animate::ChangeCenter(Point &Center)
	{
		animate_center = Center;
		return *this;
	}

	Animate& Animate::ChangeFlipMode(FlipMode Mode)
	{
		animate_flip_mode = Mode;
		return *this;
	}

	void Animate::DoDraw(const Rect& DrawRect)
	{
		float scale;
		// source_rect
		Rect source_rect;
		Rect dest_rect;// = {x, y, width, height};
		curr_frame = total_frame * ((GetTickTime() - begin_time) % total_time) / total_time;
		source_rect.x = solo_frame_width * curr_frame;
		source_rect.y = 0;
		source_rect.w = solo_frame_width;
		source_rect.h = solo_frame_height;


		switch(element_render_style)
		{
		case ELEMENT_RENDER_STYLE_ADAPT:
			if((float)width/height > (float)solo_frame_width/solo_frame_height)
			{
				scale = (float)height/solo_frame_height;
				dest_rect.y = y;
				dest_rect.x = (width - scale * solo_frame_width) * 0.5;
			}
			else
			{
				scale = (float)width/solo_frame_width;
				dest_rect.x = x;
				dest_rect.y = (height - scale * solo_frame_height) * 0.5;
			}
			dest_rect.w = scale * solo_frame_width;
			dest_rect.h = scale * solo_frame_height;
			break;

		case ELEMENT_RENDER_STYLE_FILL:
			if((float)width/height < (float)solo_frame_width/solo_frame_height)
			{
				scale = (float)height/solo_frame_height;
				dest_rect.y = y;
				dest_rect.x = (width -solo_frame_width * scale) * 0.5;
			}
			else
			{
				scale = (float)width/solo_frame_width;
				dest_rect.x = x;
				dest_rect.y = (height - solo_frame_height * scale) * 0.5;
			}
			dest_rect.w = scale * solo_frame_width;
			dest_rect.h = scale * solo_frame_height;
			break;

		case ELEMENT_RENDER_STYLE_FULL:
			dest_rect.x = x;
			dest_rect.y = y;
			dest_rect.w = width;
			dest_rect.h = height;
			break;
		}

		dest_rect.x = DrawRect.x;
		dest_rect.y = DrawRect.y;
		if (is_use_angle_and_center_to_draw)
		{
			image.RenderEx(source_rect, dest_rect, animate_angle, animate_center, SDL_FLIP_NONE);
		}
		else
		{
			image.Render(source_rect, dest_rect);
		}
	}

}
