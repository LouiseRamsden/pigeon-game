
#include "LevelObject.h"

#include "Texture2D.h"

#include "constants.h"
#include "Collisions.h"

LevelObject::LevelObject(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition) : GameObject(renderer, imagePath, startPosition) 
{

}
LevelObject::~LevelObject() 
{

}

void LevelObject::Render() 
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
}
void LevelObject::Update(float deltaTime, SDL_Event e)
{

}

void LevelObject::Scroll(DIRECTION direction, float movementSpeed, float deltaTime) 
{
	switch (direction) 
	{
	case LEFT:
		m_position.x -= deltaTime * movementSpeed;
		m_scrollOffset.x -= deltaTime * movementSpeed;
		break;
	case RIGHT:
		m_position.x += deltaTime * movementSpeed;
		m_scrollOffset.x += deltaTime * movementSpeed;
		break;
	}
}

Vector2D LevelObject::GetScrollOffset() 
{
	return m_scrollOffset;
}
void LevelObject::SetScrollOffset(Vector2D newOffset) 
{
	m_scrollOffset = newOffset;
}