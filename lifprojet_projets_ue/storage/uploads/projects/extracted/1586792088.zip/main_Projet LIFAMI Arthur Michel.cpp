#include <cmath>
#include <Grapic.h>
#include<stdio.h>
#include <math.h>
#include<iostream>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
using namespace std;
using namespace grapic;
int const DIMW = 670;
const int NMAX = 10000;
const float FRICTION = 0.60f;



// Gestion des images
struct Image_prog
{
        Image spectre ;
        Image carre ;
        Image flecheg;
        Image fleched;
        Image lien;
        Image bombe;
        Image menu2;
        Image flechemenu;
        Image menu1;
        Image Gameover;
        Image bouton_menu;
        Image bouton_rejouer;
        Image bouton_espace;
        Image bouton_valider;
        Image bouton_jouer;
        Image bouton_regle1;
        Image bouton_regle2;

    };
void initImage_prog (Image_prog & imp)
{
    imp.spectre = image("data/Carre_magique/Spectre.png");
    imp.carre = image("data/Carre_magique/Carre.png");
    imp.flecheg = image("data/Carre_magique/FlecheG.png");
    imp.fleched = image("data/Carre_magique/FlecheD.png");
    imp.lien = image ("data/Carre_magique/Lien.png");
    imp.bombe = image ("data/Carre_magique/Bombe.png");
    imp.menu2 = image ("data/Carre_magique/Menu2.png");
    imp.flechemenu = image ("data/Carre_magique/flechmenupr.png");
    imp.menu1 = image ("data/Carre_magique/Menu1.png");
    imp.Gameover = image ("data/Carre_magique/GAMEOVER.png");
    imp.bouton_menu = image ("data/Carre_magique/bouton_menu.png");
    imp.bouton_rejouer = image ("data/Carre_magique/bouton_rejouer.png");
    imp.bouton_espace = image ("data/Carre_magique/bouton_espace.png");
    imp.bouton_valider = image ("data/Carre_magique/bouton_valider.png");
    imp.bouton_jouer = image ("data/Carre_magique/bouton_jouer.png");
    imp.bouton_regle1 = image ("data/Carre_magique/bouton_regle1.png");
    imp.bouton_regle2 = image ("data/Carre_magique/bouton_regle2.png");
}


//Les fonctions suivantes permettent de fabriquer un carré magique

