
#include "orz_base_text_convert.h"
namespace Orz
{
	char text_output_buffer[MAX_ARRAY]={0};

	char* ConvertTextFromeGBKToUTF8(const char *text_gbk)
	{
		text_output_buffer[0] = NULL;

		// ��ת��
		iconv_t converter = iconv_open("UTF-8", "gbk");

		// ����Ƿ�֧��ת��----------------------------------------------
		if(converter== iconv_t(-1))
		{
			error_out("ConvertGBKToUTF8 - ��֧�ֵ�ת��: gbk ----> utf8");
		}
		else
		{
			const char *input = text_gbk; // ָ��Ҫת�����ַ���
			char *output = text_output_buffer; // ָ������Ĺ����ռ�

			size_t in_left_size=strlen(input)+1; // Ҫת�����ֽ���+1 , ���Զ�ȡ�� 0x00, ��ֹͣת��
			size_t out_left_size=MAX_ARRAY; // ���Ҫת�������ֽ�,������֤������׼ȷ�Ͱ�ȫ

			//ת��-------------------------------------------------------------
			if(iconv(converter, &input, &in_left_size, &output, &out_left_size)==(size_t)-1)
			{
				error_out("ConvertGBKToUTF8 - ת��ʧ��");
			}
		}

		// �ر�ת��---------------------------------------------------------
		iconv_close(converter);

		return text_output_buffer;
	}

	char* ConvertTextFromeGBKToUTF16(const char *text_gbk)
	{
		text_output_buffer[0] = NULL;

		// ��ת��
		iconv_t converter = iconv_open("UTF-16", "gbk");

		// ����Ƿ�֧��ת��----------------------------------------------
		if(converter== iconv_t(-1))
		{
			error_out("ConvertGBKToUTF8 - ��֧�ֵ�ת��: gbk ----> utf16");
		}
		else
		{
			const char *input = text_gbk; // ָ��Ҫת�����ַ���
			char *output = text_output_buffer; // ָ������Ĺ����ռ�

			size_t in_left_size=strlen(input)+1; // Ҫת�����ֽ���+1 , ���Զ�ȡ�� 0x00, ��ֹͣת��
			size_t out_left_size=MAX_ARRAY; // ���Ҫת�������ֽ�,������֤������׼ȷ�Ͱ�ȫ

			//ת��-------------------------------------------------------------
			if(iconv(converter, &input, &in_left_size, &output, &out_left_size)==(size_t)-1)
			{
				error_out("ConvertGBKToUTF16 - ת��ʧ��");
			}
		}

		// �ر�ת��---------------------------------------------------------
		iconv_close(converter);

		return text_output_buffer;
	}

	char* ConvertTextFromeUTF8oGBKT(const char *text_utf8)
	{
		text_output_buffer[0] = NULL;

		// ��ת��
		iconv_t converter = iconv_open("gbk", "UTF-8");

		// ����Ƿ�֧��ת��----------------------------------------------
		if(converter== iconv_t(-1))
		{
			error_out("ConvertUTF8ToGBK - ��֧�ֵ�ת��: utf8 ----> gbk");
		}
		else
		{
			const char *input = text_utf8; // ָ��Ҫת�����ַ���
			char *output = text_output_buffer; // ָ������Ĺ����ռ�

			size_t in_left_size=strlen(input)+1; // Ҫת�����ֽ���+1 , ���Զ�ȡ�� 0x00, ��ֹͣת��
			size_t out_left_size=MAX_ARRAY; // ���Ҫת�������ֽ�,������֤������׼ȷ�Ͱ�ȫ

			//ת��-------------------------------------------------------------
			if(iconv(converter, &input, &in_left_size, &output, &out_left_size)==(size_t)-1)
			{
				error_out("ConvertUTF8ToGBK - ת��ʧ��");
			}
		}

		// �ر�ת��---------------------------------------------------------
		iconv_close(converter);

		return text_output_buffer;
	}
}
