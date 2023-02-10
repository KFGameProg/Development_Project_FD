/** \file   bufferLayout.h */
#pragma once
#include "shaderDataType.h"
#include <vector>

namespace Engine
{
	/**
	 * \class BufferElement
	 * \brief A Class holding data about elements in a buffer layout
	 */
	class BufferElement
	{
	public:
		ShaderDataType m_dataType;
		uint32_t m_size;
		uint32_t m_offset;
		bool m_normalized;

		BufferElement() {};	//!< Default Constructor
		BufferElement(ShaderDataType dataType, bool normalized = false) : 
			m_dataType(dataType), 
			m_size(SDT::size(dataType)),
			m_offset(0), 
			m_normalized(normalized) 
		{};	//!< Constructor with params
	};
	
	/**
	 * \class BufferLayout
	 * \brief Abstraction of notion of a buffer layout
	 */
	class BufferLayout 
	{
	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride;

		void calcStrideAndOffsets()	//!< Calculate the stride and offsets
		{
			uint32_t l_offset = 0;

			for (auto& element : m_elements)
			{
				element.m_offset = l_offset;
				l_offset += element.m_size;
			}

			m_stride = l_offset;
		}

	public:
		BufferLayout() {};	//!< Default Constructor
		BufferLayout(const std::initializer_list<BufferElement>& element) : m_elements(element) { calcStrideAndOffsets(); }	//!< Constructor
		inline uint32_t getStride() const { return m_stride; }	//!< return buffer stride
		void addElement(ShaderDataType dataType)	//!< Add buffer element
		{
			m_elements.push_back(BufferElement(dataType));
			calcStrideAndOffsets();
		}
		inline std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		inline std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		inline std::vector<BufferElement>::const_iterator end() const { return m_elements.begin(); }		
	};
}
