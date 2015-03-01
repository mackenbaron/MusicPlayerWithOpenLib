
#include "orz_option.h"
#include "orz_base_public_resource.h"
#include "orz_log.h"

namespace Orz
{
	void Management::Go(bool (*_CreateScene)(), void (*_UpdateScene)())
	{
		if(!sdl.Init())
		{
			error_out("Root::Go - SDL 初始化失败!");
		}

		// 初始化设备
		device.Init();
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
			device.Present();
		}
	}
}