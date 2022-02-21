#include <SFML/Graphics.hpp>

#include "HealthBar.h"
#include "Vector2i.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "Colors.h"
#include "Math.h"

extern int CELL_WIDTH;

HealthBar::HealthBar(int health, Vector2 positionOffset, Vector2 healthScale) :
	m_healthScale(healthScale),
	m_positionOffset(positionOffset),
	m_health(health),
	m_maxHealth(health),
	m_fullLifeColor(sf::Color::Green),
	m_emptyLifeColor(sf::Color::Red),
	m_healthBar(new sf::RectangleShape()),
	m_healthDecoratorTransform(Transform())
{
	setSize(Vector2i(CELL_WIDTH, 6));
	setScale(m_healthScale);
	setOriginAligned(Alignment::MIDDLECENTER);
	setPosition(m_positionOffset);

	m_healthDecorator = new Sprite(&ResourceManager::uiSprites[0]);
	m_healthDecoratorTransform.setScale(m_healthScale);
	m_healthDecoratorTransform.setPosition(Vector2(-CELL_WIDTH * (m_healthScale.X / 2.f), 0));
	m_healthDecoratorTransform.setSize(Vector2i(CELL_WIDTH, 6));
	m_healthDecoratorTransform.setOriginAligned(Alignment::MIDDLELEFT);
}
HealthBar::~HealthBar()
{
	delete m_healthBar;
}

void HealthBar::removeHealth(const int& health)
{
	m_health -= health;
	setScale(Vector2(m_healthScale.X * getLifePercentage(), m_healthScale.Y));
}
float HealthBar::getLifePercentage() { return Math::clamp((float)m_health / (float)m_maxHealth, 0.f, 1.f); }

void HealthBar::setSize(const Vector2i& size)
{
	m_healthBar->setSize(size);
	GameObject::setSize(size);
}
void HealthBar::drawCall(sf::RenderWindow& window)
{
	transform.setTransformable(m_healthBar);
	m_healthBar->setFillColor(Colors::lerpRGB(m_emptyLifeColor, m_fullLifeColor, getLifePercentage()));
	Transform::compose(transform, m_healthDecoratorTransform).setTransformable(m_healthDecorator->getSprite());
	window.draw(*m_healthBar);
	window.draw(*m_healthDecorator->getSprite());
}