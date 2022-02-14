#pragma once
#include <SFML/Graphics.hpp>

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
	static int magnitude(const Vector2i& v)
	{
		return sqrtf((v.X * v.X) + (v.Y * v.Y));
	}
	static int distance(const Vector2i& v1, const Vector2i& v2)
	{
		int x = v2.X - v1.X;
		int y = v2.Y - v1.Y;

		return magnitude(Vector2i(x, y));
	}
	static int determinant(const Vector2i& v1, const Vector2i& v2)
	{
		return v1.X * v2.Y - v2.X * v1.Y;
	}
	static Vector2i normalize(const Vector2i& v)
	{
		int magn = magnitude(v);
		return Vector2i(
			v.X / magn,
			v.Y / magn
		);
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
	int magnitude() const
	{
		return magnitude(*this);
	}
	int determinant(const Vector2i& v) const
	{
		return determinant(*this, v);
	}
	int distance(const Vector2i& v) const
	{
		return distance(*this, v);
	}
	Vector2i normalized() const
	{
		return normalize(*this);
	}

	// Operator when used with SFML
	static Vector2i from(sf::Vector2f vector) { return Vector2i((int)vector.x, (int)vector.y); }
	static Vector2i from(sf::Vector2i vector) { return Vector2i(vector.x, vector.y); }
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