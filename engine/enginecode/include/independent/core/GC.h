/** \file   GC.h*/
#pragma once

namespace Engine
{
	/**
	 * \class GraphicsContext
	 * \brief OpenGL context
	 */
	class GraphicsContext
	{
	public:
		virtual void init() = 0;
		virtual void swapBuffers() = 0;
	};
}
