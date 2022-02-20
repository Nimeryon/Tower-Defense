#include <SFML/Graphics.hpp>
#include <algorithm>

#include "Event.h"
#include "GameObject.h"
#include "EngineHandler.h"

// Events
Event<void> EngineHandler::onStart = Event<void>();
Event<void> EngineHandler::onEarlyUpdate = Event<void>();
Event<void> EngineHandler::onUpdate = Event<void>();
Event<void> EngineHandler::onLateUpdate = Event<void>();
Event<void> EngineHandler::onEventTimerExecution = Event<void>();

Event<sf::RenderWindow&> EngineHandler::onDebugDraw = Event<sf::RenderWindow&>();

// GameObjects vector
std::vector<GameObject*> EngineHandler::m_objects = {};
std::vector<GameObject*> EngineHandler::m_objectsToDestroy = {};
std::vector<GameObject*> EngineHandler::m_objectsToDraw = {};

extern bool DEBUG_MODE;

void EngineHandler::update()
{
	onEarlyUpdate();
	onUpdate();
}
void EngineHandler::lateUpdate(sf::RenderWindow & window)
{
	onLateUpdate();
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
	std::sort(m_objectsToDraw.begin(), m_objectsToDraw.end(), [](GameObject* object1, GameObject* object2)
		{ return object1->getZOrder() < object2->getZOrder(); });

	for (GameObject* object : m_objectsToDraw)
		object->drawCall(window);
	m_objectsToDraw.clear();

	if (DEBUG_MODE) onDebugDraw(window);
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