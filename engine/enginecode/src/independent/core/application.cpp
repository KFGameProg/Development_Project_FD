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

		m_grid = std::make_shared<Grid>();
		o_sphere = std::make_shared<Sphere>();

		o_cube = new Cube();
		o_pyramid = new Pyramid();
		//o_sphere = new Sphere();

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

		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
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
		
		// Close on Esc press
		if (e.getKey() == NG_KEY_ESCAPE) {
			m_running = false;
		}

		//// Toggle Sets
		//if(e.getKey() == NG_KEY_1) {
		//	Ambient(!(Ambient()));
		//}
		//if (e.getKey() == NG_KEY_2) {
		//	Diffuse(!(Diffuse()));
		//}
		//if (e.getKey() == NG_KEY_3) {
		//	Specular(!(Specular()));
		//}
		//if (e.getKey() == NG_KEY_BACKSPACE) {
		//	Normal(!(Normal()));
		//}
		//if (e.getKey() == NG_KEY_MINUS) {
		//	bpFragOutput(!(bpFragOutput()));
		//}
		//if (e.getKey() == NG_KEY_ENTER) {
		//	Texture(!(Texture()));
		//}
		//if (e.getKey() == NG_KEY_EQUAL) {
		//	bpFragOutput(!(pbrFragOutput()));
		//}

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
			Log::warn("Left Mouse Button Pressed");
		}
		if (e.getButton() == NG_MOUSE_BUTTON_2)			//!< Right Mouse Button
		{
			Log::warn("Right Mouse Button Pressed");
		}
		if (e.getButton() == NG_MOUSE_BUTTON_3)			//!< Middle Mouse Button
		{
			Log::warn("Middle Mouse Button Pressed");
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
		createBuffers();

#pragma region SHADERS

		std::shared_ptr<OpenGLShader> BPShader;
		BPShader.reset(new OpenGLShader("..\\assets\\shaders\\lightingShader.vert", "..\\assets\\shaders\\lightingShader.frag"));

		std::shared_ptr<OpenGLShader> PBRShader;
		PBRShader.reset(new OpenGLShader("..\\assets\\shaders\\PBRShader.vert", "..\\assets\\shaders\\PBRShader.frag"));

		std::shared_ptr<OpenGLShader> TessShader;
		TessShader.reset(new OpenGLShader("..\\assets\\shaders\\tessVertShader.vert", "..\\assets\\shaders\\tessFragShader.frag", "..\\assets\\shaders\\Norms.gs", "..\\assets\\shaders\\tessCtrl.tcs", "..\\assets\\shaders\\tessEval.tes"));
		
		std::shared_ptr<OpenGLShader> TPShader;
		TPShader.reset(new OpenGLShader("..\\assets\\shaders\\texturePhong.vert", "..\\assets\\shaders\\texturePhong.frag"));

#pragma endregion 

#pragma region TEXTURES

		//!< White Texture
		std::shared_ptr<OpenGLTexture> plainWhiteTex;
		unsigned char whitePx[4] = { 255,255,255,255 };
		plainWhiteTex.reset(new OpenGLTexture(1, 1, 4, whitePx));

		//!< Metal Plate
		std::shared_ptr<OpenGLTexture> metalDiffuseTex;
		metalDiffuseTex.reset(new OpenGLTexture("..\\assets\\textures\\metalPlate\\diffuse.jpg"));
		std::shared_ptr<OpenGLTexture> metalNormalTex;
		metalNormalTex.reset(new OpenGLTexture("..\\assets\\textures\\metalPlate\\normal.jpg"));
		std::shared_ptr<OpenGLTexture> metalSpecularTex;
		metalSpecularTex.reset(new OpenGLTexture("..\\assets\\textures\\metalPlate\\specular.jpg"));
		//!< Rusted Metal Floor 
		std::shared_ptr<OpenGLTexture> rustDiffuseTex;
		rustDiffuseTex.reset(new OpenGLTexture("..\\assets\\textures\\metalRust\\diffuse.jpg"));
		std::shared_ptr<OpenGLTexture> rustNormalTex;
		rustNormalTex.reset(new OpenGLTexture("..\\assets\\textures\\metalRust\\normal.jpg"));
		std::shared_ptr<OpenGLTexture> rustSpecularTex;
		rustSpecularTex.reset(new OpenGLTexture("..\\assets\\textures\\metalRust\\specular.jpg"));
		//!< Rusted Iron
		std::shared_ptr<OpenGLTexture> ironDiffuseTex;
		ironDiffuseTex.reset(new OpenGLTexture("..\\assets\\textures\\rustedIron\\BaseColour.png"));
		std::shared_ptr<OpenGLTexture> ironMetallicTex;
		ironMetallicTex.reset(new OpenGLTexture("..\\assets\\textures\\rustedIron\\Metallic.png"));
		std::shared_ptr<OpenGLTexture> ironRoughnessTex;
		ironRoughnessTex.reset(new OpenGLTexture("..\\assets\\textures\\rustedIron\\Roughness.png"));
		std::shared_ptr<OpenGLTexture> ironNormalTex;
		ironNormalTex.reset(new OpenGLTexture("..\\assets\\textures\\rustedIron\\Normal.png"));
		//!< Stylized Stone
		std::shared_ptr<OpenGLTexture> stoneAmbOccTex;
		stoneAmbOccTex.reset(new OpenGLTexture("..\\assets\\textures\\stylizedStoneFloor\\ambientOcclusion.jpg"));
		std::shared_ptr<OpenGLTexture> stoneDiffuseTex;
		stoneDiffuseTex.reset(new OpenGLTexture("..\\assets\\textures\\stylizedStoneFloor\\diffuse.jpg"));
		std::shared_ptr<OpenGLTexture> stoneDisplaceTex;
		stoneDisplaceTex.reset(new OpenGLTexture("..\\assets\\textures\\stylizedStoneFloor\\displacement.png"));
		std::shared_ptr<OpenGLTexture> stoneNormalTex;
		stoneNormalTex.reset(new OpenGLTexture("..\\assets\\textures\\stylizedStoneFloor\\normal.jpg"));
		std::shared_ptr<OpenGLTexture> stoneRoughTex;
		stoneRoughTex.reset(new OpenGLTexture("..\\assets\\textures\\stylizedStoneFloor\\roughness.jpg"));
		std::shared_ptr<OpenGLTexture> stoneSpecularTex;
		stoneSpecularTex.reset(new OpenGLTexture("..\\assets\\textures\\stylizedStoneFloor\\specular.jpg"));

#pragma endregion

#pragma region MATERIALS

		glm::vec3 grey = glm::vec3(0.7f);
		glm::vec3 red = glm::vec3(0.5f, 0.f, 0.f);
		glm::vec3 green = glm::vec3(0.f, 0.5f, 0.f);
		glm::vec3 blue = glm::vec3(0.f, 0.f, 0.5f);
		glm::vec3 purple = glm::vec3(0.5f, 0.f, 1.f);
		glm::vec3 cyan = glm::vec3(0.1f, 0.70f, 0.75f);

#pragma endregion

//**********************************Scene Attributes**********************************
		// Transforms
		projection = m_cam->getProjectionMatrix();
		model[0] = glm::mat4(1.f);
		model[1] = glm::translate(model[0], glm::vec3(-15.f, 0.f, -15.f));
		model[2] = glm::translate(model[0], glm::vec3(-2.f, 1.f, -2.f));
		model[3] = glm::translate(model[0], glm::vec3(2.f, 1.f, -2.f));
		// Object
		cubeCol = glm::vec3(1.0, 0.0, 1.0);
		pyramidCol = glm::vec3(0.f, 0.f, 0.f);
		tint = glm::vec4(0.4f, 0.7f, 0.3f, 1.f);
		// Light
		lightCol = glm::vec3(1.f);
		lightPos = glm::vec3(0.f, -1.f, 0.f);
		glm::vec3 mlightCol = { glm::vec3(23.47f, 21.31f, 20.79) };
		// Sphere Placements
		unsigned int nrRows = 10;
		unsigned int nrColumns = 10;
		float spacing = 0.5;
		//!< Running window operations

		float timestep = 0.f;
		float accumulatedTime = 0.f;

		glEnable(GL_DEPTH_TEST);

		while (m_running)
		{
			timestep = m_timer->elaspedTime();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_cam->update(timestep);
			camPos = m_cam->getPosition();
			camFront = m_cam->getFront();

			view = glm::lookAt(m_cam->getPosition(), glm::vec3{ 0.f }, WORLD_UP);
			view = m_cam->getViewMatrix();
			
			m_handler->MouseMove(InputPoller::getMouseX(), InputPoller::getMouseY());
			m_handler->MouseScroll(m_handler->getMouseScrollX(), m_handler->getMouseScrollY());

			//**************************Toggles******************************
			/*BPShader->uploadBool("tAmbient", Ambient());
			BPShader->uploadBool("tDiffuse", Diffuse());
			BPShader->uploadBool("tSpecular", Specular());
			BPShader->uploadBool("tNorm", Normal());
			BPShader->uploadBool("tFragOut", bpFragOutput());
			PBRShader->uploadBool("tTexture", Texture());
			PBRShader->uploadBool("tFragOut", pbrFragOutput());*/

			//**************************OpenGL Draw**********************************
			glUseProgram(TessShader->getID());

			// Grid
			glBindVertexArray(gridVAO);

			TessShader->uploadMat4("model", model[1]);
			TessShader->uploadMat4("view", view);
			TessShader->uploadMat4("projection", projection);
			TessShader->uploadFloat3("camPos", camPos);

			/*glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			glDrawArrays(GL_PATCHES, 0, m_grid->getSize());*/

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawArrays(GL_PATCHES, 0, m_grid->getSize());

			glUseProgram(BPShader->getID());
			
			// Cube
			BPShader->uploadInt("diffuseTexture", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, stoneDiffuseTex->getID());
			BPShader->uploadInt("specularMap", 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, stoneSpecularTex->getID());
			BPShader->uploadInt("normalMap", 2);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, stoneNormalTex->getID());

			glBindVertexArray(cubeVAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO);

			BPShader->uploadMat4("model", model[2]);
			BPShader->uploadMat4("view", view);
			BPShader->uploadMat4("projection", projection);
			BPShader->uploadFloat3("objCol", cubeCol);
			BPShader->uploadFloat3("dirLightCol", lightCol);
			BPShader->uploadFloat3("dirLightPos", lightPos);
			BPShader->uploadFloat4("tint", tint);
			BPShader->uploadFloat3("camPos", camPos);

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, nullptr);

			glUseProgram(BPShader->getID());

			//Pyramid
			BPShader->uploadInt("diffuseTexture", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, metalDiffuseTex->getID());
			BPShader->uploadInt("specularMap", 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, metalSpecularTex->getID());
			BPShader->uploadInt("normalMap", 2);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, metalNormalTex->getID());
			
			glBindVertexArray(pyramidVAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO);
			
			BPShader->uploadMat4("model", model[3]);
			BPShader->uploadFloat3("objCol", pyramidCol);

			glDrawElements(GL_TRIANGLES, 3 * 6, GL_UNSIGNED_INT, nullptr);

			glUseProgram(PBRShader->getID());

			//Spheres
			PBRShader->uploadInt("albedoMap", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, ironDiffuseTex->getID());
			PBRShader->uploadInt("metallicMap", 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, ironMetallicTex->getID());
			PBRShader->uploadInt("roughnessMap", 2);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, ironRoughnessTex->getID());
			PBRShader->uploadInt("normalMap", 4);
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, ironNormalTex->getID());

			PBRShader->uploadMat4("view", view);
			PBRShader->uploadMat4("projection", projection);
			PBRShader->uploadFloat4("tint", tint);
			PBRShader->uploadFloat3("albedo", cyan);
			PBRShader->uploadFloat("ambOccul", 0.5f);
			PBRShader->uploadFloat3("camPos", camPos);
			PBRShader->uploadFloat3("lightPos", glm::vec3(0.f, 4.f, 0.f));
			PBRShader->uploadFloat3("lightCol", mlightCol);

			float rough = 0.f;
			float metal = 0.f;
			for (int col = 0; col < nrColumns; ++col)
			{
				for (int row = 0; row < nrRows; ++row)
				{
					model[4] = glm::translate(model[0], glm::vec3(-1.f, 1.f, -6.f));
					model[4] = glm::translate(model[4], glm::vec3(
						(float)(row - (nrRows / 2)) * spacing,
						(float)(col - (nrColumns / 2)) * spacing,
						0.0f
					));

					PBRShader->uploadMat4("model", model[4]);
					PBRShader->uploadFloat("roughness", rough);
					PBRShader->uploadFloat("metallic", metal);
					
					glBindVertexArray(sphereVAO);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereIBO);

					glDrawElements(GL_TRIANGLE_STRIP, o_sphere->getIndexSize(), GL_UNSIGNED_INT, nullptr);

					rough = rough + 0.1f;
				}
				rough = 0.f;
				metal = metal + 0.2f;
			}
			
			m_window->onUpdate(timestep);

			m_timer->reset();
		};
		glDisable(GL_DEPTH_TEST);

		glDeleteVertexArrays(1, &gridVAO);
		glDeleteBuffers(1, &gridVBO);

		glDeleteVertexArrays(1, &cubeVAO);
		glDeleteBuffers(1, &cubeVBO);
		glDeleteBuffers(1, &cubeIBO);

		glDeleteVertexArrays(1, &pyramidVAO);
		glDeleteBuffers(1, &pyramidVBO);
		glDeleteBuffers(1, &pyramidIBO);

		Log::info("Exiting");
	}

	void Application::createBuffers()
	{
		//*****************************************************Grid Vertex Data*******************************************************
		glCreateVertexArrays(1, &gridVAO);
		glCreateBuffers(1, &gridVBO);
		glBindVertexArray(gridVAO);
		glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
		glBufferData(GL_ARRAY_BUFFER, (m_grid->getSize() * sizeof(GLfloat)), m_grid->getData(), GL_STATIC_DRAW);

		//xyz
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//texture
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//*****************************************************Cube Vertex Data*******************************************************
		glCreateVertexArrays(1, &cubeVAO);
		glBindVertexArray(cubeVAO);

		NormalMapper cubeNormal;
		cubeNormal.calculateTanAndBitan(o_cube->getVertices(), 192, o_cube->getIndices(), 36);
		std::vector<float> normalizedCubeVertices = cubeNormal.getUpdatedVertexData();

		glCreateBuffers(1, &cubeVBO);
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
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

		//*****************************************************Pyramid Vertex Data*******************************************************
		glCreateVertexArrays(1, &pyramidVAO);
		glBindVertexArray(pyramidVAO);

		NormalMapper pyramidNormal;
		pyramidNormal.calculateTanAndBitan(o_pyramid->getVertices(), 128, o_pyramid->getIndices(), 18);
		std::vector<float> normalizedPyramidVertices = pyramidNormal.getUpdatedVertexData();

		glCreateBuffers(1, &pyramidVBO);
		glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
		glBufferData(GL_ARRAY_BUFFER, normalizedPyramidVertices.size() * sizeof(GLfloat), normalizedPyramidVertices.data(), GL_STATIC_DRAW);

		glCreateBuffers(1, &pyramidIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, o_pyramid->getIndexSize(), o_pyramid->getIndices(), GL_STATIC_DRAW);

		//(pos 0 (position), 3 floats, not normalized, 14 float between each data line, start at 0)
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0); // Position
		 //(pos 1 (normal), 3 floats, not normalized, 14 float between each data line, start at 3)
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float))); // Normal
		 //(pos 2 (uv), 2 floats, not normalized, 14 float between each data line, start at 6)
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

		//*****************************************************Sphere Vertex Data*******************************************************
		glCreateVertexArrays(1, &sphereVAO);
		glBindVertexArray(sphereVAO);

		NormalMapper sphereNormal;
		sphereNormal.calculateTanAndBitan(o_sphere->getVertexData(), o_sphere->getVertexSize() - 1, o_sphere->getIndexData(), o_sphere->getIndexSize() - 1);
		std::vector<float> normalizedSphereNormal = sphereNormal.getUpdatedVertexData();

		glCreateBuffers(1, &sphereVBO);
		glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
		glBufferData(GL_ARRAY_BUFFER, normalizedSphereNormal.size() * sizeof(GLfloat), normalizedSphereNormal.data(), GL_STATIC_DRAW);

		glCreateBuffers(1, &sphereIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, o_sphere->getIndexSize() * sizeof(GLuint), o_sphere->getIndexData(), GL_STATIC_DRAW);

		//(pos 0 (position), 3 floats, not normalized, 14 float between each data line, start at 0)
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0); // Position
		 //(pos 1 (normal), 3 floats, not normalized, 14 float between each data line, start at 3)
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float))); // Normal
		 //(pos 2 (uv), 2 floats, not normalized, 14 float between each data line, start at 6)
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
	}
}
