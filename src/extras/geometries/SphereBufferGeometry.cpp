#include "extras\geometries\SphereBufferGeometry.h"

namespace engine
{
	SphereBufferGeometry::SphereBufferGeometry(float radius, int phiSegments, int thetaSegments, float phiStart, float phiLength, float thetaStart, float thetaLength)
		: radius(radius)
		, phiSegments(phiSegments)
		, thetaSegments(thetaSegments)
		, phiStart(phiStart)
		, phiLength(phiLength)
		, thetaStart(thetaStart)
		, thetaLength(thetaLength)
	{
		float uvxStep = 1.0f / phiSegments;
		float uvyStep = 1.0f / thetaSegments;
		float phiStep = phiLength * uvxStep;
		float thetaStep = thetaLength * uvyStep;

		float uvx;
		float uvy = -uvyStep;

		float phi;
		float theta = -thetaStep + thetaStart;

		int vertexCount = (phiSegments + 1) * (thetaSegments + 1);
		std::vector<float> vertices, normals, uvs;
		vertices.reserve(vertexCount * 3);
		normals.reserve(vertexCount * 3);
		uvs.reserve(vertexCount * 2);

		for (int j = 0; j <= thetaSegments; ++j)
		{
			uvx = -uvxStep;
			uvy += uvyStep;

			phi = -phiStep + phiStart;
			theta += thetaStep;

			for (int i = 0; i <= phiSegments; ++i)
			{
				uvx += uvxStep;
				phi += phiStep;

				float cp = cosf(phi);
				float sp = sinf(phi);
				float st = sinf(theta);
				float ct = cosf(theta);

				float x = st * cp;
				float y = ct;
				float z = -st * sp;

				vertices.push_back(x * radius);
				vertices.push_back(y * radius);
				vertices.push_back(z * radius);

				normals.push_back(x);
				normals.push_back(y);
				normals.push_back(z);

				uvs.push_back(uvx);
				uvs.push_back(uvy);
			}
		}

		for (int j = 0; j < thetaSegments; ++j)
		{
			for (int i = 0; i < phiSegments; ++i)
			{
				unsigned int a = j * (phiSegments + 1) + i;
				unsigned int b = a + 1;
				unsigned int c = b + phiSegments + 1;
				unsigned int d = c - 1;

				indices.push_back(d);
				indices.push_back(c);
				indices.push_back(a);
				indices.push_back(c);
				indices.push_back(b);
				indices.push_back(a);
			}
		}

		addAttribute("position", new BufferAttribute(vertices, 3));
		addAttribute("normal", new BufferAttribute(normals, 3));
		addAttribute("uvs", new BufferAttribute(uvs, 3));
	}
}