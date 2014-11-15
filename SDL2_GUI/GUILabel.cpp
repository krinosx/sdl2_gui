#include "GUILabel.h"


GUILabel::GUILabel(int x, int y, int w, int h, std::string label, TTF_Font * font, bool border) :
GUIComponent(x, y, w, h), label(label), drawBorder(border), font(font)
{
	this->labelRectangle.x = x;
	this->labelRectangle.y = y;
	this->labelRectangle.w = w;
	this->labelRectangle.h = h;

	this->padLeft = 0;
	this->padRight = 0;
	this->padTop = 0;
	this->padBottom = 0;
}

GUILabel::~GUILabel()
{
	
}

void GUILabel::generateLabelTexture(SDL_Renderer *renderer)
{

	SDL_Surface * textureSurface = TTF_RenderText_Shaded(this->font, this->label.c_str(), this->labelColor, this->backgroundColor);
	this->texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
	SDL_FreeSurface(textureSurface);

	int textureWidth, textureHeight;
	SDL_QueryTexture(this->texture, NULL, NULL, &textureWidth, &textureHeight);

	this->labelRectangle.x = this->x + this->padLeft;
	this->labelRectangle.y = this->y + this->padTop;

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

void GUILabel::draw(SDL_Renderer *renderer)
{
	/* If its the first time rendering, create the label texture. 
	 * If the Label value is changed, the this->texture must be set to NULL
	 */
	if (this->texture == NULL)
	{
		generateLabelTexture(renderer);
	}
	/*
	Draw Order
		1 - Fill the background with backgroundColor
		2 - Draw the label
		3 - Draw the border
	*/
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

	SDL_SetRenderDrawColor(renderer, this->backgroundColor.r, this->backgroundColor.g, this->backgroundColor.b, this->backgroundColor.a);
	SDL_RenderFillRect(renderer, &this->rectangle);

	// Draw the texture Label
	SDL_RenderCopy(renderer, this->texture, NULL, &this->labelRectangle);
	
	// Draw the border
	SDL_SetRenderDrawColor(renderer, this->borderColor.r, this->borderColor.g, this->borderColor.b, this->borderColor.a);
	SDL_RenderDrawRect(renderer, &this->rectangle);
	
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void GUILabel::setBorderColor(SDL_Color color)
{
	this->borderColor = color;
}

void GUILabel::setLabelColor(SDL_Color color)
{
	this->labelColor = color;
}

void GUILabel::release(int x, int y)
{
	this->performAction();
}

void GUILabel::setPadding(int left, int right, int top, int bottom)
{
	this->padLeft = left;
	this->padRight = right;
	this->padTop = top;
	this->padBottom = bottom;
}