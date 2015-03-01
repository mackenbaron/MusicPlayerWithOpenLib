
#include "orz_base_text_convert.h"
namespace Orz
{
	char text_output_buffer[MAX_ARRAY]={0};

	char* ConvertTextFromeGBKToUTF8(const char *text_gbk)
	{
		text_output_buffer[0] = NULL;

		// 打开转换
		iconv_t converter = iconv_open("UTF-8", "gbk");

		// 检测是否支持转换----------------------------------------------
		if(converter== iconv_t(-1))
		{
			error_out("ConvertGBKToUTF8 - 不支持的转换: gbk ----> utf8");
		}
		else
		{
			const char *input = text_gbk; // 指向要转换的字符串
			char *output = text_output_buffer; // 指向输出的工作空间

			size_t in_left_size=strlen(input)+1; // 要转换的字节数+1 , 可以读取到 0x00, 以停止转换
			size_t out_left_size=MAX_ARRAY; // 最多要转换多少字节,用来保证函数的准确和安全

			//转换-------------------------------------------------------------
			if(iconv(converter, &input, &in_left_size, &output, &out_left_size)==(size_t)-1)
			{
				error_out("ConvertGBKToUTF8 - 转换失败");
			}
		}

		// 关闭转换---------------------------------------------------------
		iconv_close(converter);

		return text_output_buffer;
	}

	char* ConvertTextFromeGBKToUTF16(const char *text_gbk)
	{
		text_output_buffer[0] = NULL;

		// 打开转换
		iconv_t converter = iconv_open("UTF-16", "gbk");

		// 检测是否支持转换----------------------------------------------
		if(converter== iconv_t(-1))
		{
			error_out("ConvertGBKToUTF8 - 不支持的转换: gbk ----> utf16");
		}
		else
		{
			const char *input = text_gbk; // 指向要转换的字符串
			char *output = text_output_buffer; // 指向输出的工作空间

			size_t in_left_size=strlen(input)+1; // 要转换的字节数+1 , 可以读取到 0x00, 以停止转换
			size_t out_left_size=MAX_ARRAY; // 最多要转换多少字节,用来保证函数的准确和安全

			//转换-------------------------------------------------------------
			if(iconv(converter, &input, &in_left_size, &output, &out_left_size)==(size_t)-1)
			{
				error_out("ConvertGBKToUTF16 - 转换失败");
			}
		}

		// 关闭转换---------------------------------------------------------
		iconv_close(converter);

		return text_output_buffer;
	}

	char* ConvertTextFromeUTF8oGBKT(const char *text_utf8)
	{
		text_output_buffer[0] = NULL;

		// 打开转换
		iconv_t converter = iconv_open("gbk", "UTF-8");

		// 检测是否支持转换----------------------------------------------
		if(converter== iconv_t(-1))
		{
			error_out("ConvertUTF8ToGBK - 不支持的转换: utf8 ----> gbk");
		}
		else
		{
			const char *input = text_utf8; // 指向要转换的字符串
			char *output = text_output_buffer; // 指向输出的工作空间

			size_t in_left_size=strlen(input)+1; // 要转换的字节数+1 , 可以读取到 0x00, 以停止转换
			size_t out_left_size=MAX_ARRAY; // 最多要转换多少字节,用来保证函数的准确和安全

			//转换-------------------------------------------------------------
			if(iconv(converter, &input, &in_left_size, &output, &out_left_size)==(size_t)-1)
			{
				error_out("ConvertUTF8ToGBK - 转换失败");
			}
		}

		// 关闭转换---------------------------------------------------------
		iconv_close(converter);

		return text_output_buffer;
	}
}
