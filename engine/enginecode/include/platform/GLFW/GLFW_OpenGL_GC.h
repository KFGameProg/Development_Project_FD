/** \ file GLFW_OpenGL_GC.h */
#pragma once
#include "core/GC.h"

namespace Engine
{
	/** \class GLFW_OpenGL_GC - Setting the Graphics context */
	class GLFW_OpenGL_GC : public GraphicsContext
	{
	public:
		GLFW_OpenGL_GC(GLFWwindow* window) : m_window(window) {};
		virtual void init() override; //!< Initialises the Graphics context
		virtual void swapBuffers() override; //!< Swaps front and back buffers
	private:
		GLFWwindow* m_window;	//!< Native GLFW Window
	};
}
