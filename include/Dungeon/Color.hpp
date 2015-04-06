#ifndef DUNGEON_COLOR_HPP
#define DUNGEON_COLOR_HPP

#include <Dungeon/Types.hpp>

namespace Dungeon
{
	union Color
	{
		UInt8 data[4];
		struct
		{
			UInt8 r, g, b, a;
		};
	};
}

#endif