#include "Direction.h"
#include "Vector2i.h"

DirectionType Direction::getDirection(const Vector2i& vector)
{
	if (vector == Vector2i::up()) return NORTH;
	if (vector == Vector2i::down()) return SOUTH;
	if (vector == Vector2i::left()) return EAST;
	if (vector == Vector2i::right()) return WEST;
}
DirectionType Direction::fromString(const std::string& string)
{
	if (string == "NORTH") return NORTH;
	if (string == "SOUTH") return SOUTH;
	if (string == "EAST") return EAST;
	if (string == "WEST") return WEST;
}

Vector2i Direction::getVector2i(const DirectionType& type)
{
	if (type == NORTH) return Vector2i::up();
	if (type == SOUTH) return Vector2i::down();
	if (type == EAST) return Vector2i::left();
	if (type == WEST) return Vector2i::right();
}
Vector2 Direction::getVector2(const DirectionType& type)
{
	if (type == NORTH) return Vector2::up();
	if (type == SOUTH) return Vector2::down();
	if (type == EAST) return Vector2::left();
	if (type == WEST) return Vector2::right();
}

DirectionType Direction::getOpposite(const DirectionType& direction)
{
	if (direction == NORTH) return SOUTH;
	if (direction == SOUTH) return NORTH;
	if (direction == EAST) return WEST;
	if (direction == WEST) return EAST;
}
