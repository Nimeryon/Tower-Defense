#pragma once
#include <vector>

#include "Vector2i.h"

struct EndOfIntersection;
enum class DirectionType;

struct EndOfIntersection
{
	Vector2i m_position;
	DirectionType m_direction;

	EndOfIntersection(const Vector2i& position, const DirectionType& direction);
};

class Path
{
public:
	Path(const Vector2i& position, const DirectionType& oldDirection);
	~Path();

	Vector2i getPosition();
	Vector2i getOldPosition();

	void addDirection(const DirectionType& type, Path* pos);
	Path* getNextPath();
	Path* getPath(const DirectionType& type);
	DirectionType getOldDirection();
	int getAdjacentPathCount() const;
	
	static Path* generatePath(Path* path, const std::vector<EndOfIntersection>& endOfIntersections);

private:
	Vector2i m_position;
	DirectionType m_oldDirection;

	Path* m_pathNorth = nullptr;
	Path* m_pathSouth = nullptr;
	Path* m_pathWest = nullptr;
	Path* m_pathEast = nullptr;
};