#include <Grapic.h>
# include <iostream>
# include <math.h>
#include <cstdlib>
using namespace std;
using namespace grapic;



int const TAILLE_MAX = 600;
int const DIMW = 1600;
int const DIMY =800;
//float const DT = 1;

struct ligne
{
    int nb_case;
    bool line[TAILLE_MAX];
    int bin[TAILLE_MAX];
};

struct world
{
    ligne tab[TAILLE_MAX];
    int nb_ligne;
    float dt;
};



void calc_bin(ligne &l)
{
    int i,j,k,m;
    for(i=0;i<l.nb_case;i++)
    {
        l.bin[i]=0;
        if (i==0)
        {
            l.bin[i]+=1;    //car même si le -1 n'est pas compté, considèré comme blanc (sinon val bin erronnées)
            for (j=0;j<2;j++)
            {
                if(l.line[j]==true)
                    l.bin[i]+=pow(2,(2-j));
                else
                    l.bin[i]+=1;
            }
        }
        if((0<i)&&(i<l.nb_case-1))
        {
            for(k=i-1;k<i+2;k++)
            {
                if(l.line[k]==true)
                    l.bin[i]+=pow(2,(2-k+i));
                else
                    l.bin[i]+=1;
            }
        }
        if(i==l.nb_case-1)
        {
            l.bin[i]+=1;
            for(m=i-1;m<i+1;m++)
            {
                if(l.line[m]==true)
                    l.bin[i]+=pow(2,(2-m+i));
                else
                    l.bin[i]+=1;
            }
        }
    }
}



void add_ligne(ligne &l, world &w)        //init && ajoute 1ère ligne a world
{
    w.tab[0]=l;
    w.nb_ligne=1;
    w.dt=0;
}

void init_ligne(ligne &l, int nbcase, world &w)
{
    bool col;
    l.nb_case=nbcase;
    int i;
    for(i=0;i<nbcase;i++)
    {
            if ((i == (nbcase/2)-1))
                l.line[i]=true;
            else
                l.line[i]=false;
    }
    calc_bin(l);
    add_ligne(l,w);
}


void draw_grille(int nb_case)
{
    for(int i = 0;i<nb_case;i++)
    {
        color(0,0,0);
        line(i*DIMW/nb_case,DIMY,i*DIMW/nb_case, 0);
        line(0,DIMY - (i+1)*DIMY/nb_case,DIMW, DIMY - (i+1)*DIMY/nb_case);
    }
}



void draw_world(world &w)
{
int i,j,k,m;
//draw_grille(w.tab[0].nb_case);
for (i=0;i<w.nb_ligne+1;i++)
{
    for(j=0;j<w.tab[i].nb_case;j++)
    {
        if (w.tab[i].line[j]==true)
            color(0,0,0);
        else
            color(255,255,255);
        rectangleFill(j*DIMW/w.tab[i].nb_case,DIMY-(i+1)*DIMY/w.tab[i].nb_case,(j+1)*DIMW/w.tab[i].nb_case,DIMY-(i)*DIMY/w.tab[i].nb_case);
    }
}
if((w.tab[w.nb_ligne-1].line[0]==true)||(w.tab[w.nb_ligne-1].line[w.tab[i].nb_case-1]==true))
    {
        for (k=0;k<w.nb_ligne;k++)
        {
            w.tab[k].nb_case+=2;
            for (m=1;m<w.tab[k].nb_case-1;m++)
            {
                w.tab[k].line[w.tab[k].nb_case-m-1]=w.tab[k].line[w.tab[k].nb_case-m-2];
            }
            w.tab[k].line[0]=false;
            w.tab[k].line[w.tab[k].nb_case-1]=false;
            calc_bin(w.tab[k]);
        }
        draw_world(w);
    }
}









