#include "TerrainTile.h"

TerrainTile::TerrainTile(TerrainTileType type) : m_type(type) {}
TerrainTileType TerrainTile::getType() const
{
	return m_type;
}
