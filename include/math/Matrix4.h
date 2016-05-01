#pragma once

namespace engine
{
	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(
			float x1, float x2, float x3, float x4,
			float y1, float y2, float y3, float y4,
			float z1, float z2, float z3, float z4,
			float w1, float w2, float w3, float w4);

		Matrix4 operator*(const Matrix4& matrix);

		void operator*=(const Matrix4& matrix)
		{
			*this = *this * matrix;
		}

	public:
		float elements[16];
	};
}
