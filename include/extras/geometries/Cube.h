#pragma once

#include "core/BufferGeometry.h"

namespace engine
{
	class Cube : public BufferGeometry
	{
	public:
		Cube(float length = 1);

	public:
		float length;
	};
}