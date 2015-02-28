
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
            error_out("Root::Go - SDL ��ʼ��ʧ��!");
        }

        device.Init();
        platform.Init();

        // �����豸\ƽ̨
        CreateScene();

        // SDL �¼�
        SDL_Event event;

        is_loop = true;
        while(is_loop)
        {
            // ����ϵͳ�¼�
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    // �����¼�
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                                break;
                            default: break;
                        }break;


                    // ����¼�
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

                // �����¼�
                default: break;
                }
            }

            // �ı䳡��
            UpdateScene();

			#ifdef CodeDebug
				// ���Ƶ����õ�ͼ��
				UpdateDebugScene();
			#endif

            // ��ͼ
            device.Present();
        }
    }

    // ����һ������
    Animate* Root::CreateAnimate(KeyType Name, const char *NamePath)
    {
        bool result(true);
        RBTreeNode *new_node = new RBTreeNode;
        Animate *new_animate = NULL;
        if(!new_node)
        {
            error_out("Root::CreateAnimate - ����������ڵ�ʧ�� - �޷�����ڴ�!");
            result = false;
        }
        else
        {
            new_node->key = Name;
            new_animate = new Animate();
            new_node->p = new_animate;
            if(!new_node->p)
            {
                error_out("Root::CreateAnimate - ��������ʧ�� - �޷�����ڴ�!");
                result = false;
            }
            else
            {
                if(!new_animate->LoadAnimate(NamePath))
                {
                    error_out("��������ʧ��!");
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

    // �õ�����
    Animate& Root::GetAnimate(KeyType Name)
    {
        RBTreeNode* node = rb_tree.Search(Name);

        if(node)
            return *(Animate*)(node->p);
        else
        {
            string err = "Root::GetAnimate - �޷���ö���\""+ Name +"\"!";
            error_out(err);
            return error_animate;
        }
    }

    // ������д��
    Writer* Root::CreateWriter(KeyType Name, std::string FontName, std::string Text, int FontSize, Color FontColor, Rect DestRect)
    {
        bool result(true);
        RBTreeNode *new_node = new RBTreeNode;
        Writer *new_writer = NULL;
        if(!new_node)
        {
            error_out("Root::CreateWriter - ����������ڵ�ʧ�� - �޷�����ڴ�!");
            result = false;
        }
        else
        {
            new_node->key = Name;
            new_writer = new Writer;
            new_node->p = new_writer;
            if(!new_node->p)
            {
                error_out("Root::CreateWriter - ����д��ʧ�� - �޷�����ڴ�!");
                result = false;
            }
            else
            {
				if(!new_writer->CreateWriter(FontName.c_str(), Text.c_str(), FontSize, FontColor, DestRect))
                {
                    error_out("��������ʧ��!");
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

    // �õ���д��
    Writer& Root::GetWriter(KeyType Name)
    {
        RBTreeNode* node = rb_tree.Search(Name);

        if(node)
            return *(Writer*)(node->p);
        else
        {
            string err = "Root::GetWriter - �޷������д��\""+ Name +"\"!";
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
			error_out("Root::CreateControlText - ����������ڵ�ʧ�� - �޷�����ڴ�!");
			result = false;
		}
		else
		{
			new_node->key = Name;
			new_control = new ControlText;
			new_node->p = new_control;
			if(!new_node->p)
			{
				error_out("Root::CreateControlText - �����ؼ�Textʧ�� - �޷�����ڴ�!");
				result = false;
			}
			else
			{
				if(!new_control->CreateControlText(ControlName, X, Y, Width, Height, FontName, FontSize, Text, TextColor, BackgroundColor))
				{
					error_out("�����ؼ�Textʧ��!");
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
			error_out("Root::CreateControlText - ����������ڵ�ʧ�� - �޷�����ڴ�!");
			result = false;
		}
		else
		{
			new_node->key = Name;
			new_control = new ControlButton;
			new_node->p = new_control;
			if(!new_node->p)
			{
				error_out("Root::CreateControlText - �����ؼ�Buttonʧ�� - �޷�����ڴ�!");
				result = false;
			}
			else
			{
				if(!new_control->LoadControlButton(PathName, X, Y))
				{
					error_out("�����ؼ�Buttonʧ��!");
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
			error_out("Root::CreateControlText - ����������ڵ�ʧ�� - �޷�����ڴ�!");
			result = false;
		}
		else
		{
			new_node->key = Name;
			new_control = new ControlBar;
			new_node->p = new_control;
			if(!new_node->p)
			{
				error_out("Root::CreateControlText - �����ؼ�Barʧ�� - �޷�����ڴ�!");
				result = false;
			}
			else
			{
				if(!new_control->LoadControlBar(PathName, X, Y))
				{
					error_out("�����ؼ�Barʧ��!");
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
			error_out("Root::CreateControlText - ����������ڵ�ʧ�� - �޷�����ڴ�!");
			result = false;
		}
		else
		{
			new_node->key = Name;
			new_control = new ControlList;
			new_node->p = new_control;
			if(!new_node->p)
			{
				error_out("Root::CreateControlText - �����ؼ�Listʧ�� - �޷�����ڴ�!");
				result = false;
			}
			else
			{
				if(!new_control->LoadControlList(PathName, X, Y))
				{
					error_out("�����ؼ�Listʧ��!");
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
			string err = "Root::GetControlText - �޷���ؼ�Text\""+ Name +"\"!";
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
			string err = "Root::GetControlButton - �޷���ؼ�Button\""+ Name +"\"!";
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
			string err = "Root::GetControlBar - �޷���ؼ�Bar\""+ Name +"\"!";
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
			string err = "Root::GetControlList - �޷���ؼ�List\""+ Name +"\"!";
			error_out(err);
			return error_control_list;
		}
	}

} // end namespace Orz


















