
#include "orz_sprite.h"
#include "orz_log.h"
#include "orz_option.h"
#include <iostream>
#include <string>


namespace Orz
{
	Sprite::Sprite()
	{
	}

	Sprite::~Sprite()
	{
		Free();
	}

	bool Sprite::LoadSprite(const char* PathName, int X, int Y, int Width, int Height)
	{
		Free();
		bool succed = true;
		FILE *fp;
		fp = fopen(PathName, "r");

		if(fp != NULL)
		{
			char buff[255];
			char var[255];
			int read_sprite_state;

			// 读取名字
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
			
			// 读取状态&路径
			while (fgets(buff, 254, fp))
			{
				// 读取状态
				for(int i=0; buff[i]&&i<254; i++)
				{
					if(buff[i] == '=')
					{
						sscanf(buff + i + 1, "%d", &read_sprite_state);
						break;
					}
				}

				// 读取路径
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

						//error_out(std::string("var: ") + var);

						break;
					}
				}

				element.push_back(AnimateWithState(var, (SpriteState)read_sprite_state));
			}
		}
		else
		{
			error_out("Sprite::LoadSprite - 打开\""+string(PathName)+"\"文件出错!");
			succed = false;
		}

		fclose(fp);

		dest_rect.x = X;
		dest_rect.y = Y;
		dest_rect.w = Width;
		dest_rect.h = Height;

		curr_state = CONTROL_BUTTON_MOUSE_OUT;

		return succed;
	}

	void Sprite::SetAlpha(int Alpha)
	{
		if (Alpha != 255)
		{
			for(int i=0; i < element.size(); i++)
			{
				element[i].animate.SetBlendModeToAlpha();
				element[i].animate.SetAlpha(Alpha);
			}
		}
		else
		{
			for(int i=0; i < element.size(); i++)
			{
				element[i].animate.SetBlendModeToNone();
			}
		}
	}

	void Sprite::SetBlendModeToNone()
	{
		for(int i=0; i < element.size(); i++)
			element[i].animate.SetBlendModeToNone();
	}

	void Sprite::SetBlendModeToAlpha()
	{
		for(int i=0; i < element.size(); i++)
			element[i].animate.SetBlendModeToAlpha();
	}

	void Sprite::SetBlendModeToAdd()
	{
		for(int i=0; i < element.size(); i++)
			element[i].animate.SetBlendModeToAdd();
	}

	void Sprite::SetBlendModeToMod()
	{
		for(int i=0; i < element.size(); i++)
			element[i].animate.SetBlendModeToMod();
	}

	void Sprite::Contact(SpriteState CurrentState)
	{
		if (curr_state == CurrentState)
		{
			for(int i=0; i < element.size(); i++)
			{
				if (curr_state == element[i].state)
				{
					element[CurrentState].animate.Contact();
				}
			}
		}
		else
		{
			curr_state = CurrentState;
			for(int i=0; i < element.size(); i++)
			{
				if (curr_state == element[i].state)
				{
					element[CurrentState].animate.ContactReset();
				}
			}
		}
	}

	void Sprite::ContactReset(void)
	{
		for (int i = 0; i<element.size(); i++)
		{
			element[i].animate.ContactReset();
		}
	}

	void Sprite::Free()
	{
		name.clear();
		element.clear();
	}

	void Sprite::Draw()
	{
		for (int i = 0; i<element.size(); i++)
		{
			if (curr_state == element[i].state)
			{
				element[i].animate.Draw(dest_rect);
			}
		}
	}

	void Sprite::DrawFill()
	{
		for (int i = 0; i<element.size(); i++)
		{
			if (curr_state == element[i].state)
			{
				element[i].animate.DrawFill(dest_rect);
			}
		}
	}

	void Sprite::Draw(Rect &DestRect)
	{
		dest_rect = DestRect;
		Draw();
	}

	void Sprite::DrawFill(Rect &DestRect)
	{
		dest_rect = DestRect;
		DrawFill();
	}

	Sprite& Sprite::ChangePosition(int X, int Y)
	{
		dest_rect.x = X;
		dest_rect.y = Y;
		return *this;
	}

	Sprite& Sprite::ChangeSize(int Width, int Height)
	{
		dest_rect.w = Width;
		dest_rect.y = Height;
		return *this;
	}

	SpriteState Sprite::GetState(void)
	{
		return curr_state;
	}

}