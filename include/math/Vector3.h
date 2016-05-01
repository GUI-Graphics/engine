#pragma once

#include <math.h>
#include "Matrix4.h"

namespace engine
{
	class Vector3
	{
	public:
		Vector3()
		{ }

		Vector3(float x, float y, float z) : x(x), y(y), z(z)
		{ }

		Vector3 Vector3::operator+(float k) const
		{
			return Vector3(x + k, y + k, z + k);
		}

		Vector3 Vector3::operator-(float k) const
		{
			return Vector3(x - k, y - k, z - k);
		}

		Vector3 Vector3::operator*(float k) const
		{
			return Vector3(x * k, y * k, z * k);
		}

		Vector3 Vector3::operator/(float k) const
		{
			k = 1 / k;
			return Vector3(x * k, y * k, z * k);
		}

		void Vector3::operator+=(float k)
		{
			x += k;
			y += k;
			z += k;
		}

		void Vector3::operator-=(float k)
		{
			x -= k;
			y -= k;
			z -= k;
		}

		void Vector3::operator*=(float k)
		{
			x *= k;
			y *= k;
			z *= k;
		}

		void Vector3::operator/=(float k)
		{
			k = 1 / k;
			x *= k;
			y *= k;
			z *= k;
		}

		Vector3 Vector3::operator+(const Vector3& v) const
		{
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		Vector3 Vector3::operator-(const Vector3& v) const
		{
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		Vector3 Vector3::operator*(const Vector3& v) const
		{
			return Vector3(x * v.x, y * v.y, z * v.z);
		}

		Vector3 Vector3::operator/(const Vector3& v) const
		{
			return Vector3(x / v.x, y / v.y, z / v.z);
		}

		void Vector3::operator+=(const Vector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		void Vector3::operator-=(const Vector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		void Vector3::operator*=(const Vector3& v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
		}

		void Vector3::operator/=(const Vector3& v)
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;
		}

		Vector3 operator-() const
		{
			return Vector3(-x, -y, -z);
		}

		bool operator==(const Vector3& v) const
		{
			return x == v.x && y == v.y && z == v.z;
		}

		bool operator!=(const Vector3& v) const
		{
			return x != v.x || y != v.y || z != v.z;
		}

		Vector3 cross(const Vector3& v) const
		{
			return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
		}

		Vector3 lerp(const Vector3& v, float alpha) const
		{
			return Vector3(x + (v.x - x) * alpha, y + (v.y - y) * alpha, z + (v.z - z) * alpha);
		}

		float length() const
		{
			return sqrtf(x * x + y * y + z * z);
		}

		float lengthSquared() const
		{
			return x * x + y * y + z * z;
		}

		float lengthManhattan() const
		{
			return fabsf(x) + fabsf(y) + fabsf(z);
		}

		float dot(const Vector3& v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}

		float distanceTo(const Vector3& v) const
		{
			float distX = x - v.x;
			float distY = y - v.y;
			float distZ = z - v.z;

			return sqrtf(distX * distX + distY * distY + distZ * distZ);
		}

		float distanceToSquared(const Vector3& v) const
		{
			float distX = x - v.x;
			float distY = y - v.y;
			float distZ = z - v.z;

			return distX * distX + distY * distY + distZ * distZ;
		}

		Vector3& set(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;

			return *this;
		}

		Vector3& setLength(float length)
		{
			float k = length / this->length();

			x *= k;
			y *= k;
			z *= k;

			return *this;
		}

		Vector3& negate()
		{
			x = -x;
			y = -y;
			z = -z;

			return *this;
		}

		Vector3& normalize()
		{
			float k = 1 / length();
			x *= k;
			y *= k;
			z *= k;

			return *this;
		}

		Vector3& applyMatrix(const Matrix4& matrix)
		{
			const float* e = matrix.elements;

			float tx = e[0] * x + e[1] * y + e[ 2] * z + e[ 3];
			float ty = e[4] * x + e[5] * y + e[ 6] * z + e[ 7];
			float tz = e[8] * x + e[9] * y + e[10] * z + e[11];

			x = tx;
			y = ty;
			z = tz;

			return *this;
		}

		Vector3& applyProjection(const Matrix4& matrix)
		{
			const float* e = matrix.elements;
			float d = 1 / (e[12] * x + e[13] * y + e[14] * z + e[15]);

			float tx = (e[0] * x + e[1] * y + e[ 2] * z + e[ 3]) * d;
			float ty = (e[4] * x + e[5] * y + e[ 6] * z + e[ 7]) * d;
			float tz = (e[8] * x + e[9] * y + e[10] * z + e[11]) * d;

			x = tx;
			y = ty;
			z = tz;

			return *this;
		}

	public:
		float x;
		float y;
		float z;
	};
}

