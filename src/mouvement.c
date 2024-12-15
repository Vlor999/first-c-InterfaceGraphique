/***************************
 *                         *
 * Sous Licence GNU/GPLv3  *
 *                         *
 ***************************/

#include <stdbool.h>
#include "../include/mouvement.h"

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
