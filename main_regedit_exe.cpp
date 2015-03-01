

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
		// 子键----------------------------------------
		TCHAR    SubKeyName[MAX_KEY_LENGTH];	// 子键名缓存
		DWORD    SubNameCount = MAX_KEY_LENGTH;	// 子键名长度

		DWORD    SubKeyCount=0;			// 子键的数量 
		DWORD    MaxSubKeyCount;		// 最大的子键的数量

		// 值---------------------------------------------
		TCHAR KeyValueName[MAX_VALUE_NAME]; // 值-名称
		DWORD MaxKeyValueNameCount = MAX_VALUE_NAME;

		DWORD    SecurityDescriptor;	// 值-类型

		BYTE KeyValueData[MAX_VALUE_NAME] = ""; // 值-数据
		DWORD MaxKeyValueDataCount = MAX_VALUE_NAME;

		DWORD    KeyValueCount;			// key 的值的数量
		DWORD    MaxKeyValueCount;		// 最大的 key 的值的数量

		// 记事用-------------------------------------------
		DWORD i, result;


		// 得到类名和数量 class name and the value count. 
		result = RegQueryInfoKey(
			hKey,				// key 句柄
			NULL,				// 接受类名的缓存
			NULL,				// 类名长度
			0,					// 保留值

			&SubKeyCount,		// 子键数量
			&MaxSubKeyCount,	// 最大子键数量
			
			NULL,				// longest class string

			&KeyValueCount,			// key 的值的数量(键值的数量)
			&MaxKeyValueCount,		// 最大的键值的数量
			&MaxKeyValueDataCount,	// 最大的键-数据的长度
			&SecurityDescriptor,	// 键-类型
			NULL); // 最后修改时间

		// 列举 key 的值(键值). 
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
		// 子键----------------------------------------
		TCHAR    SubKeyName[MAX_KEY_LENGTH];	// 子键名缓存
		DWORD    SubNameCount = MAX_KEY_LENGTH;	// 子键名长度

		DWORD    SubKeyCount=0;			// 子键的数量 
		DWORD    MaxSubKeyCount;		// 最大的子键的数量

		// 值---------------------------------------------
		TCHAR KeyValueName[MAX_VALUE_NAME]; // 值-名称
		DWORD MaxKeyValueNameCount = MAX_VALUE_NAME;

		DWORD    type;	// 值-类型

		BYTE KeyValueData[MAX_VALUE_NAME] = ""; // 值-数据
		DWORD MaxKeyValueDataCount = MAX_VALUE_NAME;

		DWORD    KeyValueCount;			// key 的值的数量
		DWORD    MaxKeyValueCount;		// 最大的 key 的值的数量

		// 类-----------------------------------------------
		char Class[MAX_VALUE_NAME];
		DWORD MaxClassCount = MAX_VALUE_NAME;

		// 记事用-------------------------------------------
		DWORD i, result;


		// 得到类名和数量 class name and the value count. 
		result = RegQueryInfoKeyA(
			hKey,				// key 句柄
			Class,				// 接受类名的缓存
			&MaxClassCount,				// 类名长度
			0,					// 保留值

			&SubKeyCount,		// 子键数量
			&MaxSubKeyCount,	// 最大子键数量

			NULL,				// longest class string

			&KeyValueCount,			// key 的值的数量(键值的数量)
			&MaxKeyValueCount,		// 最大的键值的数量
			&MaxKeyValueDataCount,	// 最大的键-数据的长度
			&type,	// 键-类型
			NULL); // 最后修改时间

		printf("Class :          [%s]", Class);


		// 列举 key 的值(键值).
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
		// 结果
		char buff_var[MAX_PATH];
		DWORD type;
		DWORD size;
		LONG result;
		HKEY key;
		DWORD data_size;
		unsigned char buff_data[MAX_PATH];

		// 打开文件
		result = RegOpenKeyExA(HKEY_CLASSES_ROOT, ".mp3", 0, KEY_READ, &key);

		if (result != ERROR_SUCCESS)
		{
			if (result == ERROR_FILE_NOT_FOUND) {
				Orz::error_out("GetDefaultOpenFileWay - 没有找到 .mp3 的key");
				return true;
			} 
			else {
				Orz::error_out("GetDefaultOpenFileWay - 无法打开 key");
				return false;
			}
		} 
		else
		{
			// 列举子键(子文件夹)
			//RegEnumKeyExA(key, 0, buff_var, &size, NULL, NULL, NULL, NULL);
			//std::cout<< buff_var<<std::endl;


			//if (
			//RegEnumValueA(key, 0, 
			//	buff_var, NULL, 
			//	NULL, // 保留位置
			//	&type, // 类型
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


		// 关闭键
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
		// 第一步: 设置 MP3 的默认播放程序------------------------------------------------
		// 打开文件
		result = RegOpenKeyExA(HKEY_CLASSES_ROOT, ".mp3", 0, KEY_ALL_ACCESS, &key);

		if (result != ERROR_SUCCESS)
		{
			if (result == ERROR_FILE_NOT_FOUND)
				Orz::error_out("SetDefaultOpenFileWayToThisProgram - 没有找到 .mp3 的 key");
			else
				Orz::error_out("SetDefaultOpenFileWayToThisProgram - 无法打开 key");

			succeed = false;
		} 
		else
		{
			// 设置子键的值
			//SetKeytest(key);

			result = RegSetValueExA(key, NULL, 0, REG_SZ, key_value, sizeof(key_value));
			if (result == ERROR_SUCCESS)
			{
				Orz::error_out("SetDefaultOpenFileWayToThisProgram - 修改 .mp3 的值成功");
				succeed = true;
			}
			else if (result == ERROR_FILE_NOT_FOUND)
			{
				Orz::error_out("SetDefaultOpenFileWayToThisProgram - 无法修改 .mp3 的key");
				succeed = false;
			} 
			else
			{
				Orz::error_out("SetDefaultOpenFileWayToThisProgram - 无法打开 key");
				succeed = false;
			}


		}

		// 关闭键
		RegCloseKey(key);

		// 第二步: 创建程序的注册表

		// 要求提升权限,以能修改注册表
		// 已经开启了 VS2010 的项目 属性--连接器--清单文件
		// -> UAC执行级别 -> requireAdministrator (/level='requireAdministrator')
		// 所有不用担心创建子键权限不够
		//////////////////////////////////////////////////////////////////////////

		// 创建子键 - RainMusicPlayer.Mp3
		char new_key_name[] = "RainMusicPlayer.Mp3";
		HKEY new_key(0);
		//DWORD is_new_key_exist;
		//SECURITY_ATTRIBUTES new_key_attribute = {sizeof(SECURITY_ATTRIBUTES), NULL, true};
		//result = RegCreateKeyExA(
		//	HKEY_CLASSES_ROOT,	// 父键句柄
		//	signed_key_value,	// 创建的子键的名字
		//	0,					// 系统保留，指定为0
		//	NULL,				// 定义子键类名，通常设为NULL
		//	REG_OPTION_NON_VOLATILE, // 创建子键时的选项 创建方式,REG_OPTION_NON_VOLATILE(计算机重启后不会消失)
		//	KEY_ALL_ACCESS,	// 创建后子键的操作权限
		//	&new_key_attribute,	// 指向SECURITY_ATTRIBUTES结构，指定键句柄的继//承性
		//	&new_key, // 返回创建句柄
		//	&is_new_key_exist	// 通常设为NULL
		//	);

		result = RegCreateKeyA(HKEY_CLASSES_ROOT, new_key_name, &new_key);

		if (result == ERROR_SUCCESS)
				std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKey(Ex)A 成功创建子键:["<<new_key_name<<"]"<<std::endl;
		else
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKey(Ex)A 未成功创建子键:["<<new_key_name<<"]"
			<<"确保开启了 VS2010 的项目 属性--连接器--清单文件 -> UAC执行级别 -> requireAdministrator (/level='requireAdministrator')"<<std::endl;


		// 创建子键 - RainMusicPlayer.Mp3 - shell
		const char new_key_shell_name[] = "shell";
		HKEY new_key_shell(0);
		result = RegCreateKeyA(new_key, new_key_shell_name, &new_key_shell);

		if (result == ERROR_SUCCESS)
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKeyA 成功创建子键:["<<new_key_shell_name<<"]"<<std::endl;
		else
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKeyA 未成功创建子键:["<<new_key_shell_name<<"]"
			<<"确保开启了 VS2010 的项目 属性--连接器--清单文件 -> UAC执行级别 -> requireAdministrator (/level='requireAdministrator')"<<std::endl;

		// 创建子键 - RainMusicPlayer.Mp3 - shell - open
		const char new_key_open_name[] = "open";
		HKEY new_key_open(0);
		result = RegCreateKeyA(new_key_shell, new_key_open_name, &new_key_open);

		if (result == ERROR_SUCCESS)
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKeyA 成功创建子键:["<<new_key_open_name<<"]"<<std::endl;
		else
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKeyA 未成功创建子键:["<<new_key_open_name<<"]"
			<<"确保开启了 VS2010 的项目 属性--连接器--清单文件 -> UAC执行级别 -> requireAdministrator (/level='requireAdministrator')"<<std::endl;

		// 创建子键 - RainMusicPlayer.Mp3 - shell - open - command
		const char new_key_command_name[] = "command";
		HKEY new_key_command(0);

		SECURITY_ATTRIBUTES new_key_command_attribute = {sizeof(SECURITY_ATTRIBUTES), NULL, true};
		result = RegCreateKeyExA(
			new_key_open,	// 父键句柄
			new_key_command_name,	// 创建的子键的名字
			0,					// 系统保留，指定为0
			NULL,				// 定义子键类名，通常设为NULL
			REG_OPTION_NON_VOLATILE, // 创建子键时的选项 创建方式,REG_OPTION_NON_VOLATILE(计算机重启后不会消失)
			KEY_ALL_ACCESS,	// 创建后子键的操作权限
			&new_key_command_attribute,	// 指向SECURITY_ATTRIBUTES结构，指定键句柄的继//承性
			&new_key_command, // 返回创建句柄
			NULL	// 通常设为NULL
			);

		//result = RegCreateKeyA(new_key_open, new_key_command_name, &new_key_open);

		if (result == ERROR_SUCCESS)
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKeyA 成功创建子键:["<<new_key_command_name<<"]"<<"\nresult:["<<result<<"]"<<std::endl;
		else
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegCreateKeyA 未成功创建子键:["<<new_key_command_name<<"]"
			<<"确保开启了 VS2010 的项目 属性--连接器--清单文件 -> UAC执行级别 -> requireAdministrator (/level='requireAdministrator')"<<std::endl;

		// 修改键- RainMusicPlayer.Mp3 - shell - open - command 的值-数据
		// 获取此程序的文件路径
		char curr_program_path[MAX_PATH];
		result = GetModuleFileNameA(NULL, curr_program_path, MAX_PATH);
		if (result != 0)
		{
			Orz::error_out("SetDefaultOpenFileWayToThisProgram - GetModuleFileNameA 成功获得此程序的文件路径:\n["+std::string(curr_program_path)+"]");
			succeed = true;
		}
		else
		{
			Orz::error_out("SetDefaultOpenFileWayToThisProgram - GetModuleFileNameA :未成功获得此程序的文件路径");
			std::cout<<"windows错误消息:"<<GetLastError()<<std::endl;
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
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegSetValueExA 修改 command 的值成功"<<std::endl;
			std::cout<<"result的值为:["<<result<<"]"<<std::endl;
			succeed = true;
		}
		else
		{
			std::cout<<"SetDefaultOpenFileWayToThisProgram - RegSetValueExA 修改 command 的值失败!"<<std::endl;
			std::cout<<"result的值为:["<<result<<"]"<<std::endl;

			succeed = false;
		}


		// 关闭键
		RegCloseKey(new_key_command);
		RegCloseKey(new_key_open);
		RegCloseKey(new_key_shell);
		RegCloseKey(new_key);
		return succeed;
	}

}