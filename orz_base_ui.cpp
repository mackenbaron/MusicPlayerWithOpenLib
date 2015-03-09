
#include "orz_base_ui.h"

namespace Orz
{
	BaseUi::BaseUi(ElementType Type, float distance):
	BaseElement(Type, 0,0,0,0, 0.0f)
	{
	}

	UiMessage BaseUi::GetUiMessage(void)
	{
		return ui_message;
	}

	UiState BaseUi::GetUiState(void)
	{
		return ui_state;
	}

	void BaseUi::SetUiMessage(UiMessage Meassage)
	{
		ui_message = Meassage;
	}

	void BaseUi::SetUiState(UiState State)
	{
		ui_state = State;
	}

	void BaseUi::DoContact(void)
	{

	}

	void BaseUi::DoContactReset(void)
	{

	}

	void BaseUi::DoDraw(void)
	{
		#ifdef CodeDebug
			Rect out_rect = {x -1, y -1, width+1, height +1};
			device.display.DrawOutlineRect(RedColor, out_rect);
		#endif
	}

}