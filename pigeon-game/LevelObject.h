#pragma once
#ifndef _LEVEL_OBJECT_H_
#define _LEVEL_OBJECT_H_

#include "GameObject.h"


//Objects that are part of the level and can scroll beb
class LevelObject : public GameObject
{
public:
	LevelObject(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
	~LevelObject();

	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;

	void Scroll(DIRECTION direction, float movementSpeed, float deltaTime);

	Vector2D GetScrollOffset();
	void SetScrollOffset(Vector2D newOffset);
protected:
private:
	Vector2D m_scrollOffset;
};


#endif