
#include "main_play_list.h"
#include "orz_base_public_resource.h"
#include "orz_config.h"
#include <Windows.h>
#undef CreateWindow

#include <cmath>
#include <iostream>
using namespace std;
using namespace Orz;
using namespace Program;

// 屏幕宽高
//const int ScreenWidth = 1920;
//const int ScreenHeight = 1080;
////const int ScreenWidth = 800;
////const int ScreenHeight = 600;
const int ScreenWidth = 1280;
const int ScreenHeight = 720;

// 时间表
MusicTimeTable total_time_table;
MusicTimeTable elapsed_time_table;
MusicTimeTable remained_time_table;
char time_number_text[256];

// 播放列表
PlayList play_list;
int play_list_position = 0;

// FFT图形 0 到 120 dB
int *FFT_data = NULL;
int *FFT_top_data = NULL;
int number_of_FFT_data = 129;

bool CreateScene()
{
	// 系统函数 --------------------------------------------------------
	std::string this_program_path;
	platform.GetPathOfThisProgramGBK(this_program_path);
	//platform.SetCurrentPathOfThisProgramGBK(this_program_path);

	// 画面-------------------------------------------------------------
	platform.CreateWindow("xxx", ScreenWidth, ScreenHeight);

	// 画面-------------------------------------------------------------
	// 读取屏幕数据
	int sw, sh;
	platform.GetWindowSize(sw, sh);

	//  背景
	Animate *new_animate = NULL;
	Rect background_img_rect = {0, 0, sw, sh};
	new_animate = new Animate;
	new_animate->LoadAnimate("ref", "resource\\background.orzanimate", background_img_rect);
	manager.GerRoot().ChildrenPushBack(new_animate);
	((Animate&)manager.SearchRoot("ref")).ChangeRenderStyle(ELEMENT_RENDER_STYLE_FILL);//.ChangeBlendModeToAlpha().ChangeAlpha(100);

	// 音乐条
	Rect s_rect = {0, 0, sw, sh};
	Rect music_line_rect_prime = {0, 0, 0 ,0};
	ControlVirtual* line_box = new ControlVirtual;
	line_box->CreateControlVirtual("music_line_box", s_rect);
	for (int i = 1; i < 180*2+1; i++)
	{
		new_animate = new Animate;
		new_animate->LoadAnimate("music_line", "resource\\line.orzanimate", music_line_rect_prime);
		line_box->ChildrenPushBack(new_animate);
	}
	manager.GerRoot().ChildrenPushBack(line_box);

	// 控件--------------------------------------------
	// 按钮 x
	Rect x_button_sprite_rect = {0, 0, 30, 30};
	Sprite* new_sprite = new Sprite;
	new_sprite->LoadSprite("x_button_sprite", "resource\\x_button\\first_sprite.orzsprite", x_button_sprite_rect);

	Rect x_button = {sw - 30, 0, 30, 30};
	ControlVirtual* new_control_virtual = new ControlVirtual;
	new_control_virtual->CreateControlVirtual("x_button", x_button);
	new_control_virtual->ChildrenPushBack(new_sprite);
	manager.GerRoot().ChildrenPushBack(new_control_virtual);

	// music scroll bar
	Sprite *new_bar_sprite;
	Rect bar_sprite_rect = {0, 0, 80, 80},
		trough_sprite_rect = {0, 20, 600, 80};
	new_bar_sprite = new Sprite;
	new_bar_sprite->LoadSprite("bar_sprite","resource\\first_bar\\sprite_bar.orzsprite", bar_sprite_rect);

	Sprite *new_trough_sprite;
	new_trough_sprite = new Sprite;
	new_trough_sprite->LoadSprite("trough_sprite","resource\\first_bar\\sprite_trough.orzsprite", trough_sprite_rect);

	Rect music_bar_bar_rect = {0, 0, bar_sprite_rect.w, bar_sprite_rect.h},
	music_bar_trough_rect = {(sw-trough_sprite_rect.w)/2, (sh - trough_sprite_rect.h)/2,
	trough_sprite_rect.w, trough_sprite_rect.h};
	ControlScrollBar *new_scroll_bar = NULL;
	new_scroll_bar = new ControlScrollBar;
	new_scroll_bar->CreateControlScrollBar("music_scroll_bar", CONTROL_DIRECT_LEFT_RIGHT, music_bar_bar_rect, music_bar_trough_rect);
	new_scroll_bar->ChildrenPushBack(new_trough_sprite);
	new_scroll_bar->GetBar().ChildrenPushBack(new_bar_sprite);
	manager.GerRoot().ChildrenPushBack(new_scroll_bar);

	// list----------------------------------------------------------------
	//Rect list_bar_rect = { , , 30, 530};
	Rect list_rect = {0, 100, sw*(300.0/1280.), sh*(500./720.)};
	Color list_background_color = {200, 200, 200, 255};
	ControlList* new_control_list = new ControlList;
	new_control_list->CreateControlList("list", list_rect, list_background_color, 30, "resource\\font.ttf", 20);
	manager.GerRoot().ChildrenPushBack(new_control_list);

	ControlScrollBarWithColor* new_control_scroll_bar_with_color = new ControlScrollBarWithColor;
	Rect list_bar_rect = { list_rect.x + list_rect.w, list_rect.y, 30, list_rect.h};
	Color bar_trough_color ={200, 200, 200, 255};
	Color bar_bar_color ={150, 150, 150, 255};
	new_control_scroll_bar_with_color->CreateControlScrollBarWithColor("list_bar",CONTROL_DIRECT_UP_DOWN, list_bar_rect, bar_trough_color, bar_bar_color);
	((ControlScrollBarWithColor*)new_control_scroll_bar_with_color)->GetBar().ChangeSize(30, 40);
	manager.GerRoot().ChildrenPushBack(new_control_scroll_bar_with_color);

	// 文本---------------------------------------------------------------
	Writer* new_wirter = NULL;

	const int time_table_text_y = sh*(440.f/720.f);
	sprintf(time_number_text,"00:00");
	Rect elapsed_rect = {sw*(545.f/1280.f), time_table_text_y, 750, 120};
	Color elapsed_color = {255, 255, 255, 0xFF};
	new_wirter = new Writer;
	new_wirter->CreateWriter("elapsed_text",  "resource\\font.ttf", time_number_text, 33,  elapsed_color,  elapsed_rect);
	manager.GerRoot().ChildrenPushBack(new_wirter);

	sprintf(time_number_text,"%02d:%02d",total_time_table.minute, total_time_table.second);
	Rect remained_rect = {sw*(655.f/1280.f), time_table_text_y, 750, 120};
	Color remained_color = {255, 255, 255, 0xFF};
	new_wirter = new Writer;
	new_wirter->CreateWriter("remained_text",  "resource\\font.ttf", time_number_text, 33,  remained_color,  remained_rect);
	manager.GerRoot().ChildrenPushBack(new_wirter);

	const char small_text[] = "ELAPSED                                                      REMAINED";
	Rect  small_text_rect = {sw*(471.f/1280.f), sh*(455.f/720.f), 750, 420};
	Color  small_text_color = {255, 255, 255, 0xFF};
	new_wirter = new Writer;
	new_wirter->CreateWriter("small_text",  "resource\\font.ttf", small_text, 14,  small_text_color,  small_text_rect);
	manager.GerRoot().ChildrenPushBack(new_wirter);

	const char artist_text[] = "Artist";
	Rect artist_text_rect = {0, 0, sw, sh};
	Color artist_text_color = {255, 255, 255, 0xFF};
	new_wirter = new Writer;
	new_wirter->CreateWriter("artist_text",  "resource\\font_black.ttf", artist_text, 45,  artist_text_color,  artist_text_rect);
	manager.GerRoot().ChildrenPushBack(new_wirter);

	const char title_text[] = "warten sie";
	Rect title_text_rect = {0, 0, sw, sh};
	Color title_text_color = {255, 255, 255, 0xFF};
	new_wirter = new Writer;
	new_wirter->CreateWriter("title_text",  "resource\\font.ttf", title_text, 35,  title_text_color,  title_text_rect);
	manager.GerRoot().ChildrenPushBack(new_wirter);

	//// 版本号
	//const char version_text[] = "test test 版本号v 0.0.5";
	//Rect  version_text_rect = {0, 0, 550, 420};
	//Color  version_text_color = {255, 55, 115, 0xFF};
	//new_wirter = new Writer;
	//new_wirter->CreateWriter("version_text", "resource\\font.ttf", ConvertTextFromeGBKToUTF8(version_text), 24,  version_text_color,  version_text_rect);
	//manager.GerRoot().ChildrenPushBack(new_wirter);


	// 定义距离
	BaseElement* pp = &manager.GerRoot();

	manager.SearchRoot("ref").ChangeDistance(10.0); // 背景
	manager.SearchRoot("music_line_box").ChangeDistance(11.0); // music_line_box
	manager.SearchRoot("music_scroll_bar").ChangeDistance(30.0);

	manager.SearchRoot("elapsed_text").ChangeDistance(31.0);
	manager.SearchRoot("remained_text").ChangeDistance(32.0);
	manager.SearchRoot("small_text").ChangeDistance(33.0);
	manager.SearchRoot("artist_text").ChangeDistance(34.0);
	manager.SearchRoot("title_text").ChangeDistance(35.0);

	manager.SearchRoot("list").ChangeDistance(50.0);
	manager.SearchRoot("list_bar").ChangeDistance(51.0);

	manager.SearchRoot("x_button").ChangeDistance(100.0); // x button
	
	//manager.GerRoot().ChangeSize(1900.0/sw);

	// 读取播放列表-------------------------------------------------------
	play_list.LoadPlayListM3u("resource\\playlist.m3u");

	for (int i = 0; i < play_list.GetSongList().size(); ++i)
	{
		((ControlList&)manager.SearchRoot("list"))
			.PushBack
			(
			play_list.GetSongList()[i].path_utf8.c_str(),
			play_list.GetSongList()[i].name_utf8.c_str()
			);
	}

	// 歌曲------------------------------
	if (!play_list.GetSongList().empty())
	{
		play_list_position = play_list.GetSongList().size()-1;
		device.sound.Load(play_list.GetSongList()[play_list_position].path_gbk.c_str());
		device.sound.Play();
		device.sound.GetTotalTime(total_time_table);
		((Writer&)manager.SearchRoot("title_text")).ChangeTextUTF8(ConvertTextFromeGBKToUTF8(device.sound.GetCurrMusicID3GBK().Title));
		((Writer&)manager.SearchRoot("artist_text")).ChangeTextUTF8(ConvertTextFromeGBKToUTF8(device.sound.GetCurrMusicID3GBK().Artist));
		
	}

	return true;
}

