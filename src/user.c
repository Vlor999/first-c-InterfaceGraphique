/***************************
 *                         *
 * Sous Licence GNU/GPLv3  *
 *                         *
 ***************************/

#include <SDL2/SDL.h>
#include "../include/user.h"

void gererUser(SDL_Event event)
{
    if (event.type == SDL_QUIT)
    {
        exit(EXIT_SUCCESS);
    }
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            exit(EXIT_SUCCESS);
            break;

        default:
            break;
        }
    }
}