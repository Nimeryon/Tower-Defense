#pragma once
namespace sf
{
	class Texture;
}
class Terrain;
enum TerrainTileType;

#include "Vector2i.h"

struct EntitySprites
{
	std::vector<sf::Sprite> spritesNorth;
	std::vector<sf::Sprite> spritesSouth;
	std::vector<sf::Sprite> spritesSide;

	EntitySprites(std::vector<sf::Sprite> spritesNorth, std::vector<sf::Sprite> spritesSouth, std::vector<sf::Sprite> spritesSide);
};

struct AnimationSprite
{
	std::vector<sf::Sprite> sprites;

	AnimationSprite(std::vector<sf::Sprite> sprites);
};

class ResourceManager
{
public:
	static bool load();

	static sf::Sprite spriteFromTexture(const sf::Texture& texture, const Vector2i& pos, const Vector2i& size);
	static sf::Sprite spriteFromTexture(const sf::Texture& texture, const Vector2i& pos);

	static int getRandomSpriteIndex(std::vector<sf::Sprite>& spriteList, const int& firstLuck);
	static sf::Sprite* getRandomSprite(std::vector<sf::Sprite>& spriteList, const int& firstLuck);

	static std::vector<sf::Sprite> grassSprites;
	static std::vector<sf::Sprite> grass_border_sprites;
	static std::vector<sf::Sprite> desertSprites;
	static std::vector <sf::Sprite> desertBorderSprites;
	static std::vector<sf::Sprite> waterSprites;
	static std::vector<sf::Sprite> dirtPathSprites;

	static std::vector<AnimationSprite> startPathSprites;
	static std::vector<AnimationSprite> waterBorderSprites;

	static std::vector<EntitySprites> orcSprites;

	static sf::Sprite castleSprite;

private:
	static sf::Texture m_terrainTexture;
	static sf::Texture m_monsterTexture;
	static sf::Texture m_towerTexture;
	static sf::Texture m_waterBorderTexture;
	static sf::Texture m_startPathTexture;

	static AnimationSprite generateAnimationSprite(const sf::Texture& texture, const int& startRow, const int& startCol, const int& frameCount);
	static EntitySprites generateEntityAnimations(const sf::Texture& texture, const int& startRow, const int& frameCount);
	static std::vector<sf::Sprite> generateAutotilingSet(const sf::Texture& texture, const int& startRow);
};