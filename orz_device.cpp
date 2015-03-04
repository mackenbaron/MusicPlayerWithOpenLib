
#include "orz_base_public_resource.h"
#include "orz_base_private_resource.h"
#include "orz_device.h"
#include "orz_base_time.h"

namespace Orz
{


	bool _Device::Init()
	{
		return display.Init()&&sound.Init()&&input.Init();
	}

}
