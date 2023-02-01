/** \file   GLFWwindow.cpp */
#include "engine_pch.h"
#include "platform/GLFW/GLFWwindow.h"

namespace Engine {

#ifdef NG_PLATFORM_WINDOWS	
	Window* Window::create(const WindowProperties& properties)
	{
		return new GLFWwindowImpl(properties);
	}
#endif

	//!< Set the properties and callbacks for the window
	GLFWwindowImpl::GLFWwindowImpl(const WindowProperties& properties)
	{
		init(properties);
	}
	void GLFWwindowImpl::init(const WindowProperties& properties)
	{
		m_properties = properties;

		m_aspectRatio = static_cast<float>(m_properties.m_width) / static_cast<float>(m_properties.m_height);

		if (m_properties.m_isFullScreen) {
			Log::error("Fullscreen not yet included");
		}
		else {
			(GLFWwindow*)m_native = glfwCreateWindow(m_properties.m_width, m_properties.m_height, m_properties.m_title, nullptr, nullptr);
		}

		m_context.reset(new GLFW_OpenGL_GC(m_native));
		m_context->init();

		glfwSetWindowUserPointer(m_native, &m_eventHandler);

		glfwSetWindowCloseCallback(m_native,
			[](GLFWwindow* window)
			{
				auto handler = (EventHandler*)glfwGetWindowUserPointer(window);
				auto& callback = handler->getOnCloseCallback();

				WindowCloseEvent wce;
				callback(wce);
			}
		);

		glfwSetWindowSizeCallback(m_native,
			[](GLFWwindow* window, int32_t width, int32_t height)
			{
				auto handler = (EventHandler*)glfwGetWindowUserPointer(window);
				auto& callback = handler->getOnResizeCallBack();

				WindowResizeEvent wre(width, height);
				callback(wre);
			}
		);

		glfwSetWindowFocusCallback(m_native,
			[](GLFWwindow* window, int32_t focused)
			{
				if (focused == GLFW_TRUE)
				{
					auto handler = (EventHandler*)glfwGetWindowUserPointer(window);
					auto& callback = handler->getOnFocusCallBack();
					WindowFocusEvent wfe(focused);
					callback(wfe);
				}
				else
				{
					auto handler = (EventHandler*)glfwGetWindowUserPointer(window);
					auto& callback = handler->getOnLostFocusCallBack();

					WindowLostFocusEvent wfe(focused);
					callback(wfe);
				}
			}
		);

		glfwSetKeyCallback(m_native,
			[](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				if (action == GLFW_PRESS)
				{
					auto& onKeyPress = handler->getOnKeyPressedCallBack();

					KeyPressedEvent e(key, 0);
					onKeyPress(e);
				}
				if (action == GLFW_REPEAT)
				{
					auto& onKeyRepeat = handler->getOnKeyPressedCallBack();

					KeyPressedEvent e(key, 1);
					onKeyRepeat(e);
				}
				if (action == GLFW_RELEASE)
				{
					auto& onKeyRelease = handler->getOnKeyReleasedCallBack();

					KeyReleasedEvent e(key);
					onKeyRelease(e);
				}
			}
		);

		glfwSetMouseButtonCallback(m_native,
			[](GLFWwindow* window, int32_t button, int32_t action, int32_t mods)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				if (action == GLFW_PRESS)
				{
					auto& onButtonPress = handler->getOnButtonPressedCallBack();

					MouseButtonPressedEvent e(button);
					onButtonPress(e);
				}
				if (action == GLFW_RELEASE)
				{
					auto& onButtonRelease = handler->getOnButtonReleasedCallBack();

					MouseButtonReleasedEvent e(button);
					onButtonRelease(e);
				}
			}
		);

		glfwSetCursorPosCallback(m_native,
			[](GLFWwindow* window, double x, double y)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onMouseMove = handler->getOnMouseMovedCallBack();
				
				MouseMovedEvent e(x, y);
				onMouseMove(e);
			}
		);

		glfwSetScrollCallback(m_native,
			[](GLFWwindow* window, double xOffset, double yOffset)
			{
				EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
				auto& onScroll = handler->getOnMouseWheelCallBack();

				MouseScrolledEvent e(xOffset, yOffset);
				onScroll(e);
			}
		);
		
	}
	void GLFWwindowImpl::close()
	{
		glfwDestroyWindow(m_native);
	}

	void GLFWwindowImpl::onUpdate(float timestep)
	{
		glfwPollEvents();
		m_context->swapBuffers();
	}

	void GLFWwindowImpl::onResize(unsigned int width, unsigned int height)
	{
	}

	void GLFWwindowImpl::setVSync(bool VSync)
	{
	}
}



