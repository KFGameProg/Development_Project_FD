/** \file   GLFWInputPoller.cpp */

#include <engine_pch.h>
#include "platform/GLFW/GLFWInputPoller.h"
#include <GLFW/glfw3.h>

namespace Engine
{
#ifdef	NG_PLATFORM_WINDOWS

	/** Set Input Poller for window */
	GLFWwindow* GLFWInputPoller::s_window = nullptr;

	bool GLFWInputPoller::keyPressed(int32_t key)
	{
		if (s_window)
		{
			auto answer = glfwGetKey(s_window, key);
			return answer == GLFW_PRESS || answer == GLFW_REPEAT;
		}
		return false;
	}

	bool GLFWInputPoller::mouseButtonPressed(int32_t button)
	{
		if (s_window)
		{
			auto answer = glfwGetMouseButton(s_window, button);
			return answer == GLFW_PRESS;
		}
		return false;
	}
	glm::vec2 GLFWInputPoller::getMousePos()
	{
		if (s_window)
		{
			double x, y;
			glfwGetCursorPos(s_window, &x, &y);
			return glm::vec2(static_cast<float>(x), static_cast<float>(y));
		}
		return glm::vec2(-1.f, 1.f);
	}

#endif
}