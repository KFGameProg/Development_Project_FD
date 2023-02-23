/** \file   perspectiveCamera.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "systems/camera/perspectiveCamera.h"

namespace Engine
{
	PerspectiveCamera::PerspectiveCamera(glm::vec3 pos)
	{
		m_zoom = 45.0;
		m_yaw = -90.0f;
		m_pitch = 0.0f;
		m_pitchContrain = 89.0f;
		m_speed = 50.f;
		updateCameraVectors();
	}

	glm::mat4 PerspectiveCamera::getViewMatrix()
	{
		return glm::lookAt(m_position, m_position + m_front, WORLD_UP);
	}

	glm::mat4 PerspectiveCamera::getProjectionMatrix()
	{
		return glm::perspective(glm::radians(m_zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, m_nearP, m_farP);
	}

	void PerspectiveCamera::attachHandler(GLFWwindow* W, std::shared_ptr<InputHandler> H)
	{
		m_window = W;
		m_handler = H;
	}

	void PerspectiveCamera::update(float dt)
	{
		float velocity = m_speed * dt;
		bool mouseMove = m_handler->mouseHasMoved();

		if (InputPoller::keyPressed(NG_KEY_W)) {
			m_position += m_front * velocity;
		}
		if (InputPoller::keyPressed(NG_KEY_S)) {
			m_position -= m_front * velocity;
		}
		if (InputPoller::keyPressed(NG_KEY_A)) {
			m_position -= m_right * velocity;
		}
		if (InputPoller::keyPressed(NG_KEY_D)) {
			m_position += m_right * velocity;
		}
		if (InputPoller::keyPressed(NG_KEY_SPACE)) {
			m_position += m_up * velocity;
		}
		if (InputPoller::keyPressed(NG_KEY_LEFT_CONTROL)) {
			m_position -= m_up * velocity;
		}

		look(m_handler->getMouseDeltaX(), m_handler->getMouseDeltaY());
		zoom(m_handler->getMouseScrollY());
		
		m_handler->endFrame();
	}
	
	void PerspectiveCamera::updateCameraVectors()
	{
		m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front.y = sin(glm::radians(m_pitch));
		m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front = glm::normalize(m_front);
		//re-calculate the Right and Up vector
		m_right = glm::normalize(glm::cross(m_front, WORLD_UP));  // Normalize the vectors, because their length gets closer to zero the more you look up or down which results in slower movement.
		m_up = glm::normalize(glm::cross(m_right, m_front));
	}

	void PerspectiveCamera::zoom(float offsetY)
	{
		float min = 20.0f;
		float max = 45.0f;

		if (m_zoom >= min && m_zoom <= max) m_zoom -= offsetY;
		if (m_zoom <= min) m_zoom = min;
		if (m_zoom >= max) m_zoom = max;
	}

	void PerspectiveCamera::look(float offsetX, float offsetY)
	{
		offsetX *= m_sensitivity;
		offsetY *= m_sensitivity;

		m_yaw += offsetX;
		m_pitch += offsetY;

		std::clamp(m_pitch, -m_pitchContrain, m_pitchContrain);
		/*if (m_pitch > m_pitchContrain) m_pitch = m_pitchContrain;
		if (m_pitch < -m_pitchContrain) m_pitch = -m_pitchContrain;*/

		updateCameraVectors();
	}
}
