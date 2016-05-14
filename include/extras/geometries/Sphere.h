#pragma once

#include "math\Math.h"
#include "core\BufferGeometry.h"

namespace engine
{
	class Sphere : public BufferGeometry
	{
	public:
		Sphere(
			float radius	= 1,
			int   uSegments = 12,
			int   vSegments = 6,
			float uStart	= 0,
			float uLength	= Math::PI * 2,
			float vStart	= 0,
			float vLength	= Math::PI);

	public:
		float radius;
		int   uSegments;
		int   vSegments;
		float uStart;
		float uLength;
		float vStart;
		float vLength;
	};
}