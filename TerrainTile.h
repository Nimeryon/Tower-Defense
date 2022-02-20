#pragma once
enum class TerrainTileType
{
	GRASS,
	DIRT,
	SAND,
	WATER
};

class TerrainTile
{
public:
	explicit TerrainTile(TerrainTileType type = TerrainTileType::GRASS);

	TerrainTileType getType() const;

private:
	TerrainTileType m_type;
};