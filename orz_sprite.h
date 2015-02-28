#ifndef ORZ_SPRITE_H_INCLUDED
#define ORZ_SPRITE_H_INCLUDED

#include "orz_base_math.h"
#include "orz_animate.h"
#include <vector>
#include <string>


namespace Orz
{
	struct AnimateWithState
	{
		Animate animate;
		SpriteState state;

		AnimateWithState(const char *NamePath, SpriteState State):
		animate(NamePath), state(State)
		{
		}
	};

	// 精灵
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		bool LoadSprite(const char* PathName, int X, int Y, int Width, int Height);
		void Contact(SpriteState CurrentState);
		void ContactReset(void);
		SpriteState GetState(void);

		Sprite& ChangePosition(int X, int Y);
		Sprite& ChangeSize(int Width, int Height);

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

		// 在矩形内按比例绘制图形
		void Draw();
		void DrawFill();
		void Draw(Rect &DestRect);
		void DrawFill(Rect &DestRect);

	private:
		void Free();

		// 无法复制?
		//Sprite(const Sprite & source);
		//Sprite& operator=(const Sprite & source);

		std::vector<AnimateWithState> element;

		std::string name;
		Rect dest_rect;

		SpriteState curr_state;
	};
}

#endif // ORZ_SPRITE_H_INCLUDED

