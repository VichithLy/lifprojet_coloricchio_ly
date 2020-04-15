#include <Grapic.h>
#include <iostream>
#include <math.h>
using namespace std;
using namespace grapic;

const int MAX_PART=200;
const int DIMW_C = 800;
const int DIMW_L =500;
const float FRICTION= 1;
const int MAX_PARTICULES=10;
const int RAYON_PART=10;
const float K=40;


struct Vec2
{
    float x;
    float y;
};

struct Particules
{
    struct Vec2 position;
    float masse;
    struct Vec2 vitesse;
    struct Vec2 force;
};

struct spring
{
    float lo;
    float l;
};

struct objectif
{
    Vec2 obj;
    int rayon;
};

struct aim
{
    Vec2 visee;
    Vec2 depart;
    float rayon;
    spring s;

};

struct world
{
    int nbr;
    Particules T[MAX_PART];
    Particules balle;
    float rayon_balle;
    aim a;
    objectif o;
    Menu m;
};


Vec2 make_Vec2(float x, float y)
{
    Vec2 c;
    c.x=x;
    c.y=y;
    return c;
}

Vec2 make_Vec2_exp(float r, float theta)// théta en degré
{
    Vec2 c;
    c.x=r*cos(theta * (M_PI/180));
    c.y=r*sin(theta* (M_PI/180));
    return c;
}

float module(Vec2 v)
{
    return sqrt((v.x*v.x)+(v.y*v.y));
}


Vec2 operator+(Vec2 a, Vec2 b)
{
    Vec2 c;
    c.x=a.x+b.x;
    c.y=a.y + b.y;
    return c;
}


Vec2 operator-(Vec2 a, Vec2 b)
{
    Vec2 c;
    c.x=a.x-b.x;
    c.y=a.y-b.y;
    return c;
}

Vec2 operator* (float l,Vec2 a)
{
    Vec2 c;
    c.x=l*a.x;
    c.y=l*a.y;
    return c;
}
Vec2 operator* (Vec2 a,float l)
{
    Vec2 c;
    c.x=l*a.x;
    c.y=l*a.y;
    return c;
}

Vec2 operator* (Vec2 a , Vec2 b)
{
    Vec2 c;
    c.x=a.x*b.x-a.y*b.y;
    c.y=a.x*b.y+a.y*b.x;
    return c;
}

Vec2 operator/ (Vec2 a, float l)
{
    Vec2 p;
    p.x=a.x/l;
    p.y=a.y/l;
    return p;
}

Vec2 scale(Vec2 p,float cx, float cy,float lambda)
{
    Vec2 c;
    c=make_Vec2(cx,cy);
    return lambda*(p-c)+c;
}

Vec2 Rotate (Vec2 p, float cx, float cy, float theta)
{
    Vec2 c;
    c=make_Vec2(cx,cy);
    Vec2 r;
    r= ((p-c)*make_Vec2_exp(1,theta )+c);
    return r;
}

float distance(Vec2 a, Vec2 b)
{
    return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}

Vec2 Initposition(world w)
{
    Vec2 V;
    do
    {
        V.x=rand()%(DIMW_C-RAYON_PART*2)+RAYON_PART;
        V.y=rand()%(DIMW_L-RAYON_PART*2)+RAYON_PART;
    }
    while (V.x>(DIMW_C/2)-(75+RAYON_PART) && V.y<(75+RAYON_PART) && V.x<(DIMW_C/2)+(75+RAYON_PART));
    return V;
}

void Initworld(world &w)
{
    int i;
    w.nbr=MAX_PARTICULES;
    w.a.depart=make_Vec2(DIMW_C/2,0);
    w.a.rayon=60;
    for(i=0;i<w.nbr; i++)
    {
        w.T[i].masse=1;
        w.T[i].force=make_Vec2(0,0);
        w.T[i].position=Initposition(w);
        w.T[i].vitesse=make_Vec2((rand()%40)-20,(rand()%40)-20);
    }
    w.a.visee=make_Vec2_exp(w.a.rayon , 90)  + w.a.depart;
    w.a.s.lo=w.a.rayon;
    w.a.s.l=w.a.rayon;
    w.balle.force=make_Vec2(0,0);
    w.balle.masse=10;
    w.balle.position=w.a.visee;
    w.balle.vitesse=make_Vec2(0,0);
    w.rayon_balle=5;
    w.o.rayon=50;
    w.o.obj=make_Vec2(DIMW_C/2,DIMW_L);

}

