#include <Grapic.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace grapic;
using namespace std;

const int DIMTL=1500,DIMTl=700;
const float dt=0.001,transfert=0.80,frottement=0.998;

struct Vec2
{
    float x,y;
};

struct Color
{
    int r,g,b;
};

struct Statistique
{
    int nb_rebond_bande,nb_chocs_balle,nb_fois_rentree,nb_fois_arrete,nb_vitesse;
    float tps_survie,vitesse_moyenne;
};

struct Particule
{
    Vec2 position,vitesse,force;
    float rayon,masse;
    int temps;
    bool present,mouvement;
    Color c;
    Statistique stat;
};

struct Score
{
    int balles[16];
    Vec2 position[16];
};

struct Table
{
    Particule T[16];
    Image im;
    Vec2 trou[6];
    int temps_latence_WB;
    Statistique stat_totales;
};

struct Aide
{
    Image menu;
    int pourcentage,maxp;
    Vec2 position;
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

Statistique operator+(Statistique a,Statistique b)
{
    Statistique c;
    c.nb_chocs_balle=a.nb_chocs_balle+b.nb_chocs_balle;
    c.nb_fois_arrete=a.nb_fois_arrete+b.nb_fois_arrete;
    c.nb_fois_rentree=a.nb_fois_rentree+b.nb_fois_rentree;
    c.nb_rebond_bande=a.nb_rebond_bande+b.nb_rebond_bande;
    c.nb_vitesse=a.nb_vitesse+b.nb_vitesse;
    c.tps_survie=a.tps_survie+b.tps_survie;
    c.vitesse_moyenne=a.vitesse_moyenne+b.vitesse_moyenne;
    return c;
}

float norm(Vec2 a)
{
    return sqrt(pow(a.x,2)+pow(a.y,2));
}

float norm(Vec2 a,Vec2 b)
{
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

Statistique initStatistique()
{
    Statistique stat;
    stat.nb_fois_rentree=0;
    stat.nb_chocs_balle=0;
    stat.nb_fois_arrete=0;
    stat.nb_rebond_bande=0;
    stat.nb_vitesse=0;
    stat.vitesse_moyenne=0;
    stat.tps_survie=elapsedTime();
    return stat;
}

Particule initParticule(Particule part,float posx,int posy,Color c)
{
    part.position.x=posx;
    part.position.y=posy;
    part.vitesse.x=0;
    part.vitesse.y=0;
    part.force.x=0;
    part.force.y=0;
    part.masse=1;
    part.rayon=DIMTl/50.f;
    part.c=c;
    part.temps=3;
    part.present=true;
    part.stat=initStatistique();
    return part;
}

Color set_color(int r,int g,int b)
{
    Color c;
    c.r=r;
    c.g=g;
    c.b=b;
    return c;
}

void initTable(Particule& part,Table& tab,Statistique& stat)
{
    Color c;
    Statistique ss={0,0,0,0,0,0,0};
    tab.stat_totales=ss;
    tab.temps_latence_WB=500;
    float dimx=DIMTL*0.7,dimy=DIMTl/2,lar=DIMTl/35.f,hyp=lar*2,lon=sqrt(hyp*hyp-lar*lar);
    tab.im=image("data/IMAGES/Billard.png");
    c=set_color(255,255,255);
    tab.T[0]=initParticule(part,DIMTL*0.2,DIMTl/2,c);
    tab.T[0].mouvement=false;
    c=set_color(255,215,0);
    tab.T[1]=initParticule(part,dimx,dimy,c);
    c=set_color(0,0,255);
    tab.T[2]=initParticule(part,dimx+lon*3,dimy+lar*3,c);
    c=set_color(255,0,0);
    tab.T[3]=initParticule(part,dimx+lon,dimy+lar,c);
    c=set_color(136,77,167);
    tab.T[4]=initParticule(part,dimx+lon*3,dimy-lar,c);
    c=set_color(255,163,71);
    tab.T[5]=initParticule(part,dimx+lon*4,dimy,c);
    c=set_color(58,187,35);
    tab.T[6]=initParticule(part,dimx+lon*2,dimy-lar*2,c);
    c=set_color(167,103,38);
    tab.T[7]=initParticule(part,DIMTL*0.7+lon*4,dimy+lar*4,c);
    c=set_color(0,0,0);
    tab.T[8]=initParticule(part,dimx+lon*2,dimy,c);
    c=set_color(255,215,0);
    tab.T[9]=initParticule(part,dimx+lon*3,dimy-lar*3,c);
    c=set_color(0,0,255);
    tab.T[10]=initParticule(part,dimx+lon,dimy-lar,c);
    c=set_color(255,0,0);
    tab.T[11]=initParticule(part,dimx+lon*4,dimy-lar*2,c);
    c=set_color(136,77,167);
    tab.T[12]=initParticule(part,dimx+lon*4,dimy+lar*2,c);
    c=set_color(255,163,71);
    tab.T[13]=initParticule(part,dimx+lon*2,dimy+lar*2,c);
    c=set_color(58,187,35);
    tab.T[14]=initParticule(part,dimx+lon*4,dimy-lar*4,c);
    c=set_color(167,103,38);
    tab.T[15]=initParticule(part,dimx+lon*3,dimy+lar,c);

    tab.trou[0]=make_Vecteur(45,658);
    tab.trou[1]=make_Vecteur(748,660);
    tab.trou[2]=make_Vecteur(1448,658);
    tab.trou[3]=make_Vecteur(47,42);
    tab.trou[4]=make_Vecteur(749,40);
    tab.trou[5]=make_Vecteur(1447,43);
}

void initScore(Score& s,Table tab)
{
    Vec2 spawn1={DIMTL*0.08,DIMTl*0.9};
    for(int i=0;i<16;i++)   s.position[i]=make_Vecteur(spawn1.x+tab.T[i].rayon*2*i,spawn1.y);
}

void initAide(Aide& a)
{
    a.maxp=500;
    a.pourcentage=a.maxp;
    a.menu=image("data/IMAGES/HELP.png");
    a.position=make_Vecteur(DIMTL-a.maxp,0);
}

void drawScore(Score s,Table tab)
{
    for(int i=0;i<16;i++)
    {
        if(tab.T[i].present)
        {
            color(tab.T[i].c.r,tab.T[i].c.g,tab.T[i].c.b);
            circle(s.position[i].x,s.position[i].y,tab.T[i].rayon*0.75);
        }
        else
        {
            color(tab.T[i].c.r,tab.T[i].c.g,tab.T[i].c.b);
            circleFill(s.position[i].x,s.position[i].y,tab.T[i].rayon*0.75);
        }
    }
}

void drawParticule(Table tab)
{
    for(int i=0;i<16;i++)
    {
        if(tab.T[i].present)
        {
            color(tab.T[i].c.r,tab.T[i].c.g,tab.T[i].c.b);
            circleFill(tab.T[i].position.x,tab.T[i].position.y,tab.T[i].rayon);
        }
    }
}

void drawTable(Table tab)
{
    image_draw(tab.im,0,0,DIMTL,DIMTl);
}

void mouvement(Table& tab)
{
    float dist;
    if(tab.T[0].present)
    {
        if(!tab.T[0].mouvement)
        {
            if(isMousePressed(SDL_BUTTON_LEFT))
            {
                int x,y;
                color(0,0,0);
                mousePos(x,y);
                line(tab.T[0].position.x,tab.T[0].position.y,x,y);
                if(isMousePressed(SDL_BUTTON_RIGHT))
                {
                    tab.T[0].vitesse=make_Vecteur((tab.T[0].position.x-x)*20,(tab.T[0].position.y-y)*20);
                    tab.T[0].mouvement=true;
                }
            }
        }
        dist=norm(tab.T[0].vitesse);
        if(dist<10)
        {
            tab.T[0].vitesse=make_Vecteur(0,0);
            tab.T[0].mouvement=false;
        }
    }
}

void collisionBords(Table& tab)
{
    for(int i=0;i<16;i++)
    {
        if(tab.T[i].present)
        {
            tab.T[i].vitesse=frottement*tab.T[i].vitesse;
            //bord gauche
            if(tab.T[i].position.x-tab.T[i].rayon<45)
            {
                tab.T[i].position=make_Vecteur(45+tab.T[i].rayon,tab.T[i].position.y);
                tab.T[i].vitesse=make_Vecteur(-tab.T[i].vitesse.x,tab.T[i].vitesse.y);
                tab.T[i].vitesse=transfert*tab.T[i].vitesse;
                tab.T[i].stat.nb_rebond_bande++;
                tab.T[i].stat.vitesse_moyenne=norm(tab.T[i].vitesse);
                tab.T[i].stat.nb_vitesse++;
            }
            //bord droit
            if(tab.T[i].position.x+tab.T[i].rayon>1449)
            {
                tab.T[i].position=make_Vecteur(1449-tab.T[i].rayon,tab.T[i].position.y);
                tab.T[i].vitesse=make_Vecteur(-tab.T[i].vitesse.x,tab.T[i].vitesse.y);
                tab.T[i].vitesse=transfert*tab.T[i].vitesse;
                tab.T[i].stat.nb_rebond_bande++;
                tab.T[i].stat.vitesse_moyenne=norm(tab.T[i].vitesse);
                tab.T[i].stat.nb_vitesse++;
            }
            //bord haut
            if(tab.T[i].position.y+tab.T[i].rayon>660)
            {
                tab.T[i].position=make_Vecteur(tab.T[i].position.x,660-tab.T[i].rayon);
                tab.T[i].vitesse=make_Vecteur(tab.T[i].vitesse.x,-tab.T[i].vitesse.y);
                tab.T[i].vitesse=transfert*tab.T[i].vitesse;
                tab.T[i].stat.nb_rebond_bande++;
                tab.T[i].stat.vitesse_moyenne=norm(tab.T[i].vitesse);
                tab.T[i].stat.nb_vitesse++;
            }
            //bord bas
            if(tab.T[i].position.y-tab.T[i].rayon<40)
            {
                tab.T[i].position=make_Vecteur(tab.T[i].position.x,40+tab.T[i].rayon);
                tab.T[i].vitesse=make_Vecteur(tab.T[i].vitesse.x,-tab.T[i].vitesse.y);
                tab.T[i].vitesse=transfert*tab.T[i].vitesse;
                tab.T[i].stat.nb_rebond_bande++;
                tab.T[i].stat.vitesse_moyenne=norm(tab.T[i].vitesse);
                tab.T[i].stat.nb_vitesse++;
            }
        }
    }
}

void collisionBoules(Table& tab)
{
    float distance,ax,ay,vtx1,vty1,vtx2,vty2,tampon;
    Vec2 a;
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            if(tab.T[i].present && tab.T[j].present)
            {
                distance=sqrt(pow(tab.T[i].position.x-tab.T[j].position.x,2)+pow(tab.T[i].position.y-tab.T[j].position.y,2));
                if(j!=i && distance<=tab.T[i].rayon+tab.T[j].rayon+1)
                {
                    if(tab.T[i].temps<=0 && tab.T[j].temps<=0)
                    {
                        tab.T[i].position=tab.T[i].position-(dt*tab.T[i].vitesse);
                        tab.T[j].position=tab.T[j].position-(dt*tab.T[j].vitesse);
                        a=tab.T[j].position-tab.T[i].position;

                        vtx1=(tab.T[j].vitesse.y*a.y*a.x-tab.T[i].vitesse.y*a.y*a.x+tab.T[i].vitesse.x*a.y*a.x+tab.T[j].vitesse.x*a.y*a.x)/(a.x*a.x+a.y*a.y);
                        vty1=(tab.T[j].vitesse.y*a.y*a.y+tab.T[j].vitesse.x*a.y*a.x-tab.T[i].vitesse.x*a.y*a.x+tab.T[i].vitesse.y*a.x*a.x)/(a.x*a.x+a.y*a.y);
                        vtx2=(tab.T[i].vitesse.x*a.x*a.x-tab.T[j].vitesse.y*a.y*a.x+tab.T[i].vitesse.y*a.y*a.x+tab.T[j].vitesse.x*a.y*a.y)/(a.x*a.x+a.y*a.y);
                        vty2=(tab.T[i].vitesse.x*a.y*a.x+tab.T[i].vitesse.y*a.y*a.y-tab.T[j].vitesse.x*a.y*a.x+tab.T[j].vitesse.y*a.x*a.x)/(a.x*a.x+a.y*a.y);

                        tab.T[i].vitesse.x=vtx1*transfert;
                        tab.T[i].vitesse.y=vty1*transfert;
                        tab.T[j].vitesse.x=vtx2*transfert;
                        tab.T[j].vitesse.y=vty2*transfert;

                        tab.T[i].stat.vitesse_moyenne=norm(tab.T[i].vitesse);
                        tab.T[i].stat.nb_vitesse++;
                        tab.T[j].stat.vitesse_moyenne=norm(tab.T[j].vitesse);
                        tab.T[j].stat.nb_vitesse++;
                    }

                    tab.T[i].temps=3;
                    tab.T[j].temps=3;

                    tab.T[i].stat.nb_chocs_balle++;
                    tab.T[j].stat.nb_chocs_balle++;
                }
                tab.T[i].temps--;
                tab.T[j].temps--;
            }
        }
    }
}

