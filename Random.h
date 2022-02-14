#pragma once
class Random
{
public:
	static float randomf(); // Return float value between 0.0f and 1.0f 
	static float randomf(const float& min, const float& max); // Return float value between min and max excluded
	static int random(const int& min, const int& max); // Return int value between min and max excluded
	static bool randomb();
};
