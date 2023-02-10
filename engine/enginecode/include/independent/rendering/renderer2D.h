/** \file   renderer2D.h */
#pragma once

#include "rendering/rendererCommon.h"

#include "ft2build.h"
#include "freetype/freetype.h"

namespace Engine
{
	/**
	 * \class Quad
	 * \brief Class for building 2D quads
	 */
	class Quad
	{
	public:
		Quad() = default;
		static Quad createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents);
		static Quad createCentreHalfExtents(const glm::vec2& centre, float halfExtents);
		static Quad createCentreTopLeftSize(const glm::vec2& topLeft, const glm::vec2& size);
		static Quad createCentreTopLeftSize(const glm::vec2& topLeft, float size);
		static Quad createCentreTopLeftBottomRight(const glm::vec2& topLeft, const glm::vec2& bottomRight);
	private:
		glm::vec3 m_translate = glm::vec3(0.f);	//!< Translation Vector
		glm::vec3 m_scale = glm::vec3(1.f);	//!< Scale Vector
		friend class Renderer2D;
	};

	/**
	 * \class Renderer2D
	 * \brief Class for rendering simple 2D primitives
	 */
	class Renderer2D
	{
	public:
		static void init();	//!< Init the internal data of the renderer
		static void begin(const SceneWideUniforms& swu);	//!< Begin a 2D scene
		static void submit(const Quad& quad, const glm::vec4& tint);	//!< Render a tinted quad
		static void submit(const Quad& quad, const std::shared_ptr<OpenGLTexture>& texture);	//!< Render a texture quad
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<OpenGLTexture>& texture);	//!< Render tinted and textured quad
		static void submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees = false);	//!< Render rotating tinted quad
		static void submit(const Quad& quad, const std::shared_ptr<OpenGLTexture>& texture, float angle, bool degrees = false);	//!< Render rotating textured quad
		static void submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<OpenGLTexture>& texture, float angle, bool degrees = false);	//!< Render rotating tinted and textured quad
		
		static void submit(char ch, const glm::vec2& position, float& advance, const glm::vec4 tint);	//!< Render a character w/ a tint

		static void end();	//!< End rendering
	private:
		/** \struct InternalData */
		struct InternalData
		{
			std::shared_ptr<OpenGLTexture> defaultTexture;
			glm::vec4 defaultTint;
			std::shared_ptr<OpenGLShader> shader;
			std::shared_ptr<OpenGLVertexArray> VAO;
			glm::mat4 model;
			FT_Library ft;
			FT_Face fontFace;
			std::shared_ptr<OpenGLTexture> fontTexture;
		};

		static std::shared_ptr<InternalData> s_data;
	};
}



