#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define NAME "First Graphical Interface"
#define LARGEUR 900
#define HAUTEUR 500
#define COULEUR_FOND  0x00000000
#define PESANTEUR 9.81 
#define TIMESTEP 0.1
#define PI 3.1415
#define AMORTISSEMENT 0.95

#define NOMBRE_BALLE 5

struct Cercle
{
    double centreX;
    double centreY;
    double rayon;
    double vX;
    double vY;
    int couleur;
    int n;
};

// Gestion de la collision entre deux cercles
void gereCollision(struct Cercle* c1, struct Cercle* c2) {
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



void dessineCercle(SDL_Surface* currentSurface, struct Cercle cercle)
{
    double positionX = cercle.centreX;
    double positionY = cercle.centreY;
    double rayon = cercle.rayon;

    double distanceMax = rayon * rayon;

    double minX = positionX - rayon;
    double minY = positionY - rayon;
    double maxX = positionX + rayon;
    double maxY = positionY + rayon;

    for(double x = minX - 1; x <= maxX; x++)
    {
        for(double y = minY - 1; y <= maxY; y++)
        {
            double distance = (x - positionX) * (x - positionX) + (y - positionY) * (y - positionY);

            if (distance < distanceMax)
            {
                SDL_Rect currentPixel = (SDL_Rect) {x,y,1,1};
                SDL_FillRect(currentSurface, &currentPixel, cercle.couleur);
            }
        }        
    }
}

void deplaceBalle(struct Cercle* cercle)
{
    cercle->vY += PESANTEUR * TIMESTEP;

    cercle->centreX += cercle->vX * TIMESTEP;
    cercle->centreY += cercle->vY * TIMESTEP;

    const float ELASTICITE = AMORTISSEMENT; // Renvoie 95% de ce qui est donné

    if (cercle->centreX - cercle->rayon < 0)
    {
        cercle->centreX = cercle->rayon;
        cercle->vX = -cercle->vX * ELASTICITE;
    }
    if (cercle->centreX + cercle->rayon > LARGEUR)
    {
        cercle->centreX = LARGEUR - cercle->rayon;
        cercle->vX = -cercle->vX * ELASTICITE;
    }
    if (cercle->centreY - cercle->rayon < 0)
    {
        cercle->centreY = cercle->rayon;
        cercle->vY = -cercle->vY * ELASTICITE;
    }
    if (cercle->centreY + cercle->rayon > HAUTEUR)
    {
        cercle->centreY = HAUTEUR - cercle->rayon;
        cercle->vY = -cercle->vY * ELASTICITE;
    }

    cercle->n++; // Incrément du compteur de déplacement
}

int couleurAleatoire()
{
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    return (r << 16) | (g << 8) | b;
}

void initCercles(struct Cercle* listCercle, int nombre)
{
    for (int i = 0; i < nombre; i++)
    {
        listCercle[i].centreX = rand() % LARGEUR;
        listCercle[i].centreY = rand() % HAUTEUR;
        listCercle[i].rayon = 10 + rand() % 40; // Rayon entre 10 et 50
        listCercle[i].vX = (rand() % 100 - 50); // Vitesse entre -50 et 50
        listCercle[i].vY = (rand() % 100 - 50); // Vitesse entre -50 et 50
        listCercle[i].couleur = couleurAleatoire();
        listCercle[i].n = 0;
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

    bool continueSimulation = true;
    // struct Cercle mainCercle = (struct Cercle) {450, 250, 50, 50, 50, 0};
    struct Cercle* listCercle = malloc(NOMBRE_BALLE * sizeof(struct Cercle));
    initCercles(listCercle, NOMBRE_BALLE);
    SDL_Event event;
    while(continueSimulation)
    {
        for (int i = 0; i < NOMBRE_BALLE; i++)
        {
            dessineCercle(mainSurface, listCercle[i]);
        }

        SDL_UpdateWindowSurface(mainWindow);

        for (int i = 0; i < NOMBRE_BALLE; i++)
        {
            deplaceBalle(&listCercle[i]);
        }

        for (int i = 0; i < NOMBRE_BALLE; i++) 
        {
            for (int j = i + 1; j < NOMBRE_BALLE; j++) 
            {
                if(i != j)
                {
                    gereCollision(&listCercle[i], &listCercle[j]);
                }
            }
        }

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

    free(listCercle);
    SDL_DestroyWindow(mainWindow);
    return EXIT_SUCCESS;
}