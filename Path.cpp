#include "Path.h"
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
	delete m_pathEast;
	delete m_pathWest;
}

Vector2i Path::getPosition() { return m_position; }

void Path::addDirection(const DirectionType& type, Path* path)
{
	switch (type)
	{
		case NORTH:
			m_pathNorth = path;
			break;
		case SOUTH:
			m_pathSouth = path;
			break;
		case EAST:
			m_pathEast = path;
			break;
		case WEST:
			m_pathWest = path;
			break;
	}
}

bool Path::isPositionInPath(Path* path, Vector2i pos)
{
	if (path == nullptr) return false;
	if (path->getPosition() == pos) return true;

	if (path->getPath(NORTH) != nullptr && isPositionInPath(path->getPath(NORTH), pos)) return true;
	if (path->getPath(SOUTH) != nullptr && isPositionInPath(path->getPath(SOUTH), pos)) return true;
	if (path->getPath(EAST) != nullptr && isPositionInPath(path->getPath(EAST), pos)) return true;
	if (path->getPath(WEST) != nullptr) return isPositionInPath(path->getPath(WEST), pos);
}

Path* Path::getNextPath()
{
	std::vector<Path*> paths = {};
	if (m_pathNorth != nullptr) paths.push_back(m_pathNorth);
	if (m_pathSouth != nullptr) paths.push_back(m_pathSouth);
	if (m_pathEast != nullptr) paths.push_back(m_pathEast);
	if (m_pathWest != nullptr) paths.push_back(m_pathWest);

	if (paths.size() == 1) return paths[0];
	return paths[Random::random(0, paths.size())];
}

Path* Path::getPath(const DirectionType& type)
{
	switch (type)
	{
		case NORTH:
			return m_pathNorth;
		case SOUTH:
			return m_pathSouth;
		case EAST:
			return m_pathEast;
		case WEST:
			return m_pathWest;
	}
}

DirectionType Path::getOldDirection() { return m_oldDirection; }

int Path::getAdjacentPathCount() const
{
	int pathCount = 0;
	if (m_pathNorth != nullptr) pathCount++;
	if (m_pathNorth != nullptr) pathCount++;
	if (m_pathNorth != nullptr) pathCount++;
	if (m_pathNorth != nullptr) pathCount++;
	return pathCount;
}

Path* Path::generatePath(Path* path, std::vector<EndOfIntersection> endOfIntersections)
{
	for (EndOfIntersection endOfIntersection : endOfIntersections)
	{
		if (path->getPosition() == endOfIntersection.m_position)
		{
			path->addDirection(endOfIntersection.m_direction,
				generatePath(
					new Path(path->getPosition() + Direction::getVector2i(endOfIntersection.m_direction), Direction::getOpposite(path->getOldDirection())),
					endOfIntersections
				)
			);
			return path;
		}
	}

	Vector2i northPos = path->getPosition() + Direction::getVector2i(NORTH);
	if (path->getOldDirection() != NORTH && Terrain::terrain->getTile(northPos).getType() == DIRT)
		path->addDirection(NORTH, generatePath(new Path(northPos, SOUTH), endOfIntersections));

	Vector2i southPos = path->getPosition() + Direction::getVector2i(SOUTH);
	if (path->getOldDirection() != SOUTH && Terrain::terrain->getTile(southPos).getType() == DIRT)
		path->addDirection(SOUTH, generatePath(new Path(southPos, NORTH), endOfIntersections));

	Vector2i eastPos = path->getPosition() + Direction::getVector2i(EAST);
	if (path->getOldDirection() != EAST && Terrain::terrain->getTile(eastPos).getType() == DIRT)
		path->addDirection(EAST, generatePath(new Path(eastPos, WEST), endOfIntersections));

	Vector2i westPos = path->getPosition() + Direction::getVector2i(WEST);
	if (path->getOldDirection() != WEST && Terrain::terrain->getTile(westPos).getType() == DIRT)
		path->addDirection(WEST, generatePath(new Path(westPos, EAST), endOfIntersections));

	return path;
}