#include "Path.h"

#include <iostream>

#include "Direction.h"
#include "Random.h"
#include "Terrain.h"
#include "TerrainTile.h"

EndOfIntersection::EndOfIntersection(const Vector2i& position, const DirectionType& direction) : m_position(position), m_direction(direction) {}

Path::Path(const Vector2i& position, const DirectionType& oldDirection) : m_position(position), m_oldDirection(oldDirection) {}
Path::~Path()
{
	delete m_pathNorth;
	delete m_pathSouth;
	delete m_pathWest;
	delete m_pathEast;
}

Vector2i Path::getPosition() { return m_position; }
Vector2i Path::getOldPosition()
{
	return m_position + Direction::getVector2i(m_oldDirection);
}

void Path::addDirection(const DirectionType& type, Path* path)
{
	switch (type)
	{
		case DirectionType::NORTH:
			m_pathNorth = path;
			break;
		case DirectionType::SOUTH:
			m_pathSouth = path;
			break;
		case DirectionType::WEST:
			m_pathWest = path;
			break;
		case DirectionType::EAST:
			m_pathEast = path;
			break;
	}
}

Path* Path::getNextPath()
{
	std::vector<Path*> paths = {};
	if (m_pathNorth != nullptr) paths.push_back(m_pathNorth);
	if (m_pathSouth != nullptr) paths.push_back(m_pathSouth);
	if (m_pathWest != nullptr) paths.push_back(m_pathWest);
	if (m_pathEast != nullptr) paths.push_back(m_pathEast);
	
	if (paths.size() == 1) return paths[0];
	return paths[Random::random(0, paths.size())];
}

Path* Path::getPath(const DirectionType& type)
{
	switch (type)
	{
		case DirectionType::NORTH:
			return m_pathNorth;
		case DirectionType::SOUTH:
			return m_pathSouth;
		case DirectionType::WEST:
			return m_pathWest;
		case DirectionType::EAST:
			return m_pathEast;
	}

	return this;
}

DirectionType Path::getOldDirection() { return m_oldDirection; }

int Path::getAdjacentPathCount() const
{
	int pathCount = 0;
	if (m_pathNorth != nullptr) pathCount++;
	if (m_pathSouth != nullptr) pathCount++;
	if (m_pathWest != nullptr) pathCount++;
	if (m_pathEast != nullptr) pathCount++;
	return pathCount;
}

Path* Path::generatePath(Path* path, const std::vector<EndOfIntersection>& endOfIntersections)
{
	for (EndOfIntersection endOfIntersection : endOfIntersections)
	{
		if (path->getPosition() == endOfIntersection.m_position)
		{
			path->addDirection(endOfIntersection.m_direction,
				generatePath(
					new Path(path->getPosition() + Direction::getVector2i(endOfIntersection.m_direction), Direction::getOpposite(endOfIntersection.m_direction)),
					endOfIntersections
				)
			);
			return path;
		}
	}

	Vector2i northPos = path->getPosition() + Direction::getVector2i(DirectionType::NORTH);
	if (path->getOldDirection() != DirectionType::NORTH && Terrain::terrain->getTile(northPos).getType() == TerrainTileType::DIRT)
		path->addDirection(DirectionType::NORTH, generatePath(new Path(northPos, DirectionType::SOUTH), endOfIntersections));

	Vector2i southPos = path->getPosition() + Direction::getVector2i(DirectionType::SOUTH);
	if (path->getOldDirection() != DirectionType::SOUTH && Terrain::terrain->getTile(southPos).getType() == TerrainTileType::DIRT)
		path->addDirection(DirectionType::SOUTH, generatePath(new Path(southPos, DirectionType::NORTH), endOfIntersections));

	Vector2i westPos = path->getPosition() + Direction::getVector2i(DirectionType::WEST);
	if (path->getOldDirection() != DirectionType::WEST && Terrain::terrain->getTile(westPos).getType() == TerrainTileType::DIRT)
		path->addDirection(DirectionType::WEST, generatePath(new Path(westPos, DirectionType::EAST), endOfIntersections));

	Vector2i eastPos = path->getPosition() + Direction::getVector2i(DirectionType::EAST);
	if (path->getOldDirection() != DirectionType::EAST && Terrain::terrain->getTile(eastPos).getType() == TerrainTileType::DIRT)
		path->addDirection(DirectionType::EAST, generatePath(new Path(eastPos, DirectionType::WEST), endOfIntersections));

	return path;
}