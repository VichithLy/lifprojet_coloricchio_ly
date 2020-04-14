//
// Created by franklin on 19/03/19.
//

#include <fstream>
#include <iostream>
#include <Grapic.h>
#include "world.hpp"

using namespace std;
using namespace grapic;

int init_map(World &W)
{
    //on ouvre le fichier en lecture
    ifstream file("../data/mouvements_perso/collision/level0.txt", ios::in);
    if (!file)
    {
        cerr << "Impossible d'ouvrir le fichier level0.txt" << endl;
        return -1;
    }

    int i = 0;
    string line;
    while (getline(file, line))
    {
        W.map[i] = line;
        i++;
    }
    return 0;
}

void read_map(World &W)
{
    Vec2 pos = W.player.part.p;
    //if (pos.x > 340)
    pos.x = pos.x - 340;
    //else
        //pos.x = 10;
    cout << "position du joueur : " << pos.x << ", " << pos.y << endl;
    int pos_x = pos.x / 4;
    int pos_y = (DIMWY - pos.y) / 4;

    if (W.map[pos_y][pos_x] == '1')
    {
        switch (W.player.dir)
        {
            case HAUT:
                W.player.part.p = make_vector(340 + pos.x, pos.y - 5);
                break;
            case DROIT:
                W.player.part.p = make_vector(340 + pos.x - 5, pos.y);
                break;
            case GAUCHE:
                W.player.part.p = make_vector(pos.x + 345, pos.y);
                //W.player.set_position(make_vector(pos.x + 5, pos.y));
                break;
            case BAS:
                W.player.part.p = make_vector(pos.x, pos.y + 345);
                //W.player.set_position(make_vector(pos.x, pos.y + 5));
                break;
        }
    }
    if (W.map[pos_y][pos_x] == 'C')
    {
        W.player.part.p = make_vector(W.player.part.p.x, 500);
        //W.player.set_position(make_vector(W.player.get_position().x, 500));
        W.level_map = W.decor.levelMap[1];
    }
}