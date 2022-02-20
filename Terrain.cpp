#include "Terrain.h"
#include "TerrainTile.h"
#include "Vector2.h"
#include "Path.h"
#include "Direction.h"

#include <fstream>
#include <iostream>

#include "String.h"

extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;
extern int CELL_WIDTH;
extern int CELL_HEIGTH;
extern float SCALE_FACTOR;

Terrain* Terrain::terrain = nullptr;

Terrain::Terrain()
{
	m_terrain.resize(LEVEL_WIDTH * LEVEL_HEIGHT);
	terrain = this;
}
Terrain::~Terrain()
{
	m_terrain.clear();
	delete m_path;
}

TerrainTile& Terrain::getTile(const Vector2i& pos)
{
	if (pos.X < 0 || pos.X >= LEVEL_WIDTH || pos.Y < 0 || pos.Y >= LEVEL_HEIGHT) return m_terrain[0];
	return m_terrain[getArrayPos(pos)];
}

void Terrain::setPath(Path* path) { delete m_path; m_path = path; }
Path* Terrain::getPath() { return m_path; }

Vector2 Terrain::getWorldPosition(const Vector2i& terrainPos)
{
	return Vector2(CELL_WIDTH * terrainPos.X * SCALE_FACTOR, CELL_HEIGTH * terrainPos.Y * SCALE_FACTOR);
}
Vector2 Terrain::getWorldPosition(const int& x, const int& y)
{
	return getWorldPosition(Vector2i(x, y));
}

Vector2 Terrain::getWorldPositionCenter(const Vector2i& terrainPos)
{
	return getWorldPosition(terrainPos) + Vector2(CELL_WIDTH * SCALE_FACTOR / 2.f, CELL_HEIGTH * SCALE_FACTOR / 2.f);
}
Vector2 Terrain::getWorldPositionCenter(const int& x, const int& y)
{
	return getWorldPosition(x, y) + Vector2(CELL_WIDTH * SCALE_FACTOR / 2.f, CELL_HEIGTH * SCALE_FACTOR / 2.f);
}

Vector2 Terrain::getWorldPositionDirection(const Vector2i& terrainPos, const DirectionType& directionType)
{
	switch (directionType)
	{
		case DirectionType::NORTH:
			return getWorldPositionCenter(terrainPos) - Vector2(0, CELL_HEIGTH * SCALE_FACTOR / 2.f);
		case DirectionType::SOUTH:
			return getWorldPositionCenter(terrainPos) + Vector2(0, CELL_HEIGTH * SCALE_FACTOR / 2.f);
		case DirectionType::WEST:
			return getWorldPositionCenter(terrainPos) - Vector2(CELL_WIDTH * SCALE_FACTOR / 2.f, 0);
		case DirectionType::EAST:
			return getWorldPositionCenter(terrainPos) + Vector2(CELL_WIDTH * SCALE_FACTOR / 2.f, 0);
	}
	return Vector2::zero();
}
Vector2 Terrain::getWorldPositionDirection(const int& x, const int& y, const DirectionType& directionType)
{
	return getWorldPositionDirection(Vector2i(x, y), directionType);
}

bool Terrain::isTileType(const TerrainTileType& type, const Vector2i& pos, const bool& outsideIsSame, const std::vector<TerrainTileType>& ignoredTypes)
{
	if (pos.X < 0 || pos.X >= LEVEL_WIDTH || pos.Y < 0 || pos.Y >= LEVEL_HEIGHT) return outsideIsSame;
	for (TerrainTileType tileType : ignoredTypes)
		if (getTile(pos).getType() == tileType) return true;
	return getTile(pos).getType() == type;
}

int Terrain::getArrayPos(const Vector2i& pos) const { return pos.X + pos.Y * LEVEL_WIDTH; }

Terrain* createTerrainFromFile(const std::string& filepath)
{
	std::ifstream file(filepath);
	
	std::string line;
	Terrain* terrain = new Terrain();

	// Generate terrain tiles
	for (size_t y = 0; y < LEVEL_HEIGHT; ++y)
	{
		getline(file, line);
		for (size_t x = 0; x < LEVEL_WIDTH; ++x)
		{
			char character = line[x];
			Vector2i pos = Vector2i(x, y);
			
			if (character == 'G') terrain->getTile(pos) = TerrainTile();
			else if (character == 'D') terrain->getTile(pos) = TerrainTile(TerrainTileType::DIRT);
			else if (character == 'S') terrain->getTile(pos) = TerrainTile(TerrainTileType::SAND);
			else if (character == 'W') terrain->getTile(pos) = TerrainTile(TerrainTileType::WATER);
		}
	}

	// Generate terrain paths
	getline(file, line);
	std::vector<std::string> startPositionValues = String::split(line, ',');
	int pathX = std::stoi(startPositionValues[0]);
	int pathY = std::stoi(startPositionValues[1]);
	DirectionType startDirection = Direction::fromString(startPositionValues[2]);
	Vector2i startPosition = Vector2i(pathX, pathY);

	// Get list end of intersections
	getline(file, line);
	int nbrEndOFIntersection = std::stoi(line);
	std::vector<EndOfIntersection> endOfIntersections = {};
	for (int i = 0; i < nbrEndOFIntersection; ++i)
	{
		getline(file, line);
		std::vector<std::string> intersectionPositionValues = String::split(line, ',');
		int intersectionX = std::stoi(intersectionPositionValues[0]);
		int intersectionY = std::stoi(intersectionPositionValues[1]);
		Vector2i intersectionPosition = Vector2i(intersectionX, intersectionY);
		endOfIntersections.push_back(EndOfIntersection(intersectionPosition, Direction::fromString(intersectionPositionValues[2])));
	}
	
	terrain->setPath(Path::generatePath(new Path(startPosition, Direction::getOpposite(startDirection)), endOfIntersections));

	// Generate terrain castle
	getline(file, line);
	std::vector<std::string> castlePositionValues = String::split(line, ',');
	int castleX = std::stoi(castlePositionValues[0]);
	int castleY = std::stoi(castlePositionValues[1]);
	terrain->castlePosition = Vector2i(castleX, castleY);

	return terrain;
}
