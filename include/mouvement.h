#ifndef MOUVEMENT_H
#define MOUVEMENT_H
#include <stdbool.h>
#include "myBubble.h"

void gereCollision(Sphere* c1, struct Sphere* c2);

void deplaceBalle(Sphere* Sphere);

bool compareSphereCase(Sphere c1, Sphere c2);

void gereAllCollision(Sphere* listSphere, int nombre);

#endif

