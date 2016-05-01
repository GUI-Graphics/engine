#include "math/Matrix4.h"

namespace engine
{
	Matrix4::Matrix4() : elements{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	} { }

	Matrix4::Matrix4(
		float x1, float x2, float x3, float x4,
		float y1, float y2, float y3, float y4,
		float z1, float z2, float z3, float z4,
		float w1, float w2, float w3, float w4) : elements{
		x1, x2, x3, x4,
		y1, y2, y3, y4,
		z1, z2, z3, z4,
		w1, w2, w3, w4,
	} { }

	Matrix4 Matrix4::operator*(const Matrix4& matrix)
	{
		const float* a = elements;
		const float* b = matrix.elements;

		return Matrix4(
			a[ 0] * b[0] + a[ 1] * b[4] + a[ 2] * b[ 8] + a[ 3] * b[12],
			a[ 0] * b[1] + a[ 1] * b[5] + a[ 2] * b[ 9] + a[ 3] * b[13],
			a[ 0] * b[2] + a[ 1] * b[6] + a[ 2] * b[10] + a[ 3] * b[14],
			a[ 0] * b[3] + a[ 1] * b[7] + a[ 2] * b[11] + a[ 3] * b[15],

			a[ 4] * b[0] + a[ 5] * b[4] + a[ 6] * b[ 8] + a[ 7] * b[12],
			a[ 4] * b[1] + a[ 5] * b[5] + a[ 6] * b[ 9] + a[ 7] * b[13],
			a[ 4] * b[2] + a[ 5] * b[6] + a[ 6] * b[10] + a[ 7] * b[14],
			a[ 4] * b[3] + a[ 5] * b[7] + a[ 6] * b[11] + a[ 7] * b[15],

			a[ 8] * b[0] + a[ 9] * b[4] + a[10] * b[ 8] + a[11] * b[12],
			a[ 8] * b[1] + a[ 9] * b[5] + a[10] * b[ 9] + a[11] * b[13],
			a[ 8] * b[2] + a[ 9] * b[6] + a[10] * b[10] + a[11] * b[14],
			a[ 8] * b[3] + a[ 9] * b[7] + a[10] * b[11] + a[11] * b[15],

			a[12] * b[0] + a[13] * b[4] + a[14] * b[ 8] + a[15] * b[12],
			a[12] * b[1] + a[13] * b[5] + a[14] * b[ 9] + a[15] * b[13],
			a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14],
			a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15]
		);
	}
}