void partUpdate(Table& tab)
{
    for(int i=0;i<16;i++)
    {
        if(tab.T[i].present)
        {
            tab.T[i].vitesse=frottement*((dt*tab.T[i].force)/tab.T[i].masse+tab.T[i].vitesse);
            tab.T[i].position=tab.T[i].position+dt*tab.T[i].vitesse;
            if(tab.T[i].vitesse.x<10 && tab.T[i].vitesse.y<10 && tab.T[i].vitesse.x>-10 && tab.T[i].vitesse.y>-10)  tab.T[i].vitesse=make_Vecteur(0,0);
        }
    }
}

void collisionTrou(Table& tab)
{
    float distance;
    for(int i=0;i<16;i++)
    {
        if(tab.T[i].present)
        {
            for(int j=0;j<6;j++)
            {
                distance=norm(tab.trou[j],tab.T[i].position);
                if(distance<=25)
                {
                    tab.T[i].vitesse=make_Vecteur(0,0);
                    tab.T[i].present=false;

                    tab.T[i].stat.nb_fois_rentree++;
                    tab.T[i].stat.tps_survie=elapsedTime()-tab.T[i].stat.tps_survie;
                }
            }
        }
    }
}

bool condition_de_placement(Table tab,float rayon,int x,int y)
{
    float norm;
    bool test[15];
    for(int i=1;i<16;i++)
    {
        if(tab.T[i].present)
        {
            norm=sqrt(pow(tab.T[i].position.x-x,2)+pow(tab.T[i].position.y-y,2));
            test[i-1]=norm>rayon;
        }
        if(!tab.T[i].present)test[i-1]=true;
    }
    return(test[0] && test[1] && test[2] && test[3] && test[4] && test[5] && test[6] && test[7]
            && test[8] && test[9] && test[10] && test[11] && test[12] && test[13] && test[14]);
}

