#include "GUITextArea.h"



/*
Auxiliary functions - May be set in a 'Utils' Object
*/

std::vector<std::string> split(const char *str, char c = ' ')
{
	std::vector<std::string> result;

	do
	{
		const char *begin = str;

		while (*str != c && *str)
			str++;

		result.push_back(std::string(begin, str));
	} while (0 != *str++);

	return result;
}

SDL_Surface * drawLineText(SDL_BlendMode mode, TTF_Font * textFont, const char *text, SDL_Color fgColor, SDL_Color bgColor = {0,0,0,255} )
{

	if (mode == SDL_BLENDMODE_BLEND)
	{
		return TTF_RenderText_Blended(textFont, text, fgColor);
	} 
	else 
	{
		return TTF_RenderText_Shaded(textFont, text, fgColor, bgColor);
	}
}

SDL_Texture * GUITextArea::renderTextToTexture(std::vector<std::string> textLines, TTF_Font * font, SDL_Rect bounds, SDL_Renderer * renderer ) {


	Uint32 rmask, gmask, bmask, amask;
	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	on the endianness (byte order) of the machine */
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	// Create the full text area surface
	SDL_Surface * textAreaSurface = SDL_CreateRGBSurface(0, bounds.w, bounds.h, 32, rmask, gmask, bmask, amask);
	int totalHeight = textAreaSurface->h;

	SDL_BlendMode blendMode;

	if (SDL_GetRenderDrawBlendMode(renderer, &blendMode) < 0)
	{
		// If we got an error, so set blendMode t0 BLEND
		blendMode = SDL_BLENDMODE_BLEND;

		std::cout << "Error getting blend mode?: " << SDL_GetError() << std::endl;
	}


	// top position of current drawing line
	int currentH = this->paddingTop;

	for (std::string line : textLines)
	{

		SDL_Surface * lineSurface = drawLineText(blendMode, font, line.c_str(), this->textColor, this->backgroundColor );

		int lineSurfaceW = lineSurface->w;;
		int lineSurfaceH = lineSurface->h;
		
		if ( (currentH + lineSurfaceH + this->paddingBottom) < totalHeight) 
		{
			// only draw if we have space in the textArea, ignore the remaining text
			
			SDL_Rect src = lineSurface->clip_rect;
			SDL_Rect dest = { this->paddingLeft, currentH, lineSurfaceW, lineSurfaceH };
			SDL_BlitSurface(lineSurface, &src, textAreaSurface, &dest);
						
			currentH += lineSurfaceH;
			SDL_FreeSurface(lineSurface);
		} 
		else 
		{
			SDL_Surface * overflowSurface = drawLineText(blendMode, font, "(...)", this->textColor, this->backgroundColor);
			SDL_Rect destOverflow;
			destOverflow.y = currentH - overflowSurface->h;
			destOverflow.x = textAreaSurface->w - overflowSurface->w - this->paddingRight;
			destOverflow.w = overflowSurface->w;
			destOverflow.h = overflowSurface->h;

			SDL_BlitSurface(overflowSurface, NULL, textAreaSurface, &destOverflow);
			SDL_FreeSurface(overflowSurface);
		}
	}



	// Convert to a texture and return
	SDL_Texture * renderedTexture = SDL_CreateTextureFromSurface(renderer, textAreaSurface);
	SDL_FreeSurface(textAreaSurface);
	return renderedTexture;
}


void GUITextArea::draw(SDL_Renderer * renderer)
{
	if (!this->isRenderStateValid()) {
		this->textTexture = renderTextToTexture(this->textLines, this->textFont, this->rectangle, renderer);
	}

	// Draw BGColor and child elements
	GUIPanel::draw(renderer);
	SDL_RenderCopy(renderer, this->textTexture, NULL,&this->rectangle);
	this->validateRenderState();
	
}


std::vector<std::string> GUITextArea::getTextLinex(std::string text, SDL_Rect bounds, TTF_Font * font)
{

	/*
		Tokenize the string to get separated words, in order to be presented
	*/
	std::vector<std::string> tokens;
	tokens = split(text.c_str(), ' ');

	// Get font size information
	int fontHeight = TTF_FontHeight(font);
	int maxLineWidth = this->rectangle.w - this->paddingRight;// -this->paddingLeft - this->paddingRight;

	int spaceHeight = 0;
	int spaceWidth = 0;
	TTF_SizeText(font, " ", &spaceWidth, &spaceHeight);


	std::vector<std::string> textLines;
	textLines.clear();

	// The line start considering the padding
	int currentLineWidth = this->paddingLeft;
	
	std::string currentLine;
	currentLine.clear();
	
	for (std::string word : tokens)
	{
		int wordHeight = 0;
		int wordWidth = 0;;
		TTF_SizeText(font, word.c_str(), &wordWidth, &wordHeight);
		
		//FIXME: How about a single word is bigger than the max size?
		if ( (currentLineWidth + spaceWidth + wordWidth + this->paddingRight ) > maxLineWidth)
		{ // Put current line in the array and start a new line with the current word

			//ensure null terminated string
			currentLine.push_back('\0');
			// Check how to copy this values, if needed
			textLines.push_back(currentLine);
			
			// start a new line
			currentLine = std::string();
			currentLine.append(word);
			currentLine.push_back(' ');
			currentLineWidth = this->paddingLeft + wordWidth + spaceWidth;
		}
		else 
		{ // we still have space
			currentLine.append(word);
			currentLine.push_back(' ');

			currentLineWidth += wordWidth + spaceWidth;
		}
	}

	// Put the remaining string in the list
	currentLine.push_back('\0');
	textLines.push_back(currentLine);

	return textLines;
}

GUITextArea::GUITextArea(int x, int y, int w, int h, TTF_Font * font)
	:GUIPanel(x, y, w, h), paddingLeft(5), paddingRight(5), paddingTop(5), paddingBottom(5), textTexture(NULL)
{
	this->setId(std::string("GUITextArea-").append(std::to_string(GUIComponent::compCount)));
	this->textFont = font;
	this->invalidateRenderState();
	
}

GUITextArea::~GUITextArea()
{
	if (this->textTexture) {
		SDL_DestroyTexture(this->textTexture);
	}

}

int GUITextArea::setText(std::string text)
{
	this->invalidateRenderState();
	this->text = text;

	this->textLines = this->getTextLinex(text, this->rectangle, this->textFont);

	return this->textLines.empty() ?  this->textLines.size() : 0;
	this->invalidateRenderState();
}

void GUITextArea::setTextColor(SDL_Color color)
{
	this->textColor = color;
	this->invalidateRenderState();
}

void GUITextArea::setPadding(int paddingLeft, int paddingRight, int paddingTop, int paddingBottom)
{
	this->paddingLeft = paddingLeft;
	this->paddingRight = paddingRight;
	this->paddingTop = paddingTop;
	this->paddingBottom = paddingBottom;
	this->invalidateRenderState();
}
