/** \file   keyEvent.h */
#pragma once

#include "event.h"

namespace Engine
{
	/** \class KeyEvent - default key class */
	class KeyEvent : public Event
	{
	protected:
		KeyEvent(int32_t key) : m_key(key) {};
		int32_t m_key;
	public:
		inline int32_t getKey() const { return m_key; }	//!< Return Key Press
		virtual inline int32_t getCategory() const override { return EventCategoryKeyboard | EventCategoryInput; }	//!< Return category flag
	};

	/**\class KeyPressedEvent - event to process key press*/
	class KeyPressedEvent : public KeyEvent
	{
	protected:
		int32_t m_repeatCount;
	public:
		KeyPressedEvent(int32_t key, int32_t repeatCount) : KeyEvent(key), m_repeatCount(repeatCount) {}

		inline int32_t getRepeatCount() const { return m_repeatCount; }
		static EventType getStaticType() { return EventType::KeyPressed; }	//!< Return static type
		virtual EventType getEventType() const override { return getStaticType(); }	//!< Return event type 
	};

	/**\class KeyReleasedEvent - event to process key release*/
	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int32_t key) : KeyEvent(key) {}

		inline int32_t getKey() const { return m_key; }
		static EventType getStaticType() { return EventType::KeyReleased; }	//!< Return static type
		virtual EventType getEventType() const override { return getStaticType(); }	//!< Return event type 
	};

	/**\class KeyTypedEvent - event to process key typed*/
	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int32_t key) : KeyEvent(key) {}

		inline int32_t getKey() const { return m_key; }
		static EventType getStaticType() { return EventType::KeyTyped; }	//!< Return static type
		virtual EventType getEventType() const override { return getStaticType(); }	//!< Return event type 
	};
}
