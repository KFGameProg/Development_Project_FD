/** \file application.h */
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
#include "systems/camera/perspectiveCamera.h"
#include "independent/rendering/normalMapper.h"
#include "independent/rendering/objects/cube.h"
#include "independent/rendering/objects/pyramid.h"
#include "independent/rendering/objects/sphere.h"
#include "independent/rendering/Utilities/grid.h"

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
		std::shared_ptr<Grid> m_grid;
		GLFWwindow* m_win;
		std::shared_ptr<InputHandler> m_handler;
		PerspectiveCamera* m_cam;
		Cube* o_cube;
		Pyramid* o_pyramid;
		//Sphere* o_sphere;
		std::shared_ptr<Sphere> o_sphere;

	private:
		static Application* s_instance; //!< Singleton instance of the application
		bool m_running = true; //!< Is the application running?
		int32_t width = SCR_WIDTH;
		int32_t height = SCR_HEIGHT;
		// Buffers
		uint32_t gridVAO, gridVBO, cubeVAO, cubeVBO, cubeIBO, pyramidVAO, pyramidVBO, pyramidIBO, sphereVAO, sphereVBO, sphereIBO;
		// Transform
		glm::mat4 view, projection, model[5];
		// Object
		glm::vec3 cubeCol, pyramidCol;
		glm::vec4 tint;
		// Light
		glm::vec3 lightCol, lightPos;
		// Camera
		glm::vec3 camPos, camFront;

		// Textures
		unsigned int m_diffTex, m_normMap, m_specMap;	// Metal Sheet

		// Toggles
		bool ambient = true;
		bool diffuse = true;
		bool specular = true;
		bool texture = true;
		bool normal = true;
		bool bpfragOutput = true;
		bool pbrfragOutput = true;

		bool Ambient() { return ambient; }
		bool Diffuse() { return diffuse; }
		bool Specular() { return specular; }
		bool Texture() { return texture; }
		bool Normal() { return normal; }
		bool bpFragOutput() { return bpfragOutput; }
		bool pbrFragOutput() { return pbrfragOutput; }

		void Ambient(bool x) { ambient = x; }
		void Diffuse(bool x) { diffuse = x; }
		void Specular(bool x) { specular = x; }
		void Texture(bool x) { texture = x; }
		void Normal(bool x) { normal = x; }
		void bpFragOutput(bool x) { bpfragOutput = x; }
		void pbrFragOutput(bool x) { pbrfragOutput = x; }

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

		void createBuffers();
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}