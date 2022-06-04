/**
A GUILabel specialization. A button is basically a label with fancy functions. The button is
intended to be clicked so it have some click related functions and attributes.

attributes
clickedColor	-> Define a color to replace the background color when a button is clicked,
return to default color when the mouse is released

clickedTexture	-> Same logic as clickedColor

functions
click(x,y)		-> Send a click event to a component in the given coordinates

release(x,y)	-> Send a release event to a component in the given coordinates.

The actions related to its component is executed on release events.
*/
#pragma once
#include "GUILabel.h"
class GUIButton :
	public GUILabel
{
private:
	SDL_Color clickedColor; /**< Color to draw the background when button is clicked */
	SDL_Texture *clickedTexture; /**< Pointer to a texture to represent the TEXT to be drawn when button is clicked */
	void generateClickedTexture(SDL_Renderer * renderer); /**< internal function to generate the clicked background texture*/
	SDL_Texture * clickedImage; /**< Pointer to a texture to represent the backgroundImage to be drawn when the button is clicked */
	SDL_Rect clickedImageRect;/**< Coordinates to the background image to be drawn when button is clicked */

public:
	/**
	 * @brief Construct a new GUIButton object
	 * 
	 * @param x desired x position for this component
	 * @param y desired y position for this component
	 * @param w desired width for this component
	 * @param h desired height for this component
	 * @param label string to be drawn
	 * @param font font definition to be used to drawn the text
	 * @param border define if the borders must be drawn 
	 */
	GUIButton(int x, int y, int w, int h, std::string label, TTF_Font * font, bool border = false);
	~GUIButton();
	/**
	 * @brief execute the drawn pipeline for this component
	 * 
	 * @param renderer the SDL_Renderer managing the scene
	 */
	void draw(SDL_Renderer* renderer);
	/**
	 * @brief called when this button is pressed. 
	 * Basically change the state to GUIComponentState::pressed and
	 * invalidate the render state
	 * 
	 * @param x X position where the click happened
	 * @param y Y position where the click happened
	 */
	void click(int x, int y);
	/**
	 * @brief called when this button is released
	 * Basically change the state to GUIComponentState::base, call
	 * any assigned action and invalidate the render state
	 * 
	 * @param x X position where the click happened
	 * @param y Y position where the click happened 
	 */
	void release(int x, int y);
	/**
	 * @brief Define the background color to be drawn when the button is on GUIComponentState::pressed state
	 * 
	 * @param color SDL_Color structure
	 */
	void setClickedColor(SDL_Color color);
	/**
	 * @brief Define the background image to be drawn when the button is on GUIComponentState::pressed state
	 * 
	 * @param clickedImage SDL_Texture representing the image to be draw
	 */
	void setClickedImage(SDL_Texture * clickedImage);
	/**
	 * @brief Define the background image to be drawn when the button is on GUIComponentState::pressed state
	 * 
	 * @param clickedImage SDL_Texture representing the image to be draw
	 * @param rect the texture coordinates for the clicked image
	 */
	void setClickedImage(SDL_Texture * clickedImage, SDL_Rect rect);
	/**
	 * @brief Set the texture coordinate for clickedImage
	 * 
	 * @param x the X position relative to clickedImage texture
	 * @param y the Y position relative to clickedImage texture
	 * @param w the width of clickedImage to be used
	 * @param h the height of clickedImage to be used
	 */
	void setClickedImageRect(int x, int y, int w, int h);
};
