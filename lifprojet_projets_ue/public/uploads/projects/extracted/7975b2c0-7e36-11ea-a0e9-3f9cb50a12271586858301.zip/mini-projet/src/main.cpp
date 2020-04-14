#include <iostream>
#include <Grapic.h>
#include "world.hpp"

using namespace std;
using namespace grapic;

const int DIMWX = 1600;
const int DIMWY = 900;

void clean_music(World &W)
{
    //Mix_FreeMusic(background.sound);
    for (int i = 0; i < 1; i++)
    {
        Mix_FreeChunk(W.decor.effect[i]);
    }
    Mix_CloseAudio();
}

void load_name_object(World &W)
{
    string potion_path, shield_path, arme_path;
    for (int i = 0; i < 4; i++)
    {
        shield_path = "data/object/Shield00" + to_string(i + 1) + "_name.png";
        W.decor.Shield_name[i] = image(shield_path.c_str());
    }
    for (int i = 0; i < 7; i++)
    {
        potion_path = "data/object/Potion00" + to_string(i + 1) + "_name.png";
        W.decor.Potion_name[i] = image(potion_path.c_str());
    }
    for (int i = 0; i < 12; i++)
    {
        arme_path = "data/object/Arme0";
        if (i < 9)
            arme_path += "0";
        arme_path += to_string(i + 1) + "_name.png";
        W.decor.Arme_name[i] = image(arme_path.c_str());
    }
}

void init_decor(World &W)
{
    W.decor.in_menu = true;
    W.decor.selected_usage = 0;
    W.decor.object_usage = false;
    W.decor.player_brule = false;
    W.decor.player_dead = false;
    strcpy(W.name, " ");
    W.decor.accept_name = false;
    W.decor.selected_inventaire = 0;
    for (int i = 0; i < 4; i++)
        W.decor.tpsp[i] = elapsedTime();
    W.decor.inventaire = false;
    W.decor.is_Ramasse = false;
    W.decor.proche_tombe = false;
    W.decor.selected_coffre = 0;
    W.decor.open_treasure = false;
    string shield_path, potion_path, arme_path, flamme_path, letter_path, cursor_path;
    W.decor.background[0] = image("data/mouvements_perso/backgrounds/banderole.png");
    W.decor.background[1] = image("data/mouvements_perso/backgrounds/coffre_content.png");
    W.decor.background[2] = image("data/mouvements_perso/backgrounds/coffre.png");
    W.decor.background[3] = image("data/mouvements_perso/backgrounds/coffre_ouvert.png");
    W.decor.background[4] = image("data/mouvements_perso/backgrounds/stars.png");
    W.decor.background[5] = image("data/map_level/title0.png");
    W.decor.background[6] = image("data/mouvements_perso/backgrounds/selection.png");
    W.decor.background[7] = image("data/mouvements_perso/backgrounds/coffre_advice.png");
    W.decor.background[8] = image("data/pnj/mission1.png");
    W.decor.background[9] = image("data/pnj/select.png");
    W.decor.background[10] = image("data/mouvements_perso/backgrounds/tombe.png");
    W.decor.background[11] = image("data/mouvements_perso/backgrounds/close_inventaire.png");
    W.decor.background[12] = image("data/mouvements_perso/backgrounds/title_inventaire.png");
    W.decor.background[13] = image("data/mouvements_perso/backgrounds/background_select.png");
    W.decor.background[14] = image("data/mouvements_perso/backgrounds/input_name.png");
    W.decor.background[15] = image("data/mouvements_perso/backgrounds/perdu.png");
    W.decor.background[16] = image("data/mouvements_perso/backgrounds/selected_option.png");
    W.decor.background[17] = image("data/mouvements_perso/backgrounds/usage_background.png");
    W.decor.background[18] = image("data/mouvements_perso/backgrounds/new_item.png");
    W.decor.levelMap[0] = image("data/map_level/level0.png");
    W.decor.levelMap[1] = image("data/map_level/level1.jpg");
    //la map courante correspond à levelMap[0]
    W.level_map = W.decor.levelMap[0];
    for (int i = 0; i < 4; i++)
    {
        shield_path = "data/object/Shield00" + to_string(i + 1) + ".png";
        W.decor.Shield[i] = image(shield_path.c_str());
    }
    for (int i = 0; i < 6; i++)
    {
        potion_path = "data/object/Potion00" + to_string(i + 1) + ".png";
        W.decor.Potion[i] = image(potion_path.c_str());
    }
    for (int i = 0; i < 12; i++)
    {
        arme_path = "data/object/Arme0";
        if (i < 9)
            arme_path += "0";
        arme_path += to_string(i + 1) + ".png";
        W.decor.Arme[i] = image(arme_path.c_str());
    }
    for (int i = 0; i < 12; i++)
    {
        flamme_path = "data/flames/" + to_string(i + 1) + ".png";
        W.decor.flamme[i] = image(flamme_path.c_str());
    }

    for (int i = 0; i < 8; i++)
    {
        cursor_path = "data/mouvements_perso/backgrounds/selector/" + to_string(i + 1) + ".png";
        W.decor.cursor[i] = image(cursor_path.c_str());
    }
    for (int i = 0; i < 26; i++)
    {
        letter_path = "data/letters/" + to_string(i) + ".png";
        W.decor.letters[i] = image(letter_path.c_str());
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        exit(EXIT_FAILURE);
        //SDL_Quit();exit(1);
    }
    W.decor.effect[0] = Mix_LoadWAV("../data/sound/object.wav");
    W.decor.effect[1] = Mix_LoadWAV("../data/sound/fire.wav");
    W.decor.effect[2] = Mix_LoadWAV("../data/sound/open_chest.wav");
    W.decor.effect[3] = Mix_LoadWAV("../data/sound/boire.wav");

    for (int i = 0; i < 4; i++)
    {
        if (!W.decor.effect[i])
        {
            cerr << "failed to load the sounds" << endl;
            exit(EXIT_FAILURE);
        }
    }
    //initialisation des choix d'action associés au type d'objet
    strcpy(W.decor.potion_usage[0], "BOIRE");
    //strcpy(W.decor.potion_usage[1], "VERSER");
    strcpy(W.decor.shield_usage[0], "EQUIPER");
    strcpy(W.decor.shield_usage[1], "FRAPPER");
    strcpy(W.decor.weapon_usage[0], "PIQUER");
    strcpy(W.decor.weapon_usage[1], "COUPER");
}

