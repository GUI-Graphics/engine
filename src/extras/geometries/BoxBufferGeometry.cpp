#include "extras\geometries\BoxBufferGeometry.h"

namespace engine
{
	BoxBufferGeometry::BoxBufferGeometry(float width, float height, float depth, int widthSegments, int heightSegments, int depthSegments)
		: width(width)
		, height(height)
		, depth(depth)
		, widthSegments(widthSegments)
		, heightSegments(heightSegments)
		, depthSegments(depthSegments)
	{
		int w1 = widthSegments + 1;
		int h1 = heightSegments + 1;
		int d1 = depthSegments + 1;

		int vertexCount = (w1 * h1 + w1 * d1 + h1 * d1) * 2;
		int indexCount = (widthSegments * heightSegments + widthSegments * depthSegments + heightSegments * depthSegments) * 12;

		std::vector<float> vertices, normals, uvs;
		indices.reserve(indexCount);
		vertices.reserve(vertexCount * 3);
		normals.reserve(vertexCount * 3);
		uvs.reserve(vertexCount * 2);

		addAttribute("position", new BufferAttribute(vertices, 3));
		addAttribute("normal", new BufferAttribute(normals, 3));
		addAttribute("uv", new BufferAttribute(uvs, 2));

		buildPlane('x', 'y',  1.0f, width, height,  depth *  0.5f, widthSegments, heightSegments);
		buildPlane('x', 'y', -1.0f, width, height,  depth * -0.5f, widthSegments, heightSegments);
		buildPlane('y', 'z',  1.0f, depth, height,  width * -0.5f, depthSegments, heightSegments);
		buildPlane('y', 'z', -1.0f, depth, height,  width *  0.5f, depthSegments, heightSegments);
		buildPlane('x', 'z',  1.0f, width,  depth, height *  0.5f, widthSegments,  depthSegments);
		buildPlane('x', 'z', -1.0f, width,  depth, height * -0.5f, widthSegments,  depthSegments);
	}

	void BoxBufferGeometry::buildPlane(char u, char v, float dir, float width, float height, float depth, int widthSegments, int heightSegments)
	{
		auto& vertices = attributes["position"]->array;
		auto& normals = attributes["normal"]->array;
		auto& uvs = attributes["uv"]->array;

		int offset = (int)vertices.size() / 3;

		float widthSegmentsInverse = 1.0f / widthSegments;
		float heightSegmentsInverse = 1.0f / heightSegments;
		float segmentWidth = width * widthSegmentsInverse;
		float segmentHeight = height * heightSegmentsInverse;
		float halfWidth = width * 0.5f;
		float halfHeight = height * 0.5f;

		float position[3];
		float normal[3];
		float uv[2];

		int x = 0, y = 1, z = 2;

		if (u == 'x')
		{
			if (v == 'z')
			{
				y = 2;
				z = 1;
			}
		}
		else
		{
			x = 1;
			y = 2;
			z = 0;
		}

		normal[x] = 0;
		normal[y] = 0;
		normal[z] = dir;

		position[y] = -halfHeight - segmentHeight;
		position[z] = depth;

		uv[1] = -heightSegmentsInverse;

		int w1 = widthSegments + 1;
		int h1 = heightSegments + 1;

		for (int iy = 0; iy < h1; ++iy)
		{
			uv[0] = -widthSegmentsInverse;
			uv[1] += heightSegmentsInverse;

			position[x] = (-halfWidth - segmentWidth) * dir;
			position[y] += segmentHeight;

			for (int ix = 0; ix < w1; ++ix)
			{
				uv[0] += widthSegmentsInverse;
				position[x] += segmentWidth * dir;

				vertices.push_back(position[0]);
				vertices.push_back(position[1]);
				vertices.push_back(position[2]);

				normals.push_back(normal[0]);
				normals.push_back(normal[1]);
				normals.push_back(normal[2]);

				uvs.push_back(uv[0]);
				uvs.push_back(uv[1]);
			}
		}

		for (int iy = 0; iy < heightSegments; ++iy)
		{
			for (int ix = 0; ix < widthSegments; ++ix)
			{
				unsigned int a = iy * w1 + ix + offset;
				unsigned int b = a + 1;
				unsigned int c = b + w1;
				unsigned int d = a + w1;

				indices.push_back(a);
				indices.push_back(b);
				indices.push_back(d);
				indices.push_back(b);
				indices.push_back(c);
				indices.push_back(d);
			}
		}
	}
}