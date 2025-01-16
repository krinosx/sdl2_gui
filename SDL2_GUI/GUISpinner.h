#pragma once
#include "GUIPanel.h"
#include "GUIScrollbar.h"
#include "GUITextField.h"
/**
 * @brief A component to track the value of a single INTEGER number. The number can be 
 * set manually (by typing it) or using buttons to increment or decrement the value.
 * 
 */
class GUISpinner :
	public GUIPanel
{

private:
	int currentValue = 0; /**< Current tracked value*/
	int minValue = 0; /**< Minimum tracked value */
	int maxValue = 10; /**< Maximum tracked value */
	int pace = 1; /**< Rate of change for each increment/decrement */
	GUITextField * editingField = nullptr; /**< GUITextField to allow manual value editing  */
	GUIScrollbar * scrollbar = nullptr; /** GUIScrollbar to be used as increment/decrement container */
	TTF_Font * font = NULL; /**< Font to draw the number */

	std::function<void(GUITextField * editingField)> notifyEditing; /**< Function pointer executed when manual editing starts*/
	/**
	 * @brief Called when a internal scrollbar button is clicked 
	 */
	void increment();
	/**
	 * @brief Called when a internal scrollbar button is clicked 
	 */
	void decrement();

public:
	/**
	 * @brief Construct a new GUISpinner object
	 * 
	 * @param x desired x position for this component
	 * @param y desired y position for this component
	 * @param w desired width for this component
	 * @param h desired height for this component
	 * @param font font to draw the number
	 * @param minValue minimum value allowed 
	 * @param maxValue maximum value allowed
	 */
	GUISpinner(int x, int y, int w, int h, TTF_Font * font, int minValue, int maxValue );
	~GUISpinner();
	/**
	 * @brief Return the current value tracked by this component
	 *
	 * @return int 
	 */
	int getCurrentValue() const;
	/**
	 * @brief Set the current value for the component
	 * 
	 * @param value 
	 */
	void setCurrentValue(int value);

	/**
	 * @brief call the draw pipeline for this object
	 * 
	 * @param renderer 
	 */
	void draw(SDL_Renderer * renderer);
	/**
	 * @brief define the minimum value allowed for this component
	 * 
	 * @param minValue 
	 */
	void setMinValue(int minValue);
	/**
	 * @brief define the maximum value allowed for this component
	 * 
	 * @param maxValue 
	 */
	void setMaxValue(int maxValue);
	/**
	 * @brief define the rate of change for each increment/decrement
	 * 
	 * @param pace 
	 */
	void setPace(int pace);
	/**
	 * @brief method executed when the internal GUITextField change state to editing.
	 * 
	 * Can be used to notify the GUIManager about editing fields
	 * 
	 * @param editingListener 
	 */
	void setNotifyEditingListener(std::function<void(GUITextField * editingField)> editingListener);
};

