#include "GUIComponent.h"


GUIComponent::GUIComponent(int posX, int posY, int width, int height) : x(posX), y(posY), w(width), h(height) {
	this->rectangle.h = height;
	this->rectangle.w = width;
	this->rectangle.x = x;
	this->rectangle.y = y;
}; 


GUIComponent::~GUIComponent()
{
}


void GUIComponent::draw(SDL_Renderer* renderer)
{
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	
	SDL_SetRenderDrawColor(renderer, this->backgroundColor.r, this->backgroundColor.g, this->backgroundColor.b, this->backgroundColor.a );
	SDL_RenderFillRect(renderer, &this->rectangle);
	
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}


bool GUIComponent::isInside(int x, int y)
{
	return((x > this->x) && (x <  (this->x + this->w)) && (y > this->y) && (y < (this->y + this->h)));
}


void GUIComponent::performAction()
{
	std::cout << "Component Clicked" << std::endl;
}

void GUIComponent::setBackgroundColor(SDL_Color backgroundColor)
{
	this->backgroundColor = backgroundColor;
}