#pragma once
#include "GUIComponent.h"
#include <vector>

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

