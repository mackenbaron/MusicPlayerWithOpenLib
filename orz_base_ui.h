
#ifndef ORZ_BASE_UI_H_INCLUDED
#define ORZ_BASE_UI_H_INCLUDED

#include "orz_base_element.h"

namespace Orz
{
	class BaseUi:public BaseElement
	{
	public:
		BaseUi(ElementType Type, float distance);

		UiMessage GetUiMessage(void);
		UiState GetUiState(void);

		void SetUiMessage(UiMessage Meassage);
		void SetUiState(UiState State);

	private:
		friend class BaseContorl;

		virtual void DoContact(void);
		virtual void DoContactReset(void);
		virtual void DoDraw(const Rect& DrawRect);

		// 当前控件消息and状态
		UiMessage ui_message;
		UiState ui_state;
	};
}

#endif