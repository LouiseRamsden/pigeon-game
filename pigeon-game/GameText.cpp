              #include "GameText.h"


bool GameText::ttfHasInit = false;

GameText::GameText(SDL_Renderer* renderer, std::string path, unsigned int fontSize)
{
	if (!InitTTF()) 
	{
		std::cout << "Couldn't initialise TTF, Error is " << TTF_GetError() << std::endl;
		errorEncountered = true;
		return;
	}
	this->renderer = renderer;

	this->LoadFont(path, fontSize);

	this->color = SDL_Color{ 255,255,255,255 };
}
GameText::~GameText() 
{
	Destroy();
}

void GameText::LoadFont(std::string path, unsigned int fontSize) 
{
	this->font = TTF_OpenFont(path.c_str(), fontSize);

	if (!this->font) 
	{
		std::cout << "Couldn't load font from path " << path << " error is " << TTF_GetError() << std::endl;
		errorEncountered = true;
	}
}

void GameText::Destroy() 
{
	delete texture;
	texture = nullptr;

	delete font;
	font = nullptr;


}


bool GameText::InitTTF() 
{
	if (ttfHasInit) 
	{
		return true;
	}

	return (TTF_Init() >= 0);
}

void GameText::RenderAt(std::string text, int x, int y) 
{
	if (errorEncountered) 
	{
		return;
	}

	if (texture != nullptr) 
	{
		SDL_DestroyTexture(texture);
	}

	int w, h;
	TTF_SizeText(font, text.c_str(), &w, &h);

	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Rect renderRect{ x, y, w, h };
	SDL_RenderCopy(renderer, texture, NULL, &renderRect);
		
}
void GameText::SetColor(SDL_Color color) 
{
	this->color = color;
}
