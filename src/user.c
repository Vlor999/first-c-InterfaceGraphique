/***************************
 *                         *
 * Sous Licence GNU/GPLv3  *
 *                         *
 ***************************/

#include <SDL2/SDL.h>
#include "../include/user.h"
#include "../include/sphere.h"
#include "../include/myBubble.h"

void gererUser(SDL_Event event, Delai* delai, Sphere** listSphere, int* nombre)
{
    int numeroTouche = -1;
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
            case SDLK_SPACE:
                // Mettre en pause le jeu
                numeroTouche = 0;
                break;
            case SDLK_UP:
                // Augmenter le delai de rafraichissement : ralentir le jeu
                numeroTouche = 1;
                break;
            case SDLK_DOWN:
                // Diminuer le delai de rafraichissement : accélérer le jeu
                numeroTouche = 2;
                break;
            default:
                break;
        }
    }
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        // Ajouter une balle
        numeroTouche = 3;
    }

    gestionTouche(numeroTouche, delai, listSphere, nombre);
}

void gestionTouche(int numeroTouche, Delai* delai, Sphere** listSphere, int* nombre)
{
    switch (numeroTouche)
    {
        case 0:
            // Mettre en pause le jeu
            while(1)
            {
                SDL_Event event;
                SDL_WaitEvent(&event);
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
                {
                    break;
                }
            }
            break;
        case 1:
            // Augmenter le delai de rafraichissement : ralentir le jeu
            delai->x += 10;
            break;
        case 2:
            // Diminuer le delai de rafraichissement : accélérer le jeu
            delai->x -= 10;
            if(delai->x <= 0)
            {
                delai->x = 1;
            }
            break;
        case 3:
            // Ajouter une balle
            *nombre += 1;
            Sphere* temp = realloc(*listSphere, *nombre * sizeof(Sphere));
            if (!temp) {
                fprintf(stderr, "Erreur lors du realloc.\n");
                exit(EXIT_FAILURE);
            }
            *listSphere = temp;
            int positionX, positionY;
            SDL_GetMouseState(&positionX, &positionY);
            initNewSpherePosition(*listSphere, *nombre - 1, positionX, positionY);
            break;
        default:
            break;
    }
}