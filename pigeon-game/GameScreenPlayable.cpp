#include "GameScreenPlayable.h"
#include "commons.h"
#include "constants.h"

GameScreenPlayable::GameScreenPlayable() 
{

}

void GameScreenPlayable::RoughCollision()
{

	m_characterReference->ResetJumps();
	m_characterReference->SetPosition(m_characterReference->GetLastPosition());
}
void GameScreenPlayable::SmoothCollision()
{
	m_characterReference->ResetJumps();
	m_characterReference->SetCollidingWithFloor(true);
}

void GameScreenPlayable::BackgroundScroll(DIRECTION direction, float movementSpeed, float deltaTime)
{
	switch (direction)
	{
	case LEFT:
		m_backGroundAbsolutePosition -= deltaTime * movementSpeed;
		break;
	case RIGHT:
		m_backGroundAbsolutePosition += deltaTime * movementSpeed;
		break;
	}
}

bool GameScreenPlayable::CheckCollisionAndScroll(float deltaTime, bool& collided, bool& roughCollided, bool& changingScreens) 
{


	for (int i = 0; i < m_wallObjects.size(); i++)
	{

		if (Collisions::Instance()->Box(m_characterReference->GetCollisionBox(), m_wallObjects[i]->GetCollisionBox()))
		{
			collided = true;
			roughCollided = true;
			RoughCollision();
		}

	}
	for (int i = 0; i < m_platformObjects.size(); i++)
	{
		if (Collisions::Instance()->Box(m_characterReference->GetCollisionBox(), m_platformObjects[i]->GetCollisionBox()))
		{
			collided = true;
			SmoothCollision();

		}
	}
	for (int i = 0; i < m_hazardObjects.size(); i++)
	{
		if (Collisions::Instance()->Box(m_characterReference->GetCollisionBox(), m_hazardObjects[i]->GetCollisionBox()))
		{
			collided = true;
			m_characterReference->SetHealth(m_characterReference->GetHealth() - 25);
			if (m_characterReference->GetHealth() <= 0)
			{
				changingScreens = true;
			}
			m_characterReference->Respawn();
			for (int i = 0; i < m_platformObjects.size(); i++)
			{
				m_platformObjects[i]->SetPosition(m_platformObjects[i]->GetPosition() - m_platformObjects[i]->GetScrollOffset());
				m_platformObjects[i]->SetScrollOffset(Vector2D(0, 0));
			}
			for (int i = 0; i < m_hazardObjects.size(); i++)
			{
				m_hazardObjects[i]->SetPosition(m_hazardObjects[i]->GetPosition() - m_hazardObjects[i]->GetScrollOffset());
				m_hazardObjects[i]->SetScrollOffset(Vector2D(0, 0));
			}
			for (int i = 0; i < m_wallObjects.size(); i++)
			{
				m_wallObjects[i]->SetPosition(m_wallObjects[i]->GetPosition() - m_wallObjects[i]->GetScrollOffset());
				m_wallObjects[i]->SetScrollOffset(Vector2D(0, 0));
			}
			for (int i = 0; i < m_collectibleObjects.size(); i++)
			{
				m_collectibleObjects[i]->SetPosition(m_collectibleObjects[i]->GetPosition() - m_collectibleObjects[i]->GetScrollOffset());
				m_collectibleObjects[i]->SetScrollOffset(Vector2D(0, 0));
			}

		}
	}
	for (int i = 0; i < m_collectibleObjects.size(); i++)
	{
		if (Collisions::Instance()->Box(m_characterReference->GetCollisionBox(), m_collectibleObjects[i]->GetCollisionBox()))
		{
			m_collectibleObjects.erase(m_collectibleObjects.begin() + i);
			m_collectibleCount++;
		}
	}
	if (Collisions::Instance()->Box(m_characterReference->GetCollisionBox(), Rect2D(0, SCREEN_HEIGHT, SCREEN_WIDTH + 100, 1)))
	{
		collided = true;


		SmoothCollision();
	}

	if (collided == false)
	{
		m_characterReference->SetCollidingWithFloor(false);
	}
	m_characterReference->SetLastPosition(m_characterReference->GetPosition());

	if (roughCollided == false)
	{
		if (m_characterReference->GetPosition().x > SCREEN_WIDTH - CHARACTER_SIZE - CHARACTER_SCREEN_OFFSET)
		{
			m_characterReference->SetPosition({ (float)(SCREEN_WIDTH - CHARACTER_SIZE) - CHARACTER_SCREEN_OFFSET, m_characterReference->GetPosition().y });
			for (int i = 0; i < m_wallObjects.size(); i++)
			{
				m_wallObjects[i]->Scroll(LEFT, MOVEMENT_SPEED, deltaTime);

			}
			for (int i = 0; i < m_platformObjects.size(); i++)
			{
				m_platformObjects[i]->Scroll(LEFT, MOVEMENT_SPEED, deltaTime);
			}
			for (int i = 0; i < m_hazardObjects.size(); i++)
			{
				m_hazardObjects[i]->Scroll(LEFT, MOVEMENT_SPEED, deltaTime);
			}
			for (int i = 0; i < m_collectibleObjects.size(); i++)
			{
				m_collectibleObjects[i]->Scroll(LEFT, MOVEMENT_SPEED, deltaTime);
			}
			BackgroundScroll(LEFT, MOVEMENT_SPEED, deltaTime);
		}
		if (m_characterReference->GetPosition().x < CHARACTER_SCREEN_OFFSET)
		{
			m_characterReference->SetPosition({ 0.0f + CHARACTER_SCREEN_OFFSET, m_characterReference->GetPosition().y });
			for (int i = 0; i < m_wallObjects.size(); i++)
			{
				m_wallObjects[i]->Scroll(RIGHT, MOVEMENT_SPEED, deltaTime);
			}
			for (int i = 0; i < m_platformObjects.size(); i++)
			{
				m_platformObjects[i]->Scroll(RIGHT, MOVEMENT_SPEED, deltaTime);
			}
			for (int i = 0; i < m_hazardObjects.size(); i++)
			{
				m_hazardObjects[i]->Scroll(RIGHT, MOVEMENT_SPEED, deltaTime);
			}
			for (int i = 0; i < m_collectibleObjects.size(); i++)
			{
				m_collectibleObjects[i]->Scroll(RIGHT, MOVEMENT_SPEED, deltaTime);
			}
			BackgroundScroll(RIGHT, MOVEMENT_SPEED, deltaTime);
		}

		return changingScreens;
	}
}