// Component Showcase and demo application for SDL2_GUI lib.

//
#include <iostream>

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#define FONT_LOCATION "/Library/Fonts/Arial.ttf"
#elif defined _WIN32 || _WIN64
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#define FONT_LOCATION "C:/Windows/Fonts/Arial.ttf"
#endif


#include <memory>
#include "SDL2_GUI.h"


void checkSDLError(int);
void keyPressed(SDL_Event keyEvent);
void mousePressed(SDL_Event mouseEvent);
void keyReleased(SDL_Event keyEvent);
void mouseReleased(SDL_Event mouseEvent);
void draw(SDL_Renderer *renderer);



SDL_Texture * loadImage(const char * path, SDL_Renderer * renderer)
{
	SDL_Surface *loadingSurface = IMG_Load(path);
	if (!loadingSurface)
	{
		std::cout << "Error loading textfield BG image " << IMG_GetError() << std::endl;
	}
	SDL_Texture * loadedTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);

	SDL_FreeSurface(loadingSurface);

	return loadedTexture;
}



int main(int argc, char* argv[])
{

	bool isAppRunning = true;
	/*
	* Initializing SDL components and libraries
	*/
	SDL_Window * mainWindow;
	SDL_Renderer * sdlRenderer;
	SDL_Event sdlEvent;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		checkSDLError(__LINE__);
		exit(-1);
	}

	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init error, Unable to load TTF library: " << TTF_GetError() << std::endl;
		exit(-1);
	}

	if (IMG_Init(IMG_INIT_JPG) != (int)IMG_INIT_JPG) {
		std::cout << "Unable to init Image Library: " << IMG_GetError() << std::endl;
	}

	mainWindow = SDL_CreateWindow("SDL2_GUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	if (mainWindow == NULL)
	{
		std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
		exit(-1);
	}

	sdlRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (sdlRenderer == NULL)
	{
		std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(mainWindow);
		exit(-1);
	}
	/* Set the render to draw transparency*/
	SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);


	/* Loading default font - Arial */
	TTF_Font * arial = TTF_OpenFont(FONT_LOCATION, 18);
	if (arial == NULL)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
		SDL_DestroyWindow(mainWindow);
		SDL_DestroyRenderer(sdlRenderer);
		exit(-1);
	}


	/***********************************
	*                Load Images
	***********************************/

	SDL_Texture * backgroundImage = loadImage("E:\\Projetos\\assets\\Sample_BG.png", sdlRenderer);

	SDL_Texture * textfieldBg = loadImage("E:\\Projetos\\assets\\textfield_bg_border_gray_alpha.png", sdlRenderer);

	SDL_Texture * textfieldEditingBg = loadImage("E:\\Projetos\\assets\\textfield_bg_border_cyan_alpha.png", sdlRenderer);

	SDL_Texture * buttonOffBg = loadImage("E:\\Projetos\\assets\\buttons\\btn_1_off.png", sdlRenderer);

	SDL_Texture * buttonLitBg = loadImage("E:\\Projetos\\assets\\buttons\\btn_1_lit.png", sdlRenderer);



	/***********************************
	*                Load Images
	***********************************/



	/*
	* SDL2_GUI code
	*/



	/* Creating some basic color to our components */
	SDL_Color bg{ 255, 255, 0, 125 };
	SDL_Color c_red{ 255, 0, 0, 125 };
	SDL_Color c_green{ 0, 255, 0, 125 };
	SDL_Color c_blue{ 0, 0, 255, 125 };
	SDL_Color c_black{ 0, 0, 0, 255 };
	SDL_Color c_white{ 255, 255, 255, 125 };
	SDL_Color border{ 255, 0, 255, 125 };

	/* Main SDL2_GUI object. All components will be childs of GUIManager */
	GUIManager manager;

	int rendererW, rendererH;
	SDL_GetRendererOutputSize(sdlRenderer, &rendererW, &rendererH);

	GUIPanel * mainPanel = new GUIPanel(0, 0, rendererW, rendererH);
	mainPanel->setOpaque(true);
	mainPanel->setBackgroundImage(backgroundImage);

	GUIPanel * subPanel = new GUIPanel(75, 85, 685, 395);
	subPanel->setOpaque(true);
	subPanel->setDrawBgColor(false);

	GUILabel * testLabel1 = new GUILabel(400, 25, 450, 25, "Simple Ui Label", arial, false);
	testLabel1->setLabelColor(c_white);
	testLabel1->setDrawBgColor(false);
	testLabel1->setBorderColor(c_white);
	testLabel1->setAction([] {std::cout << "Clicked in Label" << std::endl; });

	GUIButton * button1 = new GUIButton(10, 1, 34, 34, "", arial, false);
	button1->setClickedColor(c_green);
	button1->setBackgroundColor(c_blue);
	button1->setBackgroundImage(buttonOffBg);
	button1->setClickedImage(buttonLitBg);
	button1->setBorderColor(border);
	//set button action
	button1->setAction([&] {std::cout << "Btn4 Clicked" << std::endl; });

	GUITextField * textField = new GUITextField(320, 550, 190, 31, "Simple Text Field", arial, false);
	textField->setIsPassword(false);
	textField->setAction([&] {
		std::cout << "Iniciando a digitacao do texto" << std::endl;
		manager.setActiveInputTextComponent(textField);
	});
	textField->setReturnPressedAction([&] {
		std::cout << "Texto Digitado: " << textField->getText() << std::endl;
	});
	//textField->setBackgroundColor(c_white);
	textField->setDrawBgColor(false);
	textField->setPadding(5, 5, 5, 5);
	textField->setLabelColor(c_blue);
	textField->setBackgroundImage(textfieldBg);
	textField->setBackgroundImageEditing(textfieldEditingBg);
	textField->setMaxTextLenght(15);

	/*
	Scrollbar
	*/

	GUIScrollbar *scrollbar = new GUIScrollbar(20, 230, 150, 20, arial, GUIScrollbar::ALIGN_VERTICAL);
	scrollbar->setBackgroundColor(c_white);
	scrollbar->setNotifyDecrementListener([&](unsigned int currentValue) { std::cout << "Notify Decrement" << currentValue << std::endl; });
	scrollbar->setNotifyIncrementListener([&](unsigned int currentValue) { std::cout << "Notify Increment" << currentValue << std::endl; });


	/*
	Spinner
	*/

	GUISpinner * spinner = new GUISpinner(50, 150, 60, 30, arial, -10000, 10000);
	spinner->setNotifyEditingListener([&](GUITextField * textField) {
		manager.setActiveInputTextComponent(textField);
	});




	/*
	TextArea
	*/
	GUITextArea *textArea = new GUITextArea(164, 84, 600, 300, arial);
	textArea->setOpaque(false);
	textArea->setPadding(50, 10, 30, 30);
	textArea->setText("Neste sentido, o entendimento das metas propostas maximiza as possibilidades por conta das formas de ação. A prática cotidiana prova que a crescente influência da mídia auxilia a preparação e a composição do sistema de participação geral. No entanto, não podemos esquecer que a consolidação das estruturas auxilia a preparação e a composição do processo de comunicação como um todo.");
	textArea->setTextColor(c_white);
	textArea->setDrawBgColor(false);


	// Add fields to layout

	mainPanel->addComponent(testLabel1);
	mainPanel->addComponent(subPanel);
	subPanel->addComponent(button1);

	manager.addComponent(mainPanel);
	manager.addComponent(textField);

	mainPanel->addComponent(scrollbar);
	mainPanel->addComponent(spinner);

	mainPanel->addComponent(textArea);

	bool created = true;

	SDL_StartTextInput();
	while (isAppRunning)
	{
		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				isAppRunning = false;
				break;
			case SDL_KEYDOWN:
				manager.keyPress(sdlEvent.key.keysym);
				keyPressed(sdlEvent);
				break;
			case SDL_KEYUP:
				manager.keyRelease(sdlEvent.key.keysym);
				keyReleased(sdlEvent);
				break;
			case SDL_MOUSEBUTTONDOWN:
				/* Dispatch the events for GUIManager */
				manager.click(sdlEvent.button.x, sdlEvent.button.y);
				mousePressed(sdlEvent);
				break;
			case SDL_MOUSEBUTTONUP:
				manager.release(sdlEvent.button.x, sdlEvent.button.y);

				mouseReleased(sdlEvent);
				break;

			case SDL_TEXTEDITING:
				std::cout << "TextEdit: { text:" << sdlEvent.edit.text
					<< " start:" << sdlEvent.edit.start
					<< " lenght:" << sdlEvent.edit.length << " } " << std::endl;

			case SDL_TEXTINPUT:
				std::cout << "Text: " << sdlEvent.text.text << std::endl;
				manager.textInput(sdlEvent.text);
				break;
			default:
				break;
			}

		}

		SDL_RenderClear(sdlRenderer);

		/*
		* Draw the GUIManager as last component if you wish
		* it to be displayed at top of other rendering
		*/
		manager.draw(sdlRenderer);



		//SDL_RenderCopy(sdlRenderer, textfieldBg, &textureRect, &textureRect);
		SDL_RenderPresent(sdlRenderer);

	}

	// Dealocate components
	manager.destroy();



	SDL_DestroyTexture(backgroundImage);

	SDL_DestroyTexture(textfieldBg);

	SDL_DestroyTexture(textfieldEditingBg);

	SDL_DestroyTexture(buttonOffBg);

	SDL_DestroyTexture(buttonLitBg);
	IMG_Quit();

	TTF_CloseFont(arial);
	TTF_Quit();

	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();

	std::cout << "System shutdown gracefully" << std::endl;


	return 0;
}


void keyPressed(SDL_Event keyEvent) {}
void mousePressed(SDL_Event mouseEvent) {}
void keyReleased(SDL_Event keyEvent) {}
void mouseReleased(SDL_Event mouseEvent) {


}

void checkSDLError(int line = -1)
{
#ifndef NDEBUG
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		printf("SDL Error: %s\n", error);
		if (line != -1) {
			printf(" + line: %i\n", line);
		}
		SDL_ClearError();
	}
#endif
}