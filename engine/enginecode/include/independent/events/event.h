/** \file event.h */
#pragma once

#include <inttypes.h>
#include <glm/glm.hpp>
#include <string>

namespace Engine
{
	/** \enum EventType - enum for events */
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped, MouseButtonPressed, MouseButtonReleased,
		MouseMoved, MouseScrolled
	};

	/** \enum EventCategory*/
	enum EventCategory
	{
		None = 0,
		EventCategoryWindow = 1 << 0,	//00000001
		EventCategoryInput = 1 << 1,	//00000010
		EventCategoryKeyboard = 1 << 2,	//00000100
		EventCategoryMouse = 1 << 3,	//00001000
		EventCategoryMouseButton = 1 << 4,	//00010000
	};

	/** \class Event Dispatcher */
	/*class EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_event(event) {}

		template<typename T>
		bool dispatch(EventFunc<T> func)
		{
			if (m_event.getEventType() == T::getStaticType())
			{
				m_event.handle(func(*((T*)&m_event)));
				return true;
			}
			return false;
		}
	private:
		Event& m_event;
	};*/

	/** \class Event - Event Base Class*/
	class Event
	{
	public:
		virtual EventType getEventType() const = 0;	//!<	Get Event Type
		virtual int32_t getCategory() const = 0;	//!<	Get Event Category Flags
		inline bool handled() const { return m_handled; }	//!<	Run to confirm event completion
		inline void handle(bool isHandled) { m_handled = isHandled; }	//!< Handle the event
		inline bool isInCategory(EventCategory category) const { return getCategory() & category; }	//!< check for the event in category 
	protected:
		bool m_handled = false;	//!<	Boolean classifying event completion 
	};
}