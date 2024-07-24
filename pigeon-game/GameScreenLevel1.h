#pragma once
#ifndef _GAMESCREENLEVEL1_H_
#define _GAMESCREENLEVEL1_H_

#include <vector>

#include "GameScreen.h"
#include "commons.h"
#include "Character.h"
#include "LevelObject.h"
#include "Collisions.h"
#include "GameText.h"
#include "GameScreenManager.h"

class Texture2D;
class Character;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer, GameScreenManager* manager);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void BackgroundScroll(DIRECTION direction, float movementSpeed, float deltaTime);

private:
	std::vector<GameText*> m_gameText;

	Texture2D* m_backgroundTexture = nullptr;
	Character* m_playerCharacter = nullptr;
	GameScreenManager* m_screenManager = nullptr;

	std::vector<LevelObject*> m_wallObjects;
	std::vector<LevelObject*> m_platformObjects;
	std::vector<LevelObject*> m_hazardObjects;
	std::vector<LevelObject*> m_collectibleObjects;

	int m_collectibleCount;

	float m_backGroundAbsolutePosition;

	bool SetUpLevel();

	void SmoothCollision();

	void RoughCollision();

	std::string m_winMessage;

};

#endif