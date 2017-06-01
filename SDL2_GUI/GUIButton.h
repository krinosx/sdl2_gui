/**
A GUILabel specialization. A button is basically a label with fancy functions. The button is
intented to be clicked so it have some click related functions and attributes.

attributes
clickedColor	-> Define a color to replace the background color when a button is clicked,
return to default color when the mouse is released

clickedTexture	-> Same logic as clickedColor

functions
click(x,y)		-> Send a click event to a component in the given coordinates

release(x,y)	-> Send a release event to a component in the given coordinates.
The actions related to its component is executed on release events.
*/
#pragma once
#include "GUILabel.h"
class GUIButton :
	public GUILabel
{
private:
	SDL_Color clickedColor;
	SDL_Texture *clickedTexture;
	void generateClickedTexture(SDL_Renderer * renderer);
	SDL_Texture * clickedImage;
	SDL_Rect clickedImageRect;

public:
	GUIButton(int x, int y, int w, int h, std::string label, TTF_Font * font, bool border = false);
	~GUIButton();
	void draw(SDL_Renderer* renderer);
	void click(int x, int y);
	void release(int x, int y);
	void setClickedColor(SDL_Color color);
	void setClickedImage(SDL_Texture * clickedImage);
	void setClickedImage(SDL_Texture * clickedImage, SDL_Rect rect);
	void setClickedImageRect(int x, int y, int w, int h);
};
