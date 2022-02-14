#pragma once
#include <vector>

#include "Timer.h"
#include "Sprite.h"

namespace sf
{
	class Sprite;
}

class AnimatedSprite : public Sprite
{
public:
	explicit AnimatedSprite(sf::Sprite* initialFrame, const float& animationSpeed = 1.f);
	~AnimatedSprite() override;

	void addFrame(sf::Sprite* frame);
	void removeFrame(const int& index);

	int getCurrentFrame() const;
	float getAnimationSpeed() const;
	
	void setCurrentFrame(const int& frameIndex);
	void setAnimationSpeed(const float& animationSpeed);

	void setPosition(const Vector2& position) override;
	void setOrigin(const Vector2& origin) override;
	void setScale(const Vector2& scale) override;
	void setRotation(const float& rotation) override;
	void setColor(const sf::Color& color) override;

private:
	int m_currentFrame = 0;
	Timer* m_timer;

	std::vector<sf::Sprite*> m_frames = {};

	void update();
};