void initialiser(int t[20][20], int n) //Fonction d'initialisation du tableau (carre magique)
{
	int i, j;
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			t[i][j] = 0;
		}
	}
	t[n][(n+1)/2] = 1;
}
int est_magique(int t[20][20], int n)  // retourne 1 si le tableau est un carre magique
{
	int i, j;
	int s = 0;
	int const_magique = n * (n * n + 1) / 2;

	//Somme des lignes
	for(i=1; i<=n; i++)
        {
		s = 0;
		for(j=1; j<=n; j++)
            {
            s = s + t[i][j];
            }
		if(s != const_magique)
            {
			return 0;
            }
        }

	//Somme des colonnes
	for(i=1; i<=n; i++)
        {
		s = 0;
		for(j=1; j<=n; j++)
            {
			s = s + t[j][i];
            }
		if(s != const_magique)
            {
			return 0;
            }
        }

	//Somme des diagonales
	s = 0;
	for(i=1; i<=n; i++)
        {
		s = s + t[i][i];
        }
	if(s != const_magique)
        {
		return 0;
        }

	s = 0;
	for(i=1; i<=n; i++)
        {
		s = s + t[i][n-i+1];
        }
	if(s != const_magique)
        {
		return 0;
        }

	return 1;

}
void placer(int t[20][20], int n, int i, int j) //Fonction récursive qui permet de construire le carre magique d'ordre n
{
	if(est_magique(t,n))
    {
		return;
	}
	else
    {

		int k = t[i][j];
		int i1 = i;
		int j1 = j;
		if(i == n)
            {
				i = 0;
			}
        if(j == n)
            {
				j = 0;
			}
		if(t[i+1][j+1] == 0)
            {
			t[i + 1][j + 1] = k + 1;
			placer(t, n, i+1, j+1);
            }
		else
            {
			t[i1 - 1][j1] = k + 1;
			placer(t, n, i1-1, j1);
            }

	}
}
void spectre (int Rouge [103], int Vert [103],int Bleu [103]) // Creation de trois tableau comportant les variations de couleur
{
int sr=255;
int sv=0;
int sb=0;

Rouge[0]= sr;
Vert[0]=sv;
Bleu[0]=sb;

for (int i = 1;i<=17;i++)
{
    sv=sv+15;
    Rouge [i]= sr;
    Vert[i]=sv;
    Bleu[i]=sb;


}
for (int i = 18;i<=34;i++ )
{
    sr=sr-15;
    Rouge[i]= sr;
    Vert[i]=sv;
    Bleu[i]=sb;


}
for (int i = 35;i<=51;i++ )
{
    sb=sb+15;
    Rouge[i]= sr;
    Vert[i]=sv;
    Bleu[i]=sb;


}
for (int i = 52;i<=68;i++ )
{
    sv=sv-15;
    Rouge[i]= sr;
    Vert[i]=sv;
    Bleu[i]=sb;


}
for (int i = 69;i<=85;i++ )
{
    sr=sr+15;
    Rouge[i]= sr;
    Vert[i]=sv;
    Bleu[i]=sb;


}
for (int i = 86;i<=102;i++ )
{
    sb=sb-15;
    Rouge[i]= sr;
    Vert[i]=sv;
    Bleu[i]=sb;
}
}
void traduction (int t[20][20], float t1[20][20], int n ) //Les etapes de traduction transforment les valeurs du carré magique en gradient autour du centre
{
	int i, j;
	for(i=1; i<=n; i++)
        {
		for(j=1; j<=n; j++)
            {
            t1[i][j] =(float)t[i][j]/(float)((n*n)+1);
            }
        }

}
void traduction2 ( float t1[20][20], int n )
{
	int i, j;
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			 t1[i][j] =(t1[i][j]+0.500000)-1;
		}
	}

}
void traduction3 ( int colorcible, int t[20][20],float t1[20][20], int n )
{
	int i, j;
	for(i=1; i<=n; i++)
        {
		for(j=1; j<=n; j++)
            {
            t[i][j] =(int)(t1[i][j]*34)+colorcible; // C'est ici qu'on change la couleur cible
            if ((t[i][j])<0)
                {
                t[i][j] = (int)t[i][j]+102;
                }
            if ((t[i][j])>=102)
                {
                t[i][j] = (int)t[i][j]-102;
                }
            }
        }

}
void variation (int &colorcible) // Permet de faire varier la couleur cible
{
       colorcible = colorcible +1;
       if (colorcible >=103)
       {
           colorcible =colorcible -102;
       }
}



//OUTILS
struct Vec2
{
	float x, y;
};
struct Particle
{
	Vec2 p;        // position
	Vec2 v;        // vitesse
	Vec2 f;        // force
	int col;
	float m;        // masse
};
struct World
{
	Particle part[NMAX];        // tableau de particules
	int np;                     // nombre de particules
	float dt;                   // le pas de temps

};
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
Vec2 make_vec2(float x, float y)
{
    Vec2 r;
    r.x = x;
    r.y = y;
    return r;
}
Vec2 operator*(Vec2 a, Vec2 b)
{
    Vec2 c = make_vec2( a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x );
    return c;
}


