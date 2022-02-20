#include <SFML/Graphics.hpp>

#include "HealthBar.h"
#include "Vector2i.h"
#include "TickSystem.h"
#include "Sprite.h"
#include "ResourceManager.h"

extern int CELL_WIDTH;

const Vector2 HealthBar::healthScale = Vector2(2.f, 1.f);
HealthBar::HealthBar(int width, int health) :
	m_health(health),
	m_maxHealth(health),
	m_healthBar(new sf::RectangleShape())
{
	setSize(Vector2i(width, 6));
	setScale(healthScale);
	setOriginAligned(Alignment::MIDDLECENTER);
	setPosition(Vector2(0, -48));

	m_healthDecorator = new Sprite(&ResourceManager::uiSprites[0]);

	m_healthBar->setFillColor(sf::Color::Red);
}
HealthBar::HealthBar(int health) : HealthBar(CELL_WIDTH, health) {}
HealthBar::~HealthBar()
{
	delete m_healthBar;
}

void HealthBar::removeHealth(const int& health)
{
	m_health -= health;
	setScale(Vector2(healthScale.X * ((float)m_health / (float)m_maxHealth), healthScale.Y));
}

void HealthBar::setSize(const Vector2i& size)
{
	m_healthBar->setSize(size);
	GameObject::setSize(size);
}
void HealthBar::lateUpdate()
{
	setZOrder(parent->getZOrder() + 1);
}
void HealthBar::drawCall(sf::RenderWindow& window)
{
	transform.setTransformable(m_healthBar);
	transform.setTransformable(m_healthDecorator->getSprite());
	window.draw(*m_healthBar);
	window.draw(*m_healthDecorator->getSprite());
}