#include <Grapic.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <string.h>
using namespace grapic;
using namespace std;

const int zoom=3; // Si on change le zoom, toutes les proportions restent les memes
const int DIMWX=zoom*157;
const int DIMWY=zoom*284; // Taille de la table de billard en cm augmentee
const int MAX_PART=16; // Nombre maximale de boules
const int taille_particle=zoom*3; // Boules de 6 centimètres de diamètre
const int taille_bordure=zoom*15; // Taille de la bordure en bois et de la bordure en feutre
const int taille_trou=zoom*6; // Trous de 12 cm de diametre
const int taille_queue=zoom*147; // Queues de 147 cm
const int diametre_queue=zoom*3.7; // Diametre de la queue

//Parametres modifiables
const float FRICTION=0.35f; // Ralentissement lors de collision avec un mur
const float FRICTION_LAINE=8.0f; // Frottement de la laine sur la boule
const float FRICTION_CHOC=0.9f; // Perte de vitesse lors de collision entre boules
const float MAX_FORCE_CASSE=1000; // Force maximale de tir de casse
const float MAX_FORCE=600; // Force maximale de tir classique




/* Creation des vecteurs et des fonctions associees */

struct Vec2
{
    float x,y;
};

Vec2 make_Vec2(float x, float y) //Creation d'un veccteur
{
     Vec2 v;
     v.x=x;
     v.y=y;
     return v;
}

Vec2 make_Vec2_exp(float r, float theta) //Creation d'un vecteur exponentiel (utilise pour la rotation)
{
    return make_Vec2(r*cos(theta),r*sin(theta));
}

Vec2 operator+(Vec2 a, Vec2 b) //Ajout de deux vecteurs
{
    Vec2 v;
    v.x=a.x+b.x;
    v.y=a.y+b.y;
    return v;
}

Vec2 operator-(Vec2 a, Vec2 b) //Soustraction de deux vecteurs
{
    Vec2 v;
    v.x=a.x-b.x;
    v.y=a.y-b.y;
    return v;
}

Vec2 operator*(float lambda, Vec2 a) //Multiplication d'un scalaire et d'un vecteur
{
    Vec2 v;
    v.x=lambda*a.x;
    v.y=lambda*a.y;
    return v;
}

Vec2 operator*(Vec2 a, Vec2 b) //Multiplication de deux vecteurs
{
    Vec2 v;
    v.x=a.x*b.x-a.y*b.y;
    v.y=a.x*b.y+a.y*b.x;
    return v;
}

//Rotation d'un vecteur selon un angle theta en radians
Vec2 rotation(Vec2 v, float cx, float cy, float theta) // theta en radians
{
    Vec2 tr=make_Vec2(cx,cy);
    Vec2 r=make_Vec2_exp(1,theta);
    return (r*(v-tr)+tr);
}

float convert_rad_to_deg(float theta) // Conversion radians vers degres
{
    return (theta*180/M_PI);
}

float distance(Vec2 c, Vec2 x) // Distance entre deux positions
{
    return sqrt(pow(c.x-x.x,2)+pow(c.y-x.y,2));
}

float norme(Vec2 v) // Norme d'un vecteur
{
    return (sqrt(v.x*v.x+v.y*v.y));
}

Vec2 normalise(Vec2 v) // Normalisation d'un vecteur
{
    float n=norme(v);
    if(n!=0)
    {
        v.x=v.x/n;
        v.y=v.y/n;
    }
    return v;
}




/* Structure du jeu */

struct Particle // Structure des boules de billard
{
    Vec2 p,v,f_frottement; // Position, vitesse, forces de frottements
    float m; // Masse de la boule
    int numero; // Mumero de la boule
    bool tombe; // Si la boule est tombee dans un trou ou non
    Image im; // Image de la boule
};

Particle part_init(Vec2 p, Vec2 v, float m) //Initialise une boule avec une vitesse, une position et une masse
{
    Particle part;
    part.p=p;
    part.v=v;
    part.f_frottement=make_Vec2(0,0);
    part.m=m;
    part.tombe=false;
    return part;
}

struct Trou // Trous dans lesquels peuvent tomber des boules
{
    Vec2 p; // Position du trou
};

struct Queue // Queue de billard
{
    Vec2 p; // position
    float angle; // angle en degres
    bool exist; // Si on utilise la queue ou non
    Image im_queue; // Image de la queue
};

struct World // Table de billard, avec les boules, les trous et la queue
{
    int n; // Nombre de boules
    Particle T[MAX_PART]; // Boules de billard
    Trou trou[6]; // Tableau de 6 trous
    Queue Q; // Queue du billard
    int joueur; // N° du joueur courant pour le billard americain
    int score_1, score_2; // Scores respectifs (nombre de boules rentrees) des joueurs 1 et 2 dans le billard americain
    int Score; // Score du joueur (jeu de la 15)
    int nb_tirs; // Nombre de tirs effectues
    int jeu_choisi; // Le n° du jeu choisi : 0 = jeu de la 15, 1 = jeu de la 9, 2 = billard americain
    int premier_touche; // Le n° de la premiere boule touchee (pour le jeu de la 9)
    bool touche; // Si la premiere boule a deja ete touchee (pour le jeu de la 9)
    float murs_obliques [12][5]; //Un tableau de murs obliques contenant, pour chaque mur : x_debut, y_debut, x_fin, y_fin, orientation (1 = en haut a gauche, 2 = en haut a droite, 3 = en bas a gauche et 4 = en bas a droite)
    Image table_billard;
};




/* Initialisations */