// Gestion des obstacles pour le jeu
void shuffle ( int tab[500], size_t n)
{
    int i, j;
    int temp;
    if( n == 1 )
        return;
    srand(time(NULL));
    for( i=0; i< n-1; i++)
    {
        j = i + rand() % (n-i);
        temp = tab[i];
        tab[i] = tab[j];
        tab[j] = temp;
    }
}
struct position
{
   Vec2 part[NMAX];
};
void collision(World& d, int n,position p, int indice_couleur,int AvcmentObst,Menu& m,int&score_jeux, int n2)
{
	for (int i = 0; i <=(n*n-1); ++i)
	{
    if (d.part[i].p.y < p.part[i].y )
		{
			d.part[i].p.y = p.part[i].y;
			d.part[i].v.y = 0;
		}
    // si on touche une couleur
    if ((d.part[i].p.y >=((DIMW/n2)*indice_couleur)-10) && (d.part[i].p.y<=((DIMW/n2)*indice_couleur)+20) && (d.part[i].p.x>=AvcmentObst-15) && (d.part[i].p.x<=AvcmentObst+15))
        {
        score_jeux ++;
        }
    // si on touche une bombe
    for (int j =0;j<=n2;j++)
        {
        if (j!=indice_couleur)
            {
            if ((d.part[i].p.y >=((DIMW/n2)*j)-10) && (d.part[i].p.y<=((DIMW/n2)*j)+25) && (d.part[i].p.x>=AvcmentObst-15) && (d.part[i].p.x<=AvcmentObst+15))
                {
                menu_setSelect(m,9);
                }
            }
        }

	}


}
void inittabempl(int tab_emplcment_obst[500],int n2)
{
  for(int i =0;i<=n2;i++)
{
    tab_emplcment_obst[i]=i;
}
shuffle(tab_emplcment_obst,n2+1);
}
void obstacle (World w,Image_prog imp, int& AvcmentObst,int tab_emplcment_obst[500],int& n2,int Rouge [103],int Vert [103],int Bleu [103],int & indice_couleur,int& colorjeux, int indices_bombes, int score_jeux)
{
int tab_inter[20];

    if (AvcmentObst!=0)
    {
        for (int i =0;i<=n2;i++)
        {
            if (tab_emplcment_obst[i]==1)
            {
                    color(Rouge [w.part[colorjeux].col],Vert [w.part[colorjeux].col],Bleu [w.part[colorjeux].col]);
		            circleFill( AvcmentObst, (DIMW/n2)*i  , 18);
                    indice_couleur = i;
            }
            else
            {
                    image_draw(imp.bombe, AvcmentObst-15, ((DIMW/n2)*i)-10);

            }

        }
            AvcmentObst=AvcmentObst-0.01f;
    }
    if (AvcmentObst==0)
    {
        AvcmentObst=DIMW;

        colorjeux=irand(0,(3*3)-1);
        if (score_jeux>=3000)
        {
                    n2=5;
        }
        if (score_jeux>=10000)
        {
                    n2=6;
        }
        inittabempl(tab_emplcment_obst,n2);

    }
    for (int i = 0; i<=n2;i++)
    {
        if (tab_emplcment_obst[i]==1)
        {
            i=i+1;
        }
       tab_inter[i]=tab_emplcment_obst[i];
    }



}



//Initialisation et affichage du carré magique
int addPart(World& d, float x, float y, int col)
{
    int i = d.np;



    d.part[i].p.x = x;
    d.part[i].p.y = y;
    d.part [i].col = col;

    d.part[i].v.x = 0;
    d.part[i].v.y = 0;

    d.np++;
    return d.np-1;
}
void initworld(World& d,int score[20][20],int n, int centre_x,int centre_y, int larg)
{          d.dt=0.005f;
           d.np=0;
           for(int i=1; i<=n; i++)
            {
                for(int j=1; j<=n; j++)
                    {
                    float x=(centre_x+(larg/(((n+1)/2)-1))*(j-((n+1)/2)));
                    float y=centre_y+(larg/(((n+1)/2)-1))*(-(i-((n+1)/2)));
                    int col = score[i][j];
                    addPart(d ,x ,y, col);
                    }
            }

}
void drawWord(World& d,  int Rouge [103],int Vert [103],int Bleu [103],int n,int RADIUS)
{
	int i;
	for (i = 0; i < d.np; ++i)
	{
		color(Rouge [d.part[i].col],Vert [d.part[i].col],Bleu [d.part[i].col]);
        circleFill( d.part[i].p.x, d.part[i].p.y, RADIUS);
	}
    color(255,0,0);
}


