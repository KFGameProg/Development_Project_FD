/** \file application.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "core/application.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "rendering/agnosticIndexBuffer.h"

#include "platform/OpenGL/OpenGLVertexArray.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLTexture.h"

namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		m_handler = std::make_shared<InputHandler>();

		//!< Start Systems
		m_cam = new PerspectiveCamera();
		m_cam->attachHandler(m_win, m_handler);

		o_cube = new Cube();
		o_pyramid = new Pyramid();

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

		glClearColor(0.5f, 0.5f, 0.5f, 1.f);
	}

	Application::~Application()
	{
		// Stop GLFW System
		m_GLFWsys->stop();

		// Stop Logger
		m_logSystem->stop();
	}

#pragma region EVENTS
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
		//Log::info("Key Pressed event: key {0}, repeat {1}", e.getKey(), e.getRepeatCount());
		
		if (e.getKey() == NG_KEY_ESCAPE)
		{
			m_running = false;
		}

		return e.handled();
	}

	//!< On Key Release Event
	bool Application::onKeyReleased(KeyReleasedEvent& e)
	{
		e.handle(true);
		//Log::info("Key Released Event: key {0}", e.getKey());
		return e.handled();
	}

	//!< On Mouse Button Press Event
	bool Application::onMouseButtonPress(MouseButtonPressedEvent& e)
	{
		e.handle(true);
		Log::info("Mouse Pressed Event: button {0}", e.getButton());
		if (e.getButton() == NG_MOUSE_BUTTON_1)			//!< Left Mouse Button
		{
			//Log::warn("Left Mouse Button Pressed");
			//
		}
		if (e.getButton() == NG_MOUSE_BUTTON_2)			//!< Right Mouse Button
		{
			Log::warn("Right Mouse Button Pressed");
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
#pragma endregion

	void Application::run()
	{

#pragma region GL_BUFFERS
		//!< Buffer Setup
		//******************Cube Vertex Data***********************
		//std::shared_ptr<OpenGLVertexArray> cubeVAO;
		//std::shared_ptr<OpenGLVertexBuffer> cubeVBO;
		//std::shared_ptr<OpenGLIndexBuffer> cubeIBO;
		////std::shared_ptr<AgsIndexBuffer> cubeIBO;

		//cubeVAO.reset(new OpenGLVertexArray);

		//BufferLayout cubeBufLay = { ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 };
		//cubeVBO.reset(new OpenGLVertexBuffer(o_cube.getVertices(), o_cube.getVertexSize(), cubeBufLay));
		//
		//cubeIBO.reset(new OpenGLIndexBuffer(o_cube.getIndices(), o_cube.getIndexSize()));
		////cubeIBO.reset(AgsIndexBuffer::create(o_cube.getIndices(), o_cube.getIndexSize()));
		//
		//cubeVAO->addVertexBuffer(cubeVBO);
		//cubeVAO->setIndexBuffer(cubeIBO);
		

		uint32_t cubeVAO, cubeVBO, cubeIBO;

		glCreateVertexArrays(1, &cubeVAO);
		glBindVertexArray(cubeVAO);

		NormalMapper cubeNormal;
		cubeNormal.calculateTanAndBitan(o_cube->getVertices(), 192, o_cube->getIndices(), 36);
		std::vector<float> normalizedCubeVertices = cubeNormal.getUpdatedVertexData();

		glCreateBuffers(1, &cubeVBO);
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		//glBufferData(GL_ARRAY_BUFFER, o_cube->getVertexSize(), o_cube->getVertices(), GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, normalizedCubeVertices.size() * sizeof(GLfloat), normalizedCubeVertices.data(), GL_STATIC_DRAW);

		glCreateBuffers(1, &cubeIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, o_cube->getIndexSize(), o_cube->getIndices(), GL_STATIC_DRAW);

		//(pos 0 (position), 3 floats, not normalized, 14 floats between each data line, start at 0)
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0); // Position
		//(pos 1 (normal), 3 floats, not normalized, 14 floats between each data line, start at 3)
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float))); // Normal
		//(pos 2 (uv), 2 floats, not normalized, 14 floats between each data line, start at 6)
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float))); // UV Coords
		//(pos 3 (tangent), 3 floats, not normalized, 14 floats between each data line, start at 8)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float))); // Tangent
		//(pos 4 (bi-tangent), 3 floats, not normalized, 14 floats between each data line, start at 11)
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float))); // Bi-Tangent

		 //Unbind everyting
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


		//******************Pyramid Vertex Data***********************
		//std::shared_ptr<OpenGLVertexArray> pyramidVAO;
		//std::shared_ptr<OpenGLVertexBuffer> pyramidVBO;
		//std::shared_ptr<OpenGLIndexBuffer> pyramidIBO;
		////std::shared_ptr<AgsIndexBuffer> pyramidIBO;

		//pyramidVAO.reset(new OpenGLVertexArray);

		//BufferLayout pyramidBufLay = { ShaderDataType::Float3, ShaderDataType::Float3 };
		//pyramidVBO.reset(new OpenGLVertexBuffer(o_pyramid.getVertices(), o_pyramid.getVertexSize(), pyramidBufLay));

		//pyramidIBO.reset(new OpenGLIndexBuffer(o_pyramid.getIndices(), o_pyramid.getIndexSize()));
		////pyramidIBO.reset(AgsIndexBuffer::create(o_pyramid.getIndices(), o_pyramid.getIndexSize()));

		//pyramidVAO->addVertexBuffer(pyramidVBO);
		//pyramidVAO->setIndexBuffer(pyramidIBO);

		

		uint32_t pyramidVAO, pyramidVBO, pyramidIBO;

		glCreateVertexArrays(1, &pyramidVAO);
		glBindVertexArray(pyramidVAO);

		glCreateBuffers(1, &pyramidVBO);
		glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
		glBufferData(GL_ARRAY_BUFFER, o_pyramid->getVertexSize(), o_pyramid->getVertices(), GL_STATIC_DRAW);

		glCreateBuffers(1, &pyramidIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, o_pyramid->getIndexSize(), o_pyramid->getIndices(), GL_STATIC_DRAW);

		//(pos 0 (position), 3 floats, not normalized, 6 float between each data line, start at 0)
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Position
		 //(pos 1 (normal), 3 floats, not normalized, 8 float between each data line, start at 3)
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Normal
		 //(pos 2 (uv), 2 floats, not normalized, 8 float between each data line, start at 6)
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // UV Coords
		//(pos 3 (tangent), 3 floats, not normalized, 14 floats between each data line, start at 8)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float))); // Tangent
		//(pos 4 (bi-tangent), 3 floats, not normalized, 14 floats between each data line, start at 11)
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float))); // Bi-Tangent

		 //Unbind everyting
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#pragma endregion

#pragma region SHADERS

		std::shared_ptr<OpenGLShader> TPShader;
		TPShader.reset(new OpenGLShader("..\\assets\\shaders\\texturePhong.vert", "..\\assets\\shaders\\texturePhong.frag"));

#pragma endregion 

#pragma region TEXTURES

		std::shared_ptr<OpenGLTexture> plainWhiteTex;
		unsigned char whitePx[4] = { 255,255,255,255 };
		plainWhiteTex.reset(new OpenGLTexture(1, 1, 4, whitePx));

#pragma endregion

#pragma region MATERIALS



#pragma endregion

		glm::mat4 view;
		glm::mat4 projection = m_cam->getProjectionMatrix();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -2.f));

		//!< Running window operations

		float timestep = 0.f;
		float accumulatedTime = 0.f;

		glEnable(GL_DEPTH_TEST);

		while (m_running)
		{
			timestep = m_timer->elaspedTime();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_cam->update(timestep);
			m_camPos = m_cam->getPosition();
			m_camFront = m_cam->getFront();

			view = glm::lookAt(m_cam->getPosition(), glm::vec3{ 0.f }, WORLD_UP);
			view = m_cam->getViewMatrix();
			
			m_handler->MouseMove(InputPoller::getMouseX(), InputPoller::getMouseY());
			
			//**************************OpenGL Draw**********************************
			glUseProgram(TPShader->getID());

			glBindTexture(GL_TEXTURE_2D, plainWhiteTex->getID());
			
			// Pyramid
			/*glBindVertexArray(pyramidVAO->getID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO->getID());*/
			glBindVertexArray(pyramidVAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO);

			TPShader->uploadMat4("u_view", view);
			TPShader->uploadMat4("u_projection", projection);
			TPShader->uploadFloat3("u_lightColour", { 1.f, 1.f, 1.f });
			TPShader->uploadFloat3("u_lightPos", { 1.f, 4.f, 6.f });
			TPShader->uploadFloat3("u_viewPos", { 0.f, 0.f, 0.f });
			TPShader->uploadMat4("u_model", model);
			TPShader->uploadFloat4("u_tint", { 0.4f, 0.7f, 0.3f, 1.f });
			TPShader->uploadInt("u_texData", 0);

			//glDrawElements(GL_TRIANGLES, 3 * 6, GL_UNSIGNED_INT, nullptr);

			// Cube
			/*glBindVertexArray(cubeVAO->getID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO->getID());*/
			glBindVertexArray(cubeVAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO);

			//glBindTexture(GL_TEXTURE_2D, ->getID());

			TPShader->uploadMat4("u_model", model);
			TPShader->uploadInt("u_texData", 0);

			glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, nullptr);
			//glDrawElements(GL_LINES, 6 * 6, GL_UNSIGNED_INT, nullptr);

			m_window->onUpdate(timestep);

			m_timer->reset();
		};
		glDisable(GL_DEPTH_TEST);

		Log::info("Exiting");
	}

}
