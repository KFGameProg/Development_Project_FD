/** \file   renderer2D.cpp */

#include "engine_pch.h"
#include "glad/glad.h"
#include <glm/gtc/matrix_transform.hpp>
#include "rendering/renderer2D.h"

#include "core/log.h"

namespace Engine
{
	std::shared_ptr<Renderer2D::InternalData> Renderer2D::s_data = nullptr;

	void Renderer2D::init()
	{
		s_data.reset(new InternalData);

		unsigned char whitePx[4] = { 255,255,255,255 };
		s_data->defaultTexture.reset(new OpenGLTexture(1, 1, 4, whitePx));

		s_data->defaultTint = { 1.f, 1.f, 1.f, 1.f };
		
		s_data->model = glm::mat4(1.f);

		s_data->shader.reset(new OpenGLShader("..\\assets\\shaders\\quad1.vert", "..\\assets\\shaders\\quad1.frag"));
		
		float vertices[4 * 4] = {
			-0.5f, -0.5f, 0.f, 0.f,
			-0.5f,  0.5f, 0.f, 1.f,
			 0.5f,  0.5f, 1.f, 1.f,
			 0.5f,  0.5f, 1.f, 0.f
		};
		
		uint32_t indices[4] = { 0,1,2,3 };

		std::shared_ptr<OpenGLVertexBuffer> VBO;
		std::shared_ptr<OpenGLIndexBuffer> IBO;

		s_data->VAO.reset(new OpenGLVertexArray());
		VBO.reset(new OpenGLVertexBuffer(vertices, sizeof(vertices), BufferLayout({ ShaderDataType::Float2, ShaderDataType::Float2 })));
		IBO.reset(new OpenGLIndexBuffer(indices, 4));
		s_data->VAO->addVertexBuffer(VBO);
		s_data->VAO->setIndexBuffer(IBO);

		//!< Font filepath
		const char* filePath = "..\\assets\\fonts\\Roboto-Medium.ttf";

		//!< Initialise freetype
		if (FT_Init_FreeType(&s_data->ft)) Log::error("ERROR: Freetyoe could'n be initialised");

		// Load Font
		if (FT_New_Face(s_data->ft, filePath, 0, &s_data->fontFace)) Log::error("ERROR: Freetype couldn't load font: {0}", filePath);

		//!< Set character size
		int32_t charSize = 86;
		if (FT_Set_Pixel_Sizes(s_data->fontFace, 0, charSize)) Log::error("ERROR: Freetype can't set font size");

		//!< Initialise font text
		s_data->fontTexture.reset(new OpenGLTexture(256,256,4,nullptr));
	}

	void Renderer2D::begin(const SceneWideUniforms& swu)
	{
		//!< Bind shader
		glUseProgram(s_data->shader->getID());

		//!< Apply sceneWideUniforms
		for (auto& dataPair : swu)
		{
			const char* nameOfUniform = dataPair.first;
			ShaderDataType sdt = dataPair.second.first;
			void* addressOfValue = dataPair.second.second;

			switch (sdt)
			{
			case ShaderDataType::Int:
				s_data->shader->uploadInt(nameOfUniform, *(int*)addressOfValue);
				break;
			case ShaderDataType::Float3:
				s_data->shader->uploadFloat3(nameOfUniform, *(glm::vec3*)addressOfValue);
				break;
			case ShaderDataType::Float4:
				s_data->shader->uploadFloat4(nameOfUniform, *(glm::vec4*)addressOfValue);
				break;
			case ShaderDataType::Mat4:
				s_data->shader->uploadMat4(nameOfUniform, *(glm::mat4*)addressOfValue);
				break;
			}

			//!< Bind Geometry (VAO & IBO)
			glBindVertexArray(s_data->VAO->getID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffers()->getID());
		}
	}

