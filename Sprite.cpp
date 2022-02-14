#include <SFML/Graphics.hpp>

#include "Sprite.h"

Sprite::Sprite(sf::Sprite* sprite) : m_sprite(sprite) {}
Sprite::~Sprite() = default;

void Sprite::setSprite(sf::Sprite* sprite) { m_sprite = sprite; }
sf::Sprite* Sprite::getSprite() { return m_sprite; }

void Sprite::setPosition(const Vector2& position) { getSprite()->setPosition(position); }
void Sprite::setScale(const Vector2& scale) { getSprite()->setScale(scale); }
void Sprite::setOrigin(const Vector2& origin) { getSprite()->setOrigin(origin); }
void Sprite::setRotation(const float& rotation) { getSprite()->setRotation(rotation); }
void Sprite::setColor(const sf::Color& color) { getSprite()->setColor(color); }
