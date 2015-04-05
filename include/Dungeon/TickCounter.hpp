#ifndef DUNGEON_TICKCOUNTER_HPP
#define DUNGEON_TICKCOUNTER_HPP

#include <Dungeon/Clock.hpp>

namespace Dungeon
{
	class TickCounter
	{
	public:
		Bool8 update(Float64 frequency)
		{
			Bool8 reset = false;
			if (m_clock.getElapsedTime() >= frequency)
			{
				m_tickRate = m_ticks / frequency;
				m_ticks = 0;
				reset = true;
				m_clock.restart();
			}

			m_ticks++;

			return reset;
		}

		inline Size getTickRate() const { return m_tickRate; }

	private:
		Size m_ticks = 0;
		Size m_tickRate = 0;
		Clock m_clock;
	};
}

#endif
