#pragma once

#include "math\Vector3.h"
#include "core\BufferGeometry.h"

namespace engine
{
	// @see: http://www.blackpawn.com/texts/pqtorus/ for more details

	class TorusKnot : public BufferGeometry
	{
	public:
		TorusKnot(
			float radius = 1, 
			float tube = 0.3f, 
			int   uSegments = 120,
			int   vSegments = 6,
			float p = 2, 
			float q = 3);

	private:
		Vector3 computePointOnCurve(float angle);

	public:
		float radius;
		float tube;
		int   uSegments;
		int   vSegments;
		float p;
		float q;
	};
}