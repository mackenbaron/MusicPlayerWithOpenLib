#ifndef ORZZPLAY_H_INCLUDED
#define ORZZPLAY_H_INCLUDED

#include <libzplay.h>
#include "orz_base_math.h"

// ������ 2 �� n �η�!!!
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

        // ��ʼ�� libZPlay
        bool Init();

	public:
		// ���캯��
		BaseZPlay();

		// ��������
        ~BaseZPlay();

        // ��ȡ��Ƶ�ļ�
        bool Load(const char *NamePath);
		bool LoadFileID3(const char *NamePath, TID3Info *Id3Information);

        // ��ȡ��Ƶ�ļ���ʱ��
        void GetTotalTime(unsigned int &hour, unsigned int &minute, unsigned int &second, unsigned int &millisecond);
		void GetTotalTime(MusicTimeTable &table);

        // ��ȡ��ǰ��������״̬
        PlayState GetStatue();

        // ��ȡ��ǰ��������״̬
        void GetCurrTime(unsigned int &hour, unsigned int &minute, unsigned int &second);
		void GetCurrTime(unsigned int &hour, unsigned int &minute, unsigned int &second, unsigned int &millisecond);
		void GetCurrTime(MusicTimeTable &table);
		void GetVolume(unsigned int &Volume);

		// ��ȡ��ǰ�ļ� ID3 ��Ϣ
		const TID3InfoEx& GetCurrMusicID3GBK();
		const TID3InfoEx& GetCurrMusicID3UTF8();

		// ��ȡ FFT ����
		void GetFFTDate(int **Data, int **DataTop, int *Size);
		int GetFFTMax() {return 120;}
		int GetFFTMin() {return 0;}

		// ���Ƹ���
		void SetTimeBySecond(unsigned int second);
		void SetVolume(unsigned int Volume);
		void Play(){player->Play();}
        void Pause(){player->Pause();}
        void Stop() {player->Stop();}

    private:
        // ZPlay
        ZPlay *player;

        // ����״̬
        TStreamStatus status;
        TStreamTime position;

        // �ļ� ID3 ��Ϣ
		TID3InfoEx id3_gbk;
		TID3InfoEx id3_utf8;

        // ������Ϣ
        TStreamInfo info;

		// FFT ����
		int FFTData[FFT_POINT_NUNBER];
		int FFTDataLeft[FFT_POINT_NUNBER];
		int FFTDataRight[FFT_POINT_NUNBER];
		
		// ���� FFT ����
		int FFTTopData[FFT_POINT_NUNBER];
		unsigned long last_get_fft_time, last_get_fft_top_time;
		static const int fft_down_speed = 5;
    };
}
#endif // ORZZPLAY_H_INCLUDED_H_INCLUDED



