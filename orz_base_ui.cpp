
#include "orz_base_ui.h"
#include "orz_base_public_resource.h"

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

	void BaseUi::DoDraw(const Rect& DrawRect)
	{
	}

}