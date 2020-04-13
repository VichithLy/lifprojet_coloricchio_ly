#include <Grapic.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL_mixer.h>

const int MAXLIGNE = 50;
const int MAXCOLONNE = 300;
using namespace grapic;


//const int NUMEROTILEDRAPEAU = 221;
//const int NUMEROTILEPOWERUP = 199;
const int MAXNOMBREPIECES = 15;
const int DEBUTBONUSFONCTIONCOMMUN = 10;
const int DIMWX = 1280;//640;
const int DIMWY = 768;//512;
const int TILELARGEUR = 64;
const int TILEHAUTEUR = 64;
const int XLIM = 400;
const int YLIM = 200;
const int LARGEURLIM = DIMWX - XLIM*2;
const int HAUTEURLIM = DIMWY - YLIM*2;
const int NUMEROTILEPLATEFORMEMAX = 200;
const int NUMEROTILESANSEFFETMAX = 201;

const float DT = 0.04;
const float G = 0.0625 * TILEHAUTEUR;

const float TIMEANIMGOOMBA = 0.1;
const float TIMEANIMKOOPA = 0.1;
const float TIMEANIMCARAPACE = 0.2;
const float TIMEANIMPERSO = 0.1;
const float TIMEANIMMISSILE = 0.1;
const float TIMEANIMFLEUR = 0.1;
const float TIMEANIMFIREBRO = 0.1;
const float TIMEANIMTILE = 0.1;
const float TIMEANIMPIECES = 0.02;
const float TIMEANIMCHAMPIGNONGRAND = 0.03;
const float TIMEANIMCHAMPIGNONMINI = 0.03;
const float TIMEANIMCHAMPIGNONUP = 0.03;

const float TEMPMISSILESPAWN = 1;


const int MAXFRAMEIMMOBILE = 23;
const int MAXFRAMEMARCHE = 9;
const int MAXFRAMECOURSE = 11;
const int MAXFRAMEMONTE = 4;
const int MAXFRAMEDESCENTE = 4;




/*
Explications des numéros de type  dans les fonctions commune:
- 0 : perso
- 1 : goomba
- 2 : Koopa
- 3 : Carapace
- 4 : Carré pointu
- 5 : Missile
- 6 : Fleurs
- 9 : TILE anim
- 10 : pièces
- 11 : champignon grand
- 12 : champignon up
- 13 : champignon mini

*/


struct Vec2
{
    double x;
    double y;
};

//Questionn 2:
struct Vec2 make_Vec2(double x, double y)
{
    struct Vec2 retour;
    retour.x = x;
    retour.y = y;
    return retour;
}

struct Vec2 make_Vec2_exp(double r, double theta)
{
    struct Vec2 retour;
    retour.x = r*cos(theta*M_PI/180.0);
    retour.y = r*sin(theta*M_PI/180.0);
    return retour;
}

//Question 3:
struct Vec2 operator+(struct Vec2 a, struct Vec2 b)
{
    struct Vec2 retour;
    retour.x = a.x + b.x;
    retour.y = a.y + b.y;
    return retour;
}

struct Vec2 operator-(struct Vec2 a, struct Vec2 b)
{
    struct Vec2 retour;
    retour.x = a.x - b.x;
    retour.y = a.y - b.y;
    return retour;
}

//Question 4:
struct Vec2 operator*(float lambda, struct Vec2 b)
{
    struct Vec2 retour;
    retour.x = lambda*b.x;
    retour.y = lambda*b.y;
    return retour;
}

struct Color
{
    unsigned char r, g, b;
};

Color operator*(float lambda, Color a)
{
    Color retour;
    if(a.r*lambda>255)
    {
        retour.r = 255;
    }
    else
    {
        retour.r = a.r *lambda;
    }
    if(a.g*lambda>255)
    {
        retour.g = 255;
    }
    else
    {
        retour.g = a.g *lambda;
    }
    if(a.b*lambda>255)
    {
        retour.b = 255;
    }
    else
    {
        retour.b = a.b *lambda;
    }
    return retour;
}

Color operator+(Color a, Color b)
{
    Color retour;
    if(a.r+b.r>255)
    {
        retour.r = 255;
    }
    else
    {
        retour.r = a.r + b.r;
    }
    if(a.g+b.g>255)
    {
        retour.g = 255;
    }
    else
    {
        retour.g = a.g + b.g;
    }
    if(a.b+b.b>255)
    {
        retour.b = 255;
    }
    else
    {
        retour.b = a.b + b.b;
    }
    return retour;
}




int signe(float nombre)//Renvoie le signe d'un nombre
{
    if(nombre<0)
    {
        return -1;
    }
    if(nombre>0)
    {
        return 1;
    }
    return 0;
}

struct Animation
{
    double temp;
    char frame;
    char frameMax;
};

void animationUpdate(struct Animation &anim, char type)//Type de l'animation
{
    switch(type)
    {
        case 0:
            if(anim.temp+TIMEANIMPERSO<elapsedTime())
            {
                anim.frame = (anim.frame+1)%(anim.frameMax);
                anim.temp = elapsedTime();
            }
            break;
        case 1:
            if(anim.temp+TIMEANIMGOOMBA<elapsedTime())
            {
                anim.frame = (anim.frame+1)%anim.frameMax;
                anim.temp = elapsedTime();
            }
            break;
        case 2:
            if(anim.temp+TIMEANIMKOOPA<elapsedTime())
            {
                anim.frame = (anim.frame+1)%(anim.frameMax);
                anim.temp = elapsedTime();
            }
            break;
        case 3:
            if(anim.temp+TIMEANIMCARAPACE<elapsedTime())
            {
                anim.frame = (anim.frame+1)%(anim.frameMax);
                anim.temp = elapsedTime();
            }
            break;
        case 5:
            if (anim.temp+TIMEANIMMISSILE<elapsedTime())
            {
                anim.frame = (anim.frame+1)%(anim.frameMax);
                anim.temp = elapsedTime();
            }
            break;
        case 6:
            if (anim.temp+TIMEANIMFLEUR<elapsedTime())
            {
                anim.frame = (anim.frame+1)%(anim.frameMax);
                anim.temp = elapsedTime();
            }
            break;
        case 9:
            if (anim.temp+TIMEANIMTILE<elapsedTime())
            {
                anim.frame = (anim.frame+1)%(anim.frameMax);
                anim.temp = elapsedTime();
            }
            break;
        case 10:
            if (anim.temp+TIMEANIMPIECES<elapsedTime())
            {
                anim.frame = (anim.frame+1)%(anim.frameMax);
                anim.temp = elapsedTime();
            }
            break;
        case 11:
            if (anim.temp+TIMEANIMCHAMPIGNONGRAND<elapsedTime())
            {
                anim.frame = (anim.frame+1)%(anim.frameMax);
                anim.temp = elapsedTime();
            }
            break;
        case 12:
            if (anim.temp+TIMEANIMCHAMPIGNONUP<elapsedTime())
            {
                anim.frame = (anim.frame+1)%(anim.frameMax);
                anim.temp = elapsedTime();
            }
            break;
        case 13:
            if (anim.temp+TIMEANIMCHAMPIGNONMINI<elapsedTime())
            {
                anim.frame = (anim.frame+1)%(anim.frameMax);
                anim.temp = elapsedTime();
            }
            break;

    }
}

int nombreInTab(int tab[], int n, int nombre)
{
    int save = n;
    for(int i = nombre; i>0; i--)
    {
        tab[i-1] = n%10;
        n/=10;
    }
    return nombre;
}






struct Bonus
{
    Vec2 position;
    Vec2 vitesse;
    Vec2 force;
    struct Animation anim;
    float masse;
    int largeur;
    int hauteur;
    char type;
};


struct tileAnima
{
    int tileX;
    int tileY;
    int type;
    struct Animation anim;
};


struct tileMobile
{
    char type;//0 déplacement immobile 1 déplacement horizontal 2 déplacement vertical
    int draw;
    Vec2 position;
    Vec2 debut;
    Vec2 fin;
    struct Animation anim;
    double vitesse;
    bool playerDessus;
    double largeur;
    double hauteur;
    double timerAction;
};


struct DataImages
{
    Image sol[295];
    Image solAnim[3][34];

    Image item[1][6];

    Image ennemy[7][72];

    Image perso[5][24];

    Image bonus[4][17];

    Image font[5][26];

    Image background[3];

    Image button[3];

    Image imagesSup[4];
};

struct Ennemi
{
    Vec2 position;
    Vec2 vitesse;
    Vec2 force;
    float masse;
    int largeur;
    int hauteurLoose;
    int hauteurWin;
    char type;
    struct Animation anim;
    bool inLive;
    char sol;
    char action;
};

struct personnage
{
    Vec2 position;
    Vec2 vitesse;
    Vec2 force;
    Animation anim;
    double finInvincible;
    float masse;
    int largeur;
    int hauteur;
    char sol;
    char statAnim;
};


struct Text
{
    double spawn;
    double duree;
    Vec2 pos;
    double taille;
    char chaine[100];
};


struct Particules
{
    Vec2 pos;
    Vec2 vitesse;
    Vec2 force;
    int largeur;
    int hauteur;
    Color couleur;
    int type;
    int masse;
};

struct ParticulesList
{
    Particules tab[50];
    int nb_part = 0;
};

struct ListeText
{
    struct Text tab[20];
    int nb_text = 0;
};




struct tileAnimaList
{
    struct tileAnima tab[10];
    int nbTileAnima;
};

struct tileMobileList
{
    struct tileMobile tab[50];
    char nb_tile;
};



struct BonusList
{
    struct Bonus tab[70];
    char nombreBonus = 0;
};



struct EnnemiList
{
    struct Ennemi tab[50];
    char nombreEnnemi;
};




struct Level
{
    int level[MAXLIGNE][MAXCOLONNE];
    struct personnage persoPrincipal;
    struct BonusList listeBonus;
    struct EnnemiList listeEnnemies;
    struct tileMobileList listeTileMobile;
    struct tileAnimaList listeTileAnima;
    struct ParticulesList listeParticules;
    struct ListeText listeTexte;
    int nombreTileX;
    int nombreTileY;
    int scrollX;
    int scrollY;
    int finX;
    int finY;
    int debutX;
    int debutY;
    int checkPointX;
    bool checkPointStat;
    double debut;
    char numeroLevel;
    int secondeRestante;
};

struct Jeu
{
    struct Level level;
    int nb_pieces = 0;
    int nb_vie = 5;
    int score = 0;
};



void drawInit(const char chaine[100], struct DataImages &dataImage)
{
    winClear();
    image_draw(dataImage.imagesSup[1], 1, 1, DIMWX, DIMWY);
    color(255, 255, 255);
    print(DIMWX/1.8, 20, chaine);
    winDisplay();
}

void initListImage(Image tab[], int debut, int fin, const char save[100], int n, struct DataImages &dataImage)
{
    for(int i = debut; i<=fin; i++)
    {
        char chaine[100];
        strcpy(chaine, save);
        int tableau[3] = {0, 0, 0};
        nombreInTab(tableau, i, n);
        for(int j = 0; j<n; j++)
        {

            chaine[strlen(save)+j] = tableau[j]+'0';
        }
        chaine[strlen(save)+n] = '\0';
        strcat(chaine, ".png");
        drawInit(chaine, dataImage);
        tab[i-1] = image(chaine, true, 255, 255, 255, 255);
    }
}





void initImage(struct DataImages &data)//initialise la structure contenant toutes les images
{
    /*data.sol[1] = image("data/test/sol1.png", true, 255, 255, 255, 255);
    data.sol[0] = image("data/test/sol2.png", true, 255, 255, 255, 255);
    data.sol[2] = image("data/test/sol3.png", true, 255, 255, 255, 255);
    data.sol[3] = image("data/test/sol4.png", true, 255, 255, 255, 255);
    data.sol[4] = image("data/test/sol5.png", true, 255, 255, 255, 255);
    data.sol[5] = image("data/test/sol6.png", true, 255, 255, 255, 255);
    data.sol[6] = image("data/test/sol7.png", true, 255, 255, 255, 255);
    data.sol[7] = image("data/test/lance-missile1.png", true, 255, 255, 255, 255);
    data.sol[8] = image("data/test/lance-missile2.png", true, 255, 255, 255, 255);
    data.sol[9] = image("data/test/lance-missile3.png", true, 255, 255, 255, 255);*/
    data.imagesSup[1] = image("data/mario/imageDebut.png");
    data.imagesSup[0] = image("data/mario/end.png");
    data.imagesSup[2] = image("data/mario/castle.png");
    data.imagesSup[3] = image("data/mario/logo.png");

    initListImage(data.sol, 1, 294, "data/mario/tileset/tiles-", 3, data);
    initListImage(data.solAnim[0], 1, 16, "data/mario/tileset/anim/bonus-", 2, data);
    initListImage(data.solAnim[1], 1, 34, "data/mario/tileset/anim/drapeau/drapeau1-", 2, data);
    initListImage(data.solAnim[2], 1, 34, "data/mario/tileset/anim/drapeau/drapeau-", 2, data);


    initListImage(data.ennemy[0], 1, 17, "data/mario/ennemis/goomba/Goomba", 2, data);
    initListImage(data.ennemy[1], 1, 20, "data/mario/ennemis/koopa/Koopa", 2, data);
    initListImage(data.ennemy[2], 1, 6, "data/mario/ennemis/koopa/Carapace", 1, data);
    initListImage(data.ennemy[3], 1, 2, "data/mario/ennemis/Tchomp/Tchomp", 1, data);
    initListImage(data.ennemy[4], 1, 18, "data/mario/ennemis/missile/missile", 2, data);
    initListImage(data.ennemy[5], 1, 71, "data/mario/ennemis/fleurs/piranah", 2, data);
    //initListImage(data.ennemy[6], 1, 26, "data/test/ennemis/firebro/immobile", 2);

    initListImage(data.perso[0], 1, MAXFRAMEIMMOBILE, "data/mario/perso/immobile", 2, data);
    initListImage(data.perso[1], 1, MAXFRAMEMARCHE, "data/mario/perso/marche", 2, data);
    initListImage(data.perso[2], 1, MAXFRAMECOURSE, "data/mario/perso/course", 2, data);
    initListImage(data.perso[3], 1, MAXFRAMEMONTE, "data/mario/perso/monte", 2, data);
    initListImage(data.perso[4], 1, MAXFRAMEDESCENTE, "data/mario/perso/descente", 2, data);

    initListImage(data.bonus[0], 1, 16, "data/mario/items/pieces/pieces-", 2, data);
    initListImage(data.bonus[1], 1, 16, "data/mario/items/champignon/champignon1-", 2, data);
    initListImage(data.bonus[2], 1, 16, "data/mario/items/champignon/champignon2-", 2, data);
    initListImage(data.bonus[3], 1, 16, "data/mario/items/champignon/champignon3-", 2, data);

    initListImage(data.font[1], 1, 10, "data/mario/font/number/number-", 2, data);
    initListImage(data.font[0], 1, 3, "data/mario/font/symbol/symbol-", 1, data);

    initListImage(data.background, 1, 2, "data/mario/background/monde", 1, data);

    initListImage(data.button, 1, 3, "data/mario/font/bouton/button-", 1, data);
    initListImage(data.font[2], 1, 26, "data/mario/font/letter/majuscule", 2, data);
    initListImage(data.font[3], 1, 26, "data/mario/font/letter/minuscule", 2, data);
    initListImage(data.font[4], 1, 10, "data/mario/font/letter/number", 2, data);

}


struct Bonus initBonus(float px, float py, int largeur, int hauteur, int masse, int type, float vx, float vy, float fx, float fy)
{
    struct Bonus retour;
    retour.position.x = px;
    retour.position.y = py;
    retour.largeur = largeur;
    retour.hauteur = hauteur;
    retour.vitesse.x = vx;
    retour.vitesse.y = vy;
    retour.force.x = fx;
    retour.force.y = fy;
    retour.masse = masse;
    retour.anim.temp = elapsedTime();
    retour.anim.frame = 0;
    retour.anim.frameMax = 16;
    retour.type = type;
    return retour;
};

struct personnage initPerso(float px, float py, int largeur, int hauteur, float masse)//Renvoie un personnage en fonction des paramètres passés.
{
    struct personnage retour;
    retour.position.x = px;
    retour.position.y = py;
    retour.largeur = largeur;
    retour.hauteur = hauteur;
    retour.vitesse.x = 0;
    retour.vitesse.y = 0;
    retour.force.x = 0;
    retour.force.y = 0;
    retour.masse = masse;
    retour.sol = false;
    retour.anim.frame = 0;
    retour.anim.frameMax = 23;
    retour.statAnim = 0;
    retour.anim.temp = elapsedTime();
    retour.finInvincible = elapsedTime();
    return retour;
}

struct Ennemi initEnnemi(float px, float py, int largeur, int hauteurLoose, int hauteurWin, char type, float masse, float vx, float vy, float fx, float fy)
{
    struct Ennemi retour;
    retour.position.x = px;
    retour.position.y = py;
    retour.largeur = largeur;
    retour.hauteurLoose = hauteurLoose;
    retour.hauteurWin = hauteurWin;
    retour.vitesse.x = vx;
    retour.vitesse.y = vy;
    retour.force.x = fx;
    retour.force.y = fy;
    retour.masse = masse;
    retour.type = type;
    retour.inLive = true;
    retour.action = 2;
    retour.anim.temp = elapsedTime();
    retour.anim.frame = 0;
    switch(type)
    {
        case 0:
            retour.anim.frameMax = 17;
            break;
        case 1:
            retour.anim.frameMax = 20;
            break;
        case 2:
            retour.anim.frameMax = 6;
            break;
        case 3:
            retour.anim.frameMax = 2;
            break;
        case 4:
            retour.anim.frameMax = 18;
            break;
        case 5:
            retour.anim.frameMax = 71;
            break;

    }
    retour.anim.frameMax = 16;
    return retour;
}





struct Particules initParticules(double x, double y, double fx, double fy, double vx, double vy, int type, Color c, int largeur, int hauteur)
{
    struct Particules retour;
    retour.couleur = c;
    retour.force = {fx, fy};
    retour.pos = {x, y};
    retour.vitesse = {vx, vy};
    retour.type = type;
    retour.largeur = largeur;
    retour.hauteur= hauteur;
    retour.masse = 1;
    return retour;
};





struct tileAnima initTileAnima(int tileX, int tileY, int type)
{
    struct tileAnima retour;
    retour.tileX = tileX;
    retour.tileY = tileY;
    retour.anim.frame = 0;
    retour.anim.temp = elapsedTime();
    if(type<20)
    {
        retour.anim.frameMax = 16;
    }
    else
    {
        retour.anim.frameMax = 34;
    }
    retour.type = type;
    return retour;
};

void addText(double x, double y, double taille, char chaine[100], double duree, struct ListeText &l)
{
    l.tab[l.nb_text].pos.x = x;
    l.tab[l.nb_text].pos.y = y;
    l.tab[l.nb_text].taille = taille;
    strcpy(l.tab[l.nb_text].chaine, chaine);
    l.tab[l.nb_text].spawn = elapsedTime();
    l.tab[l.nb_text].duree = duree;
    l.nb_text++;
}

struct tileMobile initTileMobile(double largeur, double hauteur, Vec2 position, double vitesse, char type, int draw, Vec2 debut, Vec2 fin)
{
    struct tileMobile retour;
    retour.type = type;
    retour.draw = draw;
    retour.debut = debut;
    retour.fin = fin;
    retour.playerDessus = false;
    retour.largeur = largeur;
    retour.hauteur = hauteur;
    retour.position = position;
    retour.vitesse = vitesse;
    retour.timerAction = elapsedTime();
    retour.anim.frame = 0;
    retour.anim.frameMax = 1;
    retour.anim.temp = elapsedTime();
    return retour;
};






int returnDrawTile(int number)
{
    if(number >= 0)//Si c'est pas du vide
    {
        if(number<174)//Si c'est une tilesolid
        {
            return 0;
        }
        else if(number<213)//Si c'est une plateforme
        {
            return 1;//Collision possible que par le haut
        }
        else//Si c'est une tile de décoration
        {
            return -1;
        }
    }
    return -1;
}

void removeTileAnima(struct Jeu &dataJeu, int x, int y)
{
    for(int i = 0; i<dataJeu.level.listeTileAnima.nbTileAnima; i++)
    {
        if(x==dataJeu.level.listeTileAnima.tab[i].tileX&&y==dataJeu.level.listeTileAnima.tab[i].tileY)
        {
            if(dataJeu.level.listeTileAnima.tab[i].type<MAXNOMBREPIECES)
            {
                dataJeu.level.listeTileAnima.tab[i].type--;
                dataJeu.level.listeBonus.tab[dataJeu.level.listeBonus.nombreBonus] = initBonus(x*TILELARGEUR+TILELARGEUR/4, (y+1)*TILEHAUTEUR, TILELARGEUR/2, TILEHAUTEUR/2, 1, 0, 0, TILEHAUTEUR/2, 0, -G);
                dataJeu.level.listeBonus.nombreBonus++;
            }
            else
            {

                dataJeu.level.listeBonus.tab[dataJeu.level.listeBonus.nombreBonus] = initBonus(x*TILELARGEUR, (y+1)*TILEHAUTEUR, TILELARGEUR, TILEHAUTEUR, 1, dataJeu.level.listeTileAnima.tab[i].type-MAXNOMBREPIECES+1, TILELARGEUR/4, TILEHAUTEUR, 0, -G);
                dataJeu.level.listeBonus.nombreBonus++;
                dataJeu.level.listeTileAnima.tab[i].type=-1;
            }
            if(dataJeu.level.listeTileAnima.tab[i].type==-1)
            {
                for(int k = i; k<dataJeu.level.listeTileAnima.nbTileAnima-1; k++)
                {
                    dataJeu.level.listeTileAnima.tab[k] = dataJeu.level.listeTileAnima.tab[k+1];
                }
                i= dataJeu.level.listeTileAnima.nbTileAnima;
                dataJeu.level.listeTileAnima.nbTileAnima--;
                dataJeu.level.level[y][x] = 2;
            }

        }
    }
}

void reorganiseTabParticule(struct ParticulesList &list, char debut)
{
    for(int i = debut; i<list.nb_part -1; i++)
    {
        list.tab[i] = list.tab[i+1];
    }
    list.nb_part--;
}

void reorganiseTabText(struct ListeText &list, char debut)
{
    for(int i = debut; i<list.nb_text -1; i++)
    {
        list.tab[i] = list.tab[i+1];
    }
    list.nb_text--;
}


void reorganiseTabTileMobile(struct tileMobileList &list, char debut)
{
    for(int i = debut; i<list.nb_tile -1; i++)
    {
        list.tab[i] = list.tab[i+1];
    }
    list.nb_tile--;
}


void reorganiseTabBonus(struct BonusList &list, char debut)
{
    for(int i = debut; i<list.nombreBonus-1; i++)
    {
        list.tab[i] = list.tab[i+1];
    }
    list.nombreBonus--;
}

void reorganiseTabEnnemy(struct EnnemiList &list, char debut)
{
    for(int i = debut; i<list.nombreEnnemi-1; i++)
    {
        list.tab[i] = list.tab[i+1];
    }
    list.nombreEnnemi--;
}


bool appartTab(int tab[], int n, int taille)
{
    for(int i = 0; i<taille; i++)
    {
        if(tab[i]==n)
        {
            return true;
        }
    }
    return false;
}








/*
-22 : goomba
-23: koopa
-21 : checkpoint
-20 : Champignon gros
-19 : Champignon up
-18 : Champignon mini
-17 à -3 : Case mystère avec pièces
-2: pièces
-1: vide
Le reste : tileset
*/
void chargeTabInMap(int level[MAXLIGNE][MAXCOLONNE], struct Jeu &dataJeu, int tailleX, int tailleY)
{
    for(int i = 0; i<tailleY; i++)
    {
        for(int j = 0; j<tailleX; j++)
        {
            if(level[i][j]==-25)
            {
                dataJeu.level.listeEnnemies.tab[dataJeu.level.listeEnnemies.nombreEnnemi] = initEnnemi(j*TILELARGEUR, (tailleY - i - 1)*TILEHAUTEUR, TILELARGEUR*2.5, TILEHAUTEUR*3, 0, 3, 2, 0, 1, 0, 0);
                dataJeu.level.level[tailleY-1-i][j]=-1;
                dataJeu.level.listeEnnemies.nombreEnnemi++;
            }
            else if(level[i][j]==-24)
            {

                dataJeu.level.listeEnnemies.tab[dataJeu.level.listeEnnemies.nombreEnnemi] = initEnnemi((j+0.375)*TILELARGEUR, (tailleY - i - 1)*TILEHAUTEUR - 20, TILELARGEUR*1.5, TILEHAUTEUR*2.5, 0, 5, 1, 0, 0, 0, 0);
                dataJeu.level.level[tailleY-1-i][j]=12;
                dataJeu.level.listeEnnemies.nombreEnnemi++;
            }
            else if(level[i][j]==-22)
            {
                dataJeu.level.listeEnnemies.tab[dataJeu.level.listeEnnemies.nombreEnnemi] =initEnnemi(j*TILELARGEUR, (tailleY - i - 1)*TILEHAUTEUR, TILELARGEUR, TILEHAUTEUR/2, TILEHAUTEUR/2, 0, 1, TILELARGEUR/32, TILEHAUTEUR/32, 0, TILEHAUTEUR*(-0.7)/32); //Goomba
                dataJeu.level.level[tailleY-1-i][j]=-1;
                dataJeu.level.listeEnnemies.nombreEnnemi++;
            }
            else if(level[i][j]==-23)
            {
                dataJeu.level.listeEnnemies.tab[dataJeu.level.listeEnnemies.nombreEnnemi] =initEnnemi(j*TILELARGEUR, (tailleY - i - 1)*TILEHAUTEUR, TILELARGEUR, TILEHAUTEUR, TILEHAUTEUR, 1, 1, TILELARGEUR/32, TILEHAUTEUR/32, 0, -G); //Koopa
                dataJeu.level.level[tailleY-1-i][j]=-1;
                dataJeu.level.listeEnnemies.nombreEnnemi++;
            }
            else if(level[i][j]==-21)
            {
                dataJeu.level.listeTileAnima.tab[0] = initTileAnima(j, tailleY - i - 1, 20);
                dataJeu.level.checkPointX = j*TILELARGEUR;
                dataJeu.level.checkPointStat = false;
                dataJeu.level.level[tailleY-1-i][j]=-1;
            }
            else if(level[i][j]<=-18)
            {
                dataJeu.level.listeTileAnima.tab[dataJeu.level.listeTileAnima.nbTileAnima] = initTileAnima(j, tailleY - 1 - i, abs(level[i][j])-3);
                dataJeu.level.listeTileAnima.nbTileAnima++;
                dataJeu.level.level[tailleY-1-i][j] = 1;
            }
            else if(level[i][j]<=-3)
            {
                dataJeu.level.listeTileAnima.tab[dataJeu.level.listeTileAnima.nbTileAnima] = initTileAnima(j, tailleY-i-1, abs(level[i][j])-3);
                dataJeu.level.listeTileAnima.nbTileAnima++;
                dataJeu.level.level[tailleY-1-i][j] = 1;
            }
            else if(level[i][j]==-2)
            {
                dataJeu.level.level[tailleY-1-i][j] = -1;
                dataJeu.level.listeBonus.tab[dataJeu.level.listeBonus.nombreBonus] = initBonus(j*TILELARGEUR+TILELARGEUR/4, (tailleY-1-i)*TILEHAUTEUR + TILEHAUTEUR/4, TILELARGEUR/2, TILEHAUTEUR/2, 1, 0, 0, 0, 0, 0);
                dataJeu.level.listeBonus.nombreBonus++;
            }
            else if(level[i][j]>=-1)
            {
                dataJeu.level.level[tailleY-1-i][j] = level[i][j];
            }
        }
    }
}




