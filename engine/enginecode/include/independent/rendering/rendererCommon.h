/** \file   rendererCommon.h */
#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>
#include "rendering/shaderDataType.h"
#include "rendering/renderAPI.h"
#include "platform/OpenGL/OpenGLVertexArray.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "platform/OpenGL/OpenGLShader.h"

namespace Engine
{
	using SceneWideUniforms = std::unordered_map<const char*, std::pair<ShaderDataType, void*>>;
}
