//
// Created by franklin on 11/04/19.
//

#ifndef LIFAMI_GAME_WORLD_HPP
#define LIFAMI_GAME_WORLD_HPP

#include <Grapic.h>
#include <SDL2/SDL_mixer.h>
#include "Personnage.hpp"
#include "color.hpp"

using namespace grapic;

extern const int DIMWX;
extern const int DIMWY;

const int CHMAX = 64;
const int MAX_TPSP = 10;
const int MAX_BACKGROUND = 20;
const int MAX_COFFRE = 20;
const int MAX_PNJ = 5;
const int MAX_STUFF = 5;
const int MAX_FLAMME = 10;
const int OPTION_WEAPON = 2;
const int OPTION_SHIELD = 2;
const int OPTION_POTION = 1;
const int MAX_SPAWN_OBJECT = 4;
const int MAX_FRELONS = 10;
const int MAX_OBJECTS_COFFRE = 5;

struct Quest
{
    int index_pnj;
    bool done;
    bool accepted;
};

//un pnj
struct Pnj
{
    Quest next_quest;
    string name;
    Vec2 pos;
    Image im;
    DIRECTION dir;
};


//animation
struct Animation
{
    int nb;
    Vec2 pos[MAX_FLAMME];
    int k;
    float tpsp;
};

//le décor
struct Decor
{
    bool in_menu;
    int selected_usage;
    bool object_usage;
    char weapon_usage[OPTION_WEAPON][CHMAX];
    char potion_usage[OPTION_POTION][CHMAX];
    char shield_usage[OPTION_SHIELD][CHMAX];
    bool player_brule;
    bool player_dead;
    bool accept_name;
    int selected_inventaire;
    float tpsp[MAX_TPSP];
    bool inventaire;
    bool is_Ramasse;
    Object obj_ramasse;
    bool proche_tombe;
    bool rencontre_pnj;
    int quest_choice;
    int pnj_index;
    Particle Ramasse[20];
    int selected_coffre;
    bool open_treasure;
    //indice du coffre en train d'être ouvert
    int index_open;
    Image letters[26];
    Image levelMap[3];
    Mix_Chunk *effect[4];
    Mix_Music *sound[4];
    Image background[MAX_BACKGROUND];
    Image Potion[6];
    Image Potion_name[7];
    Image Shield[4];
    Image Shield_name[4];
    Image Arme[13];
    Image Arme_name[13];
    Image flamme[12];
    Image cursor[8];
};

struct Coffre
{
    bool open;
    //position du coffre
    Vec2 pos;
    //tableau des objets qu'il contient
    Object objects[MAX_OBJECTS_COFFRE];
    int nb_objets;
};

struct Monster
{
    int vie;
    Particle monster;
    Image im;
};

struct Frelons
{
    bool attaque;
    Monster frelons[MAX_FRELONS];
    int nb_frelons;
};

struct Settings
{
    //image du joueur
    int model_player;
    int volume;

    char profile_name[CHMAX];

};

struct Main_menu
{
    Animation flamme;
    Settings seting;
    Color background_color;
    Image im[4];
    int index_select;
};


struct World
{
    bool quit;
    Main_menu menu;
    float dt;
    char name[CHMAX];
    //tableau de coffres
    Coffre coffre_tab[MAX_COFFRE];

    //objets au sol
    Object spawn_object[MAX_SPAWN_OBJECT];
    int nb_spawn_object;
    int nb_coffres;
    Pnj pnj_tab[MAX_PNJ];
    int nb_pnj;
    Animation flamme;
    Animation joueur;
    Animation attaque;
    Animation cursor;
    Particle javelot;
    Frelons F;
    //tableau de 250 string
    string map[250];
    Decor decor;
    Personnage player;
    Image level_map;
    Image Arc[6];
    Image Attaque_Haut[6];
    Image Attaque_Droite[6];
    Image Attaque_Gauche[6];
    Image Attaque_Bas[6];
    Image haut[9];
    Image droite[9];
    Image gauche[9];
    Image bas[9];
};

//Menu.cpp
void Init_menu(Main_menu &M);
void display_menu(World W);
void update_menu(World &W);

//object.cpp
void effect_object(World &W);
Object AleaObject(World &W, int index);
bool JoueurAtteintCoffre(World &W);
void draw_coffre(World &W);
void draw_coffre_content(Coffre C);
void Place_coffre(World &W);
void set_image(World W, Object &object);
void init_objetSol(World &W);
void InitPartRamassage(World &W);
void draw_stars(World W);
void Ramasse_object(World &W);
void draw_inventaire(World W);
void draw_inventaire_selected(World W);
void draw_spawn_objects(World W);

//Animation.cpp
void player_animation(World &W);
void init_animation(World &W);
void cursor_animation(Animation &cursor);
void flamme_animation(Animation &flamme);
void player_attaque_epee(World &W);

//effect.cpp
void crepitement_bois(World &W);
void Monster_prend_degat(World &W);

//pnj.cpp
Pnj create_pnj(string name, Vec2 p, DIRECTION dir);
void Init_PNJ(World &W);
void draw_PNJ(World W);
void png_interact(World &W);
void quest_choice(World &W);

//Monster.cpp
void init_frelons(Frelons &F);
void update_frelons(Frelons &F);
void draw_frelond(Frelons F);
void frelond_attaque(World &W);
void follow_player(World &W);
void Monster_prend_degats(Monster &M, int degats);

//map.cpp
int init_map(World &W);
void read_map(World &W);


#endif //LIFAMI_GAME_WORLD_HPP
