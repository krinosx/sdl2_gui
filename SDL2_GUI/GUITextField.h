#pragma once
#include "GUILabel.h"
class GUITextField :
	public GUILabel
{

private:
	bool textChanged = false;
	SDL_Color borderColorEditing;
	bool isEditing = false;
	int maxLenght = 256;
	SDL_Texture * backgroundImageEditing;
	SDL_Rect backgroundImageEditingRect;

protected:
	std::function<void(void)> returnPressedAction;
		
public:
	GUITextField(int x, int y, int w, int h, std::string label, TTF_Font * font, bool border = false);
	~GUITextField();

	std::string getText();
	void setText(std::string text);
	void concat(const char * c);
	void removeLastChar();
	void setBackgroundImageEditing(SDL_Texture * backgroundImageEditing);
	void setBackgroundImageEditing(SDL_Texture * backgroundImageEditing, SDL_Rect rect);
	void setBackgroundImageEditingRect(int x, int y, int w, int h);
	void draw(SDL_Renderer *renderer);

	// On release event we start editing the field
	void release(int x, int y);
	void setReturnPressedAction(std::function<void(void)> function);
	void returnPressed();
	// Change apearence to start editing
	void startEditing();
	void stopEditing();
	void setMaxTextLenght(int maxLenght);



};

