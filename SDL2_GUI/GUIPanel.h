#pragma once
#include "GUIComponent.h"
#include <vector>
/**
	A component to be used as a container for other components. The main use 
	for this one is to help the positioning of child components. edit

*/
class GUIPanel : public GUIComponent
{
private:
	
	bool opaque = false;

protected:
	std::vector<GUIComponent*> childs;
	void setParent(GUIComponent * parent);

public:
	GUIPanel();
	GUIPanel(int x, int y, int w, int h);
	~GUIPanel();
	void addComponent(GUIComponent * component);
	void draw(SDL_Renderer * renderer);
	void setOpaque(bool opaque);
	bool isOpaque();
	
	void click(int x, int y);
	void release(int x, int y);

};

