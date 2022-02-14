#pragma once
struct Vector2;

class Math
{
public:
	static float clamp(const float& value, const float& min, const float& max);
	static int clamp(const int& value, const int& min, const int& max);
};