//
// Created by franklin on 11/04/19.
//

#ifndef LIFAMI_GAME_PERSONNAGE_HPP
#define LIFAMI_GAME_PERSONNAGE_HPP

#include <iostream>
#include <Grapic.h>
#include "particule.hpp"

using namespace grapic;
using namespace std;

const int MAX_OBJECT = 5;

enum DIRECTION {GAUCHE, DROIT, HAUT, BAS};

struct Object
{
    bool taken;

    Particle obj;
    //nom de l'objet
    string name;
    //image de l'objet
    Image im;
    //model d'objet
    int model;
    //objet
    int id;
    Image image_name;
};

struct Inventaire
{
    Object Tableau[MAX_OBJECT];
    int nb_object;
};

struct Personnage
{
    bool attaque;
    Inventaire inventaire;
    DIRECTION dir;
    string name;
    float speed;
    bool bouge;
    Particle part;
    int vie;
    Image im;
};

Personnage new_personnage(string name, Vec2 pos, DIRECTION dir);
void remove_object_inventaire(Personnage &P, int index);
void add_object_inventaire(Personnage &P, Object obj);
void prend_degat(Personnage &P, int degats);

#endif //LIFAMI_GAME_PERSONNAGE_HPP
