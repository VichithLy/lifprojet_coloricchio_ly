//
// Created by franklin on 19/03/19.
//

#include <time.h>
#include <Grapic.h>
#include <iostream>
#include "world.hpp"

using namespace std;
using namespace grapic;

void effect_object(World &W)
{
    //Object selected = W.player.get_object(W.decor.selected_inventaire);
    Object selected = W.player.inventaire.Tableau[W.decor.selected_inventaire];
    switch (selected.model)
    {
        //si c'est une potion
        case 0:
            switch (W.decor.selected_usage)
            {
                //boire
                case 0:
                    Mix_PlayChannel(-1, W.decor.effect[3], 0);
                    switch (selected.id)
                    {
                        case 0:
                            prend_degat(W.player, 10);
                            break;
                    }
                    break;
                    break;
                //verser
            }
            break;
        //si c'est un bouclier
        case 1:
            /*
            switch (W.decor.selected_usage)
            {
                case 0:
                    Mix_PlayChannel(-1, )
            }
             */
            break;

        case 2:
            break;
    }
    cout << "supression de l'objet " << endl;
    //W.player.remove_object(W.decor.selected_inventaire);
    remove_object_inventaire(W.player, W.decor.selected_inventaire);
    W.decor.object_usage = false;
}

Object AleaObject(World &W, int index)
{
    Object object;
    object.model = irand(0, 2);
    switch (object.model)
    {
        case 0:
            //si c'est une potion
            object.id = irand(0, 5);
            object.im = W.decor.Potion[object.id];
            //object.name = W.decor.Potion_name[object.id];
            object.image_name = W.decor.Potion_name[object.id];
            break;
        case 1:
            //un bouclier
            object.id = irand(0, 3);
            object.im = W.decor.Shield[object.id];
            object.image_name = W.decor.Shield_name[object.id];
        case 2:
            //une arme
            object.id = irand(0, 11);
            object.im = W.decor.Arme[object.id];
            object.image_name = W.decor.Arme_name[object.id];
            break;
    }
    //objet non récupérer
    //object.taken = false;
    //tout les objets ont donc la même position que celle du coffre
    Particle Part = create_particle(W.coffre_tab[index].pos, make_vector(0, 0), make_vector(0, 0), 1);
    //Particule Part(W.coffre_tab[index].pos, make_vector(0, 0), make_vector(0, 0), 1);
    object.obj = Part;
    return object;
}

bool JoueurAtteintCoffre(World &W)
{
    Vec2 player_pos = W.player.part.p;
    for (int i = 0; i < W.nb_coffres; i++)
    {
        if (get_distance(make_vector(player_pos.x + 32, player_pos.y + 36), W.coffre_tab[i].pos) < 50)
        {
            W.decor.index_open = i;
            return true;
        }
    }
    cout << "le joueur a atteint le coffre" << endl;
    return false;
}

void draw_coffre(World &W)
{
    for (int i = 0; i < W.nb_coffres; i++)
    {
        if (!W.coffre_tab[i].open)
            image_draw(W.decor.background[2], W.coffre_tab[i].pos.x, W.coffre_tab[i].pos.y, 23, 23);
        else
            image_draw(W.decor.background[3], W.coffre_tab[i].pos.x, W.coffre_tab[i].pos.y, 23, 23);
    }
}

void draw_coffre_content(Coffre C)
{
    fontSize(24);
    color(0, 0, 0);
    int y = 580;
    for (int i = 0; i < C.nb_objets; i++)
    {
        cout << C.objects[i].name << endl;
        image_draw(C.objects[i].im, 940, y, 40, 40);
        image_draw(C.objects[i].image_name, 570, y);
        y -= 50;
    }
}

void Place_coffre(World &W)
{
    srand(time(NULL));
    W.nb_coffres = 5;
    W.coffre_tab[0].pos = make_vector(350, 100);
    W.coffre_tab[0].nb_objets = 3;
    W.coffre_tab[1].pos = make_vector(600, 700);
    W.coffre_tab[1].nb_objets = 2;
    W.coffre_tab[2].pos = make_vector(760, 800);
    W.coffre_tab[2].nb_objets = 1;
    W.coffre_tab[3].pos = make_vector(500, 400);
    W.coffre_tab[3].nb_objets = 2;
    W.coffre_tab[4].pos = make_vector(800, 800);
    W.coffre_tab[4].nb_objets = irand(0, 4);

    for (int i = 0; i < W.nb_coffres; i++)
    {
        W.coffre_tab[i].open = false;
        //on place aléatoirement des objets dans les coffres
        for (int j = 0; j < W.coffre_tab[i].nb_objets; j++)
        {
            W.coffre_tab[i].objects[j] = AleaObject(W, i);
        }
    }
}

void set_image(World W, Object &object)
{
    switch (object.model)
    {
        case 0:
            object.im = W.decor.Potion[object.id];
            break;
        case 1:
            object.im = W.decor.Shield[object.id];
            break;
        case 2:
            object.im = W.decor.Arme[object.id];
            break;
    }
}

void add_object_sol(World &W, Object obj)
{
    if (W.nb_spawn_object < MAX_SPAWN_OBJECT)
    {
        W.spawn_object[W.nb_spawn_object] = obj;
        W.nb_spawn_object++;
    } else
    {
        cout << "Failed to add a new object to the floor" << endl;
    }
}