void init_murs_obliques(World & w) // Coordonnees des murs obliques (entree des poches)
{
    w.murs_obliques[0][0]=taille_bordure; // Mur bas poche gauche
    w.murs_obliques[0][1]=DIMWY/2-taille_trou-2*zoom;
    w.murs_obliques[0][2]=taille_bordure/2;
    w.murs_obliques[0][3]=DIMWY/2-taille_trou;
    w.murs_obliques[0][4]=3;
    w.murs_obliques[1][0]=taille_bordure/2; // Mur haut poche gauche
    w.murs_obliques[1][1]=DIMWY/2+taille_trou;
    w.murs_obliques[1][2]=taille_bordure;
    w.murs_obliques[1][3]=DIMWY/2+taille_trou+2*zoom;
    w.murs_obliques[1][4]=1;
    w.murs_obliques[2][0]=DIMWX-taille_bordure; // Mur bas poche droite
    w.murs_obliques[2][1]=DIMWY/2-taille_trou-2*zoom;
    w.murs_obliques[2][2]=DIMWX-taille_bordure/2;
    w.murs_obliques[2][3]=DIMWY/2-taille_trou;
    w.murs_obliques[2][4]=4;
    w.murs_obliques[3][0]=DIMWX-taille_bordure/2; // Mur haut poche droite
    w.murs_obliques[3][1]=DIMWY/2+taille_trou;
    w.murs_obliques[3][2]=DIMWX-taille_bordure;
    w.murs_obliques[3][3]=DIMWY/2+taille_trou+2*zoom;
    w.murs_obliques[3][4]=2;
    w.murs_obliques[4][0]=taille_bordure; // Mur bas poche bas gauche
    w.murs_obliques[4][1]=taille_bordure/2;
    w.murs_obliques[4][2]=taille_bordure+taille_trou+2*zoom;
    w.murs_obliques[4][3]=taille_bordure;
    w.murs_obliques[4][4]=4;
    w.murs_obliques[5][0]=taille_bordure/2; // Mur haut poche bas gauche
    w.murs_obliques[5][1]=taille_bordure;
    w.murs_obliques[5][2]=taille_bordure;
    w.murs_obliques[5][3]=taille_bordure+taille_trou+2*zoom;
    w.murs_obliques[5][4]=1;
    w.murs_obliques[6][0]=DIMWX-taille_bordure; // Mur bas poche bas droite
    w.murs_obliques[6][1]=taille_bordure/2;
    w.murs_obliques[6][2]=DIMWX-taille_bordure-taille_trou-2*zoom;
    w.murs_obliques[6][3]=taille_bordure;
    w.murs_obliques[6][4]=3;
    w.murs_obliques[7][0]=DIMWX-taille_bordure/2; // Mur haut poche bas droite
    w.murs_obliques[7][1]=taille_bordure;
    w.murs_obliques[7][2]=DIMWX-taille_bordure;
    w.murs_obliques[7][3]=taille_bordure+taille_trou+2*zoom;
    w.murs_obliques[7][4]=2;
    w.murs_obliques[8][0]=taille_bordure; // Mur bas poche haut gauche
    w.murs_obliques[8][1]=DIMWY-taille_bordure-taille_trou-2*zoom;
    w.murs_obliques[8][2]=taille_bordure/2;
    w.murs_obliques[8][3]=DIMWY-taille_bordure;
    w.murs_obliques[8][4]=3;
    w.murs_obliques[9][0]=taille_bordure+taille_trou+2*zoom; // Mur haut poche haut gauche
    w.murs_obliques[9][1]=DIMWY-taille_bordure;
    w.murs_obliques[9][2]=taille_bordure;
    w.murs_obliques[9][3]=DIMWY-taille_bordure/2;
    w.murs_obliques[9][4]=2;
    w.murs_obliques[10][0]=DIMWX-taille_bordure; // Mur bas poche haut droite
    w.murs_obliques[10][1]=DIMWY-taille_bordure-taille_trou-2*zoom;
    w.murs_obliques[10][2]=DIMWX-taille_bordure/2;
    w.murs_obliques[10][3]=DIMWY-taille_bordure;
    w.murs_obliques[10][4]=4;
    w.murs_obliques[11][0]=DIMWX-taille_bordure-taille_trou-2*zoom; // Mur haut poche haut droite
    w.murs_obliques[11][1]=DIMWY-taille_bordure;
    w.murs_obliques[11][2]=DIMWX-taille_bordure;
    w.murs_obliques[11][3]=DIMWY-taille_bordure/2;
    w.murs_obliques[11][4]=1;
}

void place_jeu_de_la_15(World & w) // Place les boules en triangle : pour le jeu de la 15 et le billard americain
{
    w.n=16; // 15 boules plus la blanche
    w.T[1]=part_init(make_Vec2(zoom*79,zoom*200),make_Vec2(0,0),1.0f); // Placement de chaque boule individuellement
    w.T[3]=part_init(make_Vec2(zoom*79-taille_particle,zoom*200+2*taille_particle),make_Vec2(0,0),1.0f);
    w.T[10]=part_init(make_Vec2(zoom*79+taille_particle,zoom*200+2*taille_particle),make_Vec2(0,0),1.0f);
    w.T[14]=part_init(make_Vec2(zoom*79-2*taille_particle,zoom*200+4*taille_particle),make_Vec2(0,0),1.0f);
    w.T[8]=part_init(make_Vec2(zoom*79,zoom*200+4*taille_particle),make_Vec2(0,0),1.0f);
    w.T[5]=part_init(make_Vec2(zoom*79+2*taille_particle,zoom*200+4*taille_particle),make_Vec2(0,0),1.0f);
    w.T[2]=part_init(make_Vec2(zoom*79-3*taille_particle,zoom*200+6*taille_particle),make_Vec2(0,0),1.0f);
    w.T[11]=part_init(make_Vec2(zoom*79-taille_particle,zoom*200+6*taille_particle),make_Vec2(0,0),1.0f);
    w.T[7]=part_init(make_Vec2(zoom*79+taille_particle,zoom*200+6*taille_particle),make_Vec2(0,0),1.0f);
    w.T[15]=part_init(make_Vec2(zoom*79+3*taille_particle,zoom*200+6*taille_particle),make_Vec2(0,0),1.0f);
    w.T[13]=part_init(make_Vec2(zoom*79-4*taille_particle,zoom*200+8*taille_particle),make_Vec2(0,0),1.0f);
    w.T[6]=part_init(make_Vec2(zoom*79-2*taille_particle,zoom*200+8*taille_particle),make_Vec2(0,0),1.0f);
    w.T[12]=part_init(make_Vec2(zoom*79,zoom*200+8*taille_particle),make_Vec2(0,0),1.0f);
    w.T[9]=part_init(make_Vec2(zoom*79+2*taille_particle,zoom*200+8*taille_particle),make_Vec2(0,0),1.0f);
    w.T[4]=part_init(make_Vec2(zoom*79+4*taille_particle,zoom*200+8*taille_particle),make_Vec2(0,0),1.0f);
    w.T[0]=part_init(make_Vec2(zoom*79,zoom*100),make_Vec2(0,0),1.0f);
}

void place_jeu_de_la_9(World & w) // Place les boules en losange : pour le jeu de la 9
{
    w.n=10; // 9 boules plus la blanche
    w.T[1]=part_init(make_Vec2(zoom*79,zoom*200),make_Vec2(0,0),1.0f); // Placement de chaque boule individuellement
    w.T[8]=part_init(make_Vec2(zoom*79-taille_particle,zoom*200+2*taille_particle),make_Vec2(0,0),1.0f);
    w.T[2]=part_init(make_Vec2(zoom*79+taille_particle,zoom*200+2*taille_particle),make_Vec2(0,0),1.0f);
    w.T[7]=part_init(make_Vec2(zoom*79-2*taille_particle,zoom*200+4*taille_particle),make_Vec2(0,0),1.0f);
    w.T[9]=part_init(make_Vec2(zoom*79,zoom*200+4*taille_particle),make_Vec2(0,0),1.0f);
    w.T[3]=part_init(make_Vec2(zoom*79+2*taille_particle,zoom*200+4*taille_particle),make_Vec2(0,0),1.0f);
    w.T[6]=part_init(make_Vec2(zoom*79-taille_particle,zoom*200+6*taille_particle),make_Vec2(0,0),1.0f);
    w.T[4]=part_init(make_Vec2(zoom*79+taille_particle,zoom*200+6*taille_particle),make_Vec2(0,0),1.0f);
    w.T[5]=part_init(make_Vec2(zoom*79,zoom*200+8*taille_particle),make_Vec2(0,0),1.0f);
    w.T[0]=part_init(make_Vec2(zoom*79,zoom*100),make_Vec2(0,0),1.0f);
}

