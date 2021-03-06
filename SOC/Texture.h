#pragma once

#if defined(WIN32) && !defined(_USE_GL_DEFINES)

#include "TextureDX.h"

namespace Rendering
{
	namespace Texture
	{
		typedef Rendering::Texture::TextureDX Texture;
	}
}

#elif defined(__APPLE__) || defined(_USE_GL_DEFINES)

#endif