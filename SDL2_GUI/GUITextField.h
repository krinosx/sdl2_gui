#pragma once
#include "GUILabel.h"
#include <regex>

/**
 * @brief This component works as a editable text field. 
 * It can be configured to accept only specific characters using a regex.
 * 
 * Limitations: As the current implementation it is responsibility of the programmer
 * to set the maxLength (in characters), the font size and the component size (rectangle)
 * to avoid stretching of the text. If size needed by the text is greater than the size 
 * available to the component the text will be shrieked to fit the available space.
 * 
 */
class GUITextField :
	public GUILabel
{
private:
	SDL_Color borderColorEditing = { 0,0,0,0 }; /**< Color to draw border while editing the text */
	bool isEditing = false; /**< Control if the component is being edited */
	int maxLength = 256; /**< Maximum number of characters to accept */
	SDL_Texture * backgroundImageEditing = NULL; /**< Background image do be drawn when component is in editing state*/
	SDL_Rect backgroundImageEditingRect = { 0,0,0,0 }; /**< Coordinates to the image drawn when component is in editing state */
	std::regex regexFilter; /** A regex patter to filter input characters */
	bool isPassword = false; /** Define if the input is a password. If its true, mask the value with '*' */
protected:
	std::function<void(void)> returnPressedAction;
		
public:
	/**
	 * @brief Construct a new GUITextField object
	 * 
	 * @param x desired x position for this component
	 * @param y desired y position for this component
	 * @param w desired width for this component
	 * @param h desired height for this component
	 * @param label string to be drawn
	 * @param font font definition to be used to drawn the text
	 * @param border define if the borders must be drawn 
	 */
	GUITextField(int x, int y, int w, int h, std::string label, TTF_Font * font, bool border = false);
	~GUITextField();
	/**
	 * @brief Return the current text from the component
	 * 
	 * @return std::string 
	 */
	std::string getText();
	/**
	 * @brief Set the text value for the component
	 * 
	 * @param text a string to be set as a text value
	 */
	void setText(std::string text);
	/**
	 * @brief Concatenate a character in the end of current text
	 * 
	 * @param c a character to be concatenated 
	 */
	void concat(const char * c);
	/**
	 * @brief remove the last character from the current text value
	 * 
	 * e.g. Used when user press the 'backspace' while editing.
	 * 
	 */
	void removeLastChar();
	/**
	 * @brief define the texture to be drawn when the component is in editing state
	 * 
	 * @param backgroundImageEditing SDL_Texture representing the image to be draw when component is in editing state
	 */
	void setBackgroundImageEditing(SDL_Texture * backgroundImageEditing);
	/**
	 * 
	 * @brief define the texture to be drawn when the component is in editing state
	 * 
	 * @param backgroundImageEditing SDL_Texture representing the image to be draw when component is in editing state
	 * @param rect the texture coordinates to be used with the texture
	 */
	void setBackgroundImageEditing(SDL_Texture * backgroundImageEditing, SDL_Rect rect);
	/**
	 * @brief Set the texture coordinates for backgroundImageEditing
	 * 
	 * @param x the X position relative to backgroundImageEditing texture
	 * @param y the Y position relative to backgroundImageEditing texture
	 * @param w the width of backgroundImageEditing to be used
	 * @param h the height of backgroundImageEditing to be used
	 */
	void setBackgroundImageEditingRect(int x, int y, int w, int h);
	/**
	 * @brief execute the drawn pipeline for this component
	 * 
	 * @param renderer the SDL_Renderer managing the scene
	 */
	void draw(SDL_Renderer *renderer);

	// On release event we start editing the field
	/**
	 * @brief Function called when a click is released in this component. This will make the component change state to GUIComponentState:editing
	 * 
	 * @param x X position where the click happened
	 * @param y Y position where the click happened
	 */
	void release(int x, int y);
	/**
	 * @brief Define an action to be execute every time the 'return key' (ENTER) is 
	 * pressed while the button is in GUIComponentState:editing state
	 * 
	 * @param function 
	 */
	void setReturnPressedAction(std::function<void(void)> function);
	/**
	 * @brief This method is executed when the 'return key' (ENTER) is pressed.
	 * In this specific component this method will finish the editing by returning the component to 
	 * GUIComponentState:base and executing any actions defined by this.returnPressedAction()
	 * 
	 */
	void returnPressed();

	// Change appearance to start editing
	/**
	 * @brief Change state to GUIComponentState:editing
	 */
	void startEditing();
	/**
	 * @brief Change state to GUIComponentState:base
	 */
	void stopEditing();
	/**
	 * @brief Set the maximum amount of character to be accepted
	 * 
	 * @param maxLength 
	 */
	void setMaxTextLength(int maxLength);
	/**
	 * @brief Define a regex expression to filter the inserted characters
	 * 
	 * @param regexExpression 
	 */
	void setFilter(const char * regexExpression);
	/**
	 * @brief Define if the value is a password
	 * If the text is a password, the rendered characters will be masked with a * instead of
	 * real characters. The method this.getText() will return the actual characters.
	 * 
	 * @param isPassword true - mask characters, false - print the actual characters
	 */
	void setIsPassword(bool isPassword);
};