void init(World & w) // Initialise le jeu
{
    char chaine[40]; // Pour le chemin vers l'image
    int i;
    if (w.jeu_choisi==1) // Si c'est le jeu de la 9
    {
        place_jeu_de_la_9(w);
    }
    else // Si c'est le jeu de la 15 ou le billard americain
    {
        place_jeu_de_la_15(w);
    }
    for(i=0;i<w.n;i++) // On ajoute le numero et l'image a chaque boule
    {
        strcpy(chaine,"data/billard/bille_"); // Chemin de base vers l'image, auquel on ajoute le numero de la boule
        char c[3]; // Chaine de caracteres du numero de la boule
        if (i<10)
        {
            c[0]=i+'0';
            c[1]='\0';
        }
        else
        {
            c[0]='1';
            c[1]=(i-10)+'0';
            c[2]='\0';
        }
        strcat(chaine,c); // Ajout du numero de la boule
        strcat(chaine,".png"); // Ajout de l'extension
        w.T[i].numero=i; // Ajout du numero a la boule (dans l'ordre de creation)
        w.T[i].im=image(chaine,255,255,255,255,255); // Ajout de l'image à la boule
    }
    w.T[0].numero=-10; // Car on perd dix points lorsque la boule blanche tombe (dans le jeu de la 15)
    w.trou[0].p=make_Vec2(taille_bordure/1.2,taille_bordure/1.2); // Place les trous
    w.trou[1].p=make_Vec2(DIMWX-taille_bordure/1.2,taille_bordure/1.2);
    w.trou[2].p=make_Vec2(taille_bordure/1.2,DIMWY-taille_bordure/1.2);
    w.trou[3].p=make_Vec2(DIMWX-taille_bordure/1.2,DIMWY-taille_bordure/1.2);
    w.trou[4].p=make_Vec2(taille_bordure/2,DIMWY/2); // 25 au lieu de 45
    w.trou[5].p=make_Vec2(DIMWX-taille_bordure/2,DIMWY/2);
    w.Q.p=make_Vec2(0,0); // Initialisation de la queue
    w.Q.angle=0;
    w.Q.exist=false;
    w.Q.im_queue=image("data/billard/queue_billard.png",255,255,255,255);
    w.Score=0; // Initialisation des autres parametres
    w.nb_tirs=0;
    w.touche=false;
    w.premier_touche=1;
    w.score_1=0;
    w.score_2=0;
    w.joueur=1;
    init_murs_obliques(w);
    w.table_billard=image("data/billard/table_billard.png",255,255,255,255);
}





/* Dessin du jeu */

void draw(World w) //Dessine les boules et la queue
{
    image_draw(w.table_billard,0,0,DIMWX,DIMWY); // Dessine la table de billard
    for (int i=0;i<w.n;i++) // Dessin des boules
    {
        if(w.T[i].tombe==false)
        {
            image_draw(w.T[i].im,w.T[i].p.x-taille_particle,w.T[i].p.y-taille_particle,2*taille_particle,2*taille_particle); // Affiche l'image de la boule
        }
    }
    color(255,255,0); // Affichage du score, du nombre de tirs, du joueur courant
    fontSize(zoom*(20/3));
    if (w.jeu_choisi==0) // Score pour le jeu de la 15
    {
        print(zoom*(200/3),DIMWY-zoom*(25/3),"Score :"); // Affichage du score
        print(zoom*(265/3),DIMWY-zoom*(25/3),w.Score);
    }
    if (w.jeu_choisi!=2) // On n'affiche pas le nombre de tirs dans le billard americain
    {
        print(zoom*(10/3),DIMWY-zoom*(25/3),"Nombre de tirs :"); // Affichage du nombre de tirs
        print(zoom*(155/3),DIMWY-zoom*(25/3),w.nb_tirs);
    }
    else // Parametres du billard americain
    {
        print(zoom*(10/3),DIMWY-zoom*(25/3),"Joueur ");
        print(zoom*(80/3),DIMWY-zoom*(25/3),w.joueur);
        print(zoom*(130/3),DIMWY-zoom*(25/3),"Joueur 1 :");
        print(zoom*(225/3),DIMWY-zoom*(25/3),w.score_1);
        print(zoom*(260/3),DIMWY-zoom*(25/3),"Joueur 2 :");
        print(zoom*(355/3),DIMWY-zoom*(25/3),w.score_2);

    }
    if(w.Q.exist==true) // Dessine la queue et la ligne de tir
    {
        color(255,255,0);
        line(w.T[0].p.x,w.T[0].p.y,w.T[0].p.x+DIMWY*sin(w.Q.angle),w.T[0].p.y+DIMWY*cos(w.Q.angle)); // Dessin de la ligne de tir
        image_draw(w.Q.im_queue,w.Q.p.x,w.Q.p.y,diametre_queue,taille_queue,convert_rad_to_deg(w.Q.angle),0); // Dessin de la queue
    }
}

