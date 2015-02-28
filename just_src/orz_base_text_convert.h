#ifndef ORZ_BASE_TEXT_CONVERT_H_INCLUDED
#define ORZ_BASE_TEXT_CONVERT_H_INCLUDED

#include "orz_log.h"
#include <iconv.h>

// 转换空间的大小
#define MAX_ARRAY 555

namespace Orz
{
	// 转换的工作空间
	extern char text_output_buffer[MAX_ARRAY];

	// 转换 GBK 到 UTF8 返回一个字符串地址. 不是分配空间!!!
	char* ConvertTextFromeGBKToUTF8(const char *text_gbk);

	// 转换 GBK 到 UTF16 返回一个字符串地址. 不是分配空间!!!
	char* ConvertTextFromeGBKToUTF16(const char *text_gbk);

	// 转换 UTF8 到 GBK 返回一个字符串地址. 不是分配空间!!!
	char* ConvertTextFromeUTF8oGBKT(const char *text_utf8);
}


#endif // ORZ_BASE_TEXT_CONVERT_H_INCLUDED

