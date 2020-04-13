#include <Grapic.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace grapic;
using namespace std;

const int DIMWX=420;
const int DIMWY=800;
const int MAXB=3;
const int MAXBRIQUES=1000;
const float dt=0.03;
const int largeur=40;
const int longueur=80;


struct Vec2
{
    float x,y;
};

struct Bonus
{
    int bonusrestant;
};

struct Particule
{
    Vec2 position,vitesse,F;
    float masse,rayon;
    bool present=true;
};

struct Particules
{
    Particule tab[MAXB];
    int nb_particule;
};

struct barre
{
    Vec2 p;
    float longeur,largeur;
};

struct brique
{
    Vec2 p;
    float longeur,largeur;
    bool vivant;
    int nb_vie;
};

struct briques
{
    brique tab[MAXBRIQUES];
    int nb_briques;
};

Vec2 make_Vecteur (float x,float y)
{
    struct Vec2 c;
    c.x=x;
    c.y=y;
    return c;
}

Vec2 operator+(Vec2 a,Vec2 b)
{
    Vec2 c;
    c.x=a.x+b.x;
    c.y=a.y+b.y;
    return c;
}

Vec2 operator-(Vec2 a,Vec2 b)
{
    Vec2 c;
    c.x=a.x-b.x;
    c.y=a.y-b.y;
    return c;
}

Vec2 operator*(float lambda,Vec2 a)
{
    Vec2 d;
    d.x=a.x*lambda;
    d.y=a.y*lambda;
    return d;
}

Vec2 operator*(Vec2 a,Vec2 b)
{
    Vec2 c;
    c.x=a.x*b.x+a.y*b.y;
    c.y=a.x*b.y-a.y*b.x;
    return c;
}

Vec2 operator/(Vec2 a,float b)
{
    Vec2 c;
    c.x=a.x/b;
    c.y=a.y/b;
    return c;
}

Vec2 make_complex_exp(float r,float theta_deg)
{
    float theta_rad=theta_deg*M_PI/180;
    Vec2 c;
    c.x=r*cos(theta_rad);
    c.y=r*sin(theta_rad);
    return c;
}
void initBonus(Bonus &b)
{
    b.bonusrestant=MAXB-1;
}

void initParticule(Particule& part, Vec2 position, barre b)
{
    part.position.x=b.p.x;
    part.position.y=DIMWY/8;
    part.masse=1;
    part.F.x=0;
    part.F.y=0;
    part.vitesse.x=position.x;
    part.vitesse.y=position.y;
    part.rayon=DIMWX/50.f;
    part.present=true;
}

void initParticules1(Particules& part, barre b)
{
    Vec2 position;
    part.nb_particule=0;
    position=make_Vecteur(0,10);
    initParticule(part.tab[0],position, b);
    part.nb_particule++;
}

void initParticules2(Particules& part, barre b)
{
    Vec2 position;
    position=make_Vecteur(0,10);
    initParticule(part.tab[part.nb_particule],position, b);
    part.nb_particule++;
}

void initBarre(barre& b)
{
    b.largeur=10;
    b.longeur=60;
    b.p.x=DIMWX/2;
    b.p.y=DIMWY/10;
}

brique initBrique(brique b, Vec2 position)
{
    b.largeur=largeur;
    b.longeur=longueur;
    b.p.x=(b.longeur/2)+position.x;
    b.p.y=position.y-b.largeur/2;
    b.nb_vie=1;
    return b;
}

brique initBriquePlusieursVie(brique b, Vec2 position)
{
    b.largeur=largeur;
    b.longeur=longueur;
    b.p.x=(b.longeur/2)+position.x;
    b.p.y=position.y-b.largeur/2;
    b.nb_vie=3;
    return b;
}

void initBriques(briques& b)
{
    int i;
    int j;
    Vec2 position;
    b.nb_briques=0;

    for(j=DIMWY;j>=DIMWX;j=j-(largeur)-5)
    {
        for(i=0;i<=DIMWX-longueur;i=i+(longueur+5))
        {
            position=make_Vecteur(i,j);
            b.tab[b.nb_briques]=initBrique(b.tab[b.nb_briques],position);
            b.nb_briques++;
        }
    }
}

void initBriquesStage1(briques& b)
{
   int i;
    int j;
    Vec2 position;
    b.nb_briques=0;
    for(j=DIMWY;j>=DIMWX;j=j-(largeur+10)*2)
    {
        for(i=0;i<=DIMWX-longueur;i=i+(longueur+5)*2)
        {
            position=make_Vecteur(i,j);
            b.tab[b.nb_briques]=initBrique(b.tab[b.nb_briques],position);
            b.nb_briques++;
        }
    }
}