void input_letter(World &W)
{
    char c = '\0';
    if (isKeyPressed(SDLK_a))
    {
        c = 'a';
    }
    if (isKeyPressed(SDLK_b))
    {
        c = 'b';
    }
    if (isKeyPressed(SDLK_c))
    {
        c = 'c';
    }
    if (isKeyPressed(SDLK_d))
    {
        c = 'd';
    }
    if (isKeyPressed(SDLK_e))
    {
        c = 'e';
    }
    if (isKeyPressed(SDLK_f))
    {
        c = 'f';
    }
    if (isKeyPressed(SDLK_e))
    {
        c = 'e';
    }
    if (isKeyPressed(SDLK_g))
    {
        c = 'g';
    }
    if (isKeyPressed(SDLK_h))
    {
        c = 'h';
    }
    if (isKeyPressed(SDLK_i))
    {
        c = 'i';
    }
    if (isKeyPressed(SDLK_j))
    {
        c = 'j';
    }
    if (isKeyPressed(SDLK_k))
    {
        c = 'k';
    }
    if (isKeyPressed(SDLK_l))
    {
        c = 'l';
    }
    if (isKeyPressed(SDLK_m))
    {
        c = 'm';
    }
    if (isKeyPressed(SDLK_n))
    {
        c = 'n';
    }
    if (isKeyPressed(SDLK_o))
    {
        c = 'o';
    }
    if (isKeyPressed(SDLK_p))
    {
        c = 'p';
    }
    if (isKeyPressed(SDLK_q))
    {
        c = 'q';
    }
    if (isKeyPressed(SDLK_r))
    {
        c = 'r';
    }
    if (isKeyPressed(SDLK_s))
    {
        c = 's';
    }
    if (isKeyPressed(SDLK_t))
    {
        c = 't';
    }
    if (isKeyPressed(SDLK_u))
    {
        c = 'u';
    }
    if (isKeyPressed(SDLK_v))
    {
        c = 'v';
    }
    if (isKeyPressed(SDLK_w))
    {
        c = 'w';
    }
    if (isKeyPressed(SDLK_x))
    {
        c = 'x';
    }
    if (isKeyPressed(SDLK_y))
    {
        c = 'y';
    }
    if (isKeyPressed(SDLK_z))
    {
        c = 'z';
    }
    //la lettre qui suite devient celle qui la été choisit si c'est le cas sinon c'est '\0'
    *(W.name + strlen(W.name)) = c;
}


