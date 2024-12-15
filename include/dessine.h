#ifndef _DESSINE_H
#define _DESSINE_H
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "myBubble.h"

void drawCirclePoints(SDL_Surface *surface, int cx, int cy, int x, int y, Uint32 couleur);

void dessineSphere(SDL_Surface *currentSurface, Sphere sphere);

#endif