void initBriquesPlusieursVie(briques& b)
{
    int i;
    int j;
    int x=0;
    Vec2 position;
    b.nb_briques=0;

    for(j=DIMWY;j>=DIMWX;j=j-(largeur)-5)
    {
        for(i=0;i<=DIMWX-longueur;i=i+(longueur+5))
        {
            if(x%2 == 0)
            {
                position=make_Vecteur(i,j);
                b.tab[b.nb_briques]=initBrique(b.tab[b.nb_briques],position);
                b.nb_briques++;
            }
            else
            {
                position=make_Vecteur(i,j);
                b.tab[b.nb_briques]=initBriquePlusieursVie(b.tab[b.nb_briques],position);
                b.nb_briques++;
            }
        }
        x++;
    }
}

void drawParticule(Particule part)
{
    color(0,0,150);
    circleFill(part.position.x,part.position.y,part.rayon);
}

void drawParticules(Particules& part)
{
    int i;
    for(i=0;i<part.nb_particule;i++)
    {
        if(part.tab[i].present) drawParticule(part.tab[i]);
    }
}

void drawBarre(barre b)
{
    color(150,150,150);
    rectangleFill(b.p.x-b.longeur/2,b.p.y-b.largeur/2,b.p.x+b.longeur/2,b.p.y+b.largeur/2);
}


void partUpdate(Particule& part)
{
    part.position=part.position+dt*part.vitesse;
    part.vitesse=(dt*part.F)/part.masse+part.vitesse;
}

void partsUpdate(Particules& part)
{
    int i;
    for(i=0;i<part.nb_particule;i++)
    {
        if(part.tab[i].present) partUpdate(part.tab[i]);
    }
}

void partcollisonbords(Particule& part)
{
    if(part.position.y>DIMWY-part.rayon)
    {
        part.vitesse=make_Vecteur(part.vitesse.x,-part.vitesse.y);
    }
    else
    {
            if(part.position.x>DIMWX-part.rayon || part.position.x<part.rayon)
        {
            part.vitesse=make_Vecteur(-part.vitesse.x,part.vitesse.y);
        }
            else
        {
                if(part.position.y<0)
            {
                part.present=false;
            }
        }

    }
}

void partscollisionbords(Particules& part)
{
    int i;
    for(i=0;i<part.nb_particule;i++)
    {
        partcollisonbords(part.tab[i]);
    }
}

void collisionbarre(Particule& part, barre b)
{
   if(part.position.y-part.rayon<b.p.y+b.largeur/2 &&
       part.position.y+part.rayon>b.p.y-b.largeur/2 &&
       part.position.x-part.rayon<b.p.x+b.longeur/2 &&
       part.position.x+part.rayon>b.p.x-b.longeur/2)
    {
        float coeffdex;
        Vec2 vecdex={-10,0};

        if(part.position.y<b.p.y-b.largeur/2 || (part.position.y>b.p.y+b.largeur/2))
        {
            coeffdex=(b.p.x-part.position.x)/b.longeur;
            part.position=part.position+make_Vecteur(0,part.rayon);
            part.vitesse=make_Vecteur(0+vecdex.x*coeffdex,-part.vitesse.y);
        }
        else
        {
            if(part.position.x<b.p.x-b.longeur/2)
            {
                part.position=part.position-make_Vecteur(part.rayon,0);
                part.vitesse=make_Vecteur(-part.vitesse.x,part.vitesse.y);
            }
            if(part.position.x>b.p.x+b.longeur/2)
            {
                part.position=part.position+make_Vecteur(part.rayon,0);
                part.vitesse=make_Vecteur(-part.vitesse.x,part.vitesse.y);
            }
        }
    }
}

void collisionsbarre(Particules& part, barre b)
{
    int i;
    for(i=0;i<part.nb_particule;i++)
    {
        if(part.tab[i].present && part.tab[i].position.y<b.p.y+part.tab[i].rayon+b.largeur) collisionbarre(part.tab[i], b);
    }
}
void barreUpdate(barre& b)
{
    if(isKeyPressed(SDLK_LEFT))   b.p.x=b.p.x-0.4;
    if(isKeyPressed(SDLK_RIGHT))   b.p.x=b.p.x+0.4;
    if(b.p.x<=b.longeur/2)   b.p.x=b.longeur/2;
    if(b.p.x>=DIMWX-b.longeur/2)   b.p.x=DIMWX-b.longeur/2;
}

