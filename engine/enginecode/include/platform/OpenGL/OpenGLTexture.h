/** \file   OpenGLTexture.h */
#pragma once

namespace Engine
{
	/** \class OpenGLTexture */
	class OpenGLTexture
	{
	public:
		OpenGLTexture(const char* filepath, uint32_t slot = 0);
		OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data, uint32_t slot = 0);
		~OpenGLTexture();
		void bindToSlot(uint32_t slot);
		void edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char* data);
		inline uint32_t getID() { return m_OpenGL_ID; }	//!< Get Render ID
		inline uint32_t getWidth() { return m_width; }	//!< Get Texture width
		inline uint32_t getHeight() { return m_height; }	//!< Get Texture height
		inline uint32_t getWidthf() { return static_cast<float>(m_width); }	
		inline uint32_t getHeightf() { return static_cast<float>(m_height); }
		inline uint32_t getChannels () { return m_channels; }	//!< Return texture channels
	private:
		uint32_t m_OpenGL_ID;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_channels;
		void init(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data, uint32_t slot);
	};
}
