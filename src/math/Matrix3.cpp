#include "math\Matrix3.h"

namespace engine
{
	class Matrix3& Matrix3::getInverse(const Matrix4& matrix)
	{
		const float* me = matrix.elements;
		float* te = elements;

		te[0] =  me[10] * me[5] - me[6] * me[9];
		te[1] = -me[10] * me[1] + me[2] * me[9];
		te[2] =  me[ 6] * me[1] - me[2] * me[5];
		te[3] = -me[10] * me[4] + me[6] * me[8];
		te[4] =  me[10] * me[0] - me[2] * me[8];
		te[5] = -me[ 6] * me[0] + me[2] * me[4];
		te[6] =  me[ 9] * me[4] - me[5] * me[8];
		te[7] = -me[ 9] * me[0] + me[1] * me[8];
		te[8] =  me[ 5] * me[0] - me[1] * me[4];

		float det = 1 / (me[0] * te[0] + me[1] * te[3] + me[2] * te[6]);

		for (auto& e : elements)
		{
			e *= det;
		}

		return *this;
	}
}