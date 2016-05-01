#include <math.h>
#include "core\Object3D.h"

namespace engine
{
	void Object3D::setScale(float x, float y, float z)
	{
		float kx = x / scale.x;
		float ky = y / scale.y;
		float kz = z / scale.z;

		float* e = matrix.elements;

		e[0] *= kx; e[1] *= ky; e[ 2] *= kz;
		e[4] *= kx; e[5] *= ky; e[ 6] *= kz;
		e[8] *= kx; e[9] *= ky; e[10] *= kz;

		scale.x = x;
		scale.y = y;
		scale.z = z;

		matrixWorldNeedsUpdate = true;
	}

	void Object3D::rotation(float rotateY, float rotateX, float rotateZ)
	{
		float sx = sinf(rotateX), cx = cosf(rotateX);
		float sy = sinf(rotateY), cy = cosf(rotateY);
		float sz = sinf(rotateZ), cz = cosf(rotateZ);

		float cycz = cy * cz;
		float sycz = sy * cz;
		float cysz = cy * sz;
		float sysz = sy * sz;

		float* e = matrix.elements;

		if (!globalTransform)
		{
			e[0] = (sx * sysz + cycz) * scale.x;
			e[4] = (cx * sz) * scale.x;
			e[8] = (sx * cysz - sycz) * scale.x;

			e[1] = (sx * sycz - cysz) * scale.y;
			e[5] = (cx * cz) * scale.y;
			e[9] = (sx * cycz + sysz) * scale.y;

			e[2] = cx * sy * scale.z;
			e[6] = -sx * scale.z;
			e[10] = cx * cy * scale.z;
		}
		else
		{
			e[0] = (cycz - sx * sysz) * scale.x;
			e[4] = (cysz + sx * sycz) * scale.x;
			e[8] = -cx * sy * scale.x;

			e[1] = -cx * sz * scale.y;
			e[5] = cx * cz * scale.y;
			e[9] = sx * scale.y;

			e[2] = (sycz + sx * cysz) * scale.z;
			e[6] = (sysz - sx * cycz) * scale.z;
			e[10] = cx * cy * scale.z;
		}

		matrixWorldNeedsUpdate = true;
	}

	inline void Object3D::translateX(float dist)
	{
		float* e = matrix.elements;

		if (!globalTransform)
		{
			float k = dist / scale.x;

			e[3] += e[0] * k;
			e[7] += e[4] * k;
			e[11] += e[8] * k;
		}
		else
		{
			e[3] += dist;
		}

		matrixWorldNeedsUpdate = true;
	}

	void Object3D::translateY(float dist)
	{
		float* e = matrix.elements;

		if (!globalTransform)
		{
			float k = dist / scale.y;

			e[3] += e[1] * k;
			e[7] += e[5] * k;
			e[11] += e[9] * k;
		}
		else
		{
			e[7] += dist;
		}

		matrixWorldNeedsUpdate = true;
	}

	void Object3D::translateZ(float dist)
	{
		float* e = matrix.elements;

		if (!globalTransform)
		{
			float k = dist / scale.z;

			e[3] += e[2] * k;
			e[7] += e[6] * k;
			e[11] += e[10] * k;
		}
		else
		{
			e[11] += dist;
		}

		matrixWorldNeedsUpdate = true;
	}

	void Object3D::rotateX(float angle)
	{
		float s = sinf(angle);
		float c = cosf(angle);
		float* e = matrix.elements;

		if (!globalTransform)
		{
			float k = scale.y / scale.z;

			float bx = e[1], cx = e[ 2];
			float by = e[5], cy = e[ 6];
			float bz = e[9], cz = e[10];

			e[1] = bx * c + cx * s * k;
			e[5] = by * c + cy * s * k;
			e[9] = bz * c + cz * s * k;

			k = 1 / k;

			e[2] = cx * c - bx * s * k;
			e[6] = cy * c - by * s * k;
			e[10] = cz * c - bz * s * k;
		}
		else
		{
			float a = e[4];
			float b = e[8];
			e[4] = a * c - b * s;
			e[8] = a * s + b * c;

			a = e[5];
			b = e[9];
			e[5] = a * c - b * s;
			e[9] = a * s + b * c;

			a = e[ 6];
			b = e[10];
			e[6] = a * c - b * s;
			e[10] = a * s + b * c;
		}

		matrixWorldNeedsUpdate = true;
	}

	void Object3D::rotateY(float angle)
	{
		float s = sinf(angle);
		float c = cosf(angle);
		float* e = matrix.elements;

		if (!globalTransform)
		{
			float k = scale.x / scale.z;

			float ax = e[0], cx = e[2];
			float ay = e[4], cy = e[6];
			float az = e[8], cz = e[10];

			e[0] = ax * c - cx * s * k;
			e[4] = ay * c - cy * s * k;
			e[8] = az * c - cz * s * k;

			k = 1 / k;

			e[2] = cx * c + ax * s * k;
			e[6] = cy * c + ay * s * k;
			e[10] = cz * c + az * s * k;
		}
		else
		{
			float a = e[0];
			float b = e[8];
			e[0] = a * c + b * s;
			e[8] = b * c - a * s;

			a = e[1];
			b = e[9];
			e[1] = a * c + b * s;
			e[9] = b * c - a * s;

			a = e[2];
			b = e[10];
			e[2] = a * c + b * s;
			e[10] = b * c - a * s;
		}

		matrixWorldNeedsUpdate = true;
	}

