#ifndef DUNGEON_MATH_VECTOR3_HPP
#define DUNGEON_MATH_VECTOR3_HPP

#include <Dungeon/Types.hpp>
#include <cmath>

#include <Dungeon/Math/Vector2.hpp>

namespace Dungeon
{
	struct Vector3
	{
		Vector3()
			: x(0)
			, y(0)
			, z(0)
		{
		}

		explicit Vector3(Float32 xyz)
			: x(xyz)
			, y(xyz)
			, z(xyz)
		{
		}

		Vector3(Float32 x, Float32 y, Float32 z)
			: x(x)
			, y(y)
			, z(z)
		{
		}

		Vector3(Float32 xyz[3])
			: x(xyz[0])
			, y(xyz[1])
			, z(xyz[2])
		{
		}

		explicit Vector3(const Vector2 &other, Float32 z)
			: Vector3(other.x, other.y, z)
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

		Vector3 operator+(const Vector3 &other) const
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}

		Vector3 operator-(const Vector3 &other) const
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}

		Vector3 operator*(Float32 scalar) const
		{
			return Vector3(scalar * x, scalar * y, scalar * z);
		}

		Vector3 operator/(Float32 scalar) const
		{
			return Vector3(x / scalar, y / scalar, z / scalar);
		}

		Vector3 &operator+=(const Vector3 &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		Vector3 &operator-=(const Vector3 &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		Vector3 &operator*=(Float32 scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		Vector3 &operator/=(Float32 scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}

		union
		{
			Float32 data[3];
			struct
			{
				Float32 x, y, z;
			};
			struct
			{
				Float32 r, g, b;
			};
			struct
			{
				Float32 s, t, p;
			};
		};
	};

	inline Vector3 operator*(Float32 scalar, const Vector3 &vector)
	{
		return vector * scalar;
	}

	inline Float32 dot(const Vector3 &a, const Vector3 &b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	inline Vector3 cross(const Vector3 &a, const Vector3 &b)
	{
		Float32 x = a.y * b.z - b.y * a.z;
		Float32 y = a.z * b.x - b.z * a.x;
		Float32 z = a.x * b.y - b.x * a.y;
		return Vector3(x, y, z);
	}

	inline Float32 lengthSquared(const Vector3 &a)
	{
		return dot(a, a);
	}

	inline Float32 length(const Vector3 &a)
	{
		return std::sqrtf(lengthSquared(a));
	}

	inline Vector3 normalized(const Vector3 &a)
	{
		return a * (1.0f / length(a));
	}
}

#endif
