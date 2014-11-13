#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

class GUIComponent
{
protected:
	int x;
	int y;
	int w;
	int h;

	SDL_Rect rectangle;
	SDL_Color backgroundColor;
	

public:
	GUIComponent(int posX, int posY, int width, int height);
	~GUIComponent();
	virtual void draw(SDL_Renderer* renderer);
	bool isInside(int x, int y);
	virtual void performAction();
	void setBackgroundColor(SDL_Color backgroundColor);
};

