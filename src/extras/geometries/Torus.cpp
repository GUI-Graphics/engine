#include "extras\geometries\Torus.h"

namespace engine
{
	Torus::Torus(float radius, float tube, int uSegments, int vSegments, float uStart, float uLength, float vStart, float vLength)
		: radius(radius)
		, tube(tube)
		, uSegments(uSegments)
		, vSegments(vSegments)
		, uStart(uStart)
		, uLength(uLength)
		, vStart(vStart)
		, vLength(vLength)
	{
		int u1 = uSegments + 1;
		int v1 = vSegments + 1;
		int count = u1 * v1;

		std::vector<float> vertices, normals, uvs;
		vertices.reserve(count * 3);
		normals.reserve(count * 3);
		uvs.reserve(count * 2);

		float stepU = 1.0f / uSegments;
		float stepV = 1.0f / vSegments;

		float stepAngleU = stepU * uLength;
		float stepAngleV = stepV * vLength;

		float u;
		float v = -stepV;

		float angleU;
		float angleV = vStart - stepAngleV;

		float startAngleU = uStart - stepAngleU;

		float r;
		float su, cu, sv, cv;

		for (int i = 0; i < v1; ++i)
		{
			u = -stepU;
			v += stepV;

			angleU = startAngleU;
			angleV += stepAngleV;

			sv = sinf(angleV);
			cv = cosf(angleV);

			r = radius - tube * cv;

			for (int j = 0; j < u1; ++j)
			{
				u += stepU;
				angleU += stepAngleU;

				su = sinf(angleU);
				cu = cosf(angleU);

				vertices.push_back(r * su);
				vertices.push_back(-tube * sv);
				vertices.push_back(r * cu);

				normals.push_back(-su * cv);
				normals.push_back(sv);
				normals.push_back(-cu * cv);

				uvs.push_back(u);
				uvs.push_back(v);
			}
		}

		unsigned int a = -1;
		unsigned int b;
		unsigned int c;
		unsigned int d;

		indices.reserve(uSegments * vSegments * 6);

		for (int i = 0; i < vSegments; ++i)
		{

			for (int j = 0; j < uSegments; ++j)
			{
				++a;
				b = a + 1;
				c = b + u1;
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