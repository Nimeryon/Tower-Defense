#pragma once
namespace sf { class Time; }

class Time
{
public:
	static float deltaTime;
	void setTime(const float& time);
};