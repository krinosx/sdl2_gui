
#pragma once
#include <string>
#include <iostream>


#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#elif defined _WIN32 || _WIN64
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#endif

#include "GUIComponentState.h"
#include <functional>
/**
Base class for all components. This class stores basic information about positioning,
rendering, states and hold a pointer for a function to be executed when the component
is clicked.

This class also holds a pointer to another GUIComponent (parent) used to define component
hierarchy

@author Giuliano Bortolassi

*/
class GUIComponent
{

private:
	int x;
	int y;
	int w;
	int h;

	int getParentX();
	int getParentY();

protected:
	
	SDL_Rect rectangle;
	SDL_Color backgroundColor;
	SDL_Texture *backgroundImage;
	GUIComponent * parent;


	// internal use
	GUIComponentState state = GUIComponentState::base;

	// actions
	std::function<void(void)> action;

	
public:
	
	GUIComponent(int posX, int posY, int width, int height);
	virtual ~GUIComponent();
	const GUIComponentState getState() { return this->state; }
	void setBackgroundColor(SDL_Color backgroundColor);
	void setBackgroundImage(SDL_Texture *backgroundImage);
	void setBackgroundImage(SDL_Texture* backgroundImage, Uint8 alpha);

	virtual void draw(SDL_Renderer* renderer);
	bool isInside(int x, int y);
	virtual void click(int x, int y){};
	virtual void release(int x, int y){};
	
	void setAction(std::function<void(void)> function);
	virtual void performAction();

	virtual void setParent(GUIComponent * parent);

};