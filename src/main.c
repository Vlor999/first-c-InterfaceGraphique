/***************************
 *                         *
 * Sous Licence GNU/GPLv3  *
 *                         *
 ***************************/


#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "../include/myBubble.h"
#include "dessine.c"
#include "mouvement.c"
#include "user.c"
#include "sphere.c"

int main()
{
    srand(time(NULL));
    Delai* delai = malloc(sizeof(Delai));
    delai->x = 20;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* mainWindow = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR, HAUTEUR, 0);
    SDL_Surface* mainSurface = SDL_GetWindowSurface(mainWindow);
    SDL_Rect cleanWindow = (SDL_Rect) {0,0, LARGEUR, HAUTEUR};

    if(mainWindow == NULL)
    {
        perror("Problème lors de la création de la fenêtre \n");
        exit(EXIT_FAILURE);
    }

    int nombreBalle = NOMBRE_BALLE;
    Sphere* listSphere = malloc(nombreBalle * sizeof(Sphere));
    initSpheres(listSphere, nombreBalle);
    SDL_Event event;
    bool continueSimulation = true;
    while(continueSimulation)
    {
        for (int i = 0; i < nombreBalle; i++)
        {
            dessineSphere(mainSurface, listSphere[i]);
        }

        SDL_UpdateWindowSurface(mainWindow);

        for (int i = 0; i < nombreBalle; i++)
        {
            deplaceBalle(&listSphere[i]);
        }
        gereAllCollision(listSphere, nombreBalle);
        SDL_FillRect(mainSurface, &cleanWindow, COULEUR_FOND);

        while(SDL_PollEvent(&event))
        {
            gererUser(event, delai, &listSphere, &nombreBalle);
        }
        printf("Nombre de balles : %5d -- ", nombreBalle);

        SDL_Delay(delai->x);
    }

    printf("\n");
    free(listSphere);
    SDL_DestroyWindow(mainWindow);
    return EXIT_SUCCESS;
}