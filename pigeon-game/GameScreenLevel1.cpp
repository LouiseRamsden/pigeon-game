#include "GameScreenLevel1.h"

#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "Texture2D.h"
#include "Collisions.h"
#include "constants.h"
#include "commons.h"



GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer , GameScreenManager* manager) : GameScreen(renderer), GameScreenPlayable()
{
	m_screenManager = manager;
	SetUpLevel();
}
GameScreenLevel1::~GameScreenLevel1() 
{
	delete m_backgroundTexture;
	m_backgroundTexture = nullptr;

	delete m_playerCharacter;
	m_playerCharacter = nullptr;
}

void GameScreenLevel1::Render()
{
	m_backgroundTexture->Render(Vector2D(m_backGroundAbsolutePosition / BACKGROUND_DISTANCE_OFFSET, 0), SDL_FLIP_NONE);

	for (int i = 0; i < m_wallObjects.size(); i++) 
	{
		m_wallObjects[i]->Render();
	}
	for (int i = 0; i < m_platformObjects.size(); i++)
	{
		m_platformObjects[i]->Render();
	}
	for (int i = 0; i < m_hazardObjects.size(); i++)
	{
		m_hazardObjects[i]->Render();
	}
	for (int i = 0; i < m_collectibleObjects.size(); i++)
	{
		m_collectibleObjects[i]->Render();
	}
	
		
	m_playerCharacter->Render();
	m_gameText[0]->SetColor(SDL_Color{255,255,255,255});
	m_gameText[0]->RenderAt("Shiny Things: " + std::to_string(m_collectibleCount), 10, 10);
	m_gameText[1]->SetColor(SDL_Color{ 255,255,255,255 });
	m_gameText[1]->RenderAt("Health " + std::to_string(m_playerCharacter->GetHealth()), 10, 30);
	m_gameText[1]->SetColor(SDL_Color{ 255,255,255,255 });
	m_gameText[1]->RenderAt(m_winMessage, 10, 50);
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
{
	// Update Character + Character area checks
	m_playerCharacter->Update(deltaTime, e);

	bool collided = false;
	bool roughCollided = false;
	bool changingScreens = false;

	CheckCollisionAndScroll(deltaTime, collided, roughCollided, changingScreens);

	if (changingScreens == true) 
	{
		m_screenManager->ChangeScreen(SCREEN_TITLE);
	}

	if (m_collectibleCount == 11) 
	{
		m_winMessage = "YOU WIN!!!!";
	}
}

bool GameScreenLevel1::SetUpLevel() 
{
	m_collectibleCount = 0;

	m_winMessage = "";
	
	m_gameText.push_back(new GameText(m_renderer, "fonts/ComicMono.ttf", 16));
	m_gameText.push_back(new GameText(m_renderer, "fonts/ComicMono.ttf", 16));
	m_gameText.push_back(new GameText(m_renderer, "fonts/ComicMono.ttf", 16));

	//Create Character
	m_playerCharacter = new Character(m_renderer, "images/Player.png", Vector2D(40, 40));
	m_characterReference = m_playerCharacter;


	//Level Data - Walls (RoughCollision)
	m_wallObjects.push_back(new LevelObject(m_renderer, "images/YellowWall.png", Vector2D(0,100 )));
	m_wallObjects.push_back(new LevelObject(m_renderer, "images/YellowWall.png", Vector2D(0, 0)));

	m_wallObjects.push_back(new LevelObject(m_renderer, "images/YellowWall.png", Vector2D(690, 155)));
	m_wallObjects.push_back(new LevelObject(m_renderer, "images/YellowWall.png", Vector2D(690,-300)));
	m_wallObjects.push_back(new LevelObject(m_renderer, "images/YellowWall.png", Vector2D(840, 356)));
	m_wallObjects.push_back(new LevelObject(m_renderer, "images/YellowWall.png", Vector2D(840, -110)));
	m_wallObjects.push_back(new LevelObject(m_renderer, "images/YellowWall.png", Vector2D(1340, -110)));
	m_wallObjects.push_back(new LevelObject(m_renderer, "images/YellowWall.png", Vector2D(1940, 370)));
	m_wallObjects.push_back(new LevelObject(m_renderer, "images/YellowWall.png", Vector2D(2010, 370)));


	//Level Data - Platforms (SmoothCollision) 
	m_platformObjects.push_back(new LevelObject(m_renderer, "images/Smooth_Platform.png", Vector2D(100, 350)));
	m_platformObjects.push_back(new LevelObject(m_renderer, "images/Smooth_Platform.png", Vector2D(300, 250)));
	m_platformObjects.push_back(new LevelObject(m_renderer, "images/Smooth_Platform.png", Vector2D(500, 150)));
	m_platformObjects.push_back(new LevelObject(m_renderer, "images/Smooth_Platform.png", Vector2D(600, 150)));
	m_platformObjects.push_back(new LevelObject(m_renderer, "images/Smooth_Platform.png", Vector2D(840, 355)));
	m_platformObjects.push_back(new LevelObject(m_renderer, "images/Smooth_Platform.png", Vector2D(1240, 100)));
	m_platformObjects.push_back(new LevelObject(m_renderer, "images/Smooth_Platform.png", Vector2D(1540, 100)));

	//Level Data - Hazard (DamageCollision)
	for (int i = 1; i < 10; i++) 
	{
		m_hazardObjects.push_back(new LevelObject(m_renderer, "images/Hazard.png", Vector2D((i * -100), 470)));
	}
	m_hazardObjects.push_back(new LevelObject(m_renderer, "images/Hazard.png", Vector2D(700, 470)));
	m_hazardObjects.push_back(new LevelObject(m_renderer, "images/Hazard.png", Vector2D(740, 470)));
	for (int i = 1; i < 20; i++) 
	{
		m_hazardObjects.push_back(new LevelObject(m_renderer, "images/Hazard.png", Vector2D(740 + (i * 100), 470)));
	}

	//Level Data - Collectibles (No Blocking Collision)
	m_collectibleObjects.push_back(new LevelObject(m_renderer, "images/Shiny_Thing.png", Vector2D(130, 310)));
	m_collectibleObjects.push_back(new LevelObject(m_renderer, "images/Shiny_Thing.png", Vector2D(330, 210)));
	m_collectibleObjects.push_back(new LevelObject(m_renderer, "images/Shiny_Thing.png", Vector2D(530, 110)));
	m_collectibleObjects.push_back(new LevelObject(m_renderer, "images/Shiny_Thing.png", Vector2D(630, 110)));
	m_collectibleObjects.push_back(new LevelObject(m_renderer, "images/Shiny_Thing.png", Vector2D(750, 110)));
	m_collectibleObjects.push_back(new LevelObject(m_renderer, "images/Shiny_Thing.png", Vector2D(750, 210)));
	m_collectibleObjects.push_back(new LevelObject(m_renderer, "images/Shiny_Thing.png", Vector2D(750, 310)));
	m_collectibleObjects.push_back(new LevelObject(m_renderer, "images/Shiny_Thing.png", Vector2D(870, 315)));
	m_collectibleObjects.push_back(new LevelObject(m_renderer, "images/Shiny_Thing.png", Vector2D(1270, 50)));
	m_collectibleObjects.push_back(new LevelObject(m_renderer, "images/Shiny_Thing.png", Vector2D(1570, 50)));
	m_collectibleObjects.push_back(new LevelObject(m_renderer, "images/Shiny_Thing.png", Vector2D(1970, 400)));


	// Setup Background
	m_backgroundTexture = new Texture2D(m_renderer);
	if (!m_backgroundTexture->LoadFromFile("images/Pigeon.png")) 
	{
		std::cout << "Failed to load background Texture!" << std::endl;
		return false;
	}
	return true;
}

