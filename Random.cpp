#include <iostream>
#include <time.h>

#include "Random.h"

float Random::randomf()
{
	return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
}
float Random::randomf(const float& min, const float& max)
{
	return (randomf() * (max - min)) + min;
}
int Random::random(const int& min, const int& max)
{
	int rdm = static_cast<int>(randomf(min, max));
	if (rdm == max) return max - 1;
	return rdm;
}

bool Random::randomb()
{
	return randomf() >= 0.5f;
}
