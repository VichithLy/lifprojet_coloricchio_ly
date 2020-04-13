//
// Created by franklin on 12/04/19.
//

#include <iostream>
#include <Grapic.h>
#include "world.hpp"

using namespace std;
using namespace grapic;

void crepitement_bois(World &W)
{
    for (int i = 0; i < W.flamme.nb; i++)
    {
        if (get_distance(W.player.part.p, W.flamme.pos[i]) < 50)
        {
            //si le joueur reste plus de 2 secondes pres du feu, il perd de la vie
            if (!W.decor.player_brule)
            {
                W.decor.tpsp[1] = elapsedTime();
                W.decor.player_brule = true;
            }
            Mix_PlayChannel(-1, W.decor.effect[1], 0);
        }
        if ((elapsedTime() - W.decor.tpsp[2] >= 1) && W.decor.player_brule)
        {
            W.decor.tpsp[2] = elapsedTime();
            //W.player.prend_degat(4);
            prend_degat(W.player, 4);
        }
    }
}

int Monster_proche_player(World &W)
{
    for (int i = 0; i < W.F.nb_frelons; i++)
    {
        if (get_distance(W.F.frelons[i].monster.p, W.player.part.p) < 30)
        {
            return i;
        }
    }
    return -1;
}

void Monster_prend_degat(World &W)
{
    int val = Monster_proche_player(W);
    if (val != -1)
    {
        switch (W.player.dir)
        {
            case HAUT:
                if (W.player.part.p.y < W.F.frelons[val].monster.p.y)
                    cout << "monstre proche en haut" << endl;
                break;
            case BAS:
                if (Monster_proche_player(W))
                    cout << "monstre proche en bas" << endl;
                break;
            case GAUCHE:
                if (Monster_proche_player(W))
                    cout << "monstre proche à gauche" << endl;
                break;
            case DROIT:
                if (Monster_proche_player(W))
                    cout << "monstre proche à droite" << endl;
                break;
        }
    }
}