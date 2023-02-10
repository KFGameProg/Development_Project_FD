/** \file   OpenGLVertexArray.h */
#pragma once
#include <vector>
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"

namespace Engine
{
	/** \class OpenGLVertexArray */
	class OpenGLVertexArray
	{
	public:
		OpenGLVertexArray();	//!< Constructor
		~OpenGLVertexArray();	//!< Destructor
		void addVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& vertexBuffer);	//!< Add VB
		void setIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer>& indexBuffer);	//!< Set Index Buffer for VA
		inline uint32_t getID() const { return m_OpenGL_ID; }	//!< Get VA's Render ID
		inline std::vector<std::shared_ptr<OpenGLVertexBuffer>> getVertexBuffers() const { return m_vertexBuffers; }	//!< Get VB's
		inline std::shared_ptr<OpenGLIndexBuffer> getIndexBuffers() const { return m_indexBuffer; }	//!< get the IB
		inline uint32_t getDrawCount() {
			if (m_indexBuffer) { return m_indexBuffer->getCount(); }
			else { return 0; }
		}	//!< Return no. of Primitives
	private:
		uint32_t m_OpenGL_ID;	//!< Current Buffer ID
		uint32_t m_attributeIndex = 0;	//!< Indexs next Buffer Attribute
		std::vector<std::shared_ptr<OpenGLVertexBuffer>> m_vertexBuffers;	//!< Vertex Buffer Storage
		std::shared_ptr<OpenGLIndexBuffer> m_indexBuffer;	//!< Index Buffer for VB's
	};
}
