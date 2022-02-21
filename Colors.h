#pragma once
namespace sf
{
	class Color;
}

class Colors
{
public:
	static sf::Color lerpRGB(sf::Color a, sf::Color b, float t);
};