#pragma once
namespace sf
{
	class Color;
}

class ITransform
{
public:
	virtual void setPosition(const Vector2& position) = 0;
	virtual void setScale(const Vector2& scale) = 0;
	virtual void setOrigin(const Vector2& origin) = 0;
	virtual void setRotation(const float& rotation) = 0;
	virtual void setColor(const sf::Color& color) = 0;
};