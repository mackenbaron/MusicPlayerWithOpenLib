
#include "orz_log.h"
#include "orz_management.h"
#include "orz_base_public_resource.h"

namespace Orz
{
	ElementRoot::ElementRoot():
	BaseElement(ELEMENT_TYPE_ROOT, 0, 0, 0, 0, 0.0f)
	{

	}

	bool ElementRoot::CreatElementRoot(const char *ControlName, const Rect &ElementRect)
	{
		element_name = ControlName;
		x = ElementRect.x;
		y = ElementRect.y;
		width = ElementRect.w;
		height = ElementRect.h;

		return true;
	}

	void ElementRoot::DoContact()
	{

	}

	void ElementRoot::DoContactReset()
	{

	}

	void ElementRoot::DoDraw(const Rect& DrawRect)
	{

	}


	_Manager::_Manager():
	is_loop(true)
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
		Rect root_rect = {0,0, sw, sh};
		element_root.CreatElementRoot("__root__", root_rect);

		// SDL �¼�
		SDL_Event event;

		is_loop = true;

		while(is_loop)
		{
			// ����ϵͳ�¼�
			platform.DealSystemMessage(event);

			// �Ӵ�
			element_root.Contact();

			// �ı䳡��
			_UpdateScene();

			// ����
			manager.GerRoot().Draw();

			// ��ͼ
			PresentScene();
		}

		// �ڴ��Ѿ��� RBTree rb_tree �Զ��ͷ���
		//element_root.Free();
	}

	void _Manager::QuitScene()
	{
		is_loop = false;
	}

	void _Manager::PresentScene()
	{
		// ��ͼ
		device.display.Present();
	}

	void _Manager::UpdateDebugScene()
	{

	}

	BaseElement& _Manager::GerRoot()
	{
		return element_root;
	}

	BaseElement& _Manager::SearchRoot(const char *ControlName)
	{
		return element_root.SearchChildren(ControlName);
	}

}