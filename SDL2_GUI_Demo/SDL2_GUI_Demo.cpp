// Component Showcase and demo application for SDL2_GUI lib.

//
#include <iostream>

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#elif defined _WIN32 || _WIN64
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif


#define RESOURCES_PATH "../resources"
#define FONT_PATH "../resources/fonts/"


#define FONTS_FIRA_CODE FONT_PATH "FiraCodeNerdFont-Regular.ttf"
#define FONTS_FIRA_CODE_BOLD FONT_PATH "FiraCodeNerdFont-Bold.ttf"
#define FONTS_FIRA_CODE_LIGHT FONT_PATH "FiraCodeNerdFont-Light.ttf"

#include "SDL2_GUI_Demo.h"

#define WINDOW_WIDTH 1920/2
#define WINDOW_HEIGHT 1080/2


void checkSDLError(int);
void keyPressed(SDL_Event keyEvent);
void mousePressed(SDL_Event mouseEvent);
void keyReleased(SDL_Event keyEvent);
void mouseReleased(SDL_Event mouseEvent);
void draw(SDL_Renderer *renderer);


SDL_Texture *loadImage(const char *path, SDL_Renderer *renderer)
{
    SDL_Surface *loadingSurface = IMG_Load(path);
    if (!loadingSurface)
    {
        std::cout << "Error loading textfield BG image " << IMG_GetError() << std::endl;
    }
    SDL_Texture *loadedTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);

    SDL_FreeSurface(loadingSurface);

    return loadedTexture;
}