void repositionnerBalle(Table& tab)
{
    int x,y;
    float norme;
    bool cond;
    if(tab.temps_latence_WB>0) tab.temps_latence_WB--;
    if(!tab.T[0].present && tab.temps_latence_WB==0)
    {
        mousePos(x,y);
        color(255,255,255);
        circleFill(x,y,5);
        if(isMousePressed(SDL_BUTTON_RIGHT))
        {
            tab.temps_latence_WB=500;
            for(int i=1;i<16;i++)
            {
                cond=condition_de_placement(tab,tab.T[i].rayon*2,x,y);
                if(cond)
                {
                    tab.T[0].position=make_Vecteur(x,y);
                    tab.T[0].present=true;
                }
            }
        }
    }
}

void restart(Table& tab,Particule& part,Statistique& stat)
{
    if(isKeyPressed('r'))    initTable(part,tab,stat);
}

void figer(Table& tab)
{
    if(isKeyPressed('s'))
    {
        for(int i=0;i<16;i++)
        {
            if(tab.T[i].present)
            {
                if(abs(tab.T[i].vitesse.x)>10 || abs(tab.T[i].vitesse.x)>10)    tab.T[i].stat.nb_fois_arrete++;
                tab.T[i].vitesse=make_Vecteur(0,0);
            }
        }
    }
}

