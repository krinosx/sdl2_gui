#include "GUIButton.h"


GUIButton::GUIButton(int x, int y, int w, int h, std::string label, TTF_Font * font, bool border)
	: GUILabel(x, y, w, h, label, font, border) {
	
	this->clickedImage = nullptr;
	this->clickedTexture = nullptr;
	this->invalidateRenderState();
	this->setId(std::string("GUIButton-").append(std::to_string(GUIComponent::compCount)));

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

	if (this->state == GUIComponentState::base)
	{
		this->drawBackground(renderer, this->backgroundColor);	
		this->drawBackgroundImage(renderer, this->backgroundImage, &this->backgroundImageRect );
		// Draw the texture Label
		SDL_RenderCopy(renderer, this->texture, NULL, &this->labelRectangle);
	}
	else 
	{
		this->drawBackground(renderer, this->clickedColor);

		this->drawBackgroundImage(renderer, this->clickedImage, &this->clickedImageRect);
		// Draw the texture Label
		SDL_RenderCopy(renderer, this->clickedTexture, NULL, &this->labelRectangle);
	}
		
	this->drawBorders(renderer);

	this->validateRenderState();
}

void GUIButton::click(int x, int y)
{
	this->state = GUIComponentState::pressed;
	this->invalidateRenderState();
}
void GUIButton::release(int x, int y)
{
	this->state = GUIComponentState::base;
	
	this->performAction();
	this->invalidateRenderState();
}


void GUIButton::setClickedColor(SDL_Color color)
{
	this->clickedColor = color;
}

void GUIButton::setClickedImage(SDL_Texture * clickedImage)
{
	this->clickedImage = clickedImage;

	Uint32 textFormat;
	int textW = 0;
	int textH = 0;
	int textAccess = 0;

	SDL_QueryTexture(this->clickedImage, &textFormat, &textAccess, &textW, &textH);

	this->setClickedImageRect(0, 0, textW, textH);

}

void GUIButton::setClickedImage(SDL_Texture * clickedImage, SDL_Rect rect)
{
	this->clickedImage = clickedImage;
	this->setClickedImageRect(rect.x, rect.y, rect.w, rect.h);
}

void GUIButton::setClickedImageRect(int x, int y, int w, int h)
{
	this->clickedImageRect.x = x;
	this->clickedImageRect.y = y;
	this->clickedImageRect.w = w;
	this->clickedImageRect.h = h;
}