void draw_menu() // Dessin du menu principal
{
    color(144,111,74); // Rectangles interieurs
    rectangleFill(zoom*30,zoom*240,zoom*130,zoom*270);
    rectangleFill(zoom*30,zoom*190,zoom*130,zoom*220);
    rectangleFill(zoom*30,zoom*140,zoom*130,zoom*170);
    color(0,0,0); // Bordures
    rectangle(zoom*30,zoom*240,zoom*130,zoom*270);
    rectangle(zoom*30,zoom*190,zoom*130,zoom*220);
    rectangle(zoom*30,zoom*140,zoom*130,zoom*170);
    fontSize(zoom*(35/3)); // Ecritures
    print(zoom*47,zoom*247,"Jeu de la 15");
    print(zoom*50,zoom*197,"Jeu de la 9");
    print(zoom*36,zoom*147,"Billard americain");
    int x,y;
    mousePos(x,y);
    if (x>=zoom*30 && x<=zoom*130 && y>=zoom*240 && y<=zoom*270) //Affichage des regles du jeu de la 15
    {
        color(207,154,94);
        rectangleFill(zoom*30,zoom*240,zoom*130,zoom*270);
        color(0,0,0);
        rectangle(zoom*30,zoom*240,zoom*130,zoom*270);
        print(zoom*47,zoom*247,"Jeu de la 15");
        fontSize(zoom*10);
        print(zoom*10,zoom*100,"Vous devez rentrer les boules");
        print(zoom*17,zoom*85,"a l'aide de la boule blanche.");
        print(zoom*10,zoom*70,"Chaque boule rentree apporte");
        print(zoom*30,zoom*55,"au score son numero.");
        print(zoom*10,zoom*40,"Vous devez atteindre le score");
        print(zoom*17,zoom*25,"61 avec le moins de coups");
        print(zoom*55,zoom*10,"possibles.");
    }
    else if (x>=zoom*30 && x<=zoom*130 && y>=zoom*190 && y<=zoom*220) // Affichage des regles du jeu de la 9
    {
        color(207,154,94);
        rectangleFill(zoom*30,zoom*190,zoom*130,zoom*220);
        color(0,0,0);
        rectangle(zoom*30,zoom*190,zoom*130,zoom*220);
        print(zoom*50,zoom*197,"Jeu de la 9");
        fontSize(zoom*10);
        print(zoom*10,zoom*100,"Vous devez rentrer les boules");
        print(zoom*17,zoom*85,"a l'aide de la boule blanche");
        print(zoom*10,zoom*70,"en tapant le plus petit numero.");
        print(zoom*10,zoom*55,"Vous devez rentrer la derniere");
        print(zoom*10,zoom*40,"boule avec le moins de coups");
        print(zoom*55,zoom*25,"possibles.");
    }
    else if (x>=zoom*30 && x<=zoom*130 && y>=zoom*140 && y<=zoom*170) // Affichage des regles du billard americain
    {
        color(207,154,94);
        rectangleFill(zoom*30,zoom*140,zoom*130,zoom*170);
        color(0,0,0);
        rectangle(zoom*30,zoom*140,zoom*130,zoom*170);
        print(zoom*36,zoom*147,"Billard americain");
        fontSize(zoom*10);
        print(zoom*35,zoom*100,"Vous jouez a deux.");
        print(zoom*20,zoom*85,"L'un doit rentrer toutes les");
        print(zoom*22,zoom*70,"boules pleines, l'autre les");
        print(zoom*21,zoom*55,"rayees. La boule noire doit");
        print(zoom*30,zoom*40,"etre rentree en dernier.");
    }
}



/* Mises a jour et verification */

void part_update(Particle & part, float dt) // Met a jour la vitesse et la position des particules
{
    if (abs(part.v.x)<1 && abs(part.v.y)<1) // Si la vitesse est faible, on l'annule et il n'y a plus de forces de frottements
    {
        part.v.x=0;
        part.v.y=0;
        part.f_frottement=make_Vec2(0,0);
    }
    else
    {
            Vec2 frottement=normalise(part.v); // Les forces de frottement dependent de la direction de la vitesse de la boule
            part.f_frottement=-FRICTION_LAINE*frottement; // la force de frottement est constante dans le sens inverse de la vitesse
    }
    if (part.tombe==false) // On ne met a jour que si la boule n'est pas tombee
    {
        part.p=part.p+dt*part.v; // Nouvelle position
        part.v=part.v+(dt/part.m)*(part.f_frottement); // Nouvelle vitesse
    }
    else
    {
        part.p=make_Vec2(0,0); // On met a 0 la position et la vitesse si la boule est tombee
        part.v=make_Vec2(0,0);
    }
}

void verif_murs(Particle& part) // Collision avec les bords de la table
{
    if (part.tombe==false)
    {
        //Collision a gauche : on verifie egalement que la boule n'est pas dans une des poches ; les +/- taille_particule/2 sont des arrondis au niveau des angles
        if (part.p.x<taille_bordure+taille_particle && ((part.p.y>taille_bordure+taille_trou+2*zoom && part.p.y<DIMWY/2-taille_trou-2*zoom+taille_particle/2) || (part.p.y>DIMWY/2+taille_trou+2*zoom-taille_particle/2 && part.p.y<DIMWY-taille_bordure-taille_trou-2*zoom)))
        {
            part.p.x=2*taille_bordure+2*taille_particle-part.p.x; // On remet la boule hors du mur
            part.v.x=-part.v.x; // On prend le "symetrique" de la vitesse par rapport au mur
            part.v=part.v-make_Vec2(part.v.x*FRICTION,part.v.y*FRICTION); // La vitesse de la boule diminue lors d'une collision
        }
        //Collision a droite
        if (part.p.x>DIMWX-taille_bordure-taille_particle && ((part.p.y>taille_bordure+taille_trou+2*zoom && part.p.y<DIMWY/2-taille_trou-2*zoom+taille_particle/2) || (part.p.y>DIMWY/2+taille_trou+2*zoom -taille_particle/2&& part.p.y<DIMWY-taille_bordure-taille_trou-2*zoom)))
        {
            part.p.x=2*DIMWX-2*taille_particle-2*taille_bordure-part.p.x;
            part.v.x=-part.v.x;
            part.v=part.v-make_Vec2(part.v.x*FRICTION,part.v.y*FRICTION);
        }
        // Collision en bas
        if (part.p.y<taille_bordure+taille_particle && part.p.x>taille_bordure+taille_trou+2*zoom-taille_particle/2 && part.p.x<DIMWX-taille_bordure-taille_trou-2*zoom+taille_particle/2)
        {
            part.p.y=2*taille_bordure+2*taille_particle-part.p.y;
            part.v.y=-part.v.y;
            part.v=part.v-make_Vec2(part.v.x*FRICTION,part.v.y*FRICTION);
        }
        // Collision en haut
        if (part.p.y>DIMWY-taille_bordure-taille_particle && part.p.x>taille_bordure+taille_trou+2*zoom-taille_particle/2 && part.p.x<DIMWX-taille_bordure-taille_trou-2*zoom+taille_particle/2)
        {
            part.p.y=2*DIMWY-2*taille_particle-2*taille_bordure-part.p.y;
            part.v.y=-part.v.y;
            part.v=part.v-make_Vec2(part.v.x*FRICTION,part.v.y*FRICTION);
        }
    }
}

