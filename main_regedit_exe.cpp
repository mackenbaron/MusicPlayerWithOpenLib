

#include "main_regedit_exe.h"
#include "orz_log.h"
#include <Windows.h>
#include <string>

namespace Program
{

#include <stdio.h>
#include <tchar.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

	void QueryKey(HKEY hKey) 
	{ 
		BYTE achData[MAX_VALUE_NAME] = "";

		TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
		DWORD    cbName;                   // size of name string 
		TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
		DWORD    cchClassName = MAX_PATH;  // size of class string 
		DWORD    cSubKeys=0;               // number of subkeys 
		DWORD    cbMaxSubKey;              // longest subkey size 
		DWORD    cchMaxClass;              // longest class string 
		DWORD    cValues;              // number of values for key 
		DWORD    cchMaxValue;          // longest value name 
		DWORD    cbMaxValueData;       // longest value data 
		DWORD    cbSecurityDescriptor; // size of security descriptor 
		FILETIME ftLastWriteTime;      // last write time 

		DWORD i, retCode; 

		TCHAR  achValue[MAX_VALUE_NAME]; 
		DWORD cchValue = MAX_VALUE_NAME; 

		// Get the class name and the value count. 
		retCode = RegQueryInfoKey(
			hKey,                    // key handle 
			achClass,                // buffer for class name 
			&cchClassName,           // size of class string 
			NULL,                    // reserved 
			&cSubKeys,               // number of subkeys 
			&cbMaxSubKey,            // longest subkey size 
			&cchMaxClass,            // longest class string 
			&cValues,                // number of values for this key 
			&cchMaxValue,            // longest value name 
			&cbMaxValueData,         // longest value data 
			&cbSecurityDescriptor,   // security descriptor 
			&ftLastWriteTime);       // last write time 

		// Enumerate the subkeys, until RegEnumKeyEx fails.

		if (cSubKeys)
		{
			printf( "\nNumber of subkeys: %d\n", cSubKeys);

			for (i=0; i<cSubKeys; i++) 
			{ 
				cbName = MAX_KEY_LENGTH;
				retCode = RegEnumKeyEx(hKey, i,
					achKey, 
					&cbName, 
					NULL, 
					NULL, 
					NULL, 
					&ftLastWriteTime); 
				if (retCode == ERROR_SUCCESS) 
				{
					_tprintf(TEXT("(%d) %s\n"), i+1, achKey);
				}
			}
		} 

		// Enumerate the key values. 

		if (cValues) 
		{
			printf( "\nNumber of values: %d\n", cValues);

			for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 
			{ 
				cchValue = MAX_VALUE_NAME; 
				achValue[0] = '\0'; 
				retCode = RegEnumValue(hKey, i, 
					achValue, 
					&cchValue, 
					NULL, 
					NULL,
					NULL,
					NULL);

				if (retCode == ERROR_SUCCESS ) 
				{ 
					_tprintf(TEXT("(%d) %s\n"), i+1, achValue); 
				} 


				cchValue = MAX_VALUE_NAME; 
				achData[0] = '\0'; 
				//retCode = RegEnumValueW(
				//	hKey,
				//	i,
				//	achValue,
				//	NULL,
				//	NULL,
				//	NULL,
				//	achData,
				//	&cchValue);
				retCode = RegQueryValueEx(
					hKey,
					achValue,
					NULL,
					NULL,
					achData,
					&cchValue);

				if (retCode == ERROR_SUCCESS ) 
				{ 
					_tprintf(TEXT("data: [%s](%ld)\n"), achData, cchValue); 
				} 
				else
				{
					std::cout<<"error!!:"<<GetLastError()<<std::endl;
				}
			}
		}
	}

