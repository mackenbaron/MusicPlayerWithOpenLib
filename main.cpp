
#include "main_play_list.h"
#include "orz_base_public_resource.h"

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

	std::string this_program_path;
	platform.GetPathOfThisProgramGBK(this_program_path);

	// 画面-------------------------------------------------------------
	platform.CreateWindow("xxx", ScreenWidth, ScreenHeight);

	Animate *new_animate = NULL;
	Rect rect_1 = {0,0,400, 400};
	new_animate = manager.CreateAnimate("back", "resource\\background.orzanimate", rect_1);
	manager.GerRoot().ChildrenPushBack(new_animate);

	Rect rect_2 = {0, 400, 400 ,400};
	new_animate = manager.CreateAnimate("line", "resource\\line.orzanimate", rect_2);
	new_animate->ChangePosition(0,0).ChangeSize(300, 300);
	manager.GerRoot().ChildrenPushBack(new_animate);

	// 比较
	Rect rect_3 = {400, 0,800, 800};
	new_animate = manager.CreateAnimate("bxb", "resource\\sample.orzanimate", rect_3);
	manager.GerRoot().ChildrenPushBack(new_animate);
	manager.GetAnimate("bxb").ChangeBlendModeToAlpha();

	// 读取屏幕数据
	int sw, sh;
	platform.GetWindowSize(sw, sh);

	// 歌曲------------------------------
	device.sound.Load("resource\\Back To Your Heart feat.mp3");// Beyond-光辉岁月.mp3"); //四个女生-心愿.mp3");// 
	device.sound.Play();
	device.sound.GetTotalTime(total_time_table);

	// 控件--------------------------------------------

	// 按钮 x
	BaseControl* new_control = NULL;
	//Rect rect_button = {ScreenWidth - sw*(30.0/1280.), 0, 30, 30};
	Rect rect_button = {10, 10, 30, 30};
	Color button_color ={200, 200, 200, 255};
	new_control = manager.CreateControlButton("first_button", "first_button_name", rect_button, button_color);
	manager.GerRoot().Children(2).ChildrenPushBack(new_control);

	// bar
	Rect list_bar_rect = { 300, 200, 30, 530};
	Color bar_trough_color ={200, 200, 200, 255};
	Color bar_bar_color ={150, 150, 150, 255};
	new_control = manager.CreateControlScrollBar("list_bar", "list_bar_name", CONTROL_DIRECT_UP_DOWN, list_bar_rect, bar_trough_color, bar_bar_color);
	((ControlScrollBar*)new_control)->GetBar().ChangeSize(20, 20);
	manager.GerRoot().ChildrenPushBack(new_control);

	//Rect list_bar_rect = { sw*(300.0/1280.), sh*(400./720.), 30, 530};
	//manager.CreateControlList("first_list", "resource\\first_list.orzcontrol", sw*(0.0/1280.), sh*(100./720.));

	//manager.GetControlList("first_list").GetControlBar().ChangeAlpha(254);

	//// 获取数据,调整位置
	//int first_bar_w, first_bar_h;
	//manager.GetControlBar("first_bar").GetSize(first_bar_w, first_bar_h);
	//manager.GetControlBar("first_bar").ChangePosition((sw - first_bar_w)/2, (sh*1.02-first_bar_h) /2);


	//SDL_Delay(5000);

	//// 读取播放列表-------------------------------------------------------
	//play_list.LoadPlayListM3u("resource\\playlist.m3u");

	//for (int i = 0; i < play_list.GetSongList().size(); ++i)
	//{
	//	manager
	//		.GetControlList("first_list")
	//		.PushBack
	//		(
	//		play_list.GetSongList()[i].path_utf8.c_str(),
	//		play_list.GetSongList()[i].name_utf8.c_str()
	//		);
	//}

	// 文本---------------------------------------------------------------
	BaseElement* new_wirter = NULL;

	const int time_table_text_y = sh*(440.f/720.f);
	sprintf(time_number_text,"00:00");
	Rect elapsed_rect = {sw*(545.f/1280.f), time_table_text_y, 750, 120};
	Color elapsed_color = {255, 255, 255, 0xFF};
	new_wirter = manager.CreateWriter("elapsed_text",  "resource\\font.ttf", time_number_text, 33,  elapsed_color,  elapsed_rect);
	manager.GerRoot().ChildrenPushBack(new_wirter);


	sprintf(time_number_text,"%02d:%02d",total_time_table.minute, total_time_table.second);
	Rect remained_rect = {sw*(655.f/1280.f), time_table_text_y, 750, 120};
	Color remained_color = {255, 255, 255, 0xFF};
	new_wirter = manager.CreateWriter("remained_text",  "resource\\font.ttf", time_number_text, 33,  remained_color,  remained_rect);
	manager.GerRoot().ChildrenPushBack(new_wirter);


	const char small_text[] = "ELAPSED                                                      REMAINED";
	Rect  small_text_rect = {sw*(471.f/1280.f), sh*(455.f/720.f), 750, 420};
	Color  small_text_color = {255, 255, 255, 0xFF};
	new_wirter = manager.CreateWriter("small_text",  "resource\\font.ttf", small_text, 14,  small_text_color,  small_text_rect);
	manager.GerRoot().ChildrenPushBack(new_wirter);

	const char artist_text[] = "Artist";
	Rect artist_text_rect = {sw*0.5, sh*175.0/720.0, sw, sh};
	Color artist_text_color = {255, 255, 255, 0xFF};
	new_wirter = manager.CreateWriter("artist_text",  "resource\\font_black.ttf", artist_text, 45,  artist_text_color,  artist_text_rect);
	manager.GerRoot().ChildrenPushBack(new_wirter);

	const char title_text[] = "warten sie";
	Rect title_text_rect = {sw*0.5, sh*250.0/720.0, sw, sh};
	Color title_text_color = {255, 255, 255, 0xFF};
	new_wirter = manager.CreateWriter("title_text",  "resource\\font.ttf", title_text, 35,  title_text_color,  title_text_rect);
	manager.GerRoot().ChildrenPushBack(new_wirter);

	// 版本号
	const char version_text[] = "ifsad版本号v 0.0.4";
	Rect  version_text_rect = {0, 0, 550, 420};
	Color  version_text_color = {255, 155, 5, 0xFF};

	new_wirter = manager.CreateWriter("version_text", "resource\\font.ttf", ConvertTextFromeGBKToUTF8(version_text), 24,  version_text_color,  version_text_rect);
	manager.GerRoot().ChildrenPushBack(new_wirter);

	BaseElement*test=&manager.GerRoot();

	return true;
}

