/** \file windowsEvent.h */
#pragma once

#include "event.h"
#include <GLFW\glfw3.h>

namespace Engine
{
	/**\class WindowEvent - default window class*/
	class WindowEvent : public Event
	{
	public:
		virtual int32_t getCategory() const override { return EventCategoryWindow; }	//!< Return category flag
	};

	/**\class WindowCloseEvent - event to close window*/
	class WindowCloseEvent : public WindowEvent
	{
	public:
		WindowCloseEvent() {}

		static EventType getStaticType() { return EventType::WindowClose; }	//!< Return static type
		virtual EventType getEventType() const override { return getStaticType(); }	//!< Return event type 
	};
	
	/**\class WindowResizeEvent - event to resize the window*/
	class WindowResizeEvent : public WindowEvent
	{
	public:
		WindowResizeEvent(int32_t width, int32_t height) : m_width(width), m_height(height) {}

		static EventType getStaticType() { return EventType::WindowResize; }	//!< Return static type
		virtual EventType getEventType() const override { return getStaticType(); }	//!< Return event type 

		inline int32_t getWidth() const { return m_width; }
		inline int32_t getHeight() const { return m_height; }
		inline glm::ivec2 getSize() const { return { m_width, m_height }; }
	private:
		int32_t m_width;
		int32_t m_height;
	};

	/**\class WindowFocusEvent - event to focus on the window*/
	class WindowFocusEvent : public WindowEvent
	{
	public:
		WindowFocusEvent(int32_t focused) {}

		static EventType getStaticType() { return EventType::WindowFocus; }	//!< Return static type
		virtual EventType getEventType() const override { return getStaticType(); }	//!< Return event type
	};

	/**\class WindowLoseFocusEvent - event to lose focus on the window*/
	class WindowLostFocusEvent : public WindowEvent
	{
	public:
		WindowLostFocusEvent(int32_t focused) {}

		static EventType getStaticType() { return EventType::WindowLostFocus; }	//!< Return static type
		virtual EventType getEventType() const override { return getStaticType(); }	//!< Return event type
	};
}
