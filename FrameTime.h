#pragma once
#include <string>

namespace sf
{
	class Text;
	class RenderWindow;
}

class FrameTime
{
public:
	FrameTime();
	~FrameTime();
	
	void debugDraw(sf::RenderWindow& window);

	static FrameTime* frameTime;
	
	sf::Text* earlyUpdateTimeText;
	sf::Text* updateTimeText;
	sf::Text* lateUpdateTimeText;
	sf::Text* drawTimeText;
	sf::Text* debugDrawTimeText;
	sf::Text* deltaTimeText;
};