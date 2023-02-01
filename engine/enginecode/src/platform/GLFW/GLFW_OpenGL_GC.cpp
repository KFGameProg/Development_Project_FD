/** \file GLFW_OpenGL_GC.cpp */
#include <engine_pch.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "platform/GLFW/GLFW_OpenGL_GC.h"
#include "core/log.h"

namespace Engine
{
	//!< Set OpenGL Context
	void GLFW_OpenGL_GC::init()
	{
		glfwMakeContextCurrent(m_window);
		auto result = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		if (!result) { Log::error("Cannot create OpenGL context for active window: {0}", result); }

		// Enable OpenGL debug with callback
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(
			[](
				GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* userParam
				)
			{
				switch (severity)
				{
				case GL_DEBUG_SEVERITY_HIGH:
					Log::error(message);
					break;
				case GL_DEBUG_SEVERITY_MEDIUM:
					Log::warn(message);
					break;
				case GL_DEBUG_SEVERITY_LOW:
					Log::info(message);
					break;
				case GL_DEBUG_SEVERITY_NOTIFICATION:
					Log::trace(message);
					break;
				}
			}
			, nullptr);
	}

	void GLFW_OpenGL_GC::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}
