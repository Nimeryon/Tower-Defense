#pragma once
#include <vector>

#include "TerrainTile.h"

namespace sf
{
	class RenderWindow;
	class RectangleShape;
}
class Terrain;
class Sprite;
class Path;
struct Vector2i;

class TerrainView
{
public:
	TerrainView();
	~TerrainView();

	void update();
	void drawTerrain(sf::RenderWindow& window);

	void drawDebugPath(sf::RenderWindow& window, Path* path);

private:
	std::vector<Sprite*> m_sprites;

	// Debug values
	sf::RectangleShape* m_debugRectangle;
	sf::Text* m_debugPathCount;

	int calculateTerrainAutotilingIndex(const TerrainTileType& type, const Vector2i& pos, const bool& outsideIsSame, const std::vector<TerrainTileType>& ignoredTypes) const;
};