// Gestion des particules du carré magique
void updateParticle(World& d, float dt, int n)
{
	int i;
int dtt =0 ;

            d.part[((n*n)-1)/2].v = d.part[((n*n)-1)/2].v + (dt/d.part[((n*n)-1)/2].m)*d.part[((n*n)-1)/2].f;
            d.part[((n*n)-1)/2].p = d.part[((n*n)-1)/2].p+ dt*d.part[((n*n)-1)/2].v;
            d.part[((n*n)-1)/2].f.x = 0;
            d.part[((n*n)-1)/2].f.y = 0;

    for (i=0;i<n;i++)
    {
        if (d.part[i].m>0 && ((i*n)+((n-1)/2))!=((n*n)-1)/2)
        {
        d.part[(i*n)+((n-1)/2)].p = d.part[(i*n)+((n-1)/2)].p + dt*d.part[((n*n)-1)/2].v;
        }
    }
    for (i=0;i<=(n-1);i++)
    {
        for (int j=0;j<(n-1)/2;j++)
        {

        d.part[(i*n)+j].p = d.part[(i*n)+j].p + (dt)*d.part[((n*n)-1)/2].v;
        d.part[((n-1)-j)+i*n].p.y = d.part[(i*n)+j].p.y;
        }
     }



}
void saveposition(position& p,World d, int n)
{
    for (int i =0;i<=(n*n-1);i++)
    {
          p.part[i]=make_vec2(d.part[i].p.x,d.part[i].p.y);
    }

}
void computeParticleForceGravityEarth(World& d)
{
	int i,j;
	const float G = 9.81f;
	for (i = 0; i < d.np; ++i)
	{
        d.part[i].f.x = 0;
        d.part[i].f.y = -d.part[i].m * G;
	}
}
void computeParticleForceUser(World& d)
{
	int i,j;
    int G= 9;
	for (i = 0; i < d.np; ++i)
	{
        d.part[i].v.x = 0;
        d.part[i].v.y =  G*d.part[i].m;
	}
}
void addpion(World& dat, int n)
{
    float poidmax=4;
    for (int i = 0; i<= (n*n)-1;i++)
    {
         dat.part[i].m=poidmax;
    }
}
void update(World& d,int& space,int n,position p,int indice_bombe,int AvcmentObst,Menu& m, int& score_jeux, int n2)
{

    for(int i=0;i<10;++i)
    {

        computeParticleForceGravityEarth(d);
        if (space !=0)
            {
            computeParticleForceUser(d);
            }
        space =0;
        updateParticle(d, d.dt,n);
        collision(d,n,p,indice_bombe,AvcmentObst,m,score_jeux, n2);


    }
}



// Animation lors d'une variation de la couleur cible
void Rectangle_RVB (int Rouge [103],int Vert [103],int Bleu [103],int i)
{
    color (255,0,0);
    rectangleFill(345, 60, 360, 60+(Rouge[i])*0.22);
    color (0,255,0);
    rectangleFill( 365,  60,  380,60+ (Vert[i])*0.22);
    color (0,0,255);
    rectangleFill( 385,  60,  400, 60+(Bleu[i])*0.22);
    color(125,125,125);
    line (340,60,403,60);
}




