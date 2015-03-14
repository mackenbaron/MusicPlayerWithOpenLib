#ifndef ORZZPLAY_H_INCLUDED
#define ORZZPLAY_H_INCLUDED

#include <libzplay.h>
#include "orz_base_math.h"

// 必须是 2 的 n 次方!!!
#define FFT_POINT_NUNBER 256
#define HARMONIC_NUMBER ((FFT_POINT_NUNBER*/2)+1)

namespace Orz
{
    using namespace libZPlay;

    enum PlayState{PLAY, PAUSE, STOP};

    class BaseZPlay
    {
	private:
		friend class _Device;

        // 初始化 libZPlay
        bool Init();

	public:
		// 构造函数
		BaseZPlay();

		// 析构函数
        ~BaseZPlay();

        // 读取音频文件
        bool Load(const char *NamePath);
		bool LoadFileID3(const char *NamePath, TID3Info *Id3Information);

        // 获取音频文件总时间
        void GetTotalTime(unsigned int &hour, unsigned int &minute, unsigned int &second, unsigned int &millisecond);
		void GetTotalTime(MusicTimeTable &table);

        // 获取当前歌曲播放状态
        PlayState GetStatue();

        // 获取当前歌曲播放状态
        void GetCurrTime(unsigned int &hour, unsigned int &minute, unsigned int &second);
		void GetCurrTime(unsigned int &hour, unsigned int &minute, unsigned int &second, unsigned int &millisecond);
		void GetCurrTime(MusicTimeTable &table);
		void GetVolume(unsigned int &Volume);

		// 获取当前文件 ID3 信息
		const TID3InfoEx& GetCurrMusicID3GBK();
		const TID3InfoEx& GetCurrMusicID3UTF8();

		// 获取 FFT 数据
		void GetFFTDate(int **Data, int **DataTop, int *Size);
		int GetFFTMax() {return 120;}
		int GetFFTMin() {return 0;}

		// 控制歌曲
		void SetTimeBySecond(unsigned int second);
		void SetVolume(unsigned int Volume);
		void Play(){player->Play();}
        void Pause(){player->Pause();}
        void Stop() {player->Stop();}

    private:
        // ZPlay
        ZPlay *player;

        // 播放状态
        TStreamStatus status;
        TStreamTime position;

        // 文件 ID3 信息
		TID3InfoEx id3_gbk;
		TID3InfoEx id3_utf8;

        // 歌曲信息
        TStreamInfo info;

		// FFT 数据
		int FFTData[FFT_POINT_NUNBER];
		int FFTDataLeft[FFT_POINT_NUNBER];
		int FFTDataRight[FFT_POINT_NUNBER];
		
		// 辅助 FFT 数据
		int FFTTopData[FFT_POINT_NUNBER];
		unsigned long last_get_fft_time, last_get_fft_top_time;
		static const int fft_down_speed = 5;
    };
}
#endif // ORZZPLAY_H_INCLUDED_H_INCLUDED



