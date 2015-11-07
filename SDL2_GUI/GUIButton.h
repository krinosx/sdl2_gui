#pragma once
#include "GUILabel.h"

class GUIButton :
	public GUILabel
{
private:
	SDL_Color clickedColor;
	SDL_Texture *clickedTexture;
	void generateClickedTexture(SDL_Renderer * renderer);
	

public:
	GUIButton(int x, int y, int w, int h, std::string label, TTF_Font * font, bool border = false);
	~GUIButton();
	void draw(SDL_Renderer* renderer);
	void click(int x, int y);
	void release(int x, int y);
	void setClickedColor(SDL_Color color);
};
