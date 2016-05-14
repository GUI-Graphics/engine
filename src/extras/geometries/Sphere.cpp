#include "extras\geometries\Sphere.h"

namespace engine
{
	Sphere::Sphere(float radius, int uSegments, int vSegments, float uStart, float uLength, float vStart, float vLength)
		: radius(radius)
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

		float x, y, z;
		float su, cu, sv, cv;

		for (int i = 0; i < v1; ++i)
		{
			u = -stepU;
			v += stepV;

			angleU = startAngleU;
			angleV += stepAngleV;

			sv = sinf(angleV);
			cv = cosf(angleV);

			for (int j = 0; j < u1; ++j)
			{
				u += stepU;
				angleU += stepAngleU;

				su = sinf(angleU);
				cu = cosf(angleU);

				x = sv * su;
				y = -cv;
				z = sv * cu;

				vertices.push_back(x * radius);
				vertices.push_back(y * radius);
				vertices.push_back(z * radius);

				normals.push_back(x);
				normals.push_back(y);
				normals.push_back(z);

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
		addAttribute("uvs", new BufferAttribute(uvs, 3));
	}
}