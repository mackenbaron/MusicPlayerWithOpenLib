
#include "orz_base_control.h"
#include "orz_config.h"


namespace Orz
{
	BaseControl::BaseControl(ElementType Type, int X, int Y, int Width, int Height, ControlBackgroundStyle BackgroundStyle):
	BaseElement(Type, X, Y, Width, Height, 0.0f),
	background_style(BackgroundStyle)
	{

	}

	BaseControl::~BaseControl()
	{

	}

	BaseControl& BaseControl::Contact(int MouseX, int MouseY, bool IsMouseDown)
	{
		BaseElement::Contact(MouseX, MouseY, IsMouseDown);

		switch(element_message)
		{
		case ELEMENT_MESSAGE_FUNCTION_ERROR:
			control_message = CONTROL_MESSAGE_FUNCTION_ERROR;
			break;
		case ELEMENT_MESSAGE_MOUSE_OUT:
			control_message = CONTROL_MESSAGE_MOUSE_OUT;
			break;
		case ELEMENT_MESSAGE_MOUSE_OVER:
			control_message = CONTROL_MESSAGE_MOUSE_OVER;
			break;
		case ELEMENT_MESSAGE_MOUSE_CONST_DOWN:
			control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN;
			break;
		case ELEMENT_MESSAGE_MOUSE_CONST_DOWN_END:
			control_message = CONTROL_MESSAGE_MOUSE_CONST_DOWN_END;
			break;
		case ELEMENT_MESSAGE_MOUSE_CLICK:
			control_message = CONTROL_MESSAGE_MOUSE_CLICK;
			break;
		case ELEMENT_MESSAGE_MOUSE_DOUBLE_CLICK:
			control_message = CONTROL_MESSAGE_MOUSE_DOUBLE_CLICK;
			break;
		}

		switch(element_state)
		{
		case ELEMENT_STATE_MOUSE_OUT:
			control_state = CONTROL_STATE_MOUSE_OUT;
			break;
		case ELEMENT_STATE_MOUSE_OVER:
			control_state = CONTROL_STATE_MOUSE_OVER;
			break;
		case ELEMENT_STATE_MOUSE_DOWN:
			control_state = CONTROL_STATE_MOUSE_DOWN;
			break;;
		}

		return *this;
	}

	ControlMessage BaseControl::GetMessage(void)
	{
		return control_message;
	}

	ControlState BaseControl::GetState(void)
	{
		return control_state;
	}

	void BaseControl::DoDraw(void)
	{

	}
}