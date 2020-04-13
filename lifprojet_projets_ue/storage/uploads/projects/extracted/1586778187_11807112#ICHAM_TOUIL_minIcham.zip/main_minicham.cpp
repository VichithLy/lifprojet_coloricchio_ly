#include <iostream>
#include <math.h>
#include <grapic.h>
#include <time.h>

using namespace grapic;
using namespace std;

const int DIMW=500;
const int MAX=50;







// ---------------------------------------------------------------------[ Structs ] ---------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



struct ObjColor //structure de simplification d'appel a une couleur
{
    int r, g, b, a;
};




//purple, yellow, orange, brown, grey;

struct ObjColor red = {255, 0, 0, 255};
struct ObjColor green = {0, 255, 0, 255};
struct ObjColor blue = {0, 0, 255, 255}; //------------ Presets de couleurs
struct ObjColor black = {0, 0, 0, 255};
struct ObjColor white = {255, 255, 255, 255};
struct ObjColor pink = {255, 100, 255, 255};









struct Point
{
    float x, y;
};

struct AABB//boite de collision rectangle
{
    float x, y, w, h;
};

struct Complex
{
    float x,y;
};

struct Vec
{
    float x, y;
};


struct Background//permet de definir une seconde couleur pour les objets
{
    ObjColor C;
    Vec p;
    float Tx, Ty;
};


struct palette
{
    Vec p, p2; // position de la palette, entre autres
    float Tx, Ty;//taille en x et y
    AABB BoxP;//non utilise, etait cense definir une boite de collision rectangle
    ObjColor C;//couleur
    Background B;//couleur
};



struct brique
{
    Vec p; //position actuelle
    Vec dp;// position de destination, sert pour l'animation
    float Tx, Ty; //taille de la brique en x et y
    bool bonus; //bonus, non utilise
    ObjColor C;//couleur
    Background B;//couleur
    bool isDisplayed;//renvoie vrai si la brique existe
};

struct balle2
{
    Vec p; //position
    Vec v; //vitesse
    float m; //masse, sert a faire tourner l'update en continu entre autres
    int r; //rayon
    ObjColor C; //couleur
    Background B; //couleur
    float norm; //norme du vecteur vitesse
};

Vec make_vec(float x, float y)//------------------------------------------------------------------------------------------------------------------------
{
    Vec v;
    v.x = x;
    v.y = y;
    return v;
}

Vec operator+(const Vec& a, const Vec& b)
{
    Vec r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    return r;
}

Vec operator-(const Vec& a, const Vec& b)//Fonctions de calcul entre deux vercteurs et creation de vecteurs, non utilisees mais pourraient l'etre pour optimiser le programme
{
    Vec r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    return r;
}

