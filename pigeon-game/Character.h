#pragma once
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "GameObject.h"

class Character : public GameObject
{
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
	~Character();

	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;
	
	Vector2D GetLastPosition();
	void SetLastPosition(Vector2D newPosition);

	int jumps;

	void SetCollidingWithFloor(bool newCollision);
	bool GetCollidingWithFloor();

	void ResetJumps();

	void Respawn();

	Vector2D GetSpawnPosition();
	void SetSpawnPosition(Vector2D newSpawnPosition);
	
	int GetHealth();
	void SetHealth(int newHealth);
protected:
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void Jump(float deltaTime, float speed);
	virtual void Fall(float deltaTime);

	

	bool m_movingLeft;
	bool m_movingRight;
	bool m_jumping;
	bool m_falling;
	bool m_timeSinceJump;

	bool m_collidingWithFloor;


	Vector2D m_lastPosition;
private:
	FACING m_facingDirection;

	Vector2D m_spawnPosition;

	int m_health;
};
#endif