	void QueryKeytest(HKEY hKey) 
	{ 
		// �Ӽ�----------------------------------------
		TCHAR    SubKeyName[MAX_KEY_LENGTH];	// �Ӽ�������
		DWORD    SubNameCount = MAX_KEY_LENGTH;	// �Ӽ�������

		DWORD    SubKeyCount=0;			// �Ӽ������� 
		DWORD    MaxSubKeyCount;		// �����Ӽ�������

		// ֵ---------------------------------------------
		TCHAR KeyValueName[MAX_VALUE_NAME]; // ֵ-����
		DWORD MaxKeyValueNameCount = MAX_VALUE_NAME;

		DWORD    SecurityDescriptor;	// ֵ-����

		BYTE KeyValueData[MAX_VALUE_NAME] = ""; // ֵ-����
		DWORD MaxKeyValueDataCount = MAX_VALUE_NAME;

		DWORD    KeyValueCount;			// key ��ֵ������
		DWORD    MaxKeyValueCount;		// ���� key ��ֵ������

		// ������-------------------------------------------
		DWORD i, result;


		// �õ����������� class name and the value count. 
		result = RegQueryInfoKey(
			hKey,				// key ���
			NULL,				// ���������Ļ���
			NULL,				// ��������
			0,					// ����ֵ

			&SubKeyCount,		// �Ӽ�����
			&MaxSubKeyCount,	// ����Ӽ�����
			
			NULL,				// longest class string

			&KeyValueCount,			// key ��ֵ������(��ֵ������)
			&MaxKeyValueCount,		// ���ļ�ֵ������
			&MaxKeyValueDataCount,	// ���ļ�-���ݵĳ���
			&SecurityDescriptor,	// ��-����
			NULL); // ����޸�ʱ��

		// �о� key ��ֵ(��ֵ). 
		if (KeyValueCount) 
		{
			printf( "\nNumber of values: %d\n", KeyValueCount);

			for (i=0, result=ERROR_SUCCESS; i<KeyValueCount; i++) 
			{ 
				MaxKeyValueNameCount = MAX_VALUE_NAME; 
				KeyValueName[0] = '\0';
				result = RegEnumValue(hKey, i,
					KeyValueName, 
					&MaxKeyValueDataCount, 
					NULL, 
					NULL,
					NULL,
					NULL);

				if (result == ERROR_SUCCESS ) 
				{ 
					_tprintf(TEXT("(%d) %s\n"), i+1, KeyValueName); 
				} 

				MaxKeyValueDataCount = MAX_VALUE_NAME; 
				KeyValueData[0] = '\0'; 
				result = RegQueryValueEx(
					hKey,
					KeyValueName,
					NULL,
					NULL,
					KeyValueData,
					&MaxKeyValueDataCount);

				if (result == ERROR_SUCCESS ) 
				{ 
					_tprintf(TEXT("data: [%s](%ld)\n"), KeyValueData, MaxKeyValueDataCount); 
				} 
				else
				{
					std::cout<<"error!!:"<<GetLastError()<<std::endl;
				}
			}
		}
	}

