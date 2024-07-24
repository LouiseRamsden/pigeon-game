#pragma once
#ifndef _GAMESCREENTITLE_H_
#define _GAMESCREENTITLE_H_

#include <vector>

#include "GameScreen.h"
#include "commons.h"
#include "GameText.h"
#include "GameScreenManager.h"
#include "UIButton.h"

class Texture2D;

class GameScreenTitle : GameScreen
{
public:
	GameScreenTitle(SDL_Renderer* renderer, GameScreenManager* manager);
	~GameScreenTitle();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	GameText* m_titleText = nullptr;

	std::vector<UIButton*> m_buttons;

	Texture2D* m_backgroundTexture = nullptr;
	GameScreenManager* m_screenManager = nullptr;

	bool SetUpLevel();
};

#endif