void initLevel(struct Jeu &dataJeu, int numero)
{
    dataJeu.level.numeroLevel=numero;
    switch(numero)
    {
        case 0:
            {
                int level0[MAXLIGNE][MAXCOLONNE] = {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,161,162,113,162,112,114,162,114,113,162,114,113,162,162,112,113,162,162,112,162,114,113,162,162,112,112,112,166},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,121,163,116,163,163,117,163,163,115,163,163,163,163,117,163,163,163,163,163,115,163,163,163,163,117,163,163,126},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,123,163,163,163,163,163,163,173,119,120,119,118,119,118,119,120,119,118,172,163,163,163,163,116,163,163,116,124},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,105,163,117,163,116,163,163,101,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,102, 163,116,117,163,163,163,163,163,164},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,122,163,163,163,163,163,163,125,-1,-6,-1,-1,-1,-1,-1,-1,-1,-1,122,163,115,163,163,163,163,163,163,125},
                                                    {-1,-1,-1,-1,-1,-1,174,175,175,175,176,-1,-1,-1,-1,-1,174,175,175,175,176,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,105,163,163,163,163,163,163,124,255,-6,-1,-1,-1,-1,-1,-1,-1,255,121,117,163,163,163,163,163,116,163,124},
                                                    {-1,-1,-1,-1,-1,-1,-1,223,-1,223,-1,-1,-1,-1,-1,-1,-1,223,-1,223,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,121,163,116,163,163,117,163,169,162,162,166,-1,-1,-1,-1,98,99,99,168,163,163,163,116,163,163,163,163,125},
                                                    {-1,-1,-1,-2,-1,-1,-1,224,-1,224,-1,-1,-1,-1,-1,-1,-1,224,-1,224,-1,-1,-1,-5,-1,-1,-1,-1,-1,-1,-1,-1,122,163,163,163,163,163,163,163,163,162,164,-1,-1,-1,-1,122,163,163,163,163,116,163,117,163,163,163,163,164},
                                                    {-1,-1,-1,-2,-1,-1,-1,224,-1,224,-1,-1,-1,-1,-1,-1,-1,224,-1,224,-1,-1,-1,-5,-1,-1,-1,-1,-1,-1,-1,-1,105,163,163,117,163,116,163,163,163,163,124,-1,-1,-1,-1,121,163,116,163,163,163,163,163,116,163,163,163,124},
                                                    {-1,-1,189,190,191,-1,-1,224,-1,224,-1,-1,192,193,194,-1,-1,224,-1,224,-1,-1,189,190,191,-1,-1,-1,-1,-1,-1,-1,107,118,119,118,118,120,118,119,118,120,108,-1,-1,-1,-1,107,119,120,120,118,120,120,118,119,118,118,118,108},
                                                    {-1,-1,231,232,233,-1,-1,224,-1,224,-1,-1,-1,223,-1,-1,-1,224,-1,224,-1,-1,231,232,233,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,258,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,258,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,240,241,242,214,-1,224,-1,224,-1,-1,-1,224,-1,-1,-1,224,-1,224,-1,-1,240,241,242,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,259,-1,-1,-1,-1,-1,-1,-1,-1,-1,256,-1,-1,-1,259,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {213,-1,249,250,251,215,-1,224,-1,224,252,253,254,224,-1,-1,-1,224,213,224,-1,-1,249,250,251,215,-1,213,218,219,264,265,-1,-1,255,260,-1,-1,-1,-1,-1,-1,-1,-1,-1,257,255,-1,-1,260,-1,-1,-1,255,-1,-1,-1,-1,-1,-1},
                                                    {17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,20,17,17,17,17,18,177,177,198,198,161,162,113,162,112,114,162,114,113,162,114,113,162,162,112,113,162,162,112,162,114,113,162,162,112,112,112,166},
                                                    {37,37,37,37,37,37,37,37,37,37,38,39,37,37,37,38,39,37,38,39,37,38,39,37,38,39,39,46,-1,-1,-1,-1,170,116,163,163,163,163,163,116,163,163,163,116,163,115,116,163,163,163,163,116,163,163,163,163,116,116,116,164},
                                                    {37,37,37,37,37,38,39,38,37,38,39,39,39,39,39,39,39,37,38,39,37,38,39,37,38,39,39,47,-1,-1,-1,-1,170,163,116,163,116,163,163,163,116,163,163,116,163,163,163,116,163,115,163,163,163,116,163,163,163,163,163,164}};

                dataJeu.level.nombreTileY = 17;
                dataJeu.level.nombreTileX = 60;
                dataJeu.level.debutX = 1;
                dataJeu.level.debutY = 5*TILEHAUTEUR;
                dataJeu.level.listeBonus.nombreBonus = 0;
                dataJeu.level.listeTileAnima.nbTileAnima = 1;
                dataJeu.level.listeEnnemies.nombreEnnemi=0;
                for(int i = 0; i<17; i++)
                {
                    for(int j = 0; j<60; j++)
                    {
                        dataJeu.level.level[16-i][j] = level0[i][j];
                    }
                }
                dataJeu.level.listeTileMobile.nb_tile = 0;
                break;
            }
        case 1:
            {
                int level1[MAXLIGNE][MAXCOLONNE] = {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,-1,-1,-1,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-8,0,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,0,-5,0,-5,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,213,215,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-20,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-2,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,252,253,254,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-10,0,-1,-1,-1,-1,-1,-1,-1,-1,3,3,3,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,83,84,84,84,84,85,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,7,8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,19,17,17,18,-1,-1,19,36,17,17,36,36,18,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,3,3,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,213,-1,-1,-1,86,87,38,39,87,88,-1,-1,-1,-1,-1,-1,-1,214,-1,83,84,84,85,-1,-1,-1,-1,7,8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,12,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,7,8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,215,213,23,37,38,28,-22,-1,27,37,38,37,38,39,28,215,213,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,7,8,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,3,3,3,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {252,253,254,-1,213,-1,-1,-1,-1,-1,-1,215,-1,-1,-1,-22,-1,213,-1,-1,-1,-1,-1,-1,-1,83,34,35,34,35,92,38,87,39,38,47,-1,-1,-1,-1,-1,-1,213,215,-1,86,87,87,88,-1,-1,-1,-1,12,13,252,253,254,-22,-1,-1,-1,-1,213,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,213,215,-1,-1,-1,-1,-1,-1,-22,-1,-1,215,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,252,253,254,12,13,-1,-1,213,-1,-21,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,215,-1,-1,-1,-1,-1,-1,-1,-1,252,253,254,-1,-1,12,13,-1,-1,213,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,215,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,83,84,84,84,92,37,38,93,20,20,92,37,38,37,38,39,93,36,35,35,26,-1,-1,-1,-1,-1,-1,-1,-1,12,13,-1,-1,215,213,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-23,-1,-1,-1,-1,-1,252,253,254,-1,-1,-1,-1,-1,3,3,3,3,3,3,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,34,35,34,35,34,35,34,35,34,35,92,87,38,87,39,38,87,38,38,87,93,84,84,84,84,84,84,84,84,84,77,84,84,74,84,84,84,17,12,13,17,17,17,17,17,17,17,17,17,18,-1,-1,19,34,35,34,36,34,36,17,17,36,17,17,36,17,17,17,36,17,17,36,17,17,36,17,36,17,17,36,18,-1,-1,19,17,36,34,36,12,13,36,34,35,36,34,36,34,35,36,34,35,36,34,36,34,35,36,34,35,36,34,36,34,35,36,34,35,36,34,36,34,35,12,13,36,34,35,36,34,36,34,35,36,34,35,36,34,36,34,18,-1,-1,19,36,34,35,36,34,36,92,95,94,87,37,38,39,38,95,94,37,38,39,37,38,39,38,39,38,39,28,-1,-1,83,84,84,36,84,36,12,13,84,84,36,84,36,84,84,36,84,84,84,36,84,36,85,-1,-1,-1,83,84,34,36,34,36,35,84,34,36,34,36,35,84,34,36,34,36,35,84,34,36,34,36,35,84,34,36,34,36,35,84,34,36,34,36,35,84,34,36,34,36,35}};
                dataJeu.level.nombreTileY = 16;
                dataJeu.level.nombreTileX = 256;
                dataJeu.level.listeBonus.nombreBonus = 0;
                dataJeu.level.listeTileAnima.nbTileAnima = 1;
                dataJeu.level.listeEnnemies.nombreEnnemi=0;
                chargeTabInMap(level1, dataJeu, 256, 16);
                dataJeu.level.finY = 1*TILEHAUTEUR;
                dataJeu.level.finX = 240*TILELARGEUR;
                dataJeu.level.listeTileMobile.nb_tile = 0;
                dataJeu.level.debutX = 2 * TILELARGEUR;
                dataJeu.level.debutY = 5*TILEHAUTEUR;
                break;
            }
        case 2:
            {
                int level2[MAXLIGNE][MAXCOLONNE] = {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,53,-1,-1,-1,-1,-1,53,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,54,-1,-1,-1,-1,-1,54,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,54,-1,-1,-20,-1,214,54,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,213,54,-1,-1,-1,-1,215,54,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,83,77,58,-1,-1,-1,83,77,58,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,50,33,52,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,67,78,68,-1,-1,-1,67,78,68,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,65,34,66,-1,-1,-1,65,34,66,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,29,41,30,-1,-1,-1,29,41,30,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,50,33,52,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,183,184,184,184,184,185,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-21,-1,-1,-1,-1,-1,-1,-1,-1,-1,252,253,254,-1,-1,213,-1,-1,-1,-1,-1,-1,-1,-1,-1,252,253,254,-1,-1,215,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,252,253,254,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,213,-1,-1,-1,-1,-1,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,186,187,187,187,188,-1,-1,-1,-1,189,190,190,190,191,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,213,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,225,226,226,226,226,227,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,19,17,17,17,17,17,17,18,-1,-1,-1,-1,-1,-1,19,17,17,17,17,17,17,18,-1,-1,-1,-1,-1,-1,-1,19,17,17,17,17,17,17,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,19,17,17,17,17,17,17,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,19,17,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,237,229,229,229,230,-1,-1,-1,-1,233,241,233,242,240,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,19,17,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,50,31,52,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-6,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,234,226,226,226,226,227,-1,-1,-1,-1,-1,-1,-1,215,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,86,87,38,38,37,87,39,22,-1,-1,-1,-1,-1,-1,86,87,38,38,37,87,39,22,-1,-1,-1,-1,-1,-1,-1,86,87,38,38,37,87,39,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,86,87,38,38,37,87,39,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,86,87,47,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,252,253,254,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,237,238,229,229,239,-1,-1,-1,-1,241,242,241,241,241,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,86,87,47,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,183,184,184,185,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,183,184,184,184,184,226,226,226,226,227,-1,-1,-1,-1,-1,-1,19,36,34,36,34,36,34,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,39,37,87,38,87,39,22,-1,-1,-1,-1,-1,-1,27,39,37,87,38,87,39,22,-1,-1,-1,-1,-1,-1,-1,27,39,37,87,38,87,39,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,39,37,87,38,87,39,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,39,47,-1,215,-1,-1,-23,-1,-1,-1,213,-1,25,36,36,36,26,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,228,229,229,238,239,-1,-1,-1,-1,242,241,242,242,241,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,39,47,252,253,254,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,225,226,235,227,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-3,0,-3,0,-1,-1,-1,-1,-1,-1,-1,-1,225,226,226,226,235,226,226,226,226,236,-1,-1,-1,-1,-1,-1,44,37,38,39,37,38,39,28,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,38,37,39,87,39,37,22,-1,-1,-1,-1,-1,-1,23,38,37,39,87,39,37,22,-1,-1,-1,-1,-1,-1,-1,23,38,37,39,87,39,37,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,23,38,37,39,87,39,37,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,38,93,36,34,36,34,36,34,36,35,35,34,92,38,39,39,28,-1,-1,-1,-1,-1,-1,-1,49,-1,-1,-1,-1,-1,-1,-1,-1,-1,49,-1,-1,-1,-1,-1,-1,-1,-1,-1,246,229,229,247,248,213,-1,-1,-1,249,250,249,250,251,-1,215,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,38,93,20,36,20,36,20,26,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,215,-1,-1,-1,252,253,254,-1,-1,-1,-1,215,-1,-1,-1,-1,-1,252,253,254,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,234,235,235,236,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,215,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,234,226,226,226,235,226,226,226,226,227,-1,-1,-1,-1,-1,-1,43,37,38,39,37,38,39,5,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,39,38,37,87,38,87,22,-1,-1,-1,-1,-1,-1,23,39,38,37,87,38,87,22,-1,-1,-1,-1,-1,-1,-1,23,39,38,37,87,38,87,22,-1,-1,-1,-1,213,-1,-22,-1,-1,-1,-1,215,-22,-1,-1,-1,-1,23,39,38,37,87,38,87,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,39,38,37,87,38,87,37,87,38,37,87,37,38,37,38,38,88,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,25,34,34,36,34,36,36,34,36,35,34,36,35,34,36,35,35,26,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,39,38,37,38,37,38,39,28,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,25,34,34,36,34,36,36,34,36,35,34,36,35,34,36,36,36,34,36,35,34,36,35,34,36,35,35,36,36,34,36,35,34,36,35,34,36,35,35},
                                                    {-1,243,244,244,245,-1,-1,252,253,254,-1,83,84,36,84,36,84,36,84,85,-1,-1,-1,-1,-1,-1,213,-1,-1,-1,215,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,234,226,226,226,235,184,184,184,235,236,-1,-1,-1,-1,-1,-1,44,37,38,39,37,38,39,10,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,23,39,37,38,37,87,37,22,-1,-1,-1,-1,-1,-1,23,39,37,38,37,87,37,22,-1,-1,-1,-1,-1,-1,-1,23,39,37,38,37,87,37,22,-1,-1,-1,-1,50,51,52,-1,-1,-1,50,51,52,-1,-1,-1,-1,23,39,37,38,37,87,37,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,39,37,38,37,87,37,38,38,87,37,87,87,37,38,24,39,28,-1,-1,-1,-1,53,-1,-1,-1,-1,-1,-1,50,51,52,-1,-1,-1,-1,-1,-1,53,-1,-1,-1,-1,23,39,37,38,37,87,37,38,38,87,37,87,87,37,38,24,39,28,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,39,37,37,38,37,38,39,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,39,37,38,37,87,37,38,38,87,37,87,87,37,38,87,37,38,38,87,37,87,87,37,38,24,39,87,37,38,38,87,37,87,87,37,38,24,39},
                                                    {17,17,17,17,17,17,17,17,17,17,17,92,37,38,39,87,37,38,39,28,-1,-1,-23,-1,83,84,36,84,84,36,84,18,-1,252,253,254,-1,-1,-1,-1,-1,25,26,-1,213,-1,-1,225,226,226,226,235,235,235,235,235,227,-1,-1,-1,252,253,254,86,37,38,39,37,38,39,93,84,84,85,-1,-1,-1,213,-1,-1,-23,-1,-1,215,213,-1,-1,86,87,39,39,38,37,38,22,-1,-1,-1,-1,-1,-1,86,87,39,39,38,37,38,22,-1,-1,-1,-1,-1,-1,-1,86,87,39,39,38,37,38,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,86,87,39,39,38,37,38,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,86,87,39,39,38,37,38,37,39,37,87,87,37,39,38,38,24,28,-1,-1,-1,-1,55,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,55,-1,-1,-1,-1,86,87,39,39,38,37,38,37,39,37,87,87,37,39,38,38,24,28,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,86,87,39,37,38,37,38,39,28,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,86,87,39,39,38,37,38,37,39,37,87,87,37,39,38,37,38,37,39,37,87,87,37,39,38,38,24,37,38,37,39,37,87,87,37,39,38,38,24},
                                                    {87,87,87,87,87,87,87,87,87,87,87,37,38,39,37,38,39,39,24,93,17,84,17,17,92,37,38,39,37,38,39,93,84,84,84,84,84,84,84,84,84,92,93,84,84,84,84,84,84,84,84,84,84,84,84,84,84,85,-1,-1,83,84,36,92,38,37,38,39,37,38,39,87,87,93,84,84,84,84,84,84,84,84,84,84,84,84,84,92,37,37,87,37,38,37,28,-1,-1,-1,-1,-1,-1,27,37,37,87,37,38,37,28,-1,-1,-1,-1,-1,-1,-1,27,37,37,87,37,38,37,28,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,37,37,87,37,38,37,28,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,37,37,87,37,38,37,38,39,87,38,38,87,37,37,39,38,88,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,37,37,87,37,38,37,38,39,87,38,38,87,37,37,39,38,88,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,37,37,37,38,37,38,39,47,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,37,37,87,37,38,37,38,39,87,38,38,87,37,37,38,37,38,39,87,38,38,87,37,37,39,38,38,37,38,39,87,38,38,87,37,37,39,38}};
                dataJeu.level.nombreTileY = 20;
                dataJeu.level.nombreTileX = 296;
                dataJeu.level.listeBonus.nombreBonus = 0;
                dataJeu.level.listeTileAnima.nbTileAnima = 1;
                dataJeu.level.listeEnnemies.nombreEnnemi=0;
                chargeTabInMap(level2, dataJeu, 296, 20);
                dataJeu.level.listeTileMobile.nb_tile = 7;
                dataJeu.level.listeTileMobile.tab[0] = initTileMobile(4, 1, make_Vec2(81*TILELARGEUR, TILEHAUTEUR), TILEHAUTEUR/32, 2, 3, make_Vec2(81*TILELARGEUR, 3*TILEHAUTEUR), make_Vec2(81*TILELARGEUR, 11*TILEHAUTEUR));
                dataJeu.level.listeTileMobile.tab[1] = initTileMobile(4, 1, make_Vec2(96*TILELARGEUR, TILEHAUTEUR), TILEHAUTEUR/32, 2, 3, make_Vec2(96*TILELARGEUR, TILEHAUTEUR), make_Vec2(96*TILELARGEUR, 16*TILEHAUTEUR));
                dataJeu.level.listeTileMobile.tab[2] = initTileMobile(5, 1, make_Vec2(110*TILELARGEUR, TILEHAUTEUR), TILEHAUTEUR/32, 2, 3, make_Vec2(110*TILELARGEUR, TILEHAUTEUR), make_Vec2(110*TILELARGEUR, 16*TILEHAUTEUR));
                dataJeu.level.listeTileMobile.tab[3] = initTileMobile(7, 1, make_Vec2(150*TILELARGEUR, TILEHAUTEUR), TILEHAUTEUR/32, 2, 3, make_Vec2(150*TILELARGEUR, TILEHAUTEUR), make_Vec2(150*TILELARGEUR, 16*TILEHAUTEUR));
                dataJeu.level.listeTileMobile.tab[4] = initTileMobile(5, 1, make_Vec2(221*TILELARGEUR, TILEHAUTEUR), TILEHAUTEUR/32, 2, 3, make_Vec2(221*TILELARGEUR, TILEHAUTEUR), make_Vec2(221*TILELARGEUR, 16*TILEHAUTEUR));
                dataJeu.level.listeTileMobile.tab[5] = initTileMobile(5, 1, make_Vec2(228*TILELARGEUR, 16*TILEHAUTEUR), TILEHAUTEUR/32, 2, 3, make_Vec2(228*TILELARGEUR, TILEHAUTEUR), make_Vec2(228*TILELARGEUR, 16*TILEHAUTEUR));
                dataJeu.level.listeTileMobile.tab[6] = initTileMobile(3, 1, make_Vec2(245*TILELARGEUR, 5*TILEHAUTEUR), TILELARGEUR/32, 1, 3, make_Vec2(245*TILELARGEUR, 5*TILEHAUTEUR), make_Vec2(255*TILELARGEUR, 5*TILEHAUTEUR));

                dataJeu.level.finY = 3*TILEHAUTEUR;
                dataJeu.level.finX = 286*TILELARGEUR;
                dataJeu.level.debutX = 1;
                dataJeu.level.debutY = 5*TILEHAUTEUR;
                break;
            }

        case 3:
            {
                int level3[MAXLIGNE][MAXCOLONNE] = {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-2,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,186,187,187,187,187,188,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,228,229,238,229,229,239,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,228,229,229,229,229,239,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,25,17,17,17,26,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-2,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,228,238,229,238,229,230,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,29,40,41,42,30,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-2,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,186,187,187,187,187,187,229,229,229,229,239,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,53,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,53,53,-1,-1,-1,-2,-1,-2,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,228,229,229,229,229,229,229,229,229,229,230,-23,-1,-1,-1,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,189,190,191,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,19,17,17,17,17,17,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,186,187,187,188,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,54,-1,-1,-1,-1,-1,-1,189,190,191,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-1,-1,-1,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,50,31,31,52,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,57,56,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,237,229,229,229,229,238,229,187,187,187,187,188,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,231,232,231,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,37,38,37,38,39,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,0,-6,0,-6,0,-1,-1,-1,-1,-1,-1,228,238,229,230,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,54,-1,-1,-1,-1,-1,-1,233,232,233,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,237,229,229,238,229,229,229,238,229,229,229,239,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,189,190,191,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,240,241,242,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,37,38,39,38,39,47,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,83,85,-1,-1,-1,237,229,229,239,-1,-1,-1,83,85,-1,-1,-1,-1,-1,-1,-1,53,-1,-1,-1,54,-1,-1,-1,-1,-1,-1,232,233,233,-1,-1,-1,-1,-1,-1,-1,83,85,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,83,85,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,25,26,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,53,-1,53,-1,53,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,7,8,-1,-1,-23,-1,228,229,229,229,229,229,229,229,229,238,229,239,-1,-1,-21,-1,-1,-1,-1,-1,7,8,-1,-1,-1,-1,-1,-1,-1,-1,231,232,231,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,240,241,242,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,23,37,38,39,38,39,22,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,67,68,-1,-1,-1,237,229,238,239,-1,-1,-1,67,68,-1,-1,-1,-1,-1,-1,-1,54,-1,-1,-1,54,-1,-1,-1,-1,-1,-1,240,241,240,-1,-1,-1,-1,-1,-1,-1,67,68,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,67,68,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,29,30,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,57,51,60,51,56,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,12,13,83,84,34,35,36,34,35,36,34,34,35,36,34,35,36,34,34,35,36,34,35,36,34,18,12,13,-1,-1,-1,-1,-1,-1,-1,-1,240,241,242,-1,-1,-1,-1,189,190,191,-1,-1,-1,-1,232,233,233,-1,-1,-1,-1,-1,-1,19,17,17,17,17,17,17,17,17,17,17,17,77,17,17,17,17,17,17,17,17,17,17,17,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,65,66,-1,-1,-1,246,247,247,248,-1,-1,-1,65,66,-1,-1,-1,-1,-1,-1,-1,54,-1,-1,-1,54,-1,-23,-1,-1,-1,-1,249,250,251,-1,-1,-1,-1,-1,-1,-1,65,66,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,65,66,-1,-23,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-24,13,86,37,38,39,37,38,39,37,38,39,37,37,38,39,37,38,39,37,38,39,37,38,39,28,-22,13,-1,-1,-1,-1,-1,-1,-1,-1,240,241,242,-1,-1,-1,-1,231,232,231,-1,-1,-1,-1,241,241,242,-1,-1,-1,-1,-1,-1,23,24,24,24,24,24,24,37,38,39,37,38,39,24,24,37,38,39,24,37,37,37,38,39,22,-1,-1,-1,-1,-1,19,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
                                                    {17,36,20,36,17,20,36,17,17,36,17,34,36,36,17,36,20,36,17,20,36,17,17,36,17,34,36,36,17,36,20,36,17,20,36,17,17,36,17,34,36,36,17,36,20,36,17,20,36,17,17,36,17,34,36,36,17,36,20,36,17,20,36,17,17,36,17,34,36,36,18,-1,-1,19,17,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,50,51,52,-1,-1,-1,-1,-1,19,34,35,36,34,35,36,34,92,37,38,39,37,38,39,37,38,39,37,38,39,37,38,39,39,37,38,39,37,38,39,93,36,36,34,34,35,36,85,-1,-1,-1,232,233,233,-1,-1,-1,-1,240,241,242,-1,-1,-1,-1,242,241,241,-1,-1,-1,-1,-1,-1,23,37,38,39,37,38,39,37,38,39,24,24,24,24,37,38,39,37,38,39,37,37,38,39,28,-1,-1,-1,-1,-1,23,21,37,38,39,39,21,21,37,38,39,21,37,38,39,38,37,21,38,21,37,21,39,39}};
                dataJeu.level.nombreTileY = 23;
                dataJeu.level.nombreTileX = 238;
                dataJeu.level.listeBonus.nombreBonus = 0;
                dataJeu.level.listeTileAnima.nbTileAnima = 1;
                dataJeu.level.listeEnnemies.nombreEnnemi=0;
                chargeTabInMap(level3, dataJeu, 238, 23);
                dataJeu.level.listeTileMobile.nb_tile = 0;
                dataJeu.level.finY = 2*TILEHAUTEUR;
                dataJeu.level.finX = 222*TILELARGEUR;
                dataJeu.level.debutX = 2 * TILELARGEUR;
                dataJeu.level.debutY = 5*TILEHAUTEUR;
                break;
            }
        case 4:
            {
                int level4[MAXLIGNE][MAXCOLONNE] = {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,174,175,175,175,175,175,176,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,223,-1,-1,-1,-1,-1,174,175,175,175,175,175,176,-1,-1,-1,-1,-1,-1,201,181,181,181,181,181,182,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,192,193,193,193,193,194,-1,-1,-1,-1,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,223,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,223,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,216,217,-1,-1,-1,-1,-1,-1,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,224,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,3,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,221,222,-1,-23,-1,-1,-1,-1,-1,224,-1,-1,-1,-1,-1,-1,-1,-2,224,-1,-1,201,181,181,181,181,181,182,-1,-1,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-10,0,-10,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,3,3,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,213,-22,215,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,192,193,193,193,193,194,-1,-1,-1,174,175,175,175,175,175,176,-1,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,224,-23,-1,-1,-1,-1,223,-1,-1,-1,-1,-1,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,3,3,3,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,183,184,184,184,184,184,185,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,216,217,-1,-1,-1,-1,-1,221,222,-1,223,-1,-1,-1,-1,-1,224,-1,-1,-1,-1,174,175,175,175,175,175,176,-1,-1,-1,224,-1,-1,-1,-1,-2,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,3,3,3,3,3,3,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,180,182,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-2,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,225,235,226,226,235,226,236,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-1,-1,221,222,-1,-1,-1,-1,-1,221,222,-1,224,-1,-1,-1,-1,-1,224,-1,-1,-1,-1,-1,-1,-1,223,224,-1,-1,-1,-1,-1,224,-1,-1,-1,-1,-2,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-22,-1,-1,3,3,3,3,3,3,3,3,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,216,217,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-2,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,225,235,235,226,235,235,227,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,221,222,174,175,175,175,175,175,176,-1,224,-1,-1,-1,-22,-1,224,-1,-1,-1,-1,-1,-1,-1,224,224,-1,-1,-2,-2,-1,224,-1,-1,-1,-1,-2,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,186,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,221,222,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-6,0,-6,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-2,-1,-1,-1,-1,-2,-1,-1,-1,-1,49,-1,-1,234,226,226,226,226,226,227,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,221,222,-1,-1,-1,223,-1,221,222,-1,224,174,175,175,175,175,175,176,-2,-2,-1,-1,-1,-1,224,224,-1,-1,-2,-2,-1,224,-1,-1,-1,-1,-1,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,237,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,238,229,229,229,229,229,229,229,229,229,229,229,229,238,229,229,229,229,229,229,229,229,238},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,192,193,193,193,193,193,194,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,225,226,226,226,226,226,236,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,180,181,181,181,181,181,182,221,222,-1,-23,-1,224,-1,221,222,-1,224,-1,-1,-1,223,-1,224,-1,-2,-2,-1,-1,-1,-1,224,224,-1,-1,-1,-1,-1,224,-1,201,181,181,181,181,181,182,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,228,229,229,229,238,229,229,229,229,229,229,229,229,229,229,229,229,238,229,229,229,229,229,229,229,229,238,229,229,229,229,229,238,229,229,229,229,238,229,229,229,229,229,229,229,229,229,238,238,229,229,229,229},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,223,-1,221,222,-1,-1,-1,-1,-1,-1,189,190,190,190,191,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,-1,-1,214,-1,-1,-1,-1,-1,-1,234,226,235,235,226,235,236,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,223,-1,-1,-1,221,222,192,193,193,193,194,221,222,-1,224,-1,-1,-1,224,192,193,193,193,193,194,-1,-1,-1,224,224,-1,-1,-1,-23,-1,224,-1,-1,-1,-1,223,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,237,229,229,229,229,229,238,229,229,229,229,238,229,229,229,229,229,229,229,229,229,238,238,229,229,229,229,229,229,229,229,229,238,229,229,229,229,229,229,229,238,229,229,229,238,229,238,229,229,229,238,229,238},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,213,215,-1,-22,-1,-1,218,219,219,219,219,219,219,219,219,219,219,219,220,-1,215,-1,-23,-1,-1,215,213,-1,-1,-1,-1,-1,-1,-1,-1,224,-1,221,222,-1,-1,-1,-1,-1,-1,241,240,241,242,241,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,215,213,-1,-1,-21,-22,215,-1,213,-1,-1,-1,-1,-1,-1,-1,-1,-22,215,213,-1,-1,-1,-1,-1,-23,213,215,-1,-1,-1,-1,-1,-1,234,226,235,226,226,235,227,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,174,175,175,175,175,175,176,-1,-1,221,222,-1,-1,223,224,-1,221,222,-1,224,-1,-1,-1,224,-1,224,216,217,-1,-1,-1,-1,201,202,181,181,181,181,181,182,224,-1,-1,-1,-1,224,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,237,229,229,229,229,229,238,229,229,229,229,229,229,229,238,229,229,229,238,229,238,229,229,229,238,229,238,229,229,238,229,229,229,229,229,229,229,238,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229},
                                                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,183,184,184,184,184,184,184,185,177,177,-1,177,-1,-1,177,-1,177,-1,-1,183,184,184,184,184,184,184,184,184,184,185,-1,-1,-1,-1,-1,-1,224,-1,221,222,-1,-1,-1,-1,-1,-1,240,241,240,241,242,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,183,184,184,184,184,184,184,184,184,184,185,-1,-1,-1,-1,183,184,184,184,184,184,184,184,184,184,184,184,184,184,185,-1,-1,-1,-1,-1,225,226,226,226,226,226,236,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,223,-1,224,-1,-1,-1,221,222,-1,-1,224,224,-1,221,222,-1,224,-1,-1,-1,224,-1,224,221,222,-1,-1,-1,-1,-1,224,224,216,217,-1,-1,-1,224,-1,-1,-1,-1,224,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,237,229,229,238,229,229,229,229,229,229,229,238,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,238,229,229,229,229,229,229},
                                                    {187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,188,-1,-1,-1,-1,-1,225,235,226,226,226,226,226,236,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,225,235,226,226,235,226,226,226,226,226,236,-1,-1,-1,-1,-1,-1,224,-1,221,222,-1,-1,-1,-1,-1,-1,240,241,242,240,241,-1,-1,-1,-1,-1,-1,-1,186,187,187,187,187,187,187,187,187,187,188,-1,-1,-1,-1,225,235,226,226,235,226,226,226,226,226,236,-1,-1,-1,-1,225,235,226,226,235,226,226,226,226,226,235,226,226,226,236,-1,-1,-1,-1,-1,225,235,226,226,235,226,227,-1,-1,-1,-1,-1,-1,-1,-1,186,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,188,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,224,-1,224,-1,-1,-1,221,222,-1,-1,224,224,-1,221,222,-1,224,-1,-1,-1,224,-1,224,221,222,-1,-1,-1,-1,-1,224,224,221,222,-1,-1,-1,224,-1,-1,-1,-1,224,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,228,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,238,229,229,229,229,229,229,229,229,229,238,229,229,229,229,229,238,229,229,229,229,229,238,229,229,238,229,229,229,238,229,229,229},
                                                    {229,229,229,229,229,238,238,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,230,-1,-1,-1,-1,-1,225,235,235,226,235,235,235,227,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,225,235,235,226,235,235,226,235,235,235,227,-1,-1,-1,-1,-1,-1,224,-1,221,222,-1,-1,-1,-1,-1,-1,241,242,240,241,242,-1,-1,-1,-1,-1,-1,-1,228,229,238,238,229,229,229,229,229,229,230,-1,-1,-1,-1,225,235,235,226,235,235,226,235,235,235,227,-1,-1,-1,-1,225,235,235,226,235,235,226,235,235,235,235,235,235,235,227,-1,-1,-1,-1,-1,225,235,235,226,235,235,236,-1,-1,-1,-1,-1,-1,-1,-1,237,229,229,229,229,229,238,238,229,229,229,229,229,238,238,229,229,229,229,230,-1,-1,192,193,193,193,193,194,-1,-1,-1,224,-1,224,-1,-1,-1,221,222,-1,-1,224,224,-1,221,222,-1,224,-1,-1,-1,224,-1,224,221,222,-1,-1,-1,-1,-1,224,224,221,222,-1,-1,-1,224,-1,-1,-1,-1,224,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,228,229,229,229,238,229,229,229,229,229,238,229,229,229,229,229,238,229,229,238,229,229,229,238,229,229,229,229,229,229,229,229,238,229,229,229,229,229,229,229,229,229,229,229,238,229,229,229,229,229,229,238,229},
                                                    {229,229,229,229,229,238,229,229,229,229,229,229,238,238,229,229,229,229,229,238,229,229,229,239,-1,-1,-1,-1,-1,234,226,226,226,235,226,226,227,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,234,226,226,226,226,226,226,235,226,226,227,-1,-1,-1,-1,-1,-1,224,-1,221,222,-1,-1,-1,-1,-1,-1,242,242,241,240,241,-1,-1,-1,-1,-1,-1,-1,228,229,238,229,229,229,229,229,229,238,230,-1,-1,-1,-1,234,226,226,226,226,226,226,235,226,226,227,-1,-1,-1,-1,234,226,226,226,226,226,226,235,226,226,235,235,226,226,227,-1,-1,-1,-1,-1,234,226,226,226,226,226,227,-1,-1,-1,-1,-1,-1,-1,-1,237,229,229,229,229,229,238,229,229,229,229,229,229,238,229,229,229,229,229,239,-1,-1,-1,-1,216,217,-1,-1,-1,-1,-1,224,-1,224,-1,-1,-1,221,222,-1,-1,224,224,-1,221,222,-1,224,-1,-1,-1,224,-1,224,221,222,-1,-1,-1,-1,-1,224,224,221,222,-1,-1,-1,224,-1,-1,-1,-1,224,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,228,229,229,229,229,229,238,229,229,229,229,229,229,229,229,229,229,229,238,229,229,229,229,229,229,238,229,229,238,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,238,229,229},
                                                    {229,238,238,229,229,229,229,229,229,238,229,229,238,229,229,229,229,229,229,229,229,229,229,230,-1,-1,-1,-1,-1,225,226,226,226,226,226,226,236,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,225,226,226,226,226,226,226,226,226,226,236,-1,-1,-1,-1,-1,-1,224,-1,221,222,-1,-1,-1,-1,-1,-1,242,240,241,242,241,-1,-1,-1,-1,-1,-1,-1,237,229,229,229,229,229,238,229,229,238,239,-1,-1,-1,-1,225,226,226,226,226,226,226,226,226,226,236,-1,-1,-1,-1,225,226,226,226,226,226,226,226,226,226,235,226,226,226,236,-1,-1,-1,-1,-1,225,226,226,226,226,226,227,-1,-1,-1,-1,-1,-1,-1,-1,228,229,238,238,229,229,229,229,229,238,238,229,229,229,229,229,229,238,229,239,-1,-1,-1,-1,221,222,-1,-1,-1,-1,-1,224,-1,224,-1,-1,-1,221,222,-1,-1,224,224,-1,221,222,-1,224,-1,-1,-1,224,-1,224,221,222,-1,-1,-1,-1,-1,224,224,221,222,-1,-1,-1,224,-1,-1,-1,-1,224,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,237,229,238,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,238,229,229,229,229,238,229,229,229,229,238,238,229,229,229,229,229,238,238,229,229,229,229,229,238,229,229,229,229},
                                                    {229,229,229,229,238,229,229,229,238,238,229,229,229,229,229,229,238,229,229,229,229,229,229,239,-1,-1,-1,-1,-1,234,226,235,235,235,235,226,236,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,234,226,235,235,226,235,235,235,235,226,236,-1,-1,-1,-1,-1,-1,224,-1,221,222,-1,-1,-1,-1,-1,-1,241,242,241,241,241,-1,-1,-1,-1,-1,-1,-1,228,238,229,229,229,238,238,229,229,229,230,-1,-1,-1,-1,234,226,235,235,226,235,235,235,235,226,236,-1,-1,-1,-1,234,226,235,235,226,235,235,235,235,226,235,235,235,226,236,-1,-1,-1,-1,-1,234,226,235,235,226,235,236,-1,-1,-1,-1,-1,-1,-1,-1,228,229,229,229,229,238,229,229,229,229,229,229,238,229,229,229,238,238,229,230,-1,-1,-1,-1,221,222,-1,-1,-1,-1,-1,224,-1,224,-1,-1,-1,221,222,-1,-1,224,224,-1,221,222,-1,224,-1,-1,-1,224,-1,224,221,222,-1,-1,-1,-1,-1,224,224,221,222,-1,-1,-1,224,-1,-1,-1,-1,224,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,237,229,229,238,229,229,229,229,238,238,229,229,229,229,229,238,238,229,229,229,229,229,238,229,229,229,229,229,229,229,229,229,238,229,229,229,229,229,238,238,229,229,229,229,229,229,238,229,229,229,229,229,229},
                                                    {229,229,238,229,229,229,229,229,229,229,229,229,229,229,229,238,229,229,229,229,229,229,229,230,-1,-1,-1,-1,-1,234,226,235,226,226,235,226,227,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,234,226,235,226,226,235,226,226,235,226,227,-1,-1,-1,-1,-1,-1,224,-1,221,222,-1,-1,-1,-1,-1,-1,241,241,240,241,242,-1,-1,-1,-1,-1,-1,-1,237,229,229,229,229,229,229,238,229,229,239,-1,-1,-1,-1,234,226,235,226,226,235,226,226,235,226,227,-1,-1,-1,-1,234,226,235,226,226,235,226,226,235,226,235,226,235,226,227,-1,-1,-1,-1,-1,234,226,235,226,226,235,236,-1,-1,-1,-1,-1,-1,-1,-1,237,229,229,238,229,229,229,229,229,229,238,229,229,229,229,229,229,229,229,239,-1,-1,-1,-1,221,222,-1,-1,-1,-1,-1,224,-1,224,-1,-1,-1,221,222,-1,-1,224,224,-1,221,222,-1,224,-1,-1,-1,224,-1,224,221,222,-1,-1,-1,-1,-1,224,224,221,222,-1,-1,-1,224,-1,-1,-1,-1,224,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,228,229,229,229,229,229,238,229,229,229,229,229,238,238,229,229,229,229,229,229,238,229,229,229,229,229,229,229,229,238,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229},
                                                    {229,229,229,238,229,229,229,229,229,229,229,229,229,229,229,238,229,229,229,229,229,229,229,230,-1,-1,-1,-1,-1,225,226,226,226,226,226,226,236,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,225,226,226,226,226,226,226,226,226,226,236,-1,-1,-1,-1,-1,-1,224,-1,221,222,-1,-1,-1,-1,-1,-1,240,241,242,240,241,-1,-1,-1,-1,-1,-1,-1,237,229,229,229,229,229,229,229,229,229,230,-1,-1,-1,-1,225,226,226,226,226,226,226,226,226,226,236,-1,-1,-1,-1,225,226,226,226,226,226,226,226,226,226,235,226,226,226,236,-1,-1,-1,-1,-1,225,226,226,226,226,226,227,-1,-1,-1,-1,-1,-1,-1,-1,228,229,229,229,238,229,229,229,229,229,229,238,229,229,229,229,229,229,229,230,-1,-1,-1,-1,221,222,-1,-1,-1,-1,-1,224,-1,224,-1,-1,-1,221,222,-1,-1,224,224,-1,221,222,-1,224,-1,-1,-1,224,-1,224,221,222,-1,-1,-1,-1,-1,224,224,221,222,-1,-1,-1,224,-1,-1,-1,-1,224,-1,224,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,237,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,229,238,229,229,229,229,229,229,229,229}};
                dataJeu.level.nombreTileY = 44;
                dataJeu.level.nombreTileX = 292;
                dataJeu.level.listeBonus.nombreBonus = 0;
                dataJeu.level.listeTileAnima.nbTileAnima = 1;
                dataJeu.level.listeEnnemies.nombreEnnemi=0;
                chargeTabInMap(level4, dataJeu, 292, 44);
                dataJeu.level.listeTileMobile.nb_tile = 0;
                dataJeu.level.finY = 12*TILEHAUTEUR;
                dataJeu.level.finX = 276*TILELARGEUR;
                dataJeu.level.debutX = 2 * TILELARGEUR;
                dataJeu.level.debutY = 15*TILEHAUTEUR;
                break;
            }
        case 5:
            {
                int level5[MAXLIGNE][MAXCOLONNE] = {{163,164,-1,-1,-1,170,116,116,115,100,117,115,115,117,115,115,115,163,115,100,100,100,100,100,115,117,116,100,100,116,115,115,100,163,100,116,163,116,116,163,163,163,100,163,117,117,117,116,117,100,163,116,117,116,116,115,163,163,115,100,163,100,115,115,163,163,117,163,163,116,163,163,117,100,117,115,116,100,100,163,116,115,116,117,116,100,163,117,117,117,100,100,115,100,116,100,115,115,117,115,163,116,100,117,115,117,163,116,163,163,163,163,116,100,100,116,116,115,100,117,163,116,163,117,100,115,100,163,163,116,115,116,116,163,117,100,163,117,115,163,115,115,163,163,117,100,163,163,116,100,100,117,117,116,116,116,117,117,100,100,117,117,100,100,117,115,117,100,163,100,115,116,117,115,116,116,117,116,115,100,100,115,115,117,115,117,115,163,163,163,115,163,116,100,116,100,116,163,100,115,117,163,116,115,100,115,116,163,100,115,117,116,100,163,163,100,100,115,116,100,116,100,115,116,117,117,116,115,117,100,115,100,115,116,115,116,100,163,100,116,115,100,115,116,163,100,100,116,163,117,117,115,163,100,100,100,116,117,100,115},
                                                    {163,101,-1,-1,-1,123,100,117,117,116,163,163,100,100,115,116,100,116,163,115,116,100,116,100,163,117,117,163,163,163,100,100,115,163,115,163,115,100,100,116,115,117,117,115,163,117,115,100,117,116,163,116,116,115,117,163,115,163,117,163,163,117,116,115,117,115,100,117,100,163,115,117,117,163,100,117,100,163,163,116,115,117,117,116,163,163,116,115,100,115,117,115,163,163,117,115,100,116,117,116,100,116,117,163,117,115,115,116,115,163,115,163,117,116,116,163,117,100,163,115,117,117,115,116,163,115,163,117,163,115,100,100,115,163,116,117,163,163,115,117,116,115,116,115,115,100,116,117,117,117,116,100,117,116,117,115,115,100,100,116,116,117,117,115,163,115,163,100,163,163,117,163,117,100,115,163,116,116,117,163,116,163,115,117,115,163,163,163,116,116,163,100,117,163,163,163,163,115,163,163,117,116,100,163,115,163,100,163,100,115,117,117,100,116,100,117,100,117,116,116,116,100,115,117,100,115,115,100,116,116,163,117,117,115,115,163,115,116,117,117,100,115,117,115,100,100,117,117,116,100,116,100,163,117,100,115,115,117,115,115},
                                                    {100,125,-1,-1,-1,121,117,115,117,117,163,115,100,116,163,117,100,115,117,116,115,163,100,115,100,100,116,115,115,116,115,163,163,115,115,100,163,100,116,116,100,116,163,115,100,116,115,100,116,117,117,163,100,117,115,117,116,116,115,163,116,117,117,115,115,116,100,116,115,117,117,100,100,163,115,100,163,163,163,116,163,100,115,116,163,117,100,117,116,115,115,115,100,116,116,163,117,163,100,116,163,115,117,163,117,100,117,117,100,117,163,116,117,116,117,116,117,100,116,115,117,117,117,117,116,115,100,100,116,116,115,100,115,117,116,117,117,163,116,115,115,100,117,117,117,100,100,100,100,163,116,116,115,163,115,117,100,100,115,115,163,116,117,100,100,115,116,116,100,163,163,163,115,163,117,117,163,116,100,163,100,100,100,163,117,116,163,115,116,117,115,100,116,117,117,117,100,115,115,163,100,163,115,115,163,163,163,117,117,115,116,117,115,100,117,117,116,115,117,115,117,116,163,116,115,163,115,115,100,100,163,115,115,117,117,116,100,117,100,115,116,116,116,163,117,117,116,163,116,115,116,163,100,100,116,117,163,116,116,117},
                                                    {163,101,-1,-1,-1,123,100,100,117,163,115,117,116,116,163,117,115,115,116,100,115,163,117,116,163,100,117,117,115,116,163,116,116,100,100,116,115,117,117,115,116,117,115,116,116,115,115,117,100,115,100,117,100,100,115,100,100,100,117,115,116,115,116,117,163,116,163,116,115,116,100,163,116,115,117,115,100,100,116,117,117,163,163,117,117,117,116,163,100,115,100,117,100,163,115,163,100,117,163,115,100,100,116,116,100,100,115,163,115,115,115,116,117,117,117,100,100,117,116,100,100,117,117,116,116,100,116,163,115,117,116,100,163,100,100,115,163,100,116,116,117,163,115,117,163,116,100,163,116,163,100,163,115,163,117,117,115,163,115,115,115,117,115,100,115,116,163,116,115,115,117,100,117,100,100,163,115,100,100,163,117,117,115,163,163,117,115,115,116,116,163,117,117,117,163,117,115,116,100,117,163,100,117,117,100,117,115,117,116,115,116,163,116,117,115,116,116,115,116,115,117,100,115,115,163,115,115,117,116,100,100,116,116,117,116,117,115,115,116,115,117,100,116,116,117,163,117,115,115,117,116,100,115,163,117,163,163,116,100,117},
                                                    {116,125,-1,-1,-1,121,116,100,116,163,100,163,163,115,117,117,163,116,117,117,163,100,163,163,117,100,115,117,163,100,163,117,115,116,163,115,163,100,116,163,117,163,163,163,116,116,116,117,115,163,117,116,117,117,115,116,117,117,163,117,100,117,117,115,163,116,115,100,163,163,163,116,116,163,115,163,115,100,116,117,100,115,115,100,116,117,117,100,117,163,117,116,100,115,100,100,115,116,116,116,116,163,100,163,117,117,163,115,100,100,117,117,163,116,163,115,115,100,163,100,100,115,100,163,116,117,115,117,117,116,100,100,163,115,115,116,163,117,163,116,100,116,116,100,115,100,163,163,117,100,100,163,116,100,100,117,115,116,100,163,115,115,163,117,115,115,100,117,115,117,163,100,100,100,115,115,100,117,163,163,116,100,116,100,117,115,117,100,163,115,100,115,116,100,163,163,117,117,100,117,100,116,117,116,100,117,115,163,100,100,163,100,163,116,116,117,115,100,117,116,117,116,163,116,116,163,117,117,115,117,115,163,117,115,115,163,115,115,117,163,116,100,163,115,100,117,116,163,116,100,115,115,117,163,117,115,115,116,115,117},
                                                    {116,126,-1,-1,-1,123,100,163,163,115,100,115,115,117,117,100,100,163,100,115,116,100,117,117,116,117,115,117,117,100,115,100,117,117,163,163,115,100,100,115,117,117,116,117,115,117,100,116,117,115,163,117,115,116,115,100,117,115,163,115,163,100,115,117,117,115,163,116,116,117,116,117,115,117,117,163,163,116,163,115,100,100,163,116,163,117,100,117,163,100,163,115,115,115,116,117,117,117,116,117,100,115,163,117,100,117,100,117,100,115,116,117,116,117,116,117,100,163,100,100,117,100,116,117,100,115,116,116,116,116,117,115,115,117,163,117,116,100,116,163,116,115,115,100,117,163,163,100,116,115,116,163,115,116,117,115,100,163,115,115,117,163,116,115,163,115,163,116,116,163,116,100,115,117,100,117,117,117,100,117,116,117,163,116,116,100,117,100,163,115,117,115,115,115,115,100,117,163,163,117,100,163,163,163,116,100,163,115,116,117,117,100,116,115,100,117,100,115,163,100,163,117,115,163,117,163,163,115,100,115,115,116,117,163,163,163,163,116,116,116,115,115,117,100,116,117,163,117,163,100,100,117,163,100,117,115,100,116,100,115},
                                                    {116,101,-1,-1,-1,123,163,100,116,163,163,117,116,115,163,117,163,163,163,116,100,117,163,116,115,100,163,117,117,100,117,116,117,115,117,100,117,100,117,100,117,117,100,163,100,117,115,100,100,100,163,100,163,115,100,100,116,100,116,115,116,115,117,115,163,117,117,116,115,163,116,100,117,100,115,115,116,115,117,117,163,116,100,163,116,115,100,116,116,163,163,163,116,116,100,115,163,115,100,115,163,100,116,116,100,116,115,163,100,100,163,116,115,116,116,115,100,117,116,115,100,163,116,116,100,117,163,115,116,117,117,163,100,100,116,163,117,100,116,116,115,163,163,163,163,163,117,117,116,116,116,100,116,100,100,117,117,100,116,117,117,116,116,115,117,100,115,163,117,116,116,115,163,116,117,163,115,100,115,100,117,100,163,163,163,117,117,163,116,117,100,115,117,100,163,100,100,117,116,100,117,117,163,115,115,115,115,100,100,115,100,117,116,117,117,115,163,115,116,100,116,117,163,116,115,115,115,117,116,115,163,115,116,117,115,163,116,116,116,115,117,100,100,163,115,117,163,115,100,163,163,116,116,163,116,115,117,100,115,116},
                                                    {116,126,-1,-1,-1,123,115,116,116,116,100,116,117,163,163,115,100,100,117,116,115,117,100,163,163,117,100,115,163,163,116,163,100,163,116,116,116,117,100,116,163,163,117,163,163,116,116,100,117,117,116,116,163,116,116,115,117,100,116,163,117,163,117,163,100,117,115,163,116,163,100,115,163,115,100,116,117,163,163,100,163,163,116,100,163,115,115,163,163,163,115,163,117,115,116,117,100,115,117,163,116,115,116,115,116,116,116,100,116,117,116,115,163,116,115,100,115,115,163,163,117,100,116,116,116,100,163,163,100,115,117,163,163,117,163,100,115,163,117,100,100,116,116,115,100,116,163,100,117,116,163,100,116,116,116,100,115,117,163,117,100,117,116,163,163,117,117,100,116,115,115,117,116,115,100,163,116,116,100,116,115,117,117,117,117,116,117,116,116,115,116,100,116,116,117,163,163,117,163,100,163,116,163,117,117,100,100,117,116,163,116,116,116,115,117,117,117,115,116,163,163,163,115,116,115,115,117,100,117,117,116,116,100,163,100,117,117,163,117,116,117,100,117,116,163,115,116,100,115,100,163,100,163,115,100,163,116,163,163,163},
                                                    {115,126,-1,-1,-1,122,115,115,115,100,117,117,117,100,163,163,100,163,163,115,117,115,163,100,163,163,116,100,163,100,117,163,163,163,116,115,115,163,117,117,163,163,115,117,115,163,117,115,117,115,116,116,163,100,115,117,100,100,115,163,116,100,163,163,116,115,116,116,100,115,117,117,117,117,163,115,117,115,100,115,163,163,163,116,116,117,115,117,117,117,116,115,115,100,117,117,115,163,163,115,116,115,100,100,117,163,115,100,115,115,100,100,100,116,163,100,115,100,115,100,117,163,115,116,100,100,116,115,115,163,115,116,115,117,100,163,163,116,100,115,163,115,115,100,116,116,100,115,163,100,117,163,116,117,163,100,117,116,115,163,116,117,116,115,117,116,163,100,100,163,100,100,163,163,115,100,100,116,100,115,100,100,163,115,163,100,100,100,115,163,116,100,100,163,163,115,116,100,163,116,116,115,115,117,116,100,117,115,117,115,117,115,100,116,115,115,163,117,163,163,115,115,163,115,116,115,100,117,116,117,116,116,117,163,116,116,116,100,115,116,117,163,117,115,115,117,115,116,116,163,115,117,116,116,117,100,163,100,117,115},
                                                    {117,101,-1,-1,-1,122,117,163,115,100,163,100,117,116,116,116,117,100,163,163,117,163,116,116,163,117,116,116,115,117,163,100,117,100,117,116,116,117,117,115,100,115,117,163,163,116,116,115,100,115,116,163,163,117,100,115,100,163,117,163,117,100,116,116,163,100,115,163,163,100,117,115,116,100,116,100,115,163,163,117,163,115,115,100,163,117,100,116,163,115,163,100,116,116,117,116,117,117,117,117,115,115,163,163,100,115,100,115,116,117,163,115,117,115,163,100,117,117,116,100,163,117,116,116,116,115,115,163,117,116,117,115,100,100,100,100,117,117,116,163,116,100,163,117,100,115,100,163,163,100,116,100,100,115,100,115,116,117,117,100,115,115,163,100,116,116,100,116,163,100,100,116,116,100,163,117,117,117,100,117,115,163,116,163,117,163,116,116,163,115,163,117,115,115,117,163,116,117,117,100,116,115,116,117,117,116,117,117,100,163,116,115,115,117,117,117,117,163,100,116,163,100,116,117,100,116,117,117,115,117,163,100,115,163,117,100,163,163,116,100,116,163,100,115,115,163,163,115,100,115,100,117,100,115,100,117,100,117,100,115},
                                                    {117,125,-1,-1,-1,123,116,163,100,163,117,163,115,163,117,115,117,117,163,100,115,115,115,163,100,116,117,116,115,116,116,116,163,100,117,163,163,163,100,115,116,115,117,117,163,163,116,100,163,117,115,115,116,100,116,117,163,100,116,116,117,115,117,100,117,163,115,115,116,115,117,117,115,116,117,115,100,100,115,115,100,115,115,100,100,116,100,115,100,100,100,163,100,116,100,163,117,116,163,117,117,163,163,100,100,117,163,116,100,163,163,163,117,163,117,117,115,116,116,163,117,117,163,117,163,116,117,163,116,117,115,163,116,116,100,100,117,115,100,116,163,117,100,117,163,116,115,100,163,115,117,100,100,117,116,116,115,163,163,115,163,116,163,117,117,163,100,116,115,115,117,115,117,100,115,115,100,115,115,116,100,100,117,116,100,116,117,163,163,117,116,163,117,163,116,115,163,117,116,163,163,163,115,117,100,100,100,163,100,116,100,163,163,117,163,115,116,100,116,100,100,116,100,115,115,115,117,100,115,163,115,100,115,116,163,115,115,115,115,115,116,115,117,115,117,116,163,100,100,117,163,163,117,117,163,115,100,100,115,115},
                                                    {117,101,-1,-1,-1,102,115,163,117,116,163,117,100,100,100,116,163,100,100,116,100,100,116,115,116,163,116,117,117,116,116,116,116,100,116,116,163,100,163,115,115,100,117,100,163,115,117,117,163,100,115,116,116,115,117,100,116,116,100,100,116,116,100,117,116,117,115,100,163,117,116,116,116,115,100,116,100,163,116,117,163,115,163,116,117,117,117,115,163,117,116,115,116,117,100,115,163,115,163,163,115,117,115,115,115,163,116,117,116,100,100,163,115,115,163,116,100,117,100,163,163,163,100,163,100,163,115,115,163,163,116,116,100,115,116,115,116,115,117,117,115,115,116,115,115,100,117,116,100,116,100,163,100,117,117,163,100,116,116,117,100,100,100,116,115,100,100,100,163,163,117,117,100,117,100,115,117,100,116,117,100,163,100,163,115,100,100,116,116,117,100,163,100,117,117,163,163,100,115,115,116,116,115,117,115,100,115,115,116,100,163,116,115,116,117,163,100,117,163,116,116,117,100,117,100,117,117,117,117,116,163,115,115,116,163,116,116,116,115,163,116,163,115,117,115,117,115,115,117,163,117,115,100,163,117,115,117,100,100,163},
                                                    {117,125,-1,-1,-1,121,100,163,163,116,117,116,116,116,115,116,163,116,100,100,117,100,116,115,163,116,116,100,163,116,115,100,163,116,116,117,100,116,163,115,115,115,116,116,117,117,100,100,116,163,116,163,100,115,117,163,100,117,115,117,100,100,100,117,117,100,117,116,115,163,116,115,116,100,116,100,100,163,117,117,117,115,100,116,116,116,100,163,115,100,115,117,116,100,117,115,115,115,117,117,163,116,115,100,115,163,117,163,100,116,115,115,117,163,163,115,163,116,163,100,100,100,117,115,117,100,163,115,116,163,117,116,117,117,117,100,163,116,163,100,115,163,116,115,100,115,115,163,115,100,163,116,116,100,163,116,100,117,100,117,163,115,116,117,163,163,116,115,163,116,117,163,116,163,163,100,116,115,115,100,163,100,100,117,117,116,100,115,100,115,117,163,115,163,115,163,115,117,116,117,116,117,100,100,116,117,100,116,115,116,117,116,100,163,115,117,116,116,117,115,115,117,116,117,115,100,100,115,116,100,117,115,100,163,163,117,163,100,163,100,116,117,115,116,117,163,116,100,117,116,163,117,117,163,116,100,116,115,117,163},
                                                    {163,126,-1,-1,-1,123,117,163,116,117,116,100,117,163,115,163,163,116,116,115,117,115,117,117,163,117,163,115,100,100,117,117,116,115,163,116,163,115,115,100,117,100,117,117,163,100,117,116,115,163,115,116,100,117,117,100,117,100,163,115,100,115,116,100,115,163,115,100,115,116,100,116,117,100,117,116,163,163,163,116,115,116,115,116,116,163,163,117,100,100,116,116,115,117,117,163,115,100,117,117,163,100,117,163,116,100,163,115,100,100,117,115,100,100,116,100,163,117,100,115,116,115,117,116,100,100,115,116,116,117,116,100,163,115,100,116,116,117,115,163,163,100,117,116,117,163,115,163,115,163,100,115,115,117,116,115,163,116,115,115,117,116,117,163,116,115,116,115,115,163,163,100,116,117,117,115,100,115,163,100,163,115,163,115,117,163,117,115,163,163,117,117,163,115,115,116,115,115,100,115,100,100,163,116,117,100,116,116,163,163,163,116,116,163,163,100,117,115,117,115,116,115,100,116,117,117,117,163,116,116,117,100,117,163,115,115,163,117,100,115,100,116,116,116,115,163,117,116,163,115,117,115,115,116,163,116,117,100,117,115},
                                                    {116,101,-1,-1,-1,121,116,117,163,100,115,117,117,116,117,163,115,163,116,117,100,117,163,163,116,163,115,163,115,100,163,163,117,100,163,100,115,163,100,163,115,116,117,116,115,115,117,117,115,117,116,116,117,116,100,116,163,117,116,117,163,117,100,100,117,163,163,116,115,117,116,116,117,100,163,117,100,163,116,117,115,163,100,100,115,100,116,117,100,116,100,117,100,100,115,117,117,163,100,163,116,163,116,115,100,115,115,163,116,100,163,116,115,163,163,115,100,117,163,163,163,117,163,117,163,117,163,163,115,100,163,163,100,116,163,117,163,116,100,115,100,163,116,116,116,115,115,100,117,163,163,115,117,115,100,116,117,163,115,100,115,115,100,115,100,116,163,163,116,116,115,116,163,163,116,117,117,163,163,116,117,100,163,116,116,116,100,116,163,163,115,117,163,116,116,116,100,115,116,117,100,163,115,100,116,115,117,100,117,117,100,100,117,115,100,117,100,115,163,100,115,116,115,163,100,117,163,117,116,163,115,163,100,115,115,100,117,117,115,163,163,117,117,163,117,116,163,100,115,115,100,116,117,116,100,117,100,100,100,163},
                                                    {116,126,-1,-1,-1,122,115,116,117,163,163,117,100,163,100,116,163,115,115,115,117,116,100,117,100,116,100,100,116,116,117,163,163,115,100,117,115,115,117,117,100,115,116,163,116,100,100,116,100,117,115,116,100,100,115,163,163,116,115,163,100,163,163,115,115,100,116,163,117,100,117,116,100,117,163,100,100,117,100,115,117,100,115,100,163,100,115,100,116,100,116,117,163,100,100,100,116,116,115,116,100,163,117,116,100,100,115,115,116,115,163,163,100,100,115,100,163,163,116,100,117,163,115,100,115,115,100,117,163,117,163,117,117,116,115,163,116,116,115,115,117,116,116,100,163,117,115,163,117,163,117,117,163,115,117,100,163,117,100,115,115,115,116,115,163,100,163,163,116,117,116,116,117,115,163,163,115,116,163,116,163,100,117,115,163,116,100,116,117,100,163,100,116,100,100,115,100,115,163,100,115,117,115,117,115,163,163,117,100,117,115,116,115,100,117,117,115,116,115,117,115,116,100,163,116,117,116,163,100,100,100,117,117,100,115,117,117,117,163,117,115,116,117,115,115,115,116,116,100,163,100,117,117,163,163,117,163,117,163,117},
                                                    {100,126,-1,-1,-1,123,115,116,100,116,115,115,163,115,116,116,116,100,117,115,116,117,163,117,117,100,116,115,100,115,100,163,116,117,116,100,116,115,100,117,163,163,100,163,117,115,100,115,100,116,163,117,163,117,116,117,163,100,116,163,100,163,116,115,115,117,100,100,163,117,163,117,100,100,115,116,117,163,115,100,100,163,115,117,115,116,100,116,117,163,117,116,117,115,117,163,116,116,163,117,115,100,163,100,100,117,163,163,116,116,100,117,117,100,117,100,116,117,115,117,163,116,117,100,116,115,116,100,117,116,100,116,115,115,115,117,100,116,115,117,116,163,163,116,115,115,115,100,100,100,100,116,100,100,116,116,117,115,117,163,117,100,116,163,117,163,115,163,100,163,116,115,117,117,116,100,100,115,163,100,100,115,117,100,117,100,117,100,115,163,100,163,163,100,117,115,163,100,117,117,163,117,115,100,117,116,163,100,115,116,116,116,117,100,117,117,163,116,115,117,163,100,117,116,117,100,115,100,117,115,100,115,116,117,116,100,116,115,116,116,100,163,115,100,100,115,163,100,117,116,163,115,117,116,100,117,115,117,115,115},
                                                    {116,101,-1,-1,-1,121,115,115,163,163,117,115,163,115,163,100,115,115,100,163,117,117,163,163,117,115,100,100,163,115,163,115,116,163,100,115,100,100,116,116,116,116,115,100,100,117,115,116,116,115,117,115,117,100,116,100,100,100,115,117,163,115,163,163,163,117,116,115,115,115,100,117,163,100,116,117,116,163,100,163,117,115,117,115,100,100,100,115,115,100,116,163,163,116,116,163,117,116,100,117,116,116,116,117,163,116,117,116,163,163,163,117,116,115,163,163,115,100,163,163,116,100,117,100,117,100,117,117,116,115,100,116,100,163,116,115,117,163,163,116,117,117,163,117,117,117,116,115,163,115,115,100,163,117,163,163,115,116,163,115,117,100,100,115,116,100,163,163,117,115,100,100,117,115,100,115,117,116,163,115,115,117,116,116,163,115,115,117,100,163,100,163,163,116,116,163,116,117,117,115,117,100,163,115,117,116,100,116,117,115,116,115,116,163,115,116,117,115,116,115,100,100,116,163,163,163,116,116,115,115,163,117,100,116,163,163,115,100,100,117,163,163,115,116,100,117,100,100,115,116,117,115,117,163,115,115,115,115,116,117},
                                                    {116,126,-1,-1,-1,123,117,163,163,115,115,117,163,116,100,116,100,100,116,117,163,100,163,100,115,117,100,115,116,116,115,117,116,115,115,115,100,100,115,100,117,163,100,115,163,117,115,116,100,163,117,163,116,115,116,117,117,100,115,163,163,117,116,163,117,115,116,163,115,100,115,163,115,100,115,116,117,117,163,163,116,115,100,163,163,163,117,117,100,117,117,163,117,115,116,117,163,100,117,116,115,116,116,116,100,116,100,163,117,117,115,115,116,100,163,117,100,117,115,115,163,163,100,116,115,116,115,163,116,163,115,115,116,115,117,115,100,117,115,100,115,115,116,100,163,116,115,116,163,117,163,163,115,116,116,100,116,163,117,100,116,117,163,100,100,116,117,117,163,115,117,116,115,100,115,116,117,117,117,163,163,117,163,163,115,163,115,163,163,163,117,163,115,100,163,100,115,116,100,115,116,115,116,115,116,116,116,116,163,116,116,100,163,116,117,163,117,163,163,163,115,163,115,117,100,100,115,116,117,163,100,163,116,115,115,100,115,115,116,115,116,115,163,116,116,163,163,116,117,117,116,117,116,163,117,115,116,163,116,117},
                                                    {116,126,-1,-1,-1,121,100,115,163,115,117,100,116,115,163,163,116,100,100,163,100,116,163,163,116,100,163,117,100,117,116,115,116,116,100,117,163,115,116,116,100,163,100,116,117,116,115,115,117,116,163,115,100,116,117,117,100,115,163,163,115,117,117,115,115,115,115,117,117,100,100,117,115,100,100,116,117,116,100,117,100,100,115,116,100,100,115,115,163,100,115,163,116,115,163,116,117,115,100,100,116,163,100,115,117,115,117,116,116,163,116,117,100,117,116,116,116,115,115,117,116,115,117,163,100,100,117,116,116,117,163,163,117,115,116,117,163,163,100,116,117,100,115,100,100,163,100,115,115,116,115,115,116,100,116,115,100,115,115,163,116,115,115,116,115,116,116,100,115,163,163,115,117,115,115,100,117,115,117,116,100,100,117,117,163,163,116,163,100,115,163,163,163,117,163,163,117,117,117,116,117,163,115,163,163,115,100,115,117,163,115,117,115,100,116,163,100,117,117,115,163,116,115,115,117,163,100,115,117,163,163,116,115,116,117,100,116,117,116,116,100,115,117,117,100,100,117,117,115,115,100,163,117,116,115,116,116,116,163,115},
                                                    {116,101,-1,-1,-1,123,163,163,100,117,115,163,100,117,117,115,115,116,117,100,100,100,117,100,115,115,163,163,100,100,115,163,116,117,163,115,115,163,115,116,116,100,117,115,100,115,163,100,117,117,117,116,116,115,117,163,116,115,117,116,116,116,115,116,117,100,117,116,115,117,163,163,115,100,117,115,117,117,163,117,163,115,117,163,163,100,100,163,115,100,116,115,115,116,100,117,115,100,163,163,100,100,100,115,117,163,116,117,100,115,117,116,117,163,163,163,163,115,117,115,100,115,100,163,100,116,100,117,116,163,115,163,100,116,117,163,117,116,100,117,100,163,117,100,100,100,115,163,100,100,117,100,163,163,117,117,116,100,115,115,117,117,117,117,116,163,116,115,116,115,115,115,115,117,116,117,115,163,116,117,116,100,115,115,115,115,115,117,100,116,117,100,116,115,163,116,116,117,116,163,117,163,100,100,115,116,163,117,117,163,163,115,117,163,116,116,116,116,100,163,116,117,115,116,117,116,117,117,117,117,100,116,116,117,100,163,100,115,117,115,100,163,100,116,116,100,100,116,117,163,117,115,117,117,163,163,100,115,100,100},
                                                    {117,125,-1,-1,-1,123,100,115,117,115,100,163,163,100,100,115,115,115,116,163,116,116,116,117,115,100,100,115,115,100,163,163,117,100,117,100,100,115,116,115,115,116,163,117,116,116,163,100,117,115,115,117,116,117,100,115,116,117,115,115,115,115,116,115,117,117,116,163,117,163,117,116,100,116,116,100,163,100,115,116,100,117,116,116,100,100,117,116,116,117,117,116,115,117,115,115,115,115,100,117,100,163,115,163,100,163,115,115,116,115,116,100,117,115,100,163,116,100,163,163,117,163,100,115,116,117,163,116,163,115,115,115,115,100,100,115,116,100,117,117,116,100,117,116,115,115,100,117,100,100,115,116,117,117,117,163,163,116,100,116,115,117,116,117,116,115,115,100,115,117,116,115,163,100,117,100,100,163,117,100,115,100,116,163,117,163,100,115,100,163,115,117,115,115,117,100,116,100,163,116,115,116,115,163,163,115,100,163,115,115,116,100,115,163,163,116,117,116,115,117,116,163,117,117,163,163,100,115,117,115,163,163,116,116,116,163,100,116,115,116,115,100,116,116,163,100,116,100,115,100,117,116,100,163,116,163,100,100,117,100},
                                                    {100,101,-1,-1,-1,123,116,115,116,100,117,100,163,115,115,115,115,116,100,115,100,116,100,117,115,116,116,163,163,117,163,116,117,100,100,117,115,115,117,116,163,163,117,117,116,117,100,163,100,117,100,116,163,115,115,100,100,163,163,117,117,100,115,100,163,100,117,163,163,100,116,116,115,163,116,116,100,115,115,116,116,163,117,100,116,115,116,163,115,117,100,115,163,100,100,100,116,100,100,115,163,117,163,115,115,117,116,116,117,115,117,100,116,115,100,163,100,100,115,116,115,163,116,100,116,115,117,117,163,115,115,163,116,163,117,116,163,163,115,117,117,117,117,117,116,116,117,116,163,117,117,116,117,115,163,116,115,116,100,115,115,100,100,117,116,163,115,117,115,100,100,115,100,117,100,163,116,117,100,116,116,163,115,115,115,115,117,115,163,163,100,100,100,117,163,117,117,115,115,116,116,117,117,115,163,100,100,100,100,115,115,115,100,116,116,115,116,100,117,116,115,117,115,115,116,115,117,100,115,117,117,116,163,116,163,100,100,100,115,163,163,163,100,117,100,100,163,116,117,100,117,100,163,116,100,116,163,163,117,116},
                                                    {115,125,-1,-1,-1,122,116,163,115,116,163,100,163,163,115,115,100,163,117,163,117,117,116,116,100,115,163,116,115,116,115,115,117,115,117,163,117,100,100,163,163,117,116,115,117,116,116,163,115,115,115,116,115,115,100,115,116,163,100,100,116,163,117,115,116,163,115,100,116,116,115,100,115,115,100,100,117,163,115,100,115,115,115,100,116,163,163,100,116,117,100,117,100,117,115,115,115,115,116,163,100,115,116,115,100,100,116,117,117,163,115,116,100,117,163,100,116,163,163,115,163,117,115,115,115,163,115,163,117,100,100,116,116,163,163,117,116,116,115,100,116,115,116,115,115,117,163,100,100,116,117,116,163,117,116,163,116,163,115,163,117,115,163,117,163,163,115,117,100,117,116,116,117,116,163,115,116,163,117,100,116,115,117,100,115,117,116,163,117,100,117,115,115,163,100,117,116,100,116,100,100,115,116,163,117,115,116,117,117,163,117,115,163,100,100,116,115,117,163,116,115,117,117,115,100,100,100,115,117,116,163,117,100,117,100,117,115,117,115,117,116,116,117,116,163,100,163,117,117,115,117,100,115,163,115,163,117,117,117,117},
                                                    {115,126,-1,-1,-1,122,116,116,163,116,115,116,117,100,116,116,117,163,117,117,115,163,116,116,163,163,163,100,100,100,115,100,116,116,117,100,117,116,100,116,163,116,100,117,100,115,100,100,117,115,163,115,117,115,117,115,163,116,163,116,100,163,163,163,117,117,163,100,116,163,163,116,163,100,116,117,115,115,100,163,115,117,117,100,117,100,163,100,117,117,117,117,163,117,163,100,116,115,100,100,117,116,115,115,100,116,100,117,115,117,117,100,100,100,100,163,163,117,116,117,163,100,163,163,100,163,163,116,116,115,116,100,117,163,116,163,115,100,115,115,100,115,163,116,115,115,163,116,115,115,115,116,163,100,163,100,163,117,117,115,117,100,115,116,100,100,116,117,100,163,115,115,116,116,116,116,100,163,163,100,116,117,163,100,115,163,100,117,163,163,117,116,117,163,116,116,163,163,116,116,100,117,115,116,116,163,117,100,115,115,115,163,163,100,116,163,163,116,100,100,115,117,117,117,115,115,117,163,117,163,115,100,116,117,115,117,100,100,116,115,115,100,115,100,163,115,116,117,163,163,116,100,163,163,115,115,117,100,100,116},
                                                    {117,101,-1,-1,-1,123,116,115,116,117,100,117,116,117,163,163,117,100,117,116,115,163,117,115,116,116,115,163,163,115,100,116,100,100,116,117,117,116,163,163,116,117,117,115,163,100,100,100,116,117,163,100,115,115,116,116,117,116,100,163,116,117,116,116,100,163,100,116,100,115,163,116,116,100,117,115,100,117,100,163,115,163,100,115,115,163,115,115,116,115,115,117,117,116,117,163,163,115,163,163,115,163,163,117,163,117,115,100,116,115,116,100,115,116,116,163,115,115,117,117,117,100,163,115,163,117,115,116,116,117,163,117,100,117,163,163,163,100,117,116,163,115,116,115,115,163,116,163,100,117,115,163,117,163,163,116,117,117,116,115,117,116,163,163,115,117,115,100,115,100,116,116,115,116,116,116,100,100,116,117,116,117,117,163,163,115,163,116,163,115,116,115,116,116,100,100,163,163,116,163,115,115,115,115,116,116,100,117,117,100,115,116,115,163,115,163,100,115,116,163,163,116,163,116,115,163,115,163,116,116,117,115,100,116,100,163,163,117,117,117,117,163,100,100,115,100,116,117,117,116,163,115,163,115,117,116,116,115,100,115},
                                                    {116,126,-1,-1,-1,102,116,100,173,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,119,119,118,119,172,115,100,163,163,117,117,100,117,100,173,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118,118,119,119,120,118,120,119,119,118,120,120,118},
                                                    {116,126,-1,-1,-1,121,116,115,106,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,102,163,116,116,117,116,100,163,116,173,108,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,16,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {116,101,-1,-1,-1,123,100,116,106,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-2,102,117,116,115,117,116,117,163,173,108,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,16,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {163,125,-1,-1,-1,107,118,119,108,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-21,-1,-2,-1,102,163,100,116,173,118,118,119,108,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,103,113,104,-1,-1,-25,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-25,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {163,101,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-10,0,-1,-1,-1,0,0,-1,103,113,112,99,168,163,116,173,108,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,105,115,106,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,98,112,97,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {163,125,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-3,0,0,-5,0,0,-3,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,-1,107,119,118,120,119,118,120,108,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,105,115,106,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,98,96,104,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,98,113,114,168,115,101,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {115,126,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,117,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,117,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,107,119,108,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,105,100,106,-1,-1,-1,127,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,7,8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,98,114,168,100,163,163,116,125,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {117,101,-2,16,-2,103,112,104,-1,-1,-1,-1,-1,-1,-1,103,104,-1,-1,103,112,114,104,-1,-1,103,112,114,104,-1,-1,103,104,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,98,97,-1,-1,-1,161,97,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,0,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,107,118,108,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-24,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,123,100,100,163,117,163,100,101,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {117,126,-2,16,-2,122,116,169,104,-1,-1,-1,-1,-1,103,168,106,-1,-1,121,115,115,101,-1,-1,122,115,100,106,-1,-1,121,169,104,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,98,168,101,-1,-1,-1,121,169,97,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-2,-1,-1,-1,0,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,7,8,-1,-1,-1,-1,12,13,-1,-1,-1,-1,-1,7,8,-1,-1,-1,-1,121,100,115,100,115,115,163,125,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {116,126,-2,16,-2,102,115,100,169,104,-1,-1,-1,103,168,163,101,-1,-1,122,163,117,106,-1,-1,121,116,115,101,-1,-1,122,116,169,112,113,112,113,113,114,112,112,114,114,96,96,112,113,112,168,116,101,-1,-1,-1,122,100,169,99,99,97,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-1,-1,-1,-1,-1,-1,-1,98,162,162,97,-1,-1,-1,-1,-1,0,-2,16,-23,-1,0,-1,-1,-22,-1,0,-1,-1,98,99,97,-1,-1,98,97,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-24,13,-1,-1,-1,-1,12,13,-1,-1,-1,-1,-1,-24,13,-1,-1,-1,-1,102,100,100,116,100,117,163,126,-1,-1,7,8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {163,169,118,120,120,168,100,100,115,169,112,114,114,168,163,100,169,118,120,168,117,117,169,118,120,168,163,163,125,-1,-1,122,115,115,100,116,100,117,116,100,117,115,100,116,163,115,163,116,163,163,163,106,-1,-1,-1,122,117,115,100,163,169,112,113,112,113,113,114,112,113,112,113,113,114,112,112,114,114,96,96,112,113,112,113,113,114,112,112,114,114,96,96,168,115,117,169,112,113,112,113,113,114,112,112,114,114,96,96,112,113,112,113,113,114,168,116,106,-1,-1,121,169,113,113,114,112,112,114,114,96,96,112,113,112,113,113,97,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,98,112,113,112,113,113,114,112,112,114,114,96,96,112,113,112,104,12,13,103,113,112,104,12,13,103,112,114,114,104,12,13,103,112,113,99,168,100,163,116,100,100,100,101,-1,-1,12,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {100,117,100,116,115,117,100,163,163,116,115,100,163,163,115,117,163,163,115,100,117,115,117,115,116,163,115,117,101,-1,-1,122,116,163,163,115,163,100,163,100,117,100,116,117,163,115,115,116,117,100,117,106,-1,-1,-1,122,115,117,115,117,117,116,115,117,117,115,116,117,100,117,116,100,115,117,100,115,100,115,100,100,117,115,163,117,115,117,163,163,117,100,117,100,100,100,163,116,117,100,115,116,100,116,100,116,163,115,115,117,100,116,115,116,116,115,115,101,-1,-1,122,116,116,117,100,163,115,117,100,117,116,163,117,100,100,115,106,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,121,117,115,116,163,117,117,117,100,163,115,115,100,117,116,163,101,12,13,121,163,163,101,12,13,121,115,117,115,101,12,13,121,115,116,116,100,115,117,117,115,100,117,126,-1,-1,12,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {100,116,117,163,116,117,116,117,117,116,163,100,115,115,163,117,100,100,116,117,100,116,100,100,116,116,163,116,125,-1,-1,123,116,163,100,116,116,117,117,100,100,116,115,117,163,173,120,118,120,119,119,171,-1,-1,-1,123,117,116,115,116,163,100,115,163,100,115,100,163,163,116,116,100,117,100,163,163,100,116,163,117,117,117,115,163,116,117,100,116,116,115,163,115,117,100,117,163,100,100,115,117,100,100,116,116,163,115,116,163,163,115,116,117,116,116,163,125,-1,-1,122,117,163,163,117,117,163,117,115,115,117,116,115,163,163,117,101,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,122,163,117,100,115,100,100,117,117,163,100,117,116,117,163,116,125,12,13,122,100,116,125,12,13,122,100,115,116,125,12,13,122,163,115,100,163,117,116,163,116,116,163,126,-1,-1,12,13,-1,-1,-1,7,8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {115,163,117,115,116,117,116,117,163,115,116,117,115,100,115,115,163,115,116,100,100,115,116,100,116,100,117,116,126,-1,-1,102,116,173,118,120,120,118,118,119,119,120,118,172,163,126,-1,-1,-1,-1,-1,-1,-1,-1,-1,102,117,117,115,116,163,163,116,116,117,115,116,117,116,163,115,115,163,115,117,117,100,117,100,163,115,116,115,117,116,116,163,115,100,117,100,116,115,163,115,117,117,100,163,100,115,163,115,117,116,100,117,163,100,116,116,163,163,117,115,101,-1,-1,122,163,163,116,115,100,115,116,100,115,100,116,117,116,100,163,125,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,122,163,100,117,100,115,115,163,100,163,100,163,100,116,100,100,101,12,13,122,163,115,101,12,13,122,116,100,163,101,12,13,122,163,116,100,117,100,115,163,116,117,116,101,-1,-1,12,13,-1,-1,-1,12,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {116,117,115,115,117,115,100,117,116,115,100,163,117,100,115,100,163,117,117,115,116,116,115,100,100,117,115,116,101,-1,-1,121,100,126,-1,-1,-1,-1,-1,-1,-1,-1,-1,121,163,126,-1,-1,-1,-1,-1,-1,-1,-1,-1,121,116,163,115,163,117,115,163,163,117,117,100,163,115,115,116,163,116,100,116,116,116,117,115,100,100,100,115,100,117,163,117,100,163,116,115,163,163,115,163,163,100,115,115,115,116,116,117,117,100,163,100,115,115,163,100,115,100,100,117,125,-1,-1,123,117,163,163,100,115,100,115,100,116,116,117,116,163,100,116,101,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,122,115,163,100,163,100,116,115,100,117,115,100,116,163,117,100,125,12,13,122,116,115,125,12,13,122,115,117,100,125,12,13,122,115,116,117,100,117,116,115,116,163,163,125,-1,-1,12,13,-1,-1,-1,12,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {163,115,116,117,163,100,163,100,163,163,115,163,117,100,116,100,115,116,115,163,115,115,100,115,117,115,163,116,126,-1,-1,123,116,126,-1,-2,16,-2,16,-2,16,-2,-1,123,163,125,-1,-1,-1,-1,-1,-1,-1,-1,-1,123,100,163,117,116,117,116,116,117,100,163,117,163,116,115,117,115,116,163,100,100,163,163,117,115,163,117,115,117,117,115,116,116,116,100,163,117,117,163,116,117,115,117,100,163,100,115,163,116,116,163,117,100,100,100,117,115,117,116,116,126,-1,-1,102,115,100,116,116,100,163,115,163,116,163,115,100,100,115,100,125,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,123,100,115,117,115,117,163,163,163,117,117,116,115,100,117,100,126,12,13,123,115,117,126,12,13,123,116,116,115,126,12,13,123,100,115,117,100,163,163,163,117,100,117,101,-1,-1,12,13,-1,-1,-1,12,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                    {116,116,163,116,116,117,117,115,115,115,100,163,115,116,100,117,163,117,115,115,117,115,163,100,117,163,116,117,126,-1,-1,121,116,125,-1,-2,16,-2,16,-2,16,-2,-1,121,117,125,-1,-1,-1,-1,-1,-1,-1,-1,-1,121,100,117,115,163,163,100,115,115,163,116,163,100,163,117,117,115,100,163,117,117,100,100,100,100,117,100,100,117,116,116,116,115,115,163,116,117,115,163,115,100,117,115,116,163,115,100,163,163,117,115,163,117,117,117,117,100,115,163,163,101,-1,-1,121,163,117,117,115,100,117,117,163,117,163,117,117,163,115,115,126,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,102,117,117,163,100,163,163,115,100,100,115,117,163,163,117,117,101,12,13,102,100,163,101,12,13,102,117,163,117,101,12,13,102,117,115,116,100,115,116,117,117,117,100,125,-1,-1,12,13,-1,-1,-1,12,13,-1,-1,-1,-1,-1,98,99,99,112,113,112,113,113,114,112,112,114,114,96,96,112,113,112,113,113,114,112,112,114,114,96,96,112,113,112,113,113,114,112,112,114,114,96,96,112,113,112,113,113,114,112,112,114,114,96,96},
                                                    {116,117,116,117,115,117,100,116,100,163,116,115,117,116,116,115,117,117,116,116,100,117,117,100,115,116,100,115,101,-1,-1,122,117,125,-1,-2,16,-2,16,-2,16,-2,-1,122,115,126,-1,-1,-1,-1,-1,-1,-1,-1,-1,122,116,163,115,117,115,115,115,163,116,100,115,163,115,163,163,100,163,116,163,117,163,115,116,163,116,115,116,163,100,117,116,115,115,115,115,163,163,100,100,115,163,163,117,116,163,116,116,163,115,100,100,116,115,116,100,117,100,163,116,126,-1,-1,123,116,117,115,163,115,100,115,163,163,163,163,163,116,117,163,101,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,121,163,117,115,116,100,115,100,117,117,116,163,116,117,117,117,126,12,13,121,100,116,126,12,13,121,115,115,117,126,12,13,121,100,163,163,117,163,163,100,163,115,163,126,-1,-1,12,13,-1,-1,-1,12,13,-1,-1,-1,-1,-1,123,163,115,115,163,116,100,117,100,100,117,163,163,100,117,163,117,163,115,117,163,100,100,116,116,163,117,100,100,115,100,116,163,115,115,100,117,163,115,163,116,116,116,116,116,116,117,115,163,115,100},
                                                    {100,100,163,115,116,117,116,163,115,100,117,115,100,116,115,163,115,115,100,116,163,100,100,100,116,100,115,117,125,-1,-1,102,117,126,-1,-2,16,-2,16,-2,16,-2,-1,102,100,125,-1,-1,-1,-1,-1,-1,-1,-1,-1,102,115,117,115,163,163,163,100,163,116,115,100,115,116,163,115,163,116,115,100,115,100,100,100,100,163,115,117,100,100,117,116,100,163,117,115,115,116,115,100,115,163,116,117,116,116,117,115,115,100,115,115,117,115,163,115,117,116,163,115,126,-1,-1,121,117,117,115,116,117,115,100,116,116,115,100,116,115,163,100,126,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,123,117,163,116,163,100,116,115,115,116,115,116,115,117,115,116,126,12,13,123,116,117,126,12,13,123,116,115,100,126,12,13,123,116,100,117,115,100,116,163,116,100,116,101,-1,-1,12,13,-1,-1,-1,12,13,-1,-1,-1,-1,-1,121,115,100,163,100,116,117,100,116,115,117,117,163,117,115,116,117,117,163,163,115,117,100,116,163,163,100,163,117,115,117,163,117,115,116,100,163,100,163,163,100,117,115,115,116,116,100,116,163,163,100},
                                                    {116,163,117,163,117,163,163,117,116,100,116,117,117,100,117,117,116,117,100,163,100,100,117,116,115,115,115,116,101,-1,-1,165,167,171,-1,-1,-1,-1,-1,-1,-1,-1,-1,165,167,171,-1,-1,-1,-1,-1,-1,103,99,99,168,163,100,116,100,163,116,115,115,100,115,116,100,117,163,163,163,116,116,117,100,163,163,100,116,163,117,100,116,116,163,163,100,116,163,115,116,116,115,116,117,117,116,163,117,115,163,117,163,115,100,115,163,116,163,100,100,116,163,115,101,-1,-1,122,163,163,116,117,115,117,116,117,116,100,116,115,163,115,115,126,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,121,163,115,163,117,100,163,100,115,116,163,100,115,163,115,100,101,12,13,121,115,163,101,12,13,121,116,100,115,101,12,13,121,115,115,100,117,117,100,115,100,115,163,126,-1,-1,12,13,-1,-1,-1,12,13,-1,-1,-1,-1,-1,123,117,163,117,100,163,116,115,117,116,163,163,116,115,115,117,100,117,116,163,116,100,100,115,117,116,117,115,116,115,116,116,163,163,100,115,163,116,117,117,117,163,100,117,115,116,115,117,163,100,115},
                                                    {117,117,163,163,117,117,117,100,163,163,117,116,117,163,116,116,100,117,115,116,117,117,115,163,163,116,100,116,125,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,105,163,115,117,117,115,163,115,100,163,115,100,116,100,116,100,115,100,100,100,100,115,100,116,115,116,163,163,116,100,163,163,115,163,100,100,163,116,117,115,115,117,115,116,115,116,100,100,116,117,100,117,115,163,116,163,100,163,115,117,117,117,116,125,-1,-1,102,100,116,116,115,116,115,100,117,117,115,163,100,115,115,117,101,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,122,116,100,117,116,115,117,116,115,117,117,117,163,163,115,163,125,12,13,122,100,115,125,12,13,122,115,115,100,125,12,13,122,100,115,163,116,100,163,100,163,117,163,126,-1,-1,12,13,-1,-1,-1,12,13,-1,-1,-1,-1,-1,121,117,116,115,116,116,115,100,117,115,117,116,163,115,100,163,115,117,116,115,117,163,117,115,115,100,117,117,116,117,116,115,163,163,117,100,163,100,100,100,163,115,115,116,116,163,163,116,116,163,100},
                                                    {163,100,115,115,163,100,115,116,100,115,117,116,116,100,100,116,117,163,100,100,163,117,116,163,115,100,100,100,126,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,102,115,100,115,116,116,117,100,116,115,116,117,100,115,100,163,100,163,100,115,163,163,117,163,116,117,100,117,115,100,163,115,115,100,117,163,115,116,100,115,100,115,116,115,115,116,115,116,100,116,163,115,100,117,115,116,116,100,117,100,116,116,115,101,-1,-1,121,116,100,117,115,115,116,163,117,117,100,116,117,115,163,116,125,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,102,163,115,116,163,163,117,163,100,117,117,117,116,116,115,116,101,12,13,102,117,163,101,12,13,102,100,100,116,101,12,13,102,115,100,100,115,163,115,115,117,117,117,106,-1,-1,12,13,-1,-1,-1,12,13,-1,-1,-1,-1,-1,123,116,117,163,163,117,116,100,115,163,163,115,115,163,116,116,115,116,117,115,100,115,163,163,163,115,100,117,115,163,116,163,117,163,100,100,117,117,115,117,117,116,117,100,117,163,163,116,100,117,115},
                                                    {116,100,116,117,100,163,163,163,163,117,163,163,115,117,163,100,115,163,100,100,100,117,116,116,100,116,115,100,169,112,112,114,114,96,96,112,112,112,114,114,96,96,112,113,112,113,113,114,112,112,114,114,168,163,115,163,117,115,116,117,116,163,116,117,100,115,163,163,163,116,163,116,116,100,100,115,100,117,116,100,115,117,100,117,115,163,116,116,163,116,163,117,115,117,163,100,116,163,163,116,100,117,117,116,116,117,115,117,117,117,116,116,100,115,117,125,-1,-1,122,116,116,117,163,115,115,115,163,163,163,163,117,163,117,116,101,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,121,115,115,163,116,163,117,163,116,115,115,116,100,116,116,117,125,12,13,121,115,116,125,12,13,121,100,117,116,125,12,13,121,163,116,100,100,116,100,116,115,117,115,106,-1,-1,12,13,-1,-1,-1,12,13,-1,-1,-1,-1,-1,123,115,117,163,117,116,117,115,100,117,100,117,117,117,163,115,117,163,100,100,116,163,163,117,100,115,163,115,116,115,115,100,163,116,116,163,100,100,115,163,115,115,100,100,100,116,100,115,115,116,100}};
                dataJeu.level.nombreTileY = 49;
                dataJeu.level.nombreTileX = 260;
                dataJeu.level.listeBonus.nombreBonus = 0;
                dataJeu.level.listeTileAnima.nbTileAnima = 1;
                dataJeu.level.listeEnnemies.nombreEnnemi=0;
                chargeTabInMap(level5, dataJeu, 260, 49);
                dataJeu.level.listeTileMobile.nb_tile = 4;
                dataJeu.level.finY = 6*TILEHAUTEUR;
                dataJeu.level.finX = 244*TILELARGEUR;
                dataJeu.level.debutX = 2 * TILELARGEUR;
                dataJeu.level.debutY = 45*TILEHAUTEUR;
                dataJeu.level.listeTileMobile.tab[0] = initTileMobile(8, 1, make_Vec2(138*TILELARGEUR, 5*TILEHAUTEUR), TILEHAUTEUR/32, 2, 16, make_Vec2(138*TILELARGEUR, 5*TILEHAUTEUR), make_Vec2(138*TILELARGEUR, 10*TILEHAUTEUR));
                dataJeu.level.listeTileMobile.tab[1] = initTileMobile(1, 1, make_Vec2(235*TILELARGEUR, TILEHAUTEUR*7), 0.1, 4, 291, make_Vec2(1, 1), make_Vec2(1, 4));
                dataJeu.level.listeTileMobile.tab[2] = initTileMobile(1, 1, make_Vec2(235*TILELARGEUR, TILEHAUTEUR*8), 0.1*TILEHAUTEUR, 2, 293, make_Vec2(235*TILELARGEUR, TILEHAUTEUR*8), make_Vec2(235*TILELARGEUR, TILEHAUTEUR*12));
                dataJeu.level.listeTileMobile.tab[3] = initTileMobile(1, 1, make_Vec2(235*TILELARGEUR, TILEHAUTEUR*9), 0.1*TILEHAUTEUR, 2, 292, make_Vec2(235*TILELARGEUR, TILEHAUTEUR*9), make_Vec2(235*TILELARGEUR, TILEHAUTEUR*13));

                break;
            }
    }



    //dataJeu.level.listeEnnemies.tab[0] =initEnnemi(100, 384, TILELARGEUR, TILEHAUTEUR/2, TILEHAUTEUR/2, 0, 1, TILELARGEUR/32, TILEHAUTEUR/32, 0, TILEHAUTEUR*(-0.7)/32); //Goomba
    //dataJeu.level.listeEnnemies.tab[0] =initEnnemi(100, 384, TILELARGEUR, TILEHAUTEUR, TILEHAUTEUR, 1, 1, 1, 1, 0, -G); //KOOPA
    //dataJeu.level.listeEnnemies.tab[0] = initEnnemi(100, 384, TILELARGEUR*2.5, TILEHAUTEUR*3, 0, 3, 2, 0, 1, 0, 0);//Carré pointu
    //dataJeu.level.listeEnnemies.tab[4] =initEnnemi(100, 384, 32, 32, 32, 6, 1, 0, 0, 0, -0.7); //Fire bro

/*    dataJeu.level.listeTileMobile.tab[0] = initTileMobile(1, 1, make_Vec2(200, 200), 0.1, 4, 9, make_Vec2(1, 1), make_Vec2(1, 10));
    dataJeu.level.listeTileMobile.tab[1] = initTileMobile(1, 1, make_Vec2(200, 264), 0.1*TILEHAUTEUR, 2, 7, make_Vec2(200, 264), make_Vec2(200, 264+10*TILELARGEUR));
    dataJeu.level.listeTileMobile.tab[2] = initTileMobile(1, 1, make_Vec2(200, 232), 0.1*TILEHAUTEUR, 2, 8, make_Vec2(200, 232), make_Vec2(200, 232+10*TILELARGEUR));
*/
}

void drawMessage(const char chaine[100], struct DataImages &dataImage, double x, double y, double taille)//affiche les messages
{
    int j = 0;
    int largeur = 0;
    int hauteur = 0;
    //std::cout<<y<<std::endl;
    while(chaine[j]!='\0')
    {
        if(chaine[j]>='A'&&chaine[j]<='Z')
        {
            image_draw(dataImage.font[2][chaine[j]-'A'], x+largeur, y, image_width(dataImage.font[2][chaine[j]-'A'])*taille,  image_height(dataImage.font[2][chaine[j]-'A'])*taille);
            largeur+=image_width(dataImage.font[2][chaine[j]-'A'])*taille;
        }
        else if(chaine[j]>='a'&&chaine[j]<='z')
        {
            image_draw(dataImage.font[3][chaine[j]-'a'], x+largeur, y, image_width(dataImage.font[3][chaine[j]-'a'])*taille,  image_height(dataImage.font[3][chaine[j]-'a'])*taille);
            largeur+=image_width(dataImage.font[3][chaine[j]-'a'])*taille;
        }
        else if(chaine[j]>='0'&&chaine[j]<='9')
        {
            image_draw(dataImage.font[4][chaine[j]-'0'], x+largeur, y, image_width(dataImage.font[4][chaine[j]-'0'])*taille,  image_height(dataImage.font[4][chaine[j]-'0'])*taille);
            largeur+=image_width(dataImage.font[4][chaine[j]-'0'])*taille;
        }
        else
        {
            largeur+= taille*25;
        }
        j++;
    }
}
void drawText(struct Jeu &dataJeu, struct DataImages &dataImage)//affiche les textes
{
    for(int i = 0;i <dataJeu.level.listeTexte.nb_text; i++)
    {
        //std::cout<<dataJeu.level.listeTexte.tab[i].pos.x<<std::endl;
        drawMessage(dataJeu.level.listeTexte.tab[i].chaine, dataImage, dataJeu.level.listeTexte.tab[i].pos.x-dataJeu.level.scrollX, dataJeu.level.listeTexte.tab[i].pos.y-dataJeu.level.scrollY, dataJeu.level.listeTexte.tab[i].taille);
    }
}


void drawParticules(struct ParticulesList &l, struct Jeu &dataJeu)//Affiche les particules 
{
    for(int i = 0; i<l.nb_part; i++)
    {
        color(l.tab[i].couleur.r, l.tab[i].couleur.g, l.tab[i].couleur.b);
        if(l.tab[i].type == 0)//Cercle non rempli
        {
            circle(l.tab[i].pos.x-dataJeu.level.scrollX, l.tab[i].pos.y-dataJeu.level.scrollY, l.tab[i].largeur/2);
        }
        else if(l.tab[i].type == 1)//Cercle rempli
        {
            circleFill(l.tab[i].pos.x-dataJeu.level.scrollX, l.tab[i].pos.y-dataJeu.level.scrollY, l.tab[i].largeur/2);
        }
        else if(l.tab[i].type == 2)//Rectangle non rempli
        {
            rectangle(l.tab[i].pos.x-l.tab[i].largeur/2-dataJeu.level.scrollX, l.tab[i].pos.y-l.tab[i].hauteur/2-dataJeu.level.scrollY, l.tab[i].pos.x+l.tab[i].largeur/2-dataJeu.level.scrollX, l.tab[i].pos.y+l.tab[i].hauteur/2-dataJeu.level.scrollY);
        }
        else if(l.tab[i].type == 3)//Rectangle rempli
        {
            rectangleFill(l.tab[i].pos.x-l.tab[i].largeur/2-dataJeu.level.scrollX, l.tab[i].pos.y-l.tab[i].hauteur/2-dataJeu.level.scrollY, l.tab[i].pos.x+l.tab[i].largeur/2-dataJeu.level.scrollX, l.tab[i].pos.y+l.tab[i].hauteur/2-dataJeu.level.scrollY);
        }
    }
}

void drawNumber(struct DataImages &dataImage, int px, int py, int largeur, int hauteur, int espace, int nombre, int maxNombre)//Affiche les nombres
{
    int tailleChiffre = largeur+espace;
    int posXFinal = px+maxNombre*tailleChiffre;
    for(int i = 1; i<=maxNombre; i++)
    {
        image_draw(dataImage.font[1][nombre%10], posXFinal - i*tailleChiffre, py, largeur, hauteur);
        nombre/=10;
    }
}



void drawAffichageInGame(struct DataImages &dataImage, struct Jeu &dataJeu)//Affiche le score, pièces vie temp
{
    drawNumber(dataImage, DIMWX - TILELARGEUR*7, DIMWY-TILEHAUTEUR, TILELARGEUR/2, TILEHAUTEUR/2, -5, dataJeu.score, 8);//Affichage du score

    image_draw(dataImage.font[0][0], DIMWX-TILELARGEUR*2.5, DIMWY-TILEHAUTEUR, TILELARGEUR/2, TILEHAUTEUR/2);//Affichage de l'horloge
    drawNumber(dataImage,DIMWX-TILELARGEUR*1.75, DIMWY-TILEHAUTEUR, TILELARGEUR/2, TILELARGEUR/2, 0, dataJeu.level.secondeRestante, 3);//Affichage du timer

    image_draw(dataImage.bonus[0][0], 1, DIMWY-TILEHAUTEUR*2, TILELARGEUR/2, TILEHAUTEUR/2);//Affichage de la pièce
    image_draw(dataImage.font[0][1], TILELARGEUR/2, DIMWY-TILEHAUTEUR*2, TILELARGEUR/2, TILEHAUTEUR/2);//Affichage du fois
    drawNumber(dataImage, TILELARGEUR, DIMWY-TILEHAUTEUR*2, TILELARGEUR/2, TILEHAUTEUR/2, 0, dataJeu.nb_pieces, 2);//Affichage du nombre de pièce

    image_draw(dataImage.font[0][2], 1, DIMWY-TILEHAUTEUR, TILELARGEUR, TILEHAUTEUR);
    image_draw(dataImage.font[0][1], TILELARGEUR, DIMWY-TILEHAUTEUR*0.75, TILELARGEUR/2, TILEHAUTEUR/2);//Affichage du fois
    drawNumber(dataImage, TILELARGEUR*1.5, DIMWY-TILEHAUTEUR*0.75, TILELARGEUR/2, TILEHAUTEUR/2, 0, dataJeu.nb_vie, 2);//Affichage du nombre de vie
}

void drawTileAnim(struct tileAnimaList &l, struct DataImages &dataImage, struct Jeu &dataJeu)//Affiche les tiles animés
{
    for(int i = 0; i<l.nbTileAnima; i++)
    {
        if(l.tab[i].type<20)
        {
            if(l.tab[i].tileX <= (dataJeu.level.scrollX+ DIMWX)/TILELARGEUR && l.tab[i].tileY <= (dataJeu.level.scrollY+ DIMWY)/TILEHAUTEUR && l.tab[i].tileX + 1 > (dataJeu.level.scrollX)/TILELARGEUR && l.tab[i].tileY + 1 > (dataJeu.level.scrollY)/TILEHAUTEUR)
            {
                image_draw(dataImage.solAnim[0][l.tab[i].anim.frame], l.tab[i].tileX*TILELARGEUR-dataJeu.level.scrollX, l.tab[i].tileY*TILEHAUTEUR-dataJeu.level.scrollY    , TILELARGEUR, TILEHAUTEUR);
            }
        }
        else if(l.tab[i].type<22)
        {
            if(l.tab[i].tileX < (dataJeu.level.scrollX+ DIMWX)/TILELARGEUR && l.tab[i].tileY < (dataJeu.level.scrollY+ DIMWY)/TILEHAUTEUR && l.tab[i].tileX + 2 > (dataJeu.level.scrollX)/TILELARGEUR && l.tab[i].tileY + 3 > (dataJeu.level.scrollY)/TILEHAUTEUR)
            {
                image_draw(dataImage.solAnim[l.tab[i].type-19][l.tab[i].anim.frame], l.tab[i].tileX*TILELARGEUR-dataJeu.level.scrollX, l.tab[i].tileY*TILEHAUTEUR-dataJeu.level.scrollY    , TILELARGEUR*2, TILEHAUTEUR*3);
            }
        }
    }
}

void drawTileMobileList(struct tileMobileList l, struct DataImages &dataImage, struct Jeu &dataJeu)//Affiche les tiles mobiles
{
    for(int i = 0; i<l.nb_tile; i++)
    {

        if(l.tab[i].position.x<dataJeu.level.scrollX+DIMWX && l.tab[i].position.x + l.tab[i].largeur*TILELARGEUR > dataJeu.level.scrollX)
        {
            int debutX = TILELARGEUR*(l.tab[i].largeur - (int)l.tab[i].largeur);
            int debutY = TILEHAUTEUR*(l.tab[i].hauteur - (int)l.tab[i].hauteur);
            for(int j = -1; j<=l.tab[i].largeur-1; j++)
            {
                for(int k = -1; k<l.tab[i].hauteur-1; k++)
                {
                    if(l.tab[i].draw>=0)
                    {
                        image_draw(dataImage.sol[l.tab[i].draw], l.tab[i].position.x + (j==-1? 0 : debutX + j*TILELARGEUR) - dataJeu.level.scrollX, l.tab[i].position.y + (k==-1? 0 : debutY + k*TILEHAUTEUR) - dataJeu.level.scrollY, TILELARGEUR, TILEHAUTEUR);
                    }
                }
            }
        }
    }
}

void afficheBonus(struct Jeu &dataJeu, struct DataImages &dataImage)//Affiche les bonus
{
    for(int i =0; i<dataJeu.level.listeBonus.nombreBonus; i++)
    {
        image_draw(dataImage.bonus[dataJeu.level.listeBonus.tab[i].type][dataJeu.level.listeBonus.tab[i].anim.frame],dataJeu.level.listeBonus.tab[i].position.x-dataJeu.level.scrollX, dataJeu.level.listeBonus.tab[i].position.y - dataJeu.level.scrollY, dataJeu.level.listeBonus.tab[i].largeur, dataJeu.level.listeBonus.tab[i].hauteur, 0, (dataJeu.level.listeBonus.tab[i].vitesse.x>0? 1:0));
    }
}

void affichePerso(struct personnage p, struct Jeu &dataJeu, struct DataImages &dataImage)//Affiche le personnage
{
    color(0, 255, 0);
    image_draw(dataImage.perso[p.statAnim][p.anim.frame], p.position.x-dataJeu.level.scrollX, p.position.y - dataJeu.level.scrollY, p.largeur, p.hauteur, 0, (p.vitesse.x<0? 1:0));
}

void afficheEnnemy(struct Jeu &dataJeu, struct DataImages &dataImage)//Affiche les ennemis
{
    for(int i =0; i<dataJeu.level.listeEnnemies.nombreEnnemi; i++)
    {
        if(dataJeu.level.listeEnnemies.tab[i].position.x+dataJeu.level.listeEnnemies.tab[i].largeur>dataJeu.level.scrollX&&dataJeu.level.listeEnnemies.tab[i].position.x<dataJeu.level.scrollX+DIMWX)
        {
           if(dataJeu.level.listeEnnemies.tab[i].type!=3)
            {
                image_draw(dataImage.ennemy[dataJeu.level.listeEnnemies.tab[i].type][dataJeu.level.listeEnnemies.tab[i].anim.frame],dataJeu.level.listeEnnemies.tab[i].position.x-dataJeu.level.scrollX, dataJeu.level.listeEnnemies.tab[i].position.y - dataJeu.level.scrollY, dataJeu.level.listeEnnemies.tab[i].largeur, dataJeu.level.listeEnnemies.tab[i].hauteurLoose+dataJeu.level.listeEnnemies.tab[i].hauteurWin, 0, (dataJeu.level.listeEnnemies.tab[i].vitesse.x>0? 1:0));
                if(dataJeu.level.listeEnnemies.tab[i].type==5)
                {
                    for(int j = dataJeu.level.listeEnnemies.tab[i].position.x/TILELARGEUR; j<(dataJeu.level.listeEnnemies.tab[i].position.x+dataJeu.level.listeEnnemies.tab[i].largeur)/TILELARGEUR; j++)
                    {
                        for(int k = dataJeu.level.listeEnnemies.tab[i].position.y/TILEHAUTEUR; k<(dataJeu.level.listeEnnemies.tab[i].position.y+dataJeu.level.listeEnnemies.tab[i].hauteurLoose)/TILELARGEUR; k++)
                        {
                            if(dataJeu.level.level[k][j]>=0)
                            {
                                image_draw(dataImage.sol[dataJeu.level.level[k][j]], j*TILELARGEUR-dataJeu.level.scrollX,k*TILEHAUTEUR-dataJeu.level.scrollY, TILELARGEUR, TILEHAUTEUR);
                            }
                        }
                    }
                }
            }
            else
            {
                image_draw(dataImage.ennemy[3][(dataJeu.level.listeEnnemies.tab[i].vitesse.y>0 ? 1: 0)],dataJeu.level.listeEnnemies.tab[i].position.x-dataJeu.level.scrollX, dataJeu.level.listeEnnemies.tab[i].position.y - dataJeu.level.scrollY, dataJeu.level.listeEnnemies.tab[i].largeur, dataJeu.level.listeEnnemies.tab[i].hauteurLoose+dataJeu.level.listeEnnemies.tab[i].hauteurWin, 0, (dataJeu.level.listeEnnemies.tab[i].vitesse.x>0? 1:0));
            }
        }
    }
}


void drawJeu(struct DataImages &dataImage, struct Jeu &dataJeu)//Appelle les fonctions d'affichage du jeu
{

    for(int i = 0; i<2; i++)
    {
        image_draw(dataImage.background[dataJeu.level.numeroLevel/5], (double(-dataJeu.level.scrollX)/(dataJeu.level.nombreTileX*TILELARGEUR)+i)*DIMWX*1.5,1,DIMWX*1.5, DIMWY);
    }
    for(int i = dataJeu.level.scrollY/TILEHAUTEUR; i<=(dataJeu.level.scrollY+DIMWY)/TILEHAUTEUR; i++)
    {
        for(int j = dataJeu.level.scrollX/TILELARGEUR; j<=(dataJeu.level.scrollX+DIMWX)/TILELARGEUR; j++)
        {
            if(i<dataJeu.level.nombreTileY&&j<dataJeu.level.nombreTileX&&i>=0&&j>=0)
            {
                if(dataJeu.level.level[i][j]>=0&&dataJeu.level.level[i][j]!=1)
                {
                    int x = j*TILELARGEUR-dataJeu.level.scrollX;
                    int y = i*TILEHAUTEUR-dataJeu.level.scrollY;
                    //std::cout<<(int)dataJeu.level.level[dataJeu.level.nombreTileY-i-1][j]<<std::endl;
                    image_draw(dataImage.sol[dataJeu.level.level[i][j]], x, y, TILELARGEUR, TILEHAUTEUR);
                }
            }
        }
    }
    if(dataJeu.level.scrollX+DIMWX>dataJeu.level.finX&&dataJeu.level.scrollX<dataJeu.level.finX+2*TILELARGEUR)
    {
        image_draw(dataImage.imagesSup[0], dataJeu.level.finX-dataJeu.level.scrollX, dataJeu.level.finY-dataJeu.level.scrollY, TILELARGEUR*2, TILEHAUTEUR*8);
        image_draw(dataImage.imagesSup[2], dataJeu.level.finX-dataJeu.level.scrollX+TILELARGEUR*4, dataJeu.level.finY-dataJeu.level.scrollY, TILELARGEUR*5, TILEHAUTEUR*5);
    }
    drawText(dataJeu, dataImage);
    drawParticules(dataJeu.level.listeParticules, dataJeu);
    afficheEnnemy(dataJeu, dataImage);
    drawTileMobileList(dataJeu.level.listeTileMobile, dataImage, dataJeu);
    drawTileAnim(dataJeu.level.listeTileAnima, dataImage, dataJeu);
    afficheBonus(dataJeu, dataImage);
    affichePerso(dataJeu.level.persoPrincipal, dataJeu, dataImage);
    drawAffichageInGame(dataImage, dataJeu);
}




bool collisionRectangle(float x1, float y1, int larg1, int haut1, float x2, float y2, int larg2, int haut2)//Fonction de collision AABB
{
    if(larg1==0||haut1==0||larg2==0||haut2==0)//aucune collision possible
    {
        return false;
    }
    if(x1+larg1<x2||//Trop à gauche
            x1>x2+larg2||//trop à droite
            y1+haut1<y2||//trop en bas
            y1>y2+haut2)//trop en haut
        return false;//Aucune collision
    return true;//Collision
}




int testCollisionEnnemy(struct Ennemi e, Vec2 position, int largeur, int hauteur)
{

    if(collisionRectangle(position.x, position.y, largeur, hauteur, e.position.x, e.position.y, e.largeur, e.hauteurLoose))
    {
        return 2;//Mort du personnage
    }
    else if(collisionRectangle(position.x, position.y, largeur, hauteur, e.position.x, e.position.y+e.hauteurLoose, e.largeur, e.hauteurWin))
    {
        return 1;//Destruction de l'ennemi
    }
    return 3; //aucune collision
}



void tileMobileCollision(Vec2 &pos, Vec2 &vitesse, Vec2 &posInit, Vec2 &vitesseInit, int &largeur, int &hauteur, char &sol, struct Jeu &dataJeu, char type)
{
    char numeroTileCollision = -1;
    bool collision = false;
    Vec2 arriver = posInit + vitesseInit;
    for(int i = 0; i < dataJeu.level.listeTileMobile.nb_tile; i++)
    {
        if(type==1)dataJeu.level.listeTileMobile.tab[i].playerDessus = false;
        if(collisionRectangle(arriver.x, arriver.y, largeur, hauteur, dataJeu.level.listeTileMobile.tab[i].position.x, dataJeu.level.listeTileMobile.tab[i].position.y, dataJeu.level.listeTileMobile.tab[i].largeur * TILELARGEUR, dataJeu.level.listeTileMobile.tab[i].hauteur*TILEHAUTEUR))
        {
            numeroTileCollision = i;
            break;
        }
    }
    if(numeroTileCollision>-1)
    {
        if(vitesse.y<0&&(returnDrawTile(dataJeu.level.listeTileMobile.tab[numeroTileCollision].draw)==0||returnDrawTile(dataJeu.level.listeTileMobile.tab[numeroTileCollision].draw)==1)&&collisionRectangle(posInit.x, arriver.y, largeur, hauteur, dataJeu.level.listeTileMobile.tab[numeroTileCollision].position.x, dataJeu.level.listeTileMobile.tab[numeroTileCollision].position.y, dataJeu.level.listeTileMobile.tab[numeroTileCollision].largeur * TILELARGEUR, dataJeu.level.listeTileMobile.tab[numeroTileCollision].hauteur*TILEHAUTEUR))
        {
            pos.y = dataJeu.level.listeTileMobile.tab[numeroTileCollision].position.y + dataJeu.level.listeTileMobile.tab[numeroTileCollision].hauteur*TILEHAUTEUR - 1;
            vitesse.y = 0;
            if(type==1)dataJeu.level.listeTileMobile.tab[numeroTileCollision].playerDessus = true;
            sol = 1;
        }
        else if(vitesse.y>0&&returnDrawTile(dataJeu.level.listeTileMobile.tab[numeroTileCollision].draw)==0&&collisionRectangle(posInit.x, arriver.y, largeur, hauteur, dataJeu.level.listeTileMobile.tab[numeroTileCollision].position.x, dataJeu.level.listeTileMobile.tab[numeroTileCollision].position.y, dataJeu.level.listeTileMobile.tab[numeroTileCollision].largeur * TILELARGEUR, dataJeu.level.listeTileMobile.tab[numeroTileCollision].hauteur*TILEHAUTEUR))
        {
            pos.y = dataJeu.level.listeTileMobile.tab[numeroTileCollision].position.y - hauteur ;

            vitesse.y = 0;
        }
        else if(vitesse.x>0&&returnDrawTile(dataJeu.level.listeTileMobile.tab[numeroTileCollision].draw)==0&&collisionRectangle(arriver.x , posInit.y, largeur, hauteur, dataJeu.level.listeTileMobile.tab[numeroTileCollision].position.x, dataJeu.level.listeTileMobile.tab[numeroTileCollision].position.y, dataJeu.level.listeTileMobile.tab[numeroTileCollision].largeur * TILELARGEUR, dataJeu.level.listeTileMobile.tab[numeroTileCollision].hauteur*TILEHAUTEUR))
        {
            pos.x = dataJeu.level.listeTileMobile.tab[numeroTileCollision].position.x - largeur - 1;
            vitesse.x = 0;
        }
        else if(vitesse.x<0&&returnDrawTile(dataJeu.level.listeTileMobile.tab[numeroTileCollision].draw)==0&&collisionRectangle(arriver.x, posInit.y, largeur, hauteur, dataJeu.level.listeTileMobile.tab[numeroTileCollision].position.x, dataJeu.level.listeTileMobile.tab[numeroTileCollision].position.y, dataJeu.level.listeTileMobile.tab[numeroTileCollision].largeur * TILELARGEUR, dataJeu.level.listeTileMobile.tab[numeroTileCollision].hauteur*TILEHAUTEUR))
        {
            pos.x = dataJeu.level.listeTileMobile.tab[numeroTileCollision].position.x + dataJeu.level.listeTileMobile.tab[numeroTileCollision].largeur*TILELARGEUR + 1;
            vitesse.x = 0;
        }


    }

}

bool pointCollision(Vec2 pos, struct Jeu &dataJeu)
{
    int tileX = pos.x/TILELARGEUR, tileY = pos.y/TILEHAUTEUR;
    if(tileX<0||tileY<0||tileX>dataJeu.level.nombreTileX||tileY>dataJeu.level.nombreTileY)
    {
        return false;
    }
    if(returnDrawTile(dataJeu.level.level[tileY][tileX])>=0)
    {
        return true;
    }
    for(int i = 0; i < dataJeu.level.listeTileMobile.nb_tile; i++)
    {
        if(collisionRectangle(pos.x, pos.y, 1, 1, dataJeu.level.listeTileMobile.tab[i].position.x, dataJeu.level.listeTileMobile.tab[i].position.y, dataJeu.level.listeTileMobile.tab[i].largeur * TILELARGEUR, dataJeu.level.listeTileMobile.tab[i].hauteur*TILEHAUTEUR))
        {
            return true;
        }
    }
    return false;
}

int mapCollision(Vec2 &pos, char &statAnim, Vec2 &vitesse, int &largeur, int &hauteur, char &sol, struct Jeu &dataJeu, struct Animation &anim, char type)
{
    int testX, testY, x1, x2, y1, y2;
    Vec2 posInit = pos;
    Vec2 vitesseInit = vitesse;
    char solAvant = sol;
    sol = 0;
    if (hauteur > TILEHAUTEUR)
    {
        testY = TILEHAUTEUR;
    }
    else
    {
        testY = hauteur;
    }
    //std::cout<<DT*vitesse.x<<std::endl;

    bool boucle = true;
    while(boucle==true)
    {
        x1 = (pos.x + DT*vitesse.x) / TILELARGEUR;
        x2 = (pos.x + DT*vitesse.x + largeur) / TILELARGEUR;

        y1 = (pos.y) / TILEHAUTEUR;
        y2 = (pos.y + testY-1) / TILEHAUTEUR;

        if (x1 >= 0 && x2 < dataJeu.level.nombreTileX && y1 >= 0 && y2 < dataJeu.level.nombreTileY)
        {
            if (vitesse.x > 0)//déplacement à droite
            {
                if (returnDrawTile(dataJeu.level.level[y1][x2])==0 || returnDrawTile(dataJeu.level.level[y2][x2])==0)
                {
                    pos.x = x2 * TILELARGEUR - largeur;//Plaquage à droite
                    if(type!=0)//Ennemi
                    {
                        if(type==5)
                        {
                            return 1;//Death de l'ennemi
                        }
                        vitesse.x*= -1;
                    }
                    else
                    {
                        vitesse.x = 0;
                    }


                }
            }

            //Même chose à gauche
            else if (vitesse.x < 0)
            {
                if (returnDrawTile(dataJeu.level.level[y1][x1])==0|| returnDrawTile(dataJeu.level.level[y2][x1])==0)
                {
                    pos.x = (x1 + 1) * TILELARGEUR;//Plaquage à gauche

                    if(type!=0)//Ennemi
                    {
                        if(type==5)
                        {
                            return 1;//Death de l'ennemi
                        }
                        vitesse.x*= -1;
                    }
                    else
                    {
                        vitesse.x = 0;
                    }
                }
            }
        }
        if (testY == hauteur)
        {
            boucle = false;//si tout les tiles touchant le sprite ont été testé on sort
        }

        testY += TILEHAUTEUR;

        if (testY > hauteur)
        {
            testY = hauteur;
        }
    }


    //On recommence la même chose avec le mouvement vertical (axe des Y)
    if (largeur > TILELARGEUR)
    {
        testX = TILELARGEUR;
    }
    else
    {
        testX = largeur;
    }

    boucle = true;
    while(boucle==true)
    {
        x1 = (pos.x) / TILELARGEUR;
        x2 = (pos.x + testX - 1) / TILELARGEUR;

        y1 = (pos.y + DT*vitesse.y) / TILEHAUTEUR;
        y2 = (pos.y + DT*vitesse.y + hauteur) / TILEHAUTEUR;
        if (x1 >= 0 && x2 < dataJeu.level.nombreTileX && y1 >= 0 && y2 < dataJeu.level.nombreTileY)
        {
            if (vitesse.y < 0)//Déplacement vers le bas
            {
                if (returnDrawTile(dataJeu.level.level[y1][x1])>=0||returnDrawTile(dataJeu.level.level[y1][x2])>=0)
                {

                    pos.y = (y1+1) * TILEHAUTEUR;
                    vitesse.y = 0;
                    sol = 1;


                }
            }
            else if (vitesse.y > 0)
            {
                // Déplacement vers le haut
                if (returnDrawTile(dataJeu.level.level[y2][x1])==0 || returnDrawTile(dataJeu.level.level[y2][x2])==0)
                {
                    pos.y = (y2) * TILEHAUTEUR;
                    pos.y -= hauteur;
                    vitesse.y = 0;
                    if(dataJeu.level.level[y2][x1]==1&&type==0)
                    {
                        removeTileAnima(dataJeu, x1, y2);
                    }
                    else if(dataJeu.level.level[y2][x2]==1&&type==0)
                    {
                        removeTileAnima(dataJeu, x2, y2);
                    }
                    else if(dataJeu.level.level[y2][x1]==0&&type==0)
                    {
                        for(int l = 0; l<dataJeu.level.listeEnnemies.nombreEnnemi; l++)
                        {
                            int tileDessousX = (dataJeu.level.listeEnnemies.tab[l].position.x+dataJeu.level.listeEnnemies.tab[l].largeur/2)/TILELARGEUR;
                            int tileDessousY = (dataJeu.level.listeEnnemies.tab[l].position.y-1)/TILEHAUTEUR;
                            if(tileDessousX == x1&&tileDessousY==y2)
                            {
                                dataJeu.level.listeEnnemies.tab[l].inLive = false;
                            }
                        }
                        for(int k = 0; k<4; k++)
                        {

                            dataJeu.level.listeParticules.tab[dataJeu.level.listeParticules.nb_part+k] = initParticules(x1*TILELARGEUR, y2*TILEHAUTEUR, 0, -G, irand(-TILELARGEUR/8, TILELARGEUR/8), TILEHAUTEUR/2, 3, {115, 77, 38}, TILELARGEUR/4, TILEHAUTEUR/4);

                        }
                        dataJeu.level.listeParticules.nb_part+=4;
                        dataJeu.level.level[y2][x1]= -1;
                    }
                     else if(dataJeu.level.level[y2][x2]==0&&type==0)
                    {
                        for(int l = 0; l<dataJeu.level.listeEnnemies.nombreEnnemi; l++)
                        {
                            int tileDessousX = (dataJeu.level.listeEnnemies.tab[l].position.x+dataJeu.level.listeEnnemies.tab[l].largeur/2)/TILELARGEUR;
                            int tileDessousY = (dataJeu.level.listeEnnemies.tab[l].position.y-1)/TILEHAUTEUR;
                            if(tileDessousX == x2&&tileDessousY==y2)
                            {
                                dataJeu.level.listeEnnemies.tab[l].inLive = false;
                            }
                        }
                        for(int k = 0; k<4; k++)
                        {

                            dataJeu.level.listeParticules.tab[dataJeu.level.listeParticules.nb_part+k] = initParticules(x2*TILELARGEUR, y2*TILEHAUTEUR, 0, -G, irand(-TILELARGEUR/8, TILELARGEUR/8), TILEHAUTEUR/2, 3, {115, 77, 38}, TILELARGEUR/4, TILEHAUTEUR/4);

                        }
                        dataJeu.level.listeParticules.nb_part+=4;
                        dataJeu.level.level[y2][x2]= -1;
                    }
                }

            }
        }

        if (testX == largeur)//Si on a tous testé
        {
            boucle = false;
        }

        testX += TILELARGEUR;

        if (testX > largeur)
        {
            testX = largeur;
        }
    }
    tileMobileCollision(pos, vitesse, posInit, vitesseInit, largeur, hauteur, sol, dataJeu, type);//Collision avec les tiles mobiles
    if(type==1||type==2)
    {
        if(vitesse.x>0&&!pointCollision(make_Vec2(pos.x+DT*vitesse.x+largeur/2, pos.y-2), dataJeu))
        {
            vitesse.x*=-1;
        }
        else if(vitesse.x<0&&!pointCollision(make_Vec2(pos.x+DT*vitesse.x+largeur/2, pos.y-2), dataJeu))
        {
            vitesse.x*=-1;
        }
    }
    pos =pos + DT*vitesse;//Update de la position

    //Et on contraint son déplacement aux limites de l'écran.
    if(pos.x<1)
    {
        vitesse.x = 0;
        pos.x = 1;//réajuste les coordonnées
    }

    else if (pos.x + largeur >= dataJeu.level.nombreTileX*TILELARGEUR)
    {
        pos.x = dataJeu.level.nombreTileX*TILELARGEUR - largeur;
    }
    if(type==0)//Joueur
    {
        if(sol==1)
        {
            if(vitesse.x==0)
            {
                if(statAnim!=0)
                {
                    statAnim = 0;//Immboile
                    anim.frame = 0;
                    anim.frameMax = MAXFRAMEIMMOBILE;
                    anim.temp = elapsedTime();
                }
            }
            else if(abs(vitesse.x)<5)
            {
                if(statAnim!=1)
                {
                    statAnim = 1;//Immboile
                    anim.frame = 0;
                    anim.frameMax = MAXFRAMEMARCHE;
                    anim.temp = elapsedTime();
                }
            }
            else if(statAnim!=2)
            {
                statAnim = 2;//Immobile
                anim.frame = 0;
                anim.frameMax = MAXFRAMECOURSE;
                anim.temp = elapsedTime();

            }

        }
        else
        {
            if(vitesse.y>=0)
            {
                if(statAnim!=3)
                {
                    statAnim = 3;//Immboile
                    anim.frame = 0;
                    anim.frameMax = MAXFRAMEMONTE;
                    anim.temp = elapsedTime();
                }
                else if(anim.frame+1==MAXFRAMEMONTE)
                {
                    anim.frame = MAXFRAMEMONTE-2;
                }
            }
            else
            {
                if(statAnim!=4)
                {
                    statAnim = 4;//Immboile
                    anim.frame = 0;
                    anim.frameMax = MAXFRAMEDESCENTE;
                    anim.temp = elapsedTime();
                }
                else if(anim.frame+1==MAXFRAMEDESCENTE)
                {
                    anim.frame = MAXFRAMEDESCENTE-2;
                }
            }

        }
    }
    return 0;//Tout s'est bien passé
}


void actionTileMobile(struct tileMobile &t, struct Jeu &dataJeu)
{
    switch(t.draw)
    {
        case 292:
            if(t.timerAction + TEMPMISSILESPAWN < elapsedTime())
            {
                dataJeu.level.listeEnnemies.tab[dataJeu.level.listeEnnemies.nombreEnnemi] = initEnnemi(t.position.x-TILELARGEUR, t.position.y, TILELARGEUR, TILEHAUTEUR*0.3, TILEHAUTEUR*0.3, 4, 1, signe(dataJeu.level.persoPrincipal.position.x-t.position.x)*TILELARGEUR/8, 0, 0, 0);
                dataJeu.level.listeEnnemies.nombreEnnemi++;
                t.timerAction = elapsedTime();
            }
            break;
    }
}



void updateTileMobileList(struct tileMobileList &l, struct Jeu &dataJeu)
{
    for(int i = 0; i<l.nb_tile; i++)
    {
        if(l.tab[i].position.x+l.tab[i].largeur*TILELARGEUR>dataJeu.level.scrollX&&l.tab[i].position.x<dataJeu.level.scrollX+DIMWX)
        {
            actionTileMobile(l.tab[i], dataJeu);
            if(l.tab[i].type==1)//Mouvement horizontal
            {
                l.tab[i].position.x += l.tab[i].vitesse*DT;
                if(l.tab[i].playerDessus)
                {
                    dataJeu.level.persoPrincipal.position.x += l.tab[i].vitesse*DT;
                }
                if(l.tab[i].position.x < l.tab[i].debut.x)
                {
                    l.tab[i].position.x = l.tab[i].debut.x;
                    l.tab[i].vitesse*=-1;
                }
                if(l.tab[i].position.x + l.tab[i].largeur*TILELARGEUR > l.tab[i].fin.x)
                {
                    l.tab[i].position.x = l.tab[i].fin.x - l.tab[i].largeur*TILELARGEUR;
                    l.tab[i].vitesse*=-1;
                }
            }
            else if(l.tab[i].type==2)//Mouvement vertical
            {
                l.tab[i].position.y += l.tab[i].vitesse*DT;
                if(l.tab[i].playerDessus)
                {
                    dataJeu.level.persoPrincipal.position.y += l.tab[i].vitesse*DT;
                }
                if(l.tab[i].position.y < l.tab[i].debut.y)
                {
                    l.tab[i].position.y = l.tab[i].debut.y;
                    l.tab[i].vitesse*=-1;
                }
                if(l.tab[i].position.y + l.tab[i].hauteur*TILELARGEUR > l.tab[i].fin.y)
                {
                    l.tab[i].position.y = l.tab[i].fin.y - l.tab[i].hauteur*TILELARGEUR;
                    l.tab[i].vitesse*=-1;
                }
            }
            else if(l.tab[i].type==3)//Agrandissement horizontal
            {
                l.tab[i].largeur += l.tab[i].vitesse * DT;
                if(l.tab[i].playerDessus)
                {
                    dataJeu.level.persoPrincipal.position.x += l.tab[i].vitesse*DT*TILELARGEUR;
                }
                if(l.tab[i].largeur<l.tab[i].debut.x)
                {
                    l.tab[i].largeur = l.tab[i].debut.x;
                    l.tab[i].vitesse*=-1;
                }
                if(l.tab[i].largeur > l.tab[i].fin.x)
                {
                    l.tab[i].largeur = l.tab[i].fin.x;
                    l.tab[i].vitesse *= -1;
                }
            }

            else if(l.tab[i].type==4)//Agrandissement vertical
            {
                l.tab[i].hauteur += l.tab[i].vitesse * DT;

                if(l.tab[i].hauteur<l.tab[i].debut.y)
                {
                    l.tab[i].hauteur = l.tab[i].debut.y;
                    l.tab[i].vitesse*=-1;
                }
                if(l.tab[i].hauteur > l.tab[i].fin.y)
                {
                    l.tab[i].hauteur = l.tab[i].fin.y;
                    l.tab[i].vitesse *= -1;
                }
                if(l.tab[i].playerDessus)
                {
                    dataJeu.level.persoPrincipal.position.y = l.tab[i].position.y + l.tab[i].hauteur*TILEHAUTEUR-1;
                }
            }
        }
    }
}



void updateTileAnima(struct tileAnimaList &l)
{
    for(int i = 0; i<l.nbTileAnima; i++)
    {
        if(l.tab[i].type<20)
        {
            animationUpdate(l.tab[i].anim, 9);
        }
        else if(l.tab[i].type<=21)
        {
            animationUpdate(l.tab[i].anim, 9);
        }
    }
}




void UpdateScroll(struct Jeu &dataJeu)
{
    int centreX,centreY, xlimmin,xlimmax,ylimmin,ylimmax;
    xlimmin = dataJeu.level.scrollX + XLIM;//Limite min de la fênetre dans lequel le joueur peut se déplacer en x
    ylimmin = dataJeu.level.scrollY+ YLIM;//Limite min de la fênetre dans lequel le joueur peut se déplacer en y
    xlimmax = xlimmin + LARGEURLIM;//Limite max de la fênetre dans lequel le joueur peut se déplacer en x
    ylimmax = ylimmin + HAUTEURLIM;//Limite max de la fênetre dans lequel le joueur peut se déplacer en y
    centreX = dataJeu.level.persoPrincipal.position.x + dataJeu.level.persoPrincipal.largeur/2;//centre du perso en x
    centreY = dataJeu.level.persoPrincipal.position.y + dataJeu.level.persoPrincipal.hauteur/2;//centre du perso en y
    //std::cout<<" apres : "<<dataJeu.level.scrollY<<std::endl;
    if(centreX>xlimmax)
    {
        dataJeu.level.scrollX += centreX - xlimmax;//Déplace la fenêtre de scroll
    }
    if(centreX<xlimmin)
    {
        dataJeu.level.scrollX -= xlimmin-centreX;//Déplace la fenêtre de scroll
    }
    if(centreY>ylimmax)
    {
        dataJeu.level.scrollY += centreY - ylimmax;//Déplace la fenêtre de scroll
    }
    if(centreY<ylimmin)
    {
        dataJeu.level.scrollY -= ylimmin-centreY;//Déplace la fenêtre de scroll
    }


    if(dataJeu.level.scrollX+DIMWX-1>dataJeu.level.nombreTileX*TILELARGEUR)
    {
        dataJeu.level.scrollX = dataJeu.level.nombreTileX*TILELARGEUR-DIMWX+1;
    }
    if(dataJeu.level.scrollX<0)
    {
        dataJeu.level.scrollX=0;
    }
    if(dataJeu.level.scrollY+DIMWY-1>dataJeu.level.nombreTileY*TILEHAUTEUR)
    {
        dataJeu.level.scrollY = dataJeu.level.nombreTileY*TILEHAUTEUR-DIMWY+1;
    }
    if(dataJeu.level.scrollY<0)
    {
        dataJeu.level.scrollY=0;
    }

}












void persoAddForce(struct personnage &p, Vec2 force)
{
    p.force = p.force + force;
}

int persoUpdatePV(struct Jeu &dataJeu)
{
    animationUpdate(dataJeu.level.persoPrincipal.anim, 0);
    if(dataJeu.level.persoPrincipal.vitesse.y>TILEHAUTEUR)
    {
        dataJeu.level.persoPrincipal.vitesse.y = TILEHAUTEUR;
    }
    if(dataJeu.level.persoPrincipal.vitesse.y<-TILEHAUTEUR)
    {
        dataJeu.level.persoPrincipal.vitesse.y = -TILEHAUTEUR;
    }
    if(dataJeu.level.persoPrincipal.vitesse.x>TILELARGEUR/3)
    {
        dataJeu.level.persoPrincipal.vitesse.x = TILELARGEUR/3;
    }
    if(dataJeu.level.persoPrincipal.vitesse.x<-TILELARGEUR/3)
    {
        dataJeu.level.persoPrincipal.vitesse.x = -TILELARGEUR/3;
    }

    if(dataJeu.level.checkPointStat==false&&dataJeu.level.persoPrincipal.position.x>dataJeu.level.checkPointX&&dataJeu.level.numeroLevel!=0)
    {
        dataJeu.level.checkPointStat = true;
        dataJeu.level.listeTileAnima.tab[0] = initTileAnima(dataJeu.level.listeTileAnima.tab[0].tileX, dataJeu.level.listeTileAnima.tab[0].tileY, 21);
        addText((dataJeu.level.listeTileAnima.tab[0].tileX+2)*TILELARGEUR, (dataJeu.level.listeTileAnima.tab[0].tileY+2)*TILELARGEUR, 0.5, "500", 1, dataJeu.level.listeTexte);
        dataJeu.score+=500;
    }
    if(dataJeu.level.persoPrincipal.position.x+dataJeu.level.persoPrincipal.largeur>dataJeu.level.finX&&dataJeu.level.numeroLevel!=0)
    {
        dataJeu.score+=1000;
        return 1;
    }
    if(dataJeu.level.persoPrincipal.position.x<1)
    {
        dataJeu.level.persoPrincipal.position.x = 1;//réajuste les coordonnées
    }
    if(dataJeu.level.persoPrincipal.position.y+dataJeu.level.persoPrincipal.hauteur<1)
    {
        return -1;
    }
    mapCollision(dataJeu.level.persoPrincipal.position,dataJeu.level.persoPrincipal.statAnim, dataJeu.level.persoPrincipal.vitesse, dataJeu.level.persoPrincipal.largeur, dataJeu.level.persoPrincipal.hauteur, dataJeu.level.persoPrincipal.sol, dataJeu, dataJeu.level.persoPrincipal.anim, 0);
    dataJeu.level.persoPrincipal.vitesse = dataJeu.level.persoPrincipal.vitesse + (1/dataJeu.level.persoPrincipal.masse)*DT*dataJeu.level.persoPrincipal.force;
    return 0;
}


void updateText(struct ListeText &l)
{
    for(int i = 0; i<l.nb_text; i++)
    {
        if(l.tab[i].spawn+l.tab[i].duree<elapsedTime())
        {
            reorganiseTabText(l, i);
        }
    }
}

void updateParticules(struct ParticulesList &l)
{
    for(int i = 0; i<l.nb_part; i++)
    {
        l.tab[i].pos = l.tab[i].pos+DT*l.tab[i].vitesse;
        l.tab[i].vitesse = l.tab[i].vitesse + 1/l.tab[i].masse*DT*l.tab[i].force;
        if(l.tab[i].pos.y+l.tab[i].hauteur/2<0)
        {
            reorganiseTabParticule(l, i);
        }
    }
}

void actionEnnemy(struct Jeu &dataJeu, struct Ennemi &e)
{
    switch (e.type)
    {
        case 3://Pierre
            if(e.position.x<dataJeu.level.persoPrincipal.position.x+dataJeu.level.persoPrincipal.largeur&&dataJeu.level.persoPrincipal.position.x<e.position.x+e.largeur&&pointCollision(make_Vec2(e.position.x+e.largeur/2, e.position.y+e.hauteurLoose+1), dataJeu))//&&!testCollision(make_Vec2(e.position.x, e.position.y-1), e.largeur, e.hauteurLoose, dataJeu))
            {
                if(e.vitesse.y>0) e.vitesse.y= 0;
                e.force.y = -G*e.masse/2;
            }
            else
            {
                if(pointCollision(make_Vec2(e.position.x, e.position.y-1), dataJeu))
                {
                    e.force.y =G*e.masse/2;
                }
            }
            break;
        case 2:
            break;

    }
}

void animGrandissementPerso(int largeurMax, int hauteurMax, struct Jeu &dataJeu, double time, struct DataImages &dataImage)//time en dixième de seconde
{

    double t2 = 0;
    double timer = elapsedTime();
    int largeurInit = dataJeu.level.persoPrincipal.largeur;
    int hauteurInit = dataJeu.level.persoPrincipal.hauteur;
    bool stop = false;
    double delai = time/200;
    while(t2<1&&!stop)
    {
        winClear();


        drawJeu(dataImage, dataJeu);

        if(timer+delai<elapsedTime())
        {
            timer = elapsedTime();
            t2+= 0.05;
            if(t2>1)t2=1;
            dataJeu.level.persoPrincipal.largeur = (1 - t2)*largeurInit + t2*largeurMax;
            dataJeu.level.persoPrincipal.hauteur = (1 - t2)*hauteurInit + t2*hauteurMax;
        }

        stop = winDisplay();
    }
}



int ennemyUpdatePv(struct Jeu &dataJeu, struct DataImages &dataImage)
{
    for(int i = 0; i<dataJeu.level.listeEnnemies.nombreEnnemi; i++)
    {
        int hauteur = dataJeu.level.listeEnnemies.tab[i].hauteurLoose+dataJeu.level.listeEnnemies.tab[i].hauteurWin;
        if(dataJeu.level.listeEnnemies.tab[i].position.x+dataJeu.level.listeEnnemies.tab[i].largeur>dataJeu.level.scrollX&&dataJeu.level.listeEnnemies.tab[i].position.x<dataJeu.level.scrollX+DIMWX)
        {
            if(dataJeu.level.listeEnnemies.tab[i].inLive)
            {
                animationUpdate(dataJeu.level.listeEnnemies.tab[i].anim, dataJeu.level.listeEnnemies.tab[i].type+1);

                switch(testCollisionEnnemy(dataJeu.level.listeEnnemies.tab[i], dataJeu.level.persoPrincipal.position, dataJeu.level.persoPrincipal.largeur, dataJeu.level.persoPrincipal.hauteur))
                {
                    case 1:
                        dataJeu.level.listeEnnemies.tab[i].inLive = false;
                        if(dataJeu.level.listeEnnemies.tab[i].type!=2)
                        {
                            addText(dataJeu.level.listeEnnemies.tab[i].position.x+2*TILELARGEUR, dataJeu.level.listeEnnemies.tab[i].position.y+2*TILEHAUTEUR, 0.5, "100", 1, dataJeu.level.listeTexte);
                            dataJeu.score+=100;
                        }
                        if((dataJeu.level.listeEnnemies.tab[i].type==1||dataJeu.level.listeEnnemies.tab[i].type==2))//Si c'est un koopa ou une carapace
                        {
                            if (dataJeu.level.listeEnnemies.tab[i].type==1)
                            {
                                dataJeu.level.listeEnnemies.tab[i].hauteurLoose = 0;
                                dataJeu.level.listeEnnemies.tab[i].hauteurWin = TILEHAUTEUR;
                                dataJeu.level.listeEnnemies.tab[i].anim.frame = 0;
                                dataJeu.level.listeEnnemies.tab[i].anim.frameMax = 6;
                                dataJeu.level.listeEnnemies.tab[i].type = 2;
                                dataJeu.level.listeEnnemies.tab[i].vitesse = make_Vec2(0, 0);
                            }
                            else if(dataJeu.level.persoPrincipal.vitesse.y<=0)
                            {
                                dataJeu.level.listeEnnemies.tab[i].hauteurLoose = 0;
                                dataJeu.level.listeEnnemies.tab[i].hauteurWin = TILEHAUTEUR;
                                dataJeu.level.listeEnnemies.tab[i].anim.frame = 0;
                                dataJeu.level.listeEnnemies.tab[i].anim.frameMax = 6;
                                dataJeu.level.listeEnnemies.tab[i].type = 2;
                                dataJeu.level.listeEnnemies.tab[i].vitesse = make_Vec2(0, 0);
                            }
                            else
                            {
                                dataJeu.level.listeEnnemies.tab[i].inLive = true;
                            }

                        }

                        else
                        {
                            dataJeu.level.listeEnnemies.tab[i].hauteurWin = 0;
                            dataJeu.level.listeEnnemies.tab[i].vitesse = make_Vec2(2, 5);
                        }
                        dataJeu.level.persoPrincipal.vitesse.y = TILEHAUTEUR*15/32;
                        break;
                    case 2:
                        if(dataJeu.level.persoPrincipal.finInvincible<elapsedTime())
                        {
                            if(dataJeu.level.persoPrincipal.hauteur==TILEHAUTEUR*2)
                            {
                                animGrandissementPerso(TILELARGEUR, TILEHAUTEUR, dataJeu, 10, dataImage);
                                dataJeu.level.persoPrincipal.finInvincible = elapsedTime()+5;
                            }
                            else
                            {
                                return -1;
                            }
                        }
                        break;
                }
            }
            else if(dataJeu.level.listeEnnemies.tab[i].type==2)//Si c'est une carapace
            {
                if(dataJeu.level.persoPrincipal.vitesse.y<=0&&testCollisionEnnemy(dataJeu.level.listeEnnemies.tab[i], dataJeu.level.persoPrincipal.position, dataJeu.level.persoPrincipal.largeur, dataJeu.level.persoPrincipal.hauteur)==1)
                {
                        dataJeu.level.listeEnnemies.tab[i].inLive = true;
                        dataJeu.level.listeEnnemies.tab[i].hauteurLoose = TILEHAUTEUR*22/32;
                        dataJeu.level.listeEnnemies.tab[i].hauteurWin =  TILEHAUTEUR*10/32;

                        dataJeu.level.listeEnnemies.tab[i].anim.frameMax = 6;
                        dataJeu.level.listeEnnemies.tab[i].vitesse = make_Vec2(TILEHAUTEUR*7/32*(dataJeu.level.persoPrincipal.vitesse.x>=0 ? 1: -1), 0);
                        char statAnim;
                        mapCollision(dataJeu.level.listeEnnemies.tab[i].position, statAnim,dataJeu.level.listeEnnemies.tab[i].vitesse, dataJeu.level.listeEnnemies.tab[i].largeur, hauteur, dataJeu.level.listeEnnemies.tab[i].sol, dataJeu, dataJeu.level.listeEnnemies.tab[i].anim, dataJeu.level.listeEnnemies.tab[i].type+1);
                        dataJeu.level.persoPrincipal.vitesse.y = TILEHAUTEUR*15/32;
                }
            }
            actionEnnemy(dataJeu, dataJeu.level.listeEnnemies.tab[i]);

            if(dataJeu.level.listeEnnemies.tab[i].type!=4&&dataJeu.level.listeEnnemies.tab[i].type!=5)
            {
                if(dataJeu.level.listeEnnemies.tab[i].vitesse.y<-TILEHAUTEUR*10/32)
                {
                    dataJeu.level.listeEnnemies.tab[i].vitesse.y = -TILEHAUTEUR*10/32;
                }
                if(dataJeu.level.listeEnnemies.tab[i].vitesse.y>TILEHAUTEUR*10/32)
                {
                    dataJeu.level.listeEnnemies.tab[i].vitesse.y = TILEHAUTEUR*10/32;
                }
            }
            else if(dataJeu.level.listeEnnemies.tab[i].type==4)
            {
                if(dataJeu.level.listeEnnemies.tab[i].vitesse.y>TILEHAUTEUR*10/32)
                {
                    dataJeu.level.listeEnnemies.tab[i].vitesse.y = TILEHAUTEUR*10/32;
                }
                if(dataJeu.level.listeEnnemies.tab[i].vitesse.y<-TILEHAUTEUR*15/32)
                {
                    dataJeu.level.listeEnnemies.tab[i].vitesse.y = -TILEHAUTEUR*15/32;
                }
            }
            else
            {
                dataJeu.level.listeEnnemies.tab[i].position.y += DT*dataJeu.level.listeEnnemies.tab[i].action;
                dataJeu.level.listeEnnemies.tab[i].vitesse.y+=DT*dataJeu.level.listeEnnemies.tab[i].action;
                if(dataJeu.level.listeEnnemies.tab[i].vitesse.y>TILEHAUTEUR*3)
                {
                    dataJeu.level.listeEnnemies.tab[i].action = -3;
                }
                if(dataJeu.level.listeEnnemies.tab[i].vitesse.y<0)
                {
                    dataJeu.level.listeEnnemies.tab[i].action = 3;
                }
            }

            if(dataJeu.level.listeEnnemies.tab[i].type!=5)
            {
                if(dataJeu.level.listeEnnemies.tab[i].vitesse.x>TILELARGEUR*7/32)
                {
                    dataJeu.level.listeEnnemies.tab[i].vitesse.x = TILELARGEUR*7/32;
                }
                if(dataJeu.level.listeEnnemies.tab[i].vitesse.x<-TILELARGEUR*7/32)
                {
                    dataJeu.level.listeEnnemies.tab[i].vitesse.x = -TILELARGEUR*7/32;
                }
            }
            if(dataJeu.level.listeEnnemies.tab[i].inLive == false&&dataJeu.level.listeEnnemies.tab[i].type!=2)
            {
                if(dataJeu.level.listeEnnemies.tab[i].vitesse.y>TILEHAUTEUR*5/32)
                {
                    dataJeu.level.listeEnnemies.tab[i].vitesse.y = TILEHAUTEUR*5/32;
                }
                if(dataJeu.level.listeEnnemies.tab[i].vitesse.y<-TILEHAUTEUR*5/32)
                {
                    dataJeu.level.listeEnnemies.tab[i].vitesse.y = -TILEHAUTEUR*5/32;
                }
                dataJeu.level.listeEnnemies.tab[i].position = dataJeu.level.listeEnnemies.tab[i].position+ DT*dataJeu.level.listeEnnemies.tab[i].vitesse;
            }
            else if(dataJeu.level.listeEnnemies.tab[i].type!=5)//Si c'est pas une fleur
            {
                char statAnim;
                if(mapCollision(dataJeu.level.listeEnnemies.tab[i].position, statAnim, dataJeu.level.listeEnnemies.tab[i].vitesse, dataJeu.level.listeEnnemies.tab[i].largeur, hauteur, dataJeu.level.listeEnnemies.tab[i].sol, dataJeu, dataJeu.level.listeEnnemies.tab[i].anim, dataJeu.level.listeEnnemies.tab[i].type + 1))
                {

                    dataJeu.level.listeEnnemies.tab[i].inLive = false;
                    dataJeu.level.listeEnnemies.tab[i].vitesse = make_Vec2(0, 5);
                    dataJeu.level.listeEnnemies.tab[i].force = make_Vec2(0, -0.7);
                }
            }

            if(dataJeu.level.listeEnnemies.tab[i].position.y<1&&dataJeu.level.listeEnnemies.tab[i].type!=5)
            {
                reorganiseTabEnnemy(dataJeu.level.listeEnnemies, i);
                //reorganiseTabBonus(dataJeu.level.listeEnnemies, i);//réajustes les coordonnées
            }
            dataJeu.level.listeEnnemies.tab[i].vitesse = dataJeu.level.listeEnnemies.tab[i].vitesse + (1/dataJeu.level.listeEnnemies.tab[i].masse)*DT*dataJeu.level.listeEnnemies.tab[i].force;

        }
    }
    return 0;
}







void bonusUpdatePv(struct Jeu &dataJeu, struct DataImages &dataImage)
{
    for(int i = 0; i<dataJeu.level.listeBonus.nombreBonus; i++)
    {
        animationUpdate(dataJeu.level.listeBonus.tab[i].anim, dataJeu.level.listeBonus.tab[i].type + 10);

        if(dataJeu.level.listeBonus.tab[i].vitesse.y>TILEHAUTEUR/1.5)
        {
            dataJeu.level.listeBonus.tab[i].vitesse.y = TILEHAUTEUR/1.5;
        }
        if(dataJeu.level.listeBonus.tab[i].vitesse.y<-TILEHAUTEUR/2)
        {
            dataJeu.level.listeBonus.tab[i].vitesse.y = -TILEHAUTEUR/2;
        }
        if(dataJeu.level.listeBonus.tab[i].vitesse.x>TILELARGEUR/8)
        {
            dataJeu.level.listeBonus.tab[i].vitesse.x = TILELARGEUR/8;
        }
        if(dataJeu.level.listeBonus.tab[i].vitesse.x<-TILELARGEUR/8)
        {
            dataJeu.level.listeBonus.tab[i].vitesse.x = -TILELARGEUR/8;
        }


        if(dataJeu.level.listeBonus.tab[i].type!=0)//Si ce n'est pas une pièce on regarde si il y a collision avec un mur
        {
            char statAnim;
            char sol;

            mapCollision(dataJeu.level.listeBonus.tab[i].position, statAnim, dataJeu.level.listeBonus.tab[i].vitesse, dataJeu.level.listeBonus.tab[i].largeur, dataJeu.level.listeBonus.tab[i].hauteur, sol, dataJeu, dataJeu.level.listeBonus.tab[i].anim, dataJeu.level.listeBonus.tab[i].type+DEBUTBONUSFONCTIONCOMMUN);
            dataJeu.level.listeBonus.tab[i].vitesse = dataJeu.level.listeBonus.tab[i].vitesse + (1/dataJeu.level.listeBonus.tab[i].masse)*DT*dataJeu.level.listeBonus.tab[i].force;

        }
        else
        {
            dataJeu.level.listeBonus.tab[i].position = dataJeu.level.listeBonus.tab[i].position + DT*dataJeu.level.listeBonus.tab[i].vitesse;
            dataJeu.level.listeBonus.tab[i].vitesse = dataJeu.level.listeBonus.tab[i].vitesse + (1/dataJeu.level.listeBonus.tab[i].masse)*DT*dataJeu.level.listeBonus.tab[i].force;
            if(dataJeu.level.listeBonus.tab[i].vitesse.y<0)
            {
                addText(dataJeu.level.listeBonus.tab[i].position.x, dataJeu.level.listeBonus.tab[i].position.y, 0.5, "100", 1, dataJeu.level.listeTexte);
                dataJeu.nb_pieces++;
                if(dataJeu.nb_pieces==100)
                {
                    dataJeu.nb_pieces=0;
                    dataJeu.nb_vie++;
                }
                dataJeu.score+=100;
                reorganiseTabBonus(dataJeu.level.listeBonus, i);
            }
        }

        if(dataJeu.level.listeBonus.tab[i].position.x<1)
        {
            dataJeu.level.listeBonus.tab[i].position.x = 1;//réajuste les coordonnées
        }
        if(dataJeu.level.listeBonus.tab[i].position.y<1)
        {
            reorganiseTabBonus(dataJeu.level.listeBonus, i);//réajustes les coordonnées
        }
        if(dataJeu.level.listeBonus.tab[i].position.y>dataJeu.level.nombreTileY*TILEHAUTEUR&&dataJeu.level.listeBonus.tab[i].type ==0)
        {
            reorganiseTabBonus(dataJeu.level.listeBonus, i);
        }
        else if(collisionRectangle(dataJeu.level.listeBonus.tab[i].position.x, dataJeu.level.listeBonus.tab[i].position.y, dataJeu.level.listeBonus.tab[i].largeur, dataJeu.level.listeBonus.tab[i].hauteur, dataJeu.level.persoPrincipal.position.x, dataJeu.level.persoPrincipal.position.y, dataJeu.level.persoPrincipal.largeur, dataJeu.level.persoPrincipal.hauteur))
        {
            reorganiseTabBonus(dataJeu.level.listeBonus, i);
            if(dataJeu.level.listeBonus.tab[i].type==0)
            {
                addText(dataJeu.level.persoPrincipal.position.x+TILELARGEUR*2, dataJeu.level.persoPrincipal.position.y+TILELARGEUR*2, 0.5, "50", 1, dataJeu.level.listeTexte);
                dataJeu.nb_pieces++;
                dataJeu.score+=50;
                if(dataJeu.nb_pieces==100)
                {
                    dataJeu.nb_pieces=0;
                    dataJeu.nb_vie++;
                }
            }
            else if(dataJeu.level.listeBonus.tab[i].type==1)//Champignon grand
            {
                addText(dataJeu.level.persoPrincipal.position.x+TILELARGEUR*2, dataJeu.level.persoPrincipal.position.y+TILELARGEUR*2, 0.5, "100", 1, dataJeu.level.listeTexte);
                animGrandissementPerso(TILELARGEUR, TILEHAUTEUR*2, dataJeu, 5, dataImage);
                dataJeu.level.persoPrincipal.masse = 10;
                dataJeu.score+=100;
            }
            else if(dataJeu.level.listeBonus.tab[i].type==2)//Champignon mini
            {
                addText(dataJeu.level.persoPrincipal.position.x+TILELARGEUR*2, dataJeu.level.persoPrincipal.position.y+TILELARGEUR*2, 0.5, "100", 1, dataJeu.level.listeTexte);
                animGrandissementPerso(TILELARGEUR*0.5, TILEHAUTEUR*0.5, dataJeu, 5, dataImage);
                dataJeu.level.persoPrincipal.masse = 15;
                dataJeu.score+=100;
            }
            else if(dataJeu.level.listeBonus.tab[i].type==3)//Champignon up
            {
                addText(dataJeu.level.persoPrincipal.position.x+TILELARGEUR*2, dataJeu.level.persoPrincipal.position.y+TILELARGEUR*2, 0.5, "1 UP", 1, dataJeu.level.listeTexte);
                dataJeu.nb_vie++;
            }
        }
    }
}

int menuPauseInGame(struct Jeu &dataJeu, struct DataImages dataImage)
{
    bool stop = false;
    while(!stop)
    {
        winClear();
        drawJeu(dataImage, dataJeu);
        color(0, 0, 0, 100);
        rectangleFill(1, 1, DIMWX, DIMWY);
        image_draw(dataImage.button[2], DIMWX/4, DIMWY*0.75-DIMWY/15, DIMWX/2, DIMWY/7.5);//Bouton continuer
        image_draw(dataImage.button[1], DIMWX/4, DIMWY*0.5-DIMWY/15, DIMWX/2, DIMWY/7.5);//Bouton menu
        image_draw(dataImage.button[0], DIMWX/4, DIMWY*0.25-DIMWY/15, DIMWX/2, DIMWY/7.5);//Bouton quitter
        if(isMousePressed(SDL_BUTTON_LEFT))
        {
            int x, y;
            mousePos(x,y);
            color(255, 0, 0);
            rectangleFill(x-1, y-1, x+1, y+1);
            if(x>DIMWX/4&&x<DIMWX*0.75)
            {
                if(y>DIMWY*0.25-DIMWY/15&&y<DIMWY*0.25+DIMWY/15)
                {
                    return 3;
                }
                if(y>DIMWY*0.5-DIMWY/15&&y<DIMWY*0.5+DIMWY/15)
                {
                    return 2;
                }
                if(y>DIMWY*0.75-DIMWY/15&&y<DIMWY*0.75+DIMWY/15)
                {
                    return 0;
                }
            }
        }
        stop = winDisplay();
    }
}

void degradeLineaire(Color a, Color c, Vec2 posA, Vec2 posC, int type)
{
    float debut, fin;
    if(type ==1)//Degradé de haut en bas
    {
        debut = posA.y;
        fin = posC.y;
    }
    else
    {
        debut = posA.x;
        fin = posC.x;
    }
    for(int i = debut; i<fin; i+=2)
    {
        float t = (i - debut)/(fin - debut);
        Color p = (1 - t)* a + t * c;

        color(p.r, p.g, p.b);
        if(type==1)
        {
            rectangleFill(posA.x, i, posC.x, i+2);
        }
        else
        {
            rectangleFill(i, posA.y, i+2, posC.y);
        }
    }
}


void fondu(double time, Color a, Color b)
{
    double temp = elapsedTime();
    double t = 0;
    bool stop = false;
    double delay = time/100;
    while(t<1&&!stop)
    {
        winClear();
        Color te = (1-t)* a + t*b;
        color(te.r, te.g, te.b);
        rectangleFill(1,1, DIMWX, DIMWY);
        if(temp+delay<elapsedTime())
        {
            temp = elapsedTime();
            t+=0.01;
        }
        stop = winDisplay();
    }

}


void afficheEcranDebut(struct DataImages &dataImage)
{
    struct Animation anim;
    anim.frame = 0;
    anim.frameMax = MAXFRAMECOURSE;
    anim.temp = elapsedTime();
    double scrollX = 0;
    bool stop = false;
    int i;
    while(!stop&&!isKeyPressed(SDLK_RETURN))
    {
        winClear();
        animationUpdate(anim, 0);

        for(i = 0; i<2; i++) image_draw(dataImage.background[0], 1-scrollX+ i*DIMWX, 1, DIMWX, DIMWY);
        for(i = 0; i<DIMWX/TILELARGEUR+1; i++)
        {
            image_draw(dataImage.sol[17], 1-int(scrollX)%TILELARGEUR + i*TILELARGEUR, 1, TILELARGEUR, TILEHAUTEUR);
        }
        image_draw(dataImage.perso[2][anim.frame],TILELARGEUR*5, TILEHAUTEUR, TILELARGEUR, TILEHAUTEUR*2);
        image_draw(dataImage.imagesSup[3], DIMWX*0.25, DIMWY*0.5, DIMWX*0.5, DIMWY*0.4);
        drawMessage("Appuyez sur Entrer", dataImage, DIMWX*0.1, DIMWY*0.4, DIMWX/500);
        scrollX+=DT*TILELARGEUR/4;
        if(scrollX>DIMWX)
        {
            scrollX=0;
        }
        stop = winDisplay();
    }
    if(stop==false)
    {
        fondu(2, {255, 255, 255}, {0, 0, 0});
        fondu(2, {0, 0, 0} ,{255, 255, 255});
    }

}

void afficheJeuTermine(struct DataImages &dataImage, int score)
{
    double fin = elapsedTime()+10, temp = elapsedTime();
    bool stop = false;
    double y=DIMWY;
    fondu(1, {255, 255, 255}, {0, 0, 0});
    while(! stop && fin>elapsedTime()&&!isKeyPressed(SDLK_RETURN))
    {
        winClear();
        if(temp + 0.01<elapsedTime())
        {
            temp = elapsedTime();
            y-=(DIMWY*1.0/3)/250;
            if(y<DIMWY/1.5)
            {
                y=DIMWY/1.5;
            }
        }
        degradeLineaire({0,0,0}, {27, 32, 60}, {1, 1}, {DIMWX/2, DIMWY}, 2);
        degradeLineaire({27, 32, 60}, {0,0,0}, {DIMWX/2, 1}, {DIMWX, DIMWY}, 2);
        drawMessage("JEU TERMINE", dataImage, DIMWX/5.5, y, DIMWX/400);
        if(y==DIMWY/1.5)drawNumber(dataImage, DIMWX/3.5, DIMWY/4, DIMWX/20, DIMWY/10, -2, score, 8);
        stop = winDisplay();
    }
    fondu(1, {0, 0, 0}, {255, 255, 255});
}

void afficheDommage(struct DataImages &dataImage, int score)
{
    double fin = elapsedTime()+10, temp = elapsedTime();
    bool stop = false;
    double y=DIMWY;
    fondu(1, {255, 255, 255}, {100, 0, 0});
    while(! stop && fin>elapsedTime()&&!isKeyPressed(SDLK_RETURN))
    {
        winClear();
        if(temp + 0.01<elapsedTime())
        {
            temp = elapsedTime();
            y-=(DIMWY*1.0/3)/250;
            if(y<DIMWY/1.5)
            {
                y=DIMWY/1.5;
            }
        }
        degradeLineaire({0,0,0}, {200, 0, 0}, {1, 1}, {DIMWX/2, DIMWY}, 2);
        degradeLineaire({200, 0, 0}, {0,0,0}, {DIMWX/2, 1}, {DIMWX, DIMWY}, 2);
        drawMessage("DOMMAGE", dataImage, DIMWX/6, y, DIMWX/400);
        if(y==DIMWY/1.5)drawNumber(dataImage, DIMWX/3.5, DIMWY/4, DIMWX/20, DIMWY/10, -2, score, 8);
        stop = winDisplay();
    }
    fondu(1, {100, 0, 0}, {255, 255, 255});
}

void afficheGameOver(struct DataImages &dataImage, int score)
{
    double fin = elapsedTime()+10, temp = elapsedTime();
    bool stop = false;
    double y=DIMWY;
    fondu(1, {255, 255, 255}, {100, 0, 0});
    while(! stop && fin>elapsedTime()&&!isKeyPressed(SDLK_RETURN))
    {
        winClear();
        if(temp + 0.01<elapsedTime())
        {
            temp = elapsedTime();
            y-=(DIMWY*1.0/3)/250;
            if(y<DIMWY/1.5)
            {
                y=DIMWY/1.5;
            }
        }
        degradeLineaire({0,0,0}, {200, 0, 0}, {1, 1}, {DIMWX/2, DIMWY}, 2);
        degradeLineaire({200, 0, 0}, {0,0,0}, {DIMWX/2, 1}, {DIMWX, DIMWY}, 2);
        drawMessage("GAME OVER", dataImage, DIMWX/6, y, DIMWX/400);
        if(y==DIMWY/1.5)drawNumber(dataImage, DIMWX/3.5, DIMWY/4, DIMWX/20, DIMWY/10, -2, score, 8);
        stop = winDisplay();
    }
    fondu(1, {100, 0, 0}, {255, 255, 255});
}

void afficheClear(struct DataImages &dataImage, int score)
{
    double fin = elapsedTime()+5, temp = elapsedTime();
    bool stop = false;
    double y=DIMWY;
    fondu(1, {255, 255, 255}, {0, 0, 100});
    while(! stop && fin>elapsedTime()&&!isKeyPressed(SDLK_RETURN))
    {
        winClear();
        if(temp + 0.01<elapsedTime())
        {
            temp = elapsedTime();
            y-=(DIMWY*1.0/3)/100;
            if(y<DIMWY/1.5)
            {
                y=DIMWY/1.5;
            }
        }
        degradeLineaire({0,0,0}, {0, 0, 200}, {1, 1}, {DIMWX/2, DIMWY}, 1);
        degradeLineaire({0, 0, 200}, {0,0,0}, {DIMWX/2, 1}, {DIMWX, DIMWY}, 1);
        drawMessage("CLEAR", dataImage, DIMWX/3.5, y, DIMWX/400);
        if(y==DIMWY/1.5)drawNumber(dataImage, DIMWX/3.5, DIMWY/4, DIMWX/20, DIMWY/10, -2, score, 8);
        stop = winDisplay();
    }
    fondu(1, {0, 0, 100}, {255, 255, 255});

}

void afficheLevel(struct DataImages &dataImage, struct Jeu &dataJeu, int level)
{
    double fin = elapsedTime()+5, temp = elapsedTime();
    bool stop = false;
    fondu(1, {255, 255, 255},{0, 0, 0});
    char chaine[100] ="Monde ";
    chaine[6] = level/5+1+'0';
    chaine[7] = '\0';
    strcat(chaine, " level ");
    chaine[14] = (level-level/5*4)+'0';
    chaine[15]='\0';
    while(! stop && fin>elapsedTime()&&!isKeyPressed(SDLK_RETURN)||isKeyPressed(SDLK_UP))
    {
        winClear();
        color(0,0,0);
        rectangleFill(1, 1, DIMWX, DIMWY);
        drawMessage(chaine, dataImage, DIMWX/3, DIMWY/1.5, DIMWX/1000);
        image_draw(dataImage.bonus[0][0], DIMWX/2.3, DIMWY/2.5, DIMWX/40, DIMWY/30);//Affichage de la pièce
        image_draw(dataImage.font[0][1], DIMWX/2.3+DIMWX/40, DIMWY/2.5, DIMWX/40, DIMWY/30);//Affichage du fois
        drawNumber(dataImage, DIMWX/2.3+DIMWX/20, DIMWY/2.5, DIMWX/40, DIMWY/30, 0, dataJeu.nb_pieces, 2);//Affichage du nombre de pièce

        image_draw(dataImage.font[0][2], DIMWX/2.4, DIMWY/3, DIMWX/20, DIMWY/15);
        image_draw(dataImage.font[0][1], DIMWX/2.4+DIMWX/20, DIMWY/3, DIMWX/40, DIMWY/30);//Affichage du fois
        drawNumber(dataImage, DIMWX/2.4+DIMWX*3/40, DIMWY/3, DIMWX/40, DIMWY/30, 0, dataJeu.nb_vie, 2);//Affichage du nombre de vie

        stop = winDisplay();
    }
    fondu(1, {0, 0, 0},{255, 255, 255});
}

int fonctionPrincipalLevel(int level, struct Jeu dataJeu, struct DataImages &dataImage, int &nombreVie, int &nombrePieces, int &largeurPerso, int &hauteurPerso, float &masse, int &score, char &checkPoint)
{

    bool stop=false;
    int statPartie=0;
    double timer = elapsedTime();
    initLevel(dataJeu, level);
    if(checkPoint==level)
    {
        dataJeu.level.checkPointStat = true;
        dataJeu.level.persoPrincipal = initPerso(dataJeu.level.checkPointX, dataJeu.level.listeTileAnima.tab[0].tileY*TILEHAUTEUR, largeurPerso, hauteurPerso, masse);
        dataJeu.level.listeTileAnima.tab[0] = initTileAnima(dataJeu.level.listeTileAnima.tab[0].tileX, dataJeu.level.listeTileAnima.tab[0].tileY, 21);
    }
    else
    {
        checkPoint = 0;
        dataJeu.level.persoPrincipal = initPerso(dataJeu.level.debutX, dataJeu.level.debutY, largeurPerso, hauteurPerso, masse);
    }
    checkPoint = 0;

    persoAddForce(dataJeu.level.persoPrincipal, make_Vec2(0, (TILEHAUTEUR*(-2)/32)*dataJeu.level.persoPrincipal.masse));
    dataJeu.level.scrollX = 1;
    dataJeu.level.scrollY = 1;
    dataJeu.level.debut = elapsedTime();
    dataJeu.level.secondeRestante = 200;
    while( !stop &&statPartie==0)
    {
        winClear();
        if(isKeyPressed(SDLK_RIGHT))
        {
            if(dataJeu.level.persoPrincipal.vitesse.x < 0)
            {
                if(signe(dataJeu.level.persoPrincipal.vitesse.x- DT*signe(dataJeu.level.persoPrincipal.vitesse.x))!=signe(dataJeu.level.persoPrincipal.vitesse.x))
                {
                    dataJeu.level.persoPrincipal.vitesse.x = 0;
                    dataJeu.level.persoPrincipal.force.x = 0;

                }
                else
                {
                    dataJeu.level.persoPrincipal.vitesse.x-= DT*signe(dataJeu.level.persoPrincipal.vitesse.x);
                    dataJeu.level.persoPrincipal.force.x -= DT*signe(dataJeu.level.persoPrincipal.force.x);
                }
             }
             else
             {
                dataJeu.level.persoPrincipal.force.x = TILEHAUTEUR*3/32;
             }

        }
        else if(isKeyPressed(SDLK_LEFT))
        {
            if(dataJeu.level.persoPrincipal.vitesse.x > 0)
            {
                if(signe(dataJeu.level.persoPrincipal.vitesse.x- DT*signe(dataJeu.level.persoPrincipal.vitesse.x))!=signe(dataJeu.level.persoPrincipal.vitesse.x))
                {
                    dataJeu.level.persoPrincipal.vitesse.x = 0;
                    dataJeu.level.persoPrincipal.force.x = 0;

                }
                else
                {
                    dataJeu.level.persoPrincipal.vitesse.x-= DT*signe(dataJeu.level.persoPrincipal.vitesse.x);
                    dataJeu.level.persoPrincipal.force.x -= DT*signe(dataJeu.level.persoPrincipal.force.x);
                }
             }
             else
             {
                dataJeu.level.persoPrincipal.force.x = -TILEHAUTEUR*3/32;
             }

        }
        else
        {
            //std::cout<<dataJeu.level.persoPrincipal.vitesse.x<<std::endl;
            if(signe(dataJeu.level.persoPrincipal.vitesse.x- DT*signe(dataJeu.level.persoPrincipal.vitesse.x))!=signe(dataJeu.level.persoPrincipal.vitesse.x))
            {
                dataJeu.level.persoPrincipal.vitesse.x = 0;
                dataJeu.level.persoPrincipal.force.x = 0;

            }
            else
            {
                dataJeu.level.persoPrincipal.vitesse.x-= DT*signe(dataJeu.level.persoPrincipal.vitesse.x);
                dataJeu.level.persoPrincipal.force.x -= DT*signe(dataJeu.level.persoPrincipal.force.x);
            }
        }



        if(isKeyPressed(SDLK_UP))
        {
            if(dataJeu.level.persoPrincipal.sol == true)
            {
                dataJeu.level.persoPrincipal.vitesse.y=TILEHAUTEUR*25/32;
            }
            else if(dataJeu.level.persoPrincipal.vitesse.y<0&&((dataJeu.level.persoPrincipal.vitesse.x>=0&&pointCollision(make_Vec2(dataJeu.level.persoPrincipal.position.x+dataJeu.level.persoPrincipal.largeur+1, dataJeu.level.persoPrincipal.position.y), dataJeu))||(dataJeu.level.persoPrincipal.vitesse.x<0&&pointCollision(make_Vec2(dataJeu.level.persoPrincipal.position.x-1, dataJeu.level.persoPrincipal.position.y), dataJeu))))
            {
                dataJeu.level.persoPrincipal.vitesse.y=TILEHAUTEUR*25/32;
                dataJeu.level.persoPrincipal.force.x *= -1;
                dataJeu.level.persoPrincipal.vitesse.x = signe(dataJeu.level.persoPrincipal.force.x)*20;
            }
        }
        if(isKeyPressed(SDLK_RETURN))
        {
            statPartie = menuPauseInGame(dataJeu, dataImage);
        }
        drawJeu(dataImage, dataJeu);
        if(statPartie==0)
        {
            statPartie=persoUpdatePV(dataJeu);//renvoie -1 si mort du joueur, 0 si aucune fin (loose ou win), 1 si win
            if(statPartie==0)//Si on continue alors update du reste
            {
                statPartie= ennemyUpdatePv(dataJeu, dataImage);//renvoie -1 si mort du joueur 0 sinon
                if(statPartie==0)//pareil
                {
                    UpdateScroll(dataJeu);
                    bonusUpdatePv(dataJeu, dataImage);
                    updateTileMobileList(dataJeu.level.listeTileMobile, dataJeu);
                    updateTileAnima(dataJeu.level.listeTileAnima);
                    updateParticules(dataJeu.level.listeParticules);
                    updateText(dataJeu.level.listeTexte);
                }
            }
        }
        if(timer+1<elapsedTime())
        {
            timer=elapsedTime();
            dataJeu.level.secondeRestante--;
            if(dataJeu.level.secondeRestante==0)
            {
                statPartie=-1;
            }
        }

        stop = winDisplay();
    }
    nombrePieces = dataJeu.nb_pieces;
    nombreVie = dataJeu.nb_vie;
    if(statPartie!=1)
    {
        largeurPerso = TILELARGEUR;//type normal
        hauteurPerso = TILEHAUTEUR;
        masse = 10;
        nombreVie--;
        if(nombreVie!=0&&statPartie==-1)
        {
            afficheDommage(dataImage, dataJeu.score);
        }
        if(dataJeu.level.checkPointStat)
        {
            checkPoint = level;
        }
    }
    else
    {
        score += dataJeu.score;
        largeurPerso = dataJeu.level.persoPrincipal.largeur;
        hauteurPerso = dataJeu.level.persoPrincipal.hauteur;
        masse = dataJeu.level.persoPrincipal.masse;
        afficheClear(dataImage, dataJeu.score);
        checkPoint = 0;
    }
    return statPartie;
}

void drawSelect(struct DataImages &dataImage, struct Jeu &dataJeu)
{
    int taille = 30*TILELARGEUR;
    for(int i = 0; i<2; i++)
    {
        image_draw(dataImage.background[((dataJeu.level.scrollX/taille) + i)%2], (-1*dataJeu.level.scrollX)%taille+ i*taille,1,taille, DIMWY);
    }
    for(int i = dataJeu.level.scrollY/TILEHAUTEUR; i<=(dataJeu.level.scrollY+DIMWY)/TILEHAUTEUR; i++)
    {
        for(int j = dataJeu.level.scrollX/TILELARGEUR; j<=(dataJeu.level.scrollX+DIMWX)/TILELARGEUR; j++)
        {
            if(i<17&&j<80&&i>=0&&j>=0)
            {
                if(dataJeu.level.level[i][j]>=0&&dataJeu.level.level[i][j]!=1)
                {
                    int x = j*TILELARGEUR-dataJeu.level.scrollX;
                    int y = i*TILEHAUTEUR-dataJeu.level.scrollY;
                    image_draw(dataImage.sol[dataJeu.level.level[i][j]], x, y, TILELARGEUR, TILEHAUTEUR);
                }
                else if(dataJeu.level.level[i][j]<-1)
                {
                    int x = j*TILELARGEUR-dataJeu.level.scrollX;
                    int y = i*TILEHAUTEUR-dataJeu.level.scrollY;
                    if(dataJeu.level.level[i][j]==-7)
                    {
                        color(255,255,10);
                    }
                    else
                    {
                        color(0, 0, 0);
                    }
                    rectangleFill(x, y, x+TILELARGEUR, y+TILEHAUTEUR);
                }
            }
        }
    }

    affichePerso(dataJeu.level.persoPrincipal, dataJeu, dataImage);
    drawAffichageInGame(dataImage, dataJeu);
}





int selectionLevel(struct Jeu dataJeu, struct DataImages &dataImage)
{
    bool stop=false;
    int statPartie=0, levelWin = 0;
    double timer = elapsedTime();
    char checkPoint = 0;
    initLevel(dataJeu, 0);
    dataJeu.level.persoPrincipal = initPerso(1, dataJeu.level.nombreTileY*TILEHAUTEUR, TILELARGEUR*1, TILEHAUTEUR*2, 10);
    persoAddForce(dataJeu.level.persoPrincipal, make_Vec2(0, (TILEHAUTEUR*(-2)/32)*dataJeu.level.persoPrincipal.masse));
    dataJeu.level.scrollX = 1;
    dataJeu.level.scrollY = 1;
    dataJeu.level.debut = elapsedTime();
    dataJeu.level.secondeRestante=0;
    while( !stop &&statPartie==0)
    {
        winClear();
        if(isKeyPressed(SDLK_RIGHT))
        {
            if(dataJeu.level.persoPrincipal.vitesse.x < 0)
            {
                if(signe(dataJeu.level.persoPrincipal.vitesse.x- DT*signe(dataJeu.level.persoPrincipal.vitesse.x))!=signe(dataJeu.level.persoPrincipal.vitesse.x))
                {
                    dataJeu.level.persoPrincipal.vitesse.x = 0;
                    dataJeu.level.persoPrincipal.force.x = 0;

                }
                else
                {
                    dataJeu.level.persoPrincipal.vitesse.x-= DT*signe(dataJeu.level.persoPrincipal.vitesse.x);
                    dataJeu.level.persoPrincipal.force.x -= DT*signe(dataJeu.level.persoPrincipal.force.x);
                }
             }
             else
             {
                dataJeu.level.persoPrincipal.force.x = TILEHAUTEUR*3/32;
             }

        }
        else if(isKeyPressed(SDLK_LEFT))
        {
            if(dataJeu.level.persoPrincipal.vitesse.x > 0)
            {
                if(signe(dataJeu.level.persoPrincipal.vitesse.x- DT*signe(dataJeu.level.persoPrincipal.vitesse.x))!=signe(dataJeu.level.persoPrincipal.vitesse.x))
                {
                    dataJeu.level.persoPrincipal.vitesse.x = 0;
                    dataJeu.level.persoPrincipal.force.x = 0;

                }
                else
                {
                    dataJeu.level.persoPrincipal.vitesse.x-= DT*signe(dataJeu.level.persoPrincipal.vitesse.x);
                    dataJeu.level.persoPrincipal.force.x -= DT*signe(dataJeu.level.persoPrincipal.force.x);
                }
             }
             else
             {
                dataJeu.level.persoPrincipal.force.x = -TILEHAUTEUR*3/32;
             }

        }
        else
        {
            //std::cout<<dataJeu.level.persoPrincipal.vitesse.x<<std::endl;
            if(signe(dataJeu.level.persoPrincipal.vitesse.x- DT*signe(dataJeu.level.persoPrincipal.vitesse.x))!=signe(dataJeu.level.persoPrincipal.vitesse.x))
            {
                dataJeu.level.persoPrincipal.vitesse.x = 0;
                dataJeu.level.persoPrincipal.force.x = 0;

            }
            else
            {
                dataJeu.level.persoPrincipal.vitesse.x-= DT*signe(dataJeu.level.persoPrincipal.vitesse.x);
                dataJeu.level.persoPrincipal.force.x -= DT*signe(dataJeu.level.persoPrincipal.force.x);
            }
        }



        if(isKeyPressed(SDLK_UP))
        {
            int tileCY = (dataJeu.level.persoPrincipal.position.y+dataJeu.level.persoPrincipal.hauteur/2)/TILEHAUTEUR;
            int tileCX = (dataJeu.level.persoPrincipal.position.x+dataJeu.level.persoPrincipal.largeur/2)/TILELARGEUR;
            if(tileCY<dataJeu.level.nombreTileY&&tileCY>=0&&tileCX<dataJeu.level.nombreTileX&&tileCX>=0)
            {
                if(dataJeu.level.level[tileCY][tileCX]<=-2&&dataJeu.level.level[tileCY][tileCX]>-7)
                {
                    afficheLevel(dataImage, dataJeu, abs(dataJeu.level.level[tileCY][tileCX])-1);
                    int retour = fonctionPrincipalLevel(abs(dataJeu.level.level[tileCY][tileCX])-1, dataJeu, dataImage, dataJeu.nb_vie, dataJeu.nb_pieces, dataJeu.level.persoPrincipal.largeur, dataJeu.level.persoPrincipal.hauteur, dataJeu.level.persoPrincipal.masse, dataJeu.score, checkPoint);
                    if(retour==1)
                    {
                        levelWin++;
                        for(int i = -1; i<=1; i++)
                        {
                            for(int j = -1; j<=1; j++)
                            {
                                dataJeu.level.level[tileCY+i][tileCX+j] = (dataJeu.level.level[tileCY+i][tileCX+j]<-1 ? -7: dataJeu.level.level[tileCY+i][tileCX+j]);
                            }
                        }
                        if(levelWin==5)
                        {
                            statPartie = 1;
                        }


                    }
                    else if(retour==-2)
                    {
                        statPartie =retour;
                    }
                    else if(dataJeu.nb_vie==0)
                    {
                        statPartie=-1;
                    }
                    else
                    {
                        statPartie=0;
                    }
                }
            }
            if(dataJeu.level.persoPrincipal.sol == true)
            {
                dataJeu.level.persoPrincipal.vitesse.y=TILEHAUTEUR*25/32;
            }
            else if(dataJeu.level.persoPrincipal.vitesse.y<0&&((dataJeu.level.persoPrincipal.vitesse.x>=0&&pointCollision(make_Vec2(dataJeu.level.persoPrincipal.position.x+dataJeu.level.persoPrincipal.largeur+1, dataJeu.level.persoPrincipal.position.y), dataJeu))||(dataJeu.level.persoPrincipal.vitesse.x<0&&pointCollision(make_Vec2(dataJeu.level.persoPrincipal.position.x-1, dataJeu.level.persoPrincipal.position.y), dataJeu))))
            {
                dataJeu.level.persoPrincipal.vitesse.y=TILEHAUTEUR*25/32;
                dataJeu.level.persoPrincipal.force.x *= -1;
                dataJeu.level.persoPrincipal.vitesse.x = signe(dataJeu.level.persoPrincipal.force.x)*20;
            }
        }

        drawSelect(dataImage, dataJeu);
        UpdateScroll(dataJeu);
        persoUpdatePV(dataJeu);


        stop = winDisplay();
    }
    if(statPartie==1)
    {
        afficheJeuTermine(dataImage,dataJeu.score);
        return true;
    }
    else if(statPartie==-1)
    {
        afficheGameOver(dataImage, dataJeu.score);
        return true;
    }
    return false;
}


int main(int, char** )
{
    struct DataImages dataImage;
    struct Jeu dataJeu;

    winInit("Mario plateforme", DIMWX, DIMWY);


    setKeyRepeatMode(true);
    initImage(dataImage);
    bool recommencer = true, stop = false;
    while(!stop && recommencer)
    {
        afficheEcranDebut(dataImage);
        recommencer = selectionLevel(dataJeu, dataImage);
        stop = winDisplay();
    }
    winQuit();

    return 0;
}
