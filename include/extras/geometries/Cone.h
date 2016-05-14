#pragma once

#include "core\BufferGeometry.h"

namespace engine
{
	class Cone : public BufferGeometry
	{
	public:
		Cone(float radius, float height, int radialSegments, int heightSegments, float arc, bool openEnded);

	public:
		bool  openEnded;
		float radius;
		float height;
		int   radialSegments;
		int   heightSegments;
		float arc;
	};
}