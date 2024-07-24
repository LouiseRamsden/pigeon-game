#pragma once
#ifndef _GAME_TEXT_H_
#define _GAME_TEXT_H_

#include <string>
#include <iostream>

#include "SDL.h"
#include "SDL_ttf.h"


class GameText
{
public:
	GameText(SDL_Renderer* renderer, std::string path, unsigned int fontSize);
	~GameText();

	void LoadFont(std::string path, unsigned int fontSize);
	void RenderAt(std::string text, int x, int y);
	void SetColor(SDL_Color color);

protected:
	SDL_Texture* texture = nullptr;
	TTF_Font* font = nullptr;
	SDL_Color color;
	SDL_Renderer* renderer = nullptr;

private:
	void Destroy();

	static bool ttfHasInit;
	static bool InitTTF();

	bool errorEncountered = false;



};



#endif

