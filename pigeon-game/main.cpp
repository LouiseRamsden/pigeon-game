#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "constants.h"
#include "commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"

//Globals
SDL_Window* gameWindow = nullptr;
SDL_Renderer* gameRenderer = nullptr;
GameScreenManager* gameScreenManager;
uint32_t gameOldTime;

//Function Declarations
bool InitSDL();
void CloseSDL();
bool Update();

/*START OF SDL INITIALIZATION, GAMELOOP AND CLOSING*/
bool InitSDL() 
{
	//SDL Setup
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) < 0) 
	{
		//SDL failed to init
		std::cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	//Setup Success, Create Window
	gameWindow = SDL_CreateWindow("Bespoke Platform Dev", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		SCREEN_WIDTH, 
		SCREEN_HEIGHT, 
		SDL_WINDOW_SHOWN);
	//Was Window Created?
	if (gameWindow == nullptr) 
	{
		//Window failed to be created
		std::cout << "SDL did not initialize. Error: " << SDL_GetError();
		return false;
	}
	//Window Creation Success, Create Renderer
	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);

	//If game Renderer is nullptr, return false
	if (gameRenderer == nullptr)
	{
		std::cout << "Renderer could not initialise. Error: " << SDL_GetError();
		return false;
	}

	//Check if able to load an image
	int imageFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imageFlags) & imageFlags)) //Init, image flags, then check if its been initialized, if not return error.
	{
		std::cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
		return false;
	}

	SDL_JoystickOpen(1);

	return true;
}

void CloseSDL() 
{
	//When closing sdl, destroy window, set game window to nullptr and quit sdl
	SDL_DestroyWindow(gameWindow);
	gameWindow = nullptr;


	//release renderer
	SDL_DestroyRenderer(gameRenderer);
	gameRenderer = nullptr;

	//Destroy Game Screen manager
	delete gameScreenManager;
	gameScreenManager = nullptr;

	SDL_Quit();
}

bool Update()
{
	//New time
	uint32_t newTime = SDL_GetTicks();

	//Event handler
	SDL_Event e;

	//Get events
	SDL_PollEvent(&e);

	//Handle Events
	switch (e.type) 
	{
	case SDL_KEYDOWN:
		//Check if pressing a key
		//Then switch on scancode
		switch (e.key.keysym.scancode) 
		{
		case SDL_SCANCODE_0:
			std::cout << "YIPPEEE!!!!" << "\n";
			break;
		}
		break;
		//When x is pressed on the window
	case SDL_QUIT:
		return true;
		break;
	}
	gameScreenManager->Update((float)(newTime - gameOldTime)/ 1000.0f, e);
	gameOldTime = newTime;

	return false;
}
/*END OF SDL INITIALIZATION, GAMELOOP AND CLOSING*/

void Render() 
{
	//Clear the Screen
	SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderClear(gameRenderer);

	gameScreenManager->Render();

	//Update the screen
	SDL_RenderPresent(gameRenderer);	
}
int main(int argc, char* argv[])
{
	if (InitSDL()) 
	{
		gameScreenManager = new GameScreenManager(gameRenderer, SCREEN_TITLE);
		//set the time
		gameOldTime = SDL_GetTicks();

		//Quit check flag
		bool quit = false;

		//Call game loop while not quitting
		while (!quit) 
		{
			Render();
			quit = Update();
		}
	}
	CloseSDL();
	return 0;
}