#ifndef ORZ_BASE_PUBLIC_RESOURCE_INCLUDE
#define ORZ_BASE_PUBLIC_RESOURCE_INCLUDE

// 控制代码的选项
#include "orz_config.h"
#include "orz_log.h"

// 工具
#include "orz_base_text_convert.h"
#include "orz_base_math.h"

// 类
#include "orz_base_sdl.h"
#include "orz_platform.h"
#include "orz_device.h"
#include "orz_management.h"

namespace Orz
{
	const Color WhiteColor = {255, 255, 255, 255};
	const Color RedColor = {255, 0,0,255};
	const Color GreenColor = {0,255,0, 255};
	const Color BlueColor = {0,0,255, 255};
	const Color OriginColor = {255, 155, 0, 255};
	const Color PurpleColor = {255, 0, 255, 0};

	// 写手
	extern Writer error_writer;

	// 动画
	extern Animate error_animate;

	// 其他
	extern BaseSDL sdl;

	// 平台
	extern _Platform platform;

	// 设备
	extern _Device device;

	// 管理者
	extern _Manager manager;
}

#endif