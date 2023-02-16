/** \file   camera.h */
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "events/eventHandler.h"
#include "systems/inputPoller.h"
#include "systems/properties.h"
#include "platform/GLFW/GLFWCodes.h"

namespace Engine {

	class Camera
	{
	public:
		Camera(glm::vec3 pos = glm::vec3(0, 0, 10)) :
			m_position(pos),
			m_front(glm::vec3(0.f,0.f,-1.f)),
			m_right(glm::vec3(-1.f,0.f,0.f)),
			m_up(glm::vec3(0.f,-1.f,0.f)),
			m_zoom(45.f),
			m_yaw(-90.0f),
			m_pitch(0.0),
			m_nearP(0.1f),
			m_farP(500.0f)
		{};

		// Virtual view and projection matrices
		virtual glm::mat4 getViewMatrix() { return glm::lookAt(m_position, m_position + m_front, WORLD_UP); }
		virtual glm::mat4 getProjectionMatrix() { return glm::perspective(glm::radians(m_zoom), 1.0f, 0.1f, 20.0f); }

		virtual glm::vec3& getPosition() { return m_position; }
		virtual float getFOV() { return glm::radians(m_zoom); }
		virtual float& getNearPlane() { return m_nearP; }
		virtual float& getFarPlane() { return m_farP; }
		virtual glm::vec3& getFront() { return  m_front; }
		virtual glm::vec3& getUp() { return  m_up; }
		virtual glm::vec3& getRight() { return  m_right; }

		// Control
		virtual void update(float dt) {};
		virtual void attachHandler(std::shared_ptr<Window> W, std::shared_ptr<InputPoller> H) {};

	protected:
		glm::vec3 m_position;
		glm::vec3 m_front;
		glm::vec3 m_right;     
		glm::vec3 m_up;        

		float m_zoom;
		float m_yaw;
		float m_pitch;
		float m_nearP;
		float m_farP;
	};
}