void verif_murs_obliques(Particle& part, World w) // Collisions sur les murs obliques (au niveau des poches)
{
    for(int i=0;i<12;i++)
    {
        float a=(w.murs_obliques[i][3]-w.murs_obliques[i][1])/(w.murs_obliques[i][2]-w.murs_obliques[i][0]); // Coefficient directeur de la droite representant le mur
        float b=w.murs_obliques[i][1]-a*w.murs_obliques[i][0]; // Ordonnee a l'origine de la droite representant le mur
        float angle;
        if(w.murs_obliques[i][4]==1 || w.murs_obliques[i][4]==4) // Selon l'orientation du mur
        {
            angle=M_PI/2-atan(a); // Angle de contact entre l'horizontale et la droite passant par le centre de la boule et perpendiculaire au mur
        }
        else
        {
            angle=M_PI/2-atan(-a);
        }
        Vec2 point_contact; // Point de la surface de la boule qui touche
        switch(int(w.murs_obliques[i][4])) // Ce point de contact est different selon l'orientation du mur
        {
            case 1 : point_contact=make_Vec2(part.p.x-cos(angle)*taille_particle,part.p.y+sin(angle)*taille_particle);
                break;
            case 2 : point_contact=make_Vec2(part.p.x+cos(angle)*taille_particle,part.p.y+sin(angle)*taille_particle);
                break;
            case 3 : point_contact=make_Vec2(part.p.x-cos(angle)*taille_particle,part.p.y-sin(angle)*taille_particle);
                break;
            case 4 : point_contact=make_Vec2(part.p.x+cos(angle)*taille_particle,part.p.y-sin(angle)*taille_particle);
                break;
        }
        Vec2 point_droite; // Point de la droite que la boule touche
        point_droite.x=(point_contact.x+(point_contact.y-b)*a)/(1+a*a); //projete orthogonal de point_contact sur la droite
        point_droite.y=a*point_droite.x+b;
        Vec2 ecart=point_contact-point_droite; //Distance avec laquelle la boule est rentree avec le mur
        switch(int(w.murs_obliques[i][4])) // Les formules de changement de la vitesse ne sont pas les memes selon l'orientation du mur
        {
            //On verifie si la boule passe a travers le mur et si elle est au niveau de ce mur (dans le rectangle delimite par la droite ; les +/-taille_particle/2 sont des arrondis au niveau des angles
            case 1 : if(point_contact.y>=a*point_contact.x+b && point_contact.x>=w.murs_obliques[i][0]-taille_particle/2 && point_contact.x<=w.murs_obliques[i][2]+taille_particle/2 && point_contact.y>=w.murs_obliques[i][1]-taille_particle/2 && point_contact.y<=w.murs_obliques[i][3]+taille_particle/2)
                {
                    part.p=part.p-2*ecart; //Replacement de la boule hors du mur
                    float angle_vitesse=acos((part.v.x+a*part.v.y)/(norme(part.v)*(1+a*a))); // Angle (positif) entre la droite et le vecteur vitesse
                    if(angle_vitesse<=M_PI/2) // Selon le cote d'ou arrive la boule
                    {
                        part.v=rotation(part.v,0,0,-2*((M_PI/2)-angle)); //Symetrique du vecteur vitesse par rapport a la droite allant de la boule au mur
                    }
                    else
                    {
                        part.v=rotation(part.v,0,0,2*((M_PI/2)-angle));
                    }
                    part.v=part.v-make_Vec2(part.v.x*FRICTION,part.v.y*FRICTION); // Ralentissement de la boule apres la collision
                }
                break;
            case 2 : if(point_contact.y>=a*point_contact.x+b && point_contact.x>=w.murs_obliques[i][2]-taille_particle/2 && point_contact.x<=w.murs_obliques[i][0]+taille_particle/2 && point_contact.y>=w.murs_obliques[i][1]-taille_particle/2 && point_contact.y<=w.murs_obliques[i][3]+taille_particle/2)
                {
                    part.p=part.p-2*ecart; // Replacement de la boule hors du mur
                    float angle_vitesse=acos((part.v.x+a*part.v.y)/(norme(part.v)*(1+a*a))); // Angle (positif) entre la droite et le vecteur vitesse
                    if(angle_vitesse<=M_PI/2)
                    {
                        part.v=rotation(part.v,0,0,-2*((M_PI/2)-angle)); // Symetrique du vecteur vitesse par rapport a la droite allant de la boule au mur
                    }
                    else
                    {
                        part.v=rotation(part.v,0,0,2*((M_PI/2)-angle));
                    }
                    part.v=part.v-make_Vec2(part.v.x*FRICTION,part.v.y*FRICTION); // Ralentissement de la boule apres la collision
                }
                break;
            case 3 : if((point_contact.y<=a*point_contact.x+b) && point_contact.x>=w.murs_obliques[i][2]-taille_particle/2 && point_contact.x<=w.murs_obliques[i][0]+taille_particle/2 && point_contact.y>=w.murs_obliques[i][1]-taille_particle/2 && point_contact.y<=w.murs_obliques[i][3]+taille_particle/2)
                {
                    part.p=part.p-2*ecart; // Replacement de la boule hors du mur
                    float angle_vitesse=acos((part.v.x+a*part.v.y)/(norme(part.v)*(1+a*a))); // Angle (positif) entre la droite et le vecteur vitesse
                    if(angle_vitesse<=M_PI/2)
                    {
                        part.v=rotation(part.v,0,0,2*((M_PI/2)-angle)); // Symetrique du vecteur vitesse par rapport a la droite allant de la boule au mur
                    }
                    else
                    {
                        part.v=rotation(part.v,0,0,-2*((M_PI/2)-angle));
                    }
                    part.v=part.v-make_Vec2(part.v.x*FRICTION,part.v.y*FRICTION); // Ralentissement de la boule apres la collision
                }
                break;
            case 4 : if(point_contact.y<=a*point_contact.x+b && part.p.x>=w.murs_obliques[i][0]-taille_particle/2 && point_contact.x<=w.murs_obliques[i][2]+taille_particle/2 && point_contact.y>=w.murs_obliques[i][1]-taille_particle/2 && point_contact.y<=w.murs_obliques[i][3]+taille_particle/2)
                {
                    part.p=part.p-2*ecart; // Replacement de la boule hors du mur
                    float angle_vitesse=acos((part.v.x+a*part.v.y)/(norme(part.v)*(1+a*a))); // Angle (positif) entre la droite et le vecteur vitesse
                    if(angle_vitesse<=M_PI/2)
                    {
                        part.v=rotation(part.v,0,0,2*((M_PI/2)-angle)); // Symetrique du vecteur vitesse par rapport a la droite allant de la boule au mur
                    }
                    else
                    {
                        part.v=rotation(part.v,0,0,-2*((M_PI/2)-angle));
                    }
                    part.v=part.v-make_Vec2(part.v.x*FRICTION,part.v.y*FRICTION); // Ralentissement de la boule après la collision
                }
                break;
        }
    }
}

