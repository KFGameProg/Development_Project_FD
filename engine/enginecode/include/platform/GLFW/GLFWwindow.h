/** \file GLFWwindow.h */
#pragma once

#include "platform/GLFW/GLFWsystems.h"
#include "platform/GLFW/GLFW_OpenGL_GC.h"
#include "platform/window/window.h"
#include <include\independent\systems\inputPoller.h>
#include <include\platform\GLFW\GLFWCodes.h>

namespace Engine
{
	/** \class GLFWwindowImpl - Implementation of the GLFW window */
	class GLFWwindowImpl : public Window
	{
	public:
		GLFWwindowImpl(const WindowProperties& properties);
		virtual void init(const WindowProperties& properties) override;
		virtual void close() override;
		//virtual ~Window() {};
		virtual void onUpdate(float timestep) override;
		virtual void onResize(unsigned int width, unsigned int height) override;
		virtual void setVSync(bool VSync) override;
		virtual inline unsigned int getWidth() const override { return m_properties.m_width; }
		virtual inline unsigned int getHeight() const override { return m_properties.m_height; }
		virtual inline void* getNativeWindow() const override { return m_native; }
		virtual inline bool isFullScreenMode() const override { return m_properties.m_isFullScreen; }
		virtual inline bool isVSync() const override { return m_properties.m_isVSync; }

		virtual EventHandler& getEventHandler() override { return m_eventHandler; }
	protected:
		WindowProperties m_properties; //!< Properties
		GLFWwindow* m_native;	//!< Native GLFW Window
		EventHandler m_eventHandler; //!< Event Handler

		float m_aspectRatio; //!< Aspect Ratio
	};
}
