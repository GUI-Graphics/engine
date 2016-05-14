#include "math\Math.h"
#include "extras\geometries\TorusKnot.h"

namespace engine
{
	TorusKnot::TorusKnot(float radius, float tube, int uSegments, int vSegments, float p, float q)
		: radius(radius)
		, tube(tube)
		, uSegments(uSegments)
		, vSegments(vSegments)
		, p(p)
		, q(q)
	{
		int u1 = uSegments + 1;
		int v1 = vSegments + 1;
		int vertexCount = u1 * v1;

		std::vector<float> vertices, normals, uvs;
		vertices.reserve(vertexCount * 3);
		normals.reserve(vertexCount * 3);
		uvs.reserve(vertexCount * 2);

		float stepU = 1.0f / uSegments;
		float stepV = 1.0f / vSegments;
		float stepAngleU = stepU * Math::PI * 2 * p;
		float stepAngleV = stepV * Math::PI * 2;

		float u = -stepU;
		float v;

		float angleU = -stepAngleU;
		float angleV;

		for (int i = 0; i < u1; ++i)
		{
			u += stepU;
			v = -stepU;

			angleU += stepAngleU;
			angleV = -stepAngleV;

			Vector3 a = computePointOnCurve(angleU);
			Vector3 b = computePointOnCurve(angleU + 0.01f);

			Vector3 T = b - a;
			Vector3 N = a + b;
			Vector3 B = T.cross(N);

			N = B.cross(T);
			B.normalize();
			N.normalize();

			for (int j = 0; j < v1; ++j)
			{
				v += stepV;
				angleV += stepAngleV;

				float sv = sinf(angleV);
				float cv = cosf(angleV);

				// normal = sv dot N add cv dot -B;

				float nx = sv * N.x - cv * B.x;
				float ny = sv * N.y - cv * B.y;
				float nz = sv * N.z - cv * B.z;

				normals.push_back(nx);
				normals.push_back(ny);
				normals.push_back(nz);

				vertices.push_back(a.x + nx * tube);
				vertices.push_back(a.y + ny * tube);
				vertices.push_back(a.z + nz * tube);

				uvs.push_back(u);
				uvs.push_back(v);
			}
		}

		indices.reserve(uSegments * vSegments * 6);

		unsigned int a = -1;
		unsigned int b;
		unsigned int c;
		unsigned int d;

		for (int i = 0; i < uSegments; ++i)
		{
			for (int j = 0; j < vSegments; ++j)
			{
				++a;
				b = a + v1;
				c = b + 1;
				d = a + 1;

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

	Vector3 TorusKnot::computePointOnCurve(float angle)
	{
		float pa = p * angle;
		float qa = q * angle;
		float radius = 0.5f * (2 + sinf(qa)) * this->radius;
		return Vector3(radius * cosf(pa), radius * cosf(qa), radius * sinf(pa));
	}
}