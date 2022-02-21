#include <SFML/Graphics.hpp>

#include "Transform.h"

Transform::Transform(Vector2 position, Vector2i size, Vector2 scale, float rotation, Vector2 origin) :
	position(position),
	size(size),
	scale(scale),
	rotation(rotation),
	origin(origin)
{}

void Transform::setTransformable(sf::Transformable* transformable)
{
	transformable->setPosition(position);
	transformable->setRotation(rotation);
	transformable->setScale(scale);
	transformable->setOrigin(origin);
}

void Transform::setPosition(const Vector2& position)
{
	this->position = position;
}
void Transform::move(const Vector2& position)
{
	this->position += position;
}
void Transform::setScale(const Vector2& scale)
{
	this->scale = scale;
}
void Transform::setOrigin(const Vector2& origin)
{
	this->origin = origin;
}
void Transform::setOriginAligned(const Alignment& alignment)
{
	switch (alignment)
	{
		case Alignment::TOPLEFT:
			this->origin = Vector2::zero();
			break;
		case Alignment::TOPCENTER:
			this->origin = Vector2(size.X / 2.f, 0);
			break;
		case Alignment::TOPRIGHT:
			this->origin = Vector2(size.X, 0);
			break;
		case Alignment::MIDDLELEFT:
			this->origin = Vector2(0, size.Y / 2.f);
			break;
		case Alignment::MIDDLECENTER:
			this->origin = Vector2(size.X / 2.f, size.Y / 2.f);
			break;
		case Alignment::MIDDLERIGHT:
			this->origin = Vector2(size.X, size.Y / 2.f);
			break;
		case Alignment::BOTTOMLEFT:
			this->origin = Vector2(0, size.Y);
			break;
		case Alignment::BOTTOMCENTER:
			this->origin = Vector2(size.X / 2.f, size.Y);
			break;
		case Alignment::BOTTOMRIGHT:
			this->origin = size.toFloat();
			break;
	}
}
void Transform::setSize(const Vector2i& size)
{
	this->size = size;
}
void Transform::setRotation(const float& rotation)
{
	this->rotation = rotation;
}
void Transform::rotate(const float& rotation)
{
	this->rotation += rotation;
}

Transform Transform::compose(Transform transform1, Transform transform2)
{
	Transform transform = Transform();
	transform.position = transform1.position + transform2.position;
	transform.size = transform2.size;
	transform.scale = transform2.scale;
	transform.rotation = transform1.rotation + transform2.rotation;
	transform.origin = transform2.origin;

	return transform;
}