int victoire(world w)
{
    float a;
    a=distance(w.balle.position,w.o.obj);
    if (a < (w.o.rayon))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int defaite(world w, int n)
{
    bool a=0;
    for (int i=0;i<w.nbr;i++)
    {
        if (distance(w.balle.position,w.T[i].position)<(w.rayon_balle+RAYON_PART))
        {
            a=1;
        }
        if (n==1)
        {
            if (w.balle.position.x>(DIMW_C/2)-150 && w.balle.position.x<(DIMW_C/2)+150 && w.balle.position.y<(DIMW_L/2)+6 && w.balle.position.y>(DIMW_L/2)-6)
            {
                a=1;
            }
        }
    }
    return a;

}

void vise(world &w)
{
    Vec2 V;
    float D;
    if ( isKeyPressed (SDLK_RIGHT))
    {
        w.a.visee=Rotate(w.a.visee, w.a.depart.x, w.a.depart.y ,-2);
        w.balle.position=w.a.visee;

    }
    if ( isKeyPressed (SDLK_LEFT))
    {
        w.a.visee=Rotate(w.a.visee, w.a.depart.x, w.a.depart.y, 2);
        w.balle.position=w.a.visee;
    }
    if ( isKeyPressed(SDLK_DOWN) && w.a.s.l>15)
    {
        D=w.a.s.l;
        V=w.balle.position-w.a.depart;
        w.a.s.l-=5;
        D=w.a.s.l/D;
        w.balle.position=V*D+w.a.depart;
    }
    if (isKeyPressed(SDLK_UP) && w.a.s.l<w.a.rayon)
    {
        D=w.a.s.l;
        V=w.balle.position-w.a.depart;
        w.a.s.l+=5;
        D=w.a.s.l/D;
        w.balle.position=V*D+w.a.depart;
    }
    if (isKeyPressed(SDLK_SPACE))
    {
        w.balle.force=-K*(w.a.s.l - w.a.s.lo)*(w.balle.position-w.a.depart)/module(w.balle.position-w.a.depart);
    }
}

void UpdateBalle (Particules &p, world w)
{
    if (p.position.x<RAYON_PART)
    {
        p.vitesse.x=-FRICTION*p.vitesse.x;
    }
    if (p.position.y<RAYON_PART)
    {
        p.vitesse.y=-FRICTION*p.vitesse.y;
    }
    if (p.position.y>DIMW_L-RAYON_PART)
    {
        p.vitesse.y=-FRICTION*p.vitesse.y;
    }
    if (p.position.x>DIMW_C-RAYON_PART)
    {
        p.vitesse.x=-FRICTION*p.vitesse.x;
    }
    p.position=p.position+0.2*p.vitesse;
    p.vitesse=p.vitesse+(0.1*p.force)/p.masse;
 }

void UpdatePart(Particules &p, world w)
{
    if(p.position.x>(DIMW_C/2)-(75+RAYON_PART) && p.position.y<(75+RAYON_PART) && (p.position.x<(DIMW_C/2)+(75+RAYON_PART)))
    {
        if (p.position.y<(70+RAYON_PART))
        {
            p.vitesse.x =-1 * p.vitesse.x;
        }
        else
        {
            p.vitesse.y = -1 * p.vitesse.y;
        }
    }
    if (p.position.x<RAYON_PART)
    {
        p.vitesse.x=-FRICTION*p.vitesse.x;
    }
    if (p.position.y<RAYON_PART)
    {
        p.vitesse.y=-FRICTION*p.vitesse.y;
    }
    if (p.position.y>DIMW_L-RAYON_PART)
    {
        p.vitesse.y=-FRICTION*p.vitesse.y;
    }
    if (p.position.x>DIMW_C-RAYON_PART)
    {
        p.vitesse.x=-FRICTION*p.vitesse.x;
    }
    p.position=p.position+0.2*p.vitesse;
    p.vitesse=p.vitesse+(1*p.force)/p.masse;
 }

void Update(world &w)
 {
    int i;
    for(i=0;i<w.nbr;i++)
    {
        UpdatePart(w.T[i], w);
    }
    if (w.balle.vitesse.x==0 && w.balle.vitesse.y==0)
    {
        vise(w);
    }

    UpdateBalle(w.balle, w);
    if (w.balle.force.x!=0 or w.balle.force.y!=0)
    {
        w.balle.force=make_Vec2(0,0);
    }
 }

void Draw(world w, int n)
{
    int i;
    for (i=0;i<w.nbr;i++)
    {
        color(15, 5, 107);
        circleFill(w.T[i].position.x,w.T[i].position.y,RAYON_PART);
    }
    color(255,0,0);
    circle(w.a.depart.x,w.a.depart.y,w.a.rayon);
    color(252, 93, 93);
    line(w.a.depart.x,w.a.depart.y,w.a.visee.x,w.a.visee.y);
    color(0,0,255);
    circleFill(w.balle.position.x,w.balle.position.y,w.rayon_balle);
    circleFill(w.o.obj.x,w.o.obj.y,w.o.rayon);
    Vec2 x=w.a.depart-make_Vec2_exp(75*sqrt(2),45);
    Vec2 y=w.a.depart+make_Vec2_exp(75*sqrt(2),45);
    rectangle(x.x,x.y,y.x,y.y);
    if (n>=1)
    {
        color(15, 5, 107);
        rectangleFill((DIMW_C/2)-150, (DIMW_L/2)-6, (DIMW_C/2)+150, (DIMW_L/2)+6);
    }
}

void Menue(world &w, int &n)
{
    menu_draw(w.m, 5,5, 120, 100);
    switch(menu_select(w.m))
    {
        case 0 : break;
        case 1 : n=0;Initworld(w); menu_setSelect(w.m,0); break;
        case 2 :
            {
                if (n<1)
                {
                    n++;
                }
                menu_setSelect(w.m,0);
                break;
            }
        case 3:
            {
                if (n>0)
                {
                    n--;
                }
                menu_setSelect(w.m,0);
                break;
            }
    }
}


int main(int , char **)
{
    srand(time(NULL));
    int niveau = 0;
    world dat;

    menu_add( dat.m, "0");
    menu_add( dat.m, "Restart");
    menu_add( dat.m, "Niveau suivant");
    menu_add( dat.m, "Niveau precedent");

    int vic = 0;
    int def = 0;
    bool stop=false;
    winInit("Particles", DIMW_C, DIMW_L);
    backgroundColor(255, 255, 107);
    Initworld(dat);
    while( !stop)
    {
        winClear();
        Draw(dat, niveau);
        Menue(dat, niveau);
        def = defaite(dat,niveau);
        vic = victoire(dat);
        if (vic==0 && def==0)
        {
            Update(dat);
        }
        else
        {
            if (vic==1)
            {
                print( 10, 10, "                                         victoire");
            }
            else
            {
                print( 10, 10, "                                          defaite");
            }
        }
        stop = winDisplay();

    }
    winQuit();
    return 0;
}
