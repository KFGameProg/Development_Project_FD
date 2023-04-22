 /** \ file OpenGLShader.h */
#pragma once
#include <glm/gtc/type_ptr.hpp>

namespace Engine 
{
	/** \class OpenGLShader - shader class */
	class OpenGLShader
	{
	public:
		OpenGLShader(const char* vertexFilepath, const char* fragmentFilepath, const char* geoPath = nullptr, const char* tessCtrlPath = nullptr, const char* tessEvalPath = nullptr);
		OpenGLShader(const char* filepath);
		~OpenGLShader();
		uint32_t getID() { return m_OpenGL_ID; }	//!< Get render ID
		void use();

		void uploadInt(const char* name, int value);
		void uploadFloat(const char* name, float value);
		void uploadFloat2(const char* name, const glm::vec2& value);
		void uploadFloat3(const char* name, const glm::vec3& value);
		void uploadFloat4(const char* name, const glm::vec4& value);
		void uploadMat4(const char* name, const glm::mat4& value);

	private:
		uint32_t m_OpenGL_ID;
		void compileAndLink(const char* vertexShaderSrc, const char* fragmentShaderSrc, const char* geoFilepath = nullptr, const char* tessCtrlFilepath = nullptr, const char* tessEvalFilepath = nullptr);
	};
}