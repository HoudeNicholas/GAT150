#pragma once
#include "pch.h"



namespace nc
{
	class Timer
	{
	public:
		using myClock = std::chrono::high_resolution_clock;
		using clockDuration = std::chrono::duration<myClock::rep, std::nano>;

		Timer() : point(myClock::now()) {};

		void reset();
		myClock::rep elapsedTicks();
		myClock::rep tps();

		double elapsedSeconds();

	protected:
		myClock::time_point point;

	};

	class FrameTimer : public Timer
	{
	public:
		void tick();
		float deltaTime() { return dt; };

	protected:
		float dt = 0;


	};
}