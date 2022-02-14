#pragma once
class Sprite;

enum CursorType { HAND, HOVER };

class Cursor
{
public:


private:
	CursorType m_cursorType;

	Sprite* m_sprite;
};