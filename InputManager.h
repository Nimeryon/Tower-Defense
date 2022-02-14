#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <map>

struct Vector2;

class InputManager
{
public:
	static void update();

	// KeyBoard Events
	static bool isKey(sf::Keyboard::Key key);
	static bool isKeyDown(sf::Keyboard::Key key);
	static bool isKeyUp(sf::Keyboard::Key key);

	// Mouse Events
	static Vector2 getMousePosition();
	static void setMousePosition(Vector2 position);

	static bool isMouseButton(sf::Mouse::Button button);
	static bool isMouseDownButton(sf::Mouse::Button button);
	static bool isMouseUpButton(sf::Mouse::Button button);

private:
	// State
	static std::map<sf::Keyboard::Key, bool> getKeyBoardState();
	static std::map<sf::Mouse::Button, bool> getMouseState();

	// KeyBoard
	static std::map<sf::Keyboard::Key, bool> m_keyboardState;
	static std::map<sf::Keyboard::Key, bool> m_oldKeyboardState;
	// Mouse
	static std::map<sf::Mouse::Button, bool> m_mouseState;
	static std::map<sf::Mouse::Button, bool> m_oldmouseState;
};