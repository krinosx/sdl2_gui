#include "GUIManager.h"


GUIManager::GUIManager()
{
}


GUIManager::~GUIManager()
{
	this->componentList.clear();
}


void GUIManager::addComponent(GUIComponent * component)
{
	this->componentList.push_back(component);
}


void GUIManager::click(int x, int y)
{
	for (GUIComponent *comp : this->componentList)
	{
		if (comp->isInside(x, y))
		{
			comp->click(x, y);
		}
	}
}

void GUIManager::release(int x, int y){
	for (GUIComponent *comp : this->componentList)
	{
		if (comp->isInside(x, y))
		{
			comp->release(x, y);
		}
	}
}


void GUIManager::keyPress(int keyCode)
{
	// handle key press events.... 
	// its posible to add a "shortcut key" here to access the components
	// or event handle events to open specific components, like menus
}

void GUIManager::keyRelease(int keyCode)
{
	// handle key press events.... 
	// its posible to add a "shortcut key" here to access the components
	// or event handle events to open specific components, like menus
}

void GUIManager::draw(SDL_Renderer* renderer)
{
	for (GUIComponent* component : this->componentList)
	{
		component->draw( renderer );
	}
}
