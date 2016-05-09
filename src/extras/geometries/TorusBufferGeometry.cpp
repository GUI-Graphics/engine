#include "extras\geometries\TorusBufferGeometry.h"

namespace engine
{
	TorusBufferGeometry::TorusBufferGeometry(float radius, float tube, int radialSegments, int tubeSegments, float arc)
		: radius(radius)
		, tube(tube)
		, radialSegments(radialSegments)
		, tubeSegments(tubeSegments)
		, arc(arc)
	{
		int r1 = radialSegments + 1;
		int t1 = tubeSegments + 1;
		int vertexCount = r1 * t1;
		int indexCount = radialSegments * tubeSegments * 6;

		std::vector<float> vertices, normals, uvs;
		vertices.reserve(vertexCount * 3);
		normals.reserve(vertexCount * 3);
		uvs.reserve(vertexCount * 2);
		indices.reserve(indexCount);

		float stepU = 1.0f / radialSegments;
		float stepV = 1.0f / tubeSegments;
		float stepUAngle = stepU * arc;
		float stepVAngle = stepV * Math::PI * 2;

		float u = -stepU;
		float v;

		float uAngle = -stepUAngle;
		float vAngle;

		for (int i = 0; i < r1; ++i)
		{
			u += stepU;
			v = -stepV;

			uAngle += stepUAngle;
			vAngle = -stepVAngle;


			float cu = cosf(uAngle);
			float su = sinf(uAngle);

			for (int j = 0; j < t1; ++j)
			{
				v += stepV;
				vAngle += stepVAngle;

				float cv = cosf(vAngle);
				float sv = sinf(vAngle);

				float r = radius + tube * cv;

				vertices.push_back(r * cu);
				vertices.push_back(tube * sv);
				vertices.push_back(-r * su);

				normals.push_back(cu * cv);
				normals.push_back(sv);
				normals.push_back(-su * cv);

				uvs.push_back(u);
				uvs.push_back(v);
			}
		}

		unsigned int start = -t1;

		for (int i = 0; i < radialSegments; ++i)
		{
			start += t1;

			for (int j = 0; j < tubeSegments; ++j)
			{
				unsigned int a = start + j;
				unsigned int b = a + t1;
				unsigned int c = b + 1;
				unsigned int d = a + 1;

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