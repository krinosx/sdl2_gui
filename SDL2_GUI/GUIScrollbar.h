#pragma once
#include "GUIPanel.h"
#include "GUIButton.h"
/**
 * @brief Represent an scrollbar.
 * 
 * The component have 2 clickable areas that increment internal counter to track the 
 * current position of the bar. It can be horizontal or vertical bar. 
 * 
 */
class GUIScrollbar :
	public GUIPanel
{

private:
	unsigned int align = ALIGN_VERTICAL; /**< Define if the bar is drawn horizontally or vertically */
	unsigned int min = 0;/**< Minimum value tracked by the scrollbar */	
	unsigned int max = 100;/**< Maximum value tracked by the scrollbar */
	unsigned int currentValue = 0; /**< Current value for scrollbar */	
	unsigned int pace = 10;/**< How many inits each increment()/decrement() function call will add or remove to currentValue */
	void increment(); /**< Increment in 'pace' units the currentValue */
	void decrement(); /**< Decrement in 'pace' units the currentValue */

	/** 
	 * GUIButton component to act as an increment clickable area. If its horizontal aligned, 
 	 * the increment will be on right hand part. If its vertical, increment button will be on top
	 */
	GUIButton *incrementButton; 
 	/** 
	 * GUIButton component to act as an decrement clickable area. If its horizontal aligned, 
 	 * the increment will be on left hand part. If its vertical, increment button will be on bottom
	 */
	GUIButton *decrementButton; 
	/** Callback function to be executed when a increment happens */
	std::function<void(unsigned int currentValue)> notifyDecrement = nullptr;
	/** Callback function to be executed when a decrement happens */
	std::function<void(unsigned int currentValue)> notifyIncrement = nullptr;
	
public:
	// Constants
	static const unsigned int ALIGN_VERTICAL = 0; /**< Local constant to define alignment */
	static const unsigned int ALIGN_HORIZONTAL = 1; /**< Local constant to define alignment */
	unsigned static const int MIN_BUTTON_SIZE = 20; /**< Minimum size a button must be draw - for now only square buttons */
	unsigned static const int MIN_BAR_WIDTH = MIN_BUTTON_SIZE * 2; /**< Minimum width (considering a horizontal bar) a scrollbar must be draw (its necessary at least 2 buttons ) */
	unsigned static const int MIN_BAR_HEIGHT = MIN_BUTTON_SIZE; /**< Minimum height (considering a horizontal bar) a button must be draw */
	/**
	 * @brief Construct a new GUIScrollbar object with default values
	 * 
	 */
	GUIScrollbar();
	/**
	 * @brief Construct a new GUIScrollbar
	 * 
	 * @param x desired x position for this component
	 * @param y desired y position for this component
	 * @param w desired width for this component
	 * @param h desired height for this component
	 * @param font font to render the buttons - TODO: It must be changed to textures/images
	 * @param align define if it must be  horizontal or vertical aligned
	 */
	GUIScrollbar(int x, int y, int w, int h, TTF_Font * font, unsigned int align = ALIGN_HORIZONTAL);
	~GUIScrollbar();


	/**
	 * @brief Set the minimum value tracked by scrollbar
	 * 
	 * When current value matches the minimum value, any decrement will have no effects.
	 * 
	 * @param minValue 
	 */
	void setMinValue(unsigned int minValue);
	/**
	 * @brief Set the maximum value tracked by scrollbar
	 * 
	 * When current value matches the maximum value, any increment will have no effects.
	 * 
	 * @param maxValue 
	 */
	void setMaxValue(unsigned int maxValue);
	/**
	 * @brief define the rate of change for each call of increment or decrement methods
	 * 
	 * @param pace an integer tha must be less than the maximum value
	 */
	void setPace(unsigned int pace);
	/**
	 * @brief return the minimum value tracked by this component
	 * 
	 * @return unsigned int minimum value tracked by this component 
	 */
	unsigned int getMinValue();
	/**
	 * @brief return the maximum value tracked by this component
	 * 
	 * @return unsigned int maximum value tracked by this component 
	 */	
	unsigned int getMaxValue();
	/**
	 * @brief Get the current value for this object. This value can be used to determine the positioning of the scrollable component.
	 * 
	 * @return unsigned int 
	 */
	unsigned int getCurrentValue();
	/**
	 * @brief set a pointer to a function to be called every time a successful increment happens
	 * 
	 * @param incrementListener 
	 */
	void setNotifyIncrementListener(std::function<void(unsigned int currentValue)> incrementListener);
	/**
	 * @brief set a pointer to a function to be called every time a successful decrement happens
	 * 
	 * @param decrementListener 
	 */
	void setNotifyDecrementListener(std::function<void(unsigned int currentValue)> decrementListener);

	/**
	 * @brief Call the draw pipeline for this component and nested components.
	 * 
	 * @param renderer 
	 */
	void draw(SDL_Renderer * renderer);
};