	void QueryKeytest1(HKEY hKey) 
	{ 
		// �Ӽ�----------------------------------------
		TCHAR    SubKeyName[MAX_KEY_LENGTH];	// �Ӽ�������
		DWORD    SubNameCount = MAX_KEY_LENGTH;	// �Ӽ�������

		DWORD    SubKeyCount=0;			// �Ӽ������� 
		DWORD    MaxSubKeyCount;		// �����Ӽ�������

		// ֵ---------------------------------------------
		TCHAR KeyValueName[MAX_VALUE_NAME]; // ֵ-����
		DWORD MaxKeyValueNameCount = MAX_VALUE_NAME;

		DWORD    type;	// ֵ-����

		BYTE KeyValueData[MAX_VALUE_NAME] = ""; // ֵ-����
		DWORD MaxKeyValueDataCount = MAX_VALUE_NAME;

		DWORD    KeyValueCount;			// key ��ֵ������
		DWORD    MaxKeyValueCount;		// ���� key ��ֵ������

		// ��-----------------------------------------------
		char Class[MAX_VALUE_NAME];
		DWORD MaxClassCount = MAX_VALUE_NAME;

		// ������-------------------------------------------
		DWORD i, result;


		// �õ����������� class name and the value count. 
		result = RegQueryInfoKeyA(
			hKey,				// key ���
			Class,				// ���������Ļ���
			&MaxClassCount,				// ��������
			0,					// ����ֵ

			&SubKeyCount,		// �Ӽ�����
			&MaxSubKeyCount,	// ����Ӽ�����

			NULL,				// longest class string

			&KeyValueCount,			// key ��ֵ������(��ֵ������)
			&MaxKeyValueCount,		// ���ļ�ֵ������
			&MaxKeyValueDataCount,	// ���ļ�-���ݵĳ���
			&type,	// ��-����
			NULL); // ����޸�ʱ��

		printf("Class :          [%s]", Class);


		// �о� key ��ֵ(��ֵ).
		if (KeyValueCount) 
		{
			printf( "\nNumber of values: %d\n", KeyValueCount);
			printf("name                type                      data\n");

			for (i=0, result=ERROR_SUCCESS; i<KeyValueCount; i++) 
			{ 
				MaxKeyValueNameCount = MAX_VALUE_NAME;
				KeyValueName[0] = '\0';
				result = RegEnumValue(hKey, i,
					KeyValueName, 
					&MaxKeyValueDataCount, 
					NULL, 
					NULL,
					NULL,
					NULL);

				if (result == ERROR_SUCCESS ) 
				{ 
					_tprintf(TEXT("(%-d) %-16s"), i+1, KeyValueName); 
				}
				else
				{
					std::cout<<"error!!:"<<GetLastError()<<std::endl;
				}

				printf("%-8d", type);

				MaxKeyValueDataCount = MAX_VALUE_NAME; 
				KeyValueData[0] = '\0'; 
				result = RegQueryValueEx(
					hKey,
					KeyValueName,
					NULL,
					NULL,
					KeyValueData,
					&MaxKeyValueDataCount);

				if (result == ERROR_SUCCESS ) 
				{ 
					_tprintf(TEXT("[%s]\n"), KeyValueData); 
				} 
				else
				{
					std::cout<<"error!!:"<<GetLastError()<<std::endl;
				}
			}
		}
	}

	bool GetDefaultOpenFileWay()
	{
		// ���
		char buff_var[MAX_PATH];
		DWORD type;
		DWORD size;
		LONG result;
		HKEY key;
		DWORD data_size;
		unsigned char buff_data[MAX_PATH];

		// ���ļ�
		result = RegOpenKeyExA(HKEY_CLASSES_ROOT, ".mp3", 0, KEY_READ, &key);

		if (result != ERROR_SUCCESS)
		{
			if (result == ERROR_FILE_NOT_FOUND) {
				Orz::error_out("GetDefaultOpenFileWay - û���ҵ� .mp3 ��key");
				return true;
			} 
			else {
				Orz::error_out("GetDefaultOpenFileWay - �޷��� key");
				return false;
			}
		} 
		else
		{
			// �о��Ӽ�(���ļ���)
			//RegEnumKeyExA(key, 0, buff_var, &size, NULL, NULL, NULL, NULL);
			//std::cout<< buff_var<<std::endl;


			//if (
			//RegEnumValueA(key, 0, 
			//	buff_var, NULL, 
			//	NULL, // ����λ��
			//	&type, // ����
			//	buff_data, &data_size) != ERROR_SUCCESS)
			//{
			//	std::cout<<"error!!:"<<GetLastError()<<std::endl;
			//}
			//else
			//{
			//	std::cout<<buff_var <<std::endl<< buff_data <<std::endl;
			//}
			QueryKeytest1(key);

			int i;
		}


		// �رռ�
		RegCloseKey(key);

		return true;
	}

