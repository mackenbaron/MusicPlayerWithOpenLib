#ifndef ORZ_ANIMATE_H_INCLUDED
#define ORZ_ANIMATE_H_INCLUDED

#include "orz_base_math.h"
#include "orz_base_texture.h"
#include "orz_base_ui.h"

namespace Orz
{
    // 帧动画
    class Animate: public BaseUi
    {
	private:
		void DoChangeAlpha(uint8_t Alpha);

    public:
		Animate();

		// 读取文件
        bool LoadAnimate(const char *NamePath, const Rect &AnimateRect);

		// 混合模式
        Animate& ChangeBlendModeToNone();	// dstRGBA = srcRGBA
        Animate& ChangeBlendModeToAlpha();	// dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA)) // dstA = srcA + (dstA * (1-srcA))
        Animate& ChangeBlendModeToAdd();	// dstRGB = (srcRGB * srcA) + dstRGB // dstA = dstA
        Animate& ChangeBlendModeToMod();	// dstRGB = srcRGB * dstRGB // dstA = dstA

		// 改变属性
		Animate& ChangeAngle(float Angle);
		Animate& ChangeCenter(Point &Center);
		Animate& ChangeFlipMode(FlipMode Mode);
		Animate& ChangeToEnableAdvanceAttribute(); // 使用 Angle, Center 和 FlipMod 属性,仅本次绘制有效
		Animate& ChangeToDisableAdvanceAttribute();

    private:
		// 绘制
		void DoDraw(void);
		void DoContact(void);
		void DoContactReset(void);

        BaseTexture image;
        bool is_loop;
        unsigned long total_time;	// total loop time (ms)
        unsigned long total_frame;	// total frame
        unsigned long curr_frame;	// current frame

        unsigned long begin_time;	// the time when it begin play
		Rect source_rect;

		bool is_use_angle_and_center_to_draw;
		Point animate_center;
		float animate_angle;
		FlipMode animate_flip_mode;
    };
}




#endif // ORZ_ANIMATE_H_INCLUDED
