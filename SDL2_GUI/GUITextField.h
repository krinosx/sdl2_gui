#pragma once
#include "GUILabel.h"
#include <regex>
class GUITextField :
	public GUILabel
{

private:
	SDL_Color borderColorEditing = { 0,0,0,0 };
	bool isEditing = false;
	int maxLenght = 256;
	SDL_Texture * backgroundImageEditing = NULL;
	SDL_Rect backgroundImageEditingRect = { 0,0,0,0 };
	std::regex regexFilter;
	bool isPassword = false;
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
	void setFilter(const char * regexExpression);
	void setIsPassword(bool isPassword);



};

