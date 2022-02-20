#include <SFML/Graphics.hpp>

#include "EngineHandler.h"
#include "Event.h"
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(sf::Sprite* initialFrame, const float& animationSpeed) : m_timer(new Timer(animationSpeed))
{
	addFrame(initialFrame);
	setSprite(initialFrame);
	EngineHandler::onUpdate += EventHandler::bind(&AnimatedSprite::update, this);
}
AnimatedSprite::~AnimatedSprite()
{
	EngineHandler::onUpdate -= EventHandler::bind(&AnimatedSprite::update, this);

	delete m_timer;
}

void AnimatedSprite::addFrame(sf::Sprite* frame)
{
	m_frames.push_back(frame);
}
void AnimatedSprite::removeFrame(const int& index)
{
	m_frames.erase(m_frames.begin() + index);
}

float AnimatedSprite::getAnimationSpeed() const { return m_timer->getTime(); }
int AnimatedSprite::getCurrentFrame() const { return m_currentFrame; }

void AnimatedSprite::setAnimationSpeed(const float& animationSpeed) { m_timer->setTime(animationSpeed); }
void AnimatedSprite::setCurrentFrame(const int& frameIndex) { m_currentFrame = frameIndex; }

void AnimatedSprite::update()
{
	if (m_timer->isTimerComplete())
	{
		m_currentFrame = (m_currentFrame + 1) % m_frames.size();
		setSprite(m_frames[m_currentFrame]);
	}
}

void AnimatedSprite::setPosition(const Vector2& position)
{
	for (sf::Sprite* sprite : m_frames)
	{
		sprite->setPosition(position);
	}
}
void AnimatedSprite::setScale(const Vector2& scale)
{
	for (sf::Sprite* sprite : m_frames)
	{
		sprite->setScale(scale);
	}
}
void AnimatedSprite::setOrigin(const Vector2& origin)
{
	for (sf::Sprite* sprite : m_frames)
	{
		sprite->setOrigin(origin);
	}
}
void AnimatedSprite::setRotation(const float& rotation)
{
	for (sf::Sprite* sprite : m_frames)
	{
		sprite->setRotation(rotation);
	}
}
void AnimatedSprite::setColor(const sf::Color& color)
{
	for (sf::Sprite* sprite : m_frames)
	{
		sprite->setColor(color);
	}
}
