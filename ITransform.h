#pragma once
#include "Vector2.h"
#include "Vector2i.h"

enum class Alignment;

namespace sf
{
	class Color;
}

struct ITransform
{
	virtual void setPosition(const Vector2& position) = 0;
	virtual void setScale(const Vector2& scale) = 0;
	virtual void setOrigin(const Vector2& origin) = 0;
	virtual void setRotation(const float& rotation) = 0;
	
	virtual void move(const Vector2& position) {}
	virtual void setOriginAligned(const Alignment& alignment) {}
	virtual void rotate(const float& rotation) {}
};