void UpdateScene_t()
{
	SDL_Delay(10);

	//// 打开文件-------------------------------------------------------------------
	if (platform.IsHaveFileRequireOpen())
	{
		std::string path;
		platform.GetPathOfFileThatRequireOpen(path);
	
#ifdef CodeDebug
		std::cout<<path.c_str()<<std::endl;
#endif
		if (device.sound.Load(path.c_str()))
		{
			device.sound.Play();
			play_list.PushBackEntryGBK(path.c_str());
			((ControlList&)manager.SearchRoot("list")).PushBack(play_list.GetSongList().back().path_utf8.c_str(), play_list.GetSongList().back().name_utf8.c_str());
			((Writer&)manager.SearchRoot("artist_text")).ChangeTextUTF8(device.sound.GetCurrMusicID3UTF8().Artist);
			((Writer&)manager.SearchRoot("title_text")).ChangeTextUTF8(device.sound.GetCurrMusicID3UTF8().Title);
			play_list_position = play_list.GetSongList().size()-1;
		}
	}
	// 窗口事件-----------------------------------------------------------------------------
	int mx, my, sw, sh;
	platform.GetMousePosition(mx, my);
	platform.GetWindowSize(sw, sh);

	// 背景-----------------------------------------------------------------------------------
	Rect screen_rect = {0,0,sw, sh};
	Color screen_color = {2, 3, 3, 235};
	device.display.DrawFillRect(screen_color, screen_rect);

	// List and bar -----------------------------------------------------------------------------

	// 根据 list 内容大小 调整 scroll's bar 的大小
	int trought_width, trough_height,
		bar_width, bar_height,
		list_content_size;
	((ControlScrollBarWithColor&)manager.SearchRoot("list_bar")).GetSize(trought_width, trough_height);
	((ControlScrollBarWithColor&)manager.SearchRoot("list_bar")).GetBar().GetSize(bar_width, bar_height);
	((ControlList&)manager.SearchRoot("list")).GetContentSize(list_content_size);
	if (list_content_size > trough_height)
	{
		bar_height = trough_height*(float)trough_height/list_content_size;
	}
	else
	{
		bar_height = trough_height;
	}

	((ControlScrollBarWithColor&)manager.SearchRoot("list_bar")).GetBar().ChangeSize(bar_width,bar_height);

	// list
	if (manager.SearchRoot("list").IsShow())
	{
		// 检测是否隐藏
		if (mx!=0&&
			((ControlScrollBar&)manager.SearchRoot("list_bar")).GetControlState() == CONTROL_STATE_MOUSE_OUT
			&&
			((ControlList&)manager.SearchRoot("list")).GetControlState() == CONTROL_STATE_MOUSE_OUT
			)
		{
			// 都隐藏
			manager.SearchRoot("list").Hide();
			manager.SearchRoot("list_bar").Hide();
		}
		else
		{
			// 鼠标滑轮控制滚动
			if (int t = device.input.GetMouseWheel())
			{
				float control_percent = 0.0;
				((ControlScrollBarWithColor&)(manager.SearchRoot("list_bar"))).GetPercent(control_percent);
				float new_percent = control_percent-0.25*device.input.GetMouseWheel();
				((ControlScrollBarWithColor&)(manager.SearchRoot("list_bar"))).ChangePercent(new_percent);
			}

			// 播放音乐
			if (&manager.SearchRoot("list").SearchChildThatHaveContact() != &error_element)
			{
				BaseElement* temp = &manager.SearchRoot("list").SearchChildThatHaveContact();
				if (((ControlList&)manager.SearchRoot("list").SearchChildThatHaveContact()).GetControlMessage() == CONTROL_MESSAGE_MOUSE_DOUBLE_CLICK)
				{
					//bug
					//manager.SearchRoot("list").SearchChildThatHaveContact().ChangeAlpha(200);

					vector<SongInformation>& p_play_list = play_list.GetSongList();

					for (unsigned long i = 0; i < p_play_list.size(); ++i)
					{
						string name = manager.SearchRoot("list").SearchChildThatHaveContact().GetName();
						if (p_play_list[i].path_utf8 == name)
						{
							play_list_position = i;
							device.sound.Load(p_play_list[i].path_gbk.c_str());
							((Writer&)manager.SearchRoot("title_text")).ChangeTextUTF8(ConvertTextFromeGBKToUTF8(device.sound.GetCurrMusicID3GBK().Title));
							((Writer&)manager.SearchRoot("artist_text")).ChangeTextUTF8(ConvertTextFromeGBKToUTF8(device.sound.GetCurrMusicID3GBK().Artist));
							device.sound.Play();
						}
					}
				}
			}
		
			// list bar
			float list_percent =0.;
			((ControlScrollBarWithColor&)manager.SearchRoot("list_bar")).GetPercent(list_percent);
			((ControlList&)manager.SearchRoot("list")).ChangePercent(list_percent);

			if (((ControlScrollBarWithColor&)manager.GerRoot().SearchChildren("list_bar")).GetBar().GetControlState() == CONTROL_STATE_MOUSE_DOWN
				||((ControlScrollBarWithColor&)manager.GerRoot().SearchChildren("list_bar")).GetControlState() == CONTROL_STATE_MOUSE_DOWN 
				)
			{
				((ControlScrollBarWithColor&)manager.GerRoot().SearchChildren("list_bar")).ChangePercentAccrodToMousePosition();
			}

		}// end test hide
	}
	else
	{
		// 检测是否显示
		if (mx==0)
		{
			manager.SearchRoot("list").Show();
			manager.SearchRoot("list_bar").Show();
		}
	}


	// 按钮x---------------------------------------------------------------------------------
	if (((BaseControl&)manager.GerRoot().SearchChildren("x_button")).GetControlMessage() == CONTROL_MESSAGE_MOUSE_CLICK)
	{
		manager.QuitScene();
	}

	// 音乐滚动条 and 时间文本-----------------------------------------------------------------
	device.sound.GetCurrTime(elapsed_time_table);

	// 滑动条定位
	if (((ControlScrollBar&)manager.SearchRoot("music_scroll_bar")).GetControlMessage() == CONTROL_MESSAGE_MOUSE_CLICK)
	{
		// 音乐定位
		float music_percent;
		((ControlScrollBar&)manager.SearchRoot("music_scroll_bar")).ChangePercentAccrodToMousePosition().GetPercent(music_percent);
		device.sound.SetTimeBySecond(total_time_table.GetTotalTimeBySecond()*music_percent);
	}
	else
	{
		((ControlScrollBar&)manager.SearchRoot("music_scroll_bar")).ChangePercent((float)elapsed_time_table.GetTotalTimeBySecond()/total_time_table.GetTotalTimeBySecond());

	}
	
	// 文本---------------------------------------------------------------
	((Writer&)manager.SearchRoot("artist_text")).ChangeTextCenterPosition(0.5, 175.0/720.0);
	((Writer&)manager.SearchRoot("title_text")).ChangeTextCenterPosition(0.5, 250.0/720.0);

	sprintf(time_number_text, "%02d:%02d",elapsed_time_table.minute, elapsed_time_table.second);
	((Writer&)manager.SearchRoot("elapsed_text")).ChangeTextUTF8(time_number_text);

	remained_time_table.SetTimeBySecond(total_time_table.GetTotalTimeBySecond() - elapsed_time_table.GetTotalTimeBySecond());
	sprintf(time_number_text, "%02d:%02d",remained_time_table.minute, remained_time_table.second);
	((Writer&)manager.SearchRoot("remained_text")).ChangeTextUTF8(time_number_text);


	// 绘制 FFT------------------------------------------------------------------------
	Color color_red = {255,255,0,0};
	Color color_bule = {25,255,30,0};

	// 获取 FFT
	device.sound.GetFFTDate(&FFT_data, &FFT_top_data,&number_of_FFT_data);

#ifdef CodeDebug
	for (int i = 0; i < number_of_FFT_data - 1; i++)
	{
		device.display.DrawLine(color_red, i*2 + 50, 300, i*2 + 50, 300 - FFT_data[i]);
		device.display.DrawPoint(color_bule, i*2 + 50, 500 - FFT_top_data[i]);
	}

	// FFT
	const int ttt_ppp = number_of_FFT_data / 5;
	for (int i = 0; i < number_of_FFT_data - 1; i++)
	{
		int real_m = i - i % ttt_ppp;
		int real_n = real_m + ttt_ppp;

		float percent = (float)(i % ttt_ppp)/ttt_ppp;
		int distance = (FFT_data[real_n] - FFT_data[real_m]) * percent;

		int real_high = FFT_data[real_m] + distance;

		device.display.DrawLine(color_red, i*2 + 50, 500, i*2 + 50, 500 - real_high);
		device.display.DrawPoint(color_bule, i*2 + 50, 500 - FFT_top_data[real_m]);
	}
#endif

	// 画圆
	const float px = sw / 2, py = (sh / 2)*1.0251 ; // 圆心
	const float radius = sh * (287.5/720.); // 半径
	float draw_line_high = 0.0f;
	Point draw_center = {0.5f, 0.5f};
	
	ControlVirtual* box = &(ControlVirtual&)manager.SearchRoot("music_line_box");
	if (box)
	{
		// 左半边
		float degree=0.0;
		for (int i=0; i < 180; i++)
		{
			int height = FFT_data[(int)(degree/180.0*number_of_FFT_data)]*1.;
			((Animate&)box->Children(i))
				.ChangeAngle(degree)
				.ChangeCenter(draw_center)
				.ChangeToEnableAdvanceAttribute()
				.ChangePosition(px + radius*cos((degree + 90.)/180.0*3.14159), 
				py + radius*sin((degree + 90.)/180.0*3.14159))
				.ChangeSize(6, height).ChangeRenderStyle(ELEMENT_RENDER_STYLE_FULL);
			degree+=1.0;
		}

		// 右半边
		degree=0.0;
		for (int i=180; i < 360; i++)
		{
			int height = FFT_data[(int)(degree/180.0*number_of_FFT_data)]*1.;
			((Animate&)box->Children(i))
				.ChangeAngle(-degree)
				.ChangeCenter(draw_center)
				.ChangeToEnableAdvanceAttribute()
				.ChangePosition(
				px + radius*sin((degree)/180.0*3.14159), 
				py + radius*cos((degree)/180.0*3.14159)
				)
				.ChangeSize(6, height).ChangeRenderStyle(ELEMENT_RENDER_STYLE_FULL);
			degree+=1.0;
		}
	}
	
	// 播放器状态
	if (device.sound.GetStatue() == STOP)
	{
		// 播放下一曲
		vector<SongInformation>& p_play_list = play_list.GetSongList();

		if (!p_play_list.empty())
		{
			if (play_list_position < p_play_list.size() - 1)
			{
				play_list_position++;
			}
			else
			{
				play_list_position=0;
			}

			device.sound.Load(p_play_list[play_list_position].path_gbk.c_str());
			((Writer&)manager.SearchRoot("title_text")).ChangeTextUTF8(ConvertTextFromeGBKToUTF8(device.sound.GetCurrMusicID3GBK().Title));
			((Writer&)manager.SearchRoot("artist_text")).ChangeTextUTF8(ConvertTextFromeGBKToUTF8(device.sound.GetCurrMusicID3GBK().Artist));
			device.sound.Play();
		}

	}

	// 版本号
//	((Writer&)manager.SearchRoot("version_text")).ChangeSize(mx, my);

	if (device.input.GetButtonMessage(KEY_SPACE) == CONTROL_MESSAGE_MOUSE_CLICK)
	{
		if (device.sound.GetStatue() == PLAY)
		{
			device.sound.Pause();
		}
		else if (device.sound.GetStatue() == PAUSE || device.sound.GetStatue() == STOP)
		{
			device.sound.Play();
		}
	}
	
}

int SDL_main(int arg, char*[])
{
	manager.Go(CreateScene, UpdateScene_t);

	play_list.SaveSongListM3u("resource\\playlist.m3u");

	return 1;
}