void briqueUpdate(Particule& part,brique &b)
{
    if(part.position.y-part.rayon<b.p.y+b.largeur/2 &&
       part.position.y+part.rayon>b.p.y-b.largeur/2 &&
       part.position.x-part.rayon<b.p.x+b.longeur/2 &&
       part.position.x+part.rayon>b.p.x-b.longeur/2)
    {
        if(part.position.y<b.p.y-b.largeur/2)
        {
            part.position=part.position-make_Vecteur(0,part.rayon);
            part.vitesse=make_Vecteur(part.vitesse.x,-part.vitesse.y);
        }
        else
        {
                if(part.position.y>b.p.y+b.largeur/2)
            {
                part.position=part.position+make_Vecteur(0,part.rayon);
                part.vitesse=make_Vecteur(part.vitesse.x,-part.vitesse.y);
            }
            else
            {
                if(part.position.x<b.p.x-b.longeur/2)
                {
                    part.position=part.position-make_Vecteur(part.rayon,0);
                    part.vitesse=make_Vecteur(-part.vitesse.x,part.vitesse.y);
                }
                if(part.position.x>b.p.x+b.longeur/2)
                {
                    part.position=part.position+make_Vecteur(part.rayon,0);
                    part.vitesse=make_Vecteur(-part.vitesse.x,part.vitesse.y);
                }
            }

        }

        b.nb_vie--;
    }
}

void drawBrique(brique b)
{
    if(b.nb_vie == 1)
    {
        color(255,255,255);
    rectangleFill(b.p.x-b.longeur/2,b.p.y-b.largeur/2,b.p.x+b.longeur/2,b.p.y+b.largeur/2);
    }
    if(b.nb_vie == 2)
    {
        color(125,125,125);
    rectangleFill(b.p.x-b.longeur/2,b.p.y-b.largeur/2,b.p.x+b.longeur/2,b.p.y+b.largeur/2);
    }
    if(b.nb_vie == 3)
    {
        color(0,0,0);
    rectangleFill(b.p.x-b.longeur/2,b.p.y-b.largeur/2,b.p.x+b.longeur/2,b.p.y+b.largeur/2);
    }
}

void briquesUpdate(Particules& part,briques &b)
{
    int i, j;
    for(j=0;j<part.nb_particule;j++)
    {
        if(part.tab[j].present)
        {
        for(i=0;i<=b.nb_briques;i++)
        {
            if(b.tab[i].nb_vie > 0)
            {
            briqueUpdate(part.tab[j],b.tab[i]);
            }
        }
        }
    }

}

void drawBriques(briques b)
{
    int i;
    for(i=0;i<=b.nb_briques;i++)
        {
            if(b.tab[i].nb_vie > 0)
            drawBrique(b.tab[i]);
        }
}

bool briquesvivantes(briques b)
{
    int i;
    for(i=0;i<b.nb_briques;i++)
        {
            if(b.tab[i].nb_vie > 0)
            return true;
        }
    return false;
}

void win(Particules& part)
{
    int i;
    color(0,0,0);
    print(DIMWX/2-55,DIMWY/2,"YOU WIN");
    for(i=0;i<part.nb_particule;i++)
    {
        part.tab[i].vitesse=make_Vecteur(0,0);
    }
}

void lose(Particules& part)
{int i;
    color(0,0,0);
    print(DIMWX/2-55,DIMWY/2,"GAME OVER");
    for(i=0;i<part.nb_particule;i++)
    {
        part.tab[i].vitesse=make_Vecteur(0,0);
    }
}

void niveau(int& x, briques& b,Particules& part, Bonus& bo, barre ba)
{
    if(x==1)
    {
        initParticules1(part,ba);
        initBriques(b);
        x++;
        bo.bonusrestant=MAXB-1;
    }
    else
    {
        if(x==2)
    {
        initParticules1(part,ba);
        initBriquesPlusieursVie(b);
        x++;
        bo.bonusrestant=MAXB-1;
    }
    else
    {
        if(x==3) win(part);
    }
    }

}

bool presentballe(Particules part)
{
    int i;
    for(i=0;i<part.nb_particule;i++)
    {
        if(part.tab[i].present)
        return true;
    }
    return false;
}

void bonus(Particules& part, Bonus& b, barre ba)
{
    setKeyRepeatMode(false);
    if(elapsedTime()>10 && isKeyPressed(32) && b.bonusrestant>0)
    {
        initParticules2(part,ba);
        b.bonusrestant--;
    }
    setKeyRepeatMode(true);
}