void verif_collision(Particle& p1, Particle& p2, World& w) // Gère les collisions entre boules
{
    if(p2.tombe==false) //Les boules encore sur le tapis ne calculent pas les collisions avec les boules tombees
    {
        float d=distance(p1.p,p2.p); // Distance entre les deux boules
        float e=2*taille_particle-d; // Ecart entre les bords des deux boules
        if(d<=2*taille_particle) // Si les deux boules se touchent
        {
            if (w.touche==false && p1.numero==-10) // Pour determiner quelle est la premiere boule touchee par la blanche
            {
                w.premier_touche=p2.numero; // On a le numero de la premiere boule touchee par la blanche
                w.touche=true; //La premiere boule est touchee, on ne change plus ce numero
            }
            if (p1.p.x==p2.p.x) // Si le front de collision est vertical (on ne peut pas calculer le coefficient directeur de la droite)
            {
                if(p1.p.y>p2.p.y) // Replacement de la boule si la premiere est au-dessus de la deuxieme
                {
                    p1.p.y=p1.p.y+e/2;
                    p2.p.y=p1.p.y-e/2;
                }
                else // Replacement de la boule si la deuxieme est au-dessus
                {
                    p1.p.y=p1.p.y-e/2;
                    p2.p.y=p2.p.y+e/2;
                }
            }
            else
            {
                float a=(p2.p.y-p1.p.y)/(p2.p.x-p1.p.x); // Coefficient directeur de la droite qui relie les deux boules
                if (p1.p.x>p2.p.x) // Replacement des boules si la premiere est a droite de la deuxieme
                {
                    p1.p.x=p1.p.x+e/(2*sqrt(a*a+1));
                    p1.p.y=p1.p.y+a*e/(2*sqrt(a*a+1));
                    p2.p.x=p2.p.x-e/(2*sqrt(a*a+1));
                    p2.p.y=p2.p.y-a*e/(2*sqrt(a*a+1));
                }
                else // Replacement des boules si la deuxieme est a droite de la premiere
                {
                    p1.p.x=p1.p.x-e/(2*sqrt(a*a+1));
                    p1.p.y=p1.p.y-a*e/(2*sqrt(a*a+1));
                    p2.p.x=p2.p.x+e/(2*sqrt(a*a+1));
                    p2.p.y=p2.p.y+a*e/(2*sqrt(a*a+1));
                }
            }
            Vec2 v1=p1.v,v2=p2.v; // On sauvegarde les vitesses initiales des deux boules
            Vec2 u=p2.p-p1.p; // Segment qui relie les deux boules
            p1.v.x=(v2.y*u.y*u.x-v1.y*u.y*u.x+u.y*u.y*v1.x+u.x*u.x*v2.x)/(u.x*u.x+u.y*u.y); // Choc elastique : conservation de la vitesse tangentielle
            p1.v.y=(v2.y*u.y*u.y+u.y*v2.x*u.x-u.x*v1.x*u.y+u.x*u.x*v1.y)/(u.x*u.x+u.y*u.y);
            p2.v.x=(u.x*u.x*v1.x-v2.y*u.y*u.x+v1.y*u.y*u.x+u.y*u.y*v2.x)/(u.x*u.x+u.y*u.y);
            p2.v.y=(u.x*v1.x*u.y+v1.y*u.y*u.y-u.y*v2.x*u.x+u.x*u.x*v2.y)/(u.x*u.x+u.y*u.y);
            p1.v=FRICTION_CHOC*p1.v;
            p2.v=FRICTION_CHOC*p2.v;
        }
    }
}

void verif_trou(World& w, Particle& part) // Verifie si une boule tombe dans un trou
{
    float d; // distance entre le trou et la boule
    for(int i=0;i<6;i++) // On regarde pour chaque trou
    {
        d=distance(part.p,w.trou[i].p);
        if(d<taille_trou) // Si la moitie de la boule est dans le trou (donc si le centre de la boule est au bord du trou : distance du rayon du trou entre les deux)
        {
            part.tombe=true; // La boule est tombee
            part.p=make_Vec2(0,0); // On lui affecte une position qui ne genera pas les autres boules
            part.v=make_Vec2(0,0); // On annule sa vitesse
            w.Score+=part.numero; // On augmente le score
            if(part.numero>0 && part.numero<8)
            {
                w.score_1++; //Si une boule non-rayee tombe, le score du joueur 1 augmente (pas pour la boule 8 !)
            }
            if(part.numero>8)
            {
                w.score_2++; //Si une boule rayee tombe, le score du joueur 2 augmente (pas pour la boule 8 !)
            }
        }
    }
}

void update(World& w, float dt) // Met à jour la vitesse et la position de la particule, verifie les murs, les collisions et les trous
{
    for(int i=0;i<w.n;i++)
    {
        if (w.T[i].tombe==false) // On ne change les caracteristiques que des boules sur le tapis
        {
            part_update(w.T[i],dt); // On change la vitesse, les forces et la position
            verif_trou(w,w.T[i]); // On verifie si elles tombent dans les trous
            verif_murs_obliques(w.T[i],w); // On verifie les collisions avec les murs obliques (poches)
            verif_murs(w.T[i]); // On verifie les collisions avec les murs
            for(int j=i+1;j<w.n;j++)
            {
                verif_collision(w.T[i],w.T[j],w); // On verifie les collisions entre elles
            }
        }
    }
}




/* Autres fonctions */

void place_blanche(World & w) // Pour placer la boule blanche
{
    color(0,0,0);
    line(taille_bordure,zoom*79,DIMWX-taille_bordure,zoom*79); // Limite de la zone de placement (zone de casse)
    int x,y;
    mousePos(x,y); // On la place grace a la souris
    if (y<taille_bordure+taille_particle) // La boule ne peut pas sortir de la zone de placement : limite en bas
    {
        y=taille_bordure+taille_particle;
    }
    if(y>zoom*79-taille_particle) // Limite en haut (limite de la zone de casse)
    {
        y=zoom*79-taille_particle;
    }
    if(x<taille_bordure+taille_particle) // Limite a gauche
    {
        x=taille_bordure+taille_particle;
    }
    if(x>DIMWX-taille_bordure-taille_particle) // Limite a droite
    {
        x=DIMWX-taille_bordure-taille_particle;
    }
    w.T[0].p=make_Vec2(x,y); // La boule suit la souris (en restant dans la zone)
}

bool verifie_prochain_tour(World w) // On regarde si on peut tirer : toutes les boules doivent etre immobiles
{
    int i;
    for (i=0;i<w.n;i++)
    {
        if((w.T[i].v.x!=0 || w.T[i].v.y!=0) && (w.T[i].tombe==false)) // On ne regarde que les boules encore sur le tapis
        {
            return false;
        }
    }
    return true;
}

void init_queue(World& w) // On initialise la queue
{
        w.Q.p=w.T[0].p-make_Vec2(diametre_queue/2,zoom*(20/3)+taille_queue);
        w.Q.angle=0;
        w.Q.exist=true;
}

