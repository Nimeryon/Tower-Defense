#include <SFML/Graphics.hpp>

#include "FpsCounter.h"
#include "EngineHandler.h"
#include "ResourceManager.h"
#include "Time.h"
#include "Event.h"
#include "TickSystem.h"

FpsCounter::FpsCounter() : m_fpsText(new sf::Text())
{
	m_fpsText->setFont(ResourceManager::m_font);
	m_fpsText->setCharacterSize(24);
	m_fpsText->setFillColor(sf::Color::Yellow);

	EngineHandler::onDebugDraw += EventHandler::bind<sf::RenderWindow&, FpsCounter>(&FpsCounter::debugDraw, this);
	TickSystem::system->onMiniEvent += EventHandler::bind(&FpsCounter::update, this);
}
FpsCounter::~FpsCounter()
{
	EngineHandler::onDebugDraw -= EventHandler::bind<sf::RenderWindow&, FpsCounter>(&FpsCounter::debugDraw, this);
	TickSystem::system->onMiniEvent -= EventHandler::bind(&FpsCounter::update, this);

	delete m_fpsText;
}

void FpsCounter::update()
{
	m_fps = std::to_string((int)(1 / Time::deltaTime));
	m_fpsText->setString(m_fps);
}
void FpsCounter::debugDraw(sf::RenderWindow& window) { window.draw(*m_fpsText); }
