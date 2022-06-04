
#pragma once
#include <string>
#include <iostream>


#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#elif defined _WIN32 || _WIN64
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "GUIComponentState.h"
#include <functional>
/**
Base class for all components. This class stores basic information about positioning,
rendering, states and a pointer to a function that is executed when a component receive
a click action. 

Each component have a pointer to its parent. It makes possible to generate a component
tree and disable or enable a whole branch of this tree at time.

@author Giuliano Bortolassi

*/
class GUIComponent
{

private:
	
	int x; /**< X position relative to the parent component. If parent is NULL the position is relative to render screen */
	int y; /**< Y position relative to the parent component. If parent is NULL the position is relative to render screen */	
	int w; /**< Width of the component */	
	int h; /**< Height of the component */
	/** 
	 * Compute the absolute (screen related) value for X. 
	 * 
	 * This method consider the x value for the current component and 
	 * also any x value from parent components in a component tree. The 
	 * returned value can be used to render the component in the right 
	 * screen position.
	 * 
	 * @return the absolute value for this component X
	 * */
	int getParentX();
	/** 
	 * Compute the absolute (screen related) value for ''y''. 
	 * 
	 * This method consider the y value for the current component and 
	 * also any **y** value from parent components in a component tree. The 
	 * returned value can be used to render the component in the right 
	 * screen position.
	 * 
	 * @return the absolute value for this component X
	 * */
	int getParentY();
	
protected:
	static int compCount; /**< Internal counter to track component creation. Used to generate component ids. */
	std::string compId; /**< Unique id for this component. */
	SDL_Rect rectangle = { 0,0,0,0 }; /**< Position coordinates for current component */
	SDL_Color backgroundColor = { 0, 0, 0, 0 }; /**< Background color. Presented if no image is defined */
	SDL_Texture *backgroundImage = NULL; /**< pointer to a texture to be drawn as the background */
	SDL_Rect backgroundImageRect = { 0,0,0,0 }; /**< Texture coordinates for a image do be drawn as a background for the component. 
													This value will be used as source coordinate and the component rectangle will be
													used as a destination coordinate. So consider the stretching factor while defining the
													sizes of this.rectangle and this.backgroundImageRect */
	GUIComponent * parent = nullptr; /**< Points to another component to create a parent-child relationship. This pointer allows to create a virtual
										component tree and decide, based on this.visible property if the child components must be draw. Also used to 
										determine positioning. If a parent component change position, all childs will follow the changes */
	bool drawBgColor = true;		/**< Define if the this.backgroundColor value must be draw */
	bool visible = true;	/**< Enable o disable the rendering of this component and all childs. */
	
