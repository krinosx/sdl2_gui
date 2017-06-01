#include "GUIButton.h"


GUIButton::GUIButton(int x, int y, int w, int h, std::string label, TTF_Font * font, bool border)
	: GUILabel(x, y, w, h, label, font, border) {

}


GUIButton::~GUIButton()
{
	if (this->clickedTexture != nullptr)
	{
		SDL_DestroyTexture(this->clickedTexture);
	}

}

void GUIButton::generateClickedTexture(SDL_Renderer * renderer)
{
	this->clickedTexture = this->generateTextTexture(renderer, this->label.c_str());
	
	int textureWidth, textureHeight;
	SDL_QueryTexture(this->clickedTexture, NULL, NULL, &textureWidth, &textureHeight);

	this->labelRectangle.x = this->rectangle.x + this->padLeft;
	this->labelRectangle.y = this->rectangle.y + this->padTop;

	// If label size + padding greather than entire button, resize label to fit in original size
	if (textureWidth + this->padLeft + this->padRight > this->rectangle.w)
	{
		this->labelRectangle.w = this->rectangle.w - (this->padLeft + this->padRight);
	}
	else
	{
		this->labelRectangle.w = textureWidth;
	}

	if (textureHeight + this->padTop + this->padBottom > this->rectangle.h)
	{
		this->labelRectangle.h = this->rectangle.h - (this->padTop + this->padBottom);
	}
	else
	{
		this->labelRectangle.h = textureHeight;
	}
}


void GUIButton::draw(SDL_Renderer *renderer)
{
	/* If its the first time rendering, create the label texture.
	* If the Label value is changed, the this->texture must be set to NULL
	*/
	if (this->texture == NULL)
	{
		this->generateLabelTexture(renderer);
		this->generateClickedTexture(renderer);
	}
	/*
	Draw Order
	1 - Fill the background with backgroundColor
	2 - Draw the label
	3 - Draw the border
	*/
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

	if (this->state == GUIComponentState::base)
	{
		SDL_SetRenderDrawColor(renderer, this->backgroundColor.r, this->backgroundColor.g, this->backgroundColor.b, this->backgroundColor.a);
		SDL_RenderFillRect(renderer, &this->rectangle);
		// Draw the texture Label
		SDL_RenderCopy(renderer, this->texture, NULL, &this->labelRectangle);
	}
	else 
	{
		SDL_SetRenderDrawColor(renderer, this->clickedColor.r, this->clickedColor.g, this->clickedColor.b, this->clickedColor.a);
		SDL_RenderFillRect(renderer, &this->rectangle);
		// Draw the texture Label
		SDL_RenderCopy(renderer, this->clickedTexture, NULL, &this->labelRectangle);
	}
		

	// Draw the border
	SDL_SetRenderDrawColor(renderer, this->borderColor.r, this->borderColor.g, this->borderColor.b, this->borderColor.a);
	SDL_RenderDrawRect(renderer, &this->rectangle);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void GUIButton::click(int x, int y)
{
	this->state = GUIComponentState::pressed;

}
void GUIButton::release(int x, int y)
{
	this->state = GUIComponentState::base;
	
	this->performAction();
}


void GUIButton::setClickedColor(SDL_Color color)
{
	this->clickedColor = color;
}

