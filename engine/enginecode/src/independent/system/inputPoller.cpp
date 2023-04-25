/** \file   inputPoller.cpp */

#include <engine_pch.h>
#include "independent/systems/inputPoller.h"

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWInputPoller.h"
#include <GLFW/glfw3.h>
#endif // NG_PLATFORM_WINDOWS

namespace Engine
{
#ifdef NG_PLATFORM_WINDOWS
	bool InputPoller::keyPressed(int32_t key)
	{
		return GLFWInputPoller::keyPressed(key);
	}

	bool InputPoller::mouseButtonPressed(int32_t button)
	{
		return GLFWInputPoller::mouseButtonPressed(button);
	}

	bool InputPoller::mouseButtonReleased(int32_t button)
	{
		return GLFWInputPoller::mouseButtonReleased(button);
	}

	glm::vec2 InputPoller::getMousePos()
	{
		return GLFWInputPoller::getMousePos();
	}

	void InputPoller::setNativeWindow(void* nativeWindow)
	{
		GLFWInputPoller::setCurrentWindow(reinterpret_cast<GLFWwindow*>(nativeWindow));
	}
#endif // NG_PLATFORM_WINDOWS
}
