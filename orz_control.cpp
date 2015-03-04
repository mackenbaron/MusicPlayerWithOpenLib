
#include "orz_control.h"
#include "orz_base_time.h"
#include "orz_log.h"
#include "orz_base_public_resource.h"
#include <string>

namespace Orz
{
	//  文本控件------------------------------------------------------------------
	ControlText::ControlText():
	BaseControl(0, 0, 0, 0, SOLID_COLOR),
	is_transparent(false),
	control_alpha(255)
	{
		// 白色背景
		background_color.r = background_color.g = background_color.b = background_color.a = 255;
	}
	
	bool ControlText::CreateControlText(const char *ControlName, int X, int Y, int Width, int Height, const char *FontName, int FontSize, const char* Text, Color &TextColor, Color &BackgroundColor)
	{
		control_name = ControlName;
		Color black_color = {0,0,0,0};
		Rect temp_rect = {X, Y, Width, Height};
		text_writer.CreateWriter(FontName, Text, FontSize, TextColor, temp_rect);
		ChangePosition(X, Y);
		ChangeSize(Width, Height);

		background_color = BackgroundColor;

		return true;
	}

	ControlText& ControlText::ChangeText(std::string& Text)
	{
		text_writer.ChangeText(Text.c_str());
		return *this;
	}

	ControlText& ControlText::ChangePosition(int X, int Y)
	{
		x = X;
		y = Y;
		text_writer.ChangeTextPosition(X, Y);
		return *this;
	}

	ControlText& ControlText::ChangeSize(int Width, int Height)
	{
		width = Width;
		height = Height;
		text_writer.ChangeTextSize(Width, Height);
		return *this;
	}

	ControlText& ControlText::ChangeBackgroundColor(Color BackGroundColor)
	{
		background_color = BackGroundColor;
		return *this;
	}
	
	ControlText& ControlText::ChangeToNoBackground()
	{
		is_transparent = true;
		return *this;
	}
	
	ControlText& ControlText::ChangeToUseColorBackground()
	{
		is_transparent = false;
		return *this;
	}

	ControlText& ControlText::ChangeTextAlpha(uint8_t Alpha)
	{
		text_writer.ChangeAlpah(Alpha);
		return *this;
	}

	ControlText& ControlText::ChangeAlpha(uint8_t Alpha)
	{
		control_alpha = Alpha;
		ChangeTextAlpha(Alpha);
		return *this;
	}

	void ControlText::Draw()
	{
		if(is_show)
		{
			if(!is_transparent)
			{
				SDL_Rect fill_rect = { x, y, width, height };
				if(control_alpha == 255)
				{
					device.display.DrawFillRect(background_color, fill_rect);
				}
				else
				{
					device.display.DrawAlphaSolidColor(background_color, control_alpha, fill_rect);
				}
			}

			text_writer.Write();
		}
	}

	void ControlText::Draw(int X, int Y)
	{

		if(is_show)
		{
			if(!is_transparent)
			{
				SDL_Rect fill_rect = { X, Y, width, height };
				if(control_alpha == 255)
				{
					device.display.DrawFillRect(background_color, fill_rect);
				}
				else
				{
					device.display.DrawAlphaSolidColor(background_color, control_alpha, fill_rect);
				}
			}

			text_writer.Write(X, Y);
		}
	}

	// 按钮控件--------------------------------------------------------------
	ControlButton::ControlButton():
	BaseControl(0,0,0,0, SOLID_COLOR),
	is_show_text(true),
	is_solid_color_background(true),
	control_alpha(255)
	{
		background_color.r = background_color.g = background_color.b = background_color.a = 190;
	}

	bool ControlButton::CreateControlButton(int X, int Y, int Width, int Height, Color BackgroundColor)
	{
		ChangePosition(X, Y).ChangeSize(Width, Height).ChangeBackgroundColor(BackgroundColor).ChangeToUseSolidColorBackground();
		return true;
	}

	bool ControlButton::CreateControlButton(int X, int Y, int Width, int Height, Sprite &BackgroundSprite)
	{
		ChangePosition(X, Y).ChangeSize(Width, Height).ChangeBackgroundSprite(BackgroundSprite).ChangeToUseSpriteBackground();
		return true;
	}

