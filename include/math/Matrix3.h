#pragma once

#include "Matrix4.h"

namespace engine
{
	class Matrix3
	{
	public:
		Matrix3() : elements{ 1, 0, 0, 0, 1, 0, 0, 0, 1 }
		{ }

		Matrix3(
			float x1, float y1, float z1,
			float x2, float y2, float z2,
			float x3, float y3, float z3) : elements{ x1, y1, z1, x2, y2, z2, x3, y3, z3 }
		{ }

		Matrix3& transpose()
		{
			float tmp;
			tmp = elements[1]; elements[1] = elements[3]; elements[3] = tmp;
			tmp = elements[2]; elements[2] = elements[6]; elements[6] = tmp;
			tmp = elements[5]; elements[5] = elements[7]; elements[7] = tmp;

			return *this;
		}

		Matrix3& getNormalMatrix(const Matrix4& matrix)
		{
			return getInverse(matrix).transpose();
		}

		Matrix3& getInverse(const Matrix4& matrix);

	public:
		float elements[9];
	};
}
