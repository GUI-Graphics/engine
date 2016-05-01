#pragma once

#include "core/BufferGeometry.h"

namespace engine
{
	class BoxBufferGeometry : public BufferGeometry
	{
	public:
		BoxBufferGeometry(
			float width		= 1.0f,
			float height	= 1.0f, 
			float depth		= 1.0f,
			int widthSegments	= 1, 
			int heightSegments	= 1, 
			int depthSegments	= 1);

	private:
		void buildPlane(char u, char v, float dir, float width, float height, float depth, int widthSegments, int heightSegments);

	public:
		float width;
		float height;
		float depth;
		int widthSegments;
		int heightSegments;
		int depthSegments;
	};
}
