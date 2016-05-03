#pragma once

#include "core\BufferGeometry.h"

namespace engine
{
	class BoxHelper : public BufferGeometry
	{
	public:
		BoxHelper(float width, float height, float depth) : width(width), height(height), depth(depth)
		{
			float x = width  * 0.5f;
			float y = height * 0.5f;
			float z = depth  * 0.5f;

			std::vector<float> vertices =
			{
				-x, -y,  z,
				 x, -y,  z,
				 x,  y,  z,
				-x,  y,  z,
				-x, -y, -z,
				 x, -y, -z,
				 x,  y, -z,
				-x,  y, -z,
			};

			indices = { 0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7 };

			addAttribute("position", new BufferAttribute(vertices, 3));
		}

	public:
		float width;
		float height;
		float depth;
	};
}
