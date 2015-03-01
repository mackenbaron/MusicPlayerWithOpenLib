#ifndef ORZ_ANIMATE_H_INCLUDED
#define ORZ_ANIMATE_H_INCLUDED

#include "orz_base_math.h"
#include "orz_base_texture.h"

namespace Orz
{
    // 帧动画
    class Animate
    {
    public:
		Animate();
		~Animate();
		Animate(const char *NamePath);
        bool LoadAnimate(const char *NamePath);
        Animate& Contact(void);
        void ContactReset(void);

		// 设置透明度/可见度(0 -255)
		// ( 0 - 不可见, 255 - 不透明)
		void SetAlpha(int Alpha);
        
		// dstRGBA = srcRGBA
        void SetBlendModeToNone();
        
		// dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
        // dstA = srcA + (dstA * (1-srcA))
        void SetBlendModeToAlpha();
        
		// dstRGB = (srcRGB * srcA) + dstRGB
        // dstA = dstA
        void SetBlendModeToAdd();

        // dstRGB = srcRGB * dstRGB
        // dstA = dstA
        void SetBlendModeToMod();

		void Draw(Rect &dest_rect);
		void DrawFill(Rect &DestRect);
        void Draw(int x, int y, float scale = 1.0);
		void DrawEx(int x, int y, float scale = 1.0, float angle = .0 ,Point *center = NULL, FlipMod flip_mod = FLIP_NONE);
		void DrawEx(int x, int y, float width_scale, float height_scale, float angle, Point *center);


    private:
        // 无法复制
        //Animate(const Animate & source);
        //Animate& operator=(const Animate & source);

        std::string name;
        int width;
        int height;
        BaseTexture image;
        bool is_loop, is_show;
        unsigned long total_time;	// total time
        unsigned long curr_time;	// current frame
        unsigned long total_frame;	// total frame
        unsigned long curr_frame;	// current frame

        unsigned long begin_time;	// the time when it begin play
        Rect dest_rect, source_rect;
    };
}




#endif // ORZ_ANIMATE_H_INCLUDED
