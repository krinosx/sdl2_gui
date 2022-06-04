#pragma once
#include "GUIComponent.h"
#include <string>

/**
 @brief  used to draw simple texts (labels). 

 Allows to draw strings and border colors. It can be used to 
 represent 'tiles', descriptions for text fields and or other 
 simple (single line) texts.

 @author Giuliano Bortolssi 
*/
class GUILabel :
	public GUIComponent
{
protected:
	std::string label; /**< Text to be drawn */
	SDL_Color labelColor = { 0,0,0,0 }; /**< Foreground color to drawn the text */
	SDL_Color borderColor = { 0,0,0,0 }; /**< Border color */
	bool drawBorder = false; /**< define if the border should be drawn */
	TTF_Font * font = NULL; /**< Font definition to be used */
	/** Texture to render the text */
	SDL_Texture * texture = NULL; /**< Internal texture pointer used to draw the text before sending it to local drawing pipeline */
	SDL_Rect labelRectangle = { 0,0,0,0 }; /**< Coordinates, relative to this.texture used to render the text  */
	
	/** Distance from Left/Right/Top/Bottom in pixels to draw the text */
	int padLeft 	= 0; 	/**< distance in pixels from Left border */ 
	int padRight 	= 0; 	/**< distance in pixels from Right border */ 
	int	padTop 		= 0; 	/**< distance in pixels from Top border */
	int padBottom 	= 0; 	/**< distance in pixels from Bottom border */
	//void generateLabelTexture(SDL_Renderer *renderer);
	/**
	 * @brief Instruct component to recreate the tex texture.
	 * 
	 * It will generate a texture based on this.label string value. This texture will be sent
	 * to the this.draw() function to be rendered.
	 * 
	 * @param renderer the SDL_Renderer managing the scene
	 * @param isPassword set if the field is a password. if its a password a * will be draw for each character.
	 */
	void generateLabelTexture(SDL_Renderer *renderer, bool isPassword = false);
	/**
	 * @brief call SDL functions to create a texture with the given text. Its a INTERNAL function.
	 * 
	 * @param renderer the SDL_Renderer managing the scene
	 * @param text the text to be transformed in a texture
	 * @return SDL_Texture* a texture pointer to a image with the generated text
	 */
	SDL_Texture* generateTextTexture(SDL_Renderer * renderer, const char *text);

	// Draw functions
	void drawBackground(SDL_Renderer * renderer);
	void drawBackgroundImage(SDL_Renderer * renderer, SDL_Texture *backgroundImage, SDL_Rect *imageRect);
	void drawBackground(SDL_Renderer * renderer, SDL_Color color);	
	/**
	 * @brief Draw border using the color given
	 * 
	 * @param renderer SDL_Renderer managing the scene
	 * @param borderColor color to draw the border
	 */
	void drawBorders(SDL_Renderer * renderer, SDL_Color borderColor);
	/**
	 * @brief Draw the border using the pre configured color
	 * 
	 * @param renderer SDL_Renderer managing the scene
	 */
	void drawBorders(SDL_Renderer * renderer);

public:
	/**
	 * @brief Construct a new GUILabel object
	 * 
	 * @param x desired x position for this component
	 * @param y desired y position for this component
	 * @param w desired width for this component
	 * @param h desired height for this component
	 * @param label string to be drawn
	 * @param font font definition to be used to drawn the text
	 * @param border define if the borders must be drawn 
	 */
	GUILabel(int x, int y, int w, int h, std::string label, TTF_Font * font, bool border = false);
	~GUILabel();
	/**
	 * @brief Set the Parent component
	 * 
	 * @param component 
	 */
	void setParent(GUIComponent * component);
	/**
	 * @brief Set the color to drawn the text
	 * 
	 * @param color SDL_Color structure 
	 */
	void setLabelColor(SDL_Color color);
	/**
	 * @brief Set the color to drawn the borders
	 * 
	 * @param color SDL_Color structure 
	 */
	void setBorderColor(SDL_Color color);
	/**
	 * @brief Execute the component graphic pipeline
	 * 
	 * @param renderer SDL_Renderer managing the scene
	 */
	void draw(SDL_Renderer* renderer);
	/**
	 * @brief Callback function called when a click happens on this component.
	 * This fuction is called when the state of the click is 'released'. 
	 * This method will call any actions (function pointes) configured
	 * 
	 * @param x screen position where the click happened
	 * @param y screen position where the click happened
	 */
	void release(int x, int y);
	/**
	 * @brief Set the Padding values
	 * 
	 * @param left distance in pixels from Left border
	 * @param right distance in pixels from Right border
	 * @param top distance in pixels from Top border
	 * @param bottom distance in pixels from Bottom border
	 */
	void setPadding(int left, int right, int top, int bottom);
};
