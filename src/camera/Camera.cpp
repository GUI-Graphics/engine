#include "camera/Camera.h"

namespace engine
{
	void Camera::updateMatrixWorldInverse()
	{
		const float* b = matrixWorld.elements;
		float* a = matrixWorldInverse.elements;

		a[0] = b[0]; a[1] = b[4]; a[ 2] = b[ 8];
		a[4] = b[1]; a[5] = b[5]; a[ 6] = b[ 9];
		a[8] = b[2]; a[9] = b[6]; a[10] = b[10];

		Vector3 x(b[0], b[4], b[ 8]);
		Vector3 y(b[1], b[5], b[ 9]);
		Vector3 z(b[2], b[6], b[10]);
		Vector3 p = position();

		a[ 3] = -x.dot(p);
		a[ 7] = -y.dot(p);
		a[11] = -z.dot(p);
	}
}