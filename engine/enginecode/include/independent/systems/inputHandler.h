/** \file   inputHandler.h */
#pragma once
#include <vector>
#include <GLFW/glfw3.h>
#include <iostream>
#include <numeric>

#include "core/log.h"
#include "platform/GLFW/GLFWCodes.h"
#include "events/eventHandler.h"
#include "inputPoller.h"
#include "properties.h"

#define numOfMouseButtons 2
#define numKeys 350

namespace Engine
{
    class InputHandler
    {
    public:
        InputHandler() {};
        ~InputHandler() {};
        void KeyPress(int32_t key, int32_t scancode, int32_t action, int32_t mods);
        void MouseScroll(float xOffset, float yOffset);
        void MouseMove(float xPos, float yPos);
        void MouseClick(int32_t button, int32_t action, int32_t mods);
        void endFrame();

        inline float getMousePosX()    { return m_lastX; }
        inline float getMousePosY()    { return m_lastY; }
        inline float getMouseDeltaX()  { return m_mouseDeltaX; }
        inline float getMouseDeltaY()  { return m_mouseDeltaY; }
        inline float getMouseScrollX() { return m_Xscroll; }
        inline float getMouseScrollY() { return m_Yscroll; }
        inline bool  isRightClicked()  { return m_mouseButtonPressed[1]; }
        inline bool  isLeftClicked()   { return m_mouseButtonPressed[0]; }
        inline bool  isDragging()      { return m_isDragging && m_mouseButtonPressed[1]; }
        inline bool  mouseHasMoved()   { return (m_mouseDeltaX != 0.0 && m_mouseDeltaY != 0.0); }

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

        bool keyHasBeenPressed();
        bool isKeyPressed(int keyCode) { return m_keysPressed[keyCode]; }
        void processedKey(int keyCode) { m_keysPressed[keyCode] = false; }

    private:
        bool m_running = true;
        float m_Xscroll = 0.0;
        float m_Yscroll = 0.0;
        float m_Xpos = SCR_WIDTH / 2;
        float m_Ypos = SCR_HEIGHT / 2;
        float m_mouseDeltaX = 0.0f;
        float m_mouseDeltaY = 0.0f;
        float m_lastX = 0.0f;
        float m_lastY = 0.0f;
        bool m_mouseButtonPressed[numOfMouseButtons] = { 0 };
        bool m_isDragging = false;
        bool m_firstPress = true;

        bool m_keysPressed[numKeys] = { 0 };

    };
}
