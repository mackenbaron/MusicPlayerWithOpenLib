#ifndef ORZ_BASE_PUBLIC_RESOURCE_INCLUDE
#define ORZ_BASE_PUBLIC_RESOURCE_INCLUDE

// 控制代码的选项
#include "orz_config.h"

// 工具
#include "orz_base_text_convert.h"
#include "orz_base_math.h"
const Orz::Color RedColor = {255, 0,0,0};

// 类
#include "orz_platform.h"
#include "orz_device.h"
#include "orz_management.h"


// 平台
extern Orz::_Platform platform;

// 设备
extern Orz::_Device device;

// 管理者
extern Orz::_Manager manager;

#endif