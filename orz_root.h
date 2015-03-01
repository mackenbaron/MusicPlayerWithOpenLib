#ifndef ORZ_ROOT_H_INCLUDED
#define ORZ_ROOT_H_INCLUDED

#include "orz_animate.h"
#include "orz_writer.h"
#include "orz_base_RBTree.h"
#include "orz_control.h"

namespace Orz
{
    class Root
    {
    public:
        Root();

        // 初始化
        virtual bool CreateScene();

        // 绘制图形
        virtual void UpdateScene();

        // 退出场景
        void QuitScene();

        // 运行
        virtual void Go();

        // 绘图
        void ShowScene();

        // 动画
        Animate* CreateAnimate(KeyType Name, const char *NamePath);
        Animate& GetAnimate(KeyType Name);

        // 书写者
        Writer* CreateWriter(KeyType Name, std::string FontName, std::string Text, int FontSize, Color FontColor, Rect DestRect);
        Writer& GetWriter(KeyType Name);

		// 创建控件
		ControlText* CreateControlText(KeyType Name, const char *ControlName, int X, int Y, int Width, int Height, const char *FontName, int FontSize, const char *Text, Color &TextColor, Color &BackgroundColor);
		ControlButton* CreateControlButton(KeyType Name, const char* PathName, int X, int Y);
		ControlBar* CreateControlBar(KeyType Name, const char* PathName, int X, int Y);
		ControlList* CreateControlList(KeyType Name, const char* PathName, int X, int Y);

		// 得到控件
		ControlText& GetControlText(KeyType Name);
		ControlButton& GetControlButton(KeyType Name);
		ControlBar& GetControlBar(KeyType Name);
		ControlList& GetControlList(KeyType Name);
		

	private:
		friend class Management;

        // 用于标识循环
        bool is_loop;

		// 错误处理
        Animate error_animate;
		Writer error_writer;
		ControlText error_control_text;
		ControlButton error_control_button;
		ControlBar error_control_bar;
		ControlList error_control_list;

		// 红黑树
        RBTree rb_tree;
    };
}
#endif // ORZ_ROOT_H_INCLUDED
