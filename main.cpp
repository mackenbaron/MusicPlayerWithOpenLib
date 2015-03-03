#include "orz_base_public_resource.h"
#include "orz_control.h"
#include "main_play_list.h"
#include "main_regedit_exe.h"
#include "orz_option.h"

#include <cmath>
#include <iostream>
using namespace std;
using namespace Orz;
using namespace Program;

// 屏幕宽高
const int ScreenWidth = 1280;
const int ScreenHeight = 720;

// 时间表
MusicTimeTable total_time_table;
MusicTimeTable elapsed_time_table;
MusicTimeTable remained_time_table;
char time_number_text[256];

// 播放列表
PlayList play_list;

// FFT图形 0 到 120 dB
int *FFT_data = NULL;
int *FFT_top_data = NULL;
int number_of_FFT_data;

bool CreateScene()
{
	// 系统函数 --------------------------------------------------------

	GetDefaultOpenFileWay();
	SetDefaultOpenFileWayToThisProgram();

	std::string this_program_path;
	platform.GetPathOfThisProgramGBK(this_program_path);

	//// case 1
	//// 加载 DLL 文件
	//platform.SetPathOfDLLGBK(this_program_path);
	//platform.SetCurrentPathOfThisProgramGBK(this_program_path);

	// case 2
	this_program_path.pop_back(); // 消去 Debug
	this_program_path.pop_back();
	this_program_path.pop_back();
	this_program_path.pop_back();
	this_program_path.pop_back();
	this_program_path.append("Orz_VS_Project_alpha_02");// 加上 Orz_VS_Project_alpha_02
	// 加载 DLL 文件
	platform.SetPathOfDLLGBK(this_program_path);
	platform.SetCurrentPathOfThisProgramGBK(this_program_path);

	// 画面-------------------------------------------------------------
	platform.CreateWindow("xxx", ScreenWidth, ScreenHeight);
	manager.CreateAnimate("back", "resource\\background.orzanimate");
	manager.CreateAnimate("line", "resource\\line.orzanimate");

	// 比较
	manager.CreateAnimate("bxb", "resource\\sample.orzanimate");
	manager.GetAnimate("bxb").SetBlendModeToAlpha();

	// 读取屏幕数据
	int sw, sh;
	platform.GetWindowSize(sw, sh);

	// 歌曲------------------------------
	device.sound.Load("resource\\Beyond-光辉岁月.mp3");// Back To Your Heart feat.mp3 Beyond-光辉岁月.mp3
	device.sound.Play();
	device.sound.GetTotalTime(total_time_table);

	// 控件--------------------------------------------
	manager.CreateControlButton("first_button", "resource\\first_button.orzcontrol", ScreenWidth - sw*(30.0/1280.), 0);
	manager.CreateControlBar("first_bar", "resource\\first_bar.orzcontrol", sw*(300.0/1280.), sh*(400./720.));
	manager.CreateControlList("first_list", "resource\\first_list.orzcontrol", sw*(0.0/1280.), sh*(100./720.));

	manager.GetControlList("first_list").GetControlBar().ChangeAlpha(254);

	// 获取数据,调整位置
	int first_bar_w, first_bar_h;
	manager.GetControlBar("first_bar").GetSize(first_bar_w, first_bar_h);
	manager.GetControlBar("first_bar").ChangePosition((sw - first_bar_w)/2, (sh*1.02-first_bar_h) /2);



	//SDL_Delay(5000);

	// 读取播放列表-------------------------------------------------------
	play_list.LoadPlayListM3u("resource\\playlist.m3u");

	for (int i = 0; i < play_list.GetSongList().size(); ++i)
	{
		manager
			.GetControlList("first_list")
			.PushBack
			(
			play_list.GetSongList()[i].path_utf8.c_str(),
			play_list.GetSongList()[i].name_utf8.c_str()
			);
	}

	// 文本---------------------------------------------------------------
	const int time_table_text_y = sh*(440.f/720.f);
	sprintf(time_number_text,"00:00");
	Rect elapsed_rect = {sw*(545.f/1280.f), time_table_text_y, 750, 120};
	Color elapsed_color = {255, 255, 255, 0xFF};
	manager.CreateWriter("elapsed_text",  "resource\\font.ttf", time_number_text, 33,  elapsed_color,  elapsed_rect);

	sprintf(time_number_text,"%02d:%02d",total_time_table.minute, total_time_table.second);
	Rect remained_rect = {sw*(655.f/1280.f), time_table_text_y, 750, 120};
	Color remained_color = {255, 255, 255, 0xFF};
	manager.CreateWriter("remained_text",  "resource\\font.ttf", time_number_text, 33,  remained_color,  remained_rect);
	
	const char small_text[] = "ELAPSED                                                      REMAINED";
	Rect  small_text_rect = {sw*(471.f/1280.f), sh*(455.f/720.f), 750, 420};
	Color  small_text_color = {255, 255, 255, 0xFF};
	manager.CreateWriter("small_text",  "resource\\font.ttf", small_text, 14,  small_text_color,  small_text_rect);
	
	//// 获取数据,调整位置
	//Rect small_text, elapsed_text, remained_text;
	//manager.GetWriter("small_text").GetTextPosition(small_text.x, small_text.y);
	//manager.GetWriter("elapsed_text").GetTextPosition(elapsed_text.x, elapsed_text.y);
	//manager.GetWriter("remained_text").GetTextPosition(remained_text.x, remained_text.y);

	const char artist_text[] = "Artist";
	Rect artist_text_rect = {0, 0, sw, sh};
	Color artist_text_color = {255, 255, 255, 0xFF};
	manager.CreateWriter("artist_text",  "resource\\font_black.ttf", artist_text, 45,  artist_text_color,  artist_text_rect);

	const char title_text[] = "warten sie";
	Rect title_text_rect = {0, 0, sw, sh};
	Color title_text_color = {255, 255, 255, 0xFF};
	manager.CreateWriter("title_text",  "resource\\font.ttf", title_text, 35,  title_text_color,  title_text_rect);

	// 版本号
	const char version_text[] = "版本号v 0.0.4";
	Rect  version_text_rect = {0, 0, 550, 420};
	Color  version_text_color = {255, 5, 5, 0xFF};
	manager.CreateWriter("version_text", "resource\\font.ttf", ConvertTextFromeGBKToUTF8(version_text), 24,  version_text_color,  version_text_rect);

	return true;
}

