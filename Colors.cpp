#include <SFML/Graphics.hpp>

#include "Colors.h"
#include "Math.h"

sf::Color Colors::lerpRGB(sf::Color a, sf::Color b, float t)
{
	t = Math::clamp(t, 0.f, 1.f);
	return sf::Color(
		a.r + (b.r - a.r) * t,
		a.g + (b.g - a.g) * t,
		a.b + (b.b - a.b) * t,
		a.a + (b.a - a.a) * t
	);
}
