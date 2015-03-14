
#include "orz_sprite.h"
#include "orz_log.h"
#include "orz_config.h"
#include "orz_animate.h"
#include "orz_base_public_resource.h"
#include <string>

namespace Orz
{
	Sprite::Sprite():
	BaseUi(ELEMENT_TYPE_UI_ANIMATE_SPRITE, 0.0f)
	{
	}

	bool Sprite::LoadSprite(const char *SpriteName, const char* PathName, const Rect &SpriteRect)
	{
		Free();
		bool succed = true;
		element_name = SpriteName;
		FILE *fp;
		fp = fopen(PathName, "r");

		if(fp != NULL)
		{
			char buff[255];
			char var[255];

			// 读取状态&路径
			int index(0);
			while (fgets(buff, 254, fp))
			{
				// 读取 Animate 路径
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

				Animate *new_animate = new Animate;
				new_animate->LoadAnimate("", var, SpriteRect);
				new_animate->SetUiState((UiState)index);
				ChildrenPushBack(new_animate);
				index++;
			}
		}
		else
		{
			error_out("Sprite::LoadSprite - 打开\""+string(PathName)+"\"文件出错!");
			succed = false;
		}

		x = SpriteRect.x;
		y = SpriteRect.y;
		width = SpriteRect.w;
		height = SpriteRect.h;

		fclose(fp);
		return succed;
	}

	Sprite& Sprite::ChangeBlendModeToNone()
	{
		for(int i=0; i < ChildrenSize(); i++)
		{
			if (element_type == ELEMENT_TYPE_UI_ANIMATE)
			{
				((Animate&)Children(i)).ChangeBlendModeToNone();
			}
		}
		return *this;
	}

	Sprite& Sprite::ChangeBlendModeToAlpha()
	{
		for(int i=0; i < ChildrenSize(); i++)
		{
			if (element_type == ELEMENT_TYPE_UI_ANIMATE)
			{
				((Animate&)Children(i)).ChangeBlendModeToAlpha();
			}
		}
		return *this;
	}

	Sprite& Sprite::ChangeBlendModeToAdd()
	{
		for(int i=0; i < ChildrenSize(); i++)
		{
			if (element_type == ELEMENT_TYPE_UI_ANIMATE)
			{
				((Animate&)Children(i)).ChangeBlendModeToAdd();
			}
		}
		return *this;
	}

	Sprite& Sprite::ChangeBlendModeToMod()
	{
		for(int i=0; i < ChildrenSize(); i++)
		{
			if (element_type == ELEMENT_TYPE_UI_ANIMATE)
			{
				((Animate&)Children(i)).ChangeBlendModeToMod();
			}
		}
		return *this;
	}

	void Sprite::DoDraw(const Rect& DrawRect)
	{
		for(int i=0; i < ChildrenSize(); i++)
		{
			if (Children(i).element_type == ELEMENT_TYPE_UI_ANIMATE)
			{
				Children(i).Hide();
			}
		}

		int element_state_position;
		if (parent)
		{
			switch(parent->element_type)
			{
			case ELEMENT_TYPE_UI_CONTROL_VIRTUAL	:
			case ELEMENT_TYPE_UI_CONTROL_CANVAS		:
			case ELEMENT_TYPE_UI_CONTROL_TEXT		:
			case ELEMENT_TYPE_UI_CONTROL_BUTTON		:
			case ELEMENT_TYPE_UI_CONTROL_SCROLL_BAR	:
			case ELEMENT_TYPE_UI_CONTROL_LIST		:
				element_state_position = ((BaseUi*)parent)->GetUiState();
				break;
			default:
				element_state_position = UI_STATE_DEFAULT;
				break;
			}
		}
		else
		{
			element_state_position = UI_STATE_DEFAULT;
		}

		if (0 <= element_state_position && element_state_position < ChildrenSize())
		{
			if (Children(element_state_position).element_type == ELEMENT_TYPE_UI_ANIMATE)
			{
				Children(element_state_position).Show();
			}
		}
	}

	void Sprite::DoContact(void)
	{
	}

	void Sprite::DoContactReset(void)
	{
	}

	void Sprite::DoChangeAlpha(uint8_t Alpha)
	{
		if (Alpha != 255)
		{
			for(int i=0; i < ChildrenSize(); i++)
			{
				if (element_type == ELEMENT_TYPE_UI_ANIMATE)
				{
					((Animate&)Children(i)).ChangeBlendModeToAlpha();
				}
			}
		}
		else
		{
			for(int i=0; i < ChildrenSize(); i++)
			{
				if (element_type == ELEMENT_TYPE_UI_ANIMATE)
				{
					((Animate&)Children(i)).ChangeBlendModeToNone();
				}
			}
		}
	}
}