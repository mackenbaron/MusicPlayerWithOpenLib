

#include "main_play_list.h"
#include "orz_base_text_convert.h"
#include "orz_log.h"
#include <iostream>

#define MAX_CHAR_PATH 1024
namespace Program
{
	bool PlayList::LoadPlayList(const char *Path)
	{
		bool succeed(true);
		FILE *fp;

		fp = fopen(Path, "r");

		if (fp)
		{
			SongInformation temp_song_information;
			char buff[MAX_CHAR_PATH];
			int name_start_position = 0;
			while(fgets(buff, MAX_CHAR_PATH-1, fp))
			{
				if (isalpha(buff[0]))
				{
					// *��Ҫ,�������з�!!!!
					int index(0);
					while(index<MAX_CHAR_PATH-1)
					{
						if (buff[index] == 0)
						{
							if (index>1&&buff[index-1]=='\n')
							{
								buff[index-1] = 0;
							}
							break;
						}
						index++;
					}

					// ����·��
					temp_song_information.path_gbk = buff;
					
					// �õ�����
					int i = 0;
					for (i = 0; buff[i]; i++)
					{
						if (buff[i] == '\\')
						{
							name_start_position = i + 1;
						}
					}

					temp_song_information.name_gbk.clear();
					temp_song_information.name_gbk.append(buff + name_start_position);

					// ɾȥ .xxx Ŀǰ�ٶ���4��
					//temp_song_information.name.pop_back();
					//temp_song_information.name.pop_back();
					//temp_song_information.name.pop_back();
					//temp_song_information.name.pop_back();
					//temp_song_information.name.pop_back();

					temp_song_information.name_utf8 = Orz::ConvertTextFromeGBKToUTF8(temp_song_information.name_gbk.c_str());
					temp_song_information.path_utf8 = Orz::ConvertTextFromeGBKToUTF8(temp_song_information.path_gbk.c_str());

					song_list.push_back(temp_song_information);
				}
			}
		}
		else
		{
			succeed = false;
			Orz::error_out("PlayList::LoadPlayList - �޷����ļ�\""+ std::string(Path) +"\"!");
		}

		fclose(fp);
		return succeed;
	}

	std::vector<SongInformation>& PlayList::GetSongList()
	{
		return song_list;
	}

}