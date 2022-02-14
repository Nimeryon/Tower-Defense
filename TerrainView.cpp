#include <SFML/Graphics.hpp>

#include "Sprite.h"
#include "AnimatedSprite.h"
#include "TerrainView.h"

#include <iostream>

#include "Terrain.h"
#include "Vector2i.h"
#include "ResourceManager.h"
#include "TerrainTile.h"
#include "Vector2.h"
#include "Path.h"

extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;
extern int CELL_WIDTH;
extern int CELL_HEIGTH;
extern float SCALE_FACTOR;
extern bool DEBUG_MODE;

TerrainView::TerrainView() : m_debugLine(sf::RectangleShape())
{
	m_sprites.resize(LEVEL_WIDTH * LEVEL_HEIGHT);
	m_castleSprite = new Sprite(&ResourceManager::castleSprite);

	// Setup debugLine
	m_debugLine.setScale(Vector2i(SCALE_FACTOR));
	m_debugLine.setFillColor(sf::Color(255, 0, 0, 128));

	update();
}

void TerrainView::update()
{
	for (size_t y = 0; y < LEVEL_HEIGHT; ++y)
	{
		for (size_t x = 0; x < LEVEL_WIDTH; ++x)
		{
			Vector2i pos = Vector2i(x, y);
			delete m_sprites[Terrain::terrain->getArrayPos(pos)];

			TerrainTileType type = Terrain::terrain->getTile(pos).getType();
			int tileIndex;
			switch (type)
			{
				case GRASS:
					tileIndex = calculateTerrainAutotilingIndex(type, pos, true, {DIRT, SAND});
					if (pos == Terrain::terrain->castlePosition
						|| pos == Vector2i(Terrain::terrain->castlePosition.X - 1, Terrain::terrain->castlePosition.Y)
						|| pos == Vector2i(Terrain::terrain->castlePosition.X + 1, Terrain::terrain->castlePosition.Y)
						|| pos == Vector2i(Terrain::terrain->castlePosition.X, Terrain::terrain->castlePosition.Y - 1)
						|| pos == Vector2i(Terrain::terrain->castlePosition.X, Terrain::terrain->castlePosition.Y + 1)
						|| pos == Vector2i(Terrain::terrain->castlePosition.X - 1, Terrain::terrain->castlePosition.Y - 1)
						|| pos == Vector2i(Terrain::terrain->castlePosition.X - 1, Terrain::terrain->castlePosition.Y + 1)
						|| pos == Vector2i(Terrain::terrain->castlePosition.X + 1, Terrain::terrain->castlePosition.Y - 1)
						|| pos == Vector2i(Terrain::terrain->castlePosition.X + 1, Terrain::terrain->castlePosition.Y + 1))
					{
						m_sprites[Terrain::terrain->getArrayPos(pos)] = new Sprite(&ResourceManager::grassSprites[0]);
					}
					else if (tileIndex == 10) m_sprites[Terrain::terrain->getArrayPos(pos)] = new Sprite(ResourceManager::getRandomSprite(ResourceManager::grassSprites, 8));
					else m_sprites[Terrain::terrain->getArrayPos(pos)] = new Sprite(&ResourceManager::grass_border_sprites[tileIndex]);
					break;

				case DIRT:
					if (pos == Terrain::terrain->getPath()->getPosition())
					{
						int startPathIndex;
						if (Terrain::terrain->getPath()->getOldDirection() == NORTH) startPathIndex = 1;
						if (Terrain::terrain->getPath()->getOldDirection() == SOUTH) startPathIndex = 0;
						if (Terrain::terrain->getPath()->getOldDirection() == EAST) startPathIndex = 2;
						if (Terrain::terrain->getPath()->getOldDirection() == WEST) startPathIndex = 3;

						AnimatedSprite* animatedSprite = new AnimatedSprite(&ResourceManager::startPathSprites[startPathIndex].sprites[0], .15f);
						animatedSprite->addFrame(&ResourceManager::startPathSprites[startPathIndex].sprites[1]);
						animatedSprite->addFrame(&ResourceManager::startPathSprites[startPathIndex].sprites[2]);
						animatedSprite->addFrame(&ResourceManager::startPathSprites[startPathIndex].sprites[3]);
						animatedSprite->addFrame(&ResourceManager::startPathSprites[startPathIndex].sprites[4]);
						animatedSprite->addFrame(&ResourceManager::startPathSprites[startPathIndex].sprites[5]);
						animatedSprite->addFrame(&ResourceManager::startPathSprites[startPathIndex].sprites[6]);
						animatedSprite->addFrame(&ResourceManager::startPathSprites[startPathIndex].sprites[5]);
						animatedSprite->addFrame(&ResourceManager::startPathSprites[startPathIndex].sprites[3]);
						animatedSprite->addFrame(&ResourceManager::startPathSprites[startPathIndex].sprites[2]);
						animatedSprite->addFrame(&ResourceManager::startPathSprites[startPathIndex].sprites[1]);

						m_sprites[Terrain::terrain->getArrayPos(pos)] = animatedSprite;
					}
					else
					{
						tileIndex = calculateTerrainAutotilingIndex(type, pos, false, {});
						m_sprites[Terrain::terrain->getArrayPos(pos)] = new Sprite(&ResourceManager::dirtPathSprites[tileIndex]);
					}
					break;

				case SAND:
					tileIndex = calculateTerrainAutotilingIndex(type, pos, true, { DIRT, GRASS });
					if (pos == Terrain::terrain->castlePosition
						|| pos == Vector2i(Terrain::terrain->castlePosition.X - 1, Terrain::terrain->castlePosition.Y)
						|| pos == Vector2i(Terrain::terrain->castlePosition.X + 1, Terrain::terrain->castlePosition.Y)
						|| pos == Vector2i(Terrain::terrain->castlePosition.X, Terrain::terrain->castlePosition.Y - 1)
						|| pos == Vector2i(Terrain::terrain->castlePosition.X, Terrain::terrain->castlePosition.Y + 1)
						|| pos == Vector2i(Terrain::terrain->castlePosition.X - 1, Terrain::terrain->castlePosition.Y - 1)
						|| pos == Vector2i(Terrain::terrain->castlePosition.X - 1, Terrain::terrain->castlePosition.Y + 1)
						|| pos == Vector2i(Terrain::terrain->castlePosition.X + 1, Terrain::terrain->castlePosition.Y - 1)
						|| pos == Vector2i(Terrain::terrain->castlePosition.X + 1, Terrain::terrain->castlePosition.Y + 1))
					{
						m_sprites[Terrain::terrain->getArrayPos(pos)] = new Sprite(&ResourceManager::desertSprites[0]);
					}
					else if (tileIndex == 10) m_sprites[Terrain::terrain->getArrayPos(pos)] = new Sprite(ResourceManager::getRandomSprite(ResourceManager::desertSprites, 8));
					else m_sprites[Terrain::terrain->getArrayPos(pos)] = new Sprite(&ResourceManager::desertBorderSprites[tileIndex]);
					break;
					
				case WATER:
					tileIndex = calculateTerrainAutotilingIndex(type, pos, true, {});
					if (tileIndex == 10)
						m_sprites[Terrain::terrain->getArrayPos(pos)] = new Sprite(ResourceManager::getRandomSprite(ResourceManager::waterSprites, 8));
					else 
					{
						AnimatedSprite* animatedSprite = new AnimatedSprite(&ResourceManager::waterBorderSprites[0].sprites[tileIndex], .4f);
						animatedSprite->addFrame(&ResourceManager::waterBorderSprites[1].sprites[tileIndex]);
						animatedSprite->addFrame(&ResourceManager::waterBorderSprites[2].sprites[tileIndex]);
						animatedSprite->addFrame(&ResourceManager::waterBorderSprites[1].sprites[tileIndex]);

						m_sprites[Terrain::terrain->getArrayPos(pos)] = animatedSprite;
					}
					break;
			}
		}
	}
	
	m_castleSprite->setPosition(Terrain::getWorldPosition(Terrain::terrain->castlePosition));
	m_castleSprite->setScale(Vector2(SCALE_FACTOR));
	m_castleSprite->setOrigin(Vector2(CELL_WIDTH / 2.0f, CELL_HEIGTH));
}
void TerrainView::drawTerrain(sf::RenderWindow& window)
{
	for (size_t y = 0; y < LEVEL_HEIGHT; ++y)
	{
		for (size_t x = 0; x < LEVEL_WIDTH; ++x)
		{
			Vector2i pos = Vector2i(x, y);

			m_sprites[Terrain::terrain->getArrayPos(pos)]->setPosition(Terrain::getWorldPosition(pos));
			m_sprites[Terrain::terrain->getArrayPos(pos)]->setScale(Vector2(SCALE_FACTOR));
			window.draw(*m_sprites[Terrain::terrain->getArrayPos(pos)]->getSprite());
		}
	}
	window.draw(*m_castleSprite->getSprite());

	if (DEBUG_MODE) drawDebugPath(window, Terrain::terrain->getPath());
}

