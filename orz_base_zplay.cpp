
#include "orz_config.h"
#include "orz_base_zplay.h"
#include "orz_base_time.h"
#include "orz_base_text_convert.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Orz
{
	BaseZPlay::BaseZPlay()
	{
		Init();
		last_get_fft_time = 0;
		last_get_fft_top_time = 0;
	}

	BaseZPlay::~BaseZPlay()
	{
		// 结束ZPaly
		player->Release();
		player = nullptr;
	}

	bool BaseZPlay::Init()
	{
		// 创建 ZPlay
		player = CreateZPlay();

		if(player)
			return true;

		return false;
	}

	// 读取音频文件
	bool BaseZPlay::Load(const char *NamePath)
	{
		// 检测文件名是否有效
		if(!NamePath)
		{
			#ifdef CodeDebug
				cout<<"BaseZPlay: 输入了无效的文件路径 !"<<endl;
				cout<<"BaseZPlay: 打开文件\""<<NamePath<<"\"失败"<<endl;
				cout<<"来自libZPlay的错误输出: "<<player->GetError()<<endl;
			#endif // CodeDebug

			return false;
		}

		// 打开文件并自动侦测文件类型
		if(player->OpenFile(NamePath, sfAutodetect) == 0)
		{
			#ifdef CodeDebug
				cout<<"BaseZPlay: 打开文件\""<<NamePath<<"\"失败"<<endl;
				cout<<"来自libZPlay的错误输出: "<<player->GetError()<<endl;
			#endif // CodeDebug
			return false;
		}
		else
		{
			// 获取文件 ID3 信息
			if(player->LoadID3Ex(&id3_gbk, 0) == 0) // 第二个参数 0 代表不解析图片
			{
				#ifdef CodeDebug
					cout<<"BaseZPlay: 文件没有 ID3 信息"<<endl;
				#endif // CodeDebug
			}
			else
			{
				// 手动转换
				id3_utf8.Title					= ConvertTextFromeGBKToUTF8WithMemory(id3_gbk.Title		);
				id3_utf8.Artist					= ConvertTextFromeGBKToUTF8WithMemory(id3_gbk.Artist		);	
				id3_utf8.Album					= ConvertTextFromeGBKToUTF8WithMemory(id3_gbk.Album		);
				id3_utf8.Year					= ConvertTextFromeGBKToUTF8WithMemory(id3_gbk.Year		);
				id3_utf8.Comment				= ConvertTextFromeGBKToUTF8WithMemory(id3_gbk.Comment		);
				id3_utf8.TrackNum				= ConvertTextFromeGBKToUTF8WithMemory(id3_gbk.TrackNum	);
				id3_utf8.Genre					= ConvertTextFromeGBKToUTF8WithMemory(id3_gbk.Genre		);
				id3_utf8.AlbumArtist			= ConvertTextFromeGBKToUTF8WithMemory(id3_gbk.AlbumArtist	);
				id3_utf8.Composer				= ConvertTextFromeGBKToUTF8WithMemory(id3_gbk.Composer	);
				id3_utf8.OriginalArtist			= ConvertTextFromeGBKToUTF8WithMemory(id3_gbk.OriginalArtist);
				id3_utf8.Copyright				= ConvertTextFromeGBKToUTF8WithMemory(id3_gbk.Copyright	);
				id3_utf8.URL					= ConvertTextFromeGBKToUTF8WithMemory(id3_gbk.URL			);
				id3_utf8.Encoder				= ConvertTextFromeGBKToUTF8WithMemory(id3_gbk.Encoder		);
				id3_utf8.Publisher				= ConvertTextFromeGBKToUTF8WithMemory(id3_gbk.Publisher	);

				id3_utf8.BPM = id3_gbk.BPM;
			}

			// 获取流信息
			player->GetStreamInfo(&info);
		}

		return true;
	}

	bool BaseZPlay::LoadFileID3(const char *NamePath, TID3Info *Id3Information)
	{
		if(!NamePath)
		{

		#ifdef CodeDebug
			cout<<"BaseZPlay::LoadID3: 输入了无效的文件路径 !"<<endl;
			cout<<"BaseZPlay::LoadID3: 打开文件\""<<NamePath<<"\"失败"<<endl;
		#endif // CodeDebug
			
			Id3Information = NULL;
			return false;
		}

		return player->LoadFileID3(NamePath, sfAutodetect, id3Version1, Id3Information);		
	}

	// 获取音频文件总时间
	void BaseZPlay::GetTotalTime(unsigned int &hour, unsigned int &minute, unsigned int &second, unsigned int &millisecond)
	{
		hour = info.Length.hms.hour;
		minute = info.Length.hms.minute;
		second = info.Length.hms.second;
		millisecond = info.Length.hms.millisecond;
	}

	void BaseZPlay::GetTotalTime(MusicTimeTable &table)
	{
		table.hour = info.Length.hms.hour;
		table.minute = info.Length.hms.minute;
		table.second = info.Length.hms.second;
		table.millisecond = info.Length.hms.millisecond;
	}

	// 获取当前歌曲播放状态
	PlayState BaseZPlay::GetStatue()
	{
		player->GetStatus(&status);

		if(status.fPlay)
			return PLAY; // 播放中
		else if(status.fPause)
			return PAUSE; // 暂停中
		else
			return STOP; // 歌曲已停止
	}


	// 获取当前歌曲播放状态
	void BaseZPlay::GetCurrTime(unsigned int &hour, unsigned int &minute, unsigned int &second)
	{
		player->GetPosition(&position);
		hour = position.hms.hour;
		minute = position.hms.minute;
		second = position.hms.second;
	}

	void BaseZPlay::GetCurrTime(unsigned int &hour, unsigned int &minute, unsigned int &second, unsigned int &millisecond)
	{
		player->GetPosition(&position);
		hour = position.hms.hour;
		minute = position.hms.minute;
		second = position.hms.second;
		millisecond = position.hms.millisecond;
	}

	void BaseZPlay::GetCurrTime(MusicTimeTable &table)
	{
		player->GetPosition(&position);
		table.hour = position.hms.hour;
		table.minute = position.hms.minute;
		table.second = position.hms.second;
		table.millisecond = position.hms.millisecond;
	}

	const TID3InfoEx& BaseZPlay::GetCurrMusicID3GBK()
	{
		return id3_gbk;
	}

	const TID3InfoEx& BaseZPlay::GetCurrMusicID3UTF8()
	{
		return id3_utf8;
	}

	//void BaseZPlay::GetFFTDate(int **LeftData, int **RightData, int *Size)
	//{
	//	int NumberOfHarmonics = (FFT_POINT_NUNBER / 2) + 1;
	//	if (0==player->GetFFTData(FFT_POINT_NUNBER, fwRectangular, &NumberOfHarmonics, NULL,FFTDataLeft, FFTDataRight, NULL, NULL))
	//	{
	//		cout<<"BaseZPlay::GetFFTDate 获取 FFTData 失败"<<endl;

	//		// 检测是否是 2 的 n 次方
	//		int test_last_number = FFT_POINT_NUNBER;
	//		int test_curr_number = test_last_number;
	//		do 
	//		{
	//			if (test_last_number % 2)
	//			{
	//				cout<<"BaseZPlay::GetFFTDate ---- FFT_POINT_NUNBER 不是 2 的 N 次方!!!!!!!!!"<<endl;
	//				break;
	//			}

	//		} while (test_last_number %= 2);
	//		cout<<"来自libZPlay的错误输出: "<<player->GetError()<<endl;
	//	}

	//	*LeftData = FFTDataLeft;
	//	*RightData = FFTDataRight;
	//	*Size = NumberOfHarmonics;
	//}

	void BaseZPlay::GetFFTDate(int **Data, int **DataTop, int *Size)
	{
		int NumberOfHarmonics = (FFT_POINT_NUNBER / 2) + 1;
		unsigned long _current_time = GetTickTime();
		if (_current_time - last_get_fft_time > 30)
		{
			if (0==player->GetFFTData(FFT_POINT_NUNBER, fwBartlettHann, &NumberOfHarmonics, NULL, FFTDataLeft, FFTDataRight, NULL, NULL))
			{
				cout<<"BaseZPlay::GetFFTDate 获取 FFTData 失败"<<endl;

				// 检测是否是 2 的 n 次方
				int test_last_number = FFT_POINT_NUNBER;
				int test_curr_number = test_last_number;
				do 
				{
					if (test_last_number % 2)
					{
						cout<<"BaseZPlay::GetFFTDate ---- FFT_POINT_NUNBER 不是 2 的 N 次方!!!!!!!!!"<<endl;
						break;
					}

				} while (test_last_number %= 2);
				cout<<"来自libZPlay的错误输出: "<<player->GetError()<<endl;
			}
		
			for(int i=0; i < NumberOfHarmonics;i++)
			{
				this->FFTData[i] = (FFTDataLeft[i] + FFTDataRight[i]);
				if (FFTData[i] > FFTTopData[i])
				{
					FFTTopData[i] = FFTData[i];
				}
			}

			//for(int i=0; i < NumberOfHarmonics;i++)
			//{
			//	FFTData[i] *= 0.01;
			//}

			last_get_fft_time = _current_time;
		}
		
		// 降调
		if (_current_time - last_get_fft_top_time > 30)
		{
			for(int i=0; i < NumberOfHarmonics;i++)
			{
				FFTTopData[i] -= (_current_time - last_get_fft_top_time) * 0.005f;
				if (FFTTopData[i] < 0)
					FFTTopData[i] = 0;
			}

			last_get_fft_top_time = _current_time;
		}

		//for(int i=0; i < NumberOfHarmonics;i++)
		//{
		//	FFTTopData[i] -= 1;
		//	if (FFTTopData[i] < 0)
		//		FFTTopData[i] = 0;
		//}
		

		*DataTop = FFTTopData;
		*Data = FFTData;
		*Size = NumberOfHarmonics;
	}

	void BaseZPlay::SetTimeBySecond(unsigned int second)
	{
		TStreamTime temp_time_table={second};
		player->Seek(tfSecond, &temp_time_table, smFromBeginning);
	}

}








