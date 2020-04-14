//
// Created by franklin on 26/04/19.
//

#include <Grapic.h>
#include <iostream>
#include "world.hpp"

using namespace std;
using namespace grapic;

void Init_menu(Main_menu &M)
{
    M.flamme.k = 0;
    M.flamme.tpsp = elapsedTime();
    M.flamme.nb = 2;
    M.flamme.pos[0] = make_vector(270, 390);
    M.flamme.pos[1] = make_vector(600, 370);
    M.flamme.pos[2] = make_vector(1400, 380);
    M.im[0] = image("data/menu/Background.png");
    for (int i = 1; i < 3; i++)
    {
        string name = "data/menu/texture" + to_string(i) + ".png";
        M.im[i] = image(name.c_str());
    }
    //M.im[3] = image("data/menu/torche.png");
    M.background_color = make_color(204, 20, 40);
    M.seting.volume = 70;
    M.seting.model_player = 0;
    M.index_select = 0;
}

void update_menu(World &W)
{
    if (isKeyPressed(SDLK_DOWN) && W.menu.index_select < 4)
    {
        W.menu.index_select++;
    }
    if (isKeyPressed(SDLK_UP) && W.menu.index_select > 0)
    {
        W.menu.index_select--;
    }
    if (isKeyPressed(SDLK_RETURN))
    {
        switch (W.menu.index_select)
        {
            case 0:
                W.decor.in_menu = false;
                break;
            case 1:
                W.quit = true;
                break;
        }
    }
    flamme_animation(W.menu.flamme);
}

void display_menu(World W)
{
    color(W.menu.background_color.r, W.menu.background_color.g, W.menu.background_color.b);
    image_draw(W.menu.im[0], 0, 0, DIMWX, DIMWY);
    //on colori le fond de la case selectionnée
    switch (W.menu.index_select)
    {
        case 0:
            rectangleFill(605, 505, 995, 590);
            break;
        case 1:
            rectangleFill(605, 305, 995, 385);
            break;
    }
    //rectangleFill(605, 505 - 150 * menu.index_select, 995, 590);
    image_draw(W.menu.im[1], 600, 500, 400, 90);
    image_draw(W.menu.im[2], 600, 300, 400, 90);
    //image_draw(W.menu.im[3], 250, 340, 80, 120);
    image_draw(W.decor.flamme[W.menu.flamme.k], W.menu.flamme.pos[0].x, W.menu.flamme.pos[0].y, 37, 50);
    image_draw(W.decor.flamme[W.menu.flamme.k], W.menu.flamme.pos[1].x, W.menu.flamme.pos[1].y, 64, 80);
    image_draw(W.decor.flamme[W.menu.flamme.k], W.menu.flamme.pos[2].x, W.menu.flamme.pos[2].y, 64, 80);

}