#ifndef ORZ_BASE_CONTROL_H_INCLUDED
#define ORZ_BASE_CONTROL_H_INCLUDED

#include <SDL.h>
#include <iostream>
#include "orz_base_math.h"
#include "orz_base_texture.h"
#include "orz_writer.h"
#include <string>

namespace Orz
{
    const int CLICK_DELTA_TIME = 150;
    const int DOUBLE_CLICK_DELTA_TIME = 150;
    //
    //                       ____________  发送"单击"消息
    //                      |
    //                     \|/
    //        _____
    //_______|     |___________________
    //
    //       |________|
    //           |
    //           |
    //           |
    //       CLICK_DELTA_TIME
    //-------------------------------------------------------------
    //
    //
    //
    //                   ________ DOUBLE_CLICK_DELTA_TIME
    //                  |
    //          _____  \|/  _____
    //_________|     |_____|     |_____________
    //
    //                          /|\
    //                           |
    //                           |
    //                        发送"双击"消息
    //
    //----------------------------------------------------------
    //                   ____________________________ 持续发送"持续按键"消息
    //                  ||||||||||||||||||||||
    //                  ||||||||||||||||||||||
    //          _____________________________
    //_________|                             |_______________
    //
    //         |________|                   /|\
    //             |                         |
    //             |                         |
    //             |                         |_____________发送"持续按键结束"消息
    //        CLICK_DELTA_TIME
    //

	// 基础控件类 - 纯虚类
    class BaseControl
    {
    public:

		// 构造函数
		BaseControl(int X, int Y, int Width, int Height, ControlBackgroundStyle BackgroundStyle);

		// 析构函数
        virtual ~BaseControl()=0;

        // 改变控件位置
		virtual BaseControl& ChangePosition(int X, int Y);
		virtual BaseControl& ChangeSize(int Width, int Height);

		// 获取控件位置信息
		const char* GetName();
		BaseControl& GetPosition(int &x, int &y);
		BaseControl& GetSize(int &width, int &height);
		virtual int GetSizeWidth();
		virtual int GetSizeHeight();
		bool IsShow();

		// 显示/隐藏
		void Show(void);
		void Hide(void);

        // 活动 - 判断控件状态
        virtual BaseControl& Contact(int MouseX, int MouseY, bool IsMouseDown);

		// 获取当前控件状态
		ControlMessage GetMessage(void);
		ControlState GetState(void);

		// 判断鼠标是否在控件上
		bool IsMouseOver(int MouseX, int MouseY);

		// 绘制
		virtual void Draw(void);
		virtual void DrawFill(void);

		// 控件名字
		std::string control_name;

		// 位置信息
		int x, y, width, height;

		// 背景样式
		ControlBackgroundStyle background_style;

		// 是否显示
		bool is_show;

		// 当前控件消息&状态
		ControlMessage control_message;
		ControlState control_state;

        // 处理/记录事件
        unsigned int last_down_time, last_up_time; //  最后一次单击/双击控件的时间
        bool is_last_down; // 上次是否按下
        bool in_judge_click, in_judge_double_click, in_judge_const_down; // 是否在判断鼠标事件之内
        unsigned int curr_time, delta_time; // 当前时间/推移时间

    };

}

#endif // ORZ_CONTROL_H_INCLUDED
