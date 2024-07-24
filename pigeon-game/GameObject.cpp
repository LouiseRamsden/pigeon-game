#include "GameObject.h"


GameObject::GameObject(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition) 
{
	m_renderer = renderer;
	m_position = startPosition;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background Texture!" << std::endl;
	}

	//Default Collision Radius - Change later
	m_collisionRadius = 100.0f;
}
GameObject::~GameObject() 
{
	m_renderer = nullptr;
}

void GameObject::Render() 
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
}
void GameObject::Update(float deltaTime, SDL_Event e) 
{

}
void GameObject::SetPosition(Vector2D newPosition) 
{
	m_position = newPosition;
}
Vector2D GameObject::GetPosition()
{
	return m_position;
}

float GameObject::GetCollisionRadius()
{
	return m_collisionRadius;
}

