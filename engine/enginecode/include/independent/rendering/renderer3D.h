/** \file   renderer3D.h */
#pragma once

#include "rendering/rendererCommon.h"

namespace Engine
{
	/** \class RendererCommon
	 *  \brief data and functionality common for renderers
	 */
	class RendererCommon
	{
	public:
		static std::shared_ptr<OpenGLTexture> defaultTexture;	//!< Default White Texture
		static std::shared_ptr<OpenGLTexture> subTexture;	//!< Default White Sub Texture
		static glm::vec4 defaultTint;	//!< Default White Tint
	};

	/** \class Material
	 *  \brief Hold a shader and its associated uniform data
	 */
	class Material 
	{
	public:
		Material(const std::shared_ptr<OpenGLShader>& shader) : 
			m_shader(shader), m_flags(0), m_texture(nullptr), m_tint(glm::vec4(0.f))
		{}
		Material(const std::shared_ptr<OpenGLShader>& shader, const std::shared_ptr<OpenGLTexture>& texture, const glm::vec4& tint) :
			m_shader(shader), m_texture(texture), m_tint(tint)
		{
			setFlag(flag_texture | flag_tint);
		}
		Material(const std::shared_ptr<OpenGLShader>& shader, const std::shared_ptr<OpenGLTexture>& texture) :
			m_shader(shader), m_texture(texture), m_tint(glm::vec4(0.f))
		{
			setFlag(flag_texture);
		}
		Material(const std::shared_ptr<OpenGLShader>& shader, const glm::vec4& tint) :
			m_shader(shader), m_texture(nullptr), m_tint(tint)
		{
			setFlag(flag_tint);
		}

		inline std::shared_ptr<OpenGLShader> getShader() const { return m_shader; }		//!< Return current shader
		inline std::shared_ptr<OpenGLTexture> getTexture() const { return m_texture; }	//!< Return current texture
		inline glm::vec4 getTint() const { return m_tint; }				//!< Return current tint
		bool isFlagSet(uint32_t flag) const { return m_flags & flag; }	//!< If flag is anything other than 0, the flag is set

		void setTexture(const std::shared_ptr<OpenGLTexture>& texture) { m_texture = texture; }
		void setTint(const glm::vec4& tint) { m_tint = tint; }

		constexpr static uint32_t flag_texture = 1 << 0;	//!< 00000001
		constexpr static uint32_t flag_tint = 1 << 1;		//!< 00000010
	private:
		uint32_t m_flags = 0; //!< Bitfield representation of shader settings
		std::shared_ptr<OpenGLShader> m_shader; //!< Materials shader
		std::shared_ptr<OpenGLTexture> m_texture; //!< Texture to apply to material
		glm::vec4 m_tint; //!< Colour tint applied to geometry
		void setFlag(uint32_t flag) { m_flags = m_flags | flag; }
	};

	/**
	 * \class Renderer3D
	 * \brief A class which rendered 3D geometry instantly (non-batched)
	 */
	class Renderer3D
	{
	public:
		static void init();	//!< Init the Renderer
		static void begin(const SceneWideUniforms& sceneWiderUniforms);	//!< Begin a new 3D scene
		static void submit(const std::shared_ptr<OpenGLVertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4& model);	//!< Submit a piece of geometry to be rendered
		static void end();	//!< End the current 3D scene
	private:
		struct InternalData
		{
			SceneWideUniforms sceneWideUniforms;	//!< Replace with UBO at some point
			std::shared_ptr<OpenGLTexture> defaultTexture;	//!< Empty blank texture
			glm::vec4 defaultTint;	//!< Default white tint
		};

		static std::shared_ptr<InternalData> s_data;	//!< Data internal to the renderer
	};
}
