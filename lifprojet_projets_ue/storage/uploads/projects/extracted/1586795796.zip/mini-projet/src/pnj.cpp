//
// Created by franklin on 24/03/19.
//

#include <Grapic.h>
#include <iostream>
#include "world.hpp"

using namespace grapic;
using namespace std;

Pnj create_pnj(string name, Vec2 p, DIRECTION dir)
{
    Pnj my_pnj;
    my_pnj.name = name;
    my_pnj.pos = p;
    my_pnj.dir = dir;
    my_pnj.next_quest.accepted = false;
    my_pnj.next_quest.done = false;
    my_pnj.next_quest.index_pnj = -1;
    return my_pnj;
}

void Init_PNJ(World &W)
{
    W.decor.rencontre_pnj = false;
    W.decor.quest_choice = 0;
    W.nb_pnj = 1;
    //Pnj aml("David", make_vector(100, 300), 0.3, DROIT);
    Pnj aml = create_pnj("David", make_vector(430, 270), DROIT);
    aml.im = image("data/pnj/chevalier.png");
    W.pnj_tab[0] = aml;
}

void draw_PNJ(World W)
{
    for (int i = 0; i < W.nb_pnj; i++)
    {
        image_draw(W.pnj_tab[i].im, W.pnj_tab[i].pos.x, W.pnj_tab[i].pos.y);
    }
}

//retourne l'indice du pnj vers le lequelle le joueur addresse la parole
void png_interact(World &W)
{
    for (int i = 0; i < W.nb_pnj; i++)
    {
        if (get_distance(W.player.part.p, W.pnj_tab[i].pos) < 40 && isKeyPressed(SDLK_RETURN))
        {
            W.decor.rencontre_pnj = true;
            W.decor.pnj_index = i;
        }
    }
}

void quest_choice(World &W)
{
    setKeyRepeatMode(false);

    if (isKeyPressed(SDLK_s))
    {
        //on socke les quêtes à faire dans un autre tableau
        //addQuest(W);
        W.decor.rencontre_pnj = false;
        setKeyRepeatMode(true);
    }
    //oui ou non
    if (isKeyPressed(SDLK_DOWN) && W.decor.quest_choice == 0)
    {
        W.decor.quest_choice = 1;
    }
    if (isKeyPressed(SDLK_UP) && W.decor.quest_choice > 0)
    {
        W.decor.quest_choice = 0;
    }
}