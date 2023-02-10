/** \file   renderAPI.cpp */
#include "engine_pch.h"
#include "rendering/renderAPI.h"
#include "core/log.h"

#include "rendering/agnosticIndexBuffer.h"

#include "platform/OpenGL/OpenGLIndexBuffer.h"

namespace Engine
{
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

	AgsIndexBuffer* AgsIndexBuffer::create(uint32_t* indices, uint32_t count)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::None :
			Log::error("No Rendering API Applied");
			break;
		case RenderAPI::API::OpenGL :
			//return new OpenGLIndexBuffer(indices, count);
			break;
		case RenderAPI::API::Direct3D :
			Log::error("Direct3D API Not Currently Supported");
			break;
		case RenderAPI::API::Vulkan :
			Log::error("Vulkan API Not Currently Supported");
			break;
		}

		return nullptr;
	}
}