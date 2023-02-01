/** \file   mouseEvent.h */
#pragma once

#include "event.h"

namespace Engine
{
	/**\class MouseEvent - default mouse class*/
	class MouseEvent : public Event
	{
	public:
		virtual inline int32_t getCategory() const override { return EventCategoryMouse | EventCategoryInput; }	//!< Return category flag
	};

	/**\class MouseButtonPressedEvent - event to process mouse button press*/
	class MouseButtonPressedEvent : public MouseEvent
	{
	protected:
		int32_t m_button;
	public:
		MouseButtonPressedEvent(int32_t button) : m_button(button) {}

		inline int32_t getButton() const { return m_button; }
		static EventType getStaticType() { return EventType::MouseButtonPressed; }	//!< Return static type
		virtual EventType getEventType() const override { return getStaticType(); }	//!< Return event type 
	};

	/**\class MouseButtonReleasedEvent - event to process mouse button release*/
	class MouseButtonReleasedEvent : public MouseEvent
	{
	protected:
		int32_t m_button;
	public:
		MouseButtonReleasedEvent(int32_t button) : m_button(button) {}

		inline int32_t getButton() const { return m_button; }
		static EventType getStaticType() { return EventType::MouseButtonReleased; }	//!< Return static type
		virtual EventType getEventType() const override { return getStaticType(); }	//!< Return event type 
	};

	/**\class MouseMovedEvent - event to process mouse move*/
	class MouseMovedEvent : public MouseEvent
	{
	protected:
		float m_mouseX, m_mouseY;
	public:
		MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}

		static EventType getStaticType() { return EventType::MouseMoved; }	//!< Return static type
		virtual EventType getEventType() const override { return getStaticType(); }	//!< Return event type 
		inline float getX() const { return m_mouseX; }
		inline float getY() const { return m_mouseY; }
		inline glm::vec2 getPos() const { return glm::vec2(m_mouseX, m_mouseY); }
	};

	/**\class MouseScrolledEvent - event to process mouse scroll*/
	class MouseScrolledEvent : public MouseEvent
	{
	protected:
		float m_offsetX, m_offsetY;
	public:
		MouseScrolledEvent(float offsetX, float offsetY) : m_offsetX(offsetX), m_offsetY(offsetY) {}

		static EventType getStaticType() { return EventType::MouseScrolled; }	//!< Return static type
		virtual EventType getEventType() const override { return getStaticType(); }	//!< Return event type 
		inline float getOffsetX() const { return m_offsetX; }
		inline float getOffsetY() const { return m_offsetY; }
	};
}
