#include "GUILabel.h"


GUILabel::GUILabel(int x, int y, int w, int h, std::string label, TTF_Font * font, bool border) :
GUIComponent(x, y, w, h), label(label), drawBorder(border), font(font)
{
	this->labelRectangle.x = x;
	this->labelRectangle.y = y;
	this->labelRectangle.w = w;
	this->labelRectangle.h = h;
}

GUILabel::~GUILabel()
{
	
}

void GUILabel::draw(SDL_Renderer *renderer)
{
	/* If its the first time rendering, create the label texture. 
	 * If the Label value is changed, the this->texture must be set to NULL
	 */
	if (this->texture == NULL)
	{
		SDL_Surface * textureSurface = TTF_RenderText_Shaded(this->font, this->label.c_str(), this->labelColor, this->backgroundColor);
		this->texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
		SDL_FreeSurface(textureSurface);

		int textureWidth, textureHeight;
		SDL_QueryTexture(this->texture, NULL, NULL, &textureWidth, &textureHeight);

		this->labelRectangle.w = textureWidth;
		this->labelRectangle.h = textureHeight;
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

void GUILabel::performAction()
{
	std::cout << "Label Clicked: " << this->label << std::endl;
}