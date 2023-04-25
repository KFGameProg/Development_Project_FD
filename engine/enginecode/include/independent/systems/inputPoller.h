/** \file   inputPoller.h */
#pragma once
#include <glm/glm.hpp>

namespace Engine {

	/**
	 * \class InputPoller
	 * \brief Class to capture window related user data
	 */
	class InputPoller
	{
	public:
		static bool keyPressed(int32_t key); //!< Whether specified key is called
		static bool mouseButtonPressed(int32_t button); //!< Whether mouse button is pressed 
		static bool mouseButtonReleased(int32_t button); //!< Whether mouse button is released 
		static glm::vec2 getMousePos(); //!< function to determine mouse position
		static void setNativeWindow(void* nativeWindow);
		inline static float getMouseX() { return getMousePos().x; } //!< Returns x position of mouse
		inline static float getMouseY() { return getMousePos().y; } //!< Returns y position of mouse
	};
}