void TerrainView::drawCastle(sf::RenderWindow& window)
{
	window.draw(*m_castleSprite->getSprite());
}

void TerrainView::drawDebugPath(sf::RenderWindow& window, Path* path)
{
	// Draw cube in path center
	m_debugLine.setFillColor(sf::Color(255, 0, 0, 255));
	m_debugLine.setSize(Vector2i(4, 4));
	m_debugLine.setPosition(Terrain::getWorldPositionCenter(path->getPosition()));
	m_debugLine.setOrigin(Vector2i(2, 2));

	window.draw(m_debugLine);
	m_debugLine.setFillColor(sf::Color(255, 0, 0, 64));

	if (path->getPath(NORTH) != nullptr)
	{
		// Draw self path half line
		m_debugLine.setSize(Vector2i(2 ,CELL_HEIGTH / 2 - 2));
		m_debugLine.setPosition(Terrain::getWorldPositionCenter(path->getPosition()));
		m_debugLine.setOrigin(Vector2i(1, CELL_HEIGTH / 2));

		window.draw(m_debugLine);

		// Draw next path line
		m_debugLine.setSize(Vector2i(2, CELL_HEIGTH / 2 - 2));
		m_debugLine.setPosition(Terrain::getWorldPositionCenter(path->getPath(NORTH)->getPosition()));
		m_debugLine.setOrigin(Vector2i(1, -2));

		window.draw(m_debugLine);

		drawDebugPath(window, path->getPath(NORTH));
	}

	if (path->getPath(SOUTH) != nullptr)
	{
		// Draw self path half line
		m_debugLine.setSize(Vector2i(2, CELL_HEIGTH / 2 - 2));
		m_debugLine.setPosition(Terrain::getWorldPositionCenter(path->getPosition()));
		m_debugLine.setOrigin(Vector2i(1, -2));

		window.draw(m_debugLine);

		// Draw next path line
		m_debugLine.setSize(Vector2i(2, CELL_HEIGTH / 2 - 2));
		m_debugLine.setPosition(Terrain::getWorldPositionCenter(path->getPath(SOUTH)->getPosition()));
		m_debugLine.setOrigin(Vector2i(1, CELL_HEIGTH / 2));

		window.draw(m_debugLine);

		drawDebugPath(window, path->getPath(SOUTH));
	}

	if (path->getPath(EAST) != nullptr)
	{
		// Draw self path half line
		m_debugLine.setSize(Vector2i(CELL_WIDTH / 2 - 2, 2));
		m_debugLine.setPosition(Terrain::getWorldPositionCenter(path->getPosition()));
		m_debugLine.setOrigin(Vector2i(CELL_WIDTH / 2, 1));

		window.draw(m_debugLine);

		// Draw next path line
		m_debugLine.setSize(Vector2i(CELL_WIDTH / 2 - 2, 2));
		m_debugLine.setPosition(Terrain::getWorldPositionCenter(path->getPath(EAST)->getPosition()));
		m_debugLine.setOrigin(Vector2i(-2, 1));

		window.draw(m_debugLine);

		drawDebugPath(window, path->getPath(EAST));
	}

	if (path->getPath(WEST) != nullptr)
	{
		// Draw self path half line
		m_debugLine.setSize(Vector2i(CELL_WIDTH / 2 - 2, 2));
		m_debugLine.setPosition(Terrain::getWorldPositionCenter(path->getPosition()));
		m_debugLine.setOrigin(Vector2i(-2, 1));

		window.draw(m_debugLine);

		// Draw next path line
		m_debugLine.setSize(Vector2i(CELL_WIDTH / 2 - 2, 2));
		m_debugLine.setPosition(Terrain::getWorldPositionCenter(path->getPath(WEST)->getPosition()));
		m_debugLine.setOrigin(Vector2i(CELL_WIDTH / 2, 1));

		window.draw(m_debugLine);

		drawDebugPath(window, path->getPath(WEST));
	}
}

