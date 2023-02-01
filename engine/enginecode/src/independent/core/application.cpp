/** \file application.cpp
*/

#include "engine_pch.h"
#include <glad/glad.h>
#include "core/application.h"

namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}
		//!< Start Systems

		//!< Start Log
		m_logSystem.reset(new Log);
		m_logSystem->start();

		//Start GLFW System
		m_GLFWsys.reset(new GLFWSystem);
		m_GLFWsys->start();

		m_timer.reset(new ChronoTimer);
		m_timer->start();

		WindowProperties properties("Hey you.. you're finally awake", width, height, false, true);

		m_window.reset(Window::create(properties));

		m_window->getEventHandler().setOnCloseCallBack(std::bind(&Application::onClose, this, std::placeholders::_1));
		m_window->getEventHandler().setOnResizeCallBack(std::bind(&Application::onResize, this, std::placeholders::_1));
		m_window->getEventHandler().setOnFocusCallBack(std::bind(&Application::onFocus, this, std::placeholders::_1));
		m_window->getEventHandler().setOnLostFocusCallBack(std::bind(&Application::onLostFocus, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyPressedCallBack(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyReleasedCallBack(std::bind(&Application::onKeyReleased, this, std::placeholders::_1));
		m_window->getEventHandler().setOnButtonPressedCallBack(std::bind(&Application::onMouseButtonPress, this, std::placeholders::_1));
		m_window->getEventHandler().setOnButtonReleasedCallBack(std::bind(&Application::onMouseButtonRelease, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseMovedCallBack(std::bind(&Application::onMouseMove, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseWheelCallBack(std::bind(&Application::onMouseScroll, this, std::placeholders::_1));

		InputPoller::setNativeWindow(m_window->getNativeWindow());
	}

	Application::~Application()
	{
		// Stop GLFW System
		m_GLFWsys->stop();

		// Stop Logger
		m_logSystem->stop();
	}

	//!< On Close Event 
	bool Application::onClose(WindowCloseEvent& e)
	{
		e.handle(true);
		Log::info("Closing Application");
		m_running = false;
		return e.handled();
	}

	//!< On Resize Event
	bool Application::onResize(WindowResizeEvent& e)
	{
		e.handle(true);
		auto& size = e.getSize();
		Log::info("Resize Window to {0}x{1}", size.x, size.y);
		return e.handled();
	}

	//!< On Window Focus Event
	bool Application::onFocus(WindowFocusEvent& e)
	{
		e.handle(true);
		Log::info("Window Focused");
		return e.handled();
	}

	//!< On Window Lost Focus Event
	bool Application::onLostFocus(WindowLostFocusEvent& e)
	{
		e.handle(true);
		Log::info("Lost Window Focus");
		return e.handled();
	}

	//!< On Key Press Event
	bool Application::onKeyPressed(KeyPressedEvent& e)
	{
		e.handle(true);
		Log::info("Key Pressed event: key {0}, repeat {1}", e.getKey(), e.getRepeatCount());
		if (e.getKey() == NG_KEY_SPACE)			//!< Space Key
		{
			width = 800, height = 600;
			Log::debug("SPACEBAR");
		}

		if (e.getKey() == NG_KEY_W)				//!< W Key
		{
			height += 100;
			Log::debug("W Pressed");
		}
		else if (e.getKey() == NG_KEY_S)		//!< S Key
		{
			height -= 100;
			Log::debug("S Pressed");
		}
		
		if (e.getKey() == NG_KEY_D)				//!< D Key
		{
			width += 100;
			Log::debug("D Pressed");
		}
		else if (e.getKey() == NG_KEY_A)		//!< A Key
		{
			width -= 100;
			Log::debug("A Pressed");
		}

		return e.handled();
	}

	//!< On Key Release Event
	bool Application::onKeyReleased(KeyReleasedEvent& e)
	{
		e.handle(true);
		Log::info("Key Released Event: key {0}, repeat {1}", e.getKey());
		return e.handled();
	}

	//!< On Mouse Button Press Event
	bool Application::onMouseButtonPress(MouseButtonPressedEvent& e)
	{
		e.handle(true);
		Log::info("Mouse Pressed Event: button {0}", e.getButton());
		if (e.getButton() == NG_MOUSE_BUTTON_1)			//!< Left Mouse Button
		{
			Log::warn("Left Mouse Button Pressed");
			glClearColor(1.f, 1.f, 1.f, 1.f);
		}
		if (e.getButton() == NG_MOUSE_BUTTON_2)			//!< Right Mouse Button
		{
			Log::warn("Right Mouse Button Pressed");
			glClearColor(0.f, 0.f, 0.f, 1.f);
		}
		if (e.getButton() == NG_MOUSE_BUTTON_3)			//!< Middle Mouse Button
		{
			Log::warn("Middle Mouse Button Pressed");
			Log::error("Current Mouse Position: ({0}, {1})", InputPoller::getMouseX(), InputPoller::getMouseY());
		}
		return e.handled();
	}

	//!< On Mouse Button Release Event
	bool Application::onMouseButtonRelease(MouseButtonReleasedEvent& e)
	{
		e.handle(true);
		Log::info("Mouse Released Event: button {0}", e.getButton());
		return e.handled();
	}

	//!< On Mouse Move Event
	bool Application::onMouseMove(MouseMovedEvent& e)
	{
		e.handle(true);
		auto& pos = e.getPos();
		//Log::info("Mouse Moved Event: ({0}, {1})", pos.x, pos.y);
		return e.handled();
	}

	//!< On Mouse Scroll Event
	bool Application::onMouseScroll(MouseScrolledEvent& e)
	{
		e.handle(true);
		Log::info("Mouse Wheel Event: {0}", e.getOffsetY());
		return e.handled();
	}


	void Application::run()
	{
		//!< Running window operations

		float timestep = 0.f;
		float accumulatedTime = 0.f;

		glEnable(GL_DEPTH_TEST);

		while (m_running)
		{
			timestep = m_timer->elaspedTime();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_window->onUpdate(timestep);

			m_timer->reset();
		};

		Log::info("Exiting");
	}

}
