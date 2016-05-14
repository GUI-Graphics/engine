#pragma once

#include "core/BufferGeometry.h"

namespace engine
{
	class Box : public BufferGeometry
	{
	public:
		Box(float width = 1, float height = 1, float depth = 1);

	public:
		float width;
		float height;
		float depth;
	};
}
