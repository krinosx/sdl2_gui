#include "GUIPanel.h"


GUIPanel::~GUIPanel()
{
	for (GUIComponent * component : this->childs){
		delete(component);
	}

}

void GUIPanel::addComponent(GUIComponent * component)
{
	if ( component != nullptr ) 
	{
		component->setParent(this);
		this->childs.push_back(component);	
	}
}

void GUIPanel::draw(SDL_Renderer * renderer)
{
	if (this->opaque)
	{
		GUIComponent::draw(renderer); // render background color
	}
	
	for (GUIComponent * comp : this->childs)
	{
		comp->draw(renderer);
	}
}
/*
	If set to opaque = true the background will be rendered. If it is set to 
	false the component will not be rendered and will be used only as a positional
	component.
*/
void GUIPanel::setOpaque(bool opaque) 
{ 
	this->opaque = opaque;
};
bool GUIPanel::isOpaque() 
{ 
	return this->opaque;
};

void GUIPanel::click(int x, int y)
{
	for (GUIComponent * comp : this->childs)
	{
		if (comp->isInside(x, y))
		{
			comp->click(x, y);
		}
	}
}
void GUIPanel::release(int x, int y){
	for (GUIComponent * comp : this->childs)
	{
		if (comp->isInside(x, y))
		{
			comp->release(x, y);
		}
	}
}


void GUIPanel::setParent(GUIComponent * parent)
{
	GUIComponent::setParent(parent);

	for (GUIComponent * comp : this->childs)
	{
		comp->setParent(this);
	}
}