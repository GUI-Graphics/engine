#pragma once

#include <stdlib.h>

namespace engine
{
	class Math
	{
	public:
		static float degree(float radius)
		{
			return radius / PI * 180.0f;
		}

		static float radius(float degree)
		{
			return degree * PI / 180.0f;
		}

		static float random()
		{
			return (float)rand() / RAND_MAX;
		}

		static const float PI;
	};
}

