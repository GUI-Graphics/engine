#include "extras\geometries\Plane.h"

namespace engine
{
	Plane::Plane(float width, float height, int widthSegments, int heightSegments)
		: width(width)
		, height(height)
		, widthSegments(widthSegments)
		, heightSegments(heightSegments)
	{
		int w1 = widthSegments + 1;
		int h1 = heightSegments + 1;
		int count = w1 * h1;

		std::vector<float> vertices, normals, uvs;
		vertices.reserve(count * 3);
		normals.reserve(count * 3);
		uvs.reserve(count * 2);

		float stepU = 1.0f / widthSegments;
		float stepV = 1.0f / heightSegments;

		float stepX = stepU * width;
		float stepY = stepV * height;

		float startX = -0.5f * width - stepX;
		float startY = -0.5f * height - stepY;

		float x;
		float y = startY;

		float u;
		float v = -stepV;

		for (int i = 0; i < h1; ++i)
		{
			x = startX;
			y += stepY;

			u = -stepU;
			v += stepV;

			for (int j = 0; j < w1; ++j)
			{
				x += stepX;
				u += stepU;

				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(0);

				normals.push_back(0);
				normals.push_back(1);
				normals.push_back(0);

				uvs.push_back(u);
				uvs.push_back(v);
			}
		}

		indices.reserve(widthSegments * heightSegments * 6);

		unsigned int a = -1;
		unsigned int b;
		unsigned int c;
		unsigned int d;

		for (int i = 0; i < heightSegments; ++i)
		{
			for (int j = 0; j < widthSegments; ++j)
			{
				++a;
				b = a + 1;
				c = b + w1;
				d = c - 1;

				indices.push_back(a);
				indices.push_back(b);
				indices.push_back(d);
				indices.push_back(b);
				indices.push_back(c);
				indices.push_back(d);
			}

			++a;
		}

		addAttribute("position", new BufferAttribute(vertices, 3));
		addAttribute("normal", new BufferAttribute(normals, 3));
		addAttribute("uv", new BufferAttribute(uvs, 2));
	}
}