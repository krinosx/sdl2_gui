#pragma once

#include "GUIPanel.h"

class GUITextArea : public GUIPanel
{
private:
	std::string text;
	SDL_Texture * textTexture;
	TTF_Font * textFont;
	SDL_Color textColor = { 0,0,0,0 };
	int paddingLeft, paddingRight, paddingTop, paddingBottom, lineSpacing = 0;
	
	std::vector<std::string> textLines;
	std::vector<std::string> getTextLinex(std::string text, SDL_Rect bounds, TTF_Font * font);

	SDL_Texture * GUITextArea::renderTextToTexture(std::vector<std::string> textLines, TTF_Font * font, SDL_Rect bounds, SDL_Renderer * renderer );


public:
	GUITextArea(int x, int y, int w, int h, TTF_Font * font);
	~GUITextArea();

	/* Return how much lines the text will need to be rendered */
	int setText(std::string text);
	void setTextColor(SDL_Color color);
	void setPadding(int paddingLeft, int paddingRight, int paddingTop, int paddingBottom);

	void draw(SDL_Renderer * renderer);
};

