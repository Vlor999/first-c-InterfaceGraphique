#include <math.h>
#include "../include/sphere.h"

int couleurAleatoire()
{
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    return (r << 16) | (g << 8) | b;
}

void initNewSpherePosition(Sphere* listSphere, int nombre, int x, int y)
{
    listSphere[nombre].centre.centreX = x;
    listSphere[nombre].centre.centreY = y;
    listSphere[nombre].numeroCase = (int) (listSphere[nombre].centre.centreX / TAILLE_CASE) + (int) (listSphere[nombre].centre.centreY / TAILLE_CASE) * (LARGEUR / TAILLE_CASE);
    listSphere[nombre].rayon = rand() % MAX_RAYON + 1;
    listSphere[nombre].vitesse.vX = (rand() % 100 - 50); // Vitesse entre -50 et 50
    listSphere[nombre].vitesse.vY = (rand() % 100 - 50); // Vitesse entre -50 et 50
    listSphere[nombre].couleur = couleurAleatoire();
    listSphere[nombre].volume = (4.0 / 3.0) * PI * pow(listSphere[nombre].rayon, 3);
    listSphere[nombre].trajectoire = malloc(TAILLE_TRAJECTOIRE * sizeof(Centre));
    listSphere[nombre].n = 0;
}

void initNewSphere(Sphere* listSphere, int nombre)
{
    listSphere[nombre].centre.centreX = rand() % LARGEUR;
    listSphere[nombre].centre.centreY = rand() % HAUTEUR;
    initNewSpherePosition(listSphere, nombre, listSphere[nombre].centre.centreX, listSphere[nombre].centre.centreY);
}

void initSpheres(Sphere* listSphere, int nombre)
{
    for (int i = 0; i < nombre; i++)
    {
        initNewSphere(listSphere, i);
    }
}
