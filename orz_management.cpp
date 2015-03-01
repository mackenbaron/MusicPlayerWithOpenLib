
#include "orz_option.h"
#include "orz_base_public_resource.h"
#include "orz_log.h"

namespace Orz
{
	void Management::Go(bool (*_CreateScene)(), void (*_UpdateScene)())
	{
		if(!sdl.Init())
		{
			error_out("Root::Go - SDL ��ʼ��ʧ��!");
		}

		// ��ʼ���豸
		device.Init();
		platform.Init();

		// �����豸\ƽ̨
		_CreateScene();

		// SDL �¼�
		SDL_Event event;

		is_loop = true;

		while(is_loop)
		{
			// ����ϵͳ�¼�
			platform.DealSystemMessage(event);

			// �ı䳡��
			_UpdateScene();

			// ��ͼ
			device.Present();
		}
	}
}