void input_name(World &W, int x, int y)
{
    //si le mot est valide
    if ((strlen(W.name) >= 4) && isMousePressed(SDL_BUTTON_LEFT) && (x > 930) && (x < 1170) && (y > 330) && (y < 400))
    {
        W.decor.tpsp[1] = elapsedTime();
        if (elapsedTime() - W.decor.tpsp[1] >= 4.0)
        {
            image_draw(W.decor.background[5], 600, 700, 430, 150);
            W.decor.tpsp[1] = elapsedTime();
        }
        setKeyRepeatMode(true);
        W.player.name = W.name;
        W.decor.accept_name = true;
    } else {
        input_letter(W);
    }
}

void print_name(int x, int y, int size, int ecart, World W)
{
    int i = 1;
    while (W.name[i] != '\0')
    {
        image_draw(W.decor.letters[W.name[i] - 97], x + i * ecart, y, size, size);
        i++;
    }
}

void init_player(World &W)
{
    //on charge toute les sprte du perso
    for (int i = 0; i < 9; i++)
    {
        string haut_path = "data/mouvements_perso/avant/avant" + to_string(i) + ".png";
        string bas_path = "data/mouvements_perso/bas/bas" + to_string(i) + ".png";
        string gauche_path = "data/mouvements_perso/gauche/gauche" + to_string(i) + ".png";
        string droite_path = "data/mouvements_perso/droite/droite" + to_string(i) + ".png";
        W.bas[i] = image(bas_path.c_str());
        W.haut[i] = image(haut_path.c_str());
        W.droite[i] = image(droite_path.c_str());
        W.gauche[i] = image(gauche_path.c_str());
    }
    for (int i = 0; i < 6; i++)
    {
        string attaque_haut = "data/mouvements_perso/attaque/haut/haut" + to_string(i) + ".png";
        /*
        string attaque_bas = "data/mouvements_perso/bas/bas" + to_string(i) + ".png";
        string attaque_droite = "data/mouvements_perso/droite/droite" + to_string(i) + ".png";
         */
        //string attaque_gauche = "data/mouvements_perso//gauche/gauche" + to_string(i) + ".png";
        W.Attaque_Haut[i] = image(attaque_haut.c_str());
        /*
        W.Attaque_Bas[i] = image(attaque_bas.c_str());
        W.Attaque_Droite[i] = image(attaque_droite.c_str());
         */
        //W.Attaque_Gauche[i] = image(attaque_gauche.c_str());
    }
    //Personnage joueur("Arthur", make_vector(DIMWX/2, DIMWY/2), 0.25, HAUT);
    Personnage joueur = new_personnage("Arthur", make_vector(DIMWX/2, DIMWY/2), GAUCHE);
    W.player = joueur;
    W.player.inventaire.nb_object = 0;
    W.player.speed = 0.5;
    //initialisation de la premier image du personnage
    W.player.im = W.haut[0];
    //ajout d'un javelot à l'inventaire du personnage
    //new_javelot(W);
}


void init_world(World &W)
{
    W.quit = false;
    Init_menu(W.menu);
    init_animation(W);
    load_name_object(W);
    //init_javelot(W);
    init_decor(W);
    init_player(W);
    Place_coffre(W);
    init_objetSol(W);
    init_frelons(W.F);
    Init_PNJ(W);
}

bool closeButton(int x, int y)
{
    if (isMousePressed(SDL_BUTTON_LEFT) && (x > 1023) && (x < 1045) && (y > 686) && (y < 710))
        return true;
    return false;
}

bool close_inventaire(int x, int y)
{
    if (isMousePressed(SDL_BUTTON_LEFT) && (x > 1560) && (x < 1600) && (y > 860) && (y < 900))
        return true;
    return false;
}

