// SDL2_GUI.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>
#include "SDL2_GUI.h"


#define FONT_LOCATION "C:/Windows/Fonts/Arial.ttf"

void checkSDLError(int);
void keyPressed(SDL_Event keyEvent);
void mousePressed(SDL_Event mouseEvent);
void keyReleased(SDL_Event keyEvent);
void mouseReleased(SDL_Event mouseEvent);
void draw(SDL_Renderer *renderer);


int main(int argc, char* argv[])
{
	
	bool isAppRunning = true;

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


	TTF_Font * arial = TTF_OpenFont(FONT_LOCATION, 20);
	if (arial == NULL)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
		SDL_DestroyWindow(mainWindow);
		SDL_DestroyRenderer(sdlRenderer);
		exit(-1);
	}


	SDL_Color bg{ 255, 255, 0 };

	GUIManager manager;
	GUIComponent testButton(10, 10, 300, 100);
	testButton.setBackgroundColor(bg);

	manager.addComponent(testButton);


	
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
				keyPressed(sdlEvent);
				break;
			case SDL_KEYUP:
				keyReleased(sdlEvent);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mousePressed(sdlEvent);
				break;
			case SDL_MOUSEBUTTONUP:
				mouseReleased(sdlEvent);
				break;
			default:
				break;
			}

		}

		SDL_RenderClear(sdlRenderer);
		// Draw Stuff
		manager.draw(sdlRenderer);
		//draw(sdlRenderer);
		SDL_RenderPresent(sdlRenderer);

	}

	TTF_CloseFont(arial);
	TTF_Quit();

	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
	
	std::cout << "System shutdown gracefully" << std::endl;

	
	return 0;
}


void draw(SDL_Renderer * renderer)
{

	const SDL_Rect screenBackground{ 0, 0, 800, 600 };
	
	const SDL_Rect screenDetail{ 100, 100, 400, 300 };


	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &screenBackground );
		
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &screenDetail);



}


void keyPressed(SDL_Event keyEvent){}
void mousePressed(SDL_Event mouseEvent){}
void keyReleased(SDL_Event keyEvent){}
void mouseReleased(SDL_Event mouseEvent){}

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