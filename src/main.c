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

int couleurAleatoire()
{
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    return (r << 16) | (g << 8) | b;
}

void initSpheres(Sphere* listSphere, int nombre)
{
    for (int i = 0; i < nombre; i++)
    {
        listSphere[i].centreX = rand() % LARGEUR;
        listSphere[i].centreY = rand() % HAUTEUR;
        listSphere[i].numeroCase = (int) (listSphere[i].centreX / TAILLE_CASE) + (int) (listSphere[i].centreY / TAILLE_CASE) * (LARGEUR / TAILLE_CASE);
        listSphere[i].rayon = rand() % MAX_RAYON + 1;
        listSphere[i].vX = (rand() % 100 - 50); // Vitesse entre -50 et 50
        listSphere[i].vY = (rand() % 100 - 50); // Vitesse entre -50 et 50
        listSphere[i].couleur = couleurAleatoire();
        listSphere[i].n = 0;
    }
}

int main()
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* mainWindow = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR, HAUTEUR, 0);
    SDL_Surface* mainSurface = SDL_GetWindowSurface(mainWindow);
    SDL_Rect cleanWindow = (SDL_Rect) {0,0, LARGEUR, HAUTEUR};

    if(mainWindow == NULL)
    {
        perror("Problème lors de la création de la fenêtre \n");
        exit(EXIT_FAILURE);
    }

    Sphere* listSphere = malloc(NOMBRE_BALLE * sizeof(Sphere));
    initSpheres(listSphere, NOMBRE_BALLE);
    SDL_Event event;
    bool continueSimulation = true;
    while(continueSimulation)
    {
        for (int i = 0; i < NOMBRE_BALLE; i++)
        {
            dessineSphere(mainSurface, listSphere[i]);
        }

        SDL_UpdateWindowSurface(mainWindow);

        for (int i = 0; i < NOMBRE_BALLE; i++)
        {
            deplaceBalle(&listSphere[i]);
        }
        gereAllCollision(listSphere, NOMBRE_BALLE);
        SDL_FillRect(mainSurface, &cleanWindow, COULEUR_FOND);

        while(SDL_PollEvent(&event))
        {
            gererUser(event);
        }
        SDL_Delay(20);
    }

    printf("\n");
    free(listSphere);
    SDL_DestroyWindow(mainWindow);
    return EXIT_SUCCESS;
}