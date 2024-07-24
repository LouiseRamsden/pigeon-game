#include "Texture2D.h"

#include <iostream>
#include <SDL_image.h>

Texture2D::Texture2D(SDL_Renderer* renderer) 
{
	m_renderer = renderer;
}
Texture2D::~Texture2D() 
{
	//Free Memory
	Free();
	m_renderer = nullptr;
}
bool Texture2D::LoadFromFile(std::string path) 
{
	//Remove memory use for previous texture
	Free();

	//Load image
	SDL_Surface* surfacePtr = IMG_Load(path.c_str());
	if (surfacePtr != nullptr)
	{
		SDL_SetColorKey(surfacePtr, SDL_TRUE, SDL_MapRGB(surfacePtr->format, 0, 0XFF, 0XFF));

		//Create texture from pixels on the surface
		m_texture = SDL_CreateTextureFromSurface(m_renderer, surfacePtr);
		if (m_texture == nullptr)
		{
			std::cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}
		else 
		{
			m_width = surfacePtr->w;
			m_height = surfacePtr->h;
		}
		//Remove the loaded surface now that we have a texture
		SDL_FreeSurface(surfacePtr);
	}
	else
	{
		std::cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}

	//return if process was successful
	return m_texture != nullptr;
}
void Texture2D::Free() 
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}
void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle) 
{
	//Set render location
	SDL_Rect renderLocation = { newPosition.x,newPosition.y,m_width, m_height };

	//Render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, angle, nullptr, flip);
}