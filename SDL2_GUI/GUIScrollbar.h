#pragma once
#include "GUIPanel.h"
#include "GUIButton.h"
class GUIScrollbar :
	public GUIPanel
{

private:
	unsigned int align = ALIGN_VERTICAL;
	/* Min value that scroll must indicate*/
	unsigned int min = 0;
	/* Max value that scroll must indicate*/
	unsigned int max = 100;
	/* Current value for scrollbar */
	unsigned int currentValue = 0;
	/* How much inits each increment()/decrement() function call will change the current value*/
	unsigned int pace = 10;
	/* Increment in 'pace' units the currentValue */
	void increment();
	/* Decrement in 'pace' units the currentValue */
	void decrement();

	GUIButton *incrementButton;
	GUIButton *decrementButton;

	std::function<void(unsigned int currentValue)> notifyDecrement = nullptr;
	std::function<void(unsigned int currentValue)> notifyIncrement = nullptr;
	
public:
	GUIScrollbar();
	GUIScrollbar(int x, int y, int w, int h, TTF_Font * font, unsigned int align = ALIGN_HORIZONTAL);
	~GUIScrollbar();

	/* Indicate the scrollbar align */
	static const unsigned int ALIGN_VERTICAL = 0;
	static const unsigned int ALIGN_HORIZONTAL = 1;

	void setMinValue(unsigned int minValue);
	void setMaxValue(unsigned int maxValue);
	void setPace(unsigned int pace);
	unsigned int getMinValue();
	unsigned int getMaxValue();
	unsigned int getCurrentValue();

	void setNotifyIncrementListener(std::function<void(unsigned int currentValue)> incrementListener);
	void setNotifyDecrementListener(std::function<void(unsigned int currentValue)> decrementListener);


	void draw(SDL_Renderer * renderer);


	// Constants
	unsigned static const int MIN_BUTTON_SIZE = 20;
	unsigned static const int MIN_BAR_WIDTH = MIN_BUTTON_SIZE * 2;
	unsigned static const int MIN_BAR_HEIGHT = MIN_BUTTON_SIZE;


};

