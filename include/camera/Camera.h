#pragma once

#include "core/Object3D.h"

namespace engine
{
	class Camera : public Object3D
	{
	public:
		Camera()
		{ }

		void setScaleX(float scale) = delete;
		void setScaleY(float scale) = delete;
		void setScaleZ(float scale) = delete;
		void setScale(float scaleX, float scaleY, float scaleZ) = delete;

	protected:
		void updateMatrixWorldInverse();
		virtual void updateProjectMatrix() = 0;

	public:
		Matrix4 projectMatrix;
		Matrix4 matrixWorldInverse;

		friend class GLRenderer;
	};
}