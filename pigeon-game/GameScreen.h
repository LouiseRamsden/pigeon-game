#pragma once
#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_

#include <SDL.h>

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render() = 0;
	virtual void Update(float deltaTime, SDL_Event e) = 0;

protected:
	SDL_Renderer* m_renderer = nullptr;
};

#endif

