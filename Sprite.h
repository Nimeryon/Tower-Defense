#pragma once
#include "Vector2.h"
#include "ITransform.h"

namespace sf
{
	class Sprite;
}

class Sprite : public ITransform
{
public:
	explicit Sprite(sf::Sprite* sprite = nullptr);
	virtual ~Sprite();

	sf::Sprite* getSprite();
	void setSprite(sf::Sprite* sprite);

	void setPosition(const Vector2& position) override;
	void setOrigin(const Vector2& origin) override;
	void setScale(const Vector2& scale) override;
	void setRotation(const float& rotation) override;
	void setColor(const sf::Color& color) override;

private:
	sf::Sprite* m_sprite;
};