void UpdateScene()
{

//	///////////// 打开文件
//	if (platform.IsHaveFileRequireOpen())
//	{
//		std::string path;
//		platform.GetPathOfFileThatRequireOpen(path);
//
//#ifdef CodeDebug
//		std::cout<<path.c_str()<<std::endl;
//#endif
//		play_list.PushBackEntryGBK(path.c_str());
//
//		manager.GetControlList("first_list").PushBack(play_list.GetSongList().back().path_utf8.c_str(), play_list.GetSongList().back().name_utf8.c_str());
//
//		if (device.sound.Load(path.c_str()))
//		{
//			device.sound.Play();
//			manager.GetWriter("artist_text").ChangeTextUTF8(device.sound.GetCurrMusicID3UTF8().Artist);
//			manager.GetWriter("title_text").ChangeTextUTF8(device.sound.GetCurrMusicID3UTF8().Title);
//		}
//	}
//
//	////////////////////////////////////

	int mx, my, sw, sh;
	platform.GetMousePosition(mx, my);
	platform.GetWindowSize(sw, sh);

	// 获取时间
	device.sound.GetCurrTime(elapsed_time_table);

	// 背景-----------------------------------------------------------------------------------

	Rect screen_rect = {0,0,ScreenWidth, ScreenHeight};
	Color screen_color = {23, 23, 3,523};
	device.display.DrawFillRect(screen_color, screen_rect);
	//BaseElement* test = &manager.GerRoot().ChangePosition(0,0).ChangeSize(100, 720);


	//manager.GetAnimate("back").ChangeSize(sw, sh).ChangePosition(0,0);//.ChangeSize(sw, sh);
	//manager.GerRoot().ChangeSize(0.9999999f, .9999999f);
	manager.GerRoot().Children(0);
	manager.GerRoot().Children(1);
	manager.GerRoot().Children(2).ChangeAlpha(150);


	//manager.GetAnimate("back").Draw();//.Contact().Draw(screen_rect);
//	// 比较
//	//manager.GetAnimate("bxb").SetAlpha(my);
//	//manager.GetAnimate("bxb").Draw(screen_rect);
//
//	// 滚动条---------------------------------------------------------------------------------
	
	((ControlScrollBar&)manager.GerRoot().SearchChildren("list_bar_name")).ChangePercentAccrodToMousePosition();

	if (((BaseUi&)manager.GerRoot().SearchChildren("first_button_name")).GetUiState() == UI_STATE_MOUSE_DOWN )
	{
		manager.QuitScene();
	}

//	// 滑动条定位
//	manager.GetControlBar("first_bar").Contact(mx, my, device.input.GetButton(KEY_MOUSE_LEFT));
//	if (manager.GetControlBar("first_bar").GetMessage() == CONTROL_MESSAGE_MOUSE_CLICK||manager.GetControlBar("first_bar").GetMessage() == CONTROL_MESSAGE_MOUSE_CONST_DOWN_END)
//	{
//		manager.GetControlBar("first_bar").ChangePercent(mx, my);
//		device.sound.SetTimeBySecond(total_time_table.GetTotalTimeBySecond()*manager.GetControlBar("first_bar").GetPercent());
//	}
//	else
//	{
//		manager.GetControlBar("first_bar").ChangePercent((float)elapsed_time_table.GetTotalTimeBySecond()/total_time_table.GetTotalTimeBySecond());
//	}
//	manager.GetControlBar("first_bar").Draw();
//
//	// 绘制 FFT------------------------------------------------------------------------
	//Color color_red = {255,255,0,0};
	//Color color_bule = {25,255,30,0};

	//// 获取 FFT
	//device.sound.GetFFTDate(&FFT_data, &FFT_top_data,&number_of_FFT_data);


	////for (int i = 0; i < number_of_FFT_data - 1; i++)
	////{
	////	device.DrawLine(color_red, i*2 + 50, 300, i*2 + 50, 300 - FFT_data[i]);
	////	device.DrawPoint(color_bule, i*2 + 50, 500 - FFT_top_data[i]);
	////}

	//// FFT
	//manager.GetAnimate("line").Contact();
	//const int ttt_ppp = number_of_FFT_data / 5;
	//for (int i = 0; i < number_of_FFT_data - 1; i++)
	//{
	//	int real_m = i - i % ttt_ppp;
	//	int real_n = real_m + ttt_ppp;

	//	float percent = (float)(i % ttt_ppp)/ttt_ppp;
	//	int distance = (FFT_data[real_n] - FFT_data[real_m]) * percent;

	//	int real_high = FFT_data[real_m] + distance;

	//	device.display.DrawLine(color_red, i*2 + 50, 500, i*2 + 50, 500 - real_high);
	//	device.display.DrawPoint(color_bule, i*2 + 50, 500 - FFT_top_data[real_m]);
	//}

//	// 画圆
//	const float px = sw / 2, py = (sh / 2)*1.0251 ; // 圆心
//	const float radius = sh * (287.5/720.); // 半径
//	float draw_line_high = 0.0f;
//	Point draw_center = {0.5f, 0.5f};
//
//	// 左半边
//	for (float degree=0.0; degree < 180.0; degree+=1.5)
//	{
//		// 绘制
//		manager.GetAnimate("line").DrawEx
//			(
//			px + radius*cos((degree + 90.)/180.0*3.14159), py + radius*sin((degree + 90.)/180.0*3.14159),
//			1.0,
//			(FFT_data[(int)(degree/360.0*number_of_FFT_data)] / (float)device.sound.GetFFTMax() + 0.07)*1.,
//			degree,
//			draw_center
//			);
//	}
//
//	// 右半边
//	for (float degree=0.0; degree < 180.0; degree+=1.5)
//	{
//		// 绘制
//		manager.GetAnimate("line").DrawEx(
//			px + radius*sin((degree)/180.0*3.14159), py + radius*cos((degree)/180.0*3.14159),
//			1.0,
//			(FFT_data[(int)(degree/360.0*number_of_FFT_data)] / (float)device.sound.GetFFTMax() + 0.07)*1.,
//			-degree,
//			//0.,
//			draw_center
//			);
//	}
//
	//// 文本-------------------------------------------------------------------------------
	////manager.GerRoot;

	sprintf(time_number_text, "%02d:%02d",elapsed_time_table.minute, elapsed_time_table.second);
	manager.GetWriter("elapsed_text").ChangeTextUTF8(time_number_text);

	remained_time_table.SetTimeBySecond(total_time_table.GetTotalTimeBySecond() - elapsed_time_table.GetTotalTimeBySecond());
	sprintf(time_number_text, "%02d:%02d",remained_time_table.minute, remained_time_table.second);
	manager.GetWriter("remained_text").ChangeTextUTF8(time_number_text);

	manager.GetWriter("version_text").ChangeSize(mx, my);

//	// 按钮x---------------------------------------------------------------------------------
//
//	if (my == 0)
//	{
//		manager.GetControlButton("first_button").Show();
//		manager.GetControlButton("first_button").Contact(mx, my, device.input.GetButton(KEY_MOUSE_LEFT));
//	}
//
//	if ( manager.GetControlButton("first_button").GetMessage() == CONTROL_MESSAGE_MOUSE_OVER)
//	{
//		manager.GetControlButton("first_button").Contact();
//		
//		if (manager.GetControlButton("first_button").GetMessage() == CONTROL_MESSAGE_MOUSE_CLICK)
//		{
//			manager.QuitScene();
//		}
//	}
//	else
//	{
//		manager.GetControlButton("first_button").Hide();
//	}
//
//	manager.GetControlButton("first_button").Draw();
//	
//	// 列表控件------------------------------------------------------------------------------
//	manager.GetControlList("first_list").Show();
//	if (mx==0||manager.GetControlList("first_list").GetState() == CONTROL_STATE_MOUSE_OVER||manager.GetControlList("first_list").GetState() == CONTROL_STATE_MOUSE_DOWN)
//	{
//
//		manager.GetControlList("first_list").Contact();
//		if (device.input.GetMouseWheel())
//			manager.GetControlList("first_list").ChangePercent(manager.GetControlList("first_list").GetPercent()-0.1*device.input.GetMouseWheel());
//
//		if (&manager.GetControlList("first_list").SearchChildThatHaveContact() != &error_element)
//		{
//			if (manager.GetControlList("first_list").SearchChildThatHaveContact().GetMessage() == CONTROL_MESSAGE_MOUSE_DOUBLE_CLICK)
//			{
//				manager.GetControlList("first_list").SearchChildThatHaveContact().ChangeAlpha(120);
//
//				vector<SongInformation>& p_play_list = play_list.GetSongList();
//
//				for (unsigned long i = 0; i < p_play_list.size(); ++i)
//				{
//					if (p_play_list[i].path_utf8 == manager.GetControlList("first_list").SearchChildThatHaveContact().GetName())
//					{
//						device.sound.Load(p_play_list[i].path_gbk.c_str());
//						manager.GetWriter("title_text").ChangeTextUTF8(ConvertTextFromeGBKToUTF8(device.sound.GetCurrMusicID3GBK().Title));
//						manager.GetWriter("artist_text").ChangeTextUTF8(ConvertTextFromeGBKToUTF8(device.sound.GetCurrMusicID3GBK().Artist));
//						device.sound.Play();
//					}
//					
//				}
//
//			}
//		}
//	}
//	else
//	{
//		manager.GetControlList("first_list").Hide();
//	}
//
//	manager.GetControlList("first_list").ChangeRenderStyle(ELEMENT_RENDER_STYLE_FILL).Draw();
//
//	// 版本号 ----------------------------------------------------------
//	manager.GetWriter("version_text").Draw();
}

int SDL_main(int arg, char*[])
{
	manager.Go(CreateScene, UpdateScene);

	return 1;
}

//// 限制帧率
//unsigned long last_frame_time = 0;
//if( GetCurrentTime() - last_frame_time  > 170)
//{
//	last_frame_time = GetCurrentTime();
//}