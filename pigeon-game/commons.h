#pragma once
struct Vector2D 
{
	float x;
	float y;

	Vector2D() 
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2D(float initialX, float initialY) 
	{
		x = initialX;
		y = initialY;
	}
	Vector2D operator +(const Vector2D& v) 
	{
		return Vector2D(this->x + v.x, this->y + v.y);
	}
	Vector2D operator -(const Vector2D& v) 
	{
		return Vector2D(this->x - v.x, this->y - v.y);
	}
};

struct Rect2D 
{
	float x, y, width, height;
	Rect2D(float x_pos, float y_pos, float width, float height) 
	{
		x = x_pos;
		y = y_pos;
		this->width = width;
		this->height = height;
	}
};

enum SCREENS 
{
	SCREEN_TITLE,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER
};

enum FACING 
{
	FACING_LEFT,
	FACING_RIGHT,
};

enum DIRECTION 
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum BUTTON 
{
	NO_BT,
	BT_A,
	BT_B,
	BT_X,
	BT_Y
};

