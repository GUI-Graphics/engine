#pragma once

#include "core\BufferGeometry.h"

namespace engine
{
	class PlaneBufferGeometry : public BufferGeometry
	{
	public:
		PlaneBufferGeometry(float width = 100.0f, float height = 100.0f, int widthSegments = 100, int heightSegments = 100);

	public:
		float width;
		float height;
		int widthSegments;
		int heightSegments;
	};
}
