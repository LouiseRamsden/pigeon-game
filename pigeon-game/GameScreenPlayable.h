#pragma once
#ifndef _GAMESCREENPLAYABLE_H_
#define _GAMESCREENPLAYABLE_H_

#include <vector>

#include "GameScreen.h"
#include "commons.h"
#include "Character.h"
#include "LevelObject.h"
#include "Collisions.h"
#include "GameText.h"
#include "GameScreenManager.h"

class Character;


class GameScreenPlayable
{
public:
	GameScreenPlayable();
protected:
	std::vector<LevelObject*> m_wallObjects;
	std::vector<LevelObject*> m_platformObjects;
	std::vector<LevelObject*> m_hazardObjects;
	std::vector<LevelObject*> m_collectibleObjects;

	int m_collectibleCount;

	float m_backGroundAbsolutePosition;

	void SmoothCollision();

	void RoughCollision();

	void BackgroundScroll(DIRECTION direction, float movementSpeed, float deltaTime);
	
	bool CheckCollisionAndScroll(float deltaTime, bool& collided ,bool& roughCollided, bool& changingScreens);
	std::string m_winMessage;

	Character* m_characterReference = nullptr;
private:
	
};

#endif