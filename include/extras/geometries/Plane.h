#pragma once

#include "core\BufferGeometry.h"

namespace engine
{
	class Plane : public BufferGeometry
	{
	public:
		Plane(float width = 1, float height = 1, int widthSegments = 1, int heightSegments = 1);

	public:
		float width;
		float height;
		int   widthSegments;
		int   heightSegments;
	};
}
