#include "Event.h"
#include "GameObject.h"
#include "EngineHandler.h"

GameObject::GameObject(Transform localTransform, const int& zOrder) : localTransform(localTransform), m_zOrder(zOrder), m_isVisible(true), m_needUpdate(true)
{
	// Add GameObject to the engine object array
	EngineHandler::addObject(this);

	EngineHandler::onStart += EventHandler::bind(&GameObject::awake, this);
	EngineHandler::onEarlyUpdate += EventHandler::bind(&GameObject::onDrawCall, this);
	EngineHandler::onEarlyUpdate += EventHandler::bind(&GameObject::earlyUpdate, this);
	EngineHandler::onUpdate += EventHandler::bind(&GameObject::update, this);
	EngineHandler::onLateUpdate += EventHandler::bind(&GameObject::lateUpdate, this);

	EngineHandler::onDebugDraw += EventHandler::bind<sf::RenderWindow&, GameObject>(&GameObject::debugDrawCall, this);
}
GameObject::~GameObject()
{
	EngineHandler::onStart -= EventHandler::bind(&GameObject::awake, this);
	EngineHandler::onEarlyUpdate -= EventHandler::bind(&GameObject::onDrawCall, this);
	EngineHandler::onEarlyUpdate -= EventHandler::bind(&GameObject::earlyUpdate, this);
	EngineHandler::onUpdate -= EventHandler::bind(&GameObject::update, this);
	EngineHandler::onLateUpdate -= EventHandler::bind(&GameObject::lateUpdate, this);

	EngineHandler::onDebugDraw -= EventHandler::bind<sf::RenderWindow&, GameObject>(&GameObject::debugDrawCall, this);

	for (GameObject* object : childrens)
		object->destroy();
	childrens.clear();

	removeFromParent();
}

void GameObject::awake() {}
void GameObject::earlyUpdate() {}
void GameObject::update() {}
void GameObject::lateUpdate() {}
void GameObject::destroy() { EngineHandler::destroyObject(this); }

void GameObject::drawCall(sf::RenderWindow& window) {}
void GameObject::debugDrawCall(sf::RenderWindow& window) {}

GameObject* GameObject::getChildren(const int& index)
{
	if (index < 0 || index >= childrens.size()) return nullptr;
	return childrens[index];
}
void GameObject::addChildren(GameObject* object)
{
	if (object->parent == this) return;
	childrens.push_back(object);

	object->setParent(this);
	object->needUpdate();
}
void GameObject::removeChildren(GameObject* object)
{
	if (object->parent != this) return;
	childrens.erase(std::remove(childrens.begin(), childrens.end(), object), childrens.end());

	object->parent = nullptr;
	object->needUpdate();
}
void GameObject::removeFromParent()
{
	if (parent == nullptr) return;
	parent->removeChildren(this);
}
void GameObject::setParent(GameObject* newParent)
{
	if (parent == newParent) return;;
	if (parent != nullptr) removeFromParent();
	newParent->addChildren(this);
}

void GameObject::needUpdate() { m_needUpdate = true; }
void GameObject::setVisible(const bool& isVisible) { m_isVisible = isVisible; }
void GameObject::setZOrder(const int& zOrder) { m_zOrder = zOrder; }
int GameObject::getZOrder() const { return m_zOrder; }

void GameObject::setPosition(const Vector2& position)
{
	localTransform.setPosition(position);
	needUpdate();
}
void GameObject::setScale(const Vector2& scale)
{
	localTransform.setScale(scale);
	needUpdate();
}
void GameObject::setRotation(const float& rotation)
{
	localTransform.setRotation(rotation);
	needUpdate();
}
void GameObject::setOrigin(const Vector2& origin)
{
	localTransform.setOrigin(origin);
	needUpdate();
}
void GameObject::setOriginAligned(const Alignment& alignment)
{
	localTransform.setOriginAligned(alignment);
	needUpdate();
}
void GameObject::move(const Vector2& position)
{
	localTransform.move(position);
	needUpdate();
}
void GameObject::rotate(const float& rotation)
{
	localTransform.rotate(rotation);
	needUpdate();
}

void GameObject::onDrawCall()
{
	if (!m_isVisible) return;

	if (m_needUpdate)
	{
		transform = parent != nullptr ? Transform::compose(parent->transform, localTransform) : localTransform;
		for (GameObject* child : childrens)
			child->needUpdate();

		m_needUpdate = false;
	}
	EngineHandler::drawObject(this);
}