int main(int , char** )
{
    int AvcmentObst=670;
    int apparitionColor = irand(0,500);
    int AvcmentColor = 670;
    int tab_emplcment_obst[500];
    int indice_couleur ;
    int colorjeux;
    int score_jeux=0;
    int indices_bombes=0;


	int A[20][20];
	int n ;
    int n2;
	float Afin[20][20];
	int score[20][20];

    int colorcible=0;
    int indice = 0;

    int Rouge [103];
    int Vert [103];
    int Bleu [103];
    spectre(Rouge,Vert,Bleu);

    int centre_x;
    int centre_y ;
    int larg ;
    int RADIUS=8.85;

    World w;
    position p;

    Menu m;
    menu_add( m, " ");
    menu_add( m, "**Choix taille**");
    menu_add( m, "Rouge");
    menu_add( m, "Vert");
    menu_add( m, "Bleu");
    menu_add( m, "Aléatoir");
    menu_add( m, "->Votre sélection<-");
    menu_add( m, "**Mini-jeux**");
    menu_add( m, "**Manipulation**");
    menu_add( m, "Rotation45°");
    menu_add( m, "Gravité" );



    bool stop=false;
	winInit("Couleurs magiques", DIMW, DIMW);
    Image_prog imp ;
    initImage_prog(imp);
    backgroundColor( 0, 0, 0 );

    int space;

	while( !stop )
    {
        winClear();
        switch(menu_select(m))
        {
            case 0 :

            color (255,255,255);
            fontSize(45);
            print(65,570,"Carré magique des couleurs  ");
            fontSize(15);
            print(70,365,"Carré magique (3*3)");
            image_draw( imp.carre, 75, 380, 114, 131);
            print(445,282,"Spectre des couleurs ");
            print(445,271," (synthèse additive)");
            image_draw( imp.spectre, 450, 300, 120, 60);
            image_draw( imp.flechemenu,0,0);
            n=3;
            n2=3;
            initialiser(A, n);
	        placer(A, n, n , (n+1)/2);
            traduction(A,Afin, n);
            traduction2(Afin, n);
            variation(colorcible);
            traduction3(colorcible,score,Afin, n);
            centre_x =248;
            centre_y =100;
            larg = 70;
            initworld(w,score,n, centre_x,centre_y,larg);
            drawWord(w,Rouge,Vert,Bleu,n,RADIUS);
            image_draw( imp.bouton_espace, 570, 5);
            if (isKeyPressed(SDLK_SPACE))
                {
                      menu_setSelect(m,1);
                }
            delay(50);
            break;



            case 1 :
            RADIUS=8.85;
            color (255,255,255);
            fontSize(50);
            print(275,580,"Menu  ");
            fontSize(30);
            print(10,430,"Le jeu  -->" );
            print(10,140,"Bonus   -->" );
            image_draw( imp.menu1, 160, 20);
            image_draw( imp.menu2, 160, 320);
            image_draw( imp.bouton_regle1, 495, 340);
            image_draw( imp.bouton_regle2, 495, 100);

            int x,y;
            mousePos(x,y);
            if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>150) && (y>20) && (x<500) && (y<280))
                {
                    menu_setSelect(m,2);
                }
            if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>150) && (y>320) && (x<500) && (y<580))
                {
                    menu_setSelect(m,3);
                }
            break;





                case 2 :

                initialiser(A, n);
                placer(A, n, n , (n+1)/2);
                traduction(A,Afin, n);
                traduction2(Afin, n);
                variation(colorcible);
                traduction3(colorcible,score,Afin,n);
                centre_x =340;
                centre_y =345;
                larg = 200;
                initworld(w,score,n, centre_x,centre_y,larg);

                switch(n)
                {
                    case 3: RADIUS =50.00; break;
                    case 5: RADIUS =40.00; break;
                    case 7: RADIUS =30.00; break;
                    case 9: RADIUS =23.00; break;
                    case 11: RADIUS =18.00; break;
                    case 13: RADIUS =15.00; break;
                    case 15: RADIUS =13.00; break;
                    case 17: RADIUS =11.00; break;
                    case 19: RADIUS =10.00; break;

                }
                drawWord(w,Rouge,Vert,Bleu,n,RADIUS);


                mousePos(x,y);
                if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>196) && (y>30) && (x<263) && (y<87))
                {
                n=n-2;
                if (n<3)
                {
                    n=19;
                    RADIUS=5;
                }
                winClear();
                }
                if (isKeyPressed(SDLK_LEFT))
                {
                n=n-2;
                if (n<3)
                {
                    n=19;
                }
                winClear();
                }
                if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>337) && (y>30) && (x<404) && (y<87))
                {
                n=n+2;
                if (n>19)
                {
                    n=3;
                }
                    winClear();
                }
                if (isKeyPressed(SDLK_RIGHT))
                {
                n=n+2;
                if (n>19)
                {
                    n=3;
                }
                      winClear();

                }
                image_draw( imp.flecheg, 237, 45);
                image_draw( imp.fleched,378,45);
                fontSize(50);
                print(318,45,n );
                image_draw( imp.bouton_menu, 10, 40);
                mousePos(x,y);
                if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>10) && (y>40) && (x<153) && (y<93))
                {
                menu_setSelect(m,1);
                }
                delay(50);
                break;






                case 3 :
                initialiser(A, n);
                placer(A, n, n , (n+1)/2);
                traduction(A,Afin, n);
                traduction2(Afin, n);
                variation(colorcible);
                traduction3(colorcible,score,Afin,n);
                n=3;
                RADIUS=8.85;
                color (255,255,255);
                fontSize(40);
                print(190,565,"Choix de la couleur  ");
                image_draw( imp.bouton_valider, 15, 230);

                if (isKeyPressed(SDLK_SPACE))
                {
                      menu_setSelect(m,7);

                }
                traduction3(colorcible,score,Afin, n);
                colorcible =  102;
                centre_x =365;
                centre_y =345;
                larg = 120;
                initworld(w,score,n, centre_x,centre_y,larg);
                drawWord(w,Rouge,Vert,Bleu,n,RADIUS);
                image_draw( imp.flecheg, 266, 60);
                image_draw( imp.fleched,407,60);
                Rectangle_RVB (Rouge,Vert,Bleu ,colorcible);

                int xclik,yclik;
                mousePos(xclik,yclik);
                if ((isMousePressed(SDL_BUTTON_LEFT)) && (xclik>196) && (yclik>30) && (xclik<263) && (yclik<87))
                {
                menu_setSelect(m,6);
                }
                if (isKeyPressed(SDLK_LEFT))
                {
                menu_setSelect(m,6);

                }
                if ((isMousePressed(SDL_BUTTON_LEFT)) && (xclik>337) && (yclik>30) && (xclik<404) && (yclik<87))
                {
                    menu_setSelect(m,4);
                }
                if (isKeyPressed(SDLK_RIGHT))
                {
                      menu_setSelect(m,4);

                }
                break;





                case 4 :
                color (255,255,255);
                fontSize(40);
                print(190,565,"Choix de la couleur  ");
                image_draw( imp.bouton_valider, 15, 230);
                if (isKeyPressed(SDLK_SPACE))
                {
                      menu_setSelect(m,7);

                }
                traduction3(colorcible,score,Afin, n);
                colorcible =  34;
                centre_x =365;
                centre_y =345;
                larg = 120;
                initworld(w,score,n, centre_x,centre_y,larg);
                drawWord(w,Rouge,Vert,Bleu,n,RADIUS);
                image_draw( imp.flecheg, 266, 60);
                image_draw( imp.fleched,407,60);
                Rectangle_RVB (Rouge,Vert,Bleu ,colorcible);
                mousePos(x,y);
                if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>196) && (y>30) && (x<263) && (y<87))
                {
                menu_setSelect(m,3);
                }
                if (isKeyPressed(SDLK_LEFT))
                {
                menu_setSelect(m,3);

                }
                if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>337) && (y>30) && (x<404) && (y<87))
                {
                    menu_setSelect(m,5);
                }
                if (isKeyPressed(SDLK_RIGHT))
                {
                      menu_setSelect(m,5);

                }
                break;





                case 5 :
                color (255,255,255);
                fontSize(40);
                print(190,565,"Choix de la couleur  ");
                image_draw( imp.bouton_valider, 15, 230);
                if (isKeyPressed(SDLK_SPACE))
                {
                      menu_setSelect(m,7);

                }
                traduction3(colorcible,score,Afin, n);
                colorcible =  68;
                centre_x =365;
                centre_y =345;
                larg = 120;
                initworld(w,score,n, centre_x,centre_y,larg);
                drawWord(w,Rouge,Vert,Bleu,n,RADIUS);
                image_draw( imp.flecheg, 266, 60);
                image_draw( imp.fleched,407,60);
                Rectangle_RVB (Rouge,Vert,Bleu ,colorcible);

                mousePos(x,y);
                if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>196) && (y>30) && (x<263) && (y<87))
                {
                menu_setSelect(m,4);
                }
                if (isKeyPressed(SDLK_LEFT))
                {
                menu_setSelect(m,4);

                }
                if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>337) && (y>30) && (x<404) && (y<87))
                {
                    menu_setSelect(m,6);
                }
                if (isKeyPressed(SDLK_RIGHT))
                {
                      menu_setSelect(m,6);
                }
                break;




            case 6 :
            color (255,255,255);
            fontSize(40);
            print(190,565,"Choix de la couleur  ");
            image_draw( imp.bouton_valider, 15, 230);
            if (isKeyPressed(SDLK_SPACE))
            {
            menu_setSelect(m,7);
            }
            traduction3(colorcible,score,Afin, n);
            variation(colorcible);
            centre_x =365;
            centre_y =345;
            larg = 120;
            initworld(w,score,n, centre_x,centre_y,larg);
            drawWord(w,Rouge,Vert,Bleu,n,RADIUS);
            image_draw( imp.flecheg, 266, 60);
            image_draw( imp.fleched,407,60);
            Rectangle_RVB (Rouge,Vert,Bleu ,colorcible);

            mousePos(x,y);
            if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>196) && (y>30) && (x<263) && (y<87))
                {
                menu_setSelect(m,5);
                }
            if (isKeyPressed(SDLK_LEFT))
                {
                menu_setSelect(m,5);

                }
            if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>337) && (y>30) && (x<404) && (y<87))
                {
                    menu_setSelect(m,3);
                }
            if (isKeyPressed(SDLK_RIGHT))
                {
                      menu_setSelect(m,3);

                }
            delay(50);
            break;





            case 7 :
            color (255,255,255);
            fontSize(40);
            print(242,580,"Votre sélection  ");
            image_draw( imp.bouton_jouer, 15, 230);
            if (isKeyPressed(SDLK_SPACE))
            {
                traduction3(colorcible,score,Afin, n);
                centre_x =150;
                centre_y =43;
                larg = 43;
                initworld(w,score,n, centre_x,centre_y,larg);
                saveposition(p,w,n);
                addpion(w,n);

                colorjeux=irand(0,(n*n)-1) ;
                inittabempl(tab_emplcment_obst,n);
                menu_setSelect(m,8);

            }

            initworld(w,score,n,centre_x,centre_y,larg);
            drawWord(w,Rouge,Vert,Bleu,n,RADIUS);
            break;






            case 8:
            obstacle(w,imp,AvcmentObst,tab_emplcment_obst,n2,Rouge,Vert,Bleu,indice_couleur,colorjeux, indices_bombes, score_jeux);
            update(w,space,n,p,indice_couleur ,AvcmentObst,m,score_jeux,n2);
            drawWord(w,Rouge,Vert,Bleu,n,RADIUS);
            if (isKeyPressed(SDLK_SPACE))
                {
                    space =1;
                }
                fontSize(40);
                color (200,200,200);
                print(420,630," score :  ");
                print(560,628,score_jeux);
                break;





            case 9:
                computeParticleForceGravityEarth(w);
                updateParticle(w, w.dt,n);
                drawWord(w,Rouge,Vert,Bleu,n,RADIUS);
                color (200,200,200);
                rectangleFill(250,120,535,170);
                color (0,0,0);
                image_draw( imp.Gameover, 80, 300);
                image_draw( imp.bouton_menu, 10, 150);
                image_draw( imp.bouton_rejouer, 10, 60);
                print(275,122,"Score :  ");
                print(405,122,score_jeux);
                mousePos(x,y);
                if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>10) && (y>150) && (x<153) && (y<203))
                {
                    AvcmentObst=0;
                    score_jeux=0;
                    n2=3;
                   menu_setSelect(m,1);
                }
                if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>10) && (y>60) && (x<193) && (y<123))
                {
                    AvcmentObst=0;
                    score_jeux=0;
                    n2=3;
                   menu_setSelect(m,8);
                }


                break;
        }
        stop = winDisplay();



    }
winQuit();
return 0;

}
