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
	
	if (IMG_Init(IMG_INIT_JPG) != (int) IMG_INIT_JPG ) {
		std::cout << "Unable to init Image Library: " << IMG_GetError() << std::endl;
	}

	mainWindow = SDL_CreateWindow("SDL2_GUI", 10, 10, 800, 600, SDL_WINDOW_SHOWN);

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


	/* Load Images*/
	SDL_Surface *backgroundSurface = nullptr;
	backgroundSurface = IMG_Load("E:\\Projetos\\assets\\map2.jpg");
	if (!backgroundSurface)
	{
		std::cout << "IMG_Load error - Error loading map2.jpg : " << IMG_GetError() << std::endl;
	}

	SDL_Texture* backgroundImage = SDL_CreateTextureFromSurface(sdlRenderer, backgroundSurface);

	SDL_FreeSurface(backgroundSurface);
	/*
	* SDL2_GUI code
	*/

	

	/* Creating some basic color to our components */
	SDL_Color bg{ 255, 255, 0, 125 };
	SDL_Color c_red{ 255, 0, 0, 125 };
	SDL_Color c_green{ 0, 255, 0, 125 };
	SDL_Color c_blue{ 0, 0, 255, 125 };
	SDL_Color border{ 255, 0, 255, 125 };
	
	/* Main SDL2_GUI object. All components will be childs of GUIManager */
	GUIManager manager;


	GUIPanel * mainPanel = new GUIPanel(100, 50, 500, 500);
	mainPanel->setOpaque(true);
	//mainPanel->setBackgroundColor(bg);
	mainPanel->setBackgroundImage(backgroundImage, 200);
	


	GUIPanel * subPanel = new GUIPanel(10, 200, 400, 200);
	subPanel->setOpaque(true);
	subPanel->setBackgroundColor(c_blue);

	GUILabel * testButton1 = new GUILabel(5 ,5, 200, 50, "My Button", arial,false);
	testButton1->setPadding(30, 30, 10, 10);
	testButton1->setBackgroundColor(c_red);
	testButton1->setBorderColor(border);
	testButton1->setAction([]{std::cout << "Label lambdas" << std::endl; });
	
	
	GUIButton * testButton3 = new GUIButton(20, 60, 200, 50, "Click and hold.", arial, false);
	testButton3->setClickedColor(c_green);
	testButton3->setBackgroundColor(c_blue);
	testButton3->setBorderColor(border);
	//set button action
	testButton3->setAction([&]{std::cout << "My lambda expression" << std::endl; });

	GUIButton * testButton4 = new GUIButton(10, 1, 200, 50, "BTN SUBPANEL.", arial, false);
	testButton4->setClickedColor(c_green);
	testButton4->setBackgroundColor(c_blue);
	testButton4->setBorderColor(border);
	//set button action
	testButton4->setAction([&]{std::cout << "Btn4 Clicked" << std::endl; });

	mainPanel->addComponent(testButton1);
	mainPanel->addComponent(testButton3);
	
	
	mainPanel->addComponent(subPanel);
	subPanel->addComponent(testButton4);

	manager.addComponent(mainPanel);


	
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
		
		SDL_RenderPresent(sdlRenderer);

	}


	//delete(testButton1);
	//delete(testButton3);
	manager.destroy();

	IMG_Quit();

	TTF_CloseFont(arial);
	TTF_Quit();

	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
	
	std::cout << "System shutdown gracefully" << std::endl;

	
	return 0;
}


void keyPressed(SDL_Event keyEvent){}
void mousePressed(SDL_Event mouseEvent){}
void keyReleased(SDL_Event keyEvent){}
void mouseReleased(SDL_Event mouseEvent){


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