void tire_boule(World & w, bool& tire, bool& casse) // On choisit la force du tir et on tire sur la boule blanche
{
    float force; // Contiendra la force du tir
    color(0,0,0);
    rectangle(zoom*(55/3),zoom*(100/3),zoom*(85/3),zoom*(220/3)); // Pour voir la force
    if (casse==true) // Si on est sur le premier tir (tir de casse)
    {
        force=abs(cos(elapsedTime()))*MAX_FORCE_CASSE; // Le tir est plus puissant lors de la casse (la queue est plus lourde)
        color(255,0,0);
        rectangleFill(zoom*(60/3),zoom*(110/3),zoom*(80/3),zoom*(110/3)+(force/(MAX_FORCE_CASSE/100))*zoom/3); // On affiche la force actuelle dans le rectangle
    }
    else
    {
        force=abs(cos(elapsedTime()))*MAX_FORCE; // Le tir est moins puissant hors casse
        color(255,0,0);
        rectangleFill(zoom*(60/3),zoom*(110/3),zoom*(80/3),zoom*(110/3)+(force/(MAX_FORCE/100))*zoom/3);
    }
    float force_x=sin(w.Q.angle)*force; // On cree le vecteur vitesse de la boule blanche en fonction de l'angle de la queue et de la force choisie
    float force_y=cos(w.Q.angle)*force;
    if (!isMousePressed(SDL_BUTTON_LEFT)) // On tir en relachant le clic
    {
        w.T[0].v=make_Vec2(force_x*zoom/3,force_y*zoom/3); // On applique cette vitesse a la boule blanche
        tire=false;
        casse=false;
    }
}

int determine_plus_petit_numero(World w) // Determine le plus petit numero present sur la table (jeu de la 9)
{
    for (int i=1;i<w.n;i++)
    {
        if(w.T[i].tombe==false)
        {
            return i;
        }
    }
    return 0;
}

