/** \file eventHandler.h */
#pragma once

#include <functional>

#include "events/eventCases.h"

namespace Engine
{
	/** \class EventHandler - Holds scene event data */
	class EventHandler
	{
	public:
		void setOnCloseCallBack(const std::function<bool(WindowCloseEvent&)>& fn) { m_onCloseCallback = fn; }
		void setOnResizeCallBack(const std::function<bool(WindowResizeEvent&)>& fn) { m_onResizeCallback = fn; }
		void setOnFocusCallBack(const std::function<bool(WindowFocusEvent&)>& fn) { m_onFocusCallback = fn; }
		void setOnLostFocusCallBack(const std::function<bool(WindowLostFocusEvent&)>& fn) { m_onLostFocusCallback = fn; }
		//void setOnWindowMovedCallBack(const std::function<bool(WindowMovedEvent&)>& fn) { m_onWindowMovedCallback = fn; }
		void setOnKeyPressedCallBack(const std::function<bool(KeyPressedEvent&)>& fn) { m_onKeyPressedCallback = fn; }
		void setOnKeyReleasedCallBack(const std::function<bool(KeyReleasedEvent&)>& fn) { m_onKeyReleasedCallback = fn; }
		void setOnKeyTypedCallBack(const std::function<bool(KeyTypedEvent&)>& fn) { m_onKeyTypedCallback = fn; }
		void setOnButtonPressedCallBack(const std::function<bool(MouseButtonPressedEvent&)>& fn) { m_onButtonPressedCallback = fn; }
		void setOnButtonReleasedCallBack(const std::function<bool(MouseButtonReleasedEvent&)>& fn) { m_onButtonReleasedCallback = fn; }
		void setOnMouseMovedCallBack(const std::function<bool(MouseMovedEvent&)>& fn) { m_onMouseMovedCallback = fn; }
		void setOnMouseWheelCallBack(const std::function<bool(MouseScrolledEvent&)>& fn) { m_onMouseWheelCallback = fn; }
		
		std::function<bool(WindowCloseEvent&)>& getOnCloseCallback() { return m_onCloseCallback; }
		std::function<bool(WindowResizeEvent&)>& getOnResizeCallBack() { return m_onResizeCallback; }
		std::function<bool(WindowFocusEvent&)>& getOnFocusCallBack() { return m_onFocusCallback; }
		std::function<bool(WindowLostFocusEvent&)>& getOnLostFocusCallBack() { return m_onLostFocusCallback; }
		//std::function<bool(WindowMovedEvent&)>& getOnWindowMovedCallBack() { return m_onWindowMovedCallback; }
		std::function<bool(KeyPressedEvent&)>& getOnKeyPressedCallBack() { return m_onKeyPressedCallback; }
		std::function<bool(KeyReleasedEvent&)>& getOnKeyReleasedCallBack() { return m_onKeyReleasedCallback; }
		std::function<bool(KeyTypedEvent&)>& getOnKeyTypedCallBack() { return m_onKeyTypedCallback; } 
		std::function<bool(MouseButtonPressedEvent&)>& getOnButtonPressedCallBack() { return m_onButtonPressedCallback; }
		std::function<bool(MouseButtonReleasedEvent&)>& getOnButtonReleasedCallBack() { return m_onButtonReleasedCallback; }
		std::function<bool(MouseMovedEvent&)>& getOnMouseMovedCallBack() { return m_onMouseMovedCallback; }
		std::function<bool(MouseScrolledEvent&)>& getOnMouseWheelCallBack() { return m_onMouseWheelCallback; }

	private:
		std::function<bool(WindowCloseEvent&)> m_onCloseCallback = std::bind(&EventHandler::defaultOnClose, this, std::placeholders::_1);
		std::function<bool(WindowResizeEvent&)> m_onResizeCallback = std::bind(&EventHandler::defaultOnResize, this, std::placeholders::_1);
		std::function<bool(WindowFocusEvent&)> m_onFocusCallback = std::bind(&EventHandler::defaultOnFocus, this, std::placeholders::_1);
		std::function<bool(WindowLostFocusEvent&)> m_onLostFocusCallback = std::bind(&EventHandler::defaultOnLostFocus, this, std::placeholders::_1);
		//std::function<bool(WindowMovedEvent&)> m_onWindowMovedCallback = std::bind(&EventHandler::defaultOnWindowMove, this, std::placeholders::_1);
		std::function<bool(KeyPressedEvent&)> m_onKeyPressedCallback = std::bind(&EventHandler::defaultOnKeyPress, this, std::placeholders::_1);
		std::function<bool(KeyReleasedEvent&)> m_onKeyReleasedCallback = std::bind(&EventHandler::defaultOnKeyRelease, this, std::placeholders::_1);
		std::function<bool(KeyTypedEvent&)> m_onKeyTypedCallback = std::bind(&EventHandler::defaultOnKeyType, this, std::placeholders::_1);
		std::function<bool(MouseButtonPressedEvent&)> m_onButtonPressedCallback = std::bind(&EventHandler::defaultOnMouseButtonPress, this, std::placeholders::_1);
		std::function<bool(MouseButtonReleasedEvent&)> m_onButtonReleasedCallback = std::bind(&EventHandler::defaultOnMouseButtonRelease, this, std::placeholders::_1);
		std::function<bool(MouseMovedEvent&)> m_onMouseMovedCallback = std::bind(&EventHandler::defaultOnMouseMove, this, std::placeholders::_1);
		std::function<bool(MouseScrolledEvent&)> m_onMouseWheelCallback = std::bind(&EventHandler::defaultOnMouseScroll, this, std::placeholders::_1);
		
		bool defaultOnClose(WindowCloseEvent& e) { return false; }
		bool defaultOnResize(WindowResizeEvent& e) { return false; }
		bool defaultOnFocus(WindowFocusEvent& e) { return false; }
		bool defaultOnLostFocus(WindowLostFocusEvent& e) { return false; }
		//bool defaultOnWindowMove(WindowMovedEvent& e) { return false; }
		bool defaultOnKeyPress(KeyPressedEvent& e) { return false; }
		bool defaultOnKeyRelease(KeyReleasedEvent& e) { return false; }
		bool defaultOnKeyType(KeyTypedEvent& e) { return false; }
		bool defaultOnMouseButtonPress(MouseButtonPressedEvent& e) { return false; }
		bool defaultOnMouseButtonRelease(MouseButtonReleasedEvent& e) { return false; }
		bool defaultOnMouseMove(MouseMovedEvent& e) { return false; }
		bool defaultOnMouseScroll(MouseScrolledEvent& e) { return false; }
	};
}
