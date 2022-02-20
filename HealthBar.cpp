#include <SFML/Graphics.hpp>

#include "HealthBar.h"
#include "Vector2i.h"

extern int CELL_WIDTH;

HealthBar::HealthBar(int health) :
	m_health(health),
	m_maxHealth(health),
	m_healthBar(new sf::RectangleShape())
{
	setSize(Vector2i(CELL_WIDTH, 4));
	setScale(healthScaleFactor);
	setOriginAligned(Alignment::MIDDLECENTER);
	setPosition(Vector2(0, 8));

	setVisible(false);

	m_healthBar->setFillColor(sf::Color::Red);
}
HealthBar::~HealthBar()
{
	delete m_healthBar;
}

void HealthBar::removeHealth(const int& health)
{
	m_health -= health;
	setScale(Vector2(healthScaleFactor * ((float)m_health / (float)m_maxHealth), 1));
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
	window.draw(*m_healthBar);
}