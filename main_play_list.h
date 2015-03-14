#ifndef MAIN_PLAY_LIST_INCLUDED
#define MAIN_PLAY_LIST_INCLUDED

// 播放列表相关
#include <string>
#include <vector>

namespace Program
{
	struct SongInformation
	{
		std::string name_gbk;
		std::string path_gbk;
		std::string name_utf8;
		std::string path_utf8;
	};

	class PlayList
	{
	public:
		bool LoadPlayListM3u(const char *LoadPath);
		bool SaveSongListM3u(const char *SavePath);
		void PushBackEntryGBK(const char *Path);
		std::vector<SongInformation>& GetSongList();
	private:
		std::vector<SongInformation> song_list;
	};
}

#endif // MAIN_PLAY_LIST_INCLUDED