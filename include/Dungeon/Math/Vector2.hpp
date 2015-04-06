#ifndef DUNGEON_MATH_VECTOR2_HPP
#define DUNGEON_MATH_VECTOR2_HPP

#include <Dungeon/Types.hpp>
#include <cmath>

namespace Dungeon
{
	struct Vector2
	{
		Vector2()
			: x(0)
			, y(0)
		{
		}

		explicit Vector2(Float32 xy)
			: x(xy)
			, y(xy)
		{
		}

		Vector2(Float32 x, Float32 y)
			: x(x)
			, y(y)
		{
		}

		Vector2(Float32 xy[2])
			: x(xy[0])
			, y(xy[1])
		{
		}

		Float32 &operator[](Size index)
		{
			return data[index];
		}
		const Float32 &operator[](Size index) const
		{
			return data[index];
		}

		Vector2 operator+(const Vector2 &other) const
		{
			return Vector2(x + other.x, y + other.y);
		}

		Vector2 operator-(const Vector2 &other) const
		{
			return Vector2(x - other.x, y - other.y);
		}

		Vector2 operator*(Float32 scalar) const
		{
			return Vector2(scalar * x, scalar * y);
		}

		Vector2 operator/(Float32 scalar) const
		{
			return Vector2(x / scalar, y / scalar);
		}

		Vector2 &operator+=(const Vector2 &other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		Vector2 &operator-=(const Vector2 &other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		Vector2 &operator*=(Float32 scalar)
		{
			x *= scalar;
			y *= scalar;

			return *this;
		}

		Vector2 &operator/=(Float32 scalar)
		{
			x /= scalar;
			y /= scalar;

			return *this;
		}

		union
		{
			Float32 data[2];
			struct
			{
				Float32 x, y;
			};
			struct
			{
				Float32 r, g;
			};
			struct
			{
				Float32 s, t;
			};
		};
	};

	Vector2 operator*(Float32 scalar, const Vector2 &vector)
	{
		return vector * scalar;
	}

	Float32 dot(const Vector2& a, const Vector2 &b)
	{
		return a.x * b.x + a.y * b.y;
	}

	Float32 cross(const Vector2& a, const Vector2 &b)
	{
		return a.x * b.y - b.x * a.y;
	}

	Float32 lengthSquared(const Vector2 &a)
	{
		return dot(a, a);
	}

	Float32 length(const Vector2& a)
	{
		return std::sqrtf(lengthSquared(a));
	}

	Vector2 normalized(const Vector2& a)
	{
		return a  * (1.0f / length(a));
	}
}

#endif
