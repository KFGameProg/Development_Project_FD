/** \file   OpenGLShader.cpp */
#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLShader.h"
#include <fstream>
#include "core/log.h"
#include <string>
#include <array>
#include <glm/gtc/type_ptr.hpp>


namespace Engine
{
	//!< Set and Read shaders
	OpenGLShader::OpenGLShader(const char* vertexFilepath, const char* fragmentFilepath, const char* geoFilepath, const char* tessCtrlFilepath, const char* tessEvalFilepath)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::string geoCode;
		std::string tessCcode;
		std::string tessEcode;

		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;
		std::ifstream tcShaderFile;
		std::ifstream teShaderFile;

		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		tcShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		teShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// open files
			vShaderFile.open(vertexFilepath);
			fShaderFile.open(fragmentFilepath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

			if (geoFilepath != nullptr)
			{
				gShaderFile.open(geoFilepath);
				std::stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geoCode = gShaderStream.str();
			}

			if (tessCtrlFilepath != nullptr)
			{
				tcShaderFile.open(tessCtrlFilepath);
				std::stringstream tcShaderStream;
				tcShaderStream << tcShaderFile.rdbuf();
				tcShaderFile.close();
				tessCcode = tcShaderStream.str();
			}

			if (tessEvalFilepath != nullptr)
			{
				teShaderFile.open(tessEvalFilepath);
				std::stringstream teShaderStream;
				teShaderStream << teShaderFile.rdbuf();
				teShaderFile.close();
				tessEcode = teShaderStream.str();
			}
		}
		catch (std::ifstream::failure e)
		{
			Log::error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// 2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// geometry Shader
		unsigned int geometry;
		if (geoFilepath != nullptr)
		{
			const char* gShaderCode = geoCode.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			checkCompileErrors(geometry, "GEOMETRY");
		}
		// tessellation Control Shader
		unsigned int tessControl;
		if (tessCtrlFilepath != nullptr)
		{
			const char* tcShaderCode = tessCcode.c_str();
			tessControl = glCreateShader(GL_TESS_CONTROL_SHADER);
			glShaderSource(tessControl, 1, &tcShaderCode, NULL);
			glCompileShader(tessControl);
			checkCompileErrors(tessControl, "TESSELLATION CONTROL");
		}
		// tessellation Evaluation Shader
		unsigned int tessEvaluation;
		if (tessEvalFilepath != nullptr)
		{
			const char* teShaderCode = tessEcode.c_str();
			tessEvaluation = glCreateShader(GL_TESS_EVALUATION_SHADER);
			glShaderSource(tessEvaluation, 1, &teShaderCode, NULL);
			glCompileShader(tessEvaluation);
			checkCompileErrors(tessEvaluation, "TESSELLATION EVALUATION");
		}

		// shader Program
		m_OpenGL_ID = glCreateProgram();
		glAttachShader(m_OpenGL_ID, vertex);
		glAttachShader(m_OpenGL_ID, fragment);
		if (geoFilepath != nullptr)
			glAttachShader(m_OpenGL_ID, geometry);
		if (tessCtrlFilepath != nullptr)
			glAttachShader(m_OpenGL_ID, tessControl);
		if (tessEvalFilepath != nullptr)
			glAttachShader(m_OpenGL_ID, tessEvaluation);
		glLinkProgram(m_OpenGL_ID);
		checkCompileErrors(m_OpenGL_ID, "PROGRAM");

		// delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geoFilepath != nullptr)
			glDeleteShader(geometry);
		if (tessCtrlFilepath != nullptr)
			glDeleteShader(tessControl);
		if (tessEvalFilepath != nullptr)
			glDeleteShader(tessEvaluation);
	}

	OpenGLShader::OpenGLShader(const char* filepath)
	{
		enum Region {None = -1, Vertex = 0, Fragment, Geometry, TessellationControl, TessellationEvaluation, Compute};
		std::string line;
		std::array<std::string, Region::Compute + 1> src;
		uint32_t region = Region::None;

		std::fstream handle(filepath, std::ios::in);
		if (handle.is_open())
		{
			while (getline(handle, line)) { 
				if (line.find("#region Vertex") != std::string::npos) { continue; }
				if (line.find("#region Fragment") != std::string::npos) { region = Region::Fragment; continue; }
				if (line.find("#region Geometry") != std::string::npos) { region = Region::Geometry; continue; }
				if (line.find("#region TessellationControl") != std::string::npos) { region = Region::TessellationControl; continue; }
				if (line.find("#region TessellationEvaluation") != std::string::npos) { region = Region::TessellationEvaluation; continue; }
				if (line.find("#region Compute") != std::string::npos) { region = Region::Compute; continue; }

				if (region != Region::None) src[region] += (line + "\n"); 
			}
		}
		else
		{
			Log::error("Could not open shader: {0}", filepath);
			return;
		}
		handle.close();
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_OpenGL_ID);
	}


	void OpenGLShader::uploadInt(const char* name, int value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform1i(uniformLocation, value);
	}

	void OpenGLShader::uploadFloat(const char* name, float value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform1f(uniformLocation, value);
	}

	void OpenGLShader::uploadFloat2(const char* name, const glm::vec2& value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform2f(uniformLocation, value.x, value.y);
	}

	void OpenGLShader::uploadFloat3(const char* name, const glm::vec3& value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform3f(uniformLocation, value.x, value.y, value.z);
	}

	void OpenGLShader::uploadFloat4(const char* name, const glm::vec4& value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::uploadMat4(const char* name, const glm::mat4& value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name);
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::uploadBool(const char* name, bool value)
	{
		int32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform1i(uniformLocation, (int)value);
	}

	void OpenGLShader::checkCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				Log::error("ERROR::SHADER_COMPILATION_ERROR of type: {0} \n {1} \n -- --------------------------------------------------- --", type, infoLog);
				Log::error("PROGRAM_LINKING_ERROR of type: {0} \n {1} \n -- --------------------------------------------------- --", type, infoLog);
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				Log::error("PROGRAM_LINKING_ERROR of type: {0} \n {1} \n -- --------------------------------------------------- --", type, infoLog);
			}
		}
	}
}
