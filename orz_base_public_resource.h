#ifndef ORZ_BASE_PUBLIC_RESOURCE_INCLUDE
#define ORZ_BASE_PUBLIC_RESOURCE_INCLUDE

// ���ƴ����ѡ��
#include "orz_config.h"
#include "orz_log.h"

// ����
#include "orz_base_text_convert.h"
#include "orz_base_math.h"

// ��
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

	// д��
	extern Writer error_writer;

	// ����
	extern Animate error_animate;

	// ����
	extern BaseSDL sdl;

	// ƽ̨
	extern _Platform platform;

	// �豸
	extern _Device device;

	// ������
	extern _Manager manager;
}

#endif