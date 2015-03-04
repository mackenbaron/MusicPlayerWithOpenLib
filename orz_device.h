
#ifndef ORZ_DEVICE_H_INCLUDED
#define ORZ_DEVICE_H_INCLUDED

#include "orz_base_zplay.h"
#include "orz_base_device_input.h"
#include "orz_base_device_display.h"

namespace Orz
{
	class _Device
	{
	private:
		friend class _Manager;

		bool Init();
	public:


		// 音频设备
		BaseZPlay sound;

		// 输入设备
		_DeviceInput input;

		// 视频设备
		_DeviceDisplay display;
	};
}

#endif