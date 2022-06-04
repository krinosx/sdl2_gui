#pragma once
#include "GUIComponent.h"
#include <vector>
/**
 A component to be used as a container for other components. The main use 
 for this one is to help the positioning of child components.
 @author Giuliano Bortolassi
*/
class GUIPanel : public GUIComponent
{
private:
	bool opaque = false; /**< define if the component should appear in the screen */

protected:
	std::vector<GUIComponent*> childs; /**< List of child components */
	void setParent(GUIComponent * parent); /**< Set the parent component */

public:
	/**
	 * @brief Construct a new GUIPanel object with default values
	 * 
	 */
	GUIPanel();
	/**
	 * @brief Construct a new GUIPanel object with the defined positioning and size
	 * 
	 * @param x desired x position for this component
	 * @param y desired y position for this component
	 * @param w desired width for this component
	 * @param h desired height for this component
	 */
	GUIPanel(int x, int y, int w, int h);
	~GUIPanel();
	/**
	 * @brief Add a child component to this panel
	 * 
	 * All child components will inherit the positioning from the panel.
	 * So, for all child components the coordinates will be relative to the parent panel.
	 * 
	 * @param component Any GUIComponent object
	 */
	void addComponent(GUIComponent * component);
	/**
	 * @brief Call the draw pipeline for this component and for all child components.
	 * 
	 * If this panel is is set as OPAQUE (opaque=true), the background color will be drawn. 
	 * If the panel is set to translucent (opaque=false), the nothing will be draw for this component, 
	 * but the child components will be draw nonetheless
	 * 
	 * @param renderer 
	 */
	void draw(SDL_Renderer * renderer);
	/**
	 * @brief Set the component as OPAQUE.
	 * 
	 * A Opaque panel have its background color drawn. Useful for debugging.
	 * If this property is set to false (default) nothing will be draw for this component. The child still drawn.
	 * 
	 * @param opaque 
	 */
	void setOpaque(bool opaque);
	/**
	 * @brief Check if the component is opaque
	 * 
	 * @return true means that the background color must be printed
	 * @return false means that the background color must not be printed
	 */
	bool isOpaque();
	/**
	 * @brief Click event inside the boundaries of this component
	 * 
	 * @param x X position where the click happened
	 * @param y Y position where the click happened
	 */
	void click(int x, int y);
	/**
	 * @brief Release event inside the boundaries of this component
	 * 
	 * @param x X position where the click happened
	 * @param y Y position where the click happened
	 */
	void release(int x, int y);

};

