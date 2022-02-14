#include <SFML/Graphics.hpp>

#include "Enemy.h"
#include "AnimatedSprite.h"
#include "Path.h"
#include "Sprite.h"
#include "Terrain.h"
#include "Direction.h"
#include "EngineHandler.h"
#include "ResourceManager.h"
#include "Time.h"

extern int CELL_WIDTH;
extern int CELL_HEIGTH;
extern float SCALE_FACTOR;

Enemy::Enemy(const int& health, const float& speed, EntitySprites* entitySprites) :
	m_health(health),
	m_speed(speed),
	m_path(Terrain::terrain->getPath())
{
	m_position = Terrain::getWorldPositionDirection(m_path->getPosition(), m_path->getOldDirection());

	setSprites(entitySprites);
	setNextPosition();
}
Enemy::~Enemy()
{
	delete m_animationNorth;
	delete m_animationSouth;
	delete m_animationSide;
}

void Enemy::update()
{
	setZOrder((int)m_position.Y);
	followPath();
}
void Enemy::destroy()
{
	EngineHandler::destroyObject(this);
}

void Enemy::setSprites(EntitySprites* entitySprites)
{
	m_animationNorth = new AnimatedSprite(&entitySprites->spritesNorth[0], 16.f / m_speed);
	m_animationNorth->addFrame(&entitySprites->spritesNorth[1]);
	m_animationNorth->addFrame(&entitySprites->spritesNorth[0]);
	m_animationNorth->addFrame(&entitySprites->spritesNorth[2]);
	m_animationNorth->setOrigin(Vector2(CELL_WIDTH / 2.f, CELL_HEIGTH));

	m_animationSouth = new AnimatedSprite(&entitySprites->spritesSouth[0], 16.f / m_speed);
	m_animationSouth->addFrame(&entitySprites->spritesSouth[1]);
	m_animationSouth->addFrame(&entitySprites->spritesSouth[0]);
	m_animationSouth->addFrame(&entitySprites->spritesSouth[2]);
	m_animationSouth->setOrigin(Vector2(CELL_WIDTH / 2.f, CELL_HEIGTH));

	m_animationSide = new AnimatedSprite(&entitySprites->spritesSide[0], 16.f / m_speed);
	m_animationSide->addFrame(&entitySprites->spritesSide[1]);
	m_animationSide->addFrame(&entitySprites->spritesSide[0]);
	m_animationSide->addFrame(&entitySprites->spritesSide[2]);
	m_animationSide->setOrigin(Vector2(CELL_WIDTH / 2.f, CELL_HEIGTH));
}
void Enemy::setNextPosition()
{
	m_nextDirection = Direction::getOpposite(m_path->getNextPath()->getOldDirection());
	while (m_path->getPath(m_nextDirection) != nullptr)
	{
		m_path = m_path->getNextPath();
	}
	m_nextPosition = Terrain::getWorldPositionCenter(m_path->getPosition());

	setAnimation();
}
void Enemy::setAnimation()
{
	switch (m_nextDirection)
	{
		case NORTH:
			m_currentSide = m_animationNorth;
			break;
		case SOUTH:
			m_currentSide = m_animationSouth;
			break;
		case EAST:
			m_currentSide = m_animationSide;
			break;
		case WEST:
			m_currentSide = m_animationSide;
			break;
	}
}

sf::Drawable* Enemy::getDrawable()
{
	m_currentSide->setPosition(m_position);
	m_currentSide->setScale(m_nextDirection == EAST ? Vector2(-SCALE_FACTOR, SCALE_FACTOR) : Vector2(SCALE_FACTOR, SCALE_FACTOR));
	return m_currentSide->getSprite();
}

void Enemy::followPath()
{
	m_position += Direction::getVector2(m_nextDirection) * m_speed * Time::deltaTime;
	if ((m_nextDirection == NORTH && m_position.Y <= m_nextPosition.Y) ||
		(m_nextDirection == SOUTH && m_position.Y >= m_nextPosition.Y) ||
		(m_nextDirection == EAST && m_position.X <= m_nextPosition.X) ||
		(m_nextDirection == WEST && m_position.X >= m_nextPosition.X)) 
	{
		m_position = m_nextPosition;
		if (m_path->getPosition() == Terrain::terrain->castlePosition)
			return destroy();

		setNextPosition();
	}
}