	// internal use
	GUIComponentState state = GUIComponentState::base; /**< Current state for this component. Check the GUIComponentState class to more details */
	std::function<void(void)> action = nullptr; /**< Points to a function to be executed when this component is clicked */
	bool renderStateValid = false; /**< Keep track of changes in current component attributes and define if the component must be redraw. */
	
public:
	/**
	 * @brief Construct a new GUIComponent object
	 * 
	 * @param posX desired x position for this component
	 * @param posY desired y position for this component
	 * @param width desired width for this component
	 * @param height desired height for this component
	 */
	GUIComponent(int posX, int posY, int width, int height);
	virtual ~GUIComponent();
	/**
	 * @brief Get the unique Id for this component
	 * 
	 * @return std::string unique id for this component
	 */
	std::string getId();
	/**
	 * @brief Set the unique Id object. 
	 * If this method is used is is developer responsibility to ensure the uniqueness of 
	 * the ids
	 * 
	 * @param id a unique string value for the components.
	 */
	void setId(std::string id);
	/**
	 * @brief Get the current state (GUIComponentState) for the component
	 * 
	 * @return const GUIComponentState 
	 */
	const GUIComponentState getState() { return this->state; }
	/**
	 * @brief Set the BackgroundColor values 
	 * 
	 * @param backgroundColor a SDL_Color structure
	 */
	void setBackgroundColor(SDL_Color backgroundColor);
	/**
	 * @brief Set the pointer for a BackgroundImage
	 * 
	 * @param backgroundImage a valid SDL_Texture pointer or NULL to remove a previous given image
	 */
	void setBackgroundImage(SDL_Texture *backgroundImage);
	/**
	 *  @brief Set the pointer for a BackgroundImage and the transparency
	 * 
	 * @param backgroundImage a valid SDL_Texture pointer or NULL to remove a previous given image
	 * @param alpha the transparency value (alpha) - 0: for fully transparent, 255: for fully opaque
	 */
	void setBackgroundImage(SDL_Texture* backgroundImage, Uint8 alpha);
	/**
	 * @brief Set the coordinates to the background image.
	 * This values will be relative to this component backgroundImage texture. It defines the texture
	 * coordinates to be rendered in this component rectangle.
	 * 
	 * @param x the X position relative to backgroundImage texture
	 * @param y the Y position relative to backgroundImage texture
	 * @param w the width of backgroundImage to be used
	 * @param h the height of backgroundImage to be used
	 */
	void setBackgroundImageRect(int x, int y, int w, int h);
	/**
	 * @brief Special instructions to draw this component. Each component must implement its own
	 * drawing instruction based on component data. The default implementation for GUIComponent
	 * will draw:
	 *  - Background color 
	 *  - Background image
	 * 
	 * @param renderer A SDL renderer manager for the current scene.
	 */
	virtual void draw(SDL_Renderer* renderer);
	/**
	 * @brief Check if the given screen position is inside the current component.
	 * 
	 * @param x screen position where the click happened
	 * @param y screen position where the click happened
	 * @return true if X and Y are inside the component rectangle
	 * @return false if X or Y are outside the component rectangle
	 */
	bool isInside(int x, int y);
	/**
	 * @brief Callback function called when a click happens on this component.
	 * This fuction is called when the state of the click is 'pressed'
	 * 
	 * @param x screen position where the click happened
	 * @param y screen position where the click happened
	 */
	virtual void click(int x, int y){};
	/**
	 * @brief Callback function called when a click happens on this component.
	 * This fuction is called when the state of the click is 'released'
	 * 
	 * @param x screen position where the click happened
	 * @param y screen position where the click happened
	 */
	virtual void release(int x, int y){};
	/**
	 * @brief Set a pointer to a function to be called when this.release(x,y) function is activated.
	 * 
	 * @param function a pointer to a function
	 */
	void setAction(std::function<void(void)> function);
	/**
	 * @brief execute the function stored in this.action member.
	 * 
	 */
	virtual void performAction();
	/**
	 * @brief Set the Parent component
	 * 
	 * @param parent 
	 */
	virtual void setParent(GUIComponent * parent);
	/**
	 * @brief Configure if the bgColor must be drawn or not.
	 * 
	 * @param drawBgColor 
	 */
	void setDrawBgColor(bool drawBgColor) { this->drawBgColor = drawBgColor; }
	/**
	 * @brief Get the Rectangle values for this component
	 * 
	 * @return SDL_Rect the rectangle data
	 */
	SDL_Rect getRectangle() { return this->rectangle; }
	/**
	 * @brief Change the current component position and size
	 * 
	 * @param x new X position
	 * @param y new Y position
	 * @param w new width
	 * @param h new height
	 */
	virtual void resize(int x, int y, int w, int h) {};

	/* Visibility function*/
	/**
	 * @brief Check if the current component must be shown on the screen
	 * 
	 * @return true if component must be drawn
	 * @return false if component is hidden
	 */
	bool isVisible();
	/**
	 * @brief set the component to not be drawn
	 */
	void hide();
	/**
	 * @brief Set the component to be drawn
	 */
	void show();
	/**
	 * @brief if a component is visible make it hidden, if the component is hidden make it visieble.
	 */
	void toggle();

	/* Invalidate the render state and indicate it needs a redraw */
	/**
	 * @brief mark the component to be redraw.
	 * This method must be called every time the component have any changes in its 
	 * attributes or if some other changes on the scene make the component need to
	 * be redraw.
	 */
	void invalidateRenderState();
	/**
	 * @brief Method called after each render cycle to register the component was drawn
	 */
	void validateRenderState();
	/**
	 * @brief Check if the component must be redraw. 
	 * May be used before any draw on heavy components to avoid unecessary drawing requests.
	 * 
	 * @return true if component had no changes in its internal state
	 * @return false if component had changes and need to be redraw
	 */
	bool isRenderStateValid();
};