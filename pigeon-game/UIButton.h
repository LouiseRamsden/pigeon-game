#pragma once
#ifndef _UIBUTTON_H_
#define _UIBUTTON_H_

#include "GameObject.h"

class UIButton : GameObject
{
public:
	UIButton(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, BUTTON button);
	~UIButton();

	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;

	virtual void OnSelect();

	virtual void SetButton(BUTTON bt);

	bool IsSelected();

	virtual BUTTON GetButton();
private:
	bool m_selected;
	BUTTON m_button;
};

#endif

