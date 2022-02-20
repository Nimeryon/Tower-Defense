#pragma once
#include <string>

#include "Vector2.h"

struct Vector2i;

enum class DirectionType
{
	NORTH,
	WEST,
	SOUTH,
	EAST
};

class Direction
{
public:
	static DirectionType getDirection(const Vector2i& vector);
	static DirectionType fromString(const std::string& string);
	static DirectionType getOpposite(const DirectionType& direction);

	static Vector2i getVector2i(const DirectionType& type);
	static Vector2 getVector2(const DirectionType& type);
};