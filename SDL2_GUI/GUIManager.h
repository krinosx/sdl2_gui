#pragma once
#include "GUIComponent.h"
#include "SDL.h"
#include <vector>

class GUIManager
{
public:
	GUIManager();
	~GUIManager();
	void addComponent(GUIComponent * component);
	void click(int x, int y);
	void keyPress(int keyCode);
	void draw(SDL_Renderer* renderer);
private:
	std::vector<GUIComponent*> componentList;
};

