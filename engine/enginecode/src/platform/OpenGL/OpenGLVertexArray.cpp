/** \file   OpenGLVertexArray.cpp */

#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLVertexArray.h"
#include "core/log.h"

namespace Engine
{
	//!< Create & Bind Vertex Array data
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_OpenGL_ID);
		glBindVertexArray(m_OpenGL_ID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_OpenGL_ID);
	}

	//!< Add Vertex Buffer data
	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& vertexBuffer)
	{
		m_vertexBuffers.push_back(vertexBuffer);
		
		glBindVertexArray(m_OpenGL_ID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getID());
		
		const auto& layout = vertexBuffer->getLayout();
		for (const auto& element : layout)
		{
			uint32_t normalized = GL_FALSE;
			if (element.m_normalized) { normalized = GL_TRUE; }
			glEnableVertexAttribArray(m_attributeIndex);
			glVertexAttribPointer(
				m_attributeIndex,
				SDT::componentCount(element.m_dataType),
				SDT::toGLType(element.m_dataType),
				normalized,
				layout.getStride(),
				(void*) element.m_offset);	// Position
			m_attributeIndex++;
			
			//Log::info("Vertex Buffer details, {0}, {1}, {2}, {3}", element.m_dataType, element.m_size, element.m_offset, element.m_normalized);
		}
		
		
		
		// Unbind everyting
		/*glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
	}

	//!< Add Index Buffer data
	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer>& indexBuffer)
	{
		m_indexBuffer = indexBuffer;
	}
}