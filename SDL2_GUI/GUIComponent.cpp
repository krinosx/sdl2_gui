#include "GUIComponent.h"

int GUIComponent::compCount = 0;

GUIComponent::GUIComponent(int posX, int posY, int width, int height) : x(posX), y(posY), w(width), h(height) {
	this->rectangle.h = height;
	this->rectangle.w = width;
	this->rectangle.x = x;
	this->rectangle.y = y;

	this->backgroundColor = SDL_Color{ 0, 0, 0, 255 };
	this->state = GUIComponentState::base;
	this->parent = nullptr;
	this->backgroundImage = nullptr;
	this->visible = true;

	GUIComponent::compCount++;
	this->setId(std::string("GUIComponent-").append(std::to_string(GUIComponent::compCount)) );

	this->invalidateRenderState();
}; 


GUIComponent::~GUIComponent()
{
}

std::string GUIComponent::getId()
{
	return this->compId;
}

void GUIComponent::setId(std::string id)
{
	this->compId = id;
}


void GUIComponent::draw(SDL_Renderer* renderer)
{
	
		Uint8 r, g, b, a;
		SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

		if (this->drawBgColor) {
			SDL_SetRenderDrawColor(renderer, this->backgroundColor.r, this->backgroundColor.g, this->backgroundColor.b, this->backgroundColor.a);
			SDL_RenderFillRect(renderer, &this->rectangle);
		}
		/* If backgroundImage is not null*/
		if (this->backgroundImage)
		{
			SDL_RenderCopy(renderer, this->backgroundImage, &this->backgroundImageRect, &this->rectangle);
		}

		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		
		this->validateRenderState();
}


bool GUIComponent::isInside(int x, int y)
{
	return((x > this->rectangle.x) && (x <  (this->rectangle.x + this->rectangle.w)) && (y > this->rectangle.y) && (y < (this->rectangle.y + this->rectangle.h)));
}

void GUIComponent::setBackgroundColor(SDL_Color backgroundColor)
{
	this->backgroundColor = backgroundColor;
	this->invalidateRenderState();
}

void GUIComponent::setBackgroundImage(SDL_Texture* backgroundImage) {
	this->setBackgroundImage(backgroundImage, 255);
}

void GUIComponent::setBackgroundImage(SDL_Texture* backgroundImage, Uint8 alpha) {
	if (alpha < 255 && alpha >= 0 ) {
		SDL_SetTextureBlendMode(backgroundImage, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(backgroundImage, alpha);
	}
	this->backgroundImage = backgroundImage;
	
	Uint32 textFormat;
	int textW = 0;
	int textH = 0;
	int textAccess = 0;

	SDL_QueryTexture(backgroundImage, &textFormat, &textAccess, &textW, &textH);
	
	this->setBackgroundImageRect(0, 0, textW, textH);
	this->invalidateRenderState();
}

void GUIComponent::setBackgroundImageRect(int x, int y, int w, int h)
{
	this->backgroundImageRect.x = x;
	this->backgroundImageRect.y = y;
	this->backgroundImageRect.w = w;
	this->backgroundImageRect.h = h;
	this->invalidateRenderState();
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
		// change rectangle position - WTF?
		this->rectangle.x = this->getParentX();
		this->rectangle.y = this->getParentY();
	}
	else
	{
		this->rectangle.x = this->x;
		this->rectangle.y = this->y;
	}
}

bool GUIComponent::isVisible()
{
	return this->visible;
}

void GUIComponent::hide()
{
	 this->visible = false;
	 this->invalidateRenderState();
}

void GUIComponent::show()
{
	this->visible = true;
	this->invalidateRenderState();
}

void GUIComponent::toggle()
{
	this->visible = !this->visible;
	this->invalidateRenderState();
}

void GUIComponent::invalidateRenderState()
{
	this->renderStateValid = false;
}

void GUIComponent::validateRenderState()
{
	this->renderStateValid = true;
}

bool GUIComponent::isRenderStateValid()
{
	return this->renderStateValid;
}