int main(int , char** )
{
    bool prepare_tire=false,OK_init_queue=true,tire=false,casse=true,menu_choisi=false; // prepare_tire : on peut regler l'angle de la queue ; OK_init_queue : on peut afficher la queue ; tire : on prepare la force du tire ; casse : le tir est celui de casse (premier tire) ; menu_choisi = on a choisi l'option de menu
    bool penalite_mise=false; // Pour savoir si la penaite a deja ete appliquee quand on touche la mauvaise boule ; au debut on ne peut pas encore mettre de penalite
    bool OK_change_joueur=false; // Indique si on peut changer le joueur courant
    Vec2 centre_queue, tr; // centre_queue : le centre de la queue ; tr : un vecteur de translation
    int x,y ; //coordonnées de la souris
    int plus_petite; // n° de la plus petite boule du terrain (hors boule 0)
    srand(time(NULL));
    World w;
    bool stop=false;
	winInit("Particles", DIMWX, DIMWY);
    setKeyRepeatMode(true);
	Menu m;
	menu_add(m,"Menu principal");
	menu_add(m,"Init jeu");
	menu_add(m,"Play jeu");
	menu_add(m,"Fin jeu");
	menu_add(m,"Partie perdue");
	backgroundColor(21,131,28);
	while( !stop )
    {
        winClear();
        switch (menu_select(m))
        {
            // Choix du jeu
            case 0 : draw_menu(); // Dessin du menu principal
                mousePos(x,y);
                if(isMousePressed(SDL_BUTTON_LEFT)) // On clique pour choisir le jeu
                {
                    if (x>=zoom*30 && x<=zoom*130 && y>=zoom*240 && y<=zoom*270) // Jeu de la 15
                    {
                        w.jeu_choisi=0;
                    }
                    else if (x>=zoom*30 && x<=zoom*130 && y>=zoom*190 && y<=zoom*220) // Jeu de la 9
                    {
                        w.jeu_choisi=1;
                    }
                    else if (x>=zoom*30 && x<=zoom*130 && y>=zoom*140 && y<=zoom*170) //Billard americain
                    {
                        w.jeu_choisi=2;
                    }
                    init(w); // On initialise le jeu
                    menu_setSelect(m,1); // On va a l'initialisation du jeu (placement de la bille blanche)
                }
                break;

            // Initiation du jeu (placement de la bille blanche : au debut ou quand elle est tombee)
            case 1 : //draw_table(w); // Dessine la table
                draw(w); // Dessine les boules et la queue
                if(!isMousePressed(SDL_BUTTON_LEFT))
                {
                    menu_choisi=true ; // on attend que la souris soit relachee avant de placer la bille blanche
                }
                place_blanche(w); // On place la boule blanche dans la zone de placement
                if(isMousePressed(SDL_BUTTON_LEFT) && menu_choisi==true) // On clique pour placer la boule
                {
                    OK_init_queue=true; // On peut afficher la queue
                    w.premier_touche=1; // On initialise le premier touche a 1 (pour le jeu de la 9)
                    menu_setSelect(m,2); // On passe au jeu
                }
                break;

            // Jeu
            case 2 : //draw_table(w); // Dessine la table
                draw(w); // Dessine les boules
                if(w.Score>=61 && w.jeu_choisi==0) // Condition pour gagner le jeu de la 15
                {
                    prepare_tire=false; // On ne peut pas tirer
                    tire=false;
                    OK_init_queue=false;
                    menu_setSelect(m,3); // On passe a l'affichage de la partie gagnante
                }
                if(w.T[9].tombe==true && w.jeu_choisi==1) //Condition pour gagner le jeu de la 9
                {
                    prepare_tire=false; // On ne peut pas tirer
                    tire=false;
                    OK_init_queue=false;
                    menu_setSelect(m,3); // On passe a l'affichage de la partie gagnante
                }
                if (w.T[8].tombe==true && w.score_1<7 && w.score_2<7 && w.jeu_choisi==2) // Si la boule 8 est tombee avant toutes les rayee ou toutes les pleines, la partie est perdue !
                {
                    prepare_tire=false; // On ne peut pas tirer
                    tire=false;
                    OK_init_queue=false;
                    menu_setSelect(m,4); // On passe a l'affichage de la partie perdue
                }
                else if(((w.score_1==7) || (w.score_2==7)) && w.T[8].tombe==true && w.jeu_choisi==2) // Condition pour finir le billard americain : la boule 8 doit etre tombee aussi
                {
                    prepare_tire=false; // On ne peut pas tirer
                    tire=false;
                    OK_init_queue=false;
                    menu_setSelect(m,3); // On passe a l'affichage de la partie gagnante
                }
                if(verifie_prochain_tour(w)==true && w.T[0].tombe==true) // Si la boule blanche est tombee, on doit la replacer
                {
                    prepare_tire=false; // On ne peut pas tirer
                    tire=false;
                    OK_init_queue=false;
                    w.touche=true; // On ne peut pas choisir de premiere boule a toucher
                    penalite_mise=true; // On ne peut pas mettre de penalite
                    w.premier_touche=1; // On initialise la premiere touchee
                    w.T[0].tombe=false; // On remet la boule blanche sur le tapis
                    if (w.jeu_choisi==1)
                    {
                        w.nb_tirs+=10; // On a une penalite de 10 coups si on fait tomber la boule blanche
                    }
                    menu_setSelect(m,1); // On replace la boule (initialisation)
                }
                if(verifie_prochain_tour(w)==true && w.T[0].tombe==false && OK_init_queue==true && OK_change_joueur==true) //Conditions pour changer de joueur
                {
                    if(w.joueur==1) // On passe a l'autre joueur
                    {
                        w.joueur=2;
                        OK_change_joueur=false; // On ne rechange plus le joueur
                    }
                    else
                    {
                        OK_change_joueur=false;
                        w.joueur=1;
                    }
                }
                if(verifie_prochain_tour(w)==true && OK_init_queue==true) // Les boules sont arretees et on peut tirer
                {
                    plus_petite=determine_plus_petit_numero(w); // On determine le plus petit numero avant de tirer
                    penalite_mise=false; // On peut a nouveau mettre la penalite
                    w.touche=false; // On peut a nouveau determiner la premiere boule touchee
                    init_queue(w); // On initialise la queue
                    if(!isMousePressed(SDL_BUTTON_LEFT)) // On verifie qu'on n'est pas en train de cliquer
                    {
                        prepare_tire=true; // On peut tirer
                        w.nb_tirs+=1; // On incrémente le nombre de tirs
                        OK_init_queue=false; // On ne revient plus ici
                    }
                }
                if(prepare_tire==true) // On prepare l'angle de tir
                {
                    mousePos(x,y); // On oriente la queue selon la position de la souris
                    float N=norme(make_Vec2(x,y)-w.T[0].p); //Distance entre la souris et la boule blanche
                    if(x==w.T[0].p.x && y==w.T[0].p.y) // Si on place la souris sur le centre de la boule
                    {
                        w.Q.angle=0; // On definit un angle arbitraire
                    }
                    if(x>=w.T[0].p.x)
                    {
                        w.Q.angle=acos((y-w.T[0].p.y)/N); // Angle en fonction de la position de la souris (souris a droite de la boule)
                    }
                    else
                    {
                        w.Q.angle=acos(-(y-w.T[0].p.y)/N)+M_PI; // Souris a gauche de la boule (car acos ne va qu'entre 0 et Pi, alors qu'on veut aller de 0 a 2*pi)
                    }
                    tr=make_Vec2(diametre_queue/2,taille_queue/2); //Vecteur translation vers le centre de la queue
                    centre_queue=w.Q.p+tr;
                    centre_queue.x=w.T[0].p.x-sin(w.Q.angle)*(taille_queue/1.75); // C'est le centre de la queue qu'on fait tourner
                    centre_queue.y=w.T[0].p.y-cos(w.Q.angle)*(taille_queue/1.75);
                    w.Q.p=centre_queue-tr; // On replace la queue par rapport a son centre
                    if(isMousePressed(SDL_BUTTON_LEFT)) // Si on clique, on passe a la preparation de la force de tir
                    {
                        tire=true; // On peut tirer
                        prepare_tire=false; // On ne revient pas ici
                    }
                }
                if (tire==true) // On prepare la force de tir
                {
                    tire_boule(w,tire,casse); // On tire
                }
                if (verifie_prochain_tour(w)==false && tire==false) // On vient de tirer : on remet les parametres de tir a zero
                {
                    OK_change_joueur=true; // On peut de nouveau changer le joueur
                    OK_init_queue=true; // La queue peut a nouveau reapparaitre
                    w.Q.exist=false; // On fait disparaitre la queue jusqu'au prochain tir
                }
                if(w.touche==true && penalite_mise==false && w.premier_touche>plus_petite && w.jeu_choisi==1) // Quand on a touche la mauvaise boule en premier au jeu de la 9
                {
                    w.nb_tirs+=10;
                    penalite_mise=true;
                }
                update(w,0.01f); // On met a jour les coordonnees des boules
                break;

            // Fin du jeu et victoire
            case 3 : //draw_table(w);
                draw(w);
                color(255,255,0);
                if(w.jeu_choisi!=2) // Affichage different pour le billard americain
                {
                    fontSize(zoom*(50/3));
                    print(DIMWX/2-zoom*(100/3),DIMWY/2,"Victoire !"); // On affiche qu'on a gagne
                    fontSize(zoom*10);
                    print(DIMWX/2-zoom*40,DIMWY/2-zoom*(100/3),"Nombre de tirs :"); // On affiche le nombre de tirs
                    print(DIMWX/2+zoom*(100/3),DIMWY/2-zoom*(100/3),w.nb_tirs);
                }
                else
                {
                    fontSize(zoom*(40/3));
                    print(DIMWX/2-zoom*60,DIMWY/2,"Victoire du joueur "); // On affiche qui a gagne
                    if((w.score_1==7 && w.joueur==1) || (w.score_2<7)) //Le joueur 1 a gagne s'il a 7 et qu'il a rentre lui-même la 7, ou si le joueur 2 n'a pas rentre toutes ses billes (puisque pour venir dans ce menu, on sait deja qu'un des deux au moins a 7)
                    {
                        print(DIMWX/2+zoom*(155/3),DIMWY/2,"1 !");
                    }
                    else //sinon c'est le joueur 2 qui a gagne
                    {
                        print(DIMWX/2+zoom*(155/3),DIMWY/2,"2 !");
                    }
                    fontSize(30);
                    print(DIMWX/2-zoom*40,DIMWY/2-zoom*(100/3),"Score joueur 1 :"); // On affiche le nombre de tirs
                    print(DIMWX/2+zoom*(100/3),DIMWY/2-zoom*(100/3),w.score_1);
                    print(DIMWX/2-zoom*40,DIMWY/2-zoom*(200/3),"Score joueur 2 :"); // On affiche le nombre de tirs
                    print(DIMWX/2+zoom*(100/3),DIMWY/2-zoom*(200/3),w.score_2);
                }
                update(w,0.01f); // On finit de faire avancer les boules (c'est plus joli)
                break;

            //Fin du jeu et partie perdue (que billard americain)
            case 4 : //draw_table(w);
                draw(w);
                color(255,255,0);
                fontSize(zoom*10);
                print(DIMWX/2-zoom*(200/3),DIMWY/2,"Partie perdue par le joueur"); // On affiche qui a perdu
                if (w.joueur==1)
                {
                    print(DIMWX/2+zoom*(165/3),DIMWY/2,"1 !");
                }
                else
                {
                    print(DIMWX/2+zoom*(165/3),DIMWY/2,"2 !");
                }
                print(DIMWX/2-zoom*40,DIMWY/2-zoom*(100/3),"Score joueur 1 :"); // On affiche le nombre de boules rentrees du joueur 1
                print(DIMWX/2+zoom*(100/3),DIMWY/2-zoom*(100/3),w.score_1);
                print(DIMWX/2-zoom*40,DIMWY/2-zoom*(200/3),"Score joueur 2 :"); // On affiche le nombre de boules rentrees du joueur 2
                print(DIMWX/2+zoom*(100/3),DIMWY/2-zoom*(200/3),w.score_2);
                update(w,0.01f); // On finit de faire avancer les boules (c'est plus joli)
                break;
        }
        stop = winDisplay();
    }
    winQuit();
	return 0;
}

