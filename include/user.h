#ifndef USER_H
#define USER_H
#include <SDL2/SDL.h>
#include "myBubble.h"

void gererUser(SDL_Event event, Delai* delai, Sphere** listSphere, int* nombre);

void gestionTouche(int numeroTouche, Delai* delai, Sphere** listSphere, int* nombre);

#endif
