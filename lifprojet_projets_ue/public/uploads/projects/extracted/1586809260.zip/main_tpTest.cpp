#include <Grapic.h>
#include <iostream>
using namespace grapic;
using namespace std;
const int DIMW = 1000;
const int MAX_PART = 100;
const int MAX_MARCHAND = 10;

struct pos
{
    float x;
    float y;
};
pos make_pos(float r, float i)
{
    pos c;
    c.x = r;
    c.y = i;
    return c;
}
pos make_pos_expo(float r, float theta)
{
    pos c;
    c.x = r*cos(theta);
    c.y = r*sin(theta);
    return c;
}
pos operator+(pos a, pos b)
{
    pos c = { a.x+b.x, a.y+b.y };
    return c;
}
pos operator-(pos a, pos b)
{
    pos c = { a.x-b.x, a.y-b.y };
    return c;
}
pos translate(pos p, float dx, float dy)
{
    return p + make_pos(dx,dy);
}
pos operator*(float a, pos b)
{
    pos c = { a*b.x, a*b.y };
    return c;
}
pos operator/(pos b, float d)
{
    pos c = { b.x/d, b.y/d };
    return c;
}
pos scale(pos p, float cx, float cy, float sc)
{
    pos tr = make_pos( cx, cy);
    return (sc*(p-tr))+tr;
}
float dist(pos a, pos b)
{
    pos c=a-b;
    return (sqrt(c.x*c.x+c.y*c.y));
}
struct colour
{
    unsigned char r, g, b;
};
struct marchand
{
    struct pos p;
    struct colour c;
    float prix;
    int nbclients;
    float gain;
    float somprixtot;
    float clientstot;
};
struct LesMarchands
{
    int nbm;  ///nb de marchand
    struct marchand tab[MAX_MARCHAND];
    Plot p;
};
struct rectan
{
    int x1, x2, y1, y2;
};
struct CentreCommercial
{
    struct rectan r;
    Image im_centrecom;
    bool ouverture;
};
colour make_colour(unsigned char a, unsigned char b, unsigned char d)
{
    colour c;
    c.r = a;
    c.g = b;
    c.b = d;
    return c;
}
void Init(struct LesMarchands & lm, CentreCommercial & cc)
{
    lm.nbm=4;
    for(int i=0; i<lm.nbm; i++)
    {
        lm.tab[i].p.x=rand()%600;//DIMW;lm.tab[i].p.x=rand()%390;
        lm.tab[i].p.y=rand()%600+400; //DIMW;rand()%390+110;
        lm.tab[i].prix=rand()%5+2;
        lm.tab[i].nbclients=0;
        lm.tab[i].gain=0;
        lm.tab[i].somprixtot=0;
        lm.tab[i].clientstot=0;
        //lm.tab[i].c.r=rand()%256;
        //lm.tab[i].c.g=rand()%256;
        //lm.tab[i].c.b=rand()%256;
    }
    lm.tab[0].c=make_colour(51,255,255);
    lm.tab[1].c=make_colour(51,255,51);
    lm.tab[2].c=make_colour(51,51,255);
    lm.tab[3].c=make_colour(255,255,51);
    //0TURQUOISE 1VERT 2BLEU 3JAUNE
    cc.im_centrecom= image("data/centrecom.png");
    cc.r.x1=510;//310
    cc.r.x2=600;//390
    cc.r.y1=870;//380
    cc.r.y2=1000;//500
}
void Draw(struct LesMarchands lm, struct CentreCommercial cc)
{
    for(int i=0; i<lm.nbm; i++)
    {
        color(255,0,0);
        circleFill(lm.tab[i].p.x,lm.tab[i].p.y,2);
    }
    image_draw(cc.im_centrecom,510,870,90,130);//cc.im_centrecom,310,380,80,120);
}
float distan(rectan r, float px, float py)
{
    pos a;
    pos b;
    a=make_pos(px,py);
    int height;
    int width;
    pos centre;
    float dx;
    float dy;
    width=r.x2-r.x1;///calcul de la largeur
    height=r.y2-r.y1;///calcul de la hauteur
    centre=make_pos(r.x1+(width/2),r.y1+(height/2));///calcul du centre du rectangle
    dx=max(abs(px-centre.x)-width/2,0.0f);
    dy=max(abs(py-centre.y)-height/2,0.0f);
    return sqrt(dx*dx+dy*dy);
}
colour minMarchand(float px, float py,struct LesMarchands & lm, CentreCommercial & cc)
{
    int indmin=0;
    pos a;
    colour res;
    float somme;
    float minidist;
    a=make_pos(px,py);
    if(cc.ouverture)
    {
        minidist=distan(cc.r,lm.tab[0].p.x,lm.tab[0].p.y);
    }
    else
    {
        minidist=0;
    }
    float distmin=dist(lm.tab[0].p,a) + 10*lm.tab[0].prix+ minidist;
    for(int i=1; i<lm.nbm; i++)
    {
        minidist=distan(cc.r,lm.tab[i].p.x,lm.tab[i].p.y);
        somme=dist(lm.tab[i].p,a) + 10*lm.tab[i].prix + minidist;
        if(somme<distmin)
        {
            distmin=somme;
            indmin=i;
        }
    }
    res.r=lm.tab[indmin].c.r;
    res.g=lm.tab[indmin].c.g;
    res.b=lm.tab[indmin].c.b;
    lm.tab[indmin].nbclients++;
    return res;
}
void traitevente(struct LesMarchands & lm, bool affichage, struct CentreCommercial & cc )
{
    colour res;
    for(int i=0; i<lm.nbm; i++)
    {
        lm.tab[i].nbclients=0;
    }
    for(int i=0; i<600; i++) ///int i=0; i<390; i++){
    {
        for(int j=400; j<1000; j++)///int j=110; j<500; j++)
        {
            res=minMarchand(i,j,lm,cc);
            if(affichage)
            {
                put_pixel(i,j,res.r,res.g,res.b);
            }
        }
    }
}

