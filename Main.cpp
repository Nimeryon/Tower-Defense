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
#include "FpsCounter.h"
#include "FrameTime.h"
#include "TickSystem.h"
#include "Random.h"
#include "Castle.h"

// Global Variables
int LEVEL_WIDTH = 32;
int LEVEL_HEIGHT = 20;
int CELL_WIDTH = 16;
int CELL_HEIGTH = 16;
float SCALE_FACTOR = 3.f;
bool DEBUG_MODE = false;

int WINDOW_WIDTH = LEVEL_WIDTH * CELL_WIDTH * SCALE_FACTOR;
int WINDOW_HEIGHT = LEVEL_HEIGHT * CELL_HEIGTH * SCALE_FACTOR;

std::string terrainEasyFilepath = "./Assets/Terrains/easy.txt";
std::string terrainNormalFilepath = "./Assets/Terrains/normal.txt";
std::string terrainHardFilepath = "./Assets/Terrains/hard.txt";
std::string terrainLongFilepath = "./Assets/Terrains/long.txt";

int main()
{
	// Setup random seed to now
	srand(time(0));

    // Initialize systems
    if (!ResourceManager::load()) return 1;
    Time time;
	TickSystem tick;

	// Initialize terrain
    Terrain* terrain = createTerrainFromFile(terrainLongFilepath);
    TerrainView terrainView = TerrainView();

	// Initialize castle
	new Castle(100);

	// Initialize fpsCounter
	FpsCounter fpsCounter;
	FrameTime frameTime;

	// Initialize window and clock
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tower Defense");
	window.setFramerateLimit(120);
	sf::Clock clock;

	TickSystem::system->onSmallEvent += EventHandler::bind([]() { new Enemy(100, 100, &ResourceManager::orcSprites[1]); });

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
		FrameTime::frameTime->deltaTimeText->setString("DeltaTime " + std::to_string(Time::deltaTime * 1000) + "ms");

		EngineHandler::update();
		InputManager::update();

		if (InputManager::isKeyDown(sf::Keyboard::F3)) DEBUG_MODE = !DEBUG_MODE;

        window.clear();

        terrainView.drawTerrain(window);
		EngineHandler::draw(window);

        window.display();

		EngineHandler::lateUpdate(window);
    }
}