int TerrainView::calculateTerrainAutotilingIndex(const TerrainTileType& type, const Vector2i& pos, const bool& outsideIsSame, const std::vector<TerrainTileType>& ignoredTypes) const
{
	const std::vector<int> tileIndexArray = { 15, 14, 13, 3, 11, 4, 2, 8, 12, 1, 5, 7, 0, 9, 6, 10 };

	std::string neighbourBinary = "";
	neighbourBinary += Terrain::terrain->isTileType(type, Vector2i(pos.X, pos.Y + 1), outsideIsSame, ignoredTypes) ? "1" : "0"; // 1000
	neighbourBinary += Terrain::terrain->isTileType(type, Vector2i(pos.X + 1, pos.Y), outsideIsSame, ignoredTypes) ? "1" : "0"; // 0100
	neighbourBinary += Terrain::terrain->isTileType(type, Vector2i(pos.X, pos.Y - 1), outsideIsSame, ignoredTypes) ? "1" : "0"; // 0010
	neighbourBinary += Terrain::terrain->isTileType(type, Vector2i(pos.X - 1, pos.Y), outsideIsSame, ignoredTypes) ? "1" : "0"; // 0001

	int neighbourIndex = std::stoi(neighbourBinary, 0, 2);
	return tileIndexArray[neighbourIndex];
}