	//!< Render a tinted quad
	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint)
	{
		glBindTexture(GL_TEXTURE_2D, s_data->defaultTexture->getID());

		//!< Do Geometry Transforms
		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale);

		s_data->shader->uploadInt("u_texData", 0);
		s_data->shader->uploadFloat4("u_tint", tint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ARRAY_BUFFER, s_data->VAO->getIndexBuffers()->getID());

		//!< Issue Draw Call
		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	//!< Render a texture quad
	void Renderer2D::submit(const Quad& quad, const std::shared_ptr<OpenGLTexture>& texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture->getID());

		//!< Do Geometry Transforms
		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale);

		s_data->shader->uploadInt("u_texData", 0);
		s_data->shader->uploadFloat4("u_tint", s_data->defaultTint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ARRAY_BUFFER, s_data->VAO->getIndexBuffers()->getID());

		//!< Issue Draw Call
		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	//!< Render tinted and textured quad
	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<OpenGLTexture>& texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture->getID());

		//!< Do Geometry Transforms
		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale);

		s_data->shader->uploadInt("u_texData", 0);
		s_data->shader->uploadFloat4("u_tint", tint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ARRAY_BUFFER, s_data->VAO->getIndexBuffers()->getID());

		//!< Issue Draw Call
		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	//!< Render rotating tinted quad
	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees)
	{
		if (degrees) angle = glm::radians(angle);

		glBindTexture(GL_TEXTURE_2D, s_data->defaultTexture->getID());

		//!< Do Geometry Transforms
		s_data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.f), quad.m_translate), angle, { 0.f,0.f,1.f }), quad.m_scale);

		s_data->shader->uploadInt("u_texData", 0);
		s_data->shader->uploadFloat4("u_tint", tint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ARRAY_BUFFER, s_data->VAO->getIndexBuffers()->getID());

		//!< Issue Draw Call
		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	//!< Render rotating textured quad
	void Renderer2D::submit(const Quad& quad, const std::shared_ptr<OpenGLTexture>& texture, float angle, bool degrees)
	{
		if (degrees) angle = glm::radians(angle);

		glBindTexture(GL_TEXTURE_2D, texture->getID());

		//!< Do Geometry Transforms
		s_data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.f), quad.m_translate), angle, { 0.f,0.f,1.f }), quad.m_scale);

		s_data->shader->uploadInt("u_texData", 0);
		s_data->shader->uploadFloat4("u_tint", s_data->defaultTint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ARRAY_BUFFER, s_data->VAO->getIndexBuffers()->getID());

		//!< Issue Draw Call
		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	//!< Render rotating tinted and textured quad
	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<OpenGLTexture>& texture, float angle, bool degrees)
	{
		if (degrees) angle = glm::radians(angle);

		glBindTexture(GL_TEXTURE_2D, texture->getID());

		//!< Do Geometry Transforms
		s_data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.f), quad.m_translate), angle, {0.f,0.f,1.f}), quad.m_scale);

		s_data->shader->uploadInt("u_texData", 0);
		s_data->shader->uploadFloat4("u_tint", tint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ARRAY_BUFFER, s_data->VAO->getIndexBuffers()->getID());

		//!< Issue Draw Call
		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::submit(char ch, const glm::vec2& position, float& advance, const glm::vec4 tint)
	{
		//!< Get glyph from freetype
		if (FT_Load_Char(s_data->fontFace, ch, FT_LOAD_RENDER)) Log::error("ERROR: Could not load glyph for char {0}", ch);
		else
		{
			//!< Get glyph data
			uint32_t glyphWidth = s_data->fontFace->glyph->bitmap.width;
			uint32_t glyphHeight = s_data->fontFace->glyph->bitmap.rows;
			glm::vec2 glyphSize(glyphWidth, glyphHeight);
			glm::vec2 glyphBearing(s_data->fontFace->glyph->bitmap_left, -s_data->fontFace->glyph->bitmap_top);

			//!< Calculate the advance
			advance = static_cast<float>(s_data->fontFace->glyph->advance.x >> 6);

			//!< Calculate the quad for the glyph
			glm::vec2 glyphHalfExtents = glm::vec2(s_data->fontTexture->getWidthf() * 0.5f, s_data->fontTexture->getHeightf() * 0.5f);
			glm::vec2 glyphPosition = (position + glyphBearing) + glyphHalfExtents;
			Quad quad = Quad::createCentreHalfExtents(glyphPosition, glyphHalfExtents);

			//!< Submit quad
			submit(quad, tint, s_data->fontTexture);
		}
	}

	void Renderer2D::end()
	{
		//s_data->sceneWideUniforms.clear();
	}
	
	Quad Quad::createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents)
	{
		Quad result;

		result.m_translate = glm::vec3(centre, 0.f);
		result.m_scale = glm::vec3(halfExtents * 2.f, 1.f);

		return result;
	}
}
