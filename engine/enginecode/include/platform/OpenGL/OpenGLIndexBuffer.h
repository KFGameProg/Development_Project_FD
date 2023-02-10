/** \file   OpenGLindexBuffer.h */
#pragma once
#include <cstdint>
#include "rendering/agnosticIndexBuffer.h"

namespace Engine
{
	/** \class OpenGLIndexBuffer */
	class OpenGLIndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);	//!< Constructor
		~OpenGLIndexBuffer();	//!< Destructor
		inline uint32_t getID() const { return m_OpenGL_ID; }	//!< Get IB's Render ID 
		inline uint32_t getCount() const { return m_count; }	//!< Return the draw count
	private:
		uint32_t m_OpenGL_ID;	//!< Render ID
		uint32_t m_count;	//!< Draw count
	};
}
