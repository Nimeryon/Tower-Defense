#include "InputManager.h"
#include "Vector2.h"

// KeyBoard
std::map<sf::Keyboard::Key, bool> InputManager::m_keyboardState = getKeyBoardState();
std::map<sf::Keyboard::Key, bool> InputManager::m_oldKeyboardState = m_keyboardState;
// Mouse
std::map<sf::Mouse::Button, bool> InputManager::m_mouseState = getMouseState();
std::map<sf::Mouse::Button, bool> InputManager::m_oldmouseState = m_mouseState;

void InputManager::update()
{
	// Keyboard
	m_oldKeyboardState = m_keyboardState;
	m_keyboardState = getKeyBoardState();
	// Mouse
	m_oldmouseState = m_mouseState;
	m_mouseState = getMouseState();
}

// State
std::map<sf::Keyboard::Key, bool> InputManager::getKeyBoardState()
{
	std::map<sf::Keyboard::Key, bool> keyMap = {};

	for (int keyInt = sf::Keyboard::Key::A; keyInt != sf::Keyboard::Key::Pause; ++keyInt)
	{
		auto key = static_cast<sf::Keyboard::Key>(keyInt);
		keyMap[key] = sf::Keyboard::isKeyPressed(key);
	}

	return keyMap;
}
std::map<sf::Mouse::Button, bool> InputManager::getMouseState()
{
	std::map<sf::Mouse::Button, bool> mouseMap = {};

	for (int buttonInt = sf::Mouse::Button::Left; buttonInt != sf::Mouse::Button::XButton2; ++buttonInt)
	{
		auto button = static_cast<sf::Mouse::Button>(buttonInt);
		mouseMap[button] = sf::Mouse::isButtonPressed(button);
	}

	return mouseMap;
}

// KeyBoard Events
bool InputManager::isKey(sf::Keyboard::Key key) { return m_keyboardState[key]; }
bool InputManager::isKeyDown(sf::Keyboard::Key key) { return m_keyboardState[key] && !m_oldKeyboardState[key]; }
bool InputManager::isKeyUp(sf::Keyboard::Key key) { return !m_keyboardState[key] && m_oldKeyboardState[key]; }

// Mouse Events
Vector2 InputManager::getMousePosition()
{
	sf::Vector2i pos = sf::Mouse::getPosition();
	return Vector2(pos.x, pos.y);
}
void InputManager::setMousePosition(Vector2 position) { sf::Mouse::setPosition(position); }

bool InputManager::isMouseButton(sf::Mouse::Button button) { return m_mouseState[button]; }
bool InputManager::isMouseDownButton(sf::Mouse::Button button) { return m_mouseState[button] && !m_oldmouseState[button]; }
bool InputManager::isMouseUpButton(sf::Mouse::Button button) { return !m_mouseState[button] && m_oldmouseState[button]; }