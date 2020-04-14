//
// Created by franklin on 11/04/19.
//

#include "Personnage.hpp"

void remove_object_inventaire(Personnage &P, int index)
{
    P.inventaire.Tableau[index].model = -1;
    P.inventaire.Tableau[index].id = -1;
}

void add_object_inventaire(Personnage &P, Object obj)
{
    if (P.inventaire.nb_object < MAX_OBJECT)
    {
        P.inventaire.Tableau[P.inventaire.nb_object] = obj;
        P.inventaire.nb_object++;
    } else
    {
        cout << "Failed to add a new object" << endl;
    }
}

Personnage new_personnage(string name, Vec2 pos, DIRECTION direction)
{
    Personnage P;
    P.part = create_particle(pos, make_vector(0, 0), make_vector(0, 0), 1);
    P.vie = 100;
    P.name = name;
    P.dir = direction;
    P.bouge = false;
    P.attaque = false;
    return P;
}

void prend_degat(Personnage &P, int degats)
{
    if (P.vie > degats)
        P.vie -= degats;
    else
        P.vie = 0;
}