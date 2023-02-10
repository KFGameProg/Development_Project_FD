/** \file   OpenGLVertexBuffer.h */
#pragma once
#include "rendering/bufferLayout.h"

namespace Engine
{
	/** \class OpenGLVertexBuffer */
	class OpenGLVertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, BufferLayout layout);  //!< Constructor
		~OpenGLVertexBuffer();	//!< Destructor
		void edit(void* vertices, uint32_t size, uint32_t offset);
		inline uint32_t getID() const { return m_OpenGL_ID; }	//!< Get VB's Render ID
		inline const BufferLayout& getLayout() const { return m_layout; }	//!< Get VB's Buffer Layout
	private:
		uint32_t m_OpenGL_ID;	//!< Render ID
		BufferLayout m_layout;	//!< Buffer Layout
	};
}
