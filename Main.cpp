#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

#include "AnimatedSprite.h"
#include "EngineHandler.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Terrain.h"
#include "TerrainView.h"
#include "Time.h"
#include "Enemy.h"
#include "TickSystem.h"
#include "Random.h"

// Global Variables
int LEVEL_WIDTH = 24;
int LEVEL_HEIGHT = 16;
int CELL_WIDTH = 16;
int CELL_HEIGTH = 16;
float SCALE_FACTOR = 3.f;
bool DEBUG_MODE = false;

std::string terrainEasyFilepath = "./Assets/Terrains/easy.txt";
std::string terrainNormalFilepath = "./Assets/Terrains/normal.txt";
std::string terrainHardFilepath = "./Assets/Terrains/hard.txt";

int main()
{
	// Setup random seed to now
	srand(time(0));

    // Initialize systems
    if (!ResourceManager::load()) return 1;
    Time time;
	TickSystem tick;

	// Initialize terrain
    Terrain* terrain = createTerrainFromFile(terrainEasyFilepath);
    TerrainView terrainView = TerrainView();

	// Initialize window and clock
	sf::RenderWindow window(sf::VideoMode(LEVEL_WIDTH * CELL_WIDTH * SCALE_FACTOR, LEVEL_HEIGHT * CELL_HEIGTH * SCALE_FACTOR), "Tower Defense");
	sf::Clock clock;

	// Test ennemy
	tick.onLittleEvent += EventHandler::bind([]()
	{
		new Enemy(100, 100, &ResourceManager::orcSprites[Random::random(0, 9)]);
	});

	// Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
	        switch (event.type)
	        {
	            case sf::Event::Closed:
	                window.close();
	                break;

				default: break;
	        }
        }

		// Update Systems
		time.setTime(clock.restart().asSeconds());
		EngineHandler::update();
		InputManager::update();

		if (InputManager::isKeyDown(sf::Keyboard::F3)) DEBUG_MODE = !DEBUG_MODE;

		if (InputManager::isKeyDown(sf::Keyboard::Num1))
		{
			delete terrain;
			terrain = createTerrainFromFile(terrainEasyFilepath);
			terrainView.update();
		}
		else if (InputManager::isKeyDown(sf::Keyboard::Num2))
		{
			delete terrain;
			terrain = createTerrainFromFile(terrainNormalFilepath);
			terrainView.update();
		}
		else if (InputManager::isKeyDown(sf::Keyboard::Num3))
		{
			delete terrain;
			terrain = createTerrainFromFile(terrainHardFilepath);
			terrainView.update();
		}

        window.clear();

        terrainView.drawTerrain(window);
		EngineHandler::draw(&window);
		terrainView.drawCastle(window);

        window.display();

		EngineHandler::lateUpdate(window);
    }
}