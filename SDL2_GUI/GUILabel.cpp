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
	if (this->texture != nullptr){
		SDL_DestroyTexture(this->texture);
	}

	// We do not destroy the font pointer because 
	// we are not pointer owners.
}


SDL_Texture* GUILabel::generateTextTexture(SDL_Renderer * renderer, const char *text)
{

	SDL_BlendMode * blendMode = new SDL_BlendMode; // Allocate memory for the pointer.
												   // recover the blend mode from the given render
	if (SDL_GetRenderDrawBlendMode(renderer, blendMode))
	{
		*blendMode = SDL_BLENDMODE_BLEND;
	}

	SDL_Surface * textureSurface = nullptr;
	if (*blendMode != SDL_BLENDMODE_BLEND)
	{
		textureSurface = TTF_RenderText_Shaded(this->font, text, this->labelColor, this->backgroundColor);
	}
	else {
		textureSurface = TTF_RenderText_Blended(this->font, text, this->labelColor);
	}

	delete(blendMode); // Delete the useless pointer

	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
	
	SDL_FreeSurface(textureSurface);
	
	return texture;

}

/**
	Generate a texture to print based on current text and label atributes.

*/
void GUILabel::generateLabelTexture(SDL_Renderer *renderer)
{

	this->texture = this->generateTextTexture(renderer, this->label.c_str());
	

	int textureWidth, textureHeight;
	SDL_QueryTexture(this->texture, NULL, NULL, &textureWidth, &textureHeight);

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

void GUILabel::draw(SDL_Renderer *renderer)
{
	/* If its the first time rendering, create the label texture. 
	 * If the Label value is changed, the this->texture must be set to NULL
	 */
	if (this->texture == nullptr)
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

void GUILabel::setParent(GUIComponent * parent)
{
	GUIComponent::setParent(parent);
	this->texture = nullptr;
}