void KeyEvents(World &W)
{
    //cout << "position du joueur : " << W.player.get_position().x << ", " << W.player.get_position().y << endl;
    int x, y;
    mousePos(x, y);

    //saisie du non du joueur
    if (!W.decor.accept_name)
    {
        setKeyRepeatMode(false);
        if (isKeyPressed(SDLK_BACKSPACE) && strlen(W.name) > 1)
        {
            W.name[strlen(W.name) - 1] = '\0';
        }
        if (strlen(W.name) < CHMAX)
            input_name(W, x, y);
    }
    if (W.decor.proche_tombe && isKeyPressed(SDLK_RETURN))
    {
        setKeyRepeatMode(true);
        W.decor.proche_tombe = false;
    }

    if (isKeyPressed(SDLK_i))
    {
        W.decor.inventaire = true;
        setKeyRepeatMode(false);
    }
    //on on ouvre l'inventaire du joueur
    if (W.decor.inventaire && !W.decor.object_usage)
    {
        cursor_animation(W.cursor);
        //pour changer d'objet il doit y a avoir au moins 2 objets
        if (isKeyPressed(SDLK_RIGHT) && (W.decor.selected_inventaire < W.player.inventaire.nb_object - 1) && (W.player.inventaire.nb_object > 1))
        {
            Mix_PlayChannel(-1, W.decor.effect[0], 0);
            W.decor.selected_usage = 0;
            W.decor.selected_inventaire++;
        }
        if (isKeyPressed(SDLK_LEFT) && (W.decor.selected_inventaire > 0) && (W.player.inventaire.nb_object > 1))
        {
            W.decor.selected_usage = 0;
            Mix_PlayChannel(-1, W.decor.effect[0], 0);
            W.decor.selected_inventaire--;
        }
        if (close_inventaire(x, y))
        {
            setKeyRepeatMode(true);
            W.decor.inventaire = false;
        }
        if (isKeyPressed(SDLK_RETURN) && W.player.inventaire.nb_object > 0)
        {
            setKeyRepeatMode(false);
            W.decor.object_usage = true;
        }
    }
    if (W.decor.object_usage)
    {
        if (isKeyPressed(SDLK_RETURN))
        {
            effect_object(W);
        }
        if (isKeyPressed(SDLK_DOWN) && (W.decor.selected_usage > 0))
        {
            W.decor.selected_usage--;
        }
        if (isKeyPressed(SDLK_UP) && (W.decor.selected_usage < 1))
        {
            W.decor.selected_usage++;
        }
        if (isKeyPressed(SDLK_m))
        {
            W.decor.object_usage = false;
        }
    }

    //cout << "Nouvelle position du joueur : " << W.player.part.p.x << ", " << W.player.part.p.y << endl;
    //touche entré + bonne position + ouvre qu'une seule fois
    if (isKeyPressed(SDLK_RETURN) && get_distance(W.player.part.p, make_vector(1119, 666)) < 50)  // && get_distance(W.player.get_position(), make_vector(858, 590)) < 50)
    {
        setKeyRepeatMode(false);
        //double val  = get_distance(W.player.get_position(), make_vector(500, 500));
        //cout << "distance par rapport au joueur : " << val << endl;
        W.decor.proche_tombe = true;
    }

    if (isKeyPressed(SDLK_RETURN) && JoueurAtteintCoffre(W) && !W.coffre_tab[W.decor.index_open].open)
    {
        Mix_PlayChannel(-1, W.decor.effect[2], 0);
        //on affiche une fenetre avec les info du coffre
        W.decor.open_treasure = true;
        //le coffre graphiquement devient ouvert
        W.coffre_tab[W.decor.index_open].open = true;
    }
    //ouerture d'un coffre
    if (W.decor.open_treasure)
    {
        setKeyRepeatMode(false);
        if (isKeyPressed(SDLK_s) && W.player.inventaire.nb_object < MAX_STUFF)
        {
            cout << "nombre d'ojets dans le coffre :" << W.coffre_tab[W.decor.index_open].nb_objets << endl;
            cout << "index objet sélectioné : " << W.decor.selected_coffre << endl;
            add_object_inventaire(W.player, W.coffre_tab[W.decor.index_open].objects[W.decor.selected_coffre]);
            if (W.decor.selected_coffre > 0)
            {
                W.decor.selected_coffre--;
            }
            W.coffre_tab[W.decor.index_open].nb_objets--;
        }
        if (closeButton(x, y))
        {
            W.decor.open_treasure = false;
            setKeyRepeatMode(true);
        }
        if (isKeyPressed(SDLK_DOWN) && (W.decor.selected_coffre < W.coffre_tab[W.decor.index_open].nb_objets - 1))
        {
            W.decor.selected_coffre++;
        }
        if (isKeyPressed(SDLK_UP) && (W.decor.selected_coffre > 0))
        {
            W.decor.selected_coffre--;
        }
    }
    //refus ou accepte la mission
    if (W.decor.rencontre_pnj)
        quest_choice(W);
    if (isKeyPressed(SDLK_LCTRL))
    {
        //Monster_prend_degats()
        switch (W.player.dir)
        {
            case HAUT:
                W.player.im = W.Attaque_Haut[W.attaque.k];
                break;
                /*
            case BAS:
                W.player.im = W.Attaque_Bas[W.attaque.k];
                break;
            case GAUCHE:
                W.player.im = W.Attaque_Gauche[W.attaque.k];
                break;
            case DROITE:
                W.player.im = W.Attaque_Droite[W.attaque.k];
                break;
                 */
        }
        W.player.attaque = true;
        //W.javelot.add_force(make_vector(x, y) - W.player.get_position());
        //addforce
        //lance_javelot();
    }
    else if (isKeyPressed(SDLK_UP))
    {
        W.player.im = W.haut[W.joueur.k];
        W.player.dir = HAUT;
        W.player.bouge = true;
        translate_part(W.player.part, W.player.part.p, 0, W.player.speed);
        //W.player.translate_part(W.player.get_position(), 0, W.player.get_vitessef());
    }
    else if (isKeyPressed(SDLK_DOWN))
    {
        W.player.im = W.bas[W.joueur.k];
        W.player.dir = BAS;
        W.player.bouge = true;
        translate_part(W.player.part, W.player.part.p, 0, -W.player.speed);
        //W.player.translate_part(W.player.get_position(), 0, -W.player.get_vitessef());
    }
    else if (isKeyPressed(SDLK_RIGHT))
    {
        W.player.im = W.droite[W.joueur.k];
        W.player.dir = DROIT;
        W.player.bouge = true;
        translate_part(W.player.part, W.player.part.p, W.player.speed, 0);
        //W.player.translate_part(W.player.get_position(), W.player.get_vitessef(), 0);
    }
    else if (isKeyPressed(SDLK_LEFT))
    {
        W.player.im = W.gauche[W.joueur.k];
        W.player.dir = GAUCHE;
        W.player.bouge = true;
        translate_part(W.player.part, W.player.part.p, -W.player.speed, 0);
        //W.player.translate_part(W.player.get_position(), -W.player.get_vitessef(), 0);
    }
        //si le perso ne bouge pas
    else
    {
        W.player.bouge = false;
        switch (W.player.dir)
        {
            case HAUT:
                W.player.im = W.haut[0];
                break;
            case BAS:
                W.player.im = W.bas[0];
                break;
            case GAUCHE:
                W.player.im = W.gauche[0];
                break;
            case DROIT:
                W.player.im = W.droite[0];
                break;
        }
    }
}

