/** \file   inputHandler.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "systems/inputHandler.h"

namespace Engine
{
//-----------------------------------Input Handling-----------------------------------------------
	
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

	void InputHandler::KeyPress(int32_t key, int32_t scancode, int32_t action, int32_t mods)
	{
		if(key < numKeys) {
			if (action == GLFW_PRESS)
				m_keysPressed[key] = true;
			else if (action == GLFW_RELEASE)
				m_keysPressed[key] = false;
		}
	}
}