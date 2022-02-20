#pragma once
#include "Event.h"
class Timer;

class TickSystem
{
public:
	TickSystem();
	~TickSystem();

	void update();
	int getTick() const;

	/* Occurs every #TICK_TIME per seconds ( 10 / seconds ) */ Event<void> onMiniEvent;
	/* Occurs every #TICK_TIME % 2 per seconds ( 5 / seconds) */ Event<void> onSmallEvent;
	/* Occurs every #TICK_TIME % 5 per seconds ( 2 / seconds ) */ Event<void> onLittleEvent;
	/* Occurs every #TICK_TIME % 10 per seconds ( 1 / seconds ) */ Event<void> onTickEvent;
	/* Occurs every #TICK_TIME % 50 per seconds ( 1 / 5 seconds ) */ Event<void> onLongEvent;

	static TickSystem* system;

private:
	Timer* m_timer;
	int m_tick;
};