void update(World &W)
{
    KeyEvents(W);
    PartUpdate(W.dt, W.player.part);

    if (W.player.vie == 0)
    {
        W.decor.tpsp[3] = elapsedTime();
        W.decor.player_dead = true;
    }

    for (int i = 0; i < W.F.nb_frelons; i++)
    {
        PartUpdate(W.dt, W.F.frelons[i].monster);
        //W.F.frelons[i].monster.partUpdate(W.dt);
    }
    //mise à jour des étoiles
    for (int i = 0; i < 20; i++)
    {
        PartUpdate(W.dt, W.decor.Ramasse[i]);
        //on applique la force de gravité
        W.decor.Ramasse[i].f = make_vector(0, -W.decor.Ramasse[i].m * 9.81f);
        //set_force(W.decor.Ramasse[i], make_vector(0, -W.decor.Ramasse[i].m * 9.81f));
        //W.decor.Ramasse[i].set_force(make_vector(0, -W.decor.Ramasse[i].get_masse() * 9.81f));
        //mise à jour de la position et de la vitesse
        //PartUpdate(W.dt, W.decor.Ramasse[i]);
        //W.decor.Ramasse[i].partUpdate(W.dt);
    }
    player_animation(W);
    flamme_animation(W.flamme);
    //si le joueur ne bouge pas on reste sur la premiere image
    if (!W.player.bouge)
        W.joueur.k = 0;
    read_map(W);
    Ramasse_object(W);
    update_frelons(W.F);
    frelond_attaque(W);
    follow_player(W);
    crepitement_bois(W);
    png_interact(W);
    player_attaque_epee(W);
}

