#pragma once

#include "math\Math.h"
#include "core\BufferGeometry.h"

namespace engine
{
	class TorusBufferGeometry : public BufferGeometry
	{
	public:
		TorusBufferGeometry(
			float radius			= 1,
			float tube				= 0.3f,
			int   radialSegments	= 24,
			int   tubeSegments		= 12,
			float arc				= Math::PI * 2);

	public:
		float	radius;
		float	tube;
		int		radialSegments;
		int		tubeSegments;
		float	arc;
	};
}