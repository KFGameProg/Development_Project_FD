/** \file   inputHandler.cpp */
#include "engine_pch.h"
#include <glad/glad.h>
#include "systems/inputHandler.h"

namespace Engine
{
//---------------------------------------Events---------------------------------------

	//!< On Close Event 
	bool InputHandler::onClose(WindowCloseEvent& e)
	{
		e.handle(true);
		Log::info("Closing Application");
		m_running = false;
		return e.handled();
	}

	//!< On Resize Event
	bool InputHandler::onResize(WindowResizeEvent& e)
	{
		e.handle(true);
		auto& size = e.getSize();
		Log::info("Resize Window to {0}x{1}", size.x, size.y);
		return e.handled();
	}

	//!< On Window Focus Event
	bool InputHandler::onFocus(WindowFocusEvent& e)
	{
		e.handle(true);
		Log::info("Window Focused");
		return e.handled();
	}

	//!< On Window Lost Focus Event
	bool InputHandler::onLostFocus(WindowLostFocusEvent& e)
	{
		e.handle(true);
		Log::info("Lost Window Focus");
		return e.handled();
	}

	//!< On Key Press Event
	bool InputHandler::onKeyPressed(KeyPressedEvent& e)
	{
		e.handle(true);
		Log::info("Key Pressed event: key {0}, repeat {1}", e.getKey(), e.getRepeatCount());

		if (e.getKey() == NG_KEY_ESCAPE)
		{
			m_running = false;
		}

		return e.handled();
	}

	//!< On Key Release Event
	bool InputHandler::onKeyReleased(KeyReleasedEvent& e)
	{
		e.handle(true);
		Log::info("Key Released Event: key {0}", e.getKey());
		return e.handled();
	}

	//!< On Mouse Button Press Event
	bool InputHandler::onMouseButtonPress(MouseButtonPressedEvent& e)
	{
		e.handle(true);
		Log::info("Mouse Pressed Event: button {0}", e.getButton());
		if (e.getButton() == NG_MOUSE_BUTTON_1)			//!< Left Mouse Button
		{
			Log::warn("Left Mouse Button Pressed");
			glClearColor(1.f, 1.f, 1.f, 1.f);
		}
		if (e.getButton() == NG_MOUSE_BUTTON_2)			//!< Right Mouse Button
		{
			Log::warn("Right Mouse Button Pressed");
			glClearColor(0.f, 0.f, 0.f, 1.f);
		}
		if (e.getButton() == NG_MOUSE_BUTTON_3)			//!< Middle Mouse Button
		{
			Log::warn("Middle Mouse Button Pressed");
			Log::error("Current Mouse Position: ({0}, {1})", InputPoller::getMouseX(), InputPoller::getMouseY());
		}
		return e.handled();
	}

	//!< On Mouse Button Release Event
	bool InputHandler::onMouseButtonRelease(MouseButtonReleasedEvent& e)
	{
		e.handle(true);
		Log::info("Mouse Released Event: button {0}", e.getButton());
		return e.handled();
	}

	//!< On Mouse Move Event
	bool InputHandler::onMouseMove(MouseMovedEvent& e)
	{
		e.handle(true);
		auto& pos = e.getPos();
		//Log::info("Mouse Moved Event: ({0}, {1})", pos.x, pos.y);
		return e.handled();
	}

	//!< On Mouse Scroll Event
	bool InputHandler::onMouseScroll(MouseScrolledEvent& e)
	{
		e.handle(true);
		Log::info("Mouse Wheel Event: {0}", e.getOffsetY());
		return e.handled();
	}
	

//-----------------------------------Input Handling-----------------------------------------------

	void InputHandler::KeyPress(int32_t key, int32_t scancode, int32_t action, int32_t mods)
	{
		if(key < numKeys) {
			if (action == GLFW_PRESS)
				m_keysPressed[key] = true;
			else if (action == GLFW_RELEASE)
				m_keysPressed[key] = false;
		}
	}

	void InputHandler::MouseScroll(float xOffset, float yOffset)
	{
		m_Xscroll = xOffset;
		m_Yscroll = yOffset;
	}

	void InputHandler::MouseMove(float xPos, float yPos)
	{
		if (m_firstPress) {  // initialise lastPos to currentPos on first frame

			m_lastX = m_Xpos;
			m_lastY = m_Ypos;
			m_firstPress = false;
		}
		// difference between current position and pre position
		m_mouseDeltaX = xPos - m_lastX;
		m_mouseDeltaY = m_lastY - yPos;

		m_lastX = xPos;
		m_lastY = yPos;
	}

	void InputHandler::MouseClick(int32_t button, int32_t action, int32_t mods)
	{
		if (button < numOfMouseButtons) {  // left or right mouse, update if need additional mouse buttons
			if (action == GLFW_PRESS) {
				m_mouseButtonPressed[button] = true;  // button is pressed
				m_isDragging = false;                 // mouse is dragging
			}
			else if ((action == GLFW_RELEASE)) {
				m_mouseButtonPressed[button] = false;  // button release
				m_isDragging = false;                  // no longer dragging
			}
		}
	}

	void InputHandler::endFrame()
	{
		m_mouseDeltaX = 0.0f;
		m_mouseDeltaY = 0.0f;
	}	
}