void update_add_line (world &w, int regle,float DT)
{
w.dt+=DT;
w.dt = fmod(w.dt,1);
if (w.dt<DT)
    w.dt =0;
if (w.dt == 0)
{
ligne l;
int i;
l.nb_case=w.tab[w.nb_ligne-1].nb_case;
for (i=0;i<w.tab[w.nb_ligne-1].nb_case;i++)
{

switch(regle)
{
case 1 :
    switch (w.tab[w.nb_ligne-1].bin[i]) //regle 1
    {
        case 3:
        l.line[i]=false;
        break;
        case 4:
            l.line[i]=true;
        break;
        case 6:
            l.line[i]=true;
        break;
        case 7:
            l.line[i]=true;
        break;
        case 10:
            l.line[i]=true;
        break;
        case 11:
            l.line[i]=true;
        break;
        case 13:
            l.line[i]=true;
        break;
        case 14:
            l.line[i]=true;
        break;
        //regle 1
    }
break;
case 2 :
    switch (w.tab[w.nb_ligne-1].bin[i]) //regle 2
    {
        case 3:
            l.line[i]=false;
        break;
        case 4:
            l.line[i]=true;
        break;
        case 6:
            l.line[i]=false;
        break;
        case 7:
            l.line[i]=true;
        break;
        case 10:
            l.line[i]=true;
        break;
        case 11:
            l.line[i]=true;
        break;
        case 13:
            l.line[i]=true;
        break;
        case 14:
            l.line[i]=true;
        break;
        //regle 2
    }
break;
case 3 :
    switch (w.tab[w.nb_ligne-1].bin[i]) //regle 3 :triangle de Sierpenski
    {
        case 3:
            l.line[i]=false;
        break;
        case 4:
            l.line[i]=true;
        break;
        case 6:
            l.line[i]=true;
        break;
        case 7:
            l.line[i]=true;
        break;
        case 10:
            l.line[i]=true;
        break;
        case 11:
            l.line[i]=true;
        break;
        case 13:
            l.line[i]=true;
        break;
        case 14:
            l.line[i]=false;
        break;
        //regle 3
    }
break;
case 4 :
    switch (w.tab[w.nb_ligne-1].bin[i]) //regle 4 : système chaotique
    {
        case 3:
            l.line[i]=false;
        break;
        case 4:
            l.line[i]=true;
        break;
        case 6:
            l.line[i]=true;
        break;
        case 7:
            l.line[i]=true;
        break;
        case 10:
            l.line[i]=true;
        break;
        case 11:
            l.line[i]=false;
        break;
        case 13:
            l.line[i]=false;
        break;
        case 14:
            l.line[i]=false;
        break;
        //regle 4
    }
break;
case 5 :
    switch (w.tab[w.nb_ligne-1].bin[i]) //regle 5 : règle universelle
    {
        case 3:
            l.line[i]=false;
        break;
        case 4:
            l.line[i]=true;
        break;
        case 6:
            l.line[i]=true;
        break;
        case 7:
            l.line[i]=true;
        break;
        case 10:
            l.line[i]=false;
        break;
        case 11:
            l.line[i]=true;
        break;
        case 13:
            l.line[i]=true;
        break;
        case 14:
            l.line[i]=false;
        break;
        //regle 5
    }
break;
}
}
calc_bin(l);
for(i=0;i<l.nb_case;i++)
{
    w.tab[w.nb_ligne].line[i]=l.line[i];
    w.tab[w.nb_ligne].bin[i]=l.bin[i];
    w.tab[w.nb_ligne].nb_case=l.nb_case;
}
w.nb_ligne++;
}
}


int main(int , char** )
{
    ligne l;
    world w;
    float DT;
    float t;
    bool grille;
    int regle;
    Menu menu1;
    Menu menu2;
    Menu menu3;
    int nbcase =50;
    init_ligne(l,nbcase,w);
    winInit("Jeu de la vie 1D", DIMW, DIMY);
    menu_add(menu1,"Pause => choisissez la règle !");
    menu_add(menu1,"Time x1");
    menu_add(menu1,"Time x10");
    menu_add(menu1,"Time x100");
    menu_add(menu2,"Sans grille");
    menu_add(menu2,"Avec grille");
    menu_add(menu3,"Règle 1");
    menu_add(menu3,"Règle 2");
    menu_add(menu3,"Triangle de Sierpinsky");
    menu_add(menu3,"Structure Chaotique");
    menu_add(menu3,"Règle universelle");
    bool stop=false;
    backgroundColor( 255, 255, 255 );
    while( (!stop ))
    {
        switch(menu_select(menu1))
            {
            case 0 :
                DT = 0.000001;
            break;
            case 1 :
                DT = 0.01;
            break;
            case 2 :
                DT = 0.1;
            break;
            case 3 :
                DT = 1;
            break;
            }
        switch (menu_select(menu2))
        {
            case 0 :
                grille = false;
            break;
            case 1 :
                grille = true;
            break;
        }
        switch(menu_select(menu3))
        {
        case 0 :
            regle = 1;
            break;
        case 1 :
            regle = 2;
            break;
        case 2 :
            regle = 3;
            break;
        case 3 :
            regle = 4;
            break;
        case 4 :
            regle = 5;
            break;
        }
        winClear();
        menu_draw(menu1,260,50,460,170);
        menu_draw(menu2,470,70,670,150);
        menu_draw(menu3,50,10,250,210);
        draw_world(w);
        update_add_line(w,regle,DT);
        if (grille == true)
            draw_grille(w.tab[0].nb_case);
        stop = winDisplay();
        if (w.tab[0].nb_case==TAILLE_MAX)
        {
            stop = true;
            cout << endl << endl << endl << "Taille maximale atteinte" << endl << endl << endl;
        }
    }

    winQuit();
	return 0;
}
