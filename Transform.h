#pragma once
#include "Vector2.h"
#include "ITransform.h"

namespace sf
{
	class Transformable;
}

enum class Alignment
{
	TOPLEFT,
	TOPCENTER,
	TOPRIGHT,
	MIDDLELEFT,
	MIDDLECENTER,
	MIDDLERIGHT,
	BOTTOMLEFT,
	BOTTOMCENTER,
	BOTTOMRIGHT
};

extern int CELL_WIDTH;
extern int CELL_HEIGTH;

struct Transform : ITransform
{
	Vector2i size;
	Vector2 position;
	Vector2 scale;
	float rotation;
	Vector2 origin;

	explicit Transform(
		Vector2 position = Vector2::zero(),
		Vector2i size = Vector2i(CELL_WIDTH, CELL_HEIGTH),
		Vector2 scale = Vector2::one(),
		float rotation = 0,
		Vector2 origin = Vector2::zero()
	);

	void setTransformable(sf::Transformable* transformable);

	void setSize(const Vector2i& size) override;
	void setPosition(const Vector2& position) override;
	void move(const Vector2& position) override;
	void setScale(const Vector2& scale) override;
	void setOrigin(const Vector2& origin) override;
	void setOriginAligned(const Alignment& alignment) override;
	void setRotation(const float& rotation) override;
	void rotate(const float& rotation) override;

	static Transform compose(Transform transform1, Transform transform2);
};