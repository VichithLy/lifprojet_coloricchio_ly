//
// Created by franklin on 11/04/19.
//

#include <Grapic.h>
#include <iostream>
#include "world.hpp"

using namespace grapic;
using namespace std;

void init_animation(World &W)
{
    W.flamme.nb = 6;
    W.flamme.pos[0] = make_vector(400, 10);
    W.flamme.pos[1] = make_vector(470, 10);
    W.flamme.pos[2] = make_vector(300, 20);
    W.flamme.pos[3] = make_vector(400, 800);
    W.flamme.pos[4] = make_vector(600, 827);
    W.flamme.pos[5] = make_vector(500, 853);
    W.cursor.k = 0;
    W.cursor.tpsp = 0;

    W.cursor.nb = 1;
    W.joueur.k = 0;
    W.joueur.tpsp = 0;
    W.attaque.k = 0;
    W.attaque.tpsp = 0;
}

void player_animation(World &W)
{
    if (W.player.bouge && (elapsedTime() - W.joueur.tpsp) > 1. / 17)
    {
        //explosion(dat, k);
        W.joueur.tpsp = elapsedTime();
        W.joueur.k++;
        if (W.joueur.k > 8)
        {
            W.player.bouge = false;
            W.joueur.k = 0;
        }
    }
}

void cursor_animation(Animation &cursor)
{
    if ((elapsedTime()) - cursor.tpsp > 1. / 12)
    {
        cursor.tpsp = elapsedTime();
        cursor.k++;
        if (cursor.k > 7)
        {
            cursor.k = 0;
        }
    }
}

void player_attaque_epee(World &W)
{
    if (W.player.attaque && (elapsedTime() - W.attaque.tpsp) > 1. / 22)
    {
        W.attaque.tpsp = elapsedTime();
        W.attaque.k++;
        if (W.attaque.k > 5)
        {
            W.player.attaque = false;
            W.attaque.k = 0;
        }
    }
}


void flamme_animation(Animation &flamme)
{
    if ((elapsedTime() - flamme.tpsp) > 1. / 20)
    {
        //explosion(dat, k);
        flamme.tpsp = elapsedTime();
        flamme.k++;
        if (flamme.k > 11)
        {
            flamme.k = 0;
        }
    }
}