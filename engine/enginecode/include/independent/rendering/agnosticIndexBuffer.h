/** \file   agnosticIndexBuffer.h */
#pragma once

#include <cstdint>

namespace Engine
{
	/**
	 * class AgsIndexBuffer
	 * API agnostic index buffer
	 */
	class AgsIndexBuffer
	{
	public:
		virtual ~AgsIndexBuffer() = default;
		virtual inline uint32_t getID() const = 0;
		virtual inline uint32_t getCount() const = 0;

		static AgsIndexBuffer* create(uint32_t* indices, uint32_t count);
	};
}
