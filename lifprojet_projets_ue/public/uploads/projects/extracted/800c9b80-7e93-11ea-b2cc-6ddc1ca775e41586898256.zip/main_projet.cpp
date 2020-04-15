#include <Grapic.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>

using namespace std;
using namespace grapic;


const int DIMW = 600; //dimensions fenetre
const int DIMWY = 600;
const int MAX=100; //largeur de grille max
//const int X = 480, Y = 480;

struct Cellule
{
    int etat;
};

struct Jeu_de_la_vie
{
    Cellule grille[MAX][MAX];//tableau de cellules
    int x, y; //taille de la grille
    int nbv;//nombre de cellules vivantes
    bool naissance[9];//tableau de booleen pour indiquer le nb de voisin qu'il faut
    bool survie[9];//same

};


void initJeu (Jeu_de_la_vie &J,int taille_x,int taille_y) //taille_x et taille_y : dimension de la grille de jeu
{
    int i,j;
    J.x = taille_x+2; // on laisse une colonne de chaque côté
    J.y = taille_y+2;
    J.nbv = 0;
    for (i=0; i<J.x; i++)
    {
        for (j=0; j<J.y; j++)
            {
                J.grille[i][j].etat = 0;
            }
    }
    for(i=0;i<9;i++)
    {
        J.naissance[i]=0;
        J.survie[i]=0;
    }

}

void etat_initial (Jeu_de_la_vie &J)
{
    int x,y,i;
    J.nbv = rand()%((J.x-3)*(J.y-3) - 3) + 1 ; //nombre de cellules vivantes definies aleatoirement
    cout<<"Population initiale : "<<J.nbv<<endl;
    for (i=0; i<J.nbv; i++)
    {
        do
        {
            x = irand(1, J.x-1);
            y = irand(1, J.y-1);
        } while (J.grille[x][y].etat==1);

        J.grille[x][y].etat = 1;
    }
    //règles de bases du jeu de la vie
    J.naissance[3]=1;
    J.survie[2]=1;
    J.survie[3]=1;
}


int nb_voisins (Jeu_de_la_vie &J, int x, int y)
{
    int nb = 0, i, j; //nb est le nombre de voisins vivants
    for (i=-1; i<=1; i++)
    {
        for (j=-1; j<=1; j++)
        {
            if (J.grille[x+i][y+j].etat==1)
            {
                nb++;
            }
        }
    }
    if (J.grille[x][y].etat==1)
        nb--;
    return nb;
}


void etat_suivant(Jeu_de_la_vie &J)
{
    Jeu_de_la_vie Jt1 = J;
    for(int i=0;i<J.x;i++)
    {
        for(int j=0;j<J.y;j++)
        {
            if(i==0 || i==J.x || j==0 || j==J.y)
            {
                Jt1.grille[i][j].etat=0;
            }
            else {
            int v=nb_voisins(J,i,j);
            if(J.grille[i][j].etat == 1)
            {
                Jt1.grille[i][j].etat=J.survie[v];
			}
			if(J.grille[i][j].etat == 0)
            {
                if(v==3)
                {
                    Jt1.grille[i][j].etat = J.naissance[v] ; //naissance
                }
            }
        }}
    }

    J = Jt1 ;

}


void drawJeu (Jeu_de_la_vie J, int n)
{
    int i,j;
    for (i=1; i<J.x-1; i++)
    {
        for (j=1; j<J.y-1; j++)
        {
            if (J.grille[i][j].etat==1)
            {
                color(0,0,0);
                rectangleFill((i-1)*(DIMW/n),(DIMW/2)+(DIMW/n)*(j-1),(DIMW/n)*i,(DIMW/2)+(DIMW/n)*j);
            }

            color(0,0,0);
            rectangle((i-1)*(DIMW/n),(DIMW/2)+(DIMW/n)*(j-1),(DIMW/n)*i,(DIMW/2)+(DIMW/n)*j);
        }
    }
    line(0,5*DIMW/12,DIMW,5*DIMW/12);
    line(0,DIMW/6,DIMW,DIMW/6);
    line(0,DIMW/3,DIMW,DIMW/3);
    for(i=0;i<9;i++)
    {
            line(DIMW/4+i*DIMW/12,0,DIMW/4+i*DIMW/12,5*DIMW/12);
    }


}




int main(int , char** )
{
    Menu tab_menu_naissance[9];
    Menu tab_menu_survie[9];
    for(int i=0; i<9; i++)
    {
        menu_add(tab_menu_naissance[i], " 0");
        menu_add(tab_menu_naissance[i], " 1");
        menu_add(tab_menu_survie[i], " 0");
        menu_add(tab_menu_survie[i], " 1");
    }
    int n = 50;//dim de la grille
    Jeu_de_la_vie LifeGame;
    bool stop=false;
    winInit("Game of Life", DIMW, DIMW);
    backgroundColor(255,255,255);
    initJeu(LifeGame, n, (n/2));
    setKeyRepeatMode(true);
    srand(time(NULL));
    etat_initial(LifeGame);

    for(int i=0;i<9;i++)
    {
        menu_setSelect(tab_menu_survie[i],LifeGame.survie[i]);
        menu_setSelect(tab_menu_naissance[i],LifeGame.naissance[i]);
    }
    print(5, DIMW/3+5,"Survie");
    while( !stop )
    {
        winClear();
        for(int i=0;i<9;i++)
        {
            menu_draw(tab_menu_survie[i],((DIMW/4)+i*(DIMW/12)),DIMW/6,(DIMW/4)+(i+1)*(DIMW/12),DIMW/3);
            menu_draw(tab_menu_naissance[i],((DIMW/4)+i*(DIMW/12)),0,(DIMW/4)+(i+1)*(DIMW/12),DIMW/6);
        }

        for(int i=0;i<9;i++)
        {
            LifeGame.survie[i]=menu_select(tab_menu_survie[i]);
            LifeGame.naissance[i]=menu_select(tab_menu_naissance[i]);
        }
        print(5, DIMW/4,"Survie");
        print(5, DIMW/12,"Naissance");
        print(5,9*DIMW/24,"Nombre de voisin(s)");
        for(int i=0;i<9;i++)
        {
                print(DIMW/4+(i*DIMW/12)+DIMW/24,9*DIMW/24,i);
        }


        drawJeu(LifeGame, n);
        etat_suivant(LifeGame);
        delay(200);



        stop = winDisplay();
    }

    pressSpace();

	return 0;
}
