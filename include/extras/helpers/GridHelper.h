#pragma once

#include "core\BufferGeometry.h"

namespace engine
{
	class GridHelper : public BufferGeometry
	{
	public:
		GridHelper(
			float width = 1,
			float height = 1,
			int widthSegment = 1,
			int heightSegment = 1);

	public:
		float width;
		float height;
		int widthSegment;
		int heightSegment;
	};
}