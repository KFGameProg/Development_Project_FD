/** \file   GLFWInputPoller.h */
#pragma once
#include "GLFWwindow.h"
#include <glm/glm.hpp>

namespace Engine {

	/** \class GLFWInputPoller - Input Poller for current window */
	class GLFWInputPoller
	{
	public:
		static bool keyPressed(int32_t key); //!< Whether specified key is called
		static bool mouseButtonPressed(int32_t button); //!< Whether mouse button is pressed 
		static glm::vec2 getMousePos(); //!< Function to determine mouse position
		static void setCurrentWindow(GLFWwindow* newWindow) { s_window = newWindow; } //!< Set the current active window
	protected:
		static GLFWwindow* s_window;
	};
}
