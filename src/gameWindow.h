#include <GL/gl3w.h>
#include <SDL2/SDL.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_GLContext glcontext;

int initWindow(void);
int destroyWindow(void);