#pragma once

struct WG_Vector2
{
#define VECTOR2_ZERO WG_Vector2(0,0)

public:
	int x;
	int y;

	WG_Vector2(int xs, int ys) : x(xs), y(ys) {};
	WG_Vector2 operator+(WG_Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	WG_Vector2 operator*(WG_Vector2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}
	WG_Vector2 operator/(const int val)
	{
		x /= val;
		y /= val;
		return *this;
	}
	WG_Vector2 operator*(const int val)
	{
		x *= val;
		y *= val;
		return *this;
	}
	bool operator==(const WG_Vector2 &vec)
	{
		if (x == vec.x && y == vec.y)
		{
			return true;
		}
		return false;
	}
	bool operator!=(const WG_Vector2 &vec)
	{
		if (x == vec.x && y == vec.y)
		{
			return false;
		}
		return true;
	}
	bool operator<(const WG_Vector2 &vec)
	{
		if (x <= vec.x)
		{
			if (y < vec.y)
			{
				return true;
			}
		}
		return false;
	}
	bool operator>(const WG_Vector2 &vec)
	{
		if (x >= vec.x)
		{
			if (y > vec.y)
			{
				return true;
			}
		}
		return false;
	}



};
