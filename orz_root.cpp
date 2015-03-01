
#include "orz_root.h"
#include "orz_log.h"
#include "orz_base_public_resource.h"

namespace Orz
{
	Root::Root():is_loop(true)
	{
	}

    bool Root::CreateScene()
    {
        return true;
    }

    void Root::UpdateScene()
    {
    }

    void Root::QuitScene()
    {
        is_loop = false;
    }

    void Root::Go(void)
    {
        if(!sdl.Init())
        {
            error_out("Root::Go - SDL 初始化失败!");
        }

        device.Init();
        platform.Init();

        // 创建设备\平台
        CreateScene();

        // SDL 事件
        SDL_Event event;

        is_loop = true;
        while(is_loop)
        {
            // 处理系统事件
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    // 键盘事件
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                                break;
                            default: break;
                        }break;


                    // 鼠标事件
                    case SDL_MOUSEBUTTONDOWN:
                    {
                        if(event.button.button == SDL_BUTTON_LEFT)
                            device.Contact(KEY_MOUSE_RIGHT, true);

                    }break;
                    case SDL_MOUSEBUTTONUP:
                    {
                        if(event.button.button == SDL_BUTTON_RIGHT)
                            device.Contact(KEY_MOUSE_LEFT, false);
                    }break;

                // 其他事件
                default: break;
                }
            }

            // 改变场景
            UpdateScene();

			#ifdef CodeDebug
				// 绘制调试用的图形
				UpdateDebugScene();
			#endif

            // 绘图
            device.Present();
        }
    }

    // 创建一个动画
    Animate* Root::CreateAnimate(KeyType Name, const char *NamePath)
    {
        bool result(true);
        RBTreeNode *new_node = new RBTreeNode;
        Animate *new_animate = NULL;
        if(!new_node)
        {
            error_out("Root::CreateAnimate - 创建红黑树节点失败 - 无法获得内存!");
            result = false;
        }
        else
        {
            new_node->key = Name;
            new_animate = new Animate();
            new_node->p = new_animate;
            if(!new_node->p)
            {
                error_out("Root::CreateAnimate - 创建动画失败 - 无法获得内存!");
                result = false;
            }
            else
            {
                if(!new_animate->LoadAnimate(NamePath))
                {
                    error_out("创建动画失败!");
                    result = false;
                }
                else
                {
                    rb_tree.Insert(new_node);
                }
            }
        }

        if(result)
            return new_animate;

        return NULL;
    }

    // 得到动画
    Animate& Root::GetAnimate(KeyType Name)
    {
        RBTreeNode* node = rb_tree.Search(Name);

        if(node)
            return *(Animate*)(node->p);
        else
        {
            string err = "Root::GetAnimate - 无法获得动画\""+ Name +"\"!";
            error_out(err);
            return error_animate;
        }
    }

    // 创建书写者
    Writer* Root::CreateWriter(KeyType Name, std::string FontName, std::string Text, int FontSize, Color FontColor, Rect DestRect)
    {
        bool result(true);
        RBTreeNode *new_node = new RBTreeNode;
        Writer *new_writer = NULL;
        if(!new_node)
        {
            error_out("Root::CreateWriter - 创建红黑树节点失败 - 无法获得内存!");
            result = false;
        }
        else
        {
            new_node->key = Name;
            new_writer = new Writer;
            new_node->p = new_writer;
            if(!new_node->p)
            {
                error_out("Root::CreateWriter - 创建写手失败 - 无法获得内存!");
                result = false;
            }
            else
            {
				if(!new_writer->CreateWriter(FontName.c_str(), Text.c_str(), FontSize, FontColor, DestRect))
                {
                    error_out("创建动画失败!");
                    result = false;
                }
                else
                {
                    rb_tree.Insert(new_node);
                }
            }
        }

        if(result)
            return new_writer;

        return NULL;

    }

    // 得到书写者
    Writer& Root::GetWriter(KeyType Name)
    {
        RBTreeNode* node = rb_tree.Search(Name);

        if(node)
            return *(Writer*)(node->p);
        else
        {
            string err = "Root::GetWriter - 无法获得书写者\""+ Name +"\"!";
            error_out(err);
            return error_writer;
        }
    }

	ControlText* Root::CreateControlText(KeyType Name, const char *ControlName, int X, int Y, int Width, int Height, const char *FontName, int FontSize, const char *Text, Color &TextColor, Color &BackgroundColor)
	{
		bool result(true);
		RBTreeNode *new_node = new RBTreeNode;
		ControlText *new_control = NULL;
		if(!new_node)
		{
			error_out("Root::CreateControlText - 创建红黑树节点失败 - 无法获得内存!");
			result = false;
		}
		else
		{
			new_node->key = Name;
			new_control = new ControlText;
			new_node->p = new_control;
			if(!new_node->p)
			{
				error_out("Root::CreateControlText - 创建控件Text失败 - 无法获得内存!");
				result = false;
			}
			else
			{
				if(!new_control->CreateControlText(ControlName, X, Y, Width, Height, FontName, FontSize, Text, TextColor, BackgroundColor))
				{
					error_out("创建控件Text失败!");
					result = false;
				}
				else
				{
					rb_tree.Insert(new_node);
				}
			}
		}

		if(result)
			return new_control;

		return NULL;
	}

	ControlButton* Root::CreateControlButton(KeyType Name, const char* PathName, int X, int Y)
	{
		bool result(true);
		RBTreeNode *new_node = new RBTreeNode;
		ControlButton *new_control = NULL;
		if(!new_node)
		{
			error_out("Root::CreateControlText - 创建红黑树节点失败 - 无法获得内存!");
			result = false;
		}
		else
		{
			new_node->key = Name;
			new_control = new ControlButton;
			new_node->p = new_control;
			if(!new_node->p)
			{
				error_out("Root::CreateControlText - 创建控件Button失败 - 无法获得内存!");
				result = false;
			}
			else
			{
				if(!new_control->LoadControlButton(PathName, X, Y))
				{
					error_out("创建控件Button失败!");
					result = false;
				}
				else
				{
					rb_tree.Insert(new_node);
				}
			}
		}

		if(result)
			return new_control;

		return NULL;
	}

	ControlBar* Root::CreateControlBar(KeyType Name, const char* PathName, int X, int Y)
	{
		bool result(true);
		RBTreeNode *new_node = new RBTreeNode;
		ControlBar *new_control = NULL;
		if(!new_node)
		{
			error_out("Root::CreateControlText - 创建红黑树节点失败 - 无法获得内存!");
			result = false;
		}
		else
		{
			new_node->key = Name;
			new_control = new ControlBar;
			new_node->p = new_control;
			if(!new_node->p)
			{
				error_out("Root::CreateControlText - 创建控件Bar失败 - 无法获得内存!");
				result = false;
			}
			else
			{
				if(!new_control->LoadControlBar(PathName, X, Y))
				{
					error_out("创建控件Bar失败!");
					result = false;
				}
				else
				{
					rb_tree.Insert(new_node);
				}
			}
		}

		if(result)
			return new_control;

		return NULL;
	}

	ControlList* Root::CreateControlList(KeyType Name, const char* PathName, int X, int Y)
	{
		bool result(true);
		RBTreeNode *new_node = new RBTreeNode;
		ControlList *new_control = NULL;
		if(!new_node)
		{
			error_out("Root::CreateControlText - 创建红黑树节点失败 - 无法获得内存!");
			result = false;
		}
		else
		{
			new_node->key = Name;
			new_control = new ControlList;
			new_node->p = new_control;
			if(!new_node->p)
			{
				error_out("Root::CreateControlText - 创建控件List失败 - 无法获得内存!");
				result = false;
			}
			else
			{
				if(!new_control->LoadControlList(PathName, X, Y))
				{
					error_out("创建控件List失败!");
					result = false;
				}
				else
				{
					rb_tree.Insert(new_node);
				}
			}
		}

		if(result)
			return new_control;

		return NULL;
	}

	ControlText& Root::GetControlText(KeyType Name)
	{
		RBTreeNode* node = rb_tree.Search(Name);

		if(node)
			return *(ControlText*)(node->p);
		else
		{
			string err = "Root::GetControlText - 无法获控件Text\""+ Name +"\"!";
			error_out(err);
			return error_control_text;
		}
	}

	ControlButton& Root::GetControlButton(KeyType Name)
	{
		RBTreeNode* node = rb_tree.Search(Name);

		if(node)
			return *(ControlButton*)(node->p);
		else
		{
			string err = "Root::GetControlButton - 无法获控件Button\""+ Name +"\"!";
			error_out(err);
			return error_control_button;
		}
	}

	ControlBar& Root::GetControlBar(KeyType Name)
	{
		RBTreeNode* node = rb_tree.Search(Name);

		if(node)
			return *(ControlBar*)(node->p);
		else
		{
			string err = "Root::GetControlBar - 无法获控件Bar\""+ Name +"\"!";
			error_out(err);
			return error_control_bar;
		}
	}

	ControlList& Root::GetControlList(KeyType Name)
	{
		RBTreeNode* node = rb_tree.Search(Name);

		if(node)
			return *(ControlList*)(node->p);
		else
		{
			string err = "Root::GetControlList - 无法获控件List\""+ Name +"\"!";
			error_out(err);
			return error_control_list;
		}
	}

} // end namespace Orz


















