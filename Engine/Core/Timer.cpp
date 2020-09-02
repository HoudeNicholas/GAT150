#include "pch.h"
#include "Timer.h"


namespace nc
{
	void nc::Timer::reset()
	{
		point = myClock::now();
	}

	Timer::myClock::rep Timer::elapsedTicks()
	{
		clockDuration duration = (myClock::now() - point);
		return duration.count();
	}

	Timer::myClock::rep Timer::tps()
	{
		return clockDuration::period::den;
	}

	double Timer::elapsedSeconds()
	{
		return elapsedTicks() / static_cast<double>(tps());
	}





	void FrameTimer::tick()
	{
		dt = elapsedSeconds();
		reset();
	}

}
