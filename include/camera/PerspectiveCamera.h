#pragma once

#include "math/Math.h"
#include "Camera.h"

namespace engine
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fovy, float aspect, float nearPlane, float farPlane)
			: fovy(fovy), aspect(aspect), nearPlane(nearPlane), farPlane(farPlane)
		{
			projectMatrix.elements[14] = -1;
			updateProjectMatrix();
		}

		void updateProjectMatrix() override
		{
			float top = nearPlane * tanf(Math::radius(0.5f * fovy));
			float right = top * aspect;
			float k = 1 / (farPlane - nearPlane);

			float* e = projectMatrix.elements;

			e[0] = nearPlane / right;
			e[5] = nearPlane / top;
			e[10] = -(nearPlane + farPlane) * k;
			e[11] = -2 * nearPlane * farPlane * k;
		}

	public:
		float fovy;
		float aspect;
		float nearPlane;
		float farPlane;
	};
}