#ifndef DUNGEON_CLOCK_HPP
#define DUNGEON_CLOCK_HPP

#include <Dungeon/Types.hpp>
#include <GLFW/glfw3.h>

namespace Dungeon
{
	class Clock
	{
	public:
		Float64 restart()
		{
			Float64 now = glfwGetTime();
			Float64 elpased = now - m_startTime;
			m_startTime = now;

			return elpased;
		}

		inline Float64 getElapsedTime() const { return glfwGetTime() - m_startTime; }

	private:
		Float64 m_startTime = glfwGetTime();
	};

}

#endif