void affichBonus(Bonus b, Particules part)
{
    color(0,0,0);
    print(25,25,"BONUS RESTANT :             press space");
        color(255,0,0);
        print(200,25,MAXB-part.nb_particule);
}

void Lemenu()
{
    bool test=false;
    while( !test )
    {
         winClear();


         backgroundColor(0,255,255);
         color(0,0,0);
         print(DIMWX/2-90,DIMWY/2,"Press space to start");
         if(isKeyPressed(32))
         {
             test=true;
         }
         winDisplay();
    }
}
void collisionbouboule(Particules& part)
{
    Vec2 a;
    float distance,vtx1, vtx2, vty1, vty2;
   for(int i=0;i<=part.nb_particule;i++)
    {
        for(int j=0;j<=part.nb_particule;j++)
        {
            if(part.tab[i].present && part.tab[j].present)
            {
                distance=sqrt(pow(part.tab[i].position.x-part.tab[j].position.x,2)+pow(part.tab[i].position.y-part.tab[j].position.y,2));
                if(j!=i && distance<part.tab[i].rayon+part.tab[j].rayon)
                {

                        part.tab[i].position=part.tab[i].position-(dt*part.tab[i].vitesse);
                        part.tab[j].position=part.tab[j].position-(dt*part.tab[j].vitesse);
                        a=part.tab[j].position-part.tab[i].position;

                        vtx1=(part.tab[j].vitesse.y*a.y*a.x-part.tab[i].vitesse.y*a.y*a.x+part.tab[i].vitesse.x*a.y*a.x+part.tab[j].vitesse.x*a.y*a.x)/(a.x*a.x+a.y*a.y);
                        vty1=(part.tab[j].vitesse.y*a.y*a.y+part.tab[j].vitesse.x*a.y*a.x-part.tab[i].vitesse.x*a.y*a.x+part.tab[i].vitesse.y*a.x*a.x)/(a.x*a.x+a.y*a.y);
                        vtx2=(part.tab[i].vitesse.x*a.x*a.x-part.tab[j].vitesse.y*a.y*a.x+part.tab[i].vitesse.y*a.y*a.x+part.tab[j].vitesse.x*a.y*a.y)/(a.x*a.x+a.y*a.y);
                        vty2=(part.tab[i].vitesse.x*a.y*a.x+part.tab[i].vitesse.y*a.y*a.y-part.tab[j].vitesse.x*a.y*a.x+part.tab[j].vitesse.y*a.x*a.x)/(a.x*a.x+a.y*a.y);

                        part.tab[i].vitesse.x=vtx1;
                        part.tab[i].vitesse.y=vty1;
                        part.tab[j].vitesse.x=vtx2;
                        part.tab[j].vitesse.y=vty2;
                }
            }
        }
    }

}

void regulvitesse(Particules &part)
{
    for(int i=0;i<part.nb_particule;i++)
    {
        if(part.tab[i].present)
        {
            if(part.tab[i].vitesse.y >= 0 && part.tab[i].vitesse.y != 10)
            {
                part.tab[i].vitesse.y=10;
            }
            if(part.tab[i].vitesse.y < 0 && part.tab[i].vitesse.y != -10)
            {
                part.tab[i].vitesse.y=-10;
            }
        }
    }
}

int main(int , char** )
{
    winInit("Casse Briques", DIMWX, DIMWY);
    backgroundColor(150,255,255,50);
    srand(time(NULL));
    Particules part;
    barre b;
    Bonus bonu;
    brique br;
    initBonus(bonu);
    int x=1;
    briques brs;
    color(0,0,0);
    initBarre(b);
    initParticules1(part, b);
    initBriquesStage1(brs);
    bool stop=false;
    setKeyRepeatMode(false);
    Lemenu();
    setKeyRepeatMode(true);
	while( !stop )
    {
        winClear();
        drawParticules(part);
        drawBarre(b);
        drawBriques(brs);
        partsUpdate(part);
        partscollisionbords(part);
        collisionsbarre(part,b);
        collisionbouboule(part);
        regulvitesse(part);
        barreUpdate(b);
        if(briquesvivantes(brs))
        {
            briquesUpdate(part,brs);
        }
        else niveau(x,brs,part,bonu,b);
        affichBonus(bonu,part);
        if(!presentballe(part)) lose(part);
        else bonus(part, bonu, b);
        stop = winDisplay();
    }
    winQuit();
	return 0;
}

