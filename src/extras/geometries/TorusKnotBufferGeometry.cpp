#include "math\Math.h"
#include "extras\geometries\TorusKnotBufferGeometry.h"

namespace engine
{
	TorusKnotBufferGeometry::TorusKnotBufferGeometry(float radius, float tube, int radialSegments, int tubeSegments, float p, float q)
		: radius(radius)
		, tube(tube)
		, radialSegments(radialSegments)
		, tubeSegments(tubeSegments)
		, p(p)
		, q(q)
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
		float stepUAngle = stepU * Math::PI * 2 * p;
		float stepVAngle = stepV * Math::PI * 2;

		float u = -stepU;
		float v;

		float uAngle = -stepUAngle;
		float vAngle;

		for (int i = 0; i < r1; ++i)
		{
			u += stepU;
			v = -stepU;

			uAngle += stepUAngle;
			vAngle = -stepVAngle;

			Vector3 a = computePointOnCurve(uAngle);
			Vector3 b = computePointOnCurve(uAngle + 0.01f);

			Vector3 T = b - a;
			Vector3 N = a + b;
			Vector3 B = T.cross(N);

			N = B.cross(T);
			B.normalize();
			N.normalize();

			for (int j = 0; j < t1; ++j)
			{
				v += stepV;
				vAngle += stepVAngle;

				float sv = sinf(vAngle);
				float cv = cosf(vAngle);

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

	Vector3 TorusKnotBufferGeometry::computePointOnCurve(float angle)
	{
		float pa = p * angle;
		float qa = q * angle;
		float radius = 0.5f * (2 + sinf(qa)) * this->radius;
		return Vector3(radius * cosf(pa), radius * cosf(qa), radius * sinf(pa));
	}
}