#include "GUIPanel.h"


GUIPanel::GUIPanel() : GUIComponent(0, 0, 0, 0) {

};

GUIPanel::GUIPanel(int x, int y, int w, int h) : GUIComponent(x, y, w, h) {
	this->setId(std::string("GUIPannel-").append(std::to_string(GUIComponent::compCount)));
	this->invalidateRenderState();
};

GUIPanel::~GUIPanel()
{
	for (GUIComponent * component : this->childs){
		if (component)
		{
			delete(component);
		}
	}

}

void GUIPanel::addComponent(GUIComponent * component)
{
	if ( component != nullptr ) 
	{
		component->setParent(this);
		this->childs.push_back(component);	
	}
	this->invalidateRenderState();
}

void GUIPanel::draw(SDL_Renderer * renderer)
{
	
	if (this->opaque)
	{
		GUIComponent::draw(renderer); // render background color
	}

	for (GUIComponent * comp : this->childs)
	{
		if (comp->isVisible())
		{
			comp->draw(renderer);
		}

	}

	this->validateRenderState();
	
}
/*
	If set to opaque = true the background will be rendered. If it is set to 
	false the component will not be rendered and will be used only as a positional
	component.
*/
void GUIPanel::setOpaque(bool opaque) 
{ 
	this->opaque = opaque;
	this->invalidateRenderState();
}

bool GUIPanel::isOpaque() 
{ 
	return this->opaque;
}

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
	this->invalidateRenderState();
}