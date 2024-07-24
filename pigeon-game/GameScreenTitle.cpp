#include "GameScreenTitle.h"

#include <string>
#include "Texture2D.h"
#include "constants.h"
#include "commons.h"

GameScreenTitle::GameScreenTitle(SDL_Renderer* renderer, GameScreenManager* manager) : GameScreen(renderer) 
{
	m_screenManager = manager;
	SetUpLevel();
}
GameScreenTitle::~GameScreenTitle() 
{
	delete m_backgroundTexture;
	m_backgroundTexture = nullptr;
}

void GameScreenTitle::Render() 
{
	m_backgroundTexture->Render(Vector2D(0,0), SDL_FLIP_NONE);
	m_titleText->SetColor(SDL_Color{ 0,255,0,255 });
	m_titleText->RenderAt("PIGEON ESCAPE", 10, 10);
	for (int i = 0; i < m_buttons.size(); i++) 
	{
		m_buttons[i]->Render();
	}
}
void GameScreenTitle::Update(float deltaTime, SDL_Event e) 
{

	BUTTON pressedButton = NO_BT;

	switch (e.type) 
	{
	case SDL_KEYDOWN:
		switch(e.key.keysym.sym)
		{
		case SDLK_SPACE:
			pressedButton = BT_A;
			break;
		}
		break;
	case SDL_JOYBUTTONDOWN:
		switch (e.jbutton.button) 
		{
		case 4:
			pressedButton = BT_A;
			break;
		}
		break;
	}

	switch (pressedButton) 
	{
	case BT_A:
		m_buttons[0]->OnSelect();
		break;
	}

	if (m_buttons[0]->IsSelected()) 
	{
		m_screenManager->ChangeScreen(SCREEN_LEVEL1);
	}
}

bool GameScreenTitle::SetUpLevel() 
{
	m_titleText = new GameText(m_renderer, "fonts/ComicMono.ttf", 40);

	m_buttons.push_back(new UIButton(m_renderer, "images/Menu_Button.png",Vector2D(200,400), BT_A));

	m_backgroundTexture = new Texture2D(m_renderer);
	if (!m_backgroundTexture->LoadFromFile("images/Pigeon.png")) 
	{
		std::cout << "failed to load background Texture!" << std::endl;
		return false;
	}
	return true;
}
