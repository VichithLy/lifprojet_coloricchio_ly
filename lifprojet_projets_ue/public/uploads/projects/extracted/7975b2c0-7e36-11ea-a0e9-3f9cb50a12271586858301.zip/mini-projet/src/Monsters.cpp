//
// Created by franklin on 20/03/19.
//

#include <iostream>
#include <Grapic.h>
#include "world.hpp"

using namespace std;
using namespace grapic;

const int NB_FRELONS = 7;

void init_frelons(Frelons &F)
{
    srand(time(NULL));
    F.attaque = false;
    F.nb_frelons = 0;
    Image im = image("data/monsters/frelond.png");
    for (int i = 0; i < NB_FRELONS; i++)
    {
        Monster M;
        M.im = im;
        Particle frelon = create_particle(make_vector(frand(330, 370), frand(750, 850)), make_vector(0, 0), make_vector(0, 0), 1);
        M.monster = frelon;
        M.vie = 100;
        F.frelons[i] = M;
        F.nb_frelons++;
    }
}

void update_frelons(Frelons &F)
{
    //tout les frelons font une rotation autour du même point
    if (!F.attaque)
    {
        for (int i = 0; i < 4; i++)
        {
            rotate_part(F.frelons[i].monster, F.frelons[i].monster.p, 350, 800, 0.7);
            //F.frelons[i].monster.rotate_part(F.frelons[i].monster.get_position(), 50, 800, 0.7);
        }
        for (int i = 4; i < NB_FRELONS; i++)
        {
            rotate_part(F.frelons->monster, F.frelons[i].monster.p, 350, 800, -0.7);
            //F.frelons[i].monster.rotate_part(F.frelons[i].monster.get_position(), 50, 800, -0.7);
        }
    }
}

void draw_frelond(Frelons F)
{
    for (int i = 0; i < F.nb_frelons; i++)
    {
        image_draw(F.frelons[i].im, F.frelons[i].monster.p.x, F.frelons[i].monster.p.y, 30, 30);
    }
}

void frelond_attaque(World &W)
{
    Vec2 player_pos = W.player.part.p;
    for (int i = 0; i < W.F.nb_frelons; i++)
    {
        if (get_distance(make_vector(player_pos.x + 32, player_pos.y + 36), W.F.frelons[i].monster.p + 20) < 200)
        {
            W.F.attaque = true;
        } else
        {
            W.F.attaque = false;
        }
    }
}

void follow_player(World &W)
{
    if (W.F.attaque)
    {
        //tout les folons vont dans la direction du joueur
        for (int i = 0; i < W.F.nb_frelons; i++)
        {
            Vec2 direction = (-1 * W.F.frelons[i].monster.p) + W.player.part.p;
            direction = direction + make_vector(frand(-10, 10), frand(-10, 10));
            //Vec2 vec_directeur = W.F.frelons[i].monster.get_position() + (-1 * W.player.get_position());
            //vec_directeur = 0.4 * vec_directeur;
            //W.F.frelons[i].monster.translate_part(W.player.get_position(), 0, 0);
            //W.F.frelons[i].monster.set_vitesse(0.4 * direction);
            W.F.frelons[i].monster.v = 0.4 * direction;
            //rotation des frelons autour du personnage
            if (get_distance(W.player.part.p, W.F.frelons[i].monster.p) < 30)
            {
                rotate_part(W.F.frelons[i].monster, W.F.frelons[i].monster.p, W.player.part.p.x, W.player.part.p.y, 0.7);
                //W.F.frelons[i].monster.rotate_part(W.F.frelons[i].monster.get_position(), W.player.get_position().x, W.player.get_position().y, 0.7);
            }
        }
    }
}