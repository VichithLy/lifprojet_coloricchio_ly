/*
Mini-projet LIFAMI

CORCORAL Thomas
P1802691
Groupe : C / Séquence 2
Rapporteur de projet : PARIS Axel

2019
*/

#include <iostream>
#include <Grapic.h>
#include <math.h>

using namespace grapic;
using namespace std;

const float pi = 3.14159265359;

const int DIMW = 500;                   // Taille de la fenêtre
const int NMAX = 200;
const float dt = 0.005f;
const float G = 9.81f;                   // Gravité sur la Terre
const float Gl = 1.61f;                  // Gravité sur la lune
const float  FRICTION = 0.6f;           // valeur d'absorbtion de la vitesse en cas de collision: 1=la particule repart aussi vite, 0=elle s'arrete
const float FRICTION_MOON = 0.99f;      // valeur d'absorption de la vitesse sur la lune
const float RADIUS = 5;                 // rayon des cercles des particules
const float FORCE_SEAU = 2.2f;          // Valeur du rebond sur le seau
const float VIEMAX = 500;               // Vie max du Robot.

//////////////////////////////// Structures ///////////////////////////

struct Vec2
{
	float x, y;
};

struct Particle
{
	Vec2 p;         // position
	Vec2 v;         // vitesse
	Vec2 f;         // force
	float m;        // masse
	bool etat;      // actif ou inactif
};

struct Spring
{
    int i1;         // indentifiant de la particule 1=son indice dans le tablea de particule
    int i2;         // indentifiant de la particule 2=son indice dans le tablea de particule
    float l;        // longueur au report du ressort
    float k;        // raideur du ressort
};

struct Personnage
{
    Image Im;       // Image associée au personnage
    Vec2 coord;     // Un personnage est associé à un point qui est donc un Vec2
};

struct robot
{
    Image Im;       // Image du robot

    Vec2 coord;     // Coordonnés du robot
    Vec2 v;         // Vitesse

    int vie;        // Vie restante
};

struct mini_jeu1
{
    Vec2 Seau[NMAX];            // Position du Sceau
  	Particle part[NMAX];        // tableau de particules
	int np;                     // nombre de particules
	int score;                  // nombre de particules attrapés
};

struct mini_jeu2
{
    Personnage Perso;       // Personnage principal
    int Score;              // Score du joueur (particules restantes)
    Particle part[NMAX];    // Tableau de particules
    int np;                 // Nombre de particules
};

struct DirectionMj3
{
    Image dir[NMAX];        // Tableau avec les images pour la droite et la gauche
    int direction;          // Valeur à 0 ou 1  en fonction de la droite ou la gauche
};

struct aste     // Structure d'un astéroide
{
    Particle part[NMAX];        // tableau de particules
	int np;                     // nombre de particules

	Spring spr[NMAX];           // tableau de ressort (=spring)
	int ns;                     // nombre de spring (ressort)

	Vec2 centre;                // centre de l'astéroide
};

struct mini_jeu3
{
    Vec2 Perso;             // Position du personnage
    int Score;              // Score
    DirectionMj3 direct;    // Appel de la structure DirectionMj3 pour mettre la bonne image au personnage

    aste ast[NMAX];         // astéroides
    int na;                 // nombre astéroides

	float dt;
};

struct arme     // Structure définissant une arme
{
    float delai;        // Temps de rechargement
    int degat;          // Dégat infligés par tir
    int conso_part;     // Consommation de particules par tir
    float travel_time;  // Vitesse de la balle
    Image Im_arme;      // Image associée à l'arme
};

struct mini_jeu4
{
    robot Robot;              // Robot à battre
    Personnage Viseur;        // Viseur de l'arme

    Particle Balle[NMAX];     // Balles

    int nb;                   // Nombre de balles
    int Score;                // Score --> Nombre de particules restantes

    int choix_arme;           // Choix arme parmis les 5
    arme Arme[NMAX];          // Tableau des armes

    float dernier_Tir;        // heure du dernier tir
};

struct World
{
    mini_jeu1 mj1;              // Chaque mini-jeu à une structure associée

    mini_jeu2 mj2;

    mini_jeu3 mj3;

    mini_jeu4 mj4;

	int AvancePres;             // Etape de la presentation
	Image Im_pres[NMAX];        // Présentation du projet

	int Step;                   // Etape du voyage
	Image Im_fond[NMAX];        // Images de fond

	Image Im_transition[NMAX];     // Images de transition

	float dt;                   // le pas de temps

	int TimeStart;              // temps début mini jeu
};

/////////////////////////////////////////////////////////////////////

//////////////////////////////// Operator ///////////////////////////

Vec2 operator+(const Vec2& a, const Vec2& b)
{
	Vec2 r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	return r;
}

Vec2 operator-(const Vec2& a, const Vec2& b)
{
	Vec2 r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	return r;
}

Vec2 operator-(Vec2 &a)
{
    a.x = -a.x;
    a.y = -a.y;
    return a;
}

