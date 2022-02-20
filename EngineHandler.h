#pragma once
#include <vector>
#include <chrono>

namespace sf { class RenderWindow; }
class GameObject;
template<typename T>
class Event;

class EngineHandler
{
public:
	static void update();
	static void lateUpdate(sf::RenderWindow& window);

	// GameObject Handling
	static void addObject(GameObject* object);
	static void destroyObject(GameObject* object);
	static void drawObject(GameObject* object);
	static void draw(sf::RenderWindow& window);

	// Events
	static Event<void> onStart;
	static Event<void> onEarlyUpdate;
	static Event<void> onUpdate;
	static Event<void> onLateUpdate;
	static Event<void> onEventTimerExecution;

	static Event<sf::RenderWindow&> onDebugDraw;

private:
	static std::vector<GameObject*> m_objects;
	static std::vector<GameObject*> m_objectsToDestroy;
	static std::vector<GameObject*> m_objectsToDraw;

	static std::chrono::steady_clock::time_point m_timeBegin;
	static std::chrono::steady_clock::time_point m_timeEnd;

	static void clearObjectsToDestroy();
};