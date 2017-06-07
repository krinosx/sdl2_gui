#include "GUIScrollPanel.h"


/* SDL interprets each pixel as a 32-bit number, so our masks must depend
on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
Uint32 rmask = 0xff000000;
Uint32 gmask = 0x00ff0000;
Uint32 bmask = 0x0000ff00;
Uint32 amask = 0x000000ff;
#else
Uint32 rmask = 0x000000ff;
Uint32 gmask = 0x0000ff00;
Uint32 bmask = 0x00ff0000;
Uint32 amask = 0xff000000;
#endif



GUIScrollPanel::GUIScrollPanel(int x, int y, int w, int h, TTF_Font * font)
	:GUIPanel(x,y,w,h), font(font)
{
	//init the scrollbar
	this->compId = std::string("GUIScrollPanel-").append(std::to_string(GUIComponent::compCount));


	this->contentTexture = nullptr;
	// scrollbar is based on horizontal alight
	int scrollBarHeight = GUIScrollbar::MIN_BAR_WIDTH;
	int scrollBarWidth = GUIScrollbar::MIN_BAR_HEIGHT;

	this->scrollbar = new GUIScrollbar(this->rectangle.w - scrollBarWidth, 0, this->rectangle.h, scrollBarWidth,font,GUIScrollbar::ALIGN_VERTICAL);
	
	this->scrollbar->setNotifyDecrementListener([this](unsigned int currentValue) { moveUp();  });
	this->scrollbar->setNotifyIncrementListener([this](unsigned int currentValue) { moveDown(); });
	
	this->scrollbar->setBackgroundColor({ 255, 255, 255, 255 });

	this->viewport = { this->rectangle.x, this->rectangle.y, this->rectangle.w - (int)GUIScrollbar::MIN_BAR_HEIGHT, this->rectangle.h };

	/* The texture will start alligned at top left corner- We wll change the x/y values when the scollbar is activated*/
	this->contentOffset = { 0, 0, this->viewport.w, this->viewport.h };

	this->addComponent(this->scrollbar);
	this->invalidateRenderState();

}


GUIScrollPanel::~GUIScrollPanel()
{
	if (this->contentTexture)
	{
		SDL_DestroyTexture(this->contentTexture);
	}
}


void GUIScrollPanel::validateRenderState()
{
	this->renderStateValid = true;
	this->scrollbar->validateRenderState();
}


bool GUIScrollPanel::isRenderStateValid()
{
	// If the state is already invalid, its invalid....
	if (!this->renderStateValid) {
		return false;
	} 

	// if not check the childs 
	

	for (GUIComponent * comp : this->childs)
	{
		if (!comp->isRenderStateValid())
		{
			return false;
		}
	}
	// If no changes, so its still valid
	return true;

}


void GUIScrollPanel::draw(SDL_Renderer * renderer)
{
	if ( !this->isRenderStateValid() )
	{
		std::cout << "Rebuilding texture" << std::endl;
		if (this->contentTexture)
		{
			SDL_DestroyTexture(this->contentTexture);
		}
		
		this->contentTexture = this->generateContent(renderer);
	}
	if (this->drawBgColor)
	{
		GUIComponent::draw(renderer);
	}

	// Here we do not draw the child elements we draw the content texture
	SDL_RenderCopy(renderer, this->contentTexture, &this->contentOffset, &this->viewport);
	
	//  Check if the content need a horizontal or vertical scrollbars
	if (this->contentSize.h > this->viewport.h) {
		this->scrollbar->draw(renderer);
	}
	
	this->validateRenderState();
	
}



void GUIScrollPanel::moveUp()
{
	// Check the boundaries
	if ((this->contentOffset.y + this->contentOffset.h + this->paceY) < this->contentSize.h) {
		this->contentOffset.y += paceY;
	}
	else
	{
		this->contentOffset.y = this->contentSize.h - this->contentOffset.h;
	}
}

void GUIScrollPanel::moveDown()
{
	this->contentOffset.y = this->contentOffset.y <= 0 ? 0 : this->contentOffset.y - paceY;
}

void GUIScrollPanel::moveLeft()
{
}

void GUIScrollPanel::moveRight()
{
}

SDL_Texture * GUIScrollPanel::generateContent(SDL_Renderer * renderer)
{
	// Check the content height by getting the biggest H with the child elements
	int maxHeight = 0;
	int maxWidth = 0;

	
	for(GUIComponent * comp : this->childs)
	{
		if (comp == this->scrollbar) {
			continue; // Ignore the scrollbar
		}
		SDL_Rect boundaries = comp->getRectangle();
		int lowerBoundary = boundaries.y + boundaries.h;
		int rightBoundary = boundaries.x + boundaries.w;
		
		if (lowerBoundary > maxHeight)
		{
			maxHeight = lowerBoundary;
		}

		if (rightBoundary > maxWidth)
		{
			maxWidth = rightBoundary;
		}
	}

	this->contentSize = { 0, 0, maxWidth, maxHeight };
	
	
	int textureW = contentSize.w < this->viewport.w ? this->viewport.w : contentSize.w;
	int textureH = contentSize.h < this->viewport.h ? this->viewport.h : contentSize.h;


	SDL_Texture * content = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET, textureW, textureH);
	// Draw child elements into surface
	SDL_SetTextureBlendMode(content, SDL_BLENDMODE_BLEND);

	if (SDL_SetRenderTarget(renderer, content) < 0)
	{
		// Error setting texture, generate an error texture
		std::cout << "Error changing the render target: " << SDL_GetError() << std::endl;
	}
	
	SDL_RenderClear(renderer);
	
	for (GUIComponent * comp : this->childs) {
		if (comp != this->scrollbar) {
			comp->draw(renderer);
		}
	}
	//Return the renderer to its dafault render target (window)
	SDL_SetRenderTarget(renderer, NULL);
	
	return content;
}

void GUIScrollPanel::setYPace(int paceY)
{
	this->paceY = paceY;
}

void GUIScrollPanel::setXpace(int paceX)
{
	this->paceX = paceX;
}

void GUIScrollPanel::release(int x, int y)
{
	for (GUIComponent * comp : this->childs)
	{
		int xOffset = x;
		int yOffset = y;

		if (comp != this->scrollbar) 
		{
			xOffset = (x - this->rectangle.x) + this->contentOffset.x;
			yOffset = (y - this->rectangle.y) + this->contentOffset.y;
		}	

		if (comp->isInside(xOffset, yOffset))
		{
			comp->release(xOffset, yOffset);
		}
	}
}

void GUIScrollPanel::click(int x, int y)
{
	for (GUIComponent * comp : this->childs)
	{
		int xOffset = x; 
		int yOffset = y; 

		if (comp != this->scrollbar) {
			// 'move the panel to 0,0
			xOffset = (x - this->rectangle.x) + this->contentOffset.x;
			yOffset = (y - this->rectangle.y) + this->contentOffset.y;
			std::cout << "Offset: Y=" << yOffset << std::endl;
		}
		
		if (comp->isInside(xOffset, yOffset))
		{
			comp->click(xOffset, yOffset);
		}
	}
}




void GUIScrollPanel::addComponent(GUIComponent * component)
{
	if (component != nullptr)
	{
		if (component == this->scrollbar){
			component->setParent(this);
		}
		this->childs.push_back(component);
	}
}


void GUIScrollPanel::setParent(GUIComponent * parent)
{
	GUIComponent::setParent(parent);
	

}
