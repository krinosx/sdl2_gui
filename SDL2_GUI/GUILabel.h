#pragma once
#include "GUIComponent.h"
#include <string>
/**
This class is a specialization of GUIComponent. THe intent of it is to enable the
text drawing and border drawing.

*/
class GUILabel :
	public GUIComponent
{
protected:
	std::string label;
	SDL_Color labelColor = { 0,0,0,0 };
	SDL_Color borderColor = { 0,0,0,0 };
	bool drawBorder = false;
	TTF_Font * font = NULL;
	/** Texture to render the text */
	SDL_Texture * texture = NULL;
	SDL_Rect labelRectangle = { 0,0,0,0 };
	
	/** Distance from Left/Right/Top/Bottom in pixels to draw the text */
	int padLeft, padRight, padTop, padBottom = 0;
	
	void generateLabelTexture(SDL_Renderer *renderer);
	SDL_Texture* generateTextTexture(SDL_Renderer * renderer, const char *text);

	// Draw functions
	void drawBackground(SDL_Renderer * renderer);
	void drawBackgroundImage(SDL_Renderer * renderer, SDL_Texture *backgroundImage, SDL_Rect *imageRect);
	void drawBackground(SDL_Renderer * renderer, SDL_Color color);
	void drawBorders(SDL_Renderer * renderer, SDL_Color borderColor);
	void drawBorders(SDL_Renderer * renderer);



public:
	void setParent(GUIComponent * component);
	GUILabel(int x, int y, int w, int h, std::string label, TTF_Font * font, bool border = false);
	~GUILabel();
	void setLabelColor(SDL_Color color);
	void setBorderColor(SDL_Color color);
	void draw(SDL_Renderer* renderer);
	
	void release(int x, int y);
	void setPadding(int left, int right, int top, int bottom);
};

