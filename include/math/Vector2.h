#pragma once

#include <math.h>

namespace engine
{
	class Vector2
	{
	public:
		Vector2()
		{ }

		Vector2(float x, float y) : x(x), y(y)
		{ }

		Vector2 operator+(float s) const
		{
			return Vector2(x + s, y + s);
		}

		Vector2 operator-(float s) const
		{
			return Vector2(x - s, y - s);
		}

		Vector2 operator*(float s) const
		{
			return Vector2(x * s, y * s);
		}

		Vector2 operator/(float s) const
		{
			return Vector2(x / s, y / s);
		}

		void operator+=(float s)
		{
			x += s;
			y += s;
		}

		void operator-=(float s)
		{
			x -= s;
			y -= s;
		}

		void operator*=(float s)
		{
			x *= s;
			y *= s;
		}

		void operator/=(float s)
		{
			x /= s;
			y /= s;
		}

		Vector2 operator+(const Vector2& v) const
		{
			return Vector2(x + v.x, y + v.y);
		}

		Vector2 operator-(const Vector2& v) const
		{
			return Vector2(x - v.x, y - v.y);
		}

		Vector2 operator*(const Vector2& v) const
		{
			return Vector2(x * v.x, y * v.y);
		}

		Vector2 operator/(const Vector2& v) const
		{
			return Vector2(x / v.x, y / v.y);
		}

		void operator+=(const Vector2& v)
		{
			x += v.x;
			y += v.y;
		}

		void operator-=(const Vector2& v)
		{
			x -= v.x;
			y -= v.y;
		}

		void operator*=(const Vector2& v)
		{
			x *= v.x;
			y *= v.y;
		}

		void operator/=(const Vector2& v)
		{
			x /= v.x;
			y /= v.y;
		}

		Vector2 operator-() const
		{
			return Vector2(-x, -y);
		}

		bool operator==(const Vector2& v) const
		{
			return x == v.x && y == v.y;
		}

		bool operator!=(const Vector2& v) const
		{
			return x != v.x || y != v.y;
		}

		Vector2 lerp(const Vector2& v, float alpha) const
		{
			return Vector2(x + (v.x - x) * alpha, y + (v.y - y) * alpha);
		}

		float length() const
		{
			return sqrtf(lengthSquared());
		}

		float lengthSquared() const
		{
			return x * x + y * y;
		}

		float lengthManhattan() const
		{
			return fabsf(x) + fabsf(y);
		}

		float dot(const Vector2& v) const
		{
			return x * v.x + y * v.y;
		}

		float distanceTo(const Vector2& v) const
		{
			return Vector2(x - v.x, y - v.y).length();
		}

		float distanceToSquared(const Vector2& v) const
		{
			return Vector2(x - v.x, y - v.y).lengthSquared();
		}

		Vector2& set(float x, float y)
		{
			this->x = x;
			this->y = y;
			return *this;
		}

		Vector2& setLength(float length)
		{
			float k = length / this->length();
			x *= k;
			y *= k;
			return *this;
		}

		Vector2& negate()
		{
			x = -x;
			y = -y;
			return *this;
		}

		Vector2& normalize()
		{
			x /= length();
			y /= length();
			return *this;
		}

	public:
		float x;
		float y;
	};
}

