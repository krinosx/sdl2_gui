========================================================================
    SDL_GUI 
========================================================================

This project will build an simple framework to be used with SDL2. The main 
purpose is to provide simple GUI functionalities like Buttons, Labels, 
Pannels, TextAreas to be used with SDL applications.

Motivation: 
	The initial motivation emerge from the lack of native libraries that 
	support such components with SDL. Various alternatives are available
	in the market/open source community like GTK, QT and others, but all
	this frameworks add so much complexity and have so much features that
	a simple project will not use.

Goals:
	The main gola is to provide a simple to learn and easy to integrate 
	framework to SDL projects. The basic workflow to use the SDL_GUI will
	be ass simple as (not the extra steps marked with *, all the other 
	stuff is basic from general SDL applications):

	------------- PSEUDOCODE ----------------------------------
	
	- INIT SDL LIBRARIES
	- CREATE YOUR RENDER
	(...)
	  Initialize and load your project stuff
	(...)

	* CREATE GUI MANAGER
	* CREATE GUI COMPONENTS
	* ADD GUI COMPONENTS TO THE MANAGER

	
	- START APPLICATION LOOP 
		- START SDL EVENT LOOP
			* Notify manager with desired events

		- Draw your project stuff
		* Draw manager -> ( GUIManager.draw(renderer) )
	
	- END Application loop

	* DESTROY MANAGER
	- DESTROY YOUR PROJECT STUFF

	- FINALIZE SDL
	------------- PSEUDOCODE END  ----------------------------




*****************
***** TODO  *****
*****************


FIX and IMPROVE
	- Implement scrollbars
		- Implement use of Images to replace button graphics in scrollbar
		- Implement a 'button' to indicate visually the scrollbar position

	+ Implement TextArea component - 
			- Implement support for a scrollable text, maybe a new component?
			- It may be a subclass of scrollpanel one.

NEW FEATURES
	- Implement Scroll Panels (a panel with scrollbars)


*****************
***** DONE  *****
*****************
05/06/2017
	- Implement TextArea component ( to show long texts ) - 
		* Implemented a first version of a textarea based on GUIPanel. This component support long text rendering
		  with automatic line break, it has a padding attributes and show an text "(...)" when text overflows its
		  defined height.

	- Improvements: Added a attribute to show/hide components. If the component is set to hide it will no longer 
		receive click events events or be draw.

03/06/2017
	* Implemented GUISpinner component
		- It combines a GUIScrollbar + GUITextField + GUIPannel to create a spinner component.
		- It was used to test reusability of scrollbar + textfield
		-it accepts negative values

	* Modified textField component to accept regex filter and validate input characters.


02/06/2017
  + Implement scrollbars
		- Implemented a simple and fuction version of scrollbars.
			* It has the option to set alignment (VERTICAL/HORIZONTAL)
			* It check the boundaries about min and max values
			* Its possible to add 2 callback functions to be notified when an increment or decrement occurs

01/06/2017
	+ Implement the BLEND mode while creating surfaces for text in Labels/Buttons/etc
		* implemented blend mode for text and background color in all components based in Label
		* Implemented blend for background image for all GUIComponents ( add a new function void setBackgroundImage(SDL_Texture* backgroundImage, Uint8 alpha); )

	+ Implement TextField component ( to enable input text )
		* Implemented a GUITextField component. It is able to receive simple text input, render backgroud images/borders/backgroud color.
		* It implements 2 states (GUIComponentState::base and GUIComponentState::editing) -> Each state has its own graphic configuration (diferente colors, bgImages, borders)
		* It have a seccond action triggered when return is pressed ( GUITextField::returnPressedAction)
		* New event handling implemented in GUIManager in order to deal with text editing features. At this moment only one component must edit text each time (there is need for more than one?)
  
  + Improved functionalities in GUIButton
		* Now GUIButton have the option to render background images (one for each state).
  
  + Modified some function calls to make it more reusable in GUIComponent, GUILabel


  