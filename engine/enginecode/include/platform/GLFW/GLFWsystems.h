/** \file GLFWsystems.h */
#pragma once

#include <GLFW/glfw3.h>

#include "systems/system.h"
#include "core/log.h"

namespace Engine
{
	/** \class GLFWSystem - System logic for program */
	class GLFWSystem : public System
	{
	public:
		virtual void start(SystemSignal init = SystemSignal::None, ...) override //!< Start the system
		{
			glfwInit();
			if (!glfwInit)
			{
				Log::error("glfw has Failed");
			};
			glfwSetErrorCallback(
				[](int errorCode, const char* errorMsg)
				{
					Log::error("GLFW error code {} msg {}", errorCode, errorMsg);
				}
			);
		};
		virtual void stop(SystemSignal close = SystemSignal::None, ...) override //!< Stop the system
		{
			glfwTerminate();
		};
	};
}