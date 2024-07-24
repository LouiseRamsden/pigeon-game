#include "GameScreenManager.h"

#include "GameScreen.h"
#include "GameScreenTitle.h"
#include "GameScreenLevel1.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) 
{
	m_renderer = renderer;
	m_currentScreen = nullptr;

	ChangeScreen(startScreen);
}
GameScreenManager::~GameScreenManager() 
{
	m_renderer = nullptr;

	delete m_currentScreen;
	m_currentScreen = nullptr;
}

void GameScreenManager::Render() 
{
	m_currentScreen->Render();
}
void GameScreenManager::Update(float deltaTime, SDL_Event e) 
{
	m_currentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen) 
{
	//Clear old screen
	if (m_currentScreen != nullptr) 
	{
		delete m_currentScreen;
	}

	GameScreenTitle* tempTitleScreen;
	GameScreenLevel1* tempScreen;
	switch (newScreen) 
	{
	case SCREEN_TITLE:
		tempTitleScreen = new GameScreenTitle(m_renderer, this);
		m_currentScreen = (GameScreen*)tempTitleScreen;
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_renderer, this);
		m_currentScreen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;
	default:
		break;
	}

}