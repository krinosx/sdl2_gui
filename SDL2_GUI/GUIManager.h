#pragma once
#include "GUIComponent.h"
#include <vector>
/*
	Core class for the API: This class will be instantiated and all components 
	will be attached to it. It will manage the correct rendering and event dispatching
	to the child coponents.
*/
class GUIManager
{
public:
	GUIManager();
	~GUIManager();
	void addComponent(GUIComponent * component);
	void click(int x, int y);
	void release(int x, int y);
	void keyPress(SDL_Keysym key);
	void keyRelease(SDL_Keysym key);
	void draw(SDL_Renderer* renderer);
	void destroy();
private:
	std::vector<GUIComponent*> componentList;
};

