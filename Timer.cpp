#include "Event.h"
#include "EngineHandler.h"
#include "Time.h"
#include "Timer.h"

Timer::Timer(const float& timerTime) : m_timerTime(timerTime)
{
	EngineHandler::onEarlyUpdate += EventHandler::bind(&Timer::onEarlyUpdate, this);
	EngineHandler::onEventTimerExecution += EventHandler::bind(&Timer::onEventTimerExecution, this);
}
Timer::~Timer()
{
	EngineHandler::onEarlyUpdate -= EventHandler::bind(&Timer::onEarlyUpdate, this);
	EngineHandler::onEventTimerExecution -= EventHandler::bind(&Timer::onEventTimerExecution, this);
}

bool Timer::isTimerComplete() {	return m_currentTimerTime >= m_timerTime; }

void Timer::setTime(const float& timerTime) { m_timerTime = timerTime;  }

float Timer::getTime() const { return m_timerTime; }
float Timer::getCurrentTime() const { return m_currentTimerTime; }

void Timer::onEarlyUpdate()
{
	m_currentTimerTime += Time::deltaTime;
}
void Timer::onEventTimerExecution()
{
	if (isTimerComplete())
		m_currentTimerTime -= m_timerTime;
}
