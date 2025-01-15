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
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#define FONT_LOCATION "/usr/share/fonts/truetype/ubuntu/UbuntuMono-B.ttf"
#endif


#include <memory>
#include "SDL2_GUI_Demo.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768


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

	SDL_version compiled;
	SDL_version linked;
	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	SDL_Log("SDL LIB - Compiled against SDL version %u.%u.%u ...\n",
		   compiled.major, compiled.minor, compiled.patch);
	SDL_Log("and linking against SDL version %u.%u.%u.\n",
		   linked.major, linked.minor, linked.patch);


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

	mainWindow = SDL_CreateWindow("SDL2_GUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

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
	TTF_Font * arial = TTF_OpenFont(FONT_LOCATION, 24);
	if (arial == nullptr)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
		SDL_DestroyWindow(mainWindow);
		SDL_DestroyRenderer(sdlRenderer);
		exit(-1);
	}


	/***********************************
	*                Load Images
	***********************************/

	SDL_Texture * backgroundImage = loadImage("../resources/sample_bg_image.jpg", sdlRenderer);


	// Using a skin texture
	SDL_Texture * skinTexture = loadImage("../resources/image_sheet.jpg", sdlRenderer);

	/***********************************
	*                Load Images
	***********************************/
	/*
	* SDL2_GUI code
	*/

	/* Creating some basic color to our components */
	SDL_Color bg      { 255, 255,   0, 255 };
	SDL_Color c_red   { 255,   0,   0, 255 };
	SDL_Color c_green { 0,   255,   0, 255 };
	SDL_Color c_blue  { 0,     0, 255, 255 };
	SDL_Color c_black { 0,     0,   0, 255 };
	SDL_Color c_white { 255, 255, 255, 255 };
	SDL_Color border  { 255,   0, 255, 255 };


	SDL_Color c_transparent_green { 0,   255,   0, 255 };
	SDL_Color bg_solid_white { 255, 255, 255, 255 };
	SDL_Color bg_transparent_white { 255, 255, 255, 100 };

	/* Main SDL2_GUI object. All components will be childs of GUIManager */
	GUIManager manager;

	int rendererW, rendererH;
	SDL_GetRendererOutputSize(sdlRenderer, &rendererW, &rendererH);

	GUIPanel * mainPanel = new GUIPanel(0, 0, rendererW, rendererH);
	mainPanel->setOpaque(true);
	mainPanel->setBackgroundImage(backgroundImage);

	// Pannel to organize layout
	GUIPanel * subPanel = new GUIPanel(0, 85, 200, 50);
	subPanel->setOpaque(true);
	subPanel->setBackgroundColor(c_red);
	subPanel->setDrawBgColor(true);

	GUILabel * testLabel1 = new GUILabel(400, 25, 450, 25, "Simple Ui Label", arial, false);
	testLabel1->setLabelColor(c_white);
	testLabel1->setDrawBgColor(false);
	testLabel1->setBorderColor(c_white);
	testLabel1->setAction([] {std::cout << "Clicked in Label" << std::endl; });

	GUIButton * button1 = new GUIButton(10, 10, 50, 50, "", arial, false);
	button1->setClickedColor(c_green);
	button1->setBackgroundColor(c_blue);
	button1->setBackgroundImage(skinTexture);
	button1->setBackgroundImageRect(106, 143, 60, 60);
	button1->setClickedImage(skinTexture);
	button1->setClickedImageRect(180,143,60,60);
	button1->setBorderColor(border);
	//set button action
	button1->setAction([&] {std::cout << "Btn4 Clicked" << std::endl; });

	GUITextField * textField = new GUITextField(320, 550, 180, 56, "Edit me!", arial, false);

	textField->setIsPassword(false);
	textField->setAction([&] {
		std::cout << "Iniciando a digitacao do texto" << std::endl;
		manager.setActiveInputTextComponent(textField);
	});
	textField->setReturnPressedAction([&] {
		std::cout << "Texto Digitado: " << textField->getText() << std::endl;
	});
	//textField->setBackgroundColor(c_white);
	textField->setDrawBgColor(true);
	textField->setBackgroundColor(c_black);
	textField->setPadding(37, 37, 20, 5);
	textField->setLabelColor(c_white);
	textField->setBackgroundImage(skinTexture);
	textField->setBackgroundImageRect(330, 201, 180, 56);
	textField->setBackgroundImageEditing(skinTexture);
	textField->setBackgroundImageEditingRect(330, 201, 180, 56);
	textField->setMaxTextLength(10);

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
	GUITextArea *textArea = new GUITextArea(0, 0, 800, 600, arial);
	textArea->setOpaque(false);
	textArea->setPadding(0, 15, 0, 0);
	textArea->setText("Neste sentido, o entendimento das metas propostas maximiza as possibilidades por conta das formas de ação. A prática cotidiana prova que a crescente influência da mídia auxilia a preparação e a composição do sistema de participação geral. No entanto, não podemos esquecer que a consolidação das estruturas auxilia a preparação e a composição do processo de comunicação como um todo. Neste sentido, o entendimento das metas propostas maximiza as possibilidades por conta das formas de ação. A prática cotidiana prova que a crescente influência da mídia auxilia a preparação e a composição do sistema de participação geral. No entanto, não podemos esquecer que a consolidação das estruturas auxilia a preparação e a composição do processo de comunicação como um todo. Neste sentido, o entendimento das metas propostas maximiza as possibilidades por conta das formas de ação. A prática cotidiana prova que a crescente influência da mídia auxilia a preparação e a composição do sistema de participação geral. No entanto, não podemos esquecer que a consolidação das estruturas auxilia a preparação e a composição do processo de comunicação como um todo. Neste sentido, o entendimento das metas propostas maximiza as possibilidades por conta das formas de ação. A prática cotidiana prova que a crescente influência da mídia auxilia a preparação e a composição do sistema de participação geral. No entanto, não podemos esquecer que a consolidação das estruturas auxilia a preparação e a composição do processo de comunicação como um todo. Neste sentido, o entendimento das metas propostas maximiza as possibilidades por conta das formas de ação. A prática cotidiana prova que a crescente influência da mídia auxilia a preparação e a composição do sistema de participação geral. No entanto, não podemos esquecer que a consolidação das estruturas auxilia a preparação e a composição do processo de comunicação como um todo.");
	textArea->setTextColor(c_green);
	textArea->setBackgroundColor(bg_transparent_white);
	textArea->setDrawBgColor(false);


	/*
		Scrollpanel
	*/
	GUIScrollPanel * scrollPannel = new GUIScrollPanel(164, 200, 800, 200, arial);
	scrollPannel->setYPace(21);
	scrollPannel->addComponent(textArea);
	scrollPannel->setDrawBgColor(false);
	//scrollPannel->addComponent(textField);
	// Add fields to layout

	mainPanel->addComponent(testLabel1);
	mainPanel->addComponent(subPanel);
	subPanel->addComponent(button1);



	mainPanel->addComponent(scrollbar);
	mainPanel->addComponent(spinner);

	mainPanel->addComponent(scrollPannel);


	manager.addComponent(mainPanel);
	manager.addComponent(textField);
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
	SDL_DestroyTexture(skinTexture);

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
