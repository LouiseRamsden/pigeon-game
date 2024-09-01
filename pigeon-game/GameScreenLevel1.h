#pragma once
#ifndef _GAMESCREENLEVEL1_H_
#define _GAMESCREENLEVEL1_H_

#include <vector>

#include "GameScreenPlayable.h"

class Texture2D;
class Character;

class GameScreenLevel1 : GameScreen, protected GameScreenPlayable
{
public:
	GameScreenLevel1(SDL_Renderer* renderer, GameScreenManager* manager);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	

private:
	std::vector<GameText*> m_gameText;

	Texture2D* m_backgroundTexture = nullptr;
	Character* m_playerCharacter = nullptr;
	GameScreenManager* m_screenManager = nullptr;

	bool SetUpLevel();
};

#endif