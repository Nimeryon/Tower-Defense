#pragma once
template<typename T>
class Event;

class Timer {
public:
	Timer(const float& timerTime);
	~Timer();

	bool isTimerComplete();

	void setTime(const float& timerTime);

	float getTime() const;
	float getCurrentTime() const;

private:
	float m_timerTime;
	float m_currentTimerTime = 0.f;

	void onEarlyUpdate();
	void onEventTimerExecution();
};