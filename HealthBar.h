#pragma once
#include "GameObject.h"

namespace sf
{
	class RectangleShape;
	class Color;
}
class Sprite;

class HealthBar : public GameObject
{
public:
	explicit HealthBar(int health = 100, Vector2 positionOffset = Vector2::zero(), Vector2 healthScale = Vector2(2.f, 1.f));
	~HealthBar() override;

	void removeHealth(const int& health);
	float getLifePercentage();

	void test();

	void setSize(const Vector2i& size) override;
	void drawCall(sf::RenderWindow& window) override;

private:
	Vector2 m_healthScale;
	Vector2 m_positionOffset;
	int m_health;
	int m_maxHealth;

	sf::Color m_fullLifeColor;
	sf::Color m_emptyLifeColor;

	sf::RectangleShape* m_healthBar;
	Sprite* m_healthDecorator;
	Transform m_healthDecoratorTransform;
};
