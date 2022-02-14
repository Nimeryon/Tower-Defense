#pragma once
#include <vector>

namespace sf
{
	class RenderWindow;
	class RectangleShape;
}
class Terrain;
class Sprite;
class Path;
struct Vector2i;
enum TerrainTileType;

class TerrainView
{
public:
	TerrainView();

	void update();
	void drawTerrain(sf::RenderWindow& window);
	void drawCastle(sf::RenderWindow& window);

	void drawDebugPath(sf::RenderWindow& window, Path* path);

private:
	std::vector<Sprite*> m_sprites;
	Sprite* m_castleSprite;

	// Debug values
	sf::RectangleShape m_debugLine;

	int calculateTerrainAutotilingIndex(const TerrainTileType& type, const Vector2i& pos, const bool& outsideIsSame, const std::vector<TerrainTileType>& ignoredTypes) const;
};