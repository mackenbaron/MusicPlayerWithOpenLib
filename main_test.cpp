//
//#include "orz_base_public_resource.h"
//#include <SDL.h>
//#include <iostream>
//
////using namespace Orz;
//using namespace std;

//bool CreateScene_test()
//{
//	// ϵͳ���� --------------------------------------------------------
//
//	GetDefaultOpenFileWay();
//	SetDefaultOpenFileWayToThisProgram();
//
//// case 1
//// ���� DLL �ļ�
//platform.SetPathOfDLLGBK(this_program_path);
//platform.SetCurrentPathOfThisProgramGBK(this_program_path);

//// case 2
//this_program_path.pop_back(); // ��ȥ Debug
//this_program_path.pop_back();
//this_program_path.pop_back();
//this_program_path.pop_back();
//this_program_path.pop_back();
//this_program_path.append("Orz_VS_Project_alpha_02");// ���� Orz_VS_Project_alpha_02
//// ���� DLL �ļ�
//platform.SetPathOfDLLGBK(this_program_path);
//platform.SetCurrentPathOfThisProgramGBK(this_program_path);

//
//// ��ȡ����,����λ��
//Rect small_text, elapsed_text, remained_text;
//manager.GetWriter("small_text").GetTextPosition(small_text.x, small_text.y);
//manager.GetWriter("elapsed_text").GetTextPosition(elapsed_text.x, elapsed_text.y);
//manager.GetWriter("remained_text").GetTextPosition(remained_text.x, remained_text.y);

//	std::string this_program_path;
//	platform.GetPathOfThisProgramGBK(this_program_path);
//
//	return true;
//}
//
//void UpdateScene_test()
//{
//	manager.QuitScene();
//}

//int SDL_main(int argc, char *argv[])
//{
//manager.Go(CreateScene_test, UpdateScene_test);
//	cout<<" 99999 \n";
//	system("pause");
//	SDL_Quit();
//	return 0;
//}