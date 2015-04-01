#ifndef DUNGEON_NONCOPYABLE_HPP
#define DUNGEON_NONCOPYABLE_HPP

namespace Dungeon
{
	class NonCopyable
	{
	protected:
		NonCopyable() {}

	private:
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;

		NonCopyable(const NonCopyable&&) = delete;
		NonCopyable& operator=(const NonCopyable&&) = delete;
	};
}

#endif