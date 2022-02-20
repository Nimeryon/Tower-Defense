#include "Direction.h"
#include "Vector2i.h"

DirectionType Direction::getDirection(const Vector2i& vector)
{
	if (vector == Vector2i::up()) return DirectionType::NORTH;
	if (vector == Vector2i::down()) return DirectionType::SOUTH;
	if (vector == Vector2i::left()) return DirectionType::WEST;
	if (vector == Vector2i::right()) return DirectionType::EAST;
}
DirectionType Direction::fromString(const std::string& string)
{
	if (string == "NORTH") return DirectionType::NORTH;
	if (string == "SOUTH") return DirectionType::SOUTH;
	if (string == "WEST") return DirectionType::WEST;
	if (string == "EAST") return DirectionType::EAST;
}

Vector2i Direction::getVector2i(const DirectionType& type)
{
	if (type == DirectionType::NORTH) return Vector2i::up();
	if (type == DirectionType::SOUTH) return Vector2i::down();
	if (type == DirectionType::WEST) return Vector2i::left();
	if (type == DirectionType::EAST) return Vector2i::right();
}
Vector2 Direction::getVector2(const DirectionType& type)
{
	if (type == DirectionType::NORTH) return Vector2::up();
	if (type == DirectionType::SOUTH) return Vector2::down();
	if (type == DirectionType::WEST) return Vector2::left();
	if (type == DirectionType::EAST) return Vector2::right();
}

DirectionType Direction::getOpposite(const DirectionType& direction)
{
	if (direction == DirectionType::NORTH) return DirectionType::SOUTH;
	if (direction == DirectionType::SOUTH) return DirectionType::NORTH;
	if (direction == DirectionType::WEST) return DirectionType::EAST;
	if (direction == DirectionType::EAST) return DirectionType::WEST;
}
