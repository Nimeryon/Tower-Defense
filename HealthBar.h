#pragma once
#include "GameObject.h"

namespace sf
{
	class RectangleShape;
}
class Sprite;

class HealthBar : public GameObject
{
public:
	explicit HealthBar(int width, int health = 100);
	explicit HealthBar(int health = 100);
	~HealthBar() override;

	void removeHealth(const int& health);

	void setSize(const Vector2i& size) override;
	void lateUpdate() override;
	void drawCall(sf::RenderWindow& window) override;

private:
	static const Vector2 healthScale;
	int m_health;
	int m_maxHealth;

	sf::RectangleShape* m_healthBar;
	Sprite* m_healthDecorator;
};
