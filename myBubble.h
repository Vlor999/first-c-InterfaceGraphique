#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME "First Graphical Interface"
#define LARGEUR 800
#define HAUTEUR 800
#define PROFONDEUR 800
#define COULEUR_FOND  0x0000000
#define PESANTEUR 9.81 
#define TIMESTEP 0.1
#define PI 3.1415
#define AMORTISSEMENT 0.97
#define MAX_RAYON 5
#define TAILLE_CASE MAX_RAYON

#define NOMBRE_BALLE 1000

typedef struct Sphere
{
    double centreX;
    double centreY;
    double rayon;
    double vX;
    double vY;
    int numeroCase;
    int couleur;
    int n;
}Sphere;


