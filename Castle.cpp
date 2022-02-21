#include <SFML/Graphics.hpp>

#include "Castle.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "HealthBar.h"
#include "Terrain.h"

extern int CELL_WIDTH;
extern int CELL_HEIGHT;
extern int WINDOW_WIDTH;
extern float SCALE_FACTOR;

Castle::Castle(const int& health) :
	m_castleSprite(new Sprite(&ResourceManager::castleSprite))
{
	setPosition(Terrain::getWorldPosition(Terrain::terrain->castlePosition));
	setScale(Vector2(SCALE_FACTOR));
	setOrigin(Vector2(CELL_WIDTH / 2.0f, CELL_HEIGTH - 1));
	setZOrder((localTransform.position.Y * WINDOW_WIDTH + localTransform.position.X));

	m_healthBar = new HealthBar(10, Vector2(24, 64), Vector2(8.f, 2.f));
	m_healthBar->setPosition(Vector2(WINDOW_WIDTH / 2.f, 16));
}
Castle::~Castle()
{
	delete m_castleSprite;
}

void Castle::drawCall(sf::RenderWindow& window)
{
	transform.setTransformable(m_castleSprite->getSprite());
	window.draw(*m_castleSprite->getSprite());
}