	void Object3D::rotateZ(float angle)
	{
		float s = sinf(angle);
		float c = cosf(angle);
		float* e = matrix.elements;

		if (!globalTransform)
		{
			float k = scale.x / scale.y;

			float ax = e[0], bx = e[1];
			float ay = e[4], by = e[5];
			float az = e[8], bz = e[9];

			e[0] = ax * c + bx * s * k;
			e[4] = ay * c + by * s * k;
			e[8] = az * c + bz * s * k;

			k = 1 / k;

			e[1] = bx * c - ax * s * k;
			e[5] = by * c - ay * s * k;
			e[9] = bz * c - az * s * k;
		}
		else
		{
			float a = e[0];
			float b = e[4];
			e[0] = a * c - b * s;
			e[4] = a * s + b * c;

			a = e[1];
			b = e[5];
			e[1] = a * c - b * s;
			e[5] = a * s + b * c;

			a = e[2];
			b = e[6];
			e[2] = a * c - b * s;
			e[6] = a * s + b * c;
		}

		matrixWorldNeedsUpdate = true;
	}

	void Object3D::rotateOnAxis(const Vector3& axis, float angle)
	{
		float s = sinf(angle);
		float c = cosf(angle);
		float c1 = 1 - c;

		float xs = axis.x * s;
		float ys = axis.y * s;
		float zs = axis.z * s;

		float xc1 = axis.x * c1;
		float yc1 = axis.y * c1;
		float zc1 = axis.z * c1;

		float* e = matrix.elements;

		float a[9] = {
			xc1 * axis.x + c, yc1 * axis.x + zs, zc1 * axis.x - ys,
			xc1 * axis.y - zs, yc1 * axis.y + c, zc1 * axis.y + xs,
			xc1 * axis.z + ys, yc1 * axis.z - xs, zc1 * axis.z + c
		};

		float b[9] = {
			e[0], e[1], e[2],
			e[4], e[5], e[6],
			e[8], e[9], e[10]
		};

		e[0] = a[0] * b[0] + a[1] * b[3] + a[2] * b[6];
		e[4] = a[3] * b[0] + a[4] * b[3] + a[5] * b[6];
		e[8] = a[6] * b[0] + a[7] * b[3] + a[8] * b[6];

		e[1] = a[0] * b[1] + a[1] * b[4] + a[2] * b[7];
		e[5] = a[3] * b[1] + a[4] * b[4] + a[5] * b[7];
		e[9] = a[6] * b[1] + a[7] * b[4] + a[8] * b[7];

		e[ 2] = a[0] * b[2] + a[1] * b[5] + a[2] * b[8];
		e[ 6] = a[3] * b[2] + a[4] * b[5] + a[5] * b[8];
		e[10] = a[6] * b[2] + a[7] * b[5] + a[8] * b[8];

		matrixWorldNeedsUpdate = true;
	}

	void Object3D::translateOnAxis(const Vector3& axis, float dist)
	{
		float* e = matrix.elements;

		if (!globalTransform)
		{
			float kx = dist * axis.x / scale.x;
			float ky = dist * axis.y / scale.y;
			float kz = dist * axis.z / scale.z;

			e[ 3] += (e[0] * kx + e[1] * ky + e[2] * kz);
			e[ 7] += (e[4] * kx + e[5] * ky + e[6] * kz);
			e[11] += (e[8] * kx + e[9] * ky + e[10] * kz);
		}
		else
		{
			e[ 3] += axis.x * dist;
			e[ 7] += axis.x * dist;
			e[11] += axis.x * dist;
		}

		matrixWorldNeedsUpdate = true;
	}

	void Object3D::lookAt(const Vector3& target)
	{
		float* e = matrix.elements;
		Vector3 eye(e[3], e[7], e[11]);
		Vector3 z = eye - target;
		z.normalize();
		Vector3 x = Vector3(0, 1, 0).cross(z);
		x.normalize();
		Vector3 y = z.cross(x);

		e[0] = x.x * scale.x;
		e[4] = x.y * scale.x;
		e[8] = x.z * scale.x;

		e[1] = y.x * scale.y;
		e[5] = y.y * scale.y;
		e[9] = y.z * scale.y;

		e[ 2] = z.x * scale.z;
		e[ 6] = z.y * scale.z;
		e[10] = z.z * scale.z;

		matrixWorldNeedsUpdate = true;
	}

	void Object3D::updateMatrixWorld()
	{
		if (matrixWorldNeedsUpdate)
		{
			if (!parent)
			{
				matrixWorld = matrix;
			}
			else
			{
				matrixWorld = parent->matrixWorld * matrix;
			}

			matrixWorldNeedsUpdate = false;
		}

		for (auto child : children)
		{
			child->updateMatrixWorld();
		}
	}

	void Object3D::add(Object3D* object)
	{
		if (object->parent)
		{
			object->parent->remove(object);
		}

		object->parent = this;
		children.push_back(object);
	}

	void Object3D::remove(Object3D* object)
	{
		if (object->parent == this)
		{
			auto itr = std::find(children.begin(), children.end(), object);
			children.erase(itr);
			object->parent = nullptr;
		}
		else
		{
			for (auto child : children)
			{
				child->remove(object);
				if (!object->parent) return;
			}
		}
	}

	Object3D* Object3D::getObjectById(unsigned int id)
	{
		if (this->id == id) return this;

		for (auto child : children)
		{
			auto obj = child->getObjectById(id);
			if (obj) return obj;
		}

		return nullptr;
	}

	std::vector<Object3D*> Object3D::getObjectsByName(std::string name)
	{
		std::vector<Object3D*> result;
		if (this->name == name) result.push_back(this);

		for (auto child : children)
		{
			auto objects = child->getObjectsByName(name);
			for (auto obj : objects)
			{
				objects.push_back(obj);
			}
		}

		return result;
	}
}