Vec2 operator+=(Vec2& a, const Vec2& b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

Vec2 operator*(float a, const Vec2& b)
{
	Vec2 r;
	r.x = a * b.x;
	r.y = a * b.y;
	return r;
}


/////////////////////////////////////////////////////////////////////

//////////////////////////////// Outils /////////////////////////////

Vec2 make_vec2(float x, float y)
{
    Vec2 r;
    r.x = x;
    r.y = y;
    return r;
}

float dista(Vec2 p1, Vec2 p2)
{
    float dist;
    dist = sqrt(pow(p2.y-p1.y,2) + pow(p2.x-p1.x ,2));
    return dist;
}

float norm(const Vec2 v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

float normalize(Vec2& v)
{
    float n = norm(v);
	v.x /= n;
	v.y /= n;
	return n;
}

void updateParticle(mini_jeu3 &mj3, float dt)   // Mise à jour des particules du mini-jeu n°3
{
	int i, j;
	for (j = 0; j < mj3.na ; j++)   // On parcourt la liste des astéroides
	{
        for (i = 0; i < mj3.ast[j].np; ++i)     // On parcourt la liste des particules de chaque astéroides
        {
            if (mj3.ast[j].part[i].m>0)
            {
                mj3.ast[j].part[i].v = mj3.ast[j].part[i].v + (dt/mj3.ast[j].part[i].m)*mj3.ast[j].part[i].f;
                mj3.ast[j].part[i].p = mj3.ast[j].part[i].p + dt*mj3.ast[j].part[i].v;
                mj3.ast[j].part[i].f.x = 0;
                mj3.ast[j].part[i].f.y = 0;
            }
        }
	}
}

void collisionPartSeau(Particle &p, World &w)
{
    // test si la particule est dans le seau
    if(p.p.x >= w.mj1.Seau[2].x && p.p.x <= w.mj1.Seau[3].x && p.p.y <= w.mj1.Seau[2].y && p.p.y >= w.mj1.Seau[0].y)
    {
        //test si la particule arrive de la gauche
        if(p.p.x < w.mj1.Seau[2].x+18)
        {
            p.p.x = p.p.x - (p.p.x - w.mj1.Seau[2].x)-1;
            p.v.x = -p.v.x * FORCE_SEAU;
        }

        //test si la particule arrive de la droite
        if(p.p.x > w.mj1.Seau[3].x-18)
        {
            p.p.x = p.p.x + (w.mj1.Seau[3].x - p.p.x)+1;
            p.v.x = -p.v.x * FORCE_SEAU;
        }

        //test si la particule arrive du bas
        if(p.p.y < w.mj1.Seau[0].y+18)
        {
            p.p.y = p.p.y - (p.p.y - w.mj1.Seau[0].y)-1;
            p.v.y = -p.v.y * FORCE_SEAU;
        }
        p.v = FRICTION * p.v;
    }
}

void PartUpdatePV(Particle &p)
{
    if(p.p.x < 0)
    {
        p.v.x = -p.v.x;
        p.p.x = 0;
        p.v = FRICTION * p.v;
    }
    if(p.p.x > DIMW-1)
    {
        p.v.x = -p.v.x;
        p.p.x = DIMW-2;
        p.v = FRICTION*p.v;
    }
    if(p.p.y < 0)
    {
        p.v.y = -p.v.y;
        p.p.y = 0;
        p.v = FRICTION*p.v;
    }
    if(p.p.y > DIMW-1)
    {
        p.v.y = -p.v.y;
        p.p.y = DIMW-2;
        p.v = FRICTION*p.v;
    }
    p.p.x = p.p.x + p.v.x * dt;
    p.p.y = p.p.y + p.v.y * dt;
    p.v.x = p.v.x + p.f.x * dt;
    p.v.y = p.v.y + p.f.y * dt;
}

void computeParticleForceGravityMoon(mini_jeu3 &mj3)
{
	int i,j;
	for(j = 0; j < mj3.na; j++)
    {
        for (i = 0; i < mj3.ast[j].np; ++i)
        {
            mj3.ast[j].part[i].f.y = -mj3.ast[j].part[i].m * Gl;
        }
    }
}

float rad_to_deg(float theta)
{
    return (180.f * theta/pi);
}

float deg_to_rad(float theta)
{
    return (theta*pi /180.f);
}

/////////////////////////////////////////////////////////////////////

////////////////////////////// Particules ///////////////////////////

void PartInit(Particle &p)
{
    p.m = 1.0;
    p.p.x = frand(DIMW/2-10,DIMW/2+10);
    p.p.y = frand(DIMW/2-10,DIMW/2+10);
    p.v.x = frand(-80,80);
    p.v.y = frand(-80,80);
}

void ForceInit(Vec2 &f)
{
    f.x = 0;
    f.y = -G;
}

void PartAddForce(Particle &p, Vec2 force)
{
    p.f.x = force.x;
    p.f.y = force.y;
}

////////////////////////////////////////////////////////////////////////

////////////////////////////////// Init ////////////////////////////////

void init(World &w)
{
    w.Step = 0;
    w.AvancePres = 0;
    w.mj1.np = 0;
    w.mj3.dt = 0.01f;

    // Initialisation des images

    w.Im_pres[0] = image("/data/LIFAMI_mini-projet/Pres1.png");
    w.Im_pres[1] = image("/data/LIFAMI_mini-projet/Pres2.png");
    w.Im_fond[1] = image("/data/LIFAMI_mini-projet/fond0.jpg");
    w.Im_fond[2] = image("/data/LIFAMI_mini-projet/fond1.png");
    w.Im_fond[3] = image("/data/LIFAMI_mini-projet/fond2.jpg");
    w.Im_fond[4] = image("/data/LIFAMI_mini-projet/fond3.png");
    w.Im_fond[5] = image("/data/LIFAMI_mini-projet/fond4.jpg");
    w.Im_fond[6] = image("/data/LIFAMI_mini-projet/fond5.png");
    w.Im_fond[7] = image("/data/LIFAMI_mini-projet/fond6.png");
    w.Im_fond[8] = image("/data/LIFAMI_mini-projet/fond7.png");
    w.mj2.Perso.Im = image("/data/LIFAMI_mini-projet/perso.png");
    w.mj3.direct.dir[0] = image("/data/LIFAMI_mini-projet/astronaute_gauche.png");
    w.mj3.direct.dir[1] = image("/data/LIFAMI_mini-projet/astronaute_droite.png");
    w.Im_transition[0] = image("/data/LIFAMI_mini-projet/transition0.png");
    w.Im_transition[1] = image("/data/LIFAMI_mini-projet/transition1.png");
    w.mj4.Robot.Im = image("/data/LIFAMI_mini-projet/robot.png");
    w.mj4.Viseur.Im = image("/data/LIFAMI_mini-projet/viseur.png");
}

void initSeau(World &w)
{
    w.mj1.Seau[0] = make_vec2(DIMW/2 - 45 , 15);
    w.mj1.Seau[1] = make_vec2(DIMW/2 + 45 , 15);
    w.mj1.Seau[2] = make_vec2(DIMW/2 - 45 , 75);
    w.mj1.Seau[3] = make_vec2(DIMW/2 + 45 , 75);
}

void init_minijeu1(World &w)
{
    initSeau(w);
}

void init_Perso(World &w)
{

    // Initialisation des coordonnés du personnage pour le 2eme mini-jeu

    w.mj2.Perso.coord.x = DIMW/2-25;
    w.mj2.Perso.coord.y = 160;
}

void init_part_mj2(World &w)
{
    int i;
    for(i=0; i < w.mj1.score ; i++)
    {
        w.mj2.np++;
        w.mj2.part[i].etat = true;
        w.mj2.part[i].m = 1;
        w.mj2.part[i].p.x = rand()%(DIMW-325)+160;
        w.mj2.part[i].p.y = rand()%(DIMW-245)+130;
        w.mj2.part[i].v = {0,0};
        w.mj2.part[i].f = {0,0};
    }
}

void init_minijeu2(World &w)
{
    init_Perso(w);
    init_part_mj2(w);
    w.mj2.Score = w.mj1.score;
}

void init_minijeu3(World &w)
{
    w.TimeStart = elapsedTime();
    w.mj3.Perso.x = DIMW/2;
    w.mj3.Perso.y = 40;
    w.mj3.Score = w.mj2.Score;
    w.mj3.direct.direction = 0;
    w.mj3.na = 0;
}

void init_armes(World &w)
{
    //Lance roquette
    w.mj4.Arme[0].conso_part = 3;
    w.mj4.Arme[0].degat = 150;
    w.mj4.Arme[0].delai = 6;
    w.mj4.Arme[0].travel_time = 50;
    w.mj4.Arme[0].Im_arme = image("/data/LIFAMI_mini-projet/lanceroquette.png");

    //Sniper
    w.mj4.Arme[1].conso_part = 2;
    w.mj4.Arme[1].degat = 100;
    w.mj4.Arme[1].delai = 4;
    w.mj4.Arme[1].travel_time = 170;
    w.mj4.Arme[1].Im_arme = image("/data/LIFAMI_mini-projet/sniper.jpg");

    //Pistolet
    w.mj4.Arme[2].conso_part = 1;
    w.mj4.Arme[2].degat = 70;
    w.mj4.Arme[2].delai = 3;
    w.mj4.Arme[2].travel_time = 120;
    w.mj4.Arme[2].Im_arme = image("/data/LIFAMI_mini-projet/deagle.jpg");

    //Sulfateuse
    w.mj4.Arme[3].conso_part = 2;
    w.mj4.Arme[3].degat = 30;
    w.mj4.Arme[3].delai = 0.45;
    w.mj4.Arme[3].travel_time = 600;
    w.mj4.Arme[3].Im_arme = image("/data/LIFAMI_mini-projet/sulfateuse.jpg");

    //Pistolet silencieux
    w.mj4.Arme[4].conso_part = 1;
    w.mj4.Arme[4].degat = 50;
    w.mj4.Arme[4].delai = 2.5;
    w.mj4.Arme[4].travel_time = 140;
    w.mj4.Arme[4].Im_arme = image("/data/LIFAMI_mini-projet/pistoletsil.png");
}

void init_minijeu4(World &w)
{
    w.mj4.Score = w.mj3.Score;
    w.mj4.Robot.coord.x = DIMW/2;
    w.mj4.Robot.coord.y = 360;
    w.mj4.Robot.vie = VIEMAX;
    w.mj4.Robot.v.y = 0;
    w.mj4.Robot.v.x = 10;
    w.mj4.Viseur.coord.x = DIMW/2;
    w.mj4.Viseur.coord.y = 440;
    w.mj4.nb = 0;
    init_armes(w);
}

////////////////////////////////////////////////////////////////////////

///////////////////////////// Presentation /////////////////////////////

void Presentation(World &w)
{
    int x, y;
    mousePos(x,y);
    if(isMousePressed(SDL_BUTTON_LEFT) && x > 400 && y < 75)
    {
        // Lancement du premier mini jeu.

        w.Step = 1;
        init_minijeu1(w);
        w.TimeStart = elapsedTime();
    }
    if(elapsedTime() < 20)
    {
        image_draw(w.Im_pres[0] , 0 , 0 , DIMW-1 , DIMW-1 );         // affiche la première image de présentations.
    }
    if(20 <= elapsedTime() && elapsedTime() < 40)
    {
        image_draw(w.Im_pres[1] , 0 , 0 , DIMW-1 , DIMW-1 );         // affiche la seconde image.
    }
    if(elapsedTime() >= 40)
    {
        // Lancement du premier mini jeu.

        w.Step = 1;
        init_minijeu1(w);
        w.TimeStart = elapsedTime();
    }
}

////////////////////////////////////////////////////////////////////////

///////////////////////////// Transition ///////////////////////////////

void transition1(World &w)
{
    image_draw(w.Im_transition[0], 0 , 0 , DIMW-1 , DIMW-1 );
    int x,y;
    mousePos(x,y);
    if(isMousePressed(SDL_BUTTON_LEFT) && y > 146 && y < 183 && x > 232 && x < 269)
    {
        // Lancement du mini jeu.
        w.Step++;
    }
}

void transition2(World &w)
{
    int x,y;
    image_draw(w.Im_transition[1], 0 , 0 , DIMW-1 , DIMW-1 );
    mousePos(x,y);

    // Délimitation des zones pour le choix des armes

    if(isMousePressed(SDL_BUTTON_LEFT))
    {
        if( x <= 242 && y > 160 )
        {
            w.mj4.choix_arme = 0;
        }
        if( x > 242 && y > 160 )
        {
            w.mj4.choix_arme = 1;
        }
        if( x <= 111 && y <= 160 )
        {
            w.mj4.choix_arme = 2;
        }
        if( x > 111 && x < 337 && y <= 160 )
        {
            w.mj4.choix_arme = 3;
        }
        if( x >= 337 && y <= 160 )
        {
            w.mj4.choix_arme = 4;
        }
        w.Step++;
    }
}

void fin(World &w)
{
    // Si le joueur perd au cours d'un autre mini jeu que le dernier la valeur de w.Step sera 8.

    if(w.Step == 7)
    {

        // On vérifie si le robot a encore de la vie ou non.

        if(w.mj4.Robot.vie <= 0)
        {
            if(w.TimeStart > elapsedTime() - 1)
            {
                image_draw(w.Im_fond[5], 0 , 0 , DIMW-1 , DIMW-1 );
            }
            else
            {
                image_draw(w.Im_fond[7], 0 , 0 , DIMW-1 , DIMW-1 );
                print(150, 20, "VOTRE SCORE : ");
                print(300, 20, w.mj4.Score);
            }
        }
        else
        {
            if(w.TimeStart > elapsedTime() - 1)
            {
                image_draw(w.Im_fond[6], 0 , 0 , DIMW-1 , DIMW-1 );
            }
            else
            {
                image_draw(w.Im_fond[8], 0 , 0 , DIMW-1 , DIMW-1 );
            }
        }
    }
    else
    {
        if(w.TimeStart > elapsedTime() - 1)
        {
            image_draw(w.Im_fond[6], 0 , 0 , DIMW-1 , DIMW-1 );
        }
        else
        {
            image_draw(w.Im_fond[8], 0 , 0 , DIMW-1 , DIMW-1 );
        }
    }
}

////////////////////////////////////////////////////////////////////////

////////////////////////////////// Draw ////////////////////////////////

void drawPart(Particle p)
{
    color(255,0,0);
    circleFill(p.p.x , p.p.y , 3);
}

void drawSeau(Vec2 v1, Vec2 v2, Vec2 v3, Vec2 v4)
{
    color(0,0,156);
    triangleFill(v1.x , v1.y , v3.x , v3.y , v4.x , v4.y);  // remplir le seau en faisant 2 triangles
    triangleFill(v1.x , v1.y , v2.x , v2.y , v4.x , v4.y);  // On aurait également pu faire un rectangle mais je voulais essayer cette technique.
    color(0,0,0);

    // Dessin des parois du seau

    line(v1.x , v1.y , v2.x , v2.y);
    line(v2.x , v2.y , v4.x , v4.y);
    line(v3.x , v3.y , v1.x , v1.y);
}

void drawMj1(World &w)
{
    int i;
    image_draw(w.Im_fond[1], 0 , 0 , DIMW-1 , DIMW-1 );     // Image de fond
    drawSeau(w.mj1.Seau[0], w.mj1.Seau[1], w.mj1.Seau[2], w.mj1.Seau[3]);       // Affichage du seau

    // Affichage des particules

    for(i=0; i< w.mj1.np ; i++)
    {
        if(w.mj1.part[i].etat)
        {
            drawPart(w.mj1.part[i]);
        }
    }

    // Affichage du score

    print(DIMW-107, DIMW-50, "SCORE : ");
    print(DIMW-30, DIMW-50, w.mj1.score);
}

void drawMj2(World &w)
{
    int i;
    image_draw(w.Im_fond[2], 0 , 0 , DIMW-1 , DIMW-1 );     // Image de fond
    image_draw(w.mj2.Perso.Im, w.mj2.Perso.coord.x , w.mj2.Perso.coord.y ); // Image du personnage

    // Affiche toutes les particules

    for(i=0; i< w.mj2.np ; i++)
    {
        if(w.mj2.part[i].etat)
        {
            drawPart(w.mj2.part[i]);
        }
    }

    // Et enfin l'affichage du score

    print(DIMW-107, DIMW-50, "SCORE : ");
    print(DIMW-30, DIMW-50, w.mj2.Score);
    color(255,0,0);
}

void drawMj3(World &w)
{
    int i, j;
    image_draw(w.Im_fond[3], 0 , 0 , DIMW-1 , DIMW-1 );     // fond d'écran
    image_draw(w.mj3.direct.dir[w.mj3.direct.direction], w.mj3.Perso.x, w.mj3.Perso.y); // image du personnage (droite ou gauche)
	color(239, 239, 239);

	// affiche les astéroïdes

	for(j = 0; j < w.mj3.na; j++)
    {
        for (i = 0; i < w.mj3.ast[j].np; ++i)
        {
            circleFill( w.mj3.ast[j].part[i].p.x, w.mj3.ast[j].part[i].p.y, 3);
        }
        int i1, i2;
        for (i = 0; i < w.mj3.ast[j].ns; ++i)
        {
            i1 = w.mj3.ast[j].spr[i].i1;
            i2 = w.mj3.ast[j].spr[i].i2;
            line( w.mj3.ast[j].part[i1].p.x, w.mj3.ast[j].part[i1].p.y, w.mj3.ast[j].part[i2].p.x, w.mj3.ast[j].part[i2].p.y);
        }
    }

    // Et enfin un print pour le score

    print(DIMW-107, DIMW-50, w.mj3.Score);
}

void drawMj4(World &w)
{
    int i;
    image_draw(w.Im_fond[4], 0 , 0 , DIMW-1 , DIMW-1 );     // image de fond
    image_draw(w.mj4.Arme[w.mj4.choix_arme].Im_arme, 0 , 0 , 80 , 80 );     // Affiche l'arme choisi
    image_draw(w.mj4.Robot.Im , w.mj4.Robot.coord.x, w.mj4.Robot.coord.y , 70 , 130 );      // affiche le robot
    image_draw(w.mj4.Viseur.Im , w.mj4.Viseur.coord.x-29 , w.mj4.Viseur.coord.y-29 , 60 , 60 );     // affiche le viseur
    color(0,0,255);

    // Dessine les balles

    for(i=0; i<w.mj4.nb ; i++)
    {
        if(w.mj4.Balle[i].etat)
        {
            circleFill(w.mj4.Balle[i].p.x, w.mj4.Balle[i].p.y, w.mj4.Arme[w.mj4.choix_arme].conso_part*3);
        }
    }

    //Affiche le nombre de tirs restants

    color(255,255,255);
    fontSize(14);
    print(DIMW-90, 25, "Il vous reste : ");
    int reste_tirs = w.mj4.Score/w.mj4.Arme[w.mj4.choix_arme].conso_part;
    print(DIMW-90, 5, reste_tirs);
    print(DIMW-70, 5, "Tirs");

    // Affichage de la barre de vie en vert

    color(0,255,0);
    rectangleFill(100 , 5 , (w.mj4.Robot.vie/VIEMAX)*280+100 , 15 );
}

////////////////////////////////////////////////////////////////////////

////////////////////////////// Mini-jeux ///////////////////////////////

////////////////////////////// Mini-jeu 1 //////////////////////////////

Particle putPartMj1()
{
    Particle P;
    P.p.x = rand()%(DIMW-200) + 100; // position en x entre 100 et 400.
    P.p.y = DIMW-4;
    P.v.x = 0;                       // Pas de vitesse au début
    P.v.y = 0;
    P.f.x = frand(-4, 4);            //Force latérale entre -4 et 4
    P.f.y = -G;                      // Effet de la gravité terrestre
    P.m = 1;                         // masse à 1 par défaut
    P.etat = true;                   // Toutes les particules sont activés de base
    return P;
}

void updateMj1(World &w)
{
    int i;

    // Déplacements latéraux

    if(isKeyPressed(SDLK_LEFT))
    {
        if(w.mj1.Seau[2].x-1 > 0)                      // Bloque le seau à la bordure gauche
        {
            w.mj1.Seau[0].x = w.mj1.Seau[0].x - 1;
            w.mj1.Seau[1].x = w.mj1.Seau[1].x - 1;
            w.mj1.Seau[2].x = w.mj1.Seau[2].x - 1;
            w.mj1.Seau[3].x = w.mj1.Seau[3].x - 1;
        }
    }
    if(isKeyPressed(SDLK_RIGHT))
    {
        if(w.mj1.Seau[3].x+1 < DIMW)                   // Bloque le seau à la bordure droite
        {
            w.mj1.Seau[0].x = w.mj1.Seau[0].x + 1;
            w.mj1.Seau[1].x = w.mj1.Seau[1].x + 1;
            w.mj1.Seau[2].x = w.mj1.Seau[2].x + 1;
            w.mj1.Seau[3].x = w.mj1.Seau[3].x + 1;
        }
    }

    // Ajout de particules

    int time = elapsedTime() - w.TimeStart;

    if(w.mj1.np < time && w.mj1.np < 50) // fait apparaitre une particule par seconde avec un maximum de 50 particules
    {
        w.mj1.np++;
        w.mj1.part[w.mj1.np] = putPartMj1();
    }

    // Vérifications

    for(i=0; i < w.mj1.np ; i++)
    {

        // Si la particule est dans le seau

        if(w.mj1.Seau[2].y-2 < w.mj1.part[i].p.y && w.mj1.Seau[2].y+2 > w.mj1.part[i].p.y && w.mj1.Seau[2].x < w.mj1.part[i].p.x && w.mj1.Seau[3].x > w.mj1.part[i].p.x && w.mj1.part[i].etat)
        {
            w.mj1.score++;
            w.mj1.part[i].etat = false;
        }

        // vérification que la particule est toujours active

        if(w.mj1.part[i].etat)
        {
            collisionPartSeau(w.mj1.part[i],w);
            PartUpdatePV(w.mj1.part[i]);
        }
    }

    // Si le temps est fini (54 secondes) on passe au mini-jeu suivant

    if(time == 54)
    {
        if(w.mj1.score == 0)
        {
            w.Step = 8;
        }
        else
        {
            w.Step++;
            w.TimeStart = elapsedTime();
            init_minijeu2(w);
        }
    }
}

///////////////////////////// Mini-jeu 2 ///////////////////////////////

void updateMj2(World &w)
{
    int i,x,y;
    mousePos(x,y);

    // On bloque le personnage dans la fusée

    if(x <= 180 && y < DIMW-135 && y > 150)
    {
        w.mj2.Perso.coord.y = y-25;
        w.mj2.Perso.coord.x = 181-25;
    }
    if(x >= DIMW-190 && y < DIMW-135 && y > 150)
    {
        w.mj2.Perso.coord.y = y-25;
        w.mj2.Perso.coord.x = DIMW-191-25;
    }
    if(y <= 150 && x > 180 && x < DIMW-190)
    {
        w.mj2.Perso.coord.x = x-25;
        w.mj2.Perso.coord.y = 151-25;
    }
    if(y >= DIMW-135 &&  x > 180 && x < DIMW-190)
    {
        w.mj2.Perso.coord.x = x-25;
        w.mj2.Perso.coord.y = DIMW-136-25;
    }
    if(x > 180 && x < DIMW-190 && y < DIMW-135 && y > 150)
    {
        w.mj2.Perso.coord.x = x-25;
        w.mj2.Perso.coord.y = y-25;
    }

    // Vérifications des contacts entre le joueur et les particules

    for(i=0; i<w.mj2.np ; i++)
    {
        if(w.mj2.part[i].etat)
        {
            PartUpdatePV(w.mj2.part[i]);
            if(w.mj2.part[i].p.x < 125)
            {
                w.mj2.part[i].etat = false;
                w.mj2.Score -= 1;
            }
            if(w.mj2.part[i].p.x > w.mj2.Perso.coord.x+5 && w.mj2.part[i].p.x < w.mj2.Perso.coord.x+45 && w.mj2.part[i].p.y > w.mj2.Perso.coord.y+5 && w.mj2.part[i].p.y < w.mj2.Perso.coord.y+45)
            {
                w.mj2.part[i].v.x = -150;
            }
        }
    }

    // Si le joueur à atteint la manette

    if(w.mj2.Perso.coord.x > 200  && w.mj2.Perso.coord.x < 230 && w.mj2.Perso.coord.y > 338 && w.mj2.Perso.coord.y < 340 )
    {
        delay(200);
        init_minijeu3(w);
        w.Step++;
    }
    if(w.mj2.Score <= 0)        // Cas si le joueur n'a plus de particules.
    {
        w.Step = 8;
    }
}

///////////////////////////// Mini-jeu 3 ///////////////////////////////

int addPart(aste &as, float x, float y, float m=1) // Initialisation basique d'une particule d'astéroïde
{
    int i = as.np;

    as.part[i].m = m;

    as.part[i].p.x = x;
    as.part[i].p.y = y;

    as.part[i].v.x = 10;
    as.part[i].v.y = 0;

    as.np++;
    return as.np-1;
}

void addSpring(aste & a, int i1, int i2)    // Ajout d'un ressort entre les particules i1 et i2
{
    int i = a.ns;

    a.spr[ i ].i1 = i1;
    a.spr[ i ].i2 = i2;
    a.spr[ i ].k = 500;
    a.spr[ i ].l =  norm( a.part[i1].p - a.part[i2].p );

    a.ns++;
}

void addAsteroide(mini_jeu3 &mj3)   // Création d'un astéroïde
{
    int aleatoire;
    aleatoire = rand()%400 -200;
    aste as = mj3.ast[mj3.na-1];

    // création des particules

    int a = addPart( as, aleatoire + DIMW/2-20 , DIMW-30 );
    int b = addPart( as, aleatoire + DIMW/2 , DIMW-20);
    int c = addPart( as, aleatoire + DIMW/2+20 , DIMW-30);

    int d = addPart( as, aleatoire + DIMW/2+20 , DIMW-50);
    int e = addPart( as, aleatoire + DIMW/2 , DIMW-60);
    int f = addPart( as, aleatoire + DIMW/2-20 , DIMW-50);

    // On relie les particules

    addSpring(as, a, b);
    addSpring(as, b, c);
    addSpring(as, c, d);
    addSpring(as, d, e);
    addSpring(as, e, f);
    addSpring(as, f, a);
    addSpring(as, a, d);
    addSpring(as, b, e);
    addSpring(as, c, f);

    mj3.ast[mj3.na-1] = as;     // On ajoute l'astéroïde au tableau d'astéroide de la structure du mini jeu.
}

void collisionLune(mini_jeu3 &mj3) // Gère les collisions de l'astéroïde avec les bordures sur la lune.
{
	int i, j, k;
	for (j = 0; j < mj3.na ; j++)
    {
        for (i = 0; i < mj3.ast[j].np; ++i)
        {
            if (mj3.ast[j].part[i].p.x < 0)
            {
                for(k = 0 ; k < mj3.ast[j].np ; k++)
                {
                    mj3.ast[j].part[k].p.x = mj3.ast[j].part[k].p.x + 1;
                    mj3.ast[j].part[k].v.x = -mj3.ast[j].part[k].v.x;
                    mj3.ast[j].part[k].v = FRICTION_MOON * mj3.ast[j].part[k].v;
                }
            }

            if (mj3.ast[j].part[i].p.y < 0)
            {
                for(k = 0 ; k < mj3.ast[j].np ; k++)
                {
                    mj3.ast[j].part[k].p.y = mj3.ast[j].part[k].p.y + 1;
                    mj3.ast[j].part[k].v.y = -mj3.ast[j].part[k].v.y;
                    mj3.ast[j].part[k].v = FRICTION_MOON * mj3.ast[j].part[k].v;
                }
            }

            if (mj3.ast[j].part[i].p.x >= DIMW)
            {
                for(k = 0 ; k < mj3.ast[j].np ; k++)
                {
                    mj3.ast[j].part[k].p.x = mj3.ast[j].part[k].p.x - 1;
                    mj3.ast[j].part[k].v.x = -mj3.ast[j].part[k].v.x;
                    mj3.ast[j].part[k].v = FRICTION_MOON * mj3.ast[j].part[k].v;
                }
            }

            if (mj3.ast[j].part[i].p.y >= DIMW)
            {
                for(k = 0 ; k < mj3.ast[j].np ; k++)
                {
                    mj3.ast[j].part[k].p.y = mj3.ast[j].part[k].p.y - 1;
                    mj3.ast[j].part[k].v.y = -mj3.ast[j].part[k].v.y;
                    mj3.ast[j].part[k].v = FRICTION_MOON * mj3.ast[j].part[k].v;
                }
            }
        }
    }
}

void collisionAstronaute(mini_jeu3 &mj3)
{
	int i, j, k, diff;
	for (j = 0; j < mj3.na ; j++)
    {
        for (i = 0; i < mj3.ast[j].np; ++i)
        {

            // Vérification que chaque particule de chaque astéroïde n'est pas en contact avec l'astronaute.

            if (mj3.ast[j].part[i].p.x > mj3.Perso.x && mj3.ast[j].part[i].p.x < mj3.Perso.x + 129 && mj3.ast[j].part[i].p.y > mj3.Perso.y && mj3.ast[j].part[i].p.y < mj3.Perso.y + 80)
            {
                mj3.Score--;
                if(mj3.ast[j].part[i].p.x > mj3.Perso.x && mj3.ast[j].part[i].p.x < mj3.Perso.x + 19)
                {
                    diff = mj3.ast[j].part[i].p.x - mj3.Perso.x;
                    for(k = 0 ; k < mj3.ast[j].np ; k++)
                    {
                        mj3.ast[j].part[k].p.x = mj3.ast[j].part[k].p.x - (diff + 4);
                        mj3.ast[j].part[k].v.x = -mj3.ast[j].part[k].v.x;
                        mj3.ast[j].part[k].v = FRICTION_MOON * mj3.ast[j].part[k].v;
                    }
                }
                if(mj3.ast[j].part[i].p.x > mj3.Perso.x + 110 && mj3.ast[j].part[i].p.x < mj3.Perso.x + 129)
                {
                    diff = (mj3.Perso.x + 129) - mj3.ast[j].part[i].p.x;
                    for(k = 0 ; k < mj3.ast[j].np ; k++)
                    {
                        mj3.ast[j].part[k].p.x = mj3.ast[j].part[k].p.x + (diff + 4);
                        mj3.ast[j].part[k].v.x = -mj3.ast[j].part[k].v.x;
                        mj3.ast[j].part[k].v = FRICTION_MOON * mj3.ast[j].part[k].v;
                    }
                }
                if(mj3.ast[j].part[i].p.y < mj3.Perso.y + 80 && mj3.ast[j].part[i].p.y > mj3.Perso.y + 5)
                {
                    diff = (mj3.Perso.y + 80) - mj3.ast[j].part[i].p.y;
                    for(k = 0 ; k < mj3.ast[j].np ; k++)
                    {
                        mj3.ast[j].part[k].p.y = mj3.ast[j].part[k].p.y + (diff + 4);
                        mj3.ast[j].part[k].v.y = -mj3.ast[j].part[k].v.y;
                        mj3.ast[j].part[k].v = FRICTION_MOON * mj3.ast[j].part[k].v;
                    }
                }
                if(mj3.ast[j].part[i].p.y > mj3.Perso.y && mj3.ast[j].part[i].p.y < mj3.Perso.y + 5)
                {
                    diff = mj3.ast[j].part[i].p.x - mj3.Perso.x;
                    for(k = 0 ; k < mj3.ast[j].np ; k++)
                    {
                        mj3.ast[j].part[k].p.x = mj3.ast[j].part[k].p.x - (diff + 4);
                        mj3.ast[j].part[k].v.x = -mj3.ast[j].part[k].v.x;
                        mj3.ast[j].part[k].v = FRICTION_MOON * mj3.ast[j].part[k].v;
                    }
                }
            }
        }
    }
}

void collisionAsteroides(mini_jeu3 &mj3)
{
    float y; int k;
    if(mj3.na == 2)
    {
        // vérification de la distance entre les deux centres
        y = dista(mj3.ast[0].centre, mj3.ast[1].centre);
        if ( y < 50)
        {
            if( mj3.ast[0].centre.y < mj3.ast[1].centre.y+30 &&  mj3.ast[0].centre.y > mj3.ast[1].centre.y-30)
            {
                // Si les astéroïdes sont en contact on inverse les vitesses
                if ( mj3.ast[0].centre.y < mj3.ast[1].centre.y )
                {
                    for(k = 0; k < mj3.ast[0].np; k++)
                    {
                        mj3.ast[0].part[k].p.y = mj3.ast[0].part[k].p.y - 1;
                        mj3.ast[1].part[k].p.y = mj3.ast[1].part[k].p.y + 1 ;
                        mj3.ast[0].part[k].v.y = -mj3.ast[0].part[k].v.y;
                        mj3.ast[1].part[k].v.y = -mj3.ast[1].part[k].v.y;
                    }
                }
                else
                {
                    for(k = 0; k < mj3.ast[0].np; k++)
                    {
                        mj3.ast[0].part[k].p.y = mj3.ast[0].part[k].p.y + 1;
                        mj3.ast[1].part[k].p.y = mj3.ast[1].part[k].p.y - 1 ;
                        mj3.ast[0].part[k].v.y = -mj3.ast[0].part[k].v.y;
                        mj3.ast[1].part[k].v.y = -mj3.ast[1].part[k].v.y;
                    }
                }
            }
            if( mj3.ast[0].centre.x < mj3.ast[1].centre.x+30 &&  mj3.ast[0].centre.x > mj3.ast[1].centre.x-30 )
            {
                if( mj3.ast[0].centre.x < mj3.ast[1].centre.x )
                {
                    for(k = 0; k < mj3.ast[0].np; k++)
                    {
                        mj3.ast[0].part[k].p.x = mj3.ast[0].part[k].p.x - 1;
                        mj3.ast[1].part[k].p.x = mj3.ast[1].part[k].p.x + 1 ;
                        mj3.ast[0].part[k].v.x = -mj3.ast[0].part[k].v.x;
                        mj3.ast[1].part[k].v.x = -mj3.ast[1].part[k].v.x;
                    }
                }
                else
                {
                    for(k = 0; k < mj3.ast[0].np; k++)
                    {
                        mj3.ast[0].part[k].p.x = mj3.ast[0].part[k].p.x + 1;
                        mj3.ast[1].part[k].p.x = mj3.ast[1].part[k].p.x - 1 ;
                        mj3.ast[0].part[k].v.x = -mj3.ast[0].part[k].v.x;
                        mj3.ast[1].part[k].v.x = -mj3.ast[1].part[k].v.x;
                    }
                }
            }
        }
    }
}

void update_milieu(mini_jeu3 &mj3)
{
    int i;
    // Mise à jour du centre pour tous les astéroïdes
    for(i=0; i<mj3.na ; i++)
    {
        mj3.ast[i].centre.x = (mj3.ast[i].part[0].p.x + mj3.ast[i].part[3].p.x) / 2;
        mj3.ast[i].centre.y = (mj3.ast[i].part[0].p.y + mj3.ast[i].part[3].p.y) / 2;
    }
}

void computeParticleForceSpring(mini_jeu3 &mj3)
{
	int i,j,i1,i2;
    float distance, intensity;
    Vec2 direction;
    for (j = 0; j < mj3.na; j++)
    {
        for (i = 0; i < mj3.ast[j].ns; i++)
        {
            i1 = mj3.ast[j].spr[i].i1;
            i2 = mj3.ast[j].spr[i].i2;

            direction = mj3.ast[j].part[i2].p - mj3.ast[j].part[i1].p;
            distance = normalize(direction);

            mj3.ast[j].part[i1].f +=  mj3.ast[j].spr[i].k * (distance - mj3.ast[j].spr[i].l) * direction;
            mj3.ast[j].part[i2].f +=  -mj3.ast[j].spr[i].k * (distance - mj3.ast[j].spr[i].l) * direction;

        }
    }
}

void updateSpring(mini_jeu3 &mj3)
{
    computeParticleForceGravityMoon(mj3);
    computeParticleForceSpring(mj3);
    updateParticle(mj3, mj3.dt);
    collisionLune(mj3);
    collisionAstronaute(mj3);
    update_milieu(mj3);
    collisionAsteroides(mj3);
}

void updateMj3(World &w)
{
    int i;

    // Gestion des déplacements

    if(isKeyPressed(SDLK_LEFT))
    {
        if(w.mj3.Perso.x-10 > 0)                      // Bloque l'astronaute à la bordure gauche
        {
            w.mj3.direct.direction = 0;
            w.mj3.Perso.x = w.mj3.Perso.x - 1;
        }
    }
    if(isKeyPressed(SDLK_RIGHT))
    {
        if(w.mj3.Perso.x+10 < DIMW-129)                   // Bloque l'astronaute à la bordure droite
        {
            w.mj3.direct.direction = 1;
            w.mj3.Perso.x = w.mj3.Perso.x + 1;
        }
    }
    updateSpring(w.mj3);
    int time = elapsedTime() - w.TimeStart;
    if(time <= 60 && w.mj3.na < time/3+1 && w.mj3.na < 2) // ajout d'astéroïde
    {
        w.mj3.na++;
        addAsteroide(w.mj3);
    }

    // Cas d'arrêt du mini-jeu

    if(time == 60)
    {
        w.Step++;
        init_minijeu4(w);
    }
    if(w.mj3.Score <= 0)
    {
        w.Step = 8;
    }
}

///////////////////////////// Mini-jeu 4 ///////////////////////////////

void AddBalle(mini_jeu4 &mj4)
{
    mj4.dernier_Tir = elapsedTime();
    int nb = mj4.nb;
    float tt = mj4.Arme[mj4.choix_arme].travel_time;   // travel_time / Beaucoup plus court à utiliser

    // initialisation de la balle

    mj4.Balle[nb].p.x = DIMW/2;
    mj4.Balle[nb].p.y = 1;
    mj4.Balle[nb].etat = true;
    mj4.Balle[nb].m = 1;
    mj4.Balle[nb].v.y = tt;

    // Calculs mathématiques pour trouver la vitesse en x.

    float adjacent;
    float hypothenuse;
    float oppose;

    int droite_gauche;

    oppose = (mj4.Viseur.coord.x) - mj4.Balle[nb].p.x;

    // la variable opposé ne pouvant être négative pour la suite des calculs
    // on reporte le signe moins dans une autre varible en y assignant la valeur -1
    // Puis on multipliera plus tard la vitesse pas cette variable pour avoir une vitesse en x négative.

    if (oppose < 0)
    {
        droite_gauche = -1;
        oppose = -oppose;
    }
    else
    {
        droite_gauche = 1;
    }

    adjacent = (mj4.Viseur.coord.y) - mj4.Balle[nb].p.y;
    hypothenuse = sqrt(adjacent * adjacent + oppose * oppose);

    float cosinus;
    cosinus = adjacent / hypothenuse;

    float angle;
    angle = acos(cosinus);
    angle = rad_to_deg(angle);

    float angle_max = 26.7515;      // Angle maximum constaté sur une fenêtre avec DIMW = 500.

    mj4.Balle[nb].v.x = tt * (angle/(angle_max*(adjacent/(DIMW/2-29))) * droite_gauche);

    // Initialisation des force à 0 car elles sont négligés dans ce mini jeu

    mj4.Balle[nb].f.x = 0;
    mj4.Balle[nb].f.y = 0;

    mj4.nb++;
    mj4.Score -= mj4.Arme[mj4.choix_arme].conso_part;
}

void collisionRobot(mini_jeu4 &mj4, Particle &Balle)
{
    // Fonction simple pour savoir si la balle va entrer en collision avec le robot.
    if(mj4.Robot.coord.x <= Balle.p.x && mj4.Robot.coord.x+70 >= Balle.p.x)
    {
        if(mj4.Robot.coord.y <= Balle.p.y && mj4.Robot.coord.y+130 >= Balle.p.y)
        {
            Balle.etat = false;
            mj4.Robot.vie -= mj4.Arme[mj4.choix_arme].degat;
        }
    }
}

void BalleUpdate(Particle &p)
{
    // Petite nuance avec une particule traditionnelle, si une balle sort du calme, elle disparait.
    if(p.p.x < 0)
    {
        p.etat = false;
    }
    if(p.p.x > DIMW-1)
    {
        p.etat = false;
    }
    if(p.p.y < 0)
    {
        p.etat = false;
    }
    if(p.p.y > DIMW-1)
    {
        p.etat = false;
    }
    p.p.x = p.p.x + p.v.x * dt;
    p.p.y = p.p.y + p.v.y * dt;
}

void mouv_robot(robot &Robot)
{
    int direction;
    if(Robot.coord.x < 2)
    {
        Robot.v.x = -Robot.v.x;
    }
    else
    {
        if(Robot.coord.x+70 > DIMW-2)
        {
            Robot.v.x = -Robot.v.x;
        }
        else
        {
            int r1;
            r1= frand(-4,4);        // Déplacements aléatoires du robot
            Robot.v.x += r1;
        }
    }
    Robot.coord.x += Robot.v.x * dt;
}

void updateMj4(World &w)
{
    int i, x, y, nb_tir;
    nb_tir = w.mj4.Score / w.mj4.Arme[w.mj4.choix_arme].conso_part;
    if(nb_tir > 0)
    {
        if(w.mj4.Robot.vie > 0)
        {
            mouv_robot(w.mj4.Robot);
            mousePos(x,y);
            // On bloque les coordonnés du viseur
            if(x <= 29)
            {
                w.mj4.Viseur.coord.x = 29;
            }
            if(x >= DIMW-29)
            {
                w.mj4.Viseur.coord.x = DIMW-29;
            }
            if (x > 29 && x < DIMW-29)
            {
                w.mj4.Viseur.coord.x = x;
            }
            // Si l'utilisateur clique et que le délai de rechargement est dépassé
            if(isMousePressed(SDL_BUTTON_LEFT) && (elapsedTime() - w.mj4.dernier_Tir > w.mj4.Arme[w.mj4.choix_arme].delai ))
            {
                AddBalle(w.mj4);
            }
            for(i=0; i < w.mj4.nb ; i++)
            {
                // Si la balle est active, on la met à jour et on vérifie les cas de collision avec le robot
                if(w.mj4.Balle[i].etat)
                {
                    BalleUpdate(w.mj4.Balle[i]);
                    collisionRobot(w.mj4, w.mj4.Balle[i]);
                }
            }
        }
        else
        {
            // Si plus de tirs, on passe à l'étape suivante
            w.Step++;
            w.TimeStart = elapsedTime();
        }
    }
    else
    {
        w.Step++;
        w.TimeStart = elapsedTime();
    }
}

////////////////////////////////////////////////////////////////////////

//////////////////////////////// Update ////////////////////////////////

void update(World &w)
{
    switch (w.Step)
    {
        case 0 : Presentation(w); break;
        case 1 : updateMj1(w);
                 drawMj1(w); break;
        case 2 : transition1(w); break;
        case 3 : updateMj2(w);
                 drawMj2(w); break;
        case 4 : updateMj3(w);
                 drawMj3(w); break;
        case 5 : transition2(w); break;
        case 6 : updateMj4(w);
                 drawMj4(w); break;
        case 7 : fin(w); break;
        case 8 : fin(w); break;
        default : cout << "erreur" << endl; break;
    }
}

////////////////////////////////////////////////////////////////////////

////////////////////////////////// Main ////////////////////////////////

int main(int , char** )
{
    World w;
    bool stop=false;
    srand(time(NULL));
	winInit("Le monde des Particules", DIMW, DIMW);
	backgroundColor(255,255,255);
	init(w);
	setKeyRepeatMode(true);
	while( !stop )
    {
        winClear();
        update(w);
        stop = winDisplay();
    }
    winQuit();
	return 0;
}
