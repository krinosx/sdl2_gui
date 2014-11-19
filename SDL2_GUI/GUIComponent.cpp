#include "GUIComponent.h"


GUIComponent::GUIComponent(int posX, int posY, int width, int height) : x(posX), y(posY), w(width), h(height) {
	this->rectangle.h = height;
	this->rectangle.w = width;
	this->rectangle.x = x;
	this->rectangle.y = y;

	this->state = GUIComponentState::default;
	this->parent = nullptr;
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
	return((x > this->rectangle.x) && (x <  (this->rectangle.x + this->rectangle.w)) && (y > this->rectangle.y) && (y < (this->rectangle.y + this->rectangle.h)));
}

void GUIComponent::setBackgroundColor(SDL_Color backgroundColor)
{
	this->backgroundColor = backgroundColor;
}

void GUIComponent::setAction(std::function<void(void)> function)
{
	this->action = function;
}

void GUIComponent::performAction()
{
	if (this->action)
	{
		this->action();
	}
}

int GUIComponent::getParentX()
{
	return this->parent ? this->x + this->parent->getParentX() : this->x;
}
int GUIComponent::getParentY()
{
	return this->parent ? this->y + this->parent->getParentY() : this->y;
}

void GUIComponent::setParent(GUIComponent * parent)
{
	this->parent = parent;

	if (parent)
	{
		// change rectangle position
		this->rectangle.x = this->getParentX();
		this->rectangle.y = this->getParentY();
	}
	else
	{
		this->rectangle.x = this->x;
		this->rectangle.y = this->y;
	}
}
