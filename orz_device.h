
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


		// ��Ƶ�豸
		BaseZPlay sound;

		// �����豸
		_DeviceInput input;

		// ��Ƶ�豸
		_DeviceDisplay display;
	};
}

#endif