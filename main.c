#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "myBubble.h"


void gereCollision(Sphere* c1, struct Sphere* c2) {
    double dx = c2->centreX - c1->centreX;
    double dy = c2->centreY - c1->centreY;
    double dist = dx * dx + dy * dy;
    double rayonSum = c1->rayon + c2->rayon;
    
    if (dist < rayonSum * rayonSum) 
    {
        dist = sqrt(dist);

        double nx = dx / dist;
        double ny = dy / dist;

        double v1 = c1->vX * nx + c1->vY * ny;
        double v2 = c2->vX * nx + c2->vY * ny;

        double m1 = 4 * PI * c1->rayon * c1->rayon * c1->rayon / 4;  // Masse correspond au volume (Sphère) : Masse Volumique : 1
        double m2 = 4 * PI * c2->rayon * c2->rayon * c2->rayon / 4;

        double v1_final = ((m1 - m2) * v1 + 2 * m2 * v2) / (m1 + m2);
        double v2_final = ((m2 - m1) * v2 + 2 * m1 * v1) / (m1 + m2);

        c1->vX += AMORTISSEMENT * (v1_final - v1) * nx;
        c1->vY += AMORTISSEMENT * (v1_final - v1) * ny;

        c2->vX += (v2_final - v2) * nx;
        c2->vY += (v2_final - v2) * ny;

        double overlap = rayonSum - dist;
        c1->centreX -= nx * overlap * 0.5;
        c1->centreY -= ny * overlap * 0.5;
        
        c2->centreX += nx * overlap * 0.5;
        c2->centreY += ny * overlap * 0.5;
    }
}


void drawCirclePoints(SDL_Surface* surface, int cx, int cy, int x, int y, Uint32 couleur) 
{
    SDL_Rect pixel;

    pixel = (SDL_Rect){cx + x, cy + y, 1, 1}; SDL_FillRect(surface, &pixel, couleur);
    pixel = (SDL_Rect){cx - x, cy + y, 1, 1}; SDL_FillRect(surface, &pixel, couleur);
    pixel = (SDL_Rect){cx + x, cy - y, 1, 1}; SDL_FillRect(surface, &pixel, couleur);
    pixel = (SDL_Rect){cx - x, cy - y, 1, 1}; SDL_FillRect(surface, &pixel, couleur);
    pixel = (SDL_Rect){cx + y, cy + x, 1, 1}; SDL_FillRect(surface, &pixel, couleur);
    pixel = (SDL_Rect){cx - y, cy + x, 1, 1}; SDL_FillRect(surface, &pixel, couleur);
    pixel = (SDL_Rect){cx + y, cy - x, 1, 1}; SDL_FillRect(surface, &pixel, couleur);
    pixel = (SDL_Rect){cx - y, cy - x, 1, 1}; SDL_FillRect(surface, &pixel, couleur);
}

void dessineSphere(SDL_Surface* currentSurface, Sphere sphere)
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
        if (d > 0) {
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

void deplaceBalle(Sphere* Sphere)
{
    Sphere->vY += PESANTEUR * TIMESTEP;

    Sphere->centreX += Sphere->vX * TIMESTEP;
    Sphere->centreY += Sphere->vY * TIMESTEP;

    if (Sphere->centreX - Sphere->rayon < 0)
    {
        Sphere->centreX = Sphere->rayon;
        Sphere->vX = -Sphere->vX * AMORTISSEMENT;
    }
    if (Sphere->centreX + Sphere->rayon > LARGEUR)
    {
        Sphere->centreX = LARGEUR - Sphere->rayon;
        Sphere->vX = -Sphere->vX * AMORTISSEMENT;
    }
    if (Sphere->centreY - Sphere->rayon < 0)
    {
        Sphere->centreY = Sphere->rayon;
        Sphere->vY = -Sphere->vY * AMORTISSEMENT;
    }
    if (Sphere->centreY + Sphere->rayon > HAUTEUR)
    {
        Sphere->centreY = HAUTEUR - Sphere->rayon;
        Sphere->vY = -Sphere->vY * AMORTISSEMENT;
    }
    Sphere->numeroCase = (int) (Sphere->centreX / TAILLE_CASE) + (int) (Sphere->centreY / TAILLE_CASE) * (LARGEUR / TAILLE_CASE);
    Sphere->n++; // Incrément du compteur de déplacement
}

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

bool compareSphereCase(Sphere c1, Sphere c2)
{
    int diff = abs(c1.numeroCase - c2.numeroCase);
    if (diff == 0 || diff == 1 || diff == LARGEUR / TAILLE_CASE || abs(diff  - (LARGEUR / TAILLE_CASE)) == 1)
    {
        return true;
    }
    return false;
}

void gereAllCollision(Sphere* listSphere, int nombre)
{
    int compte = 0;
    for (int i = 0; i < nombre; i++) 
    {
        for (int j = i + 1; j < nombre; j++) 
        {
            if(i != j && compareSphereCase(listSphere[i], listSphere[j]))
            {
                gereCollision(&listSphere[i], &listSphere[j]);
            }
            else
            {
                compte++;
            }
        }
    }

    printf("\rPourcentage de collision évitées : %.2f%%", (float)compte/(nombre*(nombre - 1)/2) * 100);
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
            if(event.type == SDL_QUIT)
            {
                continueSimulation = false;
            }
        }
        SDL_Delay(20);
    }

    printf("\n");
    free(listSphere);
    SDL_DestroyWindow(mainWindow);
    return EXIT_SUCCESS;
}