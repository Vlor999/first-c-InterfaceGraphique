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
    listSphere[nombre].centreX = x;
    listSphere[nombre].centreY = y;
    listSphere[nombre].numeroCase = (int) (listSphere[nombre].centreX / TAILLE_CASE) + (int) (listSphere[nombre].centreY / TAILLE_CASE) * (LARGEUR / TAILLE_CASE);
    listSphere[nombre].rayon = rand() % MAX_RAYON + 1;
    listSphere[nombre].vX = (rand() % 100 - 50); // Vitesse entre -50 et 50
    listSphere[nombre].vY = (rand() % 100 - 50); // Vitesse entre -50 et 50
    listSphere[nombre].couleur = couleurAleatoire();
    listSphere[nombre].n = 0;
}

void initNewSphere(Sphere* listSphere, int nombre)
{
    listSphere[nombre].centreX = rand() % LARGEUR;
    listSphere[nombre].centreY = rand() % HAUTEUR;
    listSphere[nombre].numeroCase = (int) (listSphere[nombre].centreX / TAILLE_CASE) + (int) (listSphere[nombre].centreY / TAILLE_CASE) * (LARGEUR / TAILLE_CASE);
    listSphere[nombre].rayon = rand() % MAX_RAYON + 1;
    listSphere[nombre].vX = (rand() % 100 - 50); // Vitesse entre -50 et 50
    listSphere[nombre].vY = (rand() % 100 - 50); // Vitesse entre -50 et 50
    listSphere[nombre].couleur = couleurAleatoire();
    listSphere[nombre].n = 0;
}

void initSpheres(Sphere* listSphere, int nombre)
{
    for (int i = 0; i < nombre; i++)
    {
        initNewSphere(listSphere, i);
    }
}
