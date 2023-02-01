/** \file   GLFWgraphics.h */
#pragma once
#include <glad/glad.h>
#include "GLFWwindow.h"
#include "core/GC.h"

namespace Engine {
	/** \class GLFWGraphicsContext - Setting the window graphics context */
	class GLFWGraphicsContext : public GraphicsContext
	{
	public:
		GLFWGraphicsContext(GLFWwindow* window) : m_window(window) {};
		void init() override;
		void swapBuffers() override;
	private:
		GLFWwindow* m_window;
	};
}