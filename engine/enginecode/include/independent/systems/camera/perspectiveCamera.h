/** \file   perspectiveCamera.h */
#pragma once
#include "platform/window/window.h"
#include "systems/camera/camera.h"
#include "events/keyEvent.h"

namespace Engine
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(glm::vec3 pos = glm::vec3(0.f, 1.f, 10.f));

		glm::mat4 getViewMatrix() override;
		glm::mat4 getProjectionMatrix() override;
		void update(float dt) override;
		void attachHandler(std::shared_ptr<Window> W, std::shared_ptr<InputPoller> H) override;

	private:
		float m_speed;         // camera speed
		float m_sensitivity;   // mouse sensitivity
		float m_pitchContrain; // keeps pitch between 90 degrees to avoid screen flips

		std::shared_ptr<Window> m_window;
		std::shared_ptr<InputPoller> m_handler;

		void updateCameraVectors();
		void zoom(float offsetY);
		void look(float offsetX, float offsetY);  // mouse scroll
	};
}
