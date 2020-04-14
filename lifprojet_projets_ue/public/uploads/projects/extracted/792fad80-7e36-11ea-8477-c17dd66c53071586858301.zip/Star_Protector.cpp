#include <Grapic.h>
#include <iostream>
#include <math.h>
using namespace grapic;
using namespace std;

//constantes utiles au jeu
const int DIMWX = 700;
const int DIMWY = 900;
const int MAX_MUNITION=50;
const float DIMSHIP=50;
const float dt=0.03;
const int MAX_ENEMY=50;
const int DIMENEMY=70;
const int MAX_CHAR=100;
const int MAX_MUNITION_ENEMY=100;
const int DIMBOSSX=300;
const int DIMBOSSY=200;
const int DIM_MUNITION_BOSS_SPECIAL_X=200;
const int DIM_MUNITION_BOSS_SPECIAL_Y=20;
//const int VIEBOSS=100;
const int MAX_LOOT=5;
const int DIM_MENU_UI_X=400;
const int DIM_MENU_UI_Y=300;

//Manipulation des complexes
struct Complex
{
    float x,y;
};

Complex make_complex(float x, float y)
{
    Complex c;
    c.x=x;
    c.y=y;
    return c;
}
Complex make_complex_exp(float r, float theta_deg)
{
    Complex c;
    c.x=r*cos(theta_deg);
    c.y=r*sin(theta_deg);
    return c;
}
Complex operator+(Complex a, Complex b)
{
    Complex r;
    r.x=a.x+b.x;
    r.y=a.y+b.y;
    return r;
}
Complex operator-(Complex a, Complex b)
{
    Complex r;
    r.x=a.x-b.x;
    r.y=a.y-b.y;
    return r;
}
Complex operator*(float a, Complex b)
{
    Complex r;
    r.x=a*b.x;
    r.y=a*b.y;
    return r;
}
Complex scale(Complex a, float cx, float cy, float lambda)
{
    Complex c=make_complex(cx,cy);
    return lambda*(a-c)+c;
}
Complex operator*(Complex a, Complex b)
{
    Complex r;
    r.x=a.x*b.x-a.y*b.y;
    r.y=a.x*b.y+b.x*a.y;
    return r;
}
Complex Rotate(Complex a, float cx, float cy, float angle)
{
    Complex c=make_complex(cx,cy);
    Complex r=make_complex_exp(1,angle);
    return (a-c)*r+c;
}
//Manipulation des vecteurs
struct Vec2
{
    float x,y;
};
Vec2 make_vec2(float a, float b)
{
    Vec2 r;
    r.x=a;
    r.y=b;
    return r;
}
Vec2 make_Vec2_exp(float r, float theta_deg)
{
    Vec2 c;
    c.x=r*cos(theta_deg);
    c.y=r*sin(theta_deg);
    return c;
}
Vec2 operator+(Vec2 a, Vec2 b)
{
    Vec2 r;
    r.x=a.x+b.x;
    r.y=a.y+b.y;
    return r;
}
Vec2 operator-(Vec2 a, Vec2 b)
{
    Vec2 r;
    r.x=a.x-b.x;
    r.y=a.y-b.y;
    return r;
}
Vec2 operator*(float f, Vec2 v)
{
    Vec2 r;
    r.x=f*v.x;
    r.y=f*v.y;
    return r;
}
Vec2 operator*(Vec2 v1, Vec2 v2)
{
    Vec2 r;
    r.x=v1.x*v2.x-v1.y*v2.y;
    r.y=v1.y*v2.x+v2.y*v1.x;
    return r;
}
Vec2 RotateVec2(Vec2 a,float cx,float cy,float angle)
{
    Vec2 c=make_vec2(cx,cy);
    Vec2 r=make_Vec2_exp(1,(angle*2*3.1416)/360);
    return (a-c)*r+c;
}
//Munition du Ship
struct Munition
{
    float m;
    Vec2 v;
    Vec2 f;
    Vec2 p;
    bool vivant;
};
// Ship
struct Spaceship
{
    Vec2 p;
    bool vivant;
    int vies;
    bool Invincible;
    float time;
    int LVL;
    Image imShip1,imShip2,imShip3;
    Image vie;
};
// Bonus
struct Bonus
{
    Vec2 p;
    bool vivant;
    Vec2 v;
};
// Ennemi
struct Enemy
{
    Vec2 p;
    Vec2 v;
    bool vivant;
    float time;
    int type;
};
// Boss
struct Boss
{
    Vec2 p;
    Vec2 v;
    bool vivant;
    float time;
    int vie;
};
// munition ennemie
struct MunitionEnemy
{
    Vec2 v;
    Vec2 p;
    bool vivant;
};
// structure du World
struct World
{
    Munition M[MAX_MUNITION];
    int nb;
    Enemy E[MAX_ENEMY];
    int nbe;
    MunitionEnemy Me[MAX_MUNITION_ENEMY];
    MunitionEnemy Mb[MAX_MUNITION_ENEMY];
    MunitionEnemy Ms[MAX_MUNITION_ENEMY];
    MunitionEnemy Mbc[MAX_MUNITION_ENEMY];
    Bonus Bn[MAX_LOOT];
    Boss B[3];
    int nbB;
    int nbBn;
    int nbms;
    int nbmb;
    int nbmbc;
    int nbme;
    int Score;
    int Stage;
    float variablei;
    Image bg;
    Image imMuniEnemy;
    Image imMuniBossSpecial;
    Image imBoss1,imBoss2,imBoss3;
    Image imEnemy1,imEnemy11,imEnemy12,imEnemy2,imEnemy21;
    Image bonus;
    Image imMunition;
   // Image overlay;
    Image MenuUI;
    //Image MenuDifficulty;
    //Image MenuControles;
    Image VictoryScreen;
    Image Scenario;
    Image Title;
    //Image anim[12];
};
// Servait à debugger le boss
void printBoss(World w, char* txt)
{
    int i;
    cout<<txt<<" ";
    cout<<"boss n="<<w.nbB<<" ";
    for (i=0;i<w.nbB;i++)
    {
        cout<<w.B[i].vie<<"/"<<w.B[i].vivant<<" ";
    }
    cout<<endl;
    pressSpace();
}
// Initialise une munition du ship
Munition initMunition(Spaceship s)
{
    Munition m;
    m.m=1;
    m.p=make_vec2(s.p.x,s.p.y+DIMSHIP/2+5);
    m.v=make_vec2(0,0.3);
    m.f=make_vec2(0,0);
    m.vivant=true;
    return m;
}
// Initialise un ennemi
Enemy initEnemy()
{
    Enemy e;
    float x,y;
    x=irand(DIMENEMY/2,DIMWX-DIMENEMY/2);
    y=DIMWY;
    e.p=make_vec2(x,y);
    e.v=make_vec2(0,-0.1);
    e.vivant=true;
    e.time=elapsedTime();
    e.type=irand(1,3);
    return e;
}
// Initialise un boss
void initBoss(World & w,int viemaxboss)
{
    int i;
    for (i=0;i<w.nbB;i++)
    {
        w.B[i].p=make_vec2(DIMWX/2,700);
        w.B[i].v=make_vec2(0,0);
        w.B[i].vivant=false;
        w.B[i].time=elapsedTime();
        w.B[i].vie=viemaxboss;
    }
}
// Initialise une munitions ennemie
void initMunitionEnemy(World & w,Enemy e)
{
    w.Me[w.nbme].p=make_vec2(e.p.x,e.p.y);
    w.Me[w.nbme].v=make_vec2(0,-0.3);
    w.Me[w.nbme].vivant=true;
}
// Initialise une munitions du boss
void initMunitionBoss(World & w,Boss b)
{
    w.Mb[w.nbmb].p=make_vec2(b.p.x,b.p.y-DIMBOSSY/2);
    w.Mb[w.nbmb].v=make_vec2(0,-0.3);
    w.Mb[w.nbmb].vivant=true;
}
// Initialise une munition spéciale du boss
void initMunitionBossSpecial(World & w,Boss b)
{
    w.Ms[w.nbms].p=make_vec2(b.p.x,b.p.y-DIMBOSSY/2);
    //w.Ms[w.nbms].p=make_vec2(250,250);
    w.Ms[w.nbms].v=make_vec2(0,-0.3);
    w.Ms[w.nbms].vivant=true;
}
// Initialise la structure World, les images, etc.
void initWorld(World & w)
{
    int i;
    w.nb=0;
    w.nbe=0;
    w.Score=0;
    w.Stage=1;
    w.nbme=0;
    w.nbmb=0;
    w.nbB=3;
    w.nbms=0;
    w.nbmbc=30;
    w.nbBn=0;
    w.imBoss1=image("data/StarProtector/boss1.png");
    w.imBoss2=image("data/StarProtector/boss2.png");
    w.imBoss3=image("data/StarProtector/boss3.png");
    w.imEnemy1=image("data/StarProtector/enemy1.png");
    w.imEnemy11=image("data/StarProtector/enemy11.png");
    w.imEnemy12=image("data/StarProtector/enemy12.png");
    w.imEnemy2=image("data/StarProtector/enemy2.png");
    w.imEnemy21=image("data/StarProtector/enemy21.png");
    w.imMunition=image("data/StarProtector/amo_ship.png");
    w.imMuniEnemy=image("data/StarProtector/amo_enemy.png");
    w.imMuniEnemy=image("data/StarProtector/amo_enemy.png");
    w.imMuniEnemy=image("data/StarProtector/amo_enemy.png");
    w.imMuniBossSpecial=image("data/StarProtector/amo_boss.png");
    w.bg=image("data/StarProtector/bg.jpg");
    w.bonus=image("data/StarProtector/ship1.png");
    //w.overlay=image("data/StarProtector/overlay.png");
    w.MenuUI=image("data/StarProtector/MenuUI.png");
    //w.MenuDifficulty=image("data/StarProtector/MenuDifficulty.png");
    //w.MenuControles=image("data/StarProtector/MenuControles.png");
    w.VictoryScreen=image("data/StarProtector/VictoryScreen.jpg");
    w.Scenario=image("data/StarProtector/Scenario.jpg");
    w.Title=image("data/StarProtector/Title.png");
    // ce qui suit est censé initialisé le tableau d'image pour l'animation de l'explosion mais ne marche pas.
    /*string path="data/StarProtector/spritExplosion/step"+to_string(i)+".png";
    for (i=0;i<12;i++)
    {
        w.anim[i]=image(path.c_str());
    }*/
}
// Initialise un bonus
void initLoot(World & w,Enemy e)
{
    w.Bn[w.nbBn].p=make_vec2(e.p.x,e.p.y);
    w.Bn[w.nbBn].v=make_vec2(0,-0.3);
    w.Bn[w.nbBn].vivant=true;
}
//Libère de la place dans le tableau de bonus lorsque celui-ci est plein
void compactLoot(World& w)
{
    int i;
    for(i=0;i<w.nbBn;++i)
    {
        if (!w.Bn[i].vivant)
        {
            w.Bn[i]= w.Bn[w.nbBn-1];
            w.nbBn--;
            i--;
        }
    }
}
// Initialise le ship
Spaceship initSpaceship()
{
    Spaceship s;
    s.p=make_vec2(DIMWX/2,25);
    s.vivant=true;
    s.vies=5;
    s.Invincible=false;
    s.time=0;
    s.LVL=1;
    s.imShip1=image("data/StarProtector/ship1.png");
    s.imShip2=image("data/StarProtector/ship2.png");
    s.imShip3=image("data/StarProtector/ship3.png");
    s.vie=image("data/StarProtector/ship1.png");
    return s;
}
//Libère de la place dans le tableau de munitions  du ship lorsque celui-ci est plein
void compactMuni(World& w)
{
    int i;
    for(i=0;i<w.nb;++i)
    {
        if (!w.M[i].vivant)
        {
            w.M[i] = w.M[w.nb-1];
            w.nb--;
            i--;
        }
    }
}
//Libère de la place dans le tableau de munitions ennemies lorsque celui-ci est plein
void compactMuniEnemy(World & w)
{
    int i;
    for(i=0;i<w.nbme;++i)
    {
        if (!w.Me[i].vivant)
        {
            w.Me[i] = w.Me[w.nbme-1];
            w.nbme--;
            i--;
        }
    }
}
//Libère de la place dans le tableau de munitions normales du boss lorsque celui-ci est plein
void compactMuniBoss(World & w)
{
    int i;
    for(i=0;i<w.nbmb;++i)
    {
        if (!w.Mb[i].vivant)
        {
            w.Mb[i] = w.Mb[w.nbmb-1];
            w.nbmb--;
            i--;
        }
    }
}
//Libère de la place dans le tableau de munitions spéciales du boss lorsque celui-ci est plein
void compactMuniBossSpecial(World & w)
{
    int i;
    for(i=0;i<w.nbms;++i)
    {
        if (!w.Ms[i].vivant)
        {
            w.Ms[i] = w.Ms[w.nbms-1];
            w.nbms--;
            i--;
        }
    }
}
// Ajoute des muntions ennemies
void addMunitionEnemy(World & w,Enemy e)
{
    if (w.nbme==MAX_MUNITION_ENEMY)
    {
        compactMuniEnemy(w);
    }
    if (w.nbme<MAX_MUNITION_ENEMY)
    {
        initMunitionEnemy(w,e);
        w.nbme++;
    }
}
//Ajoute des bonus
void addBonus(World & w,Enemy e)
{
    if (w.nbBn==MAX_LOOT)
    {
        compactLoot(w);
    }
    if (w.nbBn<MAX_LOOT)
    {
        initLoot(w,e);
        w.nbBn++;
    }
}
// Ajoute des munitions normales pour le boss
void addMunitionBoss(World & w,Boss b)
{
    if (w.nbmb==MAX_MUNITION_ENEMY)
    {
        compactMuniBoss(w);
    }
    if (w.nbmb<MAX_MUNITION_ENEMY)
    {
        initMunitionBoss(w,b);
        w.nbmb++;
    }
}
// Ajoute des munitions spéciales pour le boss
void addMunitionBossSpecial(World & w,Boss b)
{
    if (w.nbms==MAX_MUNITION_ENEMY)
    {
        compactMuniBossSpecial(w);
    }
    if (w.nbms<MAX_MUNITION_ENEMY)
    {
        initMunitionBossSpecial(w,b);
        w.nbms++;
    }
}
// Ajoute des munitions pour le ship
void addMunition(World & w,Spaceship s)
{
    if (w.nb==MAX_MUNITION)
    {
        compactMuni(w);
    }
    if (w.nb<MAX_MUNITION)
    {
        w.M[w.nb]=initMunition(s);
        w.nb++;
    }
}
// Libère de la place dans le tableau d'ennemis lorsque celui-ci est plein
void compactEn(World& w)
{
    int i;
    for(i=0;i<w.nbe;++i)
    {
        if (!w.E[i].vivant)
        {
            w.E[i] = w.E[w.nbe-1];
            w.nbe--;
            i--;
        }
    }
}
// Ajoute un ennemi
void addEnemy(World & w)
{
    if (w.nbe==MAX_ENEMY)
    {
       // cout<<"avant compact "<<w.nbe<<endl;
        compactEn(w);
       // cout<<"apres compact "<<w.nbe<<endl;
    }
    if (w.nbe<MAX_ENEMY)
    {
        w.E[w.nbe]=initEnemy();
        w.nbe++;
    }
    else
        cout<<"j'espere que ca n'arivera jamais!"<<endl;
}
// Modifie le stage dans lequel le joueur se trouve
void Stage(World & w,Spaceship & s)
{
    if ((w.Score>=5000)&&(w.Score<30000))
    {
        w.Stage=2;
        s.LVL=2;
    }
    if (w.Score>=30000)
    {
        w.Stage=3;
        s.LVL=3;
    }
}
// fonction qui renvoie un booléen true si le joueur est dans le bon stage
bool Stage1(World w)
{
    if ((w.Score>=0)&&(w.Score<2000))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Stage2(World w)
{
    if ((w.Score>=5000)&&(w.Score<20000))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Stage3(World w)
{
    if ((w.Score>=30000)&&(w.Score<70000))
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Incrémente le score lorsqu'un ennemi est tué en fonction du stage
void Score1(World & w)
{
    int i,j;
    if (Stage1(w))
    {
        w.Score+=100;
    }
    if (Stage2(w))
    {
        w.Score+=500;
    }
    if (Stage3(w))
    {
        w.Score+=1000;
    }
}
//Incrémente le score lorsqu'un boss est tué
void Score2(World & w)
{
    if ((w.Score>=2000)&&(w.Score<5000))
    {
        w.Score+=3000;
    }
    if ((w.Score>=5000)&&(w.Score<30000))
    {
        w.Score+=10000;
    }
    if ((w.Score>=30000)&&(w.Score<120000))
    {
        w.Score+=50000;
    }
}
// Crée un tableau de munitions pour l'attaque spéciale du boss : un cercle de munitions autour de celui-ci
void CreerTableauCirculaire(World & w)
{
    int i,j,k;
    for (i=0;i<w.nbB;i++)
    {
        if (w.B[i].vivant)
        {
            Vec2 v;
            v.x=w.B[i].p.x-DIMBOSSX/2;
            v.y=w.B[i].p.y;
            for (j=0;j<w.nbmbc;j++)
            {
                w.Mbc[j].p=RotateVec2(v,w.B[i].p.x,w.B[i].p.y,j*12);
                w.Mbc[j].v=w.Mbc[j].p-w.B[i].p;
                w.Mbc[j].vivant=true;
            }
        }
    }
}
// Rend le ship invincible lorsqu'il perd une vie pour ne pas perdre toutes les vies ou trop d'un coup : rend le jeu plus jouable.
void Invincible(Spaceship & s)
{
    s.Invincible=true;
    s.time=elapsedTime();
}
//Gère la vie du ship
void Vies(Spaceship & s)
{
    s.vies--;
    if (s.LVL>1)
    {
        //s.LVL--; les bonus ne marchant pas inutile pour l'instant.
    }
}
//Gère la vie du boss
void VieBoss(Boss & b)
{
    b.vie--;
}
//différentes fonction de collisions
bool collisionMuniSpecial(Vec2 v, Spaceship s)
{
    if ((v.x<=s.p.x+DIMSHIP/2)
    && (v.x>=s.p.x-DIMSHIP/2)
    && (v.y<=s.p.y+DIMSHIP/2)
    && (v.y>=s.p.y-DIMSHIP/2))
    {
        return true;
    }
    return false;
}
bool collisionBonus(Vec2 v, Spaceship s)
{
    if ((v.x<=s.p.x+DIMSHIP/2)
    && (v.x>=s.p.x-DIMSHIP/2)
    && (v.y<=s.p.y+DIMSHIP/2)
    && (v.y>=s.p.y-DIMSHIP/2))
    {
        return true;
    }
    return false;
}
bool collisionShip(MunitionEnemy m,Vec2 v)
{
    if ((v.x<=m.p.x+DIM_MUNITION_BOSS_SPECIAL_X/2)
    && (v.x>=m.p.x-DIM_MUNITION_BOSS_SPECIAL_X/2)
    && (v.y<=m.p.y+DIM_MUNITION_BOSS_SPECIAL_Y/2)
    && (v.y>=m.p.y-DIM_MUNITION_BOSS_SPECIAL_Y/2))
    {
        return true;
    }
    return false;
}
bool collisionBoss(Boss b,Vec2 v)
{
    if ((v.x<=b.p.x+DIMBOSSX/2)
    && (v.x>=b.p.x-DIMBOSSX/2)
    && (v.y<=b.p.y+DIMBOSSY/2)
    && (v.y>=b.p.y-DIMBOSSY/2))
    {
        return true;
    }
    return false;
}
bool collisionEnemy(Enemy e,Vec2 v)
{
    if ((v.x<=e.p.x+DIMENEMY/2)
    && (v.x>=e.p.x-DIMENEMY/2)
    && (v.y<=e.p.y+DIMENEMY/2)
    && (v.y>=e.p.y-DIMENEMY/2))
    {
        return true;
    }
    return false;
}
// test si le boss est vivant et incrément le score si le boss est tué
void BossVivant(World & w,Boss & b)
{
    if ((b.vie<=0)&&(b.vivant))
    {
        b.vivant=false;
        Score2(w);
        //w.variablei=VIEBOSS;
    }
}
//affiche la barre de vie du boss.
void drawBarreDeVieDuBoss(Boss b,float i)
{
    if (b.vie>=0)
    {
        //color(0,0,0);
        //rectangleFill(100,820,600,850);
        color(0,255,0);
        rectangleFill(100,820,(600-i),850);
    }
}
// Tentative d'affichage d'une animation à chaque mort de boss, ne marche pas.
/*void affiche_explosion(World w,Boss b)
{
    int i;
    float e=elapsedTime();
    for (i=0;i<12;i++)
    {
        if ((elapsedTime()-e)>=(1.0/20))
        {
            image_draw(w.anim[i],b.p.x-DIMBOSSX/2,b.p.y-DIMBOSSY/2,DIMBOSSX,DIMBOSSY);
            e=elapsedTime();
        }
    }
}*/
//affiche les éléments du jeu : ship, ennemis, boss, tir alliés et ennemis, score, stage, vies, etc.
void draw (World  w, Spaceship s, int VIEMAXBOSS)
{
    image_draw(w.bg,0,0,DIMWX,DIMWY);
    //color(255,200,0);
    int i;
    for (i=0;i<w.nb;i++)
    {
        if (w.M[i].vivant==true)
        {
            image_draw(w.imMunition,w.M[i].p.x,w.M[i].p.y);
        }
    }
    //color(0,255,255);
    for (i=0;i<w.nbe;i++)
    {
        if (w.E[i].vivant==true)
        {
            if (Stage1(w))
            {
                switch (w.E[i].type)
                {
                    case 1: image_draw(w.imEnemy1,w.E[i].p.x-DIMENEMY/2,w.E[i].p.y-DIMENEMY/2,DIMENEMY,DIMENEMY);
                    break;
                    case 2: image_draw(w.imEnemy11,w.E[i].p.x-DIMENEMY/2,w.E[i].p.y-DIMENEMY/2,DIMENEMY,DIMENEMY);
                    break;
                    case 3: image_draw(w.imEnemy12,w.E[i].p.x-DIMENEMY/2,w.E[i].p.y-DIMENEMY/2,DIMENEMY,DIMENEMY);
                    break;
                }
            }
            if (Stage2(w))
            {
                switch (w.E[i].type)
                {
                    case 1: image_draw(w.imEnemy2,w.E[i].p.x-DIMENEMY/2,w.E[i].p.y-DIMENEMY/2,DIMENEMY,DIMENEMY);
                    break;
                    case 2: image_draw(w.imEnemy21,w.E[i].p.x-DIMENEMY/2,w.E[i].p.y-DIMENEMY/2,DIMENEMY,DIMENEMY);
                    break;
                    case 3: image_draw(w.imEnemy21,w.E[i].p.x-DIMENEMY/2,w.E[i].p.y-DIMENEMY/2,DIMENEMY,DIMENEMY);
                }
            }
            if (Stage3(w))
            {
                switch (w.E[i].type)
                {
                    case 1: image_draw(w.imEnemy1,w.E[i].p.x-DIMENEMY/2,w.E[i].p.y-DIMENEMY/2,DIMENEMY,DIMENEMY);
                    break;
                    case 2: image_draw(w.imEnemy21,w.E[i].p.x-DIMENEMY/2,w.E[i].p.y-DIMENEMY/2,DIMENEMY,DIMENEMY);
                    break;
                    case 3: image_draw(w.imEnemy2,w.E[i].p.x-DIMENEMY/2,w.E[i].p.y-DIMENEMY/2,DIMENEMY,DIMENEMY);
                    break;
                }
            }
        }
    }
    //color(255,0,0);
    if (s.vivant==true)
    {
        switch (s.LVL)
        {
            case 1: image_draw(s.imShip1,s.p.x-DIMSHIP/2,s.p.y-DIMSHIP/2,DIMSHIP,DIMSHIP);
            break;
            case 2: image_draw(s.imShip2,s.p.x-DIMSHIP/2,s.p.y-DIMSHIP/2,DIMSHIP,DIMSHIP);
            break;
            case 3: image_draw(s.imShip3,s.p.x-DIMSHIP/2,s.p.y-DIMSHIP/2,DIMSHIP,DIMSHIP);
            break;
        }
    }
    if (w.B[0].vivant)
    {
        //color(0,0,200);
        image_draw(w.imBoss1,w.B[0].p.x-DIMBOSSX/2,w.B[0].p.y-DIMBOSSY/2,DIMBOSSX,DIMBOSSY);
    }
    if (w.B[1].vivant)
    {
        //color(0,0,200);
        image_draw(w.imBoss2,w.B[1].p.x-DIMBOSSX/2,w.B[1].p.y-DIMBOSSY/2,DIMBOSSX,DIMBOSSY);
    }
    if (w.B[2].vivant)
    {
        //color(0,0,200);
        image_draw(w.imBoss3,w.B[2].p.x-DIMBOSSX/2,w.B[2].p.y-DIMBOSSY/2,DIMBOSSX,DIMBOSSY);
    }
    //printBoss(w, "");
    //affichage d'une bande rouge avec les différents élements de l'UI joueur faute d'avoir un overlay qui fonctionne
    color(255,0,0);
    rectangleFill(0,DIMWY-30,DIMWX,DIMWY);
    //image_draw(w.overlay,0,DIMWY-50,700,50);
    color(0,0,0);
    print(20,DIMWY-28,"Score : ");
    print(100,DIMWY-28,w.Score);
    print(DIMWX/2-40,DIMWY-28,"Stage  ");
    print(DIMWX/2+20,DIMWY-28,w.Stage);
    for (i=1;i<=s.vies;i++)
    {
        //color(255,200,0);
        //circleFill(DIMWX-30*i,DIMWY-15,10);
        image_draw(s.imShip1,(DIMWX-30*i)-DIMSHIP/2,(DIMWY-7)-DIMSHIP/2,30,30);
    }
    for (i=0;i<w.nbme;i++)
    {
        if (w.Me[i].vivant)
        {
            //color(0,255,255);
            //cout<<w.Me[i].p.x;
            //circleFill(w.Me[i].p.x,w.Me[i].p.y,5);
            image_draw(w.imMuniEnemy,w.Me[i].p.x-20/2,w.Me[i].p.y-20/2,20,20);
        }
    }
    for (i=0;i<w.nbmb;i++)
    {
        if (w.Mb[i].vivant)
        {
            //color(255,0,0);
            //circleFill(w.Mb[i].p.x,w.Mb[i].p.y,5);
            image_draw(w.imMuniEnemy,w.Mb[i].p.x-30/2,w.Mb[i].p.y-30/2,20,20);
        }
    }
    for (i=0;i<w.nbms;i++)
    {
        //cout<<w.Ms[i].p.x<<endl;
        if (w.Ms[i].vivant)
        {
            //color(255,0,0);
            //rectangleFill(w.Ms[i].p.x-DIM_MUNITION_BOSS_SPECIAL_X/2,w.Ms[i].p.y-DIM_MUNITION_BOSS_SPECIAL_Y/2,w.Ms[i].p.x+DIM_MUNITION_BOSS_SPECIAL_X/2,w.Ms[i].p.y+DIM_MUNITION_BOSS_SPECIAL_Y/2);
            image_draw(w.imMuniBossSpecial,w.Ms[i].p.x-DIM_MUNITION_BOSS_SPECIAL_X/2,w.Ms[i].p.y-DIM_MUNITION_BOSS_SPECIAL_Y/2,DIM_MUNITION_BOSS_SPECIAL_X,DIM_MUNITION_BOSS_SPECIAL_Y,0,2); //flip = 2 car l'image était dans le mauvais sens

        }
    }
    for (i=0;i<w.nbB;i++)
    {
        if (w.B[i].vivant)
        {
            drawBarreDeVieDuBoss(w.B[i],(VIEMAXBOSS-w.B[i].vie)*500/VIEMAXBOSS);
        }
    }
    for (i=0;i<w.nbmbc;i++)
    {
        if (w.Mbc[i].vivant)
        {
            //color(255,0,0);
            //circleFill(w.Mbc[i].p.x,w.Mbc[i].p.y,5);
            image_draw(w.imMuniEnemy,w.Mbc[i].p.x-30/2,w.Mbc[i].p.y-30/2,30,30);
        }
    }
    for (i=0;i<w.nbBn;i++)
    {
        if (w.Bn[i].vivant)
        {
            //color(0,255,0);
            //rectangleFill(w.Bn[i].p.x-DIMSHIP/2,w.Bn[i].p.y-DIMSHIP/2,w.Bn[i].p.x+DIMSHIP/2,w.Bn[i].p.y+DIMSHIP/2);
            image_draw(s.imShip1,w.Bn[i].p.x-DIMSHIP/2,w.Bn[i].p.y-DIMSHIP/2,DIMSHIP,DIMSHIP);
        }
    }
}

// fonction pour faire drop un item : ne fonctionne pas
void Tirage_Bonus(World w,Enemy e)
{
    int b=irand(1,10);
    if (b==5)
    {
        addBonus(w,e);
    }
}

// Update des positions des différents éléments du jeu : ship, boss, enemy, munitions des ennemis, du ship, du boss et les munitions spéciales/circulaire du boss.
// vérification des colisions entre les munitions du ship et les ennemis, boss, entre le ship et le boss ou les ennemis, ainsi que les munitions des ennemis/boss et le ship.
// Si collisions ou un élément qui sort de l'écran son booléen vivant est mis à false = mis à mort.
void update (World & w, Spaceship & s)
{
    int i,k,l,m,x,y;
    for (i=0;i<w.nb;i++)
    {
         w.M[i].p.y=w.M[i].p.y+w.M[i].v.y;
    }
    int j;

    for (j=0;j<w.nbe;j++)
    {
        w.E[j].p.y=w.E[j].p.y+w.E[j].v.y;
    }
    for (j=0;j<w.nbme;j++)
    {
        w.Me[j].p.y+=w.Me[j].v.y;
    }
    for (j=0;j<w.nbmb;j++)
    {
        w.Mb[j].p.y+=w.Mb[j].v.y;
    }
    for (j=0;j<w.nbms;j++)
    {
        w.Ms[j].p.y+=w.Ms[j].v.y;
    }
    for (j=0;j<w.nbmbc;j++)
    {
        w.Mbc[j].p.x+=dt/30*w.Mbc[j].v.x;
        w.Mbc[j].p.y+=dt/30*w.Mbc[j].v.y;
    }
    for (j=0;j<w.nbBn;j++)
    {
        w.Bn[j].p.y+=w.Bn[j].v.y;
    }
    if (isKeyPressed(SDLK_UP))
    {
        s.p.y=s.p.y+0.2;
    }
    if (isKeyPressed(SDLK_DOWN))
    {
        s.p.y=s.p.y-0.2;
    }
    if (isKeyPressed(SDLK_LEFT))
    {
        s.p.x=s.p.x-0.2;
    }
    if (isKeyPressed(SDLK_RIGHT))
    {
        s.p.x=s.p.x+0.2;
    }
    if (s.p.y<DIMSHIP/2)
    {
        s.p.y=DIMSHIP/2;
    }
    if (s.p.y>DIMWY-DIMSHIP/2)
    {
        s.p.y=DIMWY-DIMSHIP/2;
    }
     if (s.p.x<DIMSHIP/2)
    {
        s.p.x=DIMSHIP/2;
    }
    if (s.p.x>DIMWX-DIMSHIP/2)
    {
        s.p.x=DIMWX-DIMSHIP/2;
    }
    for (i=0;i<w.nb;i++)
    {
        if (w.M[i].p.y>DIMWY)
        {
            w.M[i].vivant=false;
        }
    }
    for (k=0;k<w.nbe;k++)
    {
            if (w.E[k].vivant)
            {
                Tirage_Bonus(w,w.E[k]);
                for (l=0;l<w.nb;l++)
                {
                        if (w.M[l].vivant)
                        {
                            if (    (w.M[l].p.x>=w.E[k].p.x-DIMENEMY/2)
                                &&  (w.M[l].p.y>=w.E[k].p.y-DIMENEMY/2)
                                &&  (w.M[l].p.x<=w.E[k].p.x+DIMENEMY/2)
                                &&  (w.M[l].p.y<=w.E[k].p.y+DIMENEMY/2))
                            {
                                w.M[l].vivant=false;
                                w.E[k].vivant=false;
                                Score1(w);
                            }
                            if (w.M[l].p.y>DIMWY)
                            {
                                w.M[l].vivant=false;
                            }
                            if (w.E[k].p.y<0)
                            {
                                w.E[k].vivant=false;
                            }
                        }
                }
                if (    (collisionEnemy(w.E[k],make_vec2(s.p.x-DIMSHIP/2,s.p.y-DIMSHIP/2)))
                    ||  (collisionEnemy(w.E[k],make_vec2(s.p.x+DIMSHIP/2,s.p.y-DIMSHIP/2)))
                    ||  (collisionEnemy(w.E[k],make_vec2(s.p.x-DIMSHIP/2,s.p.y+DIMSHIP/2)))
                    ||  (collisionEnemy(w.E[k],make_vec2(s.p.x+DIMSHIP/2,s.p.y+DIMSHIP/2))))
                    {
                        if (!s.Invincible)
                        {
                            w.E[k].vivant=false;
                            Vies(s);
                            Invincible(s);
                            s.p=make_vec2(DIMWX/2,25);
                        }
                    }
            }
            else
            {
                for (m=0;m<w.nbme;m++)
                {
                    if (w.Me[m].p.x==w.E[k].p.x)
                        w.Me[m].vivant=false;
                }
            }
    }
    for (i=0;i<w.nbme;i++)
    {
        if (w.Me[i].vivant)
        {
            if (    (w.Me[i].p.x>=s.p.x-DIMSHIP/2)
                &&  (w.Me[i].p.y>=s.p.y-DIMSHIP/2)
                &&  (w.Me[i].p.x<=s.p.x+DIMSHIP/2)
                &&  (w.Me[i].p.y<=s.p.y+DIMSHIP/2))
            {
                if (!s.Invincible)
                {
                    w.Me[i].vivant=false;
                    Vies(s);
                    Invincible(s);
                    s.p=make_vec2(DIMWX/2,25);
                }
            }
        }
    }
    if ((w.Score>=2000)&&(w.Score<5000))
    {
        w.B[0].vivant=true;
    }
    if ((w.Score>=20000)&&(w.Score<30000))
    {
        w.B[1].vivant=true;
    }
    if (w.Score>=70000)
    {
        w.B[2].vivant=true;
    }
    for (i=0;i<w.nbB;i++)
    {
        if (w.B[i].vivant)
        {
            if ((elapsedTime()-w.B[i].time)>=2)
            {
                //Bossmove(w);
                x=irand(DIMBOSSX/2,DIMWX-DIMBOSSX);
                y=irand(DIMWY/3+DIMBOSSY/2,DIMWY-30-DIMBOSSY/2);
                w.B[i].p.x=x;
                w.B[i].p.y=y;
                w.B[i].time=elapsedTime();
            }
        }
    }
    for (i=0;i<w.nbmb;i++)
    {
        if (w.Mb[i].p.y<0)
        {
            w.Mb[i].vivant=false;
        }
    }
    for (i=0;i<w.nbmb;i++)
    {
        if (w.Mb[i].vivant)
        {
            if (    (w.Mb[i].p.x>=s.p.x-DIMSHIP/2)
                &&  (w.Mb[i].p.y>=s.p.y-DIMSHIP/2)
                &&  (w.Mb[i].p.x<=s.p.x+DIMSHIP/2)
                &&  (w.Mb[i].p.y<=s.p.y+DIMSHIP/2))
            {
                if (!s.Invincible)
                {
                    w.Mb[i].vivant=false;
                    Vies(s);
                    Invincible(s);
                    s.p=make_vec2(DIMWX/2,25);
                }
            }
        }
    }
    for (i=0;i<w.nbms;i++)
    {
        if ((w.Ms[i].p.y<0)||(w.Ms[i].p.y>DIMWY)||(w.Ms[i].p.x<0)||(w.Ms[i].p.x>DIMWX))
        {
            w.Ms[i].vivant=false;
        }
    }
    for (i=0;i<w.nbms;i++)
    {
        if (w.Ms[i].vivant)
        {
            if ((collisionMuniSpecial(make_vec2(w.Ms[i].p.x-DIM_MUNITION_BOSS_SPECIAL_X/2,w.Ms[i].p.y-DIM_MUNITION_BOSS_SPECIAL_Y/2),s))
            || (collisionMuniSpecial(make_vec2(w.Ms[i].p.x-DIM_MUNITION_BOSS_SPECIAL_X/2,w.Ms[i].p.y+DIM_MUNITION_BOSS_SPECIAL_Y/2),s))
            || (collisionMuniSpecial(make_vec2(w.Ms[i].p.x+DIM_MUNITION_BOSS_SPECIAL_X/2,w.Ms[i].p.y-DIM_MUNITION_BOSS_SPECIAL_Y/2),s))
            || (collisionMuniSpecial(make_vec2(w.Ms[i].p.x+DIM_MUNITION_BOSS_SPECIAL_X/2,w.Ms[i].p.y+DIM_MUNITION_BOSS_SPECIAL_Y/2),s))
            || (collisionShip(w.Ms[i],make_vec2(s.p.x-DIMSHIP/2,s.p.y-DIMSHIP/2)))
            || (collisionShip(w.Ms[i],make_vec2(s.p.x-DIMSHIP/2,s.p.y+DIMSHIP/2)))
            || (collisionShip(w.Ms[i],make_vec2(s.p.x+DIMSHIP/2,s.p.y-DIMSHIP/2)))
            || (collisionShip(w.Ms[i],make_vec2(s.p.x+DIMSHIP/2,s.p.y+DIMSHIP/2))))
            {
                if (!s.Invincible)
                {
                    w.Ms[i].vivant=false;
                    Vies(s);
                    Vies(s);
                    Invincible(s);
                    s.p=make_vec2(DIMWX/2,25);
                }
            }
        }
    }
    for (i=0;i<w.nbB;i++)
    {
        if (w.B[i].vivant)
        {
            if ((collisionBoss(w.B[i],make_vec2(s.p.x-DIMSHIP/2,s.p.y-DIMSHIP/2)))
            || (collisionBoss(w.B[i],make_vec2(s.p.x+DIMSHIP/2,s.p.y-DIMSHIP/2)))
            || (collisionBoss(w.B[i],make_vec2(s.p.x-DIMSHIP/2,s.p.y+DIMSHIP/2)))
            || (collisionBoss(w.B[i],make_vec2(s.p.x+DIMSHIP/2,s.p.y+DIMSHIP/2))))
            {
                if (!s.Invincible)
                {
                    Vies(s);
                    Invincible(s);
                    s.p=make_vec2(DIMWX/2,25);
                }
            }
        }
    }
    for (i=0;i<w.nb;i++)
    {
        if (w.M[i].vivant)
        {
            for (j=0;j<w.nbB;j++)
            {
                if (w.B[j].vivant)
                {
                    //cout<<w.B[i].vie<<endl;
                    if ((w.M[i].p.x<=w.B[j].p.x+DIMBOSSX/2)
                    && (w.M[i].p.x>=w.B[j].p.x-DIMBOSSX/2)
                    && (w.M[i].p.y<=w.B[j].p.y+DIMBOSSY/2)
                    && (w.M[i].p.y>=w.B[j].p.y-DIMBOSSY/2))
                    {
                        w.M[i].vivant=false;
                        VieBoss(w.B[j]);
                        //w.variablei-=VIEBOSS/500;
                        //printBoss(w,"colls");
                    }
                }
            }
        }
    }
    for (i=0;i<w.nbmbc;i++)
    {
        if (    (w.Mbc[i].p.x>=s.p.x-DIMSHIP/2)
                &&  (w.Mbc[i].p.y>=s.p.y-DIMSHIP/2)
                &&  (w.Mbc[i].p.x<=s.p.x+DIMSHIP/2)
                &&  (w.Mbc[i].p.y<=s.p.y+DIMSHIP/2))
                {
                    if (!s.Invincible)
                    {
                        Vies(s);
                        Invincible(s);
                        s.p=make_vec2(DIMWX/2,25);
                    }
                }
    }
    for (i=0;i<w.nbB;i++)
        {
            BossVivant(w,w.B[i]);
        }
    if (elapsedTime()-s.time>=3)
    {
        s.Invincible=false;
    }
    for (i=0;i<w.nbBn;i++)
    {
        if (w.Bn[i].vivant)
        {
            if (w.Bn[i].p.y<0)
            {
                w.Bn[i].vivant=false;
            }
            if ((collisionBonus(make_vec2(w.Bn[i].p.x-DIMSHIP/2,w.Bn[i].p.y-DIMSHIP/2),s))
            ||  (collisionBonus(make_vec2(w.Bn[i].p.x-DIMSHIP/2,w.Bn[i].p.y+DIMSHIP/2),s))
            ||  (collisionBonus(make_vec2(w.Bn[i].p.x+DIMSHIP/2,w.Bn[i].p.y-DIMSHIP/2),s))
            ||  (collisionBonus(make_vec2(w.Bn[i].p.x+DIMSHIP/2,w.Bn[i].p.y+DIMSHIP/2),s)))
            {
                w.Bn[i].vivant=false;
                if (s.LVL<3)
                {
                    s.LVL++;
                }
            }
        }
    }
    Stage(w,s);
}
//Test si le ship est vivant

void Vivant(Spaceship & s)
{
    if (s.vies<=0)
    {
        s.vivant=false;
    }
}
/*void affiche_controles(World & w)
{
    float e=elapsedTime();
    int x,y;
    mousePos(x,y);
    do
    {
        image_draw(w.MenuControles,150,300,DIM_MENU_UI_X,DIM_MENU_UI_Y);
    }while ((elapsedTime()-e)<5);
}*/
/*void affiche_difficulty(World w)
{
    image_draw(w.MenuDifficulty,150,300,DIM_MENU_UI_X,DIM_MENU_UI_Y);
}*/
/*void select_difficulty(World & w,int & VIEMAXBOSS,bool & difficulty)
{
    int x,y;
    mousePos(x,y);
    do
    {
        affiche_difficulty(w);
    }while (isMousePressed(SDL_BUTTON_LEFT));
    if ((x>=150)&&(x<=150+DIM_MENU_UI_X)&&(y>=300)&&(y<=300+DIM_MENU_UI_Y/3)&&(isMousePressed(SDL_BUTTON_LEFT)))
        {
            VIEMAXBOSS=500;
            difficulty=false;
        }
        if ((x>=150)&&(x<=150+DIM_MENU_UI_X)&&(y>=300+DIM_MENU_UI_Y/3)&&(y<=300+(2*DIM_MENU_UI_Y)/3)&&(isMousePressed(SDL_BUTTON_LEFT)))
        {
            VIEMAXBOSS=300;
            difficulty=false;
        }
        if ((x>=150)&&(x<=150+DIM_MENU_UI_X)&&(y>=300+(2*DIM_MENU_UI_Y)/3)&&(y<=300+DIM_MENU_UI_Y)&&(isMousePressed(SDL_BUTTON_LEFT)))
        {
            VIEMAXBOSS=100;
            difficulty=false;
        }
}*/
/*bool GameWon(World w)
{
    if (w.Score>=120000)
    {
        return true;
    }
    else
    {
        return false;
    }
}*/
int main(int , char** )
{
    struct World w;
    struct Munition m;
    struct Spaceship s;
    struct Enemy en;
    struct Boss b;
    int VIEMAXBOSS=100;
    bool stop=false;
	winInit("Star Protector", DIMWX, DIMWY);
    backgroundColor( 0, 0, 0 );
    s=initSpaceship();
    initWorld(w);
    int i;
    for (i=0;i<w.nbmbc;i++)
    {
        w.Mbc[i].vivant=false;
    }
    setKeyRepeatMode(true);
    float e=elapsedTime();
    float e2=elapsedTime();
    float e3=elapsedTime();
    float e4=elapsedTime();
    float e5=elapsedTime();
    float e20=elapsedTime();
    //pour le debug sinon mettre en commentaire la ligne suivante :
    //w.B[0].vivant=true;
    //printBoss(w,"init ");
    bool nouvelle_partie=false;
    bool scenario=false;
   /* while((!stop)&&(!scenario))
    {
        winClear();
        image_draw(w.Scenario,0,0,DIMWX,DIMWY);
        if ((elapsedTime()-e)>=15)
        {
            scenario=true;
        }
        stop=winDisplay();
    }*/
    initBoss(w,VIEMAXBOSS);
    w.B[2].vie=300;
   /* while((!stop)&&(!nouvelle_partie))
    {
        winClear();
        image_draw(w.Scenario,0,0,DIMWX,DIMWY);
        if ((elapsedTime()-e20)>=15)
        {
            image_draw(w.bg,0,0,DIMWX,DIMWY);
            image_draw(w.Title,150,650,400,80);
            image_draw(w.MenuUI,150,300,DIM_MENU_UI_X,DIM_MENU_UI_Y);
            int x,y;
            mousePos(x,y);
            if ((x>=150)&&(x<=150+DIM_MENU_UI_X)&&(y>=300)&&(y<=300+DIM_MENU_UI_Y/3)&&((isMousePressed(SDL_BUTTON_LEFT))||(difficulty)))
            {
                difficulty=true;
                select_difficulty(w,VIEMAXBOSS,difficulty);
            }
            if ((x>=150)&&(x<=150+DIM_MENU_UI_X)&&(y>=300+DIM_MENU_UI_Y/3)&&(y<=300+(2*DIM_MENU_UI_Y)/3)&&(isMousePressed(SDL_BUTTON_LEFT)))
            {
                nouvelle_partie=true;
            }
            if ((x>=150)&&(x<=150+DIM_MENU_UI_X)&&(y>=300+(2*DIM_MENU_UI_Y)/3)&&(y<=300+DIM_MENU_UI_Y)&&(isMousePressed(SDL_BUTTON_LEFT)))
            {
                affiche_controles(w);
            }
        }
        stop=winDisplay();
    }*/
    //initBoss(w,VIEMAXBOSS);
	while( !stop )
    {
        winClear();
        //Affiche scenario
        image_draw(w.Scenario,0,0,DIMWX,DIMWY);
        //affiche le menu avec les contrôles et le bouton nouvelle partie
        if (((elapsedTime()-e20)>=15)&&(!nouvelle_partie))
        {
            image_draw(w.bg,0,0,DIMWX,DIMWY);
            image_draw(w.Title,150,650,400,80);
            image_draw(w.MenuUI,150,300,DIM_MENU_UI_X,DIM_MENU_UI_Y);
            int x,y;
            mousePos(x,y);
            if ((x>=150)&&(x<=150+DIM_MENU_UI_X)&&(y>=300+DIM_MENU_UI_Y/3)&&(y<=300+(2*DIM_MENU_UI_Y)/3)&&(isMousePressed(SDL_BUTTON_LEFT)))
            {
                nouvelle_partie=true;
            }
        }
        //Le bouton nouvelle partie a été choisi donc le jeu commence
        if (nouvelle_partie)
        {
            draw(w,s,VIEMAXBOSS);
            //Met le jeu en pause
            if (isKeyPressed(SDLK_p))
            {
                color(0,255,0);
                print(200,250,"Appuyer sur la barre Espace pour continuer la partie");
                pressSpace();
            }
            else
            {
                update(w,s);
                //le ship tire
                if (elapsedTime()-e>=0.1)
                    {
                        addMunition(w,s);
                        e=elapsedTime();
                    }
                //les ennemis apparaissent
                if ((elapsedTime()-e2>=(irand(1,5)))&&(Stage1(w)||Stage2(w)||Stage3(w)))
                {
                    addEnemy(w);
                    e2=elapsedTime();
                }
                // les ennemis tirent
                for (i=0;i<w.nbe;i++)
                {
                    if ((elapsedTime()-w.E[i].time>=(frand(0.5,3.0)))&&(Stage1(w)||Stage2(w)||Stage3(w)))
                    {
                        addMunitionEnemy(w,w.E[i]);
                        w.E[i].time=elapsedTime();
                    }
                }
                //si le boss est vivant il tire
                if (elapsedTime()-e3>=(irand(1,4)))
                {
                    if (w.B[0].vivant)
                    {
                        addMunitionBoss(w,w.B[0]);
                        e3=elapsedTime();
                    }
                    if (w.B[1].vivant)
                    {
                        addMunitionBoss(w,w.B[1]);
                        e3=elapsedTime();
                    }
                    if (w.B[2].vivant)
                    {
                        addMunitionBoss(w,w.B[2]);
                        e3=elapsedTime();
                    }
                }
                // si le boss est vivant il tire sa munition spéciale
                if (elapsedTime()-e4>=3)
                {
                    if (w.B[0].vivant)
                    {
                        addMunitionBossSpecial(w,w.B[0]);
                        e4=elapsedTime();
                    }
                    if (w.B[1].vivant)
                    {
                        addMunitionBossSpecial(w,w.B[1]);
                        e4=elapsedTime();
                    }
                    if (w.B[2].vivant)
                    {
                        addMunitionBossSpecial(w,w.B[2]);
                        e4=elapsedTime();
                    }
                }
                //toutes les 4 secondes le boss utilise son super coup : un tir circulaire
                for (i=0;i<w.nbB;i++)
                {
                    if (w.B[i].vivant)
                    {
                        if (elapsedTime()-e5>=4)
                        {
                            //CreeTableauTirCirculaire(w);
                            CreerTableauCirculaire(w);
                            e5=elapsedTime();
                        }
                    }
                }
                //verifie si le ship est vivant
                Vivant(s);
                //s'il ne l'est pas le joueur a perdu et peut relancer une partie mais pour une raison qui m'échappe encore, le jeu devient très lent lorsque la partie est recommencée.
                if (!s.vivant)
                {
                    color(255,0,0);
                    print(DIMWX/3,DIMWY/2,"You failed the mission ...");winDisplay();delay(2000);
                    color(0,0,0);
                    rectangleFill(0,DIMWY/2-20,DIMWX,(DIMWY/2+50));
                    color(255,0,0);
                    print(DIMWX/4,DIMWY/2,"Appuyez sur espace pour relancer une nouvelle partie");winDisplay();
                    pressSpace();
                    s=initSpaceship();
                    initWorld(w);
                    initBoss(w,VIEMAXBOSS);
                    for (i=0;i<w.nbmbc;i++)
                    {
                        w.Mbc[i].vivant=false;
                    }
                }
                //lorsque le boss final est tué le joueur a gagné
                if (w.Score>=120000)
                {
                    image_draw(w.VictoryScreen,0,0,DIMWX,DIMWY);
                }
            }
        }
        stop = winDisplay();
    }
    winQuit();
	return 0;
}
