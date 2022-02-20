#pragma once
#include <string>

namespace sf
{
	class Text;
	class RenderWindow;
}

class FpsCounter
{
public:
	FpsCounter();
	~FpsCounter();

	void update();
	void debugDraw(sf::RenderWindow& window);

private:
	std::string m_fps;
	sf::Text* m_fpsText;
};