void init_objetSol(World &W)
{
    W.nb_spawn_object = 0;
    Object objet1, objet2;
    //positionnement de l'épée
    objet1.obj.p = make_vector(500, 600);
    objet1.model = 0;
    objet1.id = 0;
    objet1.taken = false;
    objet1.image_name = W.decor.Potion_name[0];
    //objet1.taken = false;
    objet2.obj.p = make_vector(400, 75);
    objet2.model = 2;
    objet2.taken = false;
    objet2.id = 5;
    objet2.image_name = W.decor.Arme_name[5];
    //objet2.taken = false;
    set_image(W, objet1);
    set_image(W, objet2);
    add_object_sol(W, objet1);
    add_object_sol(W, objet2);
}

void InitPartRamassage(World &W)
{
    frand(time(NULL));
    for (int i = 0; i < 20; i++)
    {
        Particle Part = create_particle(W.player.part.p, make_vector(frand(-20, 20), frand(-20, 20)), make_vector(0, 0), 10);
        W.decor.Ramasse[i] = Part;
    }
}

void draw_stars(World W)
{
    for (int i = 0; i < 20; i++)
    {
        image_draw(W.decor.background[4], W.decor.Ramasse[i].p.x, W.decor.Ramasse[i].p.y, 20,
                   20);
    }
}

void Ramasse_object(World &W)
{
    for (int i = 0; i < W.nb_spawn_object; i++)
    {
        //on recherche la distance entre l'objet et le centre du personnage
        if ((get_distance(make_vector(W.player.part.p.x + 32, W.player.part.p.y + 36),
                          W.spawn_object[i].obj.p + 17) < 35) &&
            (W.player.inventaire.nb_object < MAX_STUFF))
        {
            W.decor.tpsp[0] = elapsedTime();
            W.decor.is_Ramasse = true;
            W.decor.obj_ramasse = W.spawn_object[i];
            InitPartRamassage(W);
            Mix_PlayChannel(-1, W.decor.effect[0], 0);
            W.spawn_object[i].taken = true;
            add_object_inventaire(W.player, W.spawn_object[i]);
            //W.player.add_object(W.spawn_object[i]);
            //W.spawn_object.erase(W.spawn_object.begin() + i);
        }
    }
}

void draw_inventaire(World W)
{
    color(0, 0, 0, 200);
    int dx;
    if (W.player.inventaire.nb_object > 0)
        dx = 800/W.player.inventaire.nb_object;
    rectangleFill(0, 0, 1600, 900);
    image_draw(W.decor.background[12], 520, 660);
    image_draw(W.decor.background[11], 1560, 860);
    if (W.player.inventaire.nb_object > 0)
    {
        cout << "id's des objets dans l'inventaire" << endl;
        for (int i = 0; i < W.player.inventaire.nb_object; i++)
        {
            Object object = W.player.inventaire.Tableau[i];
            cout << object.name << endl;
            image_draw(object.im, 100 + i * dx, 470, 100, 100);
        }
        image_draw(W.decor.cursor[W.cursor.k], 115 + W.decor.selected_inventaire * dx, 420, 60, 60);
        Object select_obj = W.player.inventaire.Tableau[W.decor.selected_inventaire];
        image_draw(W.decor.background[13], 280, 220);
        image_draw(select_obj.image_name, 340, 265);
    }
}

void draw_inventaire_selected(World W)
{
    fontSize(30);
    color(255, 0, 0);
    //int dx;
   // if (W.player.get_nbObject() > 0)
     //   dx = 800/W.player.get_nbObject();
    Object selected = W.player.inventaire.Tableau[W.decor.selected_inventaire];
    //cout << "type de l'objet :" << selected.id << endl;
    image_draw(W.decor.background[17], 150, 300);
    switch (selected.model)
    {
        case 0:
            for (int i = 0; i < OPTION_POTION; i++)
            {
                print(370, 390 + i * 50, W.decor.potion_usage[i]);
            }
            break;
        case 1:
            for (int i = 0; i < OPTION_SHIELD; i++)
            {
                print(370, 390 + i * 50, W.decor.shield_usage[i]);
            }
            break;
        case 2:
            for (int i = 0; i < OPTION_WEAPON; i++)
            {
                print(370, 390 + i * 50, W.decor.weapon_usage[i]);
            }
            break;
    }
    image_draw(W.decor.background[16], 310, 380 + W.decor.selected_usage * 50);
}

void draw_spawn_objects(World W)
{
    for (int i = 0; i < W.nb_spawn_object; i++)
    {
        if (!W.spawn_object[i].taken)
            image_draw(W.spawn_object[i].im, W.spawn_object[i].obj.p.x,
                   W.spawn_object[i].obj.p.y);
    }
}

void init_javelot(World &W)
{
    Vec2 player_pos = W.player.part.p;
    Particle Part = create_particle(make_vector(player_pos.x + 32, player_pos.y + 36), make_vector(0, 0), make_vector(0, 0), 1);
    W.javelot = Part;
}

/*
void new_javelot(World &W)
{
    Object javelot;
    Particule Part(W.player.get_position(), make_vector(0, 0), make_vector(0, 0), 0.7);
    javelot.obj = Part;
    javelot.taken = true;
    javelot.id = -1;
    javelot.model = -1;
    javelot.name = W.decor.Arme_name[0];
    javelot.im = image("data/object/javelot.png");
    W.player.add_object(javelot);
}
*/