#pragma once
#include "Direction.h"
#include "GameObject.h"
#include "Vector2.h"

struct EntitySprites;
class Path;
class Sprite;
class AnimatedSprite;

class Enemy : public GameObject
{
public:
	Enemy(const int& health, const float& speed, EntitySprites* entitySprites);
	~Enemy() override;

	void update() override;
	void destroy() override;

	void followPath();
	void setAnimation();
	void setSprites(EntitySprites* entitySprites);
	void setNextPosition();

	sf::Drawable* getDrawable() override;

private:
	int m_health;
	float m_speed;

	Path* m_path;
	DirectionType m_nextDirection = NORTH;
	Vector2 m_nextPosition = Vector2::zero();
	Vector2 m_position = Vector2::zero();
	
	AnimatedSprite* m_animationNorth = nullptr;
	AnimatedSprite* m_animationSouth = nullptr;
	AnimatedSprite* m_animationSide = nullptr;
	AnimatedSprite* m_currentSide = nullptr;
};