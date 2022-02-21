#include <SFML/Graphics.hpp>

#include "Enemy.h"
#include "AnimatedSprite.h"
#include "Path.h"
#include "Sprite.h"
#include "Terrain.h"
#include "Direction.h"
#include "ResourceManager.h"
#include "Time.h"
#include "InputManager.h"
#include "Random.h"
#include "HealthBar.h"

extern int CELL_WIDTH;
extern int CELL_HEIGTH;
extern float SCALE_FACTOR;
extern int WINDOW_HEIGHT;
extern int WINDOW_WIDTH;

Enemy::Enemy(const int& health, const float& speed, EntitySprites* entitySprites) :
	m_health(health),
	m_speed(speed),
	m_path(Terrain::terrain->getPath()),
	m_posOffset(Vector2(Random::random(-4, 5), Random::random(-2, 13))),
	m_sizeOffset(SCALE_FACTOR - .8)
{
	setSize(Vector2i(CELL_WIDTH, CELL_HEIGTH));
	setPosition(Terrain::getWorldPositionDirection(m_path->getPosition(), m_path->getOldDirection()) + m_posOffset);
	setOriginAligned(Alignment::BOTTOMCENTER);

	setSprites(entitySprites);
	setNextPosition();

	addChildren(new HealthBar(m_health, Vector2(0, -42)));
}
Enemy::~Enemy()
{
	delete m_animationNorth;
	delete m_animationSouth;
	delete m_animationSide;
}

void Enemy::update()
{
	setZOrder((localTransform.position.Y * WINDOW_WIDTH + localTransform.position.X));
	getChildren(0)->setZOrder(getZOrder() + 1);
	followPath();
}
void Enemy::destroy()
{
	GameObject::destroy();
}

void Enemy::drawCall(sf::RenderWindow& window)
{
	transform.setTransformable(m_currentSide->getSprite());
	window.draw(*m_currentSide->getSprite());
}

void Enemy::setSprites(EntitySprites* entitySprites)
{
	m_animationNorth = new AnimatedSprite(&entitySprites->spritesNorth[0], 16.f / m_speed);
	m_animationNorth->addFrame(&entitySprites->spritesNorth[1]);
	m_animationNorth->addFrame(&entitySprites->spritesNorth[0]);
	m_animationNorth->addFrame(&entitySprites->spritesNorth[2]);

	m_animationSouth = new AnimatedSprite(&entitySprites->spritesSouth[0], 16.f / m_speed);
	m_animationSouth->addFrame(&entitySprites->spritesSouth[1]);
	m_animationSouth->addFrame(&entitySprites->spritesSouth[0]);
	m_animationSouth->addFrame(&entitySprites->spritesSouth[2]);

	m_animationSide = new AnimatedSprite(&entitySprites->spritesSide[0], 16.f / m_speed);
	m_animationSide->addFrame(&entitySprites->spritesSide[1]);
	m_animationSide->addFrame(&entitySprites->spritesSide[0]);
	m_animationSide->addFrame(&entitySprites->spritesSide[2]);
}
void Enemy::setNextPosition()
{

	bool canCheckPath = true;
	m_nextDirection = Direction::getOpposite(m_path->getNextPath()->getOldDirection());
	while (canCheckPath)
	{
		Path* path = m_path->getPath(m_nextDirection);
		if (path == nullptr) canCheckPath = false;
		else if (path->getAdjacentPathCount() == 1) m_path = path;
		else
		{
			m_path = path;
			canCheckPath = false;
		}
	}
	m_nextPosition = Terrain::getWorldPositionCenter(m_path->getPosition()) + m_posOffset;

	setAnimation();
}
void Enemy::setAnimation()
{
	switch (m_nextDirection)
	{
		case DirectionType::NORTH:
			setScale(Vector2(m_sizeOffset, m_sizeOffset));
			m_currentSide = m_animationNorth;
			break;
		case DirectionType::SOUTH:
			setScale(Vector2(m_sizeOffset, m_sizeOffset));
			m_currentSide = m_animationSouth;
			break;
		case DirectionType::WEST:
			setScale(Vector2(-m_sizeOffset, m_sizeOffset));
			m_currentSide = m_animationSide;
			break;
		case DirectionType::EAST:
			setScale(Vector2(m_sizeOffset, m_sizeOffset));
			m_currentSide = m_animationSide;
			break;
	}
}

void Enemy::followPath()
{
	move(Direction::getVector2(m_nextDirection) * m_speed * Time::deltaTime);
	if ((m_nextDirection == DirectionType::NORTH && localTransform.position.Y <= m_nextPosition.Y) ||
		(m_nextDirection == DirectionType::SOUTH && localTransform.position.Y >= m_nextPosition.Y) ||
		(m_nextDirection == DirectionType::WEST && localTransform.position.X <= m_nextPosition.X) ||
		(m_nextDirection == DirectionType::EAST && localTransform.position.X >= m_nextPosition.X))
	{
		setPosition(m_nextPosition);
		if (m_path->getPosition() == Terrain::terrain->castlePosition)
			return destroy();

		setNextPosition();
	}
}
