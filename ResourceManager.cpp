#include "ResourceManager.h"
#include "Random.h"
#include "Terrain.h"

extern int CELL_WIDTH;
extern int CELL_HEIGTH;

sf::Texture ResourceManager::m_terrainTexture = sf::Texture();
sf::Texture ResourceManager::m_waterBorderTexture = sf::Texture();
sf::Texture ResourceManager::m_monsterTexture = sf::Texture();
sf::Texture ResourceManager::m_towerTexture = sf::Texture();
sf::Texture ResourceManager::m_startPathTexture = sf::Texture();

std::vector<sf::Sprite> ResourceManager::grassSprites = {};
std::vector<sf::Sprite> ResourceManager::grass_border_sprites = {};
std::vector<sf::Sprite> ResourceManager::desertSprites = {};
std::vector<sf::Sprite> ResourceManager::desertBorderSprites = {};
std::vector<sf::Sprite> ResourceManager::waterSprites = {};
std::vector<sf::Sprite> ResourceManager::dirtPathSprites = {};

std::vector<AnimationSprite> ResourceManager::startPathSprites = {};
std::vector<AnimationSprite> ResourceManager::waterBorderSprites = {};

std::vector<EntitySprites> ResourceManager::orcSprites = {};

sf::Sprite ResourceManager::castleSprite = sf::Sprite();

EntitySprites::EntitySprites(std::vector<sf::Sprite> spritesNorth, std::vector<sf::Sprite> spritesSouth, std::vector<sf::Sprite> spritesSide) :
	spritesNorth(spritesNorth),
	spritesSouth(spritesSouth),
	spritesSide(spritesSide) {}

AnimationSprite::AnimationSprite(std::vector<sf::Sprite> sprites) : sprites(sprites) {}

bool ResourceManager::load()
{
	if (!m_terrainTexture.loadFromFile("./Assets/Sprites/terrain_tileset.png")) return false;
	if (!m_waterBorderTexture.loadFromFile("./Assets/Sprites/water_border_tileset.png")) return false;
	if (!m_monsterTexture.loadFromFile("./Assets/Sprites/monster_tileset.png")) return false;
	if (!m_towerTexture.loadFromFile("./Assets/Sprites/tower_tileset.png")) return false;
	if (!m_startPathTexture.loadFromFile("./Assets/Sprites/start_path_tileset.png")) return false;

	// Generating every terrain sprites from terrain texture
	// Grass sprites
	grassSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(9, 0)));
	grassSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(10, 0)));
	grassSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(9, 1)));
	grassSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(10, 1)));
	grassSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(9, 2)));
	grassSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(10, 2)));
	grassSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(9, 3)));
	grassSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(10, 3)));
	grassSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(9, 4)));
	grassSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(10, 4)));
	grassSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(9, 5)));
	grassSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(10, 5)));
	// Grass border sprites
	grass_border_sprites = generateAutotilingSet(m_terrainTexture, 3);
	// Desert sprites
	desertSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(11, 0)));
	desertSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(12, 0)));
	desertSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(11, 1)));
	desertSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(12, 1)));
	desertSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(11, 2)));
	desertSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(12, 2)));
	desertSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(11, 3)));
	desertSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(12, 3)));
	desertSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(11, 4)));
	desertSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(12, 4)));
	desertSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(11, 5)));
	desertSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(12, 5)));
	// Desert border sprites
	desertBorderSprites = generateAutotilingSet(m_terrainTexture, 6);
	// Water sprites
	waterSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(13, 0)));
	waterSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(13, 1)));
	waterSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(13, 2)));
	waterSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(13, 3)));
	waterSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(13, 4)));
	waterSprites.push_back(spriteFromTexture(m_terrainTexture, Vector2i(13, 5)));
	// Water border animated sprites
	waterBorderSprites.push_back({ generateAutotilingSet(m_waterBorderTexture, 0) });
	waterBorderSprites.push_back({ generateAutotilingSet(m_waterBorderTexture, 3) });
	waterBorderSprites.push_back({ generateAutotilingSet(m_waterBorderTexture, 6) });
	// Dirt path sprites
	dirtPathSprites = generateAutotilingSet(m_terrainTexture, 0);
	// Castle sprite
	castleSprite = spriteFromTexture(m_towerTexture, Vector2i(2, 0), Vector2i(32, 32));
	// Start path sprites
	startPathSprites.push_back(generateAnimationSprite(m_startPathTexture, 0, 0, 7));
	startPathSprites.push_back(generateAnimationSprite(m_startPathTexture, 0, 1, 7));
	startPathSprites.push_back(generateAnimationSprite(m_startPathTexture, 0, 2, 7));
	startPathSprites.push_back(generateAnimationSprite(m_startPathTexture, 0, 3, 7));
	// Orc sprites
	for (size_t i = 0; i < m_monsterTexture.getSize().x / 3 * CELL_WIDTH; ++i)
		orcSprites.push_back(generateEntityAnimations(m_monsterTexture, i * 3, 3));

	return true;
}

