#ifndef ORZ_SPRITE_H_INCLUDED
#define ORZ_SPRITE_H_INCLUDED

#include "orz_base_ui.h"
#include "orz_base_math.h"
#include <string>

namespace Orz
{
	// ����
	class Sprite: public BaseUi
	{
	public:
		Sprite();

		// ���ؾ���
		bool LoadSprite(const char* PathName, const Rect &SpriteRect);

		// �ı�����
		Sprite& ChangeBlendModeToNone(void);
		Sprite& ChangeBlendModeToAlpha(void);
		Sprite& ChangeBlendModeToAdd(void);
		Sprite& ChangeBlendModeToMod(void);

	private:
		void DoDraw(void);
		void DoContact(void);
		void DoContactReset(void);
		void DoChangeAlpha(uint8_t Alpha);
	};
}

#endif // ORZ_SPRITE_H_INCLUDED

