#pragma once

#include "GUIPanel.h"
/**
 * @brief A component to draw multi line text content.
 * 
 * It can be used with a GUIScrollPanel to produce a scrolling text area.
 * 
 */
class GUITextArea : public GUIPanel
{
private:
	std::string text; /**< Text to be rendered */
	SDL_Texture * textTexture; /**< Internal texture to render the text */
	TTF_Font * textFont; /**< Font to render the text  */
	SDL_Color textColor = { 0,0,0,0 }; /**< Foreground font to render the text */
	int paddingLeft = 0; /**< Distance from the left border */
	int paddingRight = 0; /**< Distance from the right border */
	int paddingTop = 0; /**< Distance from the top border */
	int paddingBottom = 0; /**< Distance from the bottom border */
	int lineSpacing = 0; /**< Distance between lines */
	
	std::vector<std::string> textLines; /**< once computed the line breaking points, separated lines will be stored in the vector for fast drawing */
	std::vector<std::string> getTextLines(std::string text, SDL_Rect bounds, TTF_Font * font); /**< return the vector with pre computed lines s*/
	/**
	 * @brief Based on line vector, draw the text to a internal texture/image
	 * 
	 * @param textLines Array with the lines already broken with the right text size to fit the textarea
	 * @param font font to draw the lines
	 * @param bounds coordinates for the texture
	 * @param renderer SDL_Renderer managing the scene
	 * @return SDL_Texture* a texture pointer to a image with the text drawn
	 */
	SDL_Texture * renderTextToTexture(std::vector<std::string> textLines, TTF_Font * font, SDL_Rect bounds, SDL_Renderer * renderer );

public:
	/**
	 * @brief Construct a new GUITextArea object
	 * 
	 * @param x desired x position for this component
	 * @param y desired y position for this component
	 * @param w desired width for this component
	 * @param h desired height for this component
	 * @param font font to draw the number
	 */
	GUITextArea(int x, int y, int w, int h, TTF_Font * font);
	~GUITextArea();
	/**
	 * @brief Set the text to be rendered and compute the array of lines based on
	 * the configured font and textArea boundaries. 
	 * 
	 * @param text A string with the text to be rendered.
	 * @return int number of lines to be rendered
	 */
	int setText(std::string text);
	/**
	 * @brief Define the color to render the text
	 * 
	 * @param color a SDL_Color structure 
	 */
	void setTextColor(SDL_Color color);
	/**
	 * @brief Define the padding to render the text
	 * 
	 * @param paddingLeft distance from the left border
	 * @param paddingRight distance from the right border
	 * @param paddingTop  distance from the top border
	 * @param paddingBottom distance from the bottom border
	 */
	void setPadding(int paddingLeft, int paddingRight, int paddingTop, int paddingBottom);
	/**
	 * @brief call the draw pipeline for this object
	 * 
	 * @param renderer 
	 */
	void draw(SDL_Renderer * renderer);
};
