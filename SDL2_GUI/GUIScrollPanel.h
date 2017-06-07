#pragma once
#include "GUIPanel.h"
#include "GUIScrollbar.h"

class GUIScrollPanel :
	public GUIPanel
{
private:
	GUIScrollbar * scrollbar;
	/* The view widow over the texture */
	SDL_Rect viewport;
	TTF_Font * font;
	SDL_Texture * contentTexture;
	/* Full boundaries of the content texture*/
	SDL_Rect contentSize;
	/* How much the texture must be moved in x/y directions*/
	SDL_Rect contentOffset;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	SDL_Texture * generateContent(SDL_Renderer * renderer);

	int paceY = 10;
	int paceX = 10;

	
	
public:
	GUIScrollPanel(int x, int y, int w, int h, TTF_Font * font);
	~GUIScrollPanel();
	void draw(SDL_Renderer * renderer);


	// Override methods
	void addComponent(GUIComponent * component);
	void setParent(GUIComponent * parent);

	void setYPace(int paceY);
	void setXpace(int paceX);
	void release(int x, int y);
	void click(int x, int y);
	bool isRenderStateValid();
	void validateRenderState();
};

