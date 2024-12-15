/***************************
 *                         *
 * Sous Licence GNU/GPLv3  *
 *                         *
 ***************************/

#include <SDL2/SDL.h>
#include <stdlib.h>
#include "../include/dessine.h"


void drawCirclePoints(SDL_Surface *surface, int cx, int cy, int x, int y, Uint32 couleur)
{
    SDL_Rect pixel;

    pixel = (SDL_Rect){cx + x, cy + y, 1, 1};
    SDL_FillRect(surface, &pixel, couleur);
    pixel = (SDL_Rect){cx - x, cy + y, 1, 1};
    SDL_FillRect(surface, &pixel, couleur);
    pixel = (SDL_Rect){cx + x, cy - y, 1, 1};
    SDL_FillRect(surface, &pixel, couleur);
    pixel = (SDL_Rect){cx - x, cy - y, 1, 1};
    SDL_FillRect(surface, &pixel, couleur);
    pixel = (SDL_Rect){cx + y, cy + x, 1, 1};
    SDL_FillRect(surface, &pixel, couleur);
    pixel = (SDL_Rect){cx - y, cy + x, 1, 1};
    SDL_FillRect(surface, &pixel, couleur);
    pixel = (SDL_Rect){cx + y, cy - x, 1, 1};
    SDL_FillRect(surface, &pixel, couleur);
    pixel = (SDL_Rect){cx - y, cy - x, 1, 1};
    SDL_FillRect(surface, &pixel, couleur);
}

void dessineSphere(SDL_Surface *currentSurface, Sphere sphere)
{
    int centreX = (int)sphere.centreX;
    int centreY = (int)sphere.centreY;
    int rayon = (int)sphere.rayon;

    int x = 0;
    int y = rayon;
    int d = 3 - 2 * rayon;

    drawCirclePoints(currentSurface, centreX, centreY, x, y, sphere.couleur);

    while (y >= x)
    {
        x++;

        // Vérifier la décision
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }

        // Dessiner les points symétriques pour le cercle
        drawCirclePoints(currentSurface, centreX, centreY, x, y, sphere.couleur);
    }
}