void draw(World W)
{
    image_draw(W.level_map, 0, 0, 1600, 900);
    //affiche les coffres
    draw_coffre(W);
    //affiche les objets au sol
    draw_spawn_objects(W);
    draw_PNJ(W);
    image_draw(W.decor.background[0], 620, 900, 400, 100);
    color(255, 0, 0);
    rectangleFill(700, 850, 700 + 2 * W.player.vie, 840);
    image_draw(W.bas[0], 920, 820);
    image_draw(W.player.im, W.player.part.p.x, W.player.part.p.y, 64, 72);
    draw_frelond(W.F);
    //affichage des flammes statiques
    for (int i = 0; i < W.flamme.nb; i++)
    {
        image_draw(W.decor.flamme[W.flamme.k], W.flamme.pos[i].x, W.flamme.pos[i].y, 32, 48);
    }
    image_draw(W.decor.flamme[W.flamme.k], W.flamme.pos[W.flamme.nb - 1].x, W.flamme.pos[W.flamme.nb -1].y, 60, 72);
    //après ouverture d'un coffre
    if (W.decor.is_Ramasse)
    {
        fontSize(50);
        color(255, 0, 0);
        draw_stars(W);

        if (elapsedTime() - W.decor.tpsp[0] >= 4.0)
        {
            W.decor.tpsp[0] = elapsedTime();
            W.decor.is_Ramasse = false;
        } else
        {
            //fontSize(60);
            //print(310, 600, "NOUVEL OBJET !!!");
            image_draw(W.decor.background[18], 310, 600);
            image_draw(W.decor.obj_ramasse.image_name, 360, 500);
        }
    }
    if (W.decor.open_treasure)
    {
        image_draw(W.decor.background[1], 545, 380, 500, 325);
        draw_coffre_content(W.coffre_tab[W.decor.index_open]);
        //cadre de sélection de l'objet

        if (W.coffre_tab[W.decor.index_open].nb_objets > 0)
            image_draw(W.decor.background[6], 560, 580 - W.decor.selected_coffre * 50);
        image_draw(W.decor.background[7], 650, 700, 280, 130);
    }
    if (W.decor.rencontre_pnj)
    {
        switch (W.decor.pnj_index)
        {
            //première quête
            case 0:
                image_draw(W.decor.background[8], 300, 300);
                if (W.decor.quest_choice == 0)
                {
                    image_draw(W.decor.background[9], 540, 340);
                } else
                    image_draw(W.decor.background[9], 540, 300);
                break;
        }
    }
    if (W.decor.proche_tombe)
    {
        image_draw(W.decor.background[10], 550, 500);
    }
    if (W.decor.player_brule)
    {
        Mix_PlayChannel(-1, W.decor.effect[1], 0);
        image_draw(W.decor.flamme[W.flamme.k], W.player.part.p.x + 20, W.player.part.p.y + 30, 32, 48);
        //si le joueur brule pendant plus de 10 s on met le booléenne à faux.
        if ((elapsedTime() - W.decor.tpsp[1]) >= 5)
        {
            W.decor.tpsp[1] = elapsedTime();
            W.decor.player_brule = false;
        }
    }
    if (W.decor.inventaire)
    {
        draw_inventaire(W);
        if (W.decor.object_usage)
        {
            draw_inventaire_selected(W);
        }
    }
    if (!W.decor.accept_name)
    {
        image_draw(W.decor.background[14], 400, 300);
        //print(318, 470, W.name);
        print_name(618, 470, 60, 25, W);
    } else
    {
        print_name(680, 945, 30, 15, W);
    }
    //si le joueur meut --> message perdu
    if (W.decor.player_dead)
    {
        if (elapsedTime() - W.decor.tpsp[3] > 5)
        {
            W.decor.tpsp[3] = elapsedTime();
            W.decor.player_dead = false;
        } else
        {
            color(0, 0, 0, 210);
            rectangleFill(0, 0, 1600, 900);
            image_draw(W.decor.background[15], 300, 500, 570, 300);
        }
    }
}

int main()
{
    World monde;
    bool stop = false;
    winInit("RPG", DIMWX, DIMWY);
    if (init_map(monde) == -1)
        return EXIT_FAILURE;
    init_world(monde);
    backgroundColor(255, 255, 255);
    while (!stop)
    {
        winClear();
        //menu principale
        if (monde.decor.in_menu)
        {
            display_menu(monde);
            update_menu(monde);
        } else
        {
            //lancement du jeu
            draw(monde);
            update(monde);
        }
        if (monde.quit)
        {
            stop = true;
        }
        else
        {
            stop = winDisplay();
        }
    }
    winQuit();
    clean_music(monde);
    return 0;
}