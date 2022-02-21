#pragma once
#include "GameObject.h"

class Sprite;

class Castle : public GameObject
{
public:
	Castle(const int& health);
	~Castle() override;

	void drawCall(sf::RenderWindow& window) override;

private:
	Sprite* m_castleSprite;

	GameObject* m_healthBar;
};
