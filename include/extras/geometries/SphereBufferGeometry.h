#pragma once

#include "math\Math.h"
#include "core\BufferGeometry.h"

namespace engine
{
	class SphereBufferGeometry : public BufferGeometry
	{
	public:
		// 构造球体几何，phi代表纬度，theta代表经度
		SphereBufferGeometry(
			float radius		= 1.0f,				
			  int phiSegments	= 12,
			  int thetaSegments = 6,
			float phiStart		= 0,
			float phiLength		= Math::PI * 2,
			float thetaStart	= 0.0f,
			float thetaLength	= Math::PI
		);

	public:
		float radius;
		  int phiSegments;
		  int thetaSegments;
		float phiStart;
		float phiLength;
		float thetaStart;
		float thetaLength;
	};
}