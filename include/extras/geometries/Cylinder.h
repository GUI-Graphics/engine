#pragma once

#include <math\Math.h>
#include <core\BufferGeometry.h>

namespace engine
{
	/**  Create a Cylinder Geometry
	 *   @param radiusBottom and @param radiusBottom
	 *
	 */
	class Cylinder : public BufferGeometry
	{
	public:
		Cylinder(
			float radiusTop			= 1,
			float radiusBottom		= 1,
			float height			= 1,
			int   radialSegments	= 8,
			int   heightSegments	= 1,
			bool  openEnded			= false,
			float thetaStart		= 0,
			float thetaLength		= Math::PI * 2);

	public:
		bool  openEnded;
		float radiusTop;
		float radiusBottom;
		float height;
		int   radialSegments;
		int   heightSegments;
		float thetaStart;
		float thetaLength;
	};
}