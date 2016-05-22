#pragma once

#include "core/BufferGeometry.h"

namespace engine
{
	class Box : public BufferGeometry
	{
	public:
		Box() : width(1), height(1), depth(1)
		{
			init();
		}

		Box(float width, float height, float depth) : width(width), height(height), depth(depth)
		{
			init();
		}

	public:
		float width;
		float height;
		float depth;

	private:
		void init();
	};
}
