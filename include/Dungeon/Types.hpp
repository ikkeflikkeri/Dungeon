#ifndef DUNGEON_TYPES_HPP
#define DUNGEON_TYPES_HPP

#include <cstdint>
#include <cstddef>

namespace Dungeon
{
	using Int8 = std::int8_t;
	using Int16 = std::int16_t;
	using Int32 = std::int32_t;
	using Int64 = std::int64_t;

	using UInt8 = std::uint8_t;
	using UInt16 = std::uint16_t;
	using UInt32 = std::uint32_t;
	using UInt64 = std::uint64_t;

	using Float32 = float;
	using Float64 = double;

	using Bool8 = bool;
	using Bool32 = Int32;

	using Size = std::size_t;
}

#endif