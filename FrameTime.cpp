#include <SFML/Graphics.hpp>

#include "FrameTime.h"

#include "EngineHandler.h"
#include "Event.h"
#include "ResourceManager.h"

FrameTime* FrameTime::frameTime = nullptr;

FrameTime::FrameTime() :
	earlyUpdateTimeText(new sf::Text()),
	updateTimeText(new sf::Text()),
	lateUpdateTimeText(new sf::Text()),
	drawTimeText(new sf::Text()),
	debugDrawTimeText(new sf::Text()),
	deltaTimeText(new sf::Text())
{
	frameTime = this;

	earlyUpdateTimeText->setFont(ResourceManager::m_font);
	earlyUpdateTimeText->setCharacterSize(16);
	earlyUpdateTimeText->setFillColor(sf::Color::Yellow);
	earlyUpdateTimeText->setPosition(Vector2i(0, 24));

	updateTimeText->setFont(ResourceManager::m_font);
	updateTimeText->setCharacterSize(16);
	updateTimeText->setFillColor(sf::Color::Yellow);
	updateTimeText->setPosition(Vector2i(0, 24 + 16));

	lateUpdateTimeText->setFont(ResourceManager::m_font);
	lateUpdateTimeText->setCharacterSize(16);
	lateUpdateTimeText->setFillColor(sf::Color::Yellow);
	lateUpdateTimeText->setPosition(Vector2i(0, 24 + 16 * 2));

	drawTimeText->setFont(ResourceManager::m_font);
	drawTimeText->setCharacterSize(16);
	drawTimeText->setFillColor(sf::Color::Yellow);
	drawTimeText->setPosition(Vector2i(0, 24 + 16 * 3));

	debugDrawTimeText->setFont(ResourceManager::m_font);
	debugDrawTimeText->setCharacterSize(16);
	debugDrawTimeText->setFillColor(sf::Color::Yellow);
	debugDrawTimeText->setPosition(Vector2i(0, 24 + 16 * 4));

	deltaTimeText->setFont(ResourceManager::m_font);
	deltaTimeText->setCharacterSize(16);
	deltaTimeText->setFillColor(sf::Color::Yellow);
	deltaTimeText->setPosition(Vector2i(0, 24 + 16 * 5));

	EngineHandler::onDebugDraw += EventHandler::bind<sf::RenderWindow&, FrameTime>(&FrameTime::debugDraw, this);
}
FrameTime::~FrameTime()
{
	EngineHandler::onDebugDraw -= EventHandler::bind<sf::RenderWindow&, FrameTime>(&FrameTime::debugDraw, this);

	delete earlyUpdateTimeText;
	delete updateTimeText;
	delete lateUpdateTimeText;
	delete drawTimeText;
	delete debugDrawTimeText;
}

void FrameTime::debugDraw(sf::RenderWindow& window)
{
	window.draw(*earlyUpdateTimeText);
	window.draw(*updateTimeText);
	window.draw(*lateUpdateTimeText);
	window.draw(*drawTimeText);
	window.draw(*debugDrawTimeText);
	window.draw(*deltaTimeText);
}
