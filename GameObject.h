#pragma once
#include <vector>

#include "Transform.h"

namespace sf
{
	class RenderWindow;
	class Drawable;
	class Transformable;
}

class GameObject : public ITransform
{
public:
	explicit GameObject(Transform localTransform = Transform(), const int& zOrder = 0);
	virtual ~GameObject();

	virtual void awake();
	virtual void earlyUpdate();
	virtual void update();
	virtual void lateUpdate();
	virtual void destroy();

	virtual void drawCall(sf::RenderWindow& window);
	virtual void debugDrawCall(sf::RenderWindow& window);

	void needUpdate();

	void setVisible(const bool& isVisible);
	void setZOrder(const float& zOrder);
	float getZOrder() const;
	
	GameObject* getChildren(const int& index);
	void addChildren(GameObject* object);
	void removeChildren(GameObject* object);
	void removeFromParent();

	void setSize(const Vector2i& size) override;
	void setPosition(const Vector2& position) override;
	void setScale(const Vector2& scale) override;
	void setRotation(const float& rotation) override;
	void setOrigin(const Vector2& origin) override;
	void setOriginAligned(const Alignment& alignment) override;
	void move(const Vector2& position) override;
	void rotate(const float& rotation) override;

	GameObject* parent = nullptr;
	std::vector<GameObject*> childrens = {};

	Transform transform;
	Transform localTransform;

private:
	float m_zOrder;
	bool m_isVisible;
	bool m_needUpdate;

	void onDrawCall();
};