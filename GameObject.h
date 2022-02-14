#pragma once
#include <vector>

namespace sf
{
	class Drawable;
}

class GameObject
{
public:
	explicit GameObject(const int& zOrder = 0);
	virtual ~GameObject();

	virtual void awake();
	virtual void earlyUpdate();
	virtual void update();
	virtual void lateUpdate();
	virtual void destroy();

	void draw();
	virtual sf::Drawable* getDrawable() = 0;

	void setZOrder(const int& zOrder);
	int getZOrder() const;

	GameObject* parent;
	std::vector<GameObject*> childrens;



private:
	int m_zOrder;
};