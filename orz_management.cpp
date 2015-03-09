
#include "orz_log.h"
#include "orz_management.h"
#include "orz_base_public_resource.h"

namespace Orz
{
	ElementRoot::ElementRoot():
	BaseElement(ELEMENT_TYPE_ROOT, 0, 0, 0, 0, 0.0f)
	{

	}

	void ElementRoot::DoContact()
	{

	}

	void ElementRoot::DoContactReset()
	{

	}

	void ElementRoot::DoDraw()
	{

	}

	_Manager::_Manager():
	is_loop(true),
	element_that_have_contact(NULL)
	{
	}

	void _Manager::Go(bool (*_CreateScene)(), void (*_UpdateScene)())
	{
		if(!device.Init())
		{
			error_out("Root::Go - SDL ��ʼ��ʧ��!");
		}

		// ��ʼ���豸
		platform.Init();

		error_element.ChangePosition(0,0);

		// �����豸\ƽ̨
		_CreateScene();

		int sw, sh;
		platform.GetWindowSize(sw, sh);
		element_root.ChangeSize(sw, sh);

		// SDL �¼�
		SDL_Event event;

		is_loop = true;

		while(is_loop)
		{
			// ����ϵͳ�¼�
			platform.DealSystemMessage(event);

			// �Ӵ�
			element_root.Contact();

			// Ѱ����Ϣ
			element_that_have_contact =  &element_root.SearchChildThatHaveContact();
			if (element_that_have_contact == &error_element)
			{
				is_have_element_that_have_contact = false;
			}else
			{
				is_have_element_that_have_contact = true;
			}

			// �ı䳡��
			_UpdateScene();

			// ����
			manager.GerRoot().Draw();

			// ��ͼ
			PresentScene();
		}

		// �ͷ��ڴ�
		element_root.Free();
	}

	void _Manager::QuitScene()
	{
		is_loop = false;
	}

	// ����һ������
	Animate* _Manager::CreateAnimate(KeyType Name, const char *NamePath, const Rect &AnimateRect)
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
				if(!new_animate->LoadAnimate(NamePath, AnimateRect))
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

	Sprite* _Manager::CreateSprite(KeyType Name, const char *NamePath, const Rect &SpriteRect)
	{
		bool result(true);
		RBTreeNode *new_node = new RBTreeNode;
		Sprite *new_sprite = NULL;
		if(!new_node)
		{
			error_out("Root::CreateAnimate - ����������ڵ�ʧ�� - �޷�����ڴ�!");
			result = false;
		}
		else
		{
			new_node->key = Name;
			new_sprite = new Sprite();
			new_node->p = new_sprite;
			if(!new_node->p)
			{
				error_out("Root::CreateAnimate - ��������ʧ�� - �޷�����ڴ�!");
				result = false;
			}
			else
			{
				if(!new_sprite->LoadSprite(NamePath, SpriteRect))
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
			return new_sprite;

		return NULL;
	}

	// ������д��
	Writer* _Manager::CreateWriter(KeyType Name, std::string FontName, std::string Text, int FontSize, Color FontColor, Rect DestRect)
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

	ControlText* _Manager::CreateControlText(KeyType Name, const char *ControlName, const Rect &ControlRect, Color &BackgroundColor, const char *FontName, int FontSize, const char *Text, Color &TextColor)
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
				if(!new_control->CreateControlText(ControlName, ControlRect, BackgroundColor, FontName, FontSize, Text, TextColor))
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

	ControlButton* _Manager::CreateControlButton(KeyType Name, const char* ControlName, const Rect &ControlRect, const Color &BackgroundColor)
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
				if(!new_control->CreateControlButton(ControlName, ControlRect, BackgroundColor))
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

	ControlScrollBar* _Manager::CreateControlScrollBar(KeyType Name, const char* ControlName, ControlDirect Direct, const Rect &ControlRect, const Color &BackgroundColorTrough, const Color &BackgroundColorBar)
	{
		bool result(true);
		RBTreeNode *new_node = new RBTreeNode;
		ControlScrollBar *new_control = NULL;
		if(!new_node)
		{
			error_out("Root::CreateControlText - ����������ڵ�ʧ�� - �޷�����ڴ�!");
			result = false;
		}
		else
		{
			new_node->key = Name;
			new_control = new ControlScrollBar;
			new_node->p = new_control;
			if(!new_node->p)
			{
				error_out("Root::CreateControlText - �����ؼ�Barʧ�� - �޷�����ڴ�!");
				result = false;
			}
			else
			{
				if(!new_control->CreateControlScrollBar(ControlName, Direct, ControlRect, BackgroundColorTrough, BackgroundColorBar ))
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

	ControlList* _Manager::CreateControlList(KeyType Name, const char* ControlName, const Rect &ControlRect, const Color &BackgroundColor, const char *FontName, int FontSize)
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
				if(!new_control->CreateControlList(ControlName, ControlRect, BackgroundColor, FontName, FontSize))
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

	// �õ�����
	Animate& _Manager::GetAnimate(KeyType Name)
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

	// �õ���д��
	Writer& _Manager::GetWriter(KeyType Name)
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

	ControlText& _Manager::GetControlText(KeyType Name)
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

	ControlButtonWithWriter& _Manager::GetControlButton(KeyType Name)
	{
		RBTreeNode* node = rb_tree.Search(Name);

		if(node)
			return *(ControlButtonWithWriter*)(node->p);
		else
		{
			string err = "Root::GetControlButton - �޷���ؼ�Button\""+ Name +"\"!";
			error_out(err);
			return error_control_button_with_writer;
		}
	}

	ControlScrollBar& _Manager::GetControlBar(KeyType Name)
	{
		RBTreeNode* node = rb_tree.Search(Name);

		if(node)
			return *(ControlScrollBar*)(node->p);
		else
		{
			string err = "Root::GetControlBar - �޷���ؼ�Bar\""+ Name +"\"!";
			error_out(err);
			return error_control_scroll_bar;
		}
	}

	ControlList& _Manager::GetControlList(KeyType Name)
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

	void _Manager::PresentScene()
	{
		// ��ͼ
		device.display.Present();
	}

	void _Manager::UpdateDebugScene()
	{

	}

	BaseElement& _Manager::GetElementThatHaveContact()
	{
		return *element_that_have_contact;
	}

	bool _Manager::IsHaveElementThatHaveContact()
	{
		return is_have_element_that_have_contact;
	}

	BaseElement& _Manager::GerRoot()
	{
		return element_root;
	}

}