	bool SetDefaultOpenFileWayToThisProgram()
	{
		bool succeed(true);
		char buff_var[MAX_PATH];
		DWORD type;
		DWORD size;
		LONG result;
		HKEY key;
		DWORD data_size;
		unsigned char buff_data[MAX_PATH];

		

		const unsigned char key_value[] = "RainMusicPlayer.Mp3";
		int key_value_count = 0;
		// ��һ��: ���� MP3 ��Ĭ�ϲ��ų���------------------------------------------------
		// ���ļ�
		result = RegOpenKeyExA(HKEY_CLASSES_ROOT, ".mp3", 0, KEY_ALL_ACCESS, &key);

		if (result != ERROR_SUCCESS)
		{
			if (result == ERROR_FILE_NOT_FOUND)
				Orz::error_out("SetDefaultOpenFileWayToThisProgram - û���ҵ� .mp3 �� key");
			else
				Orz::error_out("SetDefaultOpenFileWayToThisProgram - �޷��� key");

			succeed = false;
		} 
		else
		{
			// �����Ӽ���ֵ
			//SetKeytest(key);

			result = RegSetValueExA(key, NULL, 0, REG_SZ, key_value, sizeof(key_value));
			if (result == ERROR_SUCCESS)
			{
				Orz::error_out("SetDefaultOpenFileWayToThisProgram - �޸� .mp3 ��ֵ�ɹ�");
				succeed = true;
			}
			else if (result == ERROR_FILE_NOT_FOUND)
			{
				Orz::error_out("SetDefaultOpenFileWayToThisProgram - �޷��޸� .mp3 ��key");
				succeed = false;
			} 
			else
			{
				Orz::error_out("SetDefaultOpenFileWayToThisProgram - �޷��� key");
				succeed = false;
			}


		}

		// �رռ�
		RegCloseKey(key);

		// �ڶ���: ���������ע���

		// Ҫ������Ȩ��,�����޸�ע���
		// �Ѿ������� VS2010 ����Ŀ ����--������--�嵥�ļ�
		// -> UACִ�м��� -> requireAdministrator (/level='requireAdministrator')
		// ���в��õ��Ĵ����Ӽ�Ȩ�޲���
		//////////////////////////////////////////////////////////////////////////

		// �����Ӽ� - RainMusicPlayer.Mp3
		char new_key_name[] = "RainMusicPlayer.Mp3";
		HKEY new_key(0);
		//DWORD is_new_key_exist;
		//SECURITY_ATTRIBUTES new_key_attribute = {sizeof(SECURITY_ATTRIBUTES), NULL, true};
		//result = RegCreateKeyExA(
		//	HKEY_CLASSES_ROOT,	// �������
		//	signed_key_value,	// �������Ӽ�������
		//	0,					// ϵͳ������ָ��Ϊ0
		//	NULL,				// �����Ӽ�������ͨ����ΪNULL
		//	REG_OPTION_NON_VOLATILE, // �����Ӽ�ʱ��ѡ�� ������ʽ,REG_OPTION_NON_VOLATILE(����������󲻻���ʧ)
		//	KEY_ALL_ACCESS,	// �������Ӽ��Ĳ���Ȩ��
		//	&new_key_attribute,	// ָ��SECURITY_ATTRIBUTES�ṹ��ָ��������ļ�//����
		//	&new_key, // ���ش������
		//	&is_new_key_exist	// ͨ����ΪNULL
		//	);

		result = RegCreateKeyA(HKEY_CLASSES_ROOT, new_key_name, &new_key);

		if (result == ERROR_SUCCESS)
				std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKey(Ex)A �ɹ������Ӽ�:["<<new_key_name<<"]"<<std::endl;
		else
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKey(Ex)A δ�ɹ������Ӽ�:["<<new_key_name<<"]"
			<<"ȷ�������� VS2010 ����Ŀ ����--������--�嵥�ļ� -> UACִ�м��� -> requireAdministrator (/level='requireAdministrator')"<<std::endl;


		// �����Ӽ� - RainMusicPlayer.Mp3 - shell
		const char new_key_shell_name[] = "shell";
		HKEY new_key_shell(0);
		result = RegCreateKeyA(new_key, new_key_shell_name, &new_key_shell);

		if (result == ERROR_SUCCESS)
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKeyA �ɹ������Ӽ�:["<<new_key_shell_name<<"]"<<std::endl;
		else
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKeyA δ�ɹ������Ӽ�:["<<new_key_shell_name<<"]"
			<<"ȷ�������� VS2010 ����Ŀ ����--������--�嵥�ļ� -> UACִ�м��� -> requireAdministrator (/level='requireAdministrator')"<<std::endl;

		// �����Ӽ� - RainMusicPlayer.Mp3 - shell - open
		const char new_key_open_name[] = "open";
		HKEY new_key_open(0);
		result = RegCreateKeyA(new_key_shell, new_key_open_name, &new_key_open);

		if (result == ERROR_SUCCESS)
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKeyA �ɹ������Ӽ�:["<<new_key_open_name<<"]"<<std::endl;
		else
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKeyA δ�ɹ������Ӽ�:["<<new_key_open_name<<"]"
			<<"ȷ�������� VS2010 ����Ŀ ����--������--�嵥�ļ� -> UACִ�м��� -> requireAdministrator (/level='requireAdministrator')"<<std::endl;

		// �����Ӽ� - RainMusicPlayer.Mp3 - shell - open - command
		const char new_key_command_name[] = "command";
		HKEY new_key_command(0);

		SECURITY_ATTRIBUTES new_key_command_attribute = {sizeof(SECURITY_ATTRIBUTES), NULL, true};
		result = RegCreateKeyExA(
			new_key_open,	// �������
			new_key_command_name,	// �������Ӽ�������
			0,					// ϵͳ������ָ��Ϊ0
			NULL,				// �����Ӽ�������ͨ����ΪNULL
			REG_OPTION_NON_VOLATILE, // �����Ӽ�ʱ��ѡ�� ������ʽ,REG_OPTION_NON_VOLATILE(����������󲻻���ʧ)
			KEY_ALL_ACCESS,	// �������Ӽ��Ĳ���Ȩ��
			&new_key_command_attribute,	// ָ��SECURITY_ATTRIBUTES�ṹ��ָ��������ļ�//����
			&new_key_command, // ���ش������
			NULL	// ͨ����ΪNULL
			);

		//result = RegCreateKeyA(new_key_open, new_key_command_name, &new_key_open);

		if (result == ERROR_SUCCESS)
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKeyA �ɹ������Ӽ�:["<<new_key_command_name<<"]"<<"\nresult:["<<result<<"]"<<std::endl;
		else
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKeyA δ�ɹ������Ӽ�:["<<new_key_command_name<<"]"
			<<"ȷ�������� VS2010 ����Ŀ ����--������--�嵥�ļ� -> UACִ�м��� -> requireAdministrator (/level='requireAdministrator')"<<std::endl;

		// �޸ļ�- RainMusicPlayer.Mp3 - shell - open - command ��ֵ-����
		// ��ȡ�˳�����ļ�·��
		char curr_program_path[MAX_PATH];
		result = GetModuleFileNameA(NULL, curr_program_path, MAX_PATH);
		if (result != 0)
		{
			Orz::error_out("SetDefaultOpenFileWayToThisProgram - GetModuleFileNameA �ɹ���ô˳�����ļ�·��:\n["+std::string(curr_program_path)+"]");
			succeed = true;
		}
		else
		{
			Orz::error_out("SetDefaultOpenFileWayToThisProgram - GetModuleFileNameA :δ�ɹ���ô˳�����ļ�·��");
			std::cout<<"windows������Ϣ:"<<GetLastError()<<std::endl;
			succeed = false;
		}

		unsigned char key_command_value_data[MAX_PATH];
		int index(0);
		while(index<MAX_PATH-1)
		{
			if (curr_program_path[index]==0)
			{
				key_command_value_data[index + 0] = ' ';
				key_command_value_data[index + 1] = '\"';
				key_command_value_data[index + 2] = '%';
				key_command_value_data[index + 3] = '1';
				key_command_value_data[index + 4] = '\"';
				key_command_value_data[index + 5] = 0;
				break;
			}
			key_command_value_data[index] = curr_program_path[index];
			index++;
		}

		result = RegSetValueExA(new_key_command, NULL, 0, REG_SZ, key_command_value_data, index+5);
		if (result == ERROR_SUCCESS)
		{
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegSetValueExA �޸� command ��ֵ�ɹ�"<<std::endl;
			std::cout<<"result��ֵΪ:["<<result<<"]"<<std::endl;
			succeed = true;
		}
		else
		{
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegSetValueExA �޸� command ��ֵʧ��!"<<std::endl;
			std::cout<<"result��ֵΪ:["<<result<<"]"<<std::endl;

			succeed = false;
		}


		// �رռ�
		RegCloseKey(new_key_command);
		RegCloseKey(new_key_open);
		RegCloseKey(new_key_shell);
		RegCloseKey(new_key);
		return succeed;
	}

}