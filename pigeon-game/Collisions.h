#pragma once
#ifndef _COLLISIONS_H_
#define _COLLISIONS_H_

#include "commons.h"

#include "GameObject.h"

class Character;



class Collisions
{
public:
	~Collisions();
	
	static Collisions* Instance();

	bool Circle(GameObject* a, GameObject* b);
	bool Box(Rect2D rect1, Rect2D rect2);

private:
	Collisions();
	static Collisions* m_instance;
};


#endif

