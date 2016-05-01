#include "extras\geometries\PlaneBufferGeometry.h"

namespace engine
{
	PlaneBufferGeometry::PlaneBufferGeometry(float width, float height, int widthSegments, int heightSegments)
		: width(width)
		, height(height)
		, widthSegments(widthSegments)
		, heightSegments(heightSegments)
	{
		float halfWidth = width * 0.5f;
		float halfHeight = height * 0.5f;
		float uvxStep = 1.0f / widthSegments;
		float uvyStep = 1.0f / widthSegments;
		float widthStep = width * uvxStep;
		float heightStep = height * uvyStep;
		int w1 = widthSegments + 1;
		int h1 = heightSegments + 1;

		int count = w1 * w1;
		std::vector<float> vertices, normals, uvs;
		vertices.reserve(count * 3);
		normals.reserve(count * 3);
		uvs.reserve(count * 2);

		float position[2];
		position[1] = halfHeight + heightStep;

		float uv[2];
		uv[1] = -uvyStep;

		for (int iy = 0; iy < h1; ++iy)
		{
			position[0] = -halfWidth - widthStep;
			position[1] -= heightStep;

			uv[0] = -uvxStep;
			uv[1] += uvyStep;

			for (int ix = 0; ix < w1; ++ix)
			{
				position[0] += widthStep;
				uv[0] += uvxStep;

				vertices.push_back(position[0]);
				vertices.push_back(0);
				vertices.push_back(position[1]);

				normals.push_back(0);
				normals.push_back(1);
				normals.push_back(0);

				uvs.push_back(uv[0]);
				uvs.push_back(uv[1]);
			}
		}

		indices.reserve(widthSegments * heightSegments * 6);

		for (int iy = 0; iy < heightSegments; ++iy)
		{
			for (int ix = 0; ix < widthSegments; ++ix)
			{
				unsigned int a = w1 * iy + ix;
				unsigned int b = a + 1;
				unsigned int c = b + w1;
				unsigned int d = c - 1;

				indices.push_back(a);
				indices.push_back(b);
				indices.push_back(d);
				indices.push_back(b);
				indices.push_back(c);
				indices.push_back(d);
			}
		}

		addAttribute("position", new BufferAttribute(vertices, 3));
		addAttribute("normal", new BufferAttribute(normals, 3));
		addAttribute("uv", new BufferAttribute(uvs, 2));
	}
}