Vec operator+=(Vec& a, const Vec& b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

Vec operator*(float a, const Vec& b)//-----------------------------------------------------------------------------------------------------------------------------------------------------
{
    Vec r;
    r.x = a * b.x;
    r.y = a * b.y;
    return r;
}



/*struct Object
{
    palette p;
    brique b;
    Point P;
    Complex c;
    balle2 b2;
    ObjColor C;
};*/




struct Level // Structure du niveau en cours
{
    brique b[MAX][MAX]; // les differentes briques du niveau


    int nb2; //le nombre de balles
    balle2 b2[MAX];//tableau de balles


    palette p[MAX];//tableau de palettes, non utilisé ici
    Background B;// Une couleur
    ObjColor C;// Une couleur

    bool T; //Booleen pour la gestion du tracking

    int score; //Score
    int Timer; // Compteur de l'etat "game over"


    bool hit; // renvoie vrai quand il y a collision (ponctuel)

    bool isOver; // etat de "game over"



};


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------













// ----------------------------------------------------------------- [ Collision stuff ] ---------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



bool PBDroiteCollision(palette p, balle2 C)//Voir commentaires pour l'Axe X et appliquer a la palette
{
    // (I) unknown
    Point A , B;
    A.x = p.p.x;
    A.y = p.p.y + p.Ty;
    B.x = p.p.x + (p.Tx/2);
    B.y = p.p.y + p.Ty;



    Vec U; // Vec U = Vec AB
    U.x = B.x - A.x;
    U.y = B.y - A.y;

    Vec AC; // Vec AC = AC
    AC.x = C.p.x - A.x;
    AC.y = C.p.y - A.y;




    float numera = U.x*AC.y - U.y*AC.x;
    if (numera < 0)
    {
        numera = -numera;
    }
    float deno = sqrt((U.x*U.x) + (U.y*U.y));
    float CI = numera/deno;


    if (CI <= C.r)
    {
        return true;
    }


    return false;
}


bool CollisionPointBalle(float x, float y, balle2 C)//Gestion de la collision entre un point et une balle, fonction qui m'a servi au debuggage pour gerer les cas particuliers de balle touchant l'angle d'une brique
{
    float d2 = ((x-C.p.x)*(x-C.p.x) + (y-C.p.y)*(y-C.p.y));
    if (d2 <= (C.r*C.r))
    {
        return true;
    }

    return false;

}

bool PBSegmentCollision (palette p, balle2 C)//Voir commentaires pour l'Axe X et appliquer a la palette
{


    if (PBDroiteCollision(p, C) == false)
    {
        return false;
    }
    Point A, B, I;

    A.x = p.p.x;
    A.y = p.p.y + p.Ty;
    B.x = p.p.x + p.Tx;
    B.y = p.p.y + p.Ty;
    I.x = C.p.x;
    I.y = C.p.y;



    Vec AB, AI, BI;

    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    AI.x = I.x - A.x;
    AI.y = I.y - A.y;
    BI.x = I.x - B.x;
    BI.y = I.y - B.y;

    float pscal1 = AB.x*AI.x + AB.y* AI.y;
    float pscal2 = (-AB.x)*BI.x + (-AB.y)*BI.y;
    if (pscal1 >= 0 && pscal2 >=0)
    {
        return true;
    }

    /*if (CollisionPointBalle(A, C))
    {
        return true;
    }

    if (CollisionPointBalle(B, C))
    {
        return true;
    }*/

    return false;





}


















bool BBDroiteCollisionY(float x, float y, float Tx, float Ty, balle2 C, bool & isDisplayed)//Voir commentaires pour l'Axe X et appliquer a l'Axe Y
{


    if(isDisplayed==false)
    {
        return false;
    }

    // (I) unknown
    Point A , B;
    A.x = x;
    A.y = y;
    B.x = x + Tx;
    B.y = y;



    Vec U; // Vec U = Vec AB
    U.x = B.x - A.x;
    U.y = B.y - A.y;

    Vec AC; // Vec AC = AC
    AC.x = C.p.x - A.x;
    AC.y = C.p.y - A.y;




    float numera = U.x*AC.y - U.y*AC.x;
    if (numera < 0)
    {
        numera = -numera;
    }
    float deno = sqrt((U.x*U.x) + (U.y*U.y));
    float CI = numera/deno;


    if (CI <= C.r)
    {
        return true;
    }


    return false;
}

bool BBSegmentCollisionY(float x, float y, float Tx, float Ty, balle2 C, bool & isDisplayed)//Voir commentaires pour l'Axe X et appliquer a l'Axe Y
{



    if (BBDroiteCollisionY(x, y, Tx, Ty, C, isDisplayed) == false)
    {
        return false;
    }
    Point A, B, I;

    A.x = x;
    A.y = y;
    B.x = x + Tx;
    B.y = y;
    I.x = C.p.x;
    I.y = C.p.y;



    Vec AB, AI, BI;

    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    AI.x = I.x - A.x;
    AI.y = I.y - A.y;
    BI.x = I.x - B.x;
    BI.y = I.y - B.y;

    float pscal1 = AB.x*AI.x + AB.y* AI.y;
    float pscal2 = (-AB.x)*BI.x + (-AB.y)*BI.y;
    if (pscal1 >= 0 && pscal2 >=0)
    {
        return true;
    }

    /*if (CollisionPointBalle(A, C))
    {
        return true;
    }

    if (CollisionPointBalle(B, C))
    {
        return true;
    }

    return false;*/





}













void BBBouncingY(float x, float y, float Tx, float Ty, balle2 & b2, bool & isDisplayed, bool & hit) //Voir commentaires pour l'Axe X et appliquer a l'Axe Y
{



    if (BBSegmentCollisionY(x, y, Tx, Ty, b2, isDisplayed) == true)
    {
        b2.v.y = -b2.v.y;
        isDisplayed = false;
        hit = true;

    }




}









bool BBDroiteCollisionX(float x, float y, float Tx, float Ty, balle2 C, bool & isDisplayed)//Fonction booleenne de collision sur une droite sur l'axe X
{


    if(isDisplayed==false)
    {
        return false;
    }


    // (I) unknown
    Point A , B;
    A.x = x;
    A.y = y;
    B.x = x;
    B.y = y + Ty;



    Vec U; // Vec U = Vec AB
    U.x = B.x - A.x;
    U.y = B.y - A.y;

    Vec AC; // Vec AC = AC
    AC.x = C.p.x - A.x;
    AC.y = C.p.y - A.y;




    float numera = U.x*AC.y - U.y*AC.x; //utilisation du produit vectoriel adapté à un plan 2D pour predire l'arrivee de la balle sur une droite
    if (numera < 0)
    {
        numera = -numera;
    }
    float deno = sqrt((U.x*U.x) + (U.y*U.y));
    float CI = numera/deno;


    if (CI <= C.r)
    {
        return true;
    }


    return false; //permet une petite optimisation, si la balle ne touche pas une droite, alors on ira jamais verifier si elle touche les segments associés
}

bool BBSegmentCollisionX(float x, float y, float Tx, float Ty, balle2 C, bool & isDisplayed) //Fonction booleenne de collision sur segment sur l'axe X
{


    if (BBDroiteCollisionX(x, y, Tx, Ty, C, isDisplayed) == false)
    {
        return false;
    }
    Point A, B, I;

    A.x = x;
    A.y = y;
    B.x = x;
    B.y = y + Ty;
    I.x = C.p.x;
    I.y = C.p.y;



    Vec AB, AI, BI;

    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    AI.x = I.x - A.x;
    AI.y = I.y - A.y;
    BI.x = I.x - B.x;
    BI.y = I.y - B.y;

    float pscal1 = AB.x*AI.x + AB.y* AI.y;    //utilisation du produit scalaire pour definir un segment
    float pscal2 = (-AB.x)*BI.x + (-AB.y)*BI.y;
    if (pscal1 >= 0 && pscal2 >=0)
    {
        return true;
    }

    /*if (CollisionPointBalle(A, C))
    {
        return true;
    }

    if (CollisionPointBalle(B, C))
    {
        return true;
    }*/

    return false;





}



void BBBouncingX(float x, float y, float Tx, float Ty, balle2 & b2, bool & isDisplayed, bool & hit) //Procedure de collision pour l'Axe X
{


    if (BBSegmentCollisionX(x, y, Tx, Ty, b2, isDisplayed) == true)
    {
        b2.v.x = -b2.v.x;
        isDisplayed = false;
        hit = true;
    }




}










void CallBriqueCollision(brique B[MAX][MAX], balle2 & b2, bool & hit)//Appel aux differentes fonctions et procedures de gestion de la collision entre les balles et les briques
{
     int i, j;
     for(j=0; j<15; j++)
     {

        for (i=0; i<16; i++)
        {
            BBBouncingY(B[i][j].p.x, B[i][j].p.y, B[i][j].Tx, B[i][j].Ty, b2, B[i][j].isDisplayed, hit );
            BBBouncingY(B[i][j].p.x, B[i][j].p.y + B[i][j].Ty, B[i][j].Tx, B[i][j].Ty, b2, B[i][j].isDisplayed, hit);
            BBBouncingX(B[i][j].p.x, B[i][j].p.y, B[i][j].Tx, B[i][j].Ty, b2, B[i][j].isDisplayed, hit);
            BBBouncingX(B[i][j].p.x + B[i][j].Tx, B[i][j].p.y, B[i][j].Tx, B[i][j].Ty, b2, B[i][j].isDisplayed, hit);
            if (CollisionPointBalle( B[i][j].p.x, B[i][j].p.y, b2) || CollisionPointBalle( B[i][j].p.x + B[i][j].Tx, B[i][j].p.y, b2 ) || CollisionPointBalle( B[i][j].p.x, B[i][j].p.y + B[i][j].Ty, b2 ) || CollisionPointBalle( B[i][j].p.x + B[i][j].Tx, B[i][j].p.y + B[i][j].Ty, b2 ))
            {
                //b2.v.x = -b2.v.x;
                //b2.v.y = -b2.v.y;
                B[i][j].isDisplayed = false;
            }

        }
     }

}







// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



void collision(Level & L, balle2& b) //Collisions avec les murs de la fenetre, detection lorsque l'on touche le bas de la fenetre ==> On passe a l'etat "game over"
{
    int i;
        if (b.p.x < 0)
        {
            b.p.x = -b.p.x;
            b.v.x = -b.v.x;
            b.v =b.v;
        }

        if (b.p.y < L.b2[0].r)
        {
            b.v =b.v;
            L.isOver = true;
        }

        if (b.p.x >= DIMW)
        {
            b.p.x = DIMW-(b.p.x-DIMW);
            b.v.x = -b.v.x;
            b.v =b.v;
        }

        if (b.p.y >= DIMW)
        {
            b.p.y = DIMW - (b.p.y - DIMW);
            b.v.y = -b.v.y;
            b.v =b.v;

        }
}







void color(Background B)  //--------------------------------------------------------------------------------------------------------------------------------
{
    color(B.C.r, B.C.g, B.C.b, B.C.a);
}

void color(ObjColor C)
{
    color(C.r, C.g, C.b, C.a); // Procedures permettant d'utiliser des mots pour faire appel a des couleurs plutot qu'a leurs valeurs rgb
}

void backgroundColor(ObjColor Colors)
{
    backgroundColor(Colors.r, Colors.g, Colors.b, Colors.a); //--------------------------------------------------------------------------------------------------------------------------------
}


void colorShiftR(int & r, bool & rs, float & t)//Fonction de color shiftting pour le rouge :-)
{

    if (r>0 && t>1 && rs==true)
    {

        t = 0;

        r = r - 1;
    }
    if (r==0 && t>1 && rs==true)
    {
        rs=false;
    }
    if (r<255 && t>1 && rs==false)
    {
        t = 0;
        r = r + 1;
    }
    if (r==255 && t>1 && rs==false)
    {
        rs=true;
    }


}






void DisplayBrique(brique & b)//Gestion de l'affichage des briques
{

    if (b.isDisplayed==true)
    {


    color(black);
    rectangleFill(b.p.x, b.p.y, b.p.x + b.Tx, b.p.y + b.Ty);

    b.B.p.x = b.p.x + (0.12*b.Tx);
    b.B.p.y = b.p.y + (0.2*b.Ty);
    b.B.Tx = b.p.x + (0.88*b.Tx);
    b.B.Ty = b.p.y + (0.8*b.Ty);


    color(red);
    rectangleFill(b.B.p.x, b.B.p.y, b.B.Tx, b.B.Ty);
    }
}





void BriqueAnimation(brique & b, float & t)//Procedure d'animation des briques
{
    while (b.p.y > b.dp.y && t>1)
    {
        b.p.y = b.p.y - 1;
        t = 0;
    }

}

void CallAnimationBrique(brique B[MAX][MAX], float & t)//Procedure intermediaire d'appel a la fonction "d'animation" des briques en debut de partie
{
    int i,j;
    for(j=9; j>=0; j--)
    {
        for (i=0; i<16; i++)
        {
            BriqueAnimation(B[i][j], t);
        }
    }
}

void CallDisplayBrique(brique B[MAX][MAX]) //Procedure intermediaire d'appel a la fonction d'affichage des briques
{
    int i,j;
    for(j=0; j<10; j++)
    {
        for (i=0; i<16; i++)
        {
                DisplayBrique(B[i][j]);

        }
    }
}

void initBrique(brique B[MAX][MAX]) //Initialisation des briques
{
    int i, j;
    int a = 50, b = 400;

    for (j=0; j<10; j++)
    {
        b = b - 10;
        a = 50;
        for (i=0; i<16; i++)
        {
            B[i][j].p.x = a;
            B[i][j].Tx = 25;
            B[i][j].p.y = b;
            B[i][j].Ty = 10;
            B[i][j].dp.x = B[i][j].p.x;
            B[i][j].dp.y = B[i][j].p.y;
            B[i][j].p.y = B[i][j].p.y + 200;
            a = a + 25;
            B[i][j].isDisplayed = true;

        }
    }


}






void initBalle(balle2 B2[MAX], int nb2) // Initialisation des balles
{
    int i;
    int x, y;
    x = DIMW/2;
    y = DIMW/2;
    for (i=0; i<nb2; i++)
    {
        //B2[i].p.x = x;
        //B2[i].p.y = y;
        B2[i].v.x = 1;
        B2[i].v.y = 2;
        B2[i].m = 1;
        B2[i].r = 5;
        x = x + 10;
        y = y - 5;
        B2[i].C = red;
        B2[i].B.C = blue;
        B2[i].norm = sqrt((B2[i].v.x*B2[i].v.x)+(B2[i].v.y*B2[i].v.y));
        if (B2[i].v.y==0)
        {
            B2[i].v.y = 1;
        }

    }
}




void initCasse_Brique(palette& p, Level & L)// Initialisation des donnees necessaires pour le jeu
{






    L.nb2 = 1;
    p.p.x=DIMW/2 - 50;
    p.p.y=DIMW/2 - 180;
    p.Tx = 100;
    p.Ty = 10;
    p.C = black;
    p.B.C = red;
    initBrique(L.b);
    initBalle(L.b2, L.nb2);
    L.T = true;
    L.score = 0;
    L.hit = false;
    L.Timer = 5;
    L.isOver = false;





}






void paletteAngleBound(palette p, balle2 & b2, int nb2)//Permet de renvoyer la balle selon un angle different (logique) en fonction du point de collision sur la palette tout en conservant la norme du vecteur vitesse de base
{

    if (PBSegmentCollision(p, b2))
    {
        b2.v.x = cos((-3.14159/(p.Tx)*(b2.p.x-p.p.x)) + (3.14159)) * b2.norm;
        b2.v.y = sin((-3.14159/(p.Tx)*(b2.p.x-p.p.x)) + (3.14159)) * b2.norm;
        cout << "Collision" << endl;
    }

}


void movePalette(palette& p)//Procedure de mouvement de la palette
{
    if (isKeyPressed(SDLK_LEFT))
        if (p.p.x>0)
            p.p.x=p.p.x - 0.3;

    if (isKeyPressed(SDLK_RIGHT))
        if ((p.p.x + p.Tx)<DIMW)
            p.p.x=p.p.x + 0.3;

}



void ballePaletteTracking(palette & p, balle2 & b2) //Gestion du tracking balle/palette
{
        b2.p.x = p.p.x + (p.Tx/2);
        b2.p.y = p.p.y+p.Ty+b2.r;


}




void startThrow(palette & p, balle2 & b2, bool & T) //Pour le debut de la partie, gestion du tracking de la palette avec la balle
{
     if (T!=false)
    {

        ballePaletteTracking(p, b2);

        if (isKeyPressed(SDLK_SPACE))             // Lorsque l'on appuie sur espace, donne un vecteur vitesse vertical a la balle et arrete le tracking
        {
            b2.v.y = 3;
            b2.v.x = 0;
            T = false;
        }


    }
}


void updateScore(Level & L) //Procedure qui met a jour le score, a chaque brique detruite, le score augmente de 50, peu importe le nombre total de briques
{


    if(L.hit==true)
    {

        L.hit = false;
        L.score = L.score + 50;

    }




}



void DisplayHUD(Level & L) // Affichage du score et, si on est dans l'etat "game over" de la partie, affichage de l'ecran "game over" avec compteur
{


    fontSize(17);
    color(white);
    print(DIMW - 100, DIMW - 50, L.score);



    if(L.isOver==true)
    {
        fontSize(30);
        color(white);
        print(DIMW/2-90, DIMW/2 -100, "GAME OVER :(");
        print(DIMW/2, DIMW/2, L.Timer);
    }




}




void GameOver(palette & p, Level & L, float & t) //procedure de gestion de l'etat "game over", permet de reinitialiser la partie apres avoir perdu
{                                                //Pourrait etre associe a un nombre de vies





    if(L.isOver==true)
    {
        int time = t;

        if(L.Timer>0 && time==t)
        {
            L.Timer = L.Timer - 1;
            time = time + 1;
        }

        if(L.Timer==0)
        {
            initCasse_Brique(p, L);
        }
    }

}



void Draw(palette & p)     //Affichage de la palette a l'ecran
{
    p.p2.x = p.p.x + p.Tx;
    p.p2.y = p.p.y + p.Ty;

    color(p.C);
    rectangleFill(p.p.x, p.p.y, p.p2.x, p.p2.y);


    p.B.p.x = p.p.x + (0.1*p.Tx);
    p.B.p.y = p.p.y + (0.35*p.Ty);
    p.B.Tx = p.p.x + (0.9*p.Tx);
    p.B.Ty = p.p.y + (0.6*p.Ty);


    color(p.B);
    rectangleFill(p.B.p.x, p.B.p.y, p.B.Tx, p.B.Ty);
}



void Draw(balle2 b2[MAX], int nb2) //Affichage des balles a l'ecran(dans ce cas, une seule balle pour le jeu) et du vecteur vitesse associé
{

    for (int i=0; i<nb2; i++)
    {

        color(black);
        circleFill(b2[i].p.x, b2[i].p.y, b2[i].r);

        color(white);
        circleFill(b2[i].p.x,b2[i].p.y, 0.7*b2[i].r);

        fontSize(15);

        color(black);
        print(b2[i].p.x-40, b2[i].p.y-10, b2[i].v.x);

        color(black);
        print(b2[i].p.x+10, b2[i].p.y-10, b2[i].v.y);
    }
}







void updateCasse_Brique(palette & p, Level& L, float & t) //procedure de mise a jour(computing) des elements du jeu (Objets et leurs Affichages)
{
    const float dt = 0.1;


    startThrow(p, L.b2[0], L.T);
    GameOver(p, L, t);
    updateScore(L);
    DisplayHUD(L);



    if(L.isOver==false)
    {


        for (int i=0; i<L.nb2; i++)
        {


            if (L.b2[i].m>0)
            {

                L.b2[i].v = L.b2[i].v;    // mise à jour de la vitesse
                L.b2[i].p = L.b2[i].p + (dt*L.b2[i].v);               // mise à jour de la position
            }



            CallBriqueCollision(L.b, L.b2[i], L.hit);
            paletteAngleBound(p, L.b2[i], L.nb2);
            collision(L, L.b2[i]);
            CallDisplayBrique(L.b);
            CallAnimationBrique(L.b, t);
            Draw(p);
            movePalette(p);
            Draw(L.b2, L.nb2);

        }


    }


}






int main(int ,char**)
{


                                    //---------------------------------------------------------------------------------------------------------------------------------
    int r = 255, g = 255, b = 255; // Variables permettant de faire des ColorShift
    bool rs, gs, bs;               // Variables permettant de faire des ColorShift
    rs = true, gs = true, bs = true; // Variables permettant de faire des ColorShift

    Menu m;                         //---------------------------------------------------------------------------------------------------------------------------------
    //balle b;
    balle2 b2;
    palette p;
    Level L;
    bool stop=false;                // Initialisation du jeu
    winInit("MinIcham", DIMW, DIMW);
    setKeyRepeatMode(true);


    initCasse_Brique(p, L);
                            //---------------------------------------------------------------------------------------------------------------------------------


    while(!stop)
    {
        winClear();
        float t = elapsedTime();
        backgroundColor(r, pink.g, pink.b, pink.a );
        menu_draw(m, 5,5, 100, 102);
        updateCasse_Brique(p, L, t);
        colorShiftR(r, rs, t);
        stop=winDisplay();

    }
    winQuit();
    return 0;
}
