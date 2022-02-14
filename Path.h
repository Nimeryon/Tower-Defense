#pragma once
#include "Vector2i.h"

struct EndOfIntersection;
enum DirectionType;

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

	void addDirection(const DirectionType& type, Path* pos);
	Path* getNextPath();
	Path* getPath(const DirectionType& type);
	DirectionType getOldDirection();
	int getAdjacentPathCount() const;
	
	static bool isPositionInPath(Path* path, Vector2i pos);
	static Path* generatePath(Path* path, std::vector<EndOfIntersection> endOfIntersections);

private:
	Vector2i m_position;
	DirectionType m_oldDirection;

	Path* m_pathNorth = nullptr;
	Path* m_pathSouth = nullptr;
	Path* m_pathEast = nullptr;
	Path* m_pathWest = nullptr;
};