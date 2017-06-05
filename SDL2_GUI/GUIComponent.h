
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
	
	SDL_Rect rectangle = { 0,0,0,0 };
	SDL_Color backgroundColor = { 0,0,0,0 };
	SDL_Texture *backgroundImage = NULL;
	SDL_Rect backgroundImageRect = { 0,0,0,0 };
	GUIComponent * parent = nullptr;
	bool drawBgColor = true;
	bool visible = true;
	// internal use
	GUIComponentState state = GUIComponentState::base;

	// actions
	std::function<void(void)> action = nullptr;

	
public:
	
	GUIComponent(int posX, int posY, int width, int height);
	virtual ~GUIComponent();
	const GUIComponentState getState() { return this->state; }
	void setBackgroundColor(SDL_Color backgroundColor);
	void setBackgroundImage(SDL_Texture *backgroundImage);
	void setBackgroundImage(SDL_Texture* backgroundImage, Uint8 alpha);

	void setBackgroundImageRect(int x, int y, int w, int h);

	virtual void draw(SDL_Renderer* renderer);
	bool isInside(int x, int y);
	virtual void click(int x, int y){};
	virtual void release(int x, int y){};
	
	void setAction(std::function<void(void)> function);
	virtual void performAction();

	virtual void setParent(GUIComponent * parent);

	void setDrawBgColor(bool drawBgColor) { this->drawBgColor = drawBgColor; }

	SDL_Rect getRectangle() { return this->rectangle; }
	virtual void resize(int x, int y, int w, int h) {};

	/* Visibility function*/
	bool isVisible();
	void hide();
	void show();
	void toggle();
};