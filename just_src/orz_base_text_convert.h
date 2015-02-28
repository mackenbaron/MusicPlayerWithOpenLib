#ifndef ORZ_BASE_TEXT_CONVERT_H_INCLUDED
#define ORZ_BASE_TEXT_CONVERT_H_INCLUDED

#include "orz_log.h"
#include <iconv.h>

// ת���ռ�Ĵ�С
#define MAX_ARRAY 555

namespace Orz
{
	// ת���Ĺ����ռ�
	extern char text_output_buffer[MAX_ARRAY];

	// ת�� GBK �� UTF8 ����һ���ַ�����ַ. ���Ƿ���ռ�!!!
	char* ConvertTextFromeGBKToUTF8(const char *text_gbk);

	// ת�� GBK �� UTF16 ����һ���ַ�����ַ. ���Ƿ���ռ�!!!
	char* ConvertTextFromeGBKToUTF16(const char *text_gbk);

	// ת�� UTF8 �� GBK ����һ���ַ�����ַ. ���Ƿ���ռ�!!!
	char* ConvertTextFromeUTF8oGBKT(const char *text_utf8);
}


#endif // ORZ_BASE_TEXT_CONVERT_H_INCLUDED

