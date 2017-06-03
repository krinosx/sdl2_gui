#include "GUITextField.h"
#include <regex>

void GUITextField::setReturnPressedAction(std::function<void(void)> function)
{
	this->returnPressedAction = function;
}

GUITextField::GUITextField(int x, int y, int w, int h, std::string label, TTF_Font * font, bool border)
	: GUILabel(x, y, w, h, label, font, border)
{
	this->textChanged = true;
	this->backgroundImageEditing = NULL;
	this->backgroundImage = NULL;
	this->regexFilter = (".*");
}

GUITextField::~GUITextField()
{
}

std::string GUITextField::getText()
{
	return this->label;
}

void GUITextField::setText(std::string text)
{
	this->label = text;
	this->textChanged = true;
}

void GUITextField::concat(const char * c)
{// Do we need to make a copy of this pointer?
	// TODO: Use regex to filter the char c

	if ( std::regex_match(c, this->regexFilter) ) 
	{
		if (this->label.size() < (size_t)this->maxLenght)
		{
			this->label.append(c);
			this->textChanged = true;
		}
	}
	else {
		std::cout << "invalid filter for this field: " << c << std::endl;
	};

	
}

void GUITextField::removeLastChar()
{
	if (!this->label.empty())
	{
		this->label.pop_back();
		this->textChanged = true;
	}
	
}


void GUITextField::setBackgroundImageEditing(SDL_Texture *backgroundImageEditing)
{
	Uint32 textFormat;
	int textW = 0;
	int textH = 0;
	int textAccess = 0;

	SDL_QueryTexture(backgroundImageEditing, &textFormat, &textAccess, &textW, &textH);

	this->backgroundImageEditing = backgroundImageEditing;
	this->setBackgroundImageEditingRect(0, 0, textW, textH );
	
}

void GUITextField::setBackgroundImageEditing(SDL_Texture *backgroundImageEditing, SDL_Rect rect)
{
	this->backgroundImageEditing = backgroundImageEditing;
	this->setBackgroundImageRect(rect.x, rect.y, rect.w, rect.h);
}

void GUITextField::setBackgroundImageEditingRect(int x, int y, int w, int h) {
	this->backgroundImageEditingRect.x = x;
	this->backgroundImageEditingRect.y = y;
	this->backgroundImageEditingRect.w = w;
	this->backgroundImageEditingRect.h = h;
}


void GUITextField::draw(SDL_Renderer * renderer)
{
	// 1 - Draw the 'background' color (a rectangle with some borders)

	this->drawBackground(renderer);
	
	if (this->state == GUIComponentState::editing)
	{
		if (this->backgroundImageEditing)
		{
			SDL_RenderCopy(renderer, this->backgroundImageEditing, &this->backgroundImageEditingRect, &this->rectangle);
		}
		if (this->drawBorder) 
		{
			this->drawBorders(renderer, this->borderColorEditing);
		}
	}
	else
	{
		// 2 - Draw background image
		if (this->backgroundImage)
		{
			SDL_RenderCopy(renderer, this->backgroundImage, &this->backgroundImageRect, &this->rectangle);
		}
		if (this->drawBorder){
			this->drawBorders(renderer, this->borderColor);
		}
	}

	// 3 - Draw the text texture, respecting the paddings etc
	if (textChanged)
	{
		//this->texture = this->generateTextTexture(renderer, this->label.c_str());
		this->generateLabelTexture(renderer);
		this->textChanged = false;
	}	
	SDL_RenderCopy(renderer, this->texture, NULL, &this->labelRectangle);
}

void GUITextField::release(int x, int y)
{
	this->startEditing();
	this->performAction();
}

/*
	This component will execute the default action when ENTER(RETURN) is
	pressed. Other derived components (like a text area) may use this event
	to introduce some kind of line breaking or other types of controll.
*/
void GUITextField::returnPressed()
{
	this->stopEditing();
	if (this->returnPressedAction) {
		this->returnPressedAction();
	}
	
}

void GUITextField::startEditing()
{
	this->state = GUIComponentState::editing;
}

void GUITextField::stopEditing()
{
	this->state = GUIComponentState::base;
}

void GUITextField::setMaxTextLenght(int maxLenght)
{
	this->maxLenght = maxLenght;
}

void GUITextField::setFilter(const char * regexExpression)
{
	this->regexFilter.assign(regexExpression);
}
