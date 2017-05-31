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
	SDL_Color labelColor;
	SDL_Color borderColor;
	bool drawBorder;
	TTF_Font * font = NULL;
	/** Texture to render the text */
	SDL_Texture * texture = NULL;
	SDL_Rect labelRectangle;
	
	/** Distance from Left/Right/Top/Bottom in pixels to draw the text */
	int padLeft, padRight, padTop, padBottom;
	
	void generateLabelTexture(SDL_Renderer *renderer);

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

