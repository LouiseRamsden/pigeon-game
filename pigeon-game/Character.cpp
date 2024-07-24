#include "Character.h"

#include "Texture2D.h"

#include "constants.h"
#include "Collisions.h"



Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition) : GameObject(renderer, imagePath, startPosition)
{
	m_facingDirection = FACING_RIGHT;
	m_movingLeft = false;
	m_movingRight = false;
	m_lastPosition = startPosition;
	m_spawnPosition = startPosition;
	jumps = 3;
	m_collidingWithFloor = false;
	m_health = 100;
	
}
Character::~Character() 
{

}
void Character::ResetJumps() 
{
	jumps = JUMP_AMOUNT;
}
void Character::SetCollidingWithFloor(bool newCollision) 
{
	m_collidingWithFloor = newCollision;
}
bool Character::GetCollidingWithFloor() 
{
	return m_collidingWithFloor;
}
void Character::SetLastPosition(Vector2D newPosition) 
{
	m_lastPosition = newPosition;
}

Vector2D Character::GetLastPosition() 
{
	return m_lastPosition;
}

Vector2D Character::GetSpawnPosition() 
{
	return m_spawnPosition;
}
void Character::SetSpawnPosition(Vector2D newSpawnPosition) 
{
	m_spawnPosition = newSpawnPosition;
}
int Character::GetHealth() 
{
	return m_health;
}
void Character::SetHealth(int newHealth) 
{
	m_health = newHealth;    
}

void Character::Render()
{
	if (m_facingDirection == FACING_RIGHT) 
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
	else 
	{
		m_texture->Render(m_position, SDL_FLIP_NONE); 
	}
}
void Character::Update(float deltaTime, SDL_Event e)
{	
	//Move function calls
	if (m_movingLeft) 
	{
		MoveLeft(deltaTime);
		m_facingDirection = FACING_LEFT;
	}
	else if (m_movingRight) 
	{
		MoveRight(deltaTime);
		m_facingDirection = FACING_RIGHT;
	}
	if (m_jumping) 
	{
		Jump(deltaTime, JUMP_SPEED);
	}
	//Dont Go Out the bounds of the screen
	else if (!GetCollidingWithFloor()) 
	{
		Fall(deltaTime);
	}


	//Event Switch
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_movingLeft = true;
			break;
		case SDLK_d:
			m_movingRight = true;
			break;
		case SDLK_SPACE:
			if (jumps > 0 && m_jumping != true) 
			{
				m_jumping = true;
				jumps -= 1;
			}
			break;
		default:
			break;
		}
		break;
	case SDL_JOYBUTTONDOWN:
		switch (e.jbutton.button)
		{
		case 14: //JoyLeft
			m_movingLeft = true;
			break;
		case 15: //JoyRight
			m_movingRight = true;
			break;
		case 4: // ButtonA
			if (jumps > 0 && m_jumping != true)
			{
				m_jumping = true;
				jumps -= 1;
			}
			break;
		default:
			break;
		}
		break;
	
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a: // JoyLeft
			m_movingLeft = false;
			break;
		case SDLK_d: // JoyRight
			m_movingRight = false;
			break;
		case SDLK_SPACE: // ButtonA
			break;
		default:
			break;
		}
		break;
	case SDL_JOYBUTTONUP:
		switch (e.jbutton.button)
		{
		case 14: // JoyLeft
			m_movingLeft = false;
			break;
		case 15: // JoyRight
			m_movingRight = false;
			break;
		case 4:// ButtonA
			break;
		default:
			break;
		}
		break;

	}


	
	
}

void Character::MoveLeft(float deltaTime) 
{
	m_position.x -= deltaTime * MOVEMENT_SPEED;
}
void Character::MoveRight(float deltaTime) 
{
	m_position.x += deltaTime * MOVEMENT_SPEED;
}
void Character::Jump(float deltaTime, float speed) 
{
	static float jumpTimer;
	jumpTimer += deltaTime;

	if (jumpTimer > JUMP_LENGTH)
	{
		m_jumping = false;
		jumpTimer = 0;
	}
	m_position.y -= deltaTime * speed;
	
}
void Character::Fall(float deltaTime) 
{
	m_position.y += deltaTime * FALL_SPEED;
}

void Character::Respawn() 
{
	m_position = m_spawnPosition;
}

