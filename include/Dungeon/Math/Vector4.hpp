#ifndef DUNGEON_MATH_VECTOR4_HPP
#define DUNGEON_MATH_VECTOR4_HPP

#include <Dungeon/Types.hpp>
#include <cmath>

#include <Dungeon/Math/Vector2.hpp>
#include <Dungeon/Math/Vector3.hpp>

namespace Dungeon
{
	struct Vector4
	{
		Vector4()
			: x(0)
			, y(0)
			, z(0)
		{
		}

		explicit Vector4(Float32 xyzw)
			: x(xyzw)
			, y(xyzw)
			, z(xyzw)
			, w(xyzw)
		{
		}

		Vector4(Float32 x, Float32 y, Float32 z, Float32 w)
			: x(x)
			, y(y)
			, z(z)
			, w(w)
		{
		}

		Vector4(Float32 xyzw[4])
			: x(xyzw[0])
			, y(xyzw[1])
			, z(xyzw[2])
			, w(xyzw[3])
		{
		}

		explicit Vector4(const Vector2 &other, Float32 z, Float32 w)
			: x(other.x)
			, y(other.y)
			, z(z)
			, w(w)
		{
		}

		explicit Vector4(const Vector2 &xy, const Vector2 &zw)
			: Vector4(xy.x, xy.y, zw.x, zw.y)
		{
		}

		explicit Vector4(const Vector3 &other, Float32 w)
			: Vector4(other.x, other.y, other.z, w)
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

		Vector4 operator+(const Vector4 &other) const
		{
			return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		Vector4 operator-(const Vector4 &other) const
		{
			return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		Vector4 operator*(Float32 scalar) const
		{
			return Vector4(scalar * x, scalar * y, scalar * z, scalar * w);
		}

		Vector4 operator/(Float32 scalar) const
		{
			return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
		}

		Vector4 &operator+=(const Vector4 &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
		}

		Vector4 &operator-=(const Vector4 &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		Vector4 &operator*=(Float32 scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
			return *this;
		}

		Vector4 &operator/=(Float32 scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			w /= scalar;
			return *this;
		}

		union
		{
			Float32 data[4];
			struct
			{
				Float32 x, y, z, w;
			};
			struct
			{
				Float32 r, g, b, a;
			};
			struct
			{
				Float32 s, t, p, q;
			};
		};
	};

	inline Vector4 operator*(Float32 scalar, const Vector4 &vector)
	{
		return vector * scalar;
	}

	inline Float32 dot(const Vector4 &a, const Vector4 &b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	inline Float32 lengthSquared(const Vector4 &a)
	{
		return dot(a, a);
	}

	inline Float32 length(const Vector4 &a)
	{
		return std::sqrtf(lengthSquared(a));
	}

	inline Vector4 normalized(const Vector4 &a)
	{
		return a * (1.0f / length(a));
	}
}

#endif
