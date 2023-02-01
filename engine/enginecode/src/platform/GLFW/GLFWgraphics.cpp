/** \file   GLFWgraphics.cpp */
#include "engine_pch.h"
#include "platform/GLFW/GLFWgraphics.h"

namespace Engine {

	void GLFWGraphicsContext::init()  {
		glfwMakeContextCurrent(m_window);
		int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		//NG_ASSERT(result, "Failed to initialise GLAD");
	}
	void GLFWGraphicsContext::swapBuffers()  { glfwSwapBuffers(m_window); }
}