#include "Event.h"
#include "GameObject.h"
#include "EngineHandler.h"

GameObject::GameObject(const int& zOrder) : m_zOrder(zOrder)
{
	// Add GameObject to the engine object array
	EngineHandler::addObject(this);

	EngineHandler::onStart += EventHandler::bind(&GameObject::awake, this);
	EngineHandler::onEarlyUpdate += EventHandler::bind(&GameObject::draw, this);
	EngineHandler::onEarlyUpdate += EventHandler::bind(&GameObject::earlyUpdate, this);
	EngineHandler::onUpdate += EventHandler::bind(&GameObject::update, this);
	EngineHandler::onLateUpdate += EventHandler::bind(&GameObject::lateUpdate, this);
}
GameObject::~GameObject()
{
	EngineHandler::onStart -= EventHandler::bind(&GameObject::awake, this);
	EngineHandler::onEarlyUpdate -= EventHandler::bind(&GameObject::draw, this);
	EngineHandler::onEarlyUpdate -= EventHandler::bind(&GameObject::earlyUpdate, this);
	EngineHandler::onUpdate -= EventHandler::bind(&GameObject::update, this);
	EngineHandler::onLateUpdate -= EventHandler::bind(&GameObject::lateUpdate, this);
}

void GameObject::awake() {}
void GameObject::earlyUpdate() {}
void GameObject::update() {}
void GameObject::lateUpdate() {}
void GameObject::destroy() {}

void GameObject::draw() { EngineHandler::drawObject(this); }

void GameObject::setZOrder(const int& zOrder) { m_zOrder = zOrder; }
int GameObject::getZOrder() const { return m_zOrder; }
