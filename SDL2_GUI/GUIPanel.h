#pragma once
#include "GUIComponent.h"
#include <vector>
/**
	A component to be used as a container for other components. The main use 
	for this one is to help the positioning of child components.

*/
class GUIPanel : public GUIComponent
{
private:
	std::vector<GUIComponent*> childs;
	bool opaque = false;

protected:
	void setParent(GUIComponent * parent);

public:
	GUIPanel() : GUIComponent(0, 0, 0, 0){};
	GUIPanel(int x, int y, int w, int h) : GUIComponent(x, y, w, h){};
	~GUIPanel();
	void addComponent(GUIComponent * component);
	void draw(SDL_Renderer * renderer);
	void setOpaque(bool opaque);
	bool isOpaque();
	
	void click(int x, int y);
	void release(int x, int y);

};

