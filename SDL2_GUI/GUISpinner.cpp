#include "GUISpinner.h"



void GUISpinner::increment()
{
	this->currentValue = (this->currentValue + this->pace) > this->maxValue ? this->maxValue : (this->currentValue + this->pace);
	this->editingField->setText(std::to_string(this->currentValue));
	this->invalidateRenderState();
}

void GUISpinner::decrement()
{
	this->currentValue = (this->currentValue - this->pace) < this->minValue ? this->minValue : (this->currentValue - this->pace);
	this->editingField->setText(std::to_string(this->currentValue));
	this->invalidateRenderState();
}

GUISpinner::GUISpinner(int x, int y, int w, int h, TTF_Font * font, int minValue, int maxValue)
	:GUIPanel(x,y,w,h), minValue(minValue), maxValue(maxValue), font(font)
{

	this->setId(std::string("GUISpinner-").append(std::to_string(GUIComponent::compCount)));
	// Calculate the minimum lenght of textField
	int minTextFieldWidth = 0;
	int minTextFieldHeight = 0;
	TTF_SizeText(font, std::to_string(this->minValue).c_str(), &minTextFieldWidth, &minTextFieldHeight);

	int maxTextFieldWidth = 0;
	int maxTextFieldHeight = 0;
	
	TTF_SizeText(font, std::to_string(this->maxValue).c_str(), &maxTextFieldWidth, &maxTextFieldHeight);

	int textFieldWidth = minTextFieldWidth < maxTextFieldWidth ? maxTextFieldWidth : minTextFieldWidth;
	int textFieldHeight = minTextFieldHeight < maxTextFieldHeight ? maxTextFieldHeight : minTextFieldHeight;
	
	// scrollbar is based on horizontal alight
	int minScrollBarHeight = GUIScrollbar::MIN_BAR_WIDTH;
	int minScrollBarWidth = GUIScrollbar::MIN_BAR_HEIGHT;

	if (this->rectangle.h < minScrollBarHeight)
	{
		this->rectangle.h = minScrollBarHeight;
	}

	int totalSpinnerWidth = minScrollBarWidth + textFieldWidth;

	if (this->rectangle.w < totalSpinnerWidth) {
		this->rectangle.w = totalSpinnerWidth;
	}
	
	//Scrollbars will be always Vertical, with mininum width
	this->scrollbar = new GUIScrollbar(( this->rectangle.w - minScrollBarWidth ) , 0, this->rectangle.h, minScrollBarWidth, font, GUIScrollbar::ALIGN_VERTICAL);


	this->scrollbar->setNotifyIncrementListener([&](unsigned int currentScrollbarValue) {
		this->increment();
	});

	this->scrollbar->setNotifyDecrementListener([&](unsigned int currentScrollbarValue) {
		this->decrement();
	});



	this->editingField = new GUITextField((this->rectangle.w - minScrollBarWidth - textFieldWidth), 0, textFieldWidth, this->rectangle.h, std::to_string(this->currentValue), font, true);
	//this->editingField->setBackgroundColor(SDL_Color{ 255,0,0,255 });
	this->editingField->setDrawBgColor(false);

	this->editingField->setFilter("^([0-9_\\-]+)$");
	// click action
	this->editingField->setAction([this]() {
		notifyEditing(editingField);
	});

	this->editingField->setReturnPressedAction([&]() {
		
		std::string text = this->editingField->getText();

		std::regex isNumeric("^([+-]?[1-9]\\d*|0)$"); // make it an static member?
		int myValue = (std::regex_match(text, isNumeric)) ?  std::stoi(text) :  this->getCurrentValue();
		
		this->setCurrentvalue(myValue);
		this->editingField->setText(std::to_string(this->getCurrentValue()));

	});



	//Calculate the Padding to center the text
	int padding = (int)(this->rectangle.h - minTextFieldHeight) / 2;
	this->editingField->setPadding(0, 0, padding, padding);


	this->setBackgroundColor(SDL_Color{ 255,255,255,255 });
	this->setOpaque(true);
	this->addComponent(this->editingField);
	this->addComponent(this->scrollbar);
	this->invalidateRenderState();
}

GUISpinner::~GUISpinner()
{
	// Components instantiated here will be deleted by GUIContainer destructor
	
}

int GUISpinner::getCurrentValue()
{
	return this->currentValue;
}

void GUISpinner::setCurrentvalue(int value)
{
	this->currentValue = value > this->maxValue ? this->maxValue : value < minValue ? this->minValue : value;
	this->invalidateRenderState();
}

void GUISpinner::draw(SDL_Renderer * renderer)
{

	GUIPanel::draw(renderer);
	this->validateRenderState();
}

void GUISpinner::setMinValue(int minValue)
{
	this->minValue = minValue < this->maxValue ? minValue : this->maxValue;
}

void GUISpinner::setMaxValue(int maxValue)
{
	this->maxValue = maxValue > this->minValue ? maxValue : this->minValue;
}

void GUISpinner::setPace(int pace)
{
	this->pace = pace < (this->maxValue - this->minValue) ? pace : this->pace;
}

void GUISpinner::setNotifyEditingListener(std::function<void(GUITextField*editingField)> editingListener)
{
	this->notifyEditing = editingListener;
}
