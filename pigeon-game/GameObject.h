#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <SDL.h>
#include <iostream>

#include "commons.h"
#include "Texture2D.h"

class Texture2D;

class GameObject
{
public:
	GameObject(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
	~GameObject();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();
	float GetCollisionRadius();

	Rect2D GetCollisionBox() 
	{	
		return Rect2D(m_position.x, m_position.y, 
			m_texture->GetWidth(), m_texture->GetHeight());
	}
protected:
	SDL_Renderer* m_renderer = nullptr;
	Vector2D m_position;
	Texture2D* m_texture = nullptr;

	float m_collisionRadius;
};

#endif