#include "gameWindow.h"

int initWindow(void)
{
    // This function attempts initialise SDL then set up the window and renderer
    // if all is successful it will return 0, 
    // if something fails it calls cleanup then returns 1 to the caller 


    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("failed to initialise SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    // Try to create the window and clean up if it fails
    if ( !(window = SDL_CreateWindow("Hello Window!",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     640,
                                     480,
                                     SDL_WINDOW_OPENGL))) {
        printf("Could not create window: %s\n0", SDL_GetError());
        destroyWindow();
        return 1;
    };

    // create the GL context with our sdl window
    if ( !(glcontext = SDL_GL_CreateContext(window)))
    {
        printf("failed to create GL context %s\n", SDL_GetError());
        destroyWindow();
        return 1;
    }

    if ( gl3wInit()) {
        fprintf(stderr, "failed to initialize OpenGL\n");
        destroyWindow();
        return 1;
    }
    printf("initialisation process complete\n");
    return 0;
}

int destroyWindow(void)
{
    if (glcontext) SDL_GL_DeleteContext(glcontext);
    if (window) SDL_DestroyWindow(window);
    if (renderer) SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}