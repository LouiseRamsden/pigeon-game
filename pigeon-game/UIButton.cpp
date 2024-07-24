#include "UIButton.h"


UIButton::UIButton(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, BUTTON button) : GameObject(renderer, imagePath, startPosition)
{
	m_selected = false;
	m_button = button;
}
UIButton::~UIButton() 
{
	
}

void UIButton::Render() 
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
}
void UIButton::Update(float deltaTime, SDL_Event e) 
{

}

void UIButton::OnSelect() 
{
	m_selected = true;
}

bool UIButton::IsSelected() 
{
	return m_selected;
}
void UIButton::SetButton(BUTTON bt)
{
	m_button = bt;
}

BUTTON UIButton::GetButton() 
{
	return m_button;
}