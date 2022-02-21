#include <SFML/Graphics.hpp>
#include <algorithm>
#include <chrono>

#include "Event.h"
#include "GameObject.h"
#include "EngineHandler.h"
#include "FrameTime.h"

// Events
Event<void> EngineHandler::onStart = Event<void>();
Event<void> EngineHandler::onEarlyUpdate = Event<void>();
Event<void> EngineHandler::onUpdate = Event<void>();
Event<void> EngineHandler::onLateUpdate = Event<void>();
Event<void> EngineHandler::onEventTimerExecution = Event<void>();

Event<sf::RenderWindow&> EngineHandler::onDebugDraw = Event<sf::RenderWindow&>();

std::chrono::steady_clock::time_point EngineHandler::m_timeBegin = {};
std::chrono::steady_clock::time_point EngineHandler::m_timeEnd = {};

// GameObjects vector
std::vector<GameObject*> EngineHandler::m_objects = {};
std::vector<GameObject*> EngineHandler::m_objectsToDestroy = {};
std::vector<GameObject*> EngineHandler::m_objectsToDraw = {};

extern bool DEBUG_MODE;

void EngineHandler::update()
{
	m_timeBegin = std::chrono::steady_clock::now();
	onEarlyUpdate();
	m_timeEnd = std::chrono::steady_clock::now();
	FrameTime::frameTime->earlyUpdateTimeText->setString("EarlyUpdate " + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(m_timeEnd - m_timeBegin).count() / 1000.f) + "ms");

	m_timeBegin = std::chrono::steady_clock::now();
	onUpdate();
	m_timeEnd = std::chrono::steady_clock::now();
	FrameTime::frameTime->updateTimeText->setString("Update " + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(m_timeEnd - m_timeBegin).count() / 1000.f) + "ms");
}
void EngineHandler::lateUpdate(sf::RenderWindow & window)
{
	m_timeBegin = std::chrono::steady_clock::now();
	onLateUpdate();
	m_timeEnd = std::chrono::steady_clock::now();
	FrameTime::frameTime->lateUpdateTimeText->setString("LateUpdate " + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(m_timeEnd - m_timeBegin).count() / 1000.f) + "ms");

	onEventTimerExecution();

	clearObjectsToDestroy();
}

void EngineHandler::addObject(GameObject* object)
{
	m_objects.push_back(object);	
}
void EngineHandler::destroyObject(GameObject* object)
{
	m_objectsToDestroy.push_back(object);
}
void EngineHandler::drawObject(GameObject* object)
{
	m_objectsToDraw.push_back(object);
}
void EngineHandler::draw(sf::RenderWindow& window)
{
	m_timeBegin = std::chrono::steady_clock::now();
	std::sort(m_objectsToDraw.begin(), m_objectsToDraw.end(), [](GameObject* object1, GameObject* object2)
		{ return object1->getZOrder() < object2->getZOrder(); });
	m_timeEnd = std::chrono::steady_clock::now();
	FrameTime::frameTime->drawTimeText->setString("Draw " + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(m_timeEnd - m_timeBegin).count() / 1000.f) + "ms");

	for (GameObject* object : m_objectsToDraw)
		object->drawCall(window);
	m_objectsToDraw.clear();

	m_timeBegin = std::chrono::steady_clock::now();
	if (DEBUG_MODE) onDebugDraw(window);
	m_timeEnd = std::chrono::steady_clock::now();
	FrameTime::frameTime->debugDrawTimeText->setString("DebugDraw " + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(m_timeEnd - m_timeBegin).count() / 1000.f) + "ms");

}

void EngineHandler::clearObjectsToDestroy()
{
	for (auto it = m_objectsToDestroy.begin(); it != m_objectsToDestroy.end(); ++it)
	{
		GameObject* object = *it;
		if (object)
		{
			auto objectIt = std::find(m_objects.begin(), m_objects.end(), object);
			m_objects.erase(objectIt);

			delete object;
			object = nullptr;
		}
	}
	m_objectsToDestroy.clear();
}