#include "extras\helpers\GridHelper.h"

namespace engine
{
	GridHelper::GridHelper(float width, float height, int widthSegment, int heightSegment)
		: width(width), height(height), widthSegment(widthSegment), heightSegment(heightSegment)
	{
		float halfWidth = width  * 0.5f;
		float halfHeight = height * 0.5f;

		float stepX = width / widthSegment;
		float stepY = height / heightSegment;

		std::vector<float> vertices;
		vertices.reserve((widthSegment + heightSegment + 2) * 6);

		float z = halfHeight + stepY;

		for (int i = 0, w1 = widthSegment + 1; i < w1; ++i)
		{
			z -= stepY;
			vertices.push_back(-halfWidth);
			vertices.push_back(0);
			vertices.push_back(z);
			vertices.push_back(halfWidth);
			vertices.push_back(0);
			vertices.push_back(z);
		}

		float x = -halfWidth - stepX;

		for (int i = 0, h1 = heightSegment + 1; i < h1; ++i)
		{
			x += stepX;
			vertices.push_back(x);
			vertices.push_back(0);
			vertices.push_back(halfHeight);
			vertices.push_back(x);
			vertices.push_back(0);
			vertices.push_back(-halfHeight);
		}

		addAttribute("position", new BufferAttribute(vertices, 3));
	}
}