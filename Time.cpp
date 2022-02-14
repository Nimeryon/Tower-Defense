#include <SFML/System/Time.hpp>

#include "Time.h"

float Time::deltaTime = 0.f;
void Time::setTime(const float& time) { deltaTime = time; }