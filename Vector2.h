#pragma once
#include <SFML/Graphics.hpp>

struct Vector2
{
	float X;
	float Y;

	Vector2(float value) : X(value), Y(value) {}
	Vector2(float x, float y) : X(x), Y(y) {}

	// Static constructors
	static Vector2 zero() { return Vector2(0, 0); }
	static Vector2 one() { return Vector2(1, 1); }
	static Vector2 left() { return Vector2(-1, 0); }
	static Vector2 right() { return Vector2(1, 0); }
	static Vector2 up() { return Vector2(0, -1); }
	static Vector2 down() { return Vector2(0, 1); }

	// Static methods
	static float magnitude(const Vector2& v)
	{
		return sqrtf((v.X * v.X) + (v.Y * v.Y));
	}
	static float distance(const Vector2& v1, const Vector2& v2)
	{
		float x = v2.X - v1.X;
		float y = v2.Y - v1.Y;

		return magnitude(Vector2(x, y));
	}
	static float determinant(const Vector2& v1, const Vector2& v2)
	{
		return v1.X * v2.Y - v2.X * v1.Y;
	}
	static Vector2 normalize(const Vector2& v)
	{
		float magn = magnitude(v);
		return Vector2(
			v.X / magn,
			v.Y / magn
		);
	}

	// Methods
	void translate(const Vector2& v)
	{
		*this += v;
	}
	void scale(const Vector2& v)
	{
		*this *= v;
	}
	void scale(const float& f)
	{
		*this *= f;
	}
	float magnitude() const
	{
		return magnitude(*this);
	}
	float determinant(const Vector2& v) const
	{
		return determinant(*this, v);
	}
	float distance(const Vector2& v) const
	{
		return distance(*this, v);
	}
	Vector2 normalized() const
	{
		return normalize(*this);
	}

	// Operator when used with SFML
	static Vector2 from(sf::Vector2f vector) { return Vector2(vector.x, vector.y); }
	static Vector2 from(sf::Vector2i vector) { return Vector2(vector.x, vector.y); }
	operator sf::Vector2f() const { return { X, Y }; }
	operator sf::Vector2i() const { return { (int)X, (int)Y }; }

	// Operators
	Vector2& operator=(const Vector2& v2) = default;

	Vector2& operator+=(const Vector2& v2)
	{
		X += v2.X;
		Y += v2.Y;

		return *this;
	}
	Vector2& operator-=(const Vector2& v2)
	{
		X -= v2.X;
		Y -= v2.Y;

		return *this;
	}
	Vector2& operator*=(const Vector2& v2)
	{
		X *= v2.X;
		Y *= v2.Y;

		return *this;
	}
	Vector2& operator*=(const float& f)
	{
		X *= f;
		Y *= f;

		return *this;
	}
	Vector2& operator/=(const Vector2& v2)
	{
		X /= v2.X;
		Y /= v2.Y;

		return *this;
	}
};

// Operators
inline std::ostream& operator<<(std::ostream& os, const Vector2& v)
{
	os << "X: " << v.X << " Y: " << v.Y << std::endl;
	return os;
}

inline bool operator==(const Vector2& v1, const Vector2& v2)
{
	return v1.X == v2.X && v1.Y == v2.Y;
}
inline bool operator!=(const Vector2& v1, const Vector2& v2)
{
	return !(v1 == v2);
}

inline Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.X + v2.X, v1.Y + v2.Y);
}
inline Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.X - v2.X, v1.Y - v2.Y);
}
inline Vector2 operator*(const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.X * v2.X, v1.Y * v2.Y);
}
inline Vector2 operator*(const Vector2& v1, const float& f)
{
	return Vector2(v1.X * f, v1.Y * f);
}
inline Vector2 operator/(const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.X / v2.X, v1.Y / v2.Y);
}
inline Vector2 operator/(const Vector2& v1, const float& f)
{
	return Vector2(v1.X / f, v1.Y / f);
}