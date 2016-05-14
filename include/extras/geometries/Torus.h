#pragma once

#include "math\Math.h"
#include "core\BufferGeometry.h"

namespace engine
{
	class Torus : public BufferGeometry
	{
	public:
		Torus(
			float radius		= 1,
			float tube			= 0.3f,
			int   uSegments		= 24,
			int   vSegments		= 12,
			float uStart		= 0,
			float uLength		= Math::PI * 2,
			float vStart		= 0,
			float vLength		= Math::PI * 2);

	public:
		float radius;
		float tube;
		int	  uSegments;
		int	  vSegments;
		float uStart;
		float uLength;
		float vStart;
		float vLength;
	};
}