int main(int argc, char *argv[])
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

    if (IMG_Init(IMG_INIT_JPG) != static_cast<int>(IMG_INIT_JPG))
    {
        std::cout << "Unable to init Image Library: " << IMG_GetError() << std::endl;
    }

    SDL_Window *mainWindow = SDL_CreateWindow("SDL2_GUI SAMPLE APP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                              WINDOW_WIDTH,
                                              WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (mainWindow == nullptr)
    {
        std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        exit(-1);
    }

    SDL_Renderer *sdlRenderer =
            SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (sdlRenderer == nullptr)
    {
        std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(mainWindow);
        exit(-1);
    }
    /* Set the render to draw transparency*/
    SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);


    /* Loading default font - Fira Code Regular */
    TTF_Font *font_FiraCode = TTF_OpenFont(FONTS_FIRA_CODE, 24);
    if (font_FiraCode == nullptr)
    {
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        SDL_DestroyWindow(mainWindow);
        SDL_DestroyRenderer(sdlRenderer);
        exit(-1);
    }


    /***********************************
    *                Load Images
    ***********************************/
    SDL_Texture *backgroundImage = loadImage("../resources/sample_bg_image2.jpg", sdlRenderer);


    // Using a skin texture
    SDL_Texture *skinTexture = loadImage("../resources/image_sheet.jpg", sdlRenderer);

    /***********************************
    *                Load Images
    ***********************************/
    /*
    * SDL2_GUI code
    */

    /* Creating some basic color to our components */
    constexpr SDL_Color c_solid_red{255, 0, 0, 255};
    constexpr SDL_Color c_solid_green{0, 255, 0, 255};
    constexpr SDL_Color c_solid_blue{0, 0, 255, 255};
    constexpr SDL_Color c_solid_black{0, 0, 0, 255};
    constexpr SDL_Color c_solid_white{255, 255, 255, 255};
    constexpr SDL_Color c_solid_border{255, 0, 255, 255};
    constexpr SDL_Color c_transparent_red{255, 0, 0, 124};
    constexpr SDL_Color c_transparent_green{0, 0, 255, 124};
    constexpr SDL_Color c_transparent_blue{0, 255, 0, 124};
    constexpr SDL_Color c_transparent_white{255, 255, 255, 124};
    constexpr SDL_Color c_transparent_black{0, 0, 0, 100};

    /* Main SDL2_GUI object. All components will be children of GUIManager */
    GUIManager manager;

    int rendererW, rendererH;
    SDL_GetRendererOutputSize(sdlRenderer, &rendererW, &rendererH);

    GUIPanel *mainPanel = new GUIPanel(0, 0, rendererW, rendererH);
    mainPanel->setOpaque(true);
    mainPanel->setBackgroundImage(backgroundImage);

    GUILabel *titleLabel = new GUILabel(400, 25, 450, 25, "Simple Ui Label", font_FiraCode, false);
    titleLabel->setLabelColor(c_solid_white);
    titleLabel->setDrawBgColor(false);
    titleLabel->setBorderColor(c_solid_white);
    titleLabel->setAction([] { std::cout << "Clicked in Label" << std::endl; });
    mainPanel->addComponent(titleLabel);

    // Panel to organize layout
    GUIPanel *subPanel = new GUIPanel(0, 85, 200, 50);
    subPanel->setOpaque(true);
    subPanel->setBackgroundColor(c_solid_red);
    subPanel->setDrawBgColor(true);

    mainPanel->addComponent(subPanel);

    /* Spinner  */
    GUISpinner *spinner = new GUISpinner(60, 5, 60, 30, font_FiraCode, -10000, 10000);
    spinner->setNotifyEditingListener([&](GUITextField *textField) {
        manager.setActiveInputTextComponent(textField);
    });


    GUIButton *clickableButton = new GUIButton(0, 0, 50, 50, " =>", font_FiraCode, false);
    clickableButton->setClickedColor(c_solid_green);
    clickableButton->setBackgroundColor(c_solid_blue);
    clickableButton->setBackgroundImage(skinTexture);
    clickableButton->setBackgroundImageRect(106, 143, 60, 60);
    clickableButton->setClickedImage(skinTexture);
    clickableButton->setClickedImageRect(177, 142, 60, 60);
    //set button action
    clickableButton->setAction([&] { std::cout << "Clickable Button Clicked" << std::endl; spinner->setCurrentValue(0); });
    subPanel->addComponent(clickableButton);

    subPanel->addComponent(spinner);


    GUITextField *textField = new GUITextField(150, 450, 180, 56, "Edit me!", font_FiraCode, false);
    textField->setIsPassword(false);
    textField->setAction([&] {
        std::cout << "Starting text editing" << std::endl;
        manager.setActiveInputTextComponent(textField);
    });
    textField->setReturnPressedAction([&] {
        std::cout << "Input text: " << textField->getText() << std::endl;
    });
    textField->setDrawBgColor(true);
    textField->setBackgroundColor(c_solid_black);
    textField->setPadding(37, 37, 20, 5);
    textField->setLabelColor(c_solid_white);
    textField->setBackgroundImage(skinTexture);
    textField->setBackgroundImageRect(330, 201, 180, 56);
    textField->setBackgroundImageEditing(skinTexture);
    textField->setBackgroundImageEditingRect(330, 201, 180, 56);
    textField->setMaxTextLength(10);

    /*
    TextArea -> will be put inside a scroll panel.
    */
    GUITextArea *textArea = new GUITextArea(0, 0, 800, 600, font_FiraCode);
    textArea->setOpaque(false);
    textArea->setPadding(0, 15, 0, 0);
    textArea->setText(
        "Neste sentido, o entendimento das metas propostas maximiza as possibilidades por conta das formas de ação. A prática cotidiana prova que a crescente influência da mídia auxilia a preparação e a composição do sistema de participação geral. No entanto, não podemos esquecer que a consolidação das estruturas auxilia a preparação e a composição do processo de comunicação como um todo. Neste sentido, o entendimento das metas propostas maximiza as possibilidades por conta das formas de ação. A prática cotidiana prova que a crescente influência da mídia auxilia a preparação e a composição do sistema de participação geral. No entanto, não podemos esquecer que a consolidação das estruturas auxilia a preparação e a composição do processo de comunicação como um todo. Neste sentido, o entendimento das metas propostas maximiza as possibilidades por conta das formas de ação. A prática cotidiana prova que a crescente influência da mídia auxilia a preparação e a composição do sistema de participação geral. No entanto, não podemos esquecer que a consolidação das estruturas auxilia a preparação e a composição do processo de comunicação como um todo. Neste sentido, o entendimento das metas propostas maximiza as possibilidades por conta das formas de ação. A prática cotidiana prova que a crescente influência da mídia auxilia a preparação e a composição do sistema de participação geral. No entanto, não podemos esquecer que a consolidação das estruturas auxilia a preparação e a composição do processo de comunicação como um todo. Neste sentido, o entendimento das metas propostas maximiza as possibilidades por conta das formas de ação. A prática cotidiana prova que a crescente influência da mídia auxilia a preparação e a composição do sistema de participação geral. No entanto, não podemos esquecer que a consolidação das estruturas auxilia a preparação e a composição do processo de comunicação como um todo.");
    textArea->setTextColor(c_solid_green);
    textArea->setBackgroundColor(c_transparent_black);
    textArea->setDrawBgColor(false);


    /* Scroll panel */
    GUIScrollPanel *scrollPanel = new GUIScrollPanel(25, 200, (WINDOW_WIDTH)-50, 200, font_FiraCode);
    scrollPanel->setYPace(21);
    scrollPanel->addComponent(textArea);
    scrollPanel->setDrawBgColor(false);


    mainPanel->addComponent(scrollPanel);
    mainPanel->addComponent(textField);

    manager.addComponent(mainPanel);





    // FIXME: Find a more efficient way of dealing with this textInput (maybe only when clicking a component)
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
                            << " length:" << sdlEvent.edit.length << " } " << std::endl;

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
    SDL_StopTextInput();

    // Deallocate components
    manager.destroy();

    SDL_DestroyTexture(backgroundImage);
    SDL_DestroyTexture(skinTexture);

    IMG_Quit();

    TTF_CloseFont(font_FiraCode);
    TTF_Quit();

    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(mainWindow);

    std::cout << "System shutdown gracefully" << std::endl;

    SDL_Quit();



    return 0;
}


void keyPressed(SDL_Event keyEvent)
{
}

void mousePressed(SDL_Event mouseEvent)
{
}

void keyReleased(SDL_Event keyEvent)
{
}

void mouseReleased(SDL_Event mouseEvent)
{
}

void checkSDLError(int line = -1)
{
#ifndef NDEBUG
    const char *error = SDL_GetError();
    if (*error != '\0')
    {
        printf("SDL Error: %s\n", error);
        if (line != -1)
        {
            printf(" + line: %i\n", line);
        }
        SDL_ClearError();
    }
#endif
}
