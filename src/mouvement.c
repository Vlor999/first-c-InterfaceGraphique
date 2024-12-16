/***************************
 *                         *
 * Sous Licence GNU/GPLv3  *
 *                         *
 ***************************/

#include <stdbool.h>
#include "../include/mouvement.h"

void gereCollision(Sphere* c1, struct Sphere* c2) {
    double dx = c2->centre.centreX - c1->centre.centreX;
    double dy = c2->centre.centreY - c1->centre.centreY;
    double dist = dx * dx + dy * dy;
    double rayonSum = c1->rayon + c2->rayon;
    
    if (dist < rayonSum * rayonSum) 
    {
        dist = sqrt(dist);

        double nx = dx / dist;
        double ny = dy / dist;

        double v1 = c1->vitesse.vX * nx + c1->vitesse.vY * ny;
        double v2 = c2->vitesse.vX * nx + c2->vitesse.vY * ny;

        double m1 = c1->volume;  // Masse correspond au volume (Sphère) : Masse Volumique : 1
        double m2 = c2->volume;

        double v1_final = ((m1 - m2) * v1 + 2 * m2 * v2) / (m1 + m2);
        double v2_final = ((m2 - m1) * v2 + 2 * m1 * v1) / (m1 + m2);

        c1->vitesse.vX += AMORTISSEMENT * (v1_final - v1) * nx;
        c1->vitesse.vY += AMORTISSEMENT * (v1_final - v1) * ny;

        c2->vitesse.vX += AMORTISSEMENT * (v2_final - v2) * nx;
        c2->vitesse.vY += AMORTISSEMENT * (v2_final - v2) * ny;

        double overlap = rayonSum - dist;
        c1->centre.centreX -= nx * overlap * 0.5;
        c1->centre.centreY -= ny * overlap * 0.5;
        
        c2->centre.centreX += nx * overlap * 0.5;
        c2->centre.centreX += ny * overlap * 0.5;

        c1->trajectoire[c1->n % TAILLE_TRAJECTOIRE] = c1->centre;
        c2->trajectoire[c2->n % TAILLE_TRAJECTOIRE] = c2->centre;
    }
}

void deplaceBalle(Sphere* Sphere)
{
    Sphere->vitesse.vY += PESANTEUR * TIMESTEP;

    Sphere->centre.centreX += Sphere->vitesse.vX * TIMESTEP;
    Sphere->centre.centreY += Sphere->vitesse.vY * TIMESTEP;

    if (Sphere->centre.centreX - Sphere->rayon < 0)
    {
        Sphere->centre.centreX = Sphere->rayon;
        Sphere->vitesse.vX = -Sphere->vitesse.vX * AMORTISSEMENT;
    }
    if (Sphere->centre.centreX + Sphere->rayon > LARGEUR)
    {
        Sphere->centre.centreX = LARGEUR - Sphere->rayon;
        Sphere->vitesse.vX = -Sphere->vitesse.vX * AMORTISSEMENT;
    }
    if (Sphere->centre.centreY - Sphere->rayon < 0)
    {
        Sphere->centre.centreY = Sphere->rayon;
        Sphere->vitesse.vY = -Sphere->vitesse.vY * AMORTISSEMENT;
    }
    if (Sphere->centre.centreY + Sphere->rayon > HAUTEUR)
    {
        Sphere->centre.centreY = HAUTEUR - Sphere->rayon;
        Sphere->vitesse.vY = -Sphere->vitesse.vY * AMORTISSEMENT;
    }
    Sphere->numeroCase = (int) (Sphere->centre.centreY / TAILLE_CASE) + (int) (Sphere->centre.centreY / TAILLE_CASE) * (LARGEUR / TAILLE_CASE);
    Sphere->n++; // Incrément du compteur de déplacement
    Sphere->trajectoire[Sphere->n % TAILLE_TRAJECTOIRE] = Sphere->centre;
}


bool compareSphereCase(Sphere c1, Sphere c2)
{
    int diff = abs(c1.numeroCase - c2.numeroCase);
    int casesParLigne = LARGEUR / TAILLE_CASE;

    if ((c1.numeroCase % casesParLigne == 0 && c2.numeroCase % casesParLigne == casesParLigne - 1) ||
        (c2.numeroCase % casesParLigne == 0 && c1.numeroCase % casesParLigne == casesParLigne - 1))
    {
        return false;
    }

    if (diff == 0)
    {
        return true;
    }

    if (diff == 1 || diff == casesParLigne)
    {
        return true;
    }

    if (diff == casesParLigne + 1 || diff == casesParLigne - 1)
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

    printf("\rPourcentage de collision évitées : %6.2f%% -- ", (float)compte/(nombre*(nombre - 1)/2) * 100);
}
