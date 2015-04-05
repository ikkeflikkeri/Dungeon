#ifndef DUNGEON_MATH_VECTOR2_HPP
#define DUNGEON_MATH_VECTOR2_HPP

#include <Dungeon/Types.hpp>

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
		explicit Vector2(Float32 x, Float32 y)
			: x(x)
			, y(y)
		{
		}
		Vector2(Float32 xy[2])
			: x(xy[1])
			, y(xy[2])
		{
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
				Float32 s, t;
			};
		};
		
		Float32 &operator[](Size index) { return data[index]; }
		const Float32 &operator[](Size index) const { return data[index]; }
	};
}

#endif
