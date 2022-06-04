#pragma once
#include "GUIPanel.h"
#include "GUIScrollbar.h"
/**
 * @brief Represents a panel restricted by a viewport.
 * 
 * This component have three different coordinates:
 * 1 - The contentSize - Tracking the coordinates for the full content
 * 2 - The viewport - The size of the content that will be shown 
 * 3 - The contentOffset - The delta relative to viewport related to the full content.
 * 
 * You can think as the content as a big image and the viewport as a small window that can
 * show only a portion of that image. The contentOffset will determine the viewport position
 * relative to the content. Only the viewport content will be draw.
 * 
 * The component also have a vertical scrollbar to move the viewport up and down. The horizontal
 * movement is not yet implemented.
 * 
 */
class GUIScrollPanel :
	public GUIPanel
{
private:

	int paceY = 10; /**< size in pixels to move the Y axis for each moveUp() or moveDown() methods call */
	int paceX = 10; /**< size in pixels to move the X axis for each moveLeft() or moveRight() methods call */

	GUIScrollbar * scrollbar; /**< Component to control the scrolling of viewport */
	/* The view widow over the texture */
	SDL_Rect viewport; /**< Coordinates for the viewport */
	TTF_Font * font; /**< Font to draw buttons - Must be replaced by textures in the future */
	SDL_Texture * contentTexture; /**< The panel content to be displayed */
	SDL_Rect contentSize; /**< Full boundaries of the content texture*/
	SDL_Rect contentOffset; /**< The delta for the viewport relative to original content */

	/**
	 * @brief Move the viewport up
	 */
	void moveUp();
	/**
	 * @brief move the viewport down
	 */
	void moveDown();
	/**
	 * @brief move the viewport left
	 */
	void moveLeft();
	/**
	 * @brief move the viewport right
	 */
	void moveRight();
	/**
	 * @brief render all child components to a texture.
	 * 
	 * This texture is considered the full content for the panel.
	 * 
	 * @param renderer 
	 * @return SDL_Texture* a texture with all child components drawn
	 */
	SDL_Texture * generateContent(SDL_Renderer * renderer);

public:
	/**
	 * @brief Construct a new GUIScrollPanel object
	 * 
	 * @param x desired x position for this component
	 * @param y desired y position for this component
	 * @param w desired width for this component
	 * @param h desired height for this component
	 * @param font font to draw the number
	 */
	GUIScrollPanel(int x, int y, int w, int h, TTF_Font * font);
	~GUIScrollPanel();
	/**
	 * @brief call the draw pipeline for this object
	 * 
	 * @param renderer 
	 */
	void draw(SDL_Renderer * renderer);

	// Override methods
	/**
	 * @brief Add a child component to this scroll panel.
	 * 
	 * @param component any GUIComponent
	 */
	void addComponent(GUIComponent * component);
	/**
	 * @brief Set the Parent for this component
	 * 
	 * @param parent 
	 */
	void setParent(GUIComponent * parent);
	/**
	 * @brief set the rate of change in pixels for each movUp() or moveDown() method call
	 * 
	 * @param paceY 
	 */
	void setYPace(int paceY);
	/**
	 *  @brief set the rate of change in pixels for each movLeft() or moveRight() method call 
	 * 
	 * @param paceX 
	 */
	void setXPace(int paceX);
	/**
	 * @brief method called when a click event is released inside the boundaries of this component
	 * 
	 * @param x 
	 * @param y 
	 */
	void release(int x, int y);
	/**
	 * @brief method called when a click event is pressed inside the boundaries of this component
	 * 
	 * @param x 
	 * @param y 
	 */
	void click(int x, int y);
	/**
	 * @brief Check if the current state is valid.
	 * 
	 * If some new components got added to this panel the internal textures must be
	 * generated again. So this method is called to ensure nothing has changed and the
	 * current state can be used to draw the component
	 * 
	 * @return true if the internal state is up to date
	 * @return false if its necessary to recalculate the internal state before drawn
	 */
	bool isRenderStateValid();
	/**
	 * @brief Set the internal state as valid
	 */
	void validateRenderState();
};

