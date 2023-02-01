/** \ file window.h */
#pragma once

#include "events/windowsEvent.h"
#include "events/eventHandler.h"
#include "core/GC.h"



namespace Engine
{
	/** \struct WindowProperties
	 *  \brief Properties for window class
	 */
	struct WindowProperties
	{
		const char* m_title;
		uint32_t m_width;
		uint32_t m_height;
		bool m_isFullScreen;
		bool m_isVSync;

		WindowProperties(const char* title = "My Window", uint32_t width = 800, uint32_t height = 600, bool fullscreen = false, bool vsync = true) :
			m_title(title), m_width(width), m_height(height), m_isFullScreen(fullscreen), m_isVSync(vsync) {}
	};

	/**
	 * \class Window
	 * \brief class to build a viewer window
	 */
	class Window
	{
	public:
		virtual void init(const WindowProperties& properties) = 0;
		virtual void close() = 0;
		virtual ~Window() {};
		virtual void onUpdate(float timestep) = 0;
		virtual void onResize(unsigned int width, unsigned int height) = 0;
		virtual void setVSync(bool VSync) = 0;
		virtual inline unsigned int getWidth() const = 0; 
		virtual inline unsigned int getHeight() const = 0;
		virtual inline void* getNativeWindow() const = 0;
		virtual inline bool isFullScreenMode() const = 0;
		virtual inline bool isVSync() const = 0;

		virtual EventHandler& getEventHandler() = 0;
		
		static Window* create(const WindowProperties& properties = WindowProperties());
	protected:
		std::shared_ptr<GraphicsContext> m_context;
	};
}