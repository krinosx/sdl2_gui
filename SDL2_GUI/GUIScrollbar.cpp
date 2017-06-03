#include "GUIScrollbar.h"



GUIScrollbar::GUIScrollbar()
{
}

GUIScrollbar::GUIScrollbar(int x, int y, int w, int h, TTF_Font *font, unsigned int align)
	: GUIPanel(x, y, w, h), align(align)
{
	// Check min value constraints
	this->rectangle.w = (unsigned int)this->rectangle.w < this->minBarWidth ?  this->minBarWidth : this->rectangle.w;
	this->rectangle.h = (unsigned int)this->rectangle.h < this->minBarHeight ? this->minBarHeight : this->rectangle.h;

	this->setOpaque(true);


	int buttonSize = (unsigned int)(this->rectangle.w / 20) < this->minButtonSize ? this->minButtonSize : (int)(this->rectangle.w / 20);

	// resize the pannel based on align
	if (this->align == ALIGN_VERTICAL)
	{ // must change w and h 
		int horizontalH = this->rectangle.w;
		int horizontalW = this->rectangle.h;

		this->rectangle.h = horizontalH;
		this->rectangle.w = horizontalW;
	
		
		this->incrementButton = new GUIButton(0, 0, this->rectangle.w, buttonSize, "/\\", font, true);
		this->decrementButton = new GUIButton(0, (this->rectangle.h-(buttonSize)) , this->rectangle.w, buttonSize, "\\/", font, true);
	} 
	else 
	{ 
		this->incrementButton = new GUIButton((this->rectangle.w - buttonSize), 0, buttonSize, this->rectangle.h, " >", font, true); 
		this->decrementButton = new GUIButton(0, 0, buttonSize, this->rectangle.h, " <", font, true);
	}

	this->incrementButton->setAction([this]() { increment(); });
	this->decrementButton->setAction([this]() { decrement(); });

	SDL_Color col = { 255,255,255,255 };
	this->incrementButton->setBackgroundColor(col);
	this->decrementButton->setBackgroundColor(col);

	this->addComponent(this->incrementButton);
	this->addComponent(this->decrementButton);
	// Create increment and decrement buttons
	




}

void GUIScrollbar::increment() 
{
	if (this->currentValue < this->max)
	{
		this->currentValue = ((this->currentValue + this->pace) > this->max) ? this->max : (this->currentValue + this->pace);
	}
	if (this->notifyIncrement)
	{
		this->notifyIncrement(this->currentValue);
	}
	

}

void GUIScrollbar::decrement()
{
	if (this->currentValue > this->min)
	{
		this->currentValue = ((this->currentValue - this->pace) < this->min) ? this->min : (this->currentValue - this->pace);
	}
	if (this->notifyDecrement)
	{
		this->notifyDecrement(this->currentValue);
	}

}

GUIScrollbar::~GUIScrollbar()
{
}

void GUIScrollbar::setMinValue(unsigned int minValue)
{
	this->min = minValue;
}

void GUIScrollbar::setMaxValue(unsigned int maxValue)
{
	this->max = maxValue;
}

void GUIScrollbar::setPace(unsigned int pace)
{
	this->pace = pace;
}

unsigned int GUIScrollbar::getMinValue()
{
	return this->min;
}

unsigned int GUIScrollbar::getMaxValue()
{
	return this->max;
}

unsigned int GUIScrollbar::getCurrentValue()
{
	return this->currentValue;
}

void GUIScrollbar::setNotifyIncrementListener(std::function<void(unsigned int currentValue)> incrementListener)
{
	this->notifyIncrement = incrementListener;
}

void GUIScrollbar::setNotifyDecrementListener(std::function<void(unsigned int currentValue)> decrementListener)
{
	this->notifyDecrement = decrementListener;
}

void GUIScrollbar::draw(SDL_Renderer * renderer)
{
	GUIPanel::draw(renderer);
}
