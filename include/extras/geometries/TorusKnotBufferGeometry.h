#pragma once

#include "math\Vector3.h"
#include "core\BufferGeometry.h"

namespace engine
{
	// @see: http://www.blackpawn.com/texts/pqtorus/ for more details

	class TorusKnotBufferGeometry : public BufferGeometry
	{
	public:
		TorusKnotBufferGeometry(
			float radius = 1, 
			float tube = 0.3f, 
			int   radialSegments = 120,
			int   tubeSegments = 6,
			float p = 2, 
			float q = 3);

	private:
		Vector3 computePointOnCurve(float angle);

	public:
		float radius;
		float tube;
		int   radialSegments;
		int   tubeSegments;
		float p;
		float q;
	};
}