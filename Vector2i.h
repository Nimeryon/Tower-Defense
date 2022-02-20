#pragma once
#include "Vector2.h"

struct Vector2i
{
	int X;
	int Y;

	Vector2i(int value) : X(value), Y(value) {}
	Vector2i(int x, int y) : X(x), Y(y) {}

	// Static constructors
	static Vector2i zero() { return Vector2i(0, 0); }
	static Vector2i one() { return Vector2i(1, 1); }
	static Vector2i left() { return Vector2i(-1, 0); }
	static Vector2i right() { return Vector2i(1, 0); }
	static Vector2i up() { return Vector2i(0, -1); }
	static Vector2i down() { return Vector2i(0, 1); }

	// Static methods
	static int determinant(const Vector2i& v1, const Vector2i& v2)
	{
		return v1.X * v2.Y - v2.X * v1.Y;
	}

	// Methods
	void translate(const Vector2i& v)
	{
		*this += v;
	}
	void scale(const Vector2i& v)
	{
		*this *= v;
	}
	void scale(const int& f)
	{
		*this *= f;
	}

	int determinant(const Vector2i& v) const
	{
		return determinant(*this, v);
	}

	// Operator when used with SFML
	static Vector2i from(sf::Vector2f vector) { return Vector2i((int)vector.x, (int)vector.y); }
	static Vector2i from(sf::Vector2i vector) { return Vector2i(vector.x, vector.y); }
	static Vector2i from(Vector2 vector) { return Vector2i((int)vector.X, (int)vector.Y); }
	Vector2 toFloat() { return Vector2((int)X, (int)Y); }
	operator sf::Vector2f() const { return { (float)X, (float)Y }; }
	operator sf::Vector2i() const { return { X, Y }; }

	// Operators
	Vector2i& operator=(const Vector2i& v2) = default;

	Vector2i& operator+=(const Vector2i& v2)
	{
		X += v2.X;
		Y += v2.Y;

		return *this;
	}
	Vector2i& operator-=(const Vector2i& v2)
	{
		X -= v2.X;
		Y -= v2.Y;

		return *this;
	}
	Vector2i& operator*=(const Vector2i& v2)
	{
		X *= v2.X;
		Y *= v2.Y;

		return *this;
	}
	Vector2i& operator*=(const int& f)
	{
		X *= f;
		Y *= f;

		return *this;
	}
	Vector2i& operator/=(const Vector2i& v2)
	{
		X /= v2.X;
		Y /= v2.Y;

		return *this;
	}
};

// Operators
inline std::ostream& operator<<(std::ostream& os, const Vector2i& v)
{
	os << "X: " << v.X << " Y: " << v.Y << std::endl;
	return os;
}

inline bool operator==(const Vector2i& v1, const Vector2i& v2)
{
	return v1.X == v2.X && v1.Y == v2.Y;
}
inline bool operator!=(const Vector2i& v1, const Vector2i& v2)
{
	return !(v1 == v2);
}

inline Vector2i operator+(const Vector2i& v1, const Vector2i& v2)
{
	return Vector2i(v1.X + v2.X, v1.Y + v2.Y);
}
inline Vector2i operator-(const Vector2i& v1, const Vector2i& v2)
{
	return Vector2i(v1.X - v2.X, v1.Y - v2.Y);
}
inline Vector2i operator*(const Vector2i& v1, const Vector2i& v2)
{
	return Vector2i(v1.X * v2.X, v1.Y * v2.Y);
}
inline Vector2i operator*(const Vector2i& v1, const int& f)
{
	return Vector2i(v1.X * f, v1.Y * f);
}
inline Vector2i operator/(const Vector2i& v1, const Vector2i& v2)
{
	return Vector2i(v1.X / v2.X, v1.Y / v2.Y);
}
inline Vector2i operator/(const Vector2i& v1, const int& f)
{
	return Vector2i(v1.X / f, v1.Y / f);
}