void UpdateScene()
{
	///////////// 打开文件
	if (platform.IsHaveFileRequireOpen())
	{
		std::string path;
		platform.GetPathOfFileThatRequireOpen(path);

#ifdef CodeDebug
		std::cout<<path.c_str()<<std::endl;
#endif
		play_list.PushBackEntryGBK(path.c_str());

		manager.GetControlList("first_list").PushBack(play_list.GetSongList().back().path_utf8.c_str(), play_list.GetSongList().back().name_utf8.c_str());


		if (device.sound.Load(path.c_str()))
		{
			device.sound.Play();
			manager.GetWriter("artist_text").ChangeText(device.sound.GetCurrMusicID3UTF8().Artist);
			manager.GetWriter("title_text").ChangeText(device.sound.GetCurrMusicID3UTF8().Title);
		}
	}

	////////////////////////////////////

	int mx, my, sw, sh;
	platform.GetMousePosition(mx, my);
	platform.GetWindowSize(sw, sh);

	// 获取时间
	device.sound.GetCurrTime(elapsed_time_table);

	// 背景-----------------------------------------------------------------------------------
	Rect screen_rect = {0,0,ScreenWidth, ScreenHeight};
	manager.GetAnimate("back").Contact().DrawFill(screen_rect);

	// 比较
	//manager.GetAnimate("bxb").SetAlpha(my);
	//manager.GetAnimate("bxb").Draw(screen_rect);

	// 滚动条---------------------------------------------------------------------------------

	// 滑动条定位
	manager.GetControlBar("first_bar").Contact(mx, my, device.GetButton(KEY_MOUSE_LEFT));
	if (manager.GetControlBar("first_bar").GetMessage() == MOUSE_CLICK||manager.GetControlBar("first_bar").GetMessage() == MOUSE_CONST_DOWN_END)
	{
		manager.GetControlBar("first_bar").ChangePercent(mx, my);
		device.sound.SetTimeBySecond(total_time_table.GetTotalTimeBySecond()*manager.GetControlBar("first_bar").GetPercent());
	}
	else
	{
		manager.GetControlBar("first_bar").ChangePercent((float)elapsed_time_table.GetTotalTimeBySecond()/total_time_table.GetTotalTimeBySecond());
	}
	manager.GetControlBar("first_bar").Draw();

	// 绘制 FFT------------------------------------------------------------------------
	Color color_red = {255,255,0,0};
	Color color_bule = {25,255,30,0};

	// 获取 FFT
	device.sound.GetFFTDate(&FFT_data, &FFT_top_data,&number_of_FFT_data);


	//for (int i = 0; i < number_of_FFT_data - 1; i++)
	//{
	//	device.DrawLine(color_red, i*2 + 50, 300, i*2 + 50, 300 - FFT_data[i]);
	//	device.DrawPoint(color_bule, i*2 + 50, 500 - FFT_top_data[i]);
	//}

	// FFT
	manager.GetAnimate("line").Contact();
	const int ttt_ppp = number_of_FFT_data / 5;
	for (int i = 0; i < number_of_FFT_data - 1; i++)
	{
		int real_m = i - i % ttt_ppp;
		int real_n = real_m + ttt_ppp;

		float percent = (float)(i % ttt_ppp)/ttt_ppp;
		int distance = (FFT_data[real_n] - FFT_data[real_m]) * percent;

		int real_high = FFT_data[real_m] + distance;

		device.DrawLine(color_red, i*2 + 50, 500, i*2 + 50, 500 - real_high);
		device.DrawPoint(color_bule, i*2 + 50, 500 - FFT_top_data[real_m]);
	}

	// 画圆
	const float px = sw / 2, py = (sh / 2)*1.0251 ; // 圆心
	const float radius = sh * (287.5/720.); // 半径
	float draw_line_high = 0.0f;
	Point draw_center = {0.5f, 0.5f};

	// 左半边
	for (float degree=0.0; degree < 180.0; degree+=1.5)
	{
		// 绘制
		manager.GetAnimate("line").DrawEx
			(
			px + radius*cos((degree + 90.)/180.0*3.14159), py + radius*sin((degree + 90.)/180.0*3.14159),
			1.0,
			(FFT_data[(int)(degree/360.0*number_of_FFT_data)] / (float)device.sound.GetFFTMax() + 0.07)*1.,
			degree,
			&draw_center
			);
	}

	// 右半边
	for (float degree=0.0; degree < 180.0; degree+=1.5)
	{
		// 绘制
		manager.GetAnimate("line").DrawEx(
			px + radius*sin((degree)/180.0*3.14159), py + radius*cos((degree)/180.0*3.14159),
			1.0,
			(FFT_data[(int)(degree/360.0*number_of_FFT_data)] / (float)device.sound.GetFFTMax() + 0.07)*1.,
			-degree,
			//0.,
			&draw_center
			);
	}

	// 文本-------------------------------------------------------------------------------
	manager.GetWriter("artist_text").Write(0.5,float(175.0/720.0));
	manager.GetWriter("title_text").Write(0.5,float(250.0/720.0));
	manager.GetWriter("small_text").Write();

	sprintf(time_number_text, "%02d:%02d",elapsed_time_table.minute, elapsed_time_table.second);
	manager.GetWriter("elapsed_text").ChangeText(time_number_text).Write();

	remained_time_table.SetTimeBySecond(total_time_table.GetTotalTimeBySecond() - elapsed_time_table.GetTotalTimeBySecond());
	sprintf(time_number_text, "%02d:%02d",remained_time_table.minute, remained_time_table.second);
	manager.GetWriter("remained_text").ChangeText(time_number_text).Write();


	// 按钮x---------------------------------------------------------------------------------
	manager.GetControlButton("first_button").Show();
	if (my == 0 || manager.GetControlButton("first_button").GetMessage() == MOUSE_OVER)
	{
		manager.GetControlButton("first_button").Contact(mx, my, device.GetButton(KEY_MOUSE_LEFT));
		
		if (manager.GetControlButton("first_button").GetMessage() == MOUSE_CLICK)
		{
			manager.QuitScene();
		}
	}
	else
	{
		manager.GetControlButton("first_button").Hide();
	}

	manager.GetControlButton("first_button").Draw();
	
	// 列表控件------------------------------------------------------------------------------
	manager.GetControlList("first_list").Show();
	if (mx==0||manager.GetControlList("first_list").GetState() == CONTROL_MOUSE_OVER||manager.GetControlList("first_list").GetState() == CONTROL_MOUSE_DOWN)
	{
		manager.GetControlList("first_list").Contact(mx, my, device.GetButton(KEY_MOUSE_LEFT));
		if (device.GetMouseWheel())
			manager.GetControlList("first_list").ChangePercent(manager.GetControlList("first_list").GetPercent()-0.1*device.GetMouseWheel());

		if (manager.GetControlList("first_list").IsAnyControlTextHaveMessage())
		{
			if (manager.GetControlList("first_list").GetControlTextThatHaveMessage()->GetMessage() == MOUSE_DOUBLE_CLICK)
			{
				manager.GetControlList("first_list").GetControlTextThatHaveMessage()->ChangeAlpha(120);

				vector<SongInformation>& p_play_list = play_list.GetSongList();

				for (unsigned long i = 0; i < p_play_list.size(); ++i)
				{
					if (p_play_list[i].path_utf8 == manager.GetControlList("first_list").GetControlTextThatHaveMessage()->GetName())
					{
						device.sound.Load(p_play_list[i].path_gbk.c_str());
						manager.GetWriter("title_text").ChangeText(ConvertTextFromeGBKToUTF8(device.sound.GetCurrMusicID3GBK().Title));
						manager.GetWriter("artist_text").ChangeText(ConvertTextFromeGBKToUTF8(device.sound.GetCurrMusicID3GBK().Artist));
						device.sound.Play();
					}
					
				}

			}
		}
	}
	else
	{
		manager.GetControlList("first_list").Hide();
	}

	manager.GetControlList("first_list").DrawFill();

	

	// 版本号 ----------------------------------------------------------
	manager.GetWriter("version_text").Write();
}

bool CreateScene_test()
{
	// 系统函数 --------------------------------------------------------

	GetDefaultOpenFileWay();
	SetDefaultOpenFileWayToThisProgram();


	std::string this_program_path;
	platform.GetPathOfThisProgramGBK(this_program_path);

	return true;
}

void UpdateScene_test()
{
	manager.QuitScene();
}

int SDL_main(int arg, char*[])
{
	//manager.Go(CreateScene_test, UpdateScene_test);
	manager.Go(CreateScene, UpdateScene);

	return 1;
}

//// 限制帧率
//unsigned long last_frame_time = 0;
//if( GetCurrentTime() - last_frame_time  > 170)
//{
//	last_frame_time = GetCurrentTime();
//}