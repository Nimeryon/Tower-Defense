#pragma once
enum TerrainTileType
{
	GRASS,
	DIRT,
	SAND,
	WATER
};

class TerrainTile
{
public:
	explicit TerrainTile(TerrainTileType type = GRASS);

	TerrainTileType getType() const;

private:
	TerrainTileType m_type;
};