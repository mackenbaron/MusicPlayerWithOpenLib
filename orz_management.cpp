
#include "orz_log.h"
#include "orz_base_public_resource.h"
#include "orz_base_private_resource.h"

namespace Orz
{
	_Manager::_Manager():
	element_root(ELEMENT_TYPE_ROOT, 0, 0, 0, 0, -0.1f),
	is_loop(true)
	{
	}

	void _Manager::Go(bool (*_CreateScene)(), void (*_UpdateScene)())
	{
		if(!device.Init())
		{
			error_out("Root::Go - SDL 初始化失败!");
		}

		// 初始化设备
		platform.Init();

		// 创建设备\平台
		_CreateScene();

		// SDL 事件
		SDL_Event event;

		is_loop = true;

		while(is_loop)
		{
			// 处理系统事件
			platform.DealSystemMessage(event);

			// 改变场景
			_UpdateScene();

			// 绘图
			PresentScene();
		}
	}

	void _Manager::QuitScene()
	{
		is_loop = false;
	}

	// 创建一个动画
	Animate* _Manager::CreateAnimate(KeyType Name, const char *NamePath)
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
	Animate& _Manager::GetAnimate(KeyType Name)
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
	Writer* _Manager::CreateWriter(KeyType Name, std::string FontName, std::string Text, int FontSize, Color FontColor, Rect DestRect)
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
	Writer& _Manager::GetWriter(KeyType Name)
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

	ControlText* _Manager::CreateControlText(KeyType Name, const char *ControlName, int X, int Y, int Width, int Height, const char *FontName, int FontSize, const char *Text, Color &TextColor, Color &BackgroundColor)
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

	ControlButton* _Manager::CreateControlButton(KeyType Name, const char* PathName, int X, int Y)
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

	ControlBar* _Manager::CreateControlBar(KeyType Name, const char* PathName, int X, int Y)
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

	ControlList* _Manager::CreateControlList(KeyType Name, const char* PathName, int X, int Y)
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

	ControlText& _Manager::GetControlText(KeyType Name)
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

	ControlButton& _Manager::GetControlButton(KeyType Name)
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

	ControlBar& _Manager::GetControlBar(KeyType Name)
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

	ControlList& _Manager::GetControlList(KeyType Name)
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

	void _Manager::PresentScene()
	{



		// 绘图
		device.display.Present();
	}

	void _Manager::UpdateDebugScene()
	{

	}

}