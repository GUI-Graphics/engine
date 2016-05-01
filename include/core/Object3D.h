#pragma once

#include <list>
#include <vector>

#include "math/Vector3.h"
#include "math/Matrix3.h"

namespace engine
{
	class Object3D
	{
	public:
		Object3D()
			: visible(true)
			, matrixWorldNeedsUpdate(false)
			, parent(nullptr)
			, scale(1.0f, 1.0f, 1.0f)
		{ }

		virtual ~Object3D()
		{ }

		Vector3 position() const
		{
			return Vector3(matrix.elements[3], matrix.elements[7], matrix.elements[11]);
		}

		void Object3D::setScaleX(float s)
		{
			float k = s / scale.x;
			scale.x = s;

			matrix.elements[0] *= k;
			matrix.elements[4] *= k;
			matrix.elements[8] *= k;

			matrixWorldNeedsUpdate = true;
		}

		void Object3D::setScaleY(float s)
		{
			float k = s / scale.y;
			scale.y = s;

			matrix.elements[1] *= k;
			matrix.elements[5] *= k;
			matrix.elements[9] *= k;

			matrixWorldNeedsUpdate = true;
		}

		void Object3D::setScaleZ(float s)
		{
			float k = s / scale.z;
			scale.z = s;

			matrix.elements[2] *= k;
			matrix.elements[6] *= k;
			matrix.elements[10] *= k;

			matrixWorldNeedsUpdate = true;
		}

		void setScale(float x, float y, float z);

		void Object3D::positionX(float dist)
		{
			matrix.elements[3] = dist;
			matrixWorldNeedsUpdate = true;
		}

		void Object3D::positionY(float dist)
		{
			matrix.elements[7] = dist;
			matrixWorldNeedsUpdate = true;
		}

		void Object3D::positionZ(float dist)
		{
			matrix.elements[11] = dist;
			matrixWorldNeedsUpdate = true;
		}

		inline void Object3D::position(float x, float y, float z)
		{
			matrix.elements[3] = x;
			matrix.elements[7] = y;
			matrix.elements[11] = z;

			matrixWorldNeedsUpdate = true;
		}

		void rotateX(float angle);
		void rotateY(float angle);
		void rotateZ(float angle);
		void rotateOnAxis(const Vector3& axis, float angle);
		void rotation(float rotateY, float rotateX, float rotateZ);

		void translateX(float dist);
		void translateY(float dist);
		void translateZ(float dist);
		void translateOnAxis(const Vector3& direction, float dist);

		void lookAt(const Vector3& target);

		void add(Object3D* object);
		void remove(Object3D* object);

		Object3D* getObjectById(unsigned int id);
		std::vector<Object3D*> getObjectsByName(std::string name);

	protected:
		void updateMatrixWorld();

	public:
		bool visible;
		bool globalTransform;

		unsigned int id;
		std::string	name;

		Vector3 scale;
		Matrix4	matrix;
		Matrix4	matrixWorld;

		Object3D* parent;
		std::list<Object3D*> children;

	private:
		bool matrixWorldNeedsUpdate;
		Matrix3 normalMatrix;
		Matrix4 modelViewMatrix;

		friend class GLRenderer;
	};
}
