/** \file application.h
*/
#pragma once
#include "core/log.h"
#include "core/timer.h"
#include "events/windowsEvent.h"
#include "platform/GLFW/GLFWsystems.h"
#include "events/eventCases.h"
#include "events/eventHandler.h"
#include "independent/systems/inputPoller.h"
#include "platform/window/window.h"
#include "platform/GLFW/GLFWCodes.h"

namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor
		std::shared_ptr<Log> m_logSystem;	//!< Logger
		std::shared_ptr<Timer> m_timer;		//!< Timer
		std::shared_ptr<GLFWSystem> m_GLFWsys;	//!< GLFW initialise and terminate system
		std::shared_ptr<Window> m_window;	//!< Window

	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?
		int32_t width = 800;
		int32_t height = 600;
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		
		bool onClose(WindowCloseEvent& e); //!< On Close Event
		bool onResize(WindowResizeEvent& e); //!< On Resize Event
		bool onFocus(WindowFocusEvent& e);	//!< On Window Focus Event
		bool onLostFocus(WindowLostFocusEvent& e);	//!< On Window Lost Focus Event
		bool onKeyPressed(KeyPressedEvent& e);	//!< On Key Press Event
		bool onKeyReleased(KeyReleasedEvent& e);	//!< On Key Release Event
		bool onMouseButtonPress(MouseButtonPressedEvent& e);	//!< On Mouse Button Pressed Event 
		bool onMouseButtonRelease(MouseButtonReleasedEvent& e);	//!< On Mouse Button Released Event
		bool onMouseMove(MouseMovedEvent& e);	//!< On Mouse Moved Event 
		bool onMouseScroll(MouseScrolledEvent& e);	//!< On Mouse Wheel Scrolled Event
		
		void run(); //!< Main loop
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}