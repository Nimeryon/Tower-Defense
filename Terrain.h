#pragma once
class Path;
class TerrainTile;
enum TerrainTileType;

#include <vector>

#include "Vector2i.h"
#include "Vector2.h"
#include "Direction.h"

class Terrain
{
public:
	Terrain();
	~Terrain();

	TerrainTile& getTile(const Vector2i& pos);

	void setPath(Path* path);
	Path* getPath();

	bool isTileType(const TerrainTileType& type, const Vector2i& pos, const bool& outsideIsSame, const std::vector<TerrainTileType>& ignoredTypes);
	int getArrayPos(const Vector2i& pos) const;

	static Vector2 getWorldPosition(const Vector2i& terrainPos);
	static Vector2 getWorldPosition(const int& x, const int& y);
	static Vector2 getWorldPositionCenter(const Vector2i& terrainPos);
	static Vector2 getWorldPositionCenter(const int& x, const int& y);
	static Vector2 getWorldPositionDirection(const Vector2i& terrainPos, const DirectionType& directionType);
	static Vector2 getWorldPositionDirection(const int& x, const int& y, const DirectionType& directionType);

	static Terrain* terrain;

	Vector2i castlePosition = Vector2i::zero();

private:

	std::vector<TerrainTile> m_terrain;
	Path* m_path;
};

Terrain* createTerrainFromFile(const std::string& filepath);