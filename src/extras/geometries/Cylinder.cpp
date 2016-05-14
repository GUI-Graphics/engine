#include "extras\geometries\Cylinder.h"

namespace engine
{
	Cylinder::Cylinder(
		float radiusTop,
		float radiusBottom,
		float height,
		int   radialSegments,
		int   heightSegments,
		bool  openEnded,
		float thetaStart,
		float thetaLength)
		: radiusTop(radiusTop)
		, radiusBottom(radiusBottom)
		, height(height)
		, radialSegments(radialSegments)
		, heightSegments(heightSegments)
		, openEnded(openEnded)
		, thetaStart(thetaStart)
		, thetaLength(thetaLength)
	{
		int r1 = radialSegments + 1;
		int h1 = heightSegments + 1;

		int vertexCount = r1 * h1;
		int indexCount = radialSegments * heightSegments * 6;

		if (!openEnded)
		{
			vertexCount += (r1 + 1) * 2;
			indexCount += radialSegments * 6;
		}

		std::vector<float> vertices, normals, uvs;
		vertices.reserve(vertexCount * 3);
		normals.reserve(vertexCount * 3);
		uvs.reserve(vertexCount * 2);
	}
}