bool win_condition(Table& tab)
{
    if(!tab.T[0].present && !tab.T[1].present && !tab.T[2].present && !tab.T[3].present && !tab.T[4].present &&
       !tab.T[5].present && !tab.T[6].present && !tab.T[7].present && !tab.T[8].present && !tab.T[9].present &&
       !tab.T[10].present && !tab.T[11].present && !tab.T[12].present && !tab.T[13].present && !tab.T[14].present
       && !tab.T[15].present)
       {
           tab.T[0].stat.tps_survie=elapsedTime();
           for(int i=0;i<16;i++)    tab.stat_totales=tab.stat_totales+tab.T[i].stat;
           return true;
       }
       return false;
}

void help(Aide& a)
{
    color(0,0,0);
    fontSize(18);
    print(1260,628,"PRESS 'A' for Help");
    if(isKeyPressed('a'))   a.pourcentage-=5;
    else    a.pourcentage+=5;
    if(a.pourcentage<0)    a.pourcentage+=5;
    if(a.pourcentage>a.maxp)    a.pourcentage-=5;
    if(a.pourcentage!=a.maxp)    image_draw(a.menu,a.position.x+a.pourcentage,a.position.y,a.maxp,DIMTl);
}

void afficher_trou(Table tab)
{
    color(0,0,0);
    for(int i=0;i<6;i++)    circleFill(tab.trou[i].x,tab.trou[i].y,25);
}