	bool ControlButton::LoadControlButton(const char* PathName, int X, int Y)
	{
		bool succed = true;
		FILE *fp;
		fp = fopen(PathName, "r");

		if(fp != NULL)
		{
			char buff[255];
			char var[255];

			// 读取类型
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

			// 验证类型
			if (std::string("button") == var)
			{
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
				control_name = var;

				// 设置位置
				x = X;
				y = Y;

				// 读取位置
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%d", &width);
					}
				}
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%d", &height);
					}
				}

				// 读取精灵
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

				if (background_sprite.LoadSprite(var, x, y, width, height))
				{
					ChangeToUseSpriteBackground();
				}

			}else
			{
				error_out("ControlButton::LoadControlButton - \""+string(PathName)+"\"类型出错! - 非button!类型控件");
				succed = false;
			}
		}
		else
		{
			error_out("ControlButton::LoadControlButton - 打开\""+string(PathName)+"\"文件出错!");
			succed = false;
		}

		fclose(fp);
		return succed;
	}

	ControlButton& ControlButton::Contact(int MouseX, int MouseY, bool IsMouseDown)
	{
		// 本体
		BaseControl::Contact(MouseX, MouseY, IsMouseDown);

		// 精灵
		SpriteState curr_sprite_state;
		switch(GetState())
		{
		case CONTROL_STATE_MOUSE_OUT:
			curr_sprite_state = SPRITE_STATE_CONTROL_MOUSE_OUT;
			break;
		case CONTROL_STATE_MOUSE_OVER:
			curr_sprite_state = SPRITE_STATE_CONTROL_MOUSE_OVER;
			break;
		case CONTROL_STATE_MOUSE_DOWN:
			curr_sprite_state = SPRITE_STATE_CONTROL_MOUSE_DOWN;
			break;
		default:
			curr_sprite_state = SPRITE_STATE_DEFAULT;
		}
		background_sprite.Contact(curr_sprite_state);
	

		return *this;
	}

	ControlButton& ControlButton::ChangeText(std::string& Text)
	{
		text_writer.ChangeText(Text.c_str());
		return *this;
	}

	ControlButton& ControlButton::ChangePosition(int X, int Y)
	{
		x = X;
		y = Y;
		text_writer.ChangeTextPosition(X, Y);
		background_sprite.ChangePosition(X, Y);
		return *this;
	}

	ControlButton& ControlButton::ChangeSize(int Width, int Height)
	{
		width = Width;
		height = Height;
		text_writer.ChangeTextSize(Width, Height);
		background_sprite.ChangeSize(Width, Height);
		return *this;
	}

	ControlButton& ControlButton::ChangeBackgroundColor(Color BackGroundColor)
	{
		background_color = BackGroundColor;
		return *this;
	}

	ControlButton& ControlButton::ChangeBackgroundSprite(Sprite &BackgroundSprite)
	{
		background_sprite = BackgroundSprite;
		return *this;
	}

	ControlButton& ControlButton::ChangeAlpha(uint8_t Alpha)
	{
		control_alpha = Alpha;
		ChangeTextAlpha(Alpha).ChangeBackgroundAlpha(Alpha);
		background_sprite.SetAlpha(Alpha);
		return *this;
	}

	ControlButton& ControlButton::ChangeTextAlpha(uint8_t Alpha)
	{
		text_writer.ChangeAlpah(Alpha);
		return *this;
	}

	ControlButton& ControlButton::ChangeBackgroundAlpha(uint8_t Alpha)
	{
		background_sprite.SetAlpha(Alpha);
		return *this;
	}

	ControlButton& ControlButton::ChangeToUseSolidColorBackground()
	{
		is_solid_color_background = true;
		return *this;
	}

	ControlButton& ControlButton::ChangeToUseSpriteBackground()
	{
		is_solid_color_background = false;
		return *this;
	}

	void ControlButton::Draw()
	{
		if(is_show)
		{
			if(is_solid_color_background)
			{
				Rect fill_rect = { x, y, width, height };
				Color real_draw_color;
				bool is_draw_outline = false;
				
				switch(control_state)
				{
				case CONTROL_STATE_MOUSE_OUT:
					real_draw_color = background_color;
					break;
					
				case CONTROL_STATE_MOUSE_OVER:
					real_draw_color = background_color;
					is_draw_outline = true;
					real_draw_color.a = 255;
					real_draw_color.r = 255 - background_color.r;
					real_draw_color.b = 255 - background_color.b;
					real_draw_color.g = 255 - background_color.g;
					break;

				case CONTROL_STATE_MOUSE_DOWN:
					real_draw_color.a = 255;
					real_draw_color.r = 255 - background_color.r;
					real_draw_color.b = 255 - background_color.b;
					real_draw_color.g = 255 - background_color.g;
					break;
				}

				if(control_alpha == 255)
				{
					device.display.DrawFillRect(real_draw_color, fill_rect);
				}
				else
				{
					device.display.DrawAlphaSolidColor(real_draw_color, control_alpha, fill_rect);
				}

				if (is_draw_outline)
				{
					device.display.DrawOutlineRect(real_draw_color, fill_rect);
				}

			}
			else
			{
					Rect dest_rect = {x,y,width,height};
					background_sprite.Draw(dest_rect);
			}

			if(is_show_text)
			{
				text_writer.Write();
			}
		}
	}

	void ControlButton::DrawFill()
	{
		if(is_show)
		{
			if(is_solid_color_background)
			{
				Rect fill_rect = { x, y, width, height };
				Color real_draw_color;
				bool is_draw_outline = false;

				switch(control_state)
				{
				case SPRITE_STATE_CONTROL_MOUSE_OUT:
					real_draw_color = background_color;
					break;

				case SPRITE_STATE_CONTROL_MOUSE_OVER:
					real_draw_color = background_color;
					is_draw_outline = true;
					real_draw_color.a = 255;
					real_draw_color.r = 255 - background_color.r;
					real_draw_color.b = 255 - background_color.b;
					real_draw_color.g = 255 - background_color.g;
					break;

				case SPRITE_STATE_CONTROL_MOUSE_DOWN:
					real_draw_color.a = 255;
					real_draw_color.r = 255 - background_color.r;
					real_draw_color.b = 255 - background_color.b;
					real_draw_color.g = 255 - background_color.g;
					break;
				}

				if(control_alpha == 255)
				{
					device.display.DrawFillRect(real_draw_color, fill_rect);
				}
				else
				{
					device.display.DrawAlphaSolidColor(real_draw_color, control_alpha, fill_rect);
				}

				if (is_draw_outline)
				{
					device.display.DrawOutlineRect(real_draw_color, fill_rect);
				}

			}
			else
			{
				Rect dest_rect = {x,y,width,height};
				background_sprite.DrawFill(dest_rect);
			}

			if(is_show_text)
			{
				text_writer.Write();
			}
		}
	}



	// 滚动条控件-----------------------------------------------------------------
	ControlBar::ControlBar():
	BaseControl(0,0,0,0, SOLID_COLOR),
	control_direct(CONTROL_DIRECT_UP_DOWN),
	is_solid_color_background(true),
	control_alpha(255),
	center_x(0.5f), center_y(0.5f),
	percent(0.0f)
	{
		background_color_trough.r = background_color_trough.g = background_color_trough.b = 190;
		background_color_bar.r = background_color_bar.g = background_color_bar.b = background_color_bar.a = 80;
	}

	ControlBar& ControlBar::Contact(int MouseX, int MouseY, bool IsMouseDown)
	{
		// 本体
		BaseControl::Contact(MouseX, MouseY, IsMouseDown);
		if (control_state == CONTROL_STATE_MOUSE_DOWN)
		{
			if (control_direct == CONTROL_DIRECT_UP_DOWN)
			{
				int precent_h = MouseY - (y + bar_height * 0.5);
				if (precent_h < 0)
				{
					percent = 0.0f;
				}
				else if (precent_h > height - bar_height)
				{
					percent = 1.0f;
				} 
				else
				{
					percent = (float)precent_h/(height - bar_height);
				}
			} 
			else
			{
				int precent_w = MouseX - (x+bar_width*0.5);
				if (precent_w < 0)
				{
					percent = 0.0f;
				}
				else if (precent_w > width - bar_width)
				{
					percent = 1.0f;
				} 
				else
				{
					percent = (float)precent_w/(width-bar_width);
				}
			}
		}

		// 精灵
		SpriteState curr_sprite_state;
		switch(GetState())
		{
		case CONTROL_STATE_MOUSE_OUT:
			curr_sprite_state = SPRITE_STATE_CONTROL_MOUSE_OUT;
			break;
		case CONTROL_STATE_MOUSE_OVER:
			curr_sprite_state = SPRITE_STATE_CONTROL_MOUSE_OVER;
			break;
		case CONTROL_STATE_MOUSE_DOWN:
			curr_sprite_state = SPRITE_STATE_CONTROL_MOUSE_DOWN;
			break;
		default:
			curr_sprite_state = SPRITE_STATE_DEFAULT;
		}
		background_sprite_trough.Contact(curr_sprite_state);
		background_sprite_bar.Contact(curr_sprite_state);

		return *this;
	}

	float ControlBar::GetPercent(void)
	{
		return percent;
	}

	ControlBar& ControlBar::ChangePercent(float Percent)
	{
		if (Percent < .0f)
			percent = 0.0;
		else if (Percent > 1.0f)
			percent = 1.0;
		else
			percent = Percent; 

		return *this;
	}

	ControlBar& ControlBar::ChangePercent(int MouseX, int MouseY)
	{
		if (control_direct == CONTROL_DIRECT_UP_DOWN)
		{
			int precent_h = MouseY - (y + bar_height * 0.5);
			if (precent_h < 0)
			{
				percent = 0.0f;
			}
			else if (precent_h > height - bar_height)
			{
				percent = 1.0f;
			} 
			else
			{
				percent = (float)precent_h/(height - bar_height);
			}
		} 
		else
		{
			int precent_w = MouseX - (x+bar_width*0.5);
			if (precent_w < 0)
			{
				percent = 0.0f;
			}
			else if (precent_w > width - bar_width)
			{
				percent = 1.0f;
			} 
			else
			{
				percent = (float)precent_w/(width-bar_width);
			}
		}

		return *this;
	}

	ControlBar& ControlBar::ChangeDirect(ControlDirect Direct)
	{
		control_direct = Direct;
		return *this;
	}

	bool ControlBar::LoadControlBar(const char* PathName, int X, int Y)
	{
		bool succed = true;
		FILE *fp;
		fp = fopen(PathName, "r");

		if(fp != NULL)
		{
			char buff[255];
			char var[255];

			// 读取类型
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

			// 验证类型
			if (std::string("bar") == var)
			{
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
				control_name = var;

				// 读取滚动条方向
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
				if (var == std::string("up_down"))
				{
					control_direct = CONTROL_DIRECT_UP_DOWN;
				} 
				else if (var == std::string("left_right"))
				{
					control_direct = CONTROL_DIRECT_LEFT_RIGHT;
				} 
				else
				{
					control_direct = CONTROL_DIRECT_UP_DOWN;
				}

				// 设置位置
				x = X;
				y = Y;

				// 读取位置,大小,中心
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%d", &width);
					}
				}
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%d", &height);
					}
				}
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%d", &bar_width);
					}
				}
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%d", &bar_height);
					}
				}
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%f", &center_x);
					}
				}
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%f", &center_y);
					}
				}

				// 读取精灵 底下的槽
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

				if (background_sprite_trough.LoadSprite(var, x, y, width, height))
				{
					// 读取精灵 上面的控制点
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

					if (background_sprite_bar.LoadSprite(var, x, y, width, height))
					{
						ChangeToUseSpriteBackground();
					}
				}

			}else
			{
				error_out("ControlBar::LoadControlBar - \""+string(PathName)+"\"类型出错! - 非bar类型控件");
				succed = false;
			}
		}
		else
		{
			error_out("ControlBar::LoadControlBar - 打开\""+string(PathName)+"\"文件出错!");
			succed = false;
		}

		fclose(fp);
		return succed;
	}

	bool ControlBar::CreateControlBar(const char* Name, ControlDirect Direct, Rect &TroughRect, int BarWidth, int BarHeight, float CenterX, float CenterY, Color &BackgroundColorTrough, Color &BackgroundColorBar)
	{
		control_name = Name;
		
		control_direct = Direct;
		
		x = TroughRect.x;
		y = TroughRect.y;
		width = TroughRect.w;
		height = TroughRect.h;

		bar_width = BarWidth;
		bar_height = BarHeight;

		center_x = CenterX;
		center_y = CenterY;

		background_color_trough = BackgroundColorTrough;
		background_color_bar = BackgroundColorBar;

		return true;
	}

	ControlBar& ControlBar::ChangePosition(int X, int Y)
	{
		x = X;
		y = Y;
		background_sprite_trough.ChangePosition(X, Y);
		background_sprite_bar.ChangePosition(X, Y);
		return *this;
	}

	ControlBar& ControlBar::ChangeSize(int Width, int Height)
	{
		width = Width;
		height = Height;
		background_sprite_trough.ChangeSize(Width, Height);
		background_sprite_bar.ChangeSize(Width, Height);
		return *this;
	}

	ControlBar& ControlBar::ChangeBackgroundColor(Color& BackGroundColorTrough, Color& BackGroundColorbar)
	{
		background_color_trough = BackGroundColorTrough;
		background_color_bar = BackGroundColorbar;
		return *this;
	}

	ControlBar& ControlBar::ChangeBackgroundSprite(Sprite &BackgroundTrough, Sprite &BackgroundBar)
	{
		background_sprite_trough = BackgroundTrough;
		background_sprite_bar = BackgroundBar;
		return *this;
	}

	ControlBar& ControlBar::ChangeAlpha(uint8_t Alpha)
	{
		control_alpha = Alpha;
		background_sprite_trough.SetAlpha(Alpha);
		background_sprite_bar.SetAlpha(Alpha);
		return *this;
	}

	ControlBar& ControlBar::ChangeToUseSolidColorBackground()
	{
		is_solid_color_background = true;
		return *this;
	}

	ControlBar& ControlBar::ChangeToUseSpriteBackground()
	{
		is_solid_color_background = false;
		return *this;
	}

	void ControlBar::Draw()
	{
		if(is_show)
		{
			Rect trough_dest_rect = {x,y,width,height};

			Rect bar_dest_rect = {0,0, bar_width, bar_height};;

			if (control_direct == CONTROL_DIRECT_UP_DOWN)
			{
				bar_dest_rect.x = x + (width - bar_width) * 0.5;
				bar_dest_rect.y = y + (height - bar_height) * percent;
			} 
			else // CONTROL_DIRECT_LEFT_RIGHT 的情况
			{
				bar_dest_rect.x = x + (width - bar_width) * percent;
				bar_dest_rect.y = y + (height - bar_height) * 0.5;
			}

			if(is_solid_color_background)
			{
				Color real_draw_background_color_bar;

				if (control_state==SPRITE_STATE_CONTROL_MOUSE_DOWN)
				{
					real_draw_background_color_bar.r = 255 - background_color_bar.r;
					real_draw_background_color_bar.b = 255 - background_color_bar.b;
					real_draw_background_color_bar.g = 255 - background_color_bar.g;
				}else
				{
					real_draw_background_color_bar = background_color_bar;
				}

				if(control_alpha == 255)
				{
					// 绘制槽
					device.display.DrawFillRect(background_color_trough, trough_dest_rect );

					// 绘制点
					device.display.DrawFillRect(background_color_bar, bar_dest_rect);
				}
				else
				{
					// 绘制槽
					device.display.DrawAlphaSolidColor(background_color_trough, control_alpha, trough_dest_rect);

					// 绘制点
					device.display.DrawAlphaSolidColor(real_draw_background_color_bar, control_alpha, bar_dest_rect);
				}

			}
			else
			{
				background_sprite_trough.Draw(trough_dest_rect);
				background_sprite_bar.Draw(bar_dest_rect);
			}


#ifdef CodeDebug
			device.display.DrawOutlineRect(RedColor, trough_dest_rect);
			device.display.DrawOutlineRect(RedColor, bar_dest_rect);
#endif
			
		}
	}

	void ControlBar::DrawFill()
	{
		if(is_show)
		{
			Rect trough_dest_rect = {x,y,width,height};

			Rect bar_dest_rect = {0,0, bar_width, bar_height};;

			if (control_direct == CONTROL_DIRECT_UP_DOWN)
			{
				bar_dest_rect.x = x + (width - bar_width) * 0.5;
				bar_dest_rect.y = y + (height - bar_height) * percent;
			} 
			else // CONTROL_DIRECT_LEFT_RIGHT 的情况
			{
				bar_dest_rect.x = x + (width - bar_width) * percent;
				bar_dest_rect.y = y + (height - bar_height) * 0.5;
			}

			if(is_solid_color_background)
			{
				Color real_draw_background_color_bar;

				if (control_state==SPRITE_STATE_CONTROL_MOUSE_DOWN)
				{
					real_draw_background_color_bar.r = background_color_bar.r * 0.5;
					real_draw_background_color_bar.g = background_color_bar.r * 0.5;
					real_draw_background_color_bar.b = background_color_bar.r * 0.5;

				}else if (control_state==SPRITE_STATE_CONTROL_MOUSE_OVER)
				{
					real_draw_background_color_bar.r = background_color_bar.r * 0.8;
					real_draw_background_color_bar.g = background_color_bar.r * 0.8;
					real_draw_background_color_bar.b = background_color_bar.r * 0.8;
				}
				else
				{
					real_draw_background_color_bar = background_color_bar;
				}

				if(control_alpha == 255)
				{
					// 绘制槽
					device.display.DrawFillRect(background_color_trough, trough_dest_rect );

					// 绘制点
					device.display.DrawFillRect(background_color_bar, bar_dest_rect);
				}
				else
				{
					background_sprite_trough.Draw(trough_dest_rect);
					background_sprite_bar.Draw(bar_dest_rect);
				}

			}
			else
			{
				background_sprite_trough.DrawFill(trough_dest_rect);
				background_sprite_bar.DrawFill(bar_dest_rect);
			}


#ifdef CodeDebug
			device.display.DrawOutlineRect(RedColor, trough_dest_rect);
			device.display.DrawOutlineRect(RedColor, bar_dest_rect);
#endif

		}
	}


	// 列表控件--------------------------------------------------------------
	ControlList::ControlList():
	BaseControl(0, 0, 0, 0, SOLID_COLOR),
	is_solid_color_background(true),
	is_any_control_text_have_message(false),
	control_bar_occupy_percent(CONTROL_BAR_OCCUPY_CONTROL_LIST_PERCENT),
	control_alpha(255)
	{
		background_color.r = background_color.b = background_color.g = 225;
	}

	ControlList::~ControlList()
	{
		//// 标准迭代法
		//for (std::vector<ControlText*>::iterator item = list.begin(); item != list.end(); ++item)
		//{
		//	delete (*item);
		//	*item = NULL;
		//}

		//// 无聊的方法
		//while(!list.empty())
		//{
		//	delete list.back();
		//	list.pop_back();
		//}

		// 顺序方法
		for(int i=0; i < list.size(); ++i)
		{
			delete list[i];
			list[i] = NULL;
		}
	}

	bool ControlList::LoadControlList(const char* PathName, int X, int Y)
	{
		bool succed(true);

		FILE *fp;
		fp = fopen(PathName, "r");

		if(fp != NULL)
		{
			char buff[255];
			char var[255];

			// 读取类型
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

			// 验证类型
			if (var == std::string("list"))
			{
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
				control_name = var;

				// 设置位置
				x = X;
				y = Y;

				// 读取大小
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%d", &width);
					}
				}
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%d", &height);
					}
				}
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%d", &entry_height);
					}
				}
				fgets(buff, 254, fp);
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%f", &control_bar_occupy_percent);
					}
				}

				if (control_bar_occupy_percent < 0)
				{
					control_bar_occupy_percent = 0.0;
				} 
				else if (control_bar_occupy_percent > 1)
				{
					control_bar_occupy_percent = 1.0;
				}

				// 读取精灵
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

				if (background_sprite.LoadSprite(var, x, y, width, height))
				{
					ChangeToUseSpriteBackground();
				}
				else
				{
					ChangeToUseSolidColorBackground();
				}

				// 滑动条控件
				Rect control_bar_rect = {x + width * ( 1 - control_bar_occupy_percent), y, width * control_bar_occupy_percent, height};
				Color control_bar_trough_color = {200,200,200,200};
				Color control_bar_bar_color = {100,100,100,100};
				control_bar.CreateControlBar("fist list's bar", CONTROL_DIRECT_UP_DOWN, control_bar_rect, control_bar_rect.w, control_bar_rect.h * 0.07, 0.5, 0.5, control_bar_trough_color, control_bar_bar_color);

			}
			else
			{
				error_out("ControlList::LoadControlList - \""+string(PathName)+"\"类型出错! - 非list类型控件");
				succed = false;
			}
		}
		else
		{
			error_out("ControlList::LoadControlList - 打开\""+string(PathName)+"\"文件出错!");
			succed = false;
		}

		fclose(fp);

		return succed;
	}

	ControlList& ControlList::Contact(int MouseX, int MouseY, bool IsMouseDown)
	{
		// 本体
		BaseControl::Contact(MouseX, MouseY, IsMouseDown);

		is_any_control_text_have_message = false;
		int total_list_height = list.size() * entry_height;
		int mouse_x = MouseX - x, mouse_y = MouseY - y;
		if (total_list_height > height)
		{
			// 映射鼠标位置,接触
			mouse_y += (total_list_height - height)*GetPercent();
			for(int i=0; i < list.size(); ++i)
			{
				list[i]->Contact(MouseX, mouse_y, IsMouseDown);
				if (list[i]->GetState() == CONTROL_STATE_MOUSE_DOWN ||list[i]->GetState() == CONTROL_STATE_MOUSE_OVER)
				{
					is_any_control_text_have_message = true;
					position_of_control_text_that_have_message = i;
					break;
				}
			}
		} 
		else
		{
			for(int i=0; i < list.size(); ++i)
			{
				list[i]->Contact(mouse_x, mouse_y, IsMouseDown);
				if (list[i]->GetState() == CONTROL_STATE_MOUSE_DOWN ||list[i]->GetState() == CONTROL_STATE_MOUSE_OVER)
				{
					is_any_control_text_have_message = true;
					position_of_control_text_that_have_message = i;
					break;					
				}
			}
		}
		
		// 滚动条
		control_bar.Contact(MouseX, MouseY, IsMouseDown);

		// 精灵
		SpriteState curr_sprite_state;
		switch(GetState())
		{
		case CONTROL_STATE_MOUSE_OUT:
			curr_sprite_state = SPRITE_STATE_CONTROL_MOUSE_OUT;
			break;
		case CONTROL_STATE_MOUSE_OVER:
			curr_sprite_state = SPRITE_STATE_CONTROL_MOUSE_OVER;
			break;
		case CONTROL_STATE_MOUSE_DOWN:
			curr_sprite_state = SPRITE_STATE_CONTROL_MOUSE_DOWN;
			break;
		default:
			curr_sprite_state = SPRITE_STATE_DEFAULT;
		}
		background_sprite.Contact(curr_sprite_state);

		return *this;
	}

	float ControlList::GetPercent(void)
	{
		return control_bar.GetPercent();
	}

	ControlBar& ControlList::GetControlBar()
	{
		return control_bar;
	}

	ControlList& ControlList::ChangePercent(float Percent)
	{
		control_bar.ChangePercent(Percent);
		return *this;
	}

	ControlList& ControlList::ChangePosition(int X, int Y)
	{
		x = X;
		y = Y;
		control_bar.ChangePosition(X + width * CONTROL_BAR_OCCUPY_CONTROL_LIST_PERCENT, Y);
		return *this;
	}

	ControlList& ControlList::ChangeSize(int Width, int Height)
	{
		width = Width;
		height = Height;

		control_bar.ChangeSize(Width * control_bar_occupy_percent, Height);

		// 改变所有条目
		for(int i=0; i < list.size(); ++i)
		{
			list[i]->ChangeSize(Width * (1-control_bar_occupy_percent), entry_height);
		}

		return *this;
	}

	ControlList& ControlList::ChangeBackgroundColor(Color& BackGroundColor)
	{
		background_color = BackGroundColor;
		return *this;
	}

	ControlList& ControlList::ChangeBackgroundSprite(Sprite& BackgroundSprite)
	{
		background_sprite = BackgroundSprite;
		return *this;
	}

	ControlList& ControlList::ChangeAlpha(uint8_t Alpha)
	{
		control_alpha = Alpha;
		control_bar.ChangeAlpha(Alpha);

		// 改变所有条目

		for(int i=0; i < list.size(); ++i)
		{
			list[i]->ChangeAlpha(Alpha);
		}
		return *this;
	}

	ControlList& ControlList::ChangeToUseSolidColorBackground()
	{
		is_solid_color_background = true;
		return *this;
	}

	ControlList& ControlList::ChangeToUseSpriteBackground()
	{
		is_solid_color_background = false;
		return *this;
	}

	void ControlList::Draw()
	{
		if (is_show)
		{
			// 绘制列表
			Rect real_list_dest_rect = {x, y, width - control_bar.GetSizeWidth(), height};
			Color real_draw_background_color = background_color;

			if (is_solid_color_background)
			{
				if(control_alpha == 255)
				{
					device.display.DrawFillRect(real_draw_background_color,  real_list_dest_rect);
				}
				else
				{
					device.display.DrawAlphaSolidColor(real_draw_background_color, control_alpha, real_list_dest_rect);
				}
			} 
			else
			{
				background_sprite.Draw(real_list_dest_rect);
			}

			// 绘制条目
			int start_point_y = 0;
			int total_list_height = list.size() * entry_height;
			if (total_list_height > height)
			{
				start_point_y =  - (total_list_height - height) * control_bar.GetPercent();
				device.display.SetViewport(real_list_dest_rect);

				for(int i=0; i < list.size(); ++i)
				{
					list[i]->Draw(x, start_point_y);
					start_point_y += entry_height;
				}
				device.display.SetViewportToDefault();
			} 
			else
			{
				start_point_y = y;
				for(int i=0; i < list.size(); ++i)
				{
					list[i]->Draw(x, start_point_y);
					start_point_y += entry_height;
				}
			}

			// 绘制滚动条控件
			control_bar.Draw();
		}
	}

	void ControlList::DrawFill()
	{
		if (is_show)
		{
			// 绘制列表
			Rect real_list_dest_rect = {x, y, width - control_bar.GetSizeWidth(), height};
			Color real_draw_background_color = background_color;

			if (is_solid_color_background)
			{
				if(control_alpha == 255)
				{
					device.display.DrawFillRect( real_draw_background_color , real_list_dest_rect);
				}
				else
				{
					device.display.DrawAlphaSolidColor(real_draw_background_color, control_alpha, real_list_dest_rect);
				}
			} 
			else
			{
				background_sprite.DrawFill(real_list_dest_rect);
			}

			// 绘制条目
			int start_point_y = 0;
			int total_list_height = list.size() * entry_height;
			if (total_list_height > height)
			{
				start_point_y = - (total_list_height - height) * control_bar.GetPercent();
				device.display.SetViewport(real_list_dest_rect);

				for (std::vector<ControlText*>::iterator item = list.begin(); item != list.end(); ++item)
				{
					(*item)->Draw(x, start_point_y);
					start_point_y += entry_height;
				}

				device.display.SetViewportToDefault();
			} 
			else
			{
				start_point_y = y;
				for (std::vector<ControlText*>::iterator item = list.begin(); item != list.end(); ++item)
				{
					(*item)->Draw(x, start_point_y);
					start_point_y += entry_height;
				}
			}

			// 绘制滚动条
			control_bar.DrawFill();
		}
	}

	ControlList& ControlList::PushBack(const char *ControlName, const char* Text)
	{
		list.push_back(new ControlText());
		Color BackgroundColor = {0,0,0,0};
		Color TextColor = {255,255,255,0};
		list.back()->CreateControlText(ControlName, 0, entry_height*(list.size()-1), width * (1-control_bar_occupy_percent), entry_height, "resource\\font.ttf", 20, Text, TextColor, BackgroundColor);

		return *this;
	}

	ControlList& ControlList::PushBack(ControlText* Entry)
	{
		Entry->ChangePosition(0, entry_height*(list.size()-1)).ChangeSize(width * (1-control_bar_occupy_percent), entry_height);
		list.push_back(Entry);
		return *this;
	}

	ControlList& ControlList::Insert(int Position, const char *ControlName, const char* Text)
	{
		//        _________________在这插入
		//       |                               *即在 Position-1 和 Position 之间插入元素
		// __0__  __1__  __2__
		//          |_______________这是 Position

		if ((0 <= Position)&&(Position <= list.size()))
		{
			list.insert(list.begin() + Position, new ControlText());
			Color BackgroundColor = {0,0,0,0};
			Color TextColor = {255,255,255,0};
			list[Position]->CreateControlText(ControlName, 0, entry_height*Position, width * (1-control_bar_occupy_percent), entry_height, "resource\\font.ttf", 20, Text, TextColor, BackgroundColor);

			for(int i=Position+1; i < list.size(); ++i)
			{
				list[i]->ChangePosition(0, i * entry_height);
			}
		}
		return *this;
	}

	ControlList& ControlList::Insert(int Position, ControlText* Entry)
	{
		if ((0 <= Position)&&(Position <= list.size()))
		{
			Entry->ChangePosition(0, entry_height*Position).ChangeSize(width * (1-control_bar_occupy_percent), entry_height);
			list.insert(list.begin() + Position, Entry);

			for(int i=Position+1; i < list.size(); ++i)
			{
				list[i]->ChangePosition(0, i * entry_height);
			}
		}
		return *this;
	}

	ControlList& ControlList::Delete(int Position)
	{
		if ((0 <= Position)&&(Position < list.size()))
		{
			delete list[Position];
			list.erase(list.begin() + Position);

			for(int i=Position+1; i < list.size(); ++i)
			{
				list[i]->ChangePosition(0, i * entry_height);
			}
		}

		return *this;
	}

	ControlText* ControlList::GetControlText(int Position)
	{
		if ((0 <= Position)&&(Position < list.size()))
		{
			return list[Position];
		}

		return NULL;
	}

	bool ControlList::IsAnyControlTextHaveMessage()
	{
		return is_any_control_text_have_message;
	}

	int ControlList::GetPositionOfControlTextThatHaveMessage()
	{
		return position_of_control_text_that_have_message;
	}

	ControlText* ControlList::GetControlTextThatHaveMessage()
	{
		return GetControlText(position_of_control_text_that_have_message);
	}

}