sf::Sprite ResourceManager::spriteFromTexture(const sf::Texture& texture, const Vector2i& pos, const Vector2i& size)
{
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(size.X * pos.X, size.Y * pos.Y, size.X, size.Y));

	return sprite;
}
sf::Sprite ResourceManager::spriteFromTexture(const sf::Texture& texture, const Vector2i& pos)
{
	return spriteFromTexture(texture, pos, Vector2i(CELL_WIDTH, CELL_HEIGTH));
}

AnimationSprite ResourceManager::generateAnimationSprite(const sf::Texture& texture, const int& startRow, const int& startCol, const int& frameCount)
{
	std::vector<sf::Sprite> sprites = {};
	for (size_t frame = 0; frame < frameCount; ++frame)
	{
		sprites.push_back(spriteFromTexture(texture, Vector2i(startRow + frame, startCol)));
	}
	return { sprites };
}
EntitySprites ResourceManager::generateEntityAnimations(const sf::Texture& texture, const int& startRow, const int& frameCount)
{
	std::vector<sf::Sprite> spritesNorth = {};
	std::vector<sf::Sprite> spritesSouth = {};
	std::vector<sf::Sprite> spritesSide = {};
	for (size_t frame = 0; frame < frameCount; ++frame)
	{
		spritesSide.push_back(spriteFromTexture(texture, Vector2i(startRow + frame, 0)));
		spritesSouth.push_back(spriteFromTexture(texture, Vector2i(startRow + frame, 1)));
		spritesNorth.push_back(spriteFromTexture(texture, Vector2i(startRow + frame, 2)));
	}

	return { spritesNorth, spritesSouth, spritesSide };
}
std::vector<sf::Sprite> ResourceManager::generateAutotilingSet(const sf::Texture& texture, const int& startRow)
{
	std::vector<sf::Sprite> spriteList;
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow, 0)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow + 1, 0)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow, 1)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow + 1, 1)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow + 2, 0)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow + 2, 1)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow, 2)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow + 1, 2)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow, 3)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow + 1, 3)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow + 2, 2)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow, 4)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow + 1, 4)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow, 5)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow + 1, 5)));
	spriteList.push_back(spriteFromTexture(texture, Vector2i(startRow + 2, 3)));

	return spriteList;
}

int ResourceManager::getRandomSpriteIndex(std::vector<sf::Sprite>& spriteList, const int& firstLuck)
{
	// Favoriser le premier index
	int spriteIndex = Random::random(0, spriteList.size() + firstLuck);
	if (spriteIndex < firstLuck) return 0;
	return spriteIndex - firstLuck;
}
sf::Sprite* ResourceManager::getRandomSprite(std::vector<sf::Sprite>& spriteList, const int& firstLuck)
{
	// Favoriser le premier sprite
	return &spriteList[getRandomSpriteIndex(spriteList, firstLuck)];
}