void debug(Table& tab)
{
    for(int i=0;i<16;i++)
    {
        if(!(tab.T[i].position.x>=0 || tab.T[i].position.y>=0 || tab.T[i].position.x<=0 || tab.T[i].position.y<=0)) tab.T[i].present=false;
    }
}

void show_stats(Statistique s,bool general)
{
    color(255,255,255);
    fontSize(25);
    if(general)
    {
        print(140,435,"Nombre de chocs totaux des balles : ");
        print(140,335,"Nombre de fois où les balles sont renrées : ");
        print(140,235,"Nombre de balles arrêtées manuellement : ");
        print(140,135,"Rebond totaux des balles sur la bande : ");
        print(DIMTL*0.55,200,"Vitesse moyenne des balles : ");
        print(DIMTL*0.55,380,"Temps de survie moyen des balles : ");
        print(DIMTL*0.85,380,s.tps_survie/16);
    }
    else
    {
        print(140,435,"Nombre de chocs de la balle : ");
        print(140,335,"Nombre de fois où la balle est rentrée : ");
        print(140,235,"Nombre d'arrêt manuel de la balle : ");
        print(140,135,"Nombre de rebond sur la bande : ");
        print(DIMTL*0.55,200,"Vitesse moyenne de la balle : ");
        print(DIMTL*0.55,380,"Temps de survie de la balle : ");
        print(DIMTL*0.85,380,s.tps_survie);
    }
    print(DIMTL*0.45,435,s.nb_chocs_balle);
    print(DIMTL*0.45,335,s.nb_fois_rentree);
    print(DIMTL*0.45,235,s.nb_fois_arrete);
    print(DIMTL*0.45,135,s.nb_rebond_bande);
    print(DIMTL*0.85,200,s.vitesse_moyenne/s.nb_vitesse);

}

bool win_screen(Table tab,Score s)
{
    int x,y;
    float r;
    bool general=true;
    image_draw(tab.im,0,0,DIMTL,DIMTl);
    color(255,255,255);
    rectangleFill(DIMTL/2-2,DIMTl*0.15,DIMTL/2+2,DIMTl*0.7);
    fontSize(60);
    print(DIMTL/2-200,DIMTl*0.7,"STATISTIQUES");
    for(int i=0;i<16;i++)
    {
        mousePos(x,y);
        r=sqrt(pow(y-s.position[i].y,2)+pow(x-s.position[i].x,2));
        if(r<=tab.T[i].rayon*0.75)
        {
            color(tab.T[i].c.r,tab.T[i].c.g,tab.T[i].c.b);
            circleFill(s.position[i].x,s.position[i].y,tab.T[i].rayon*0.75);
            show_stats(tab.T[i].stat,false);
            general=false;
        }
        else
        {
            color(tab.T[i].c.r,tab.T[i].c.g,tab.T[i].c.b);
            circle(s.position[i].x,s.position[i].y,tab.T[i].rayon*0.75);
        }
    }
    if(general)show_stats(tab.stat_totales,general);
    color(0,0,0);
    fontSize(18);
    print(1110,628,"Press 'ECHAP' to Quit");
    print(65,588,"Passez votre souris sur les balles pour voir les stats individuelles");
    if(isKeyPressed(27))    return true;
    return false;
}

int main(int , char** )
{
    winInit("Billard", DIMTL,DIMTl);
    backgroundColor(255,255,255);
    srand(time(NULL));
    Particule part;
    Table tab;
    Aide a;
    Score s;
    Statistique stat;
    initTable(part,tab,stat);
    initScore(s,tab);
    initAide(a);
    setKeyRepeatMode(true);
    bool stop=false,pots=false;
	while( !stop )
    {
        stop = winDisplay();
        if(pots==false)
        {
            winClear();
            drawTable(tab);
            afficher_trou(tab);
            drawParticule(tab);
            drawScore(s,tab);
            mouvement(tab);
            partUpdate(tab);
            collisionBords(tab);
            collisionBoules(tab);
            collisionTrou(tab);
            repositionnerBalle(tab);
            restart(tab,part,stat);
            figer(tab);
            help(a);
            debug(tab);
            pots=win_condition(tab);
        }
        else   stop = win_screen(tab,s);
    }
    winQuit();
	return 0;
}