void MajMarchands(struct LesMarchands & lm, CentreCommercial & cc)
{
    pos tab_voisin[8];
    tab_voisin[0]=make_pos(0,1);
    tab_voisin[1]=make_pos(1,0);
    tab_voisin[2]=make_pos(0,-1);
    tab_voisin[3]=make_pos(-1,0);
    tab_voisin[4]=make_pos(-1,-1);
    tab_voisin[5]=make_pos(1,1);
    tab_voisin[6]=make_pos(1,-1);
    tab_voisin[7]=make_pos(-1,1);
    LesMarchands lmR;
    LesMarchands lm2;
    float gain;
    float bestgain;
    float bestprix;
    pos bestpoint;
    int maxclient;
    int gainTemps;
    lmR=lm;
    for(int i=0; i<4; i++)
    {
        maxclient=lmR.tab[i].nbclients;
        bestpoint=lmR.tab[i].p;
        for(int k=0; k<8; k++)//teste le changement de place
        {
            lm2=lm;
            lm2.tab[i].p=lm.tab[i].p+tab_voisin[k];
            traitevente(lm2,false,cc);
            if(lm2.tab[i].nbclients>maxclient)
            {
                maxclient=lm2.tab[i].nbclients;
                bestpoint=lm2.tab[i].p;
            }
        }
        lmR.tab[i].p=bestpoint;
        lmR.tab[i].nbclients=maxclient;
        bestprix=lmR.tab[i].prix;
        bestgain=lmR.tab[i].nbclients*lmR.tab[i].prix;
        lm2=lmR;
        lm2.tab[i].prix=lm2.tab[i].prix*0.9;
        traitevente(lm2,false,cc);
        gain=lm2.tab[i].prix*lm2.tab[i].nbclients;
        if(gain>bestgain)
        {
            bestprix=lm2.tab[i].prix;
        }
        else
        {
            lm2=lmR;
            if(lm2.tab[i].prix <6)
            {
                lm2.tab[i].prix=lm2.tab[i].prix*1.1;
            }
            traitevente(lm2,false,cc);
            gainTemps=lm2.tab[i].prix*lm2.tab[i].nbclients;
            if(gainTemps>bestgain)
            {
                bestprix=lm2.tab[i].prix;
            }
        }
        lmR.tab[i].prix=bestprix;
    }
    lm=lmR;
    for(int i=0; i<4; i++)
    {
        lm.tab[i].gain+=lm.tab[i].prix*lm.tab[i].nbclients;///lm.tab[i].prix;
        lm.tab[i].somprixtot+=lm.tab[i].prix;///pour dans le bilan calculer le prix moyen par marchand
        lm.tab[i].clientstot+=lm.tab[i].nbclients;///pour le bilan calculer le nombre moyen de client par marchand
    }
}
void semaine(float x,CentreCommercial cc)
{
    cc.ouverture=true;
    int a;
    fontSize(25);
    if((x>0)&&(x<=0.07))
    {
        a=1;///lundi
    }
    else if((x>0.07)&&(x<=0.14))
    {
        a=2;///mardi
    }
    else if((x>0.14)&&(x<=0.21))
    {
        a=3;///mercredi
    }
    else if((x>0.21)&&(x<=0.28))
    {
        a=4;///jeudi
    }
    else if((x>0.28)&&(x<=0.35))
    {
        a=5;///vendredi
    }
    else if((x>0.35)&&(x<=0.42))
    {
        a=6;
    }
    else if((x>0.42)&&(x<=0.48))
    {
        a=7;
    }
    switch(a)
    {
    case 1:                 ///(0<x<=0.07)
        print(605,900,"aujourd'hui c'est : lundi");
        print(605,870,"fermeture du centre commercial");
        cc.ouverture=false;
        break;
    case 2:                 ///(0.07<x<=0.14)
        print(605,900,"aujourd'hui c'est : mardi");
        break;
    case 3:                 ///(0.14<x<=0.21)
        print(605,900,"aujourd'hui c'est : mercredi");
        break;
    case 4:                 ///(0.21<x<=0.28)
        print(605,900,"aujourd'hui c'est : jeudi");
        break;
    case 5:                 ///(0.28<x<=0.35)
        print(605,900,"aujourd'hui c'est : vendredi");
        break;
    case 6:                 ///(0.35<x<=0.42)
        print(605,900,"aujourd'hui c'est : samedi");
        break;
    case 7:                 ///(0.42<x<=0.48)
        print(605,900,"aujourd'hui c'est : dimanche");
        print(605,870,"fermeture du centre commercial");
        cc.ouverture=false;
        break;
    default:
        print(10,950,"c'est la fin de la semaine, voici le bilan :");
    }
}
void prixtempsreel(CentreCommercial cc, LesMarchands lm)
{
    int a;
    a=850;
    for(int i=0; i<4; i++)
    {
        //lm.tab[i].gain=lm.tab[i].gain/lm.tab[i].nbgain;
        fontSize(15);
        print(605,a,"prix du marchand n° ");
        print(750,a,i+1);
        print(605,a-17,lm.tab[i].prix);
        //print(620,a-17,"€");
        a-=51;
    }
}
void BilanSemaine(LesMarchands lm)
{
    int a, a2, b, b2;
    int aff;///le premier a x=300 deuxième x=450 puis x=600 x=750
    a=lm.tab[0].gain;
    a2=0;
    b=lm.tab[0].clientstot;
    b2=0;
    aff=250;
    print(5,900,"marchand :");
    print(5,850,"prix moyen :");
    print(5,800,"nb clients moyen :");
    print(5,750,"gain total :");
    print(5,700,"nb clients total :");
    print(5,650,"le marchand qui a fait le plus de gain :");
    print(5,600,"le marchand qui a eu le plus de clients :");
    for(int i=0; i<4; i++)
    {
        print(aff,900,i+1);
        print(aff,850,lm.tab[i].somprixtot/48);///donne le prix par marchand moyen sur la semaine
        print(aff,800,lm.tab[i].clientstot/48);///nombre de clients moyen
        print(aff,750,lm.tab[i].gain);///les gains totaux par marchand sur toute la semaine
        print(aff,700,lm.tab[i].clientstot);///le nombre de client total par marchand sur toute la semaine
        if(lm.tab[i].gain>a)
        {
            a=lm.tab[i].gain;
            a2=i;
        }
        if(lm.tab[i].clientstot>b)
        {
            b=lm.tab[i].clientstot;
            b2=i;
        }
        aff=aff+170;
    }
    print(450,650,a2);///le marchand qui a gagné le plus de sous
    print(470,600,b2);///celui qui a eu le plus de clients
}
int main(int, char** )
{
    srand(time(NULL));
    LesMarchands lm;
    CentreCommercial cc;
    bool stop=false;
    winInit("MarchandsDeGlaces", DIMW, DIMW);
    //setKeyRepeatMode(true);
    Init(lm,cc);
    //backgroundColor( 100, 50, 200 );
    backgroundColor(250,200,170);
    float x=0.f;
    Plot p1;
    plot_setSize(p1, 100);
    Plot p2;
    plot_setSize(p2, 100);
    while( !stop )
    {
        winClear();
        semaine(x,cc);
        if(x<0.48) ///si non fin de semaine
        {
            traitevente(lm,true,cc);
            MajMarchands(lm,cc);
            Draw(lm,cc);
            x += 0.01;
            cout<<x<<endl;
            color(25,45,230);
            fontSize(40);
            print(605,950,"Bienvenue !");
            ///graphe du prix en fonction du temps pour chaque marchand
            fontSize(25);
            color( 255, 0,0);
            print(560,205,"Graphe des prix par marchand");
            plot_add(p1,x,lm.tab[0].prix,0);
            plot_add(p1,x,lm.tab[1].prix,1);
            plot_add(p1,x,lm.tab[2].prix,2);
            plot_add(p1,x,lm.tab[3].prix,3);
            color( 255, 0,0);
            plot_draw(p1,510,0,990,200);
            ///graphe du prix en fonction du temps pour chaque marchand
            fontSize(25);
            color( 255, 0,0);
            print(20,205,"Graphe du nombre de clients par marchand");
            plot_add(p2,x,lm.tab[0].nbclients,0);
            plot_add(p2,x,lm.tab[1].nbclients,1);
            plot_add(p2,x,lm.tab[2].nbclients,2);
            plot_add(p2,x,lm.tab[3].nbclients,3);
            color( 255, 0,0);
            plot_draw(p2,10,0,490,200);
            prixtempsreel(cc,lm);
            //Update();
            //delay(70);
        }
        else
        {
            BilanSemaine(lm);
            ///graphe du prix en fonction du temps pour chaque marchand
            fontSize(25);
            color( 255, 0,0);
            print(560,205,"Graphe des prix par marchand");
            plot_draw(p1,510,0,990,200);
            ///graphe du prix en fonction du temps pour chaque marchand
            fontSize(25);
            color( 255, 0,0);
            print(20,205,"Graphe du nombre de clients par marchand");
            plot_draw(p2,10,0,490,200);
        }
        stop = winDisplay();
    }

    winQuit();
    return 0;
}
