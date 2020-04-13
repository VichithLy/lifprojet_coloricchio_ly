#include <My_library/Grapic.h>
#include <iostream>

#define largeur 400
#define hauteur 100

using namespace std;
using namespace grapic;

double puissance_entiere ( double x, int puissance );

const int FRICTION = 0.99;
const int DIMW     = 900;
const double DESTROY  = 10;
const double G     = 6.67 * 1 / puissance_entiere ( 10, 11 ); // 1 / puissance_entiere ( 10, 11 ) = 10⁻¹¹ 
const int MAX_TROU_NOIR = 16;
const int MAX_MUR       = 64;
const int MAX_TAB = 64;

float valeur_absolue ( float x )
{
    if ( x >= 0 )
    {
        return x;
    }
    if ( x <= 0 )
    {
        return -x;
    }
}

double puissance_entiere ( double x, int puissance )
{
    double x_prime = x;
    for ( int i = 0; i < puissance - 1; i++ )
    {
        x = x * x_prime;
    }

    return x;
}

/* ----------------------VECTEUR---------------------- */
struct Vect
{
    float x;
    float y;
};

void debug_vect ( Vect v )
{
    cout<<v.x<<" ; "<<v.y<<endl;
}

const Vect VECTEUR_NUL = { 0, 0 };

Vect make_vector ( float x, float y )
{
    Vect c;
    c.x = x;
    c.y = y;

    return c;
}

Vect operator+ ( Vect a, Vect b )
{
    Vect c = make_vector ( a.x + b.x, a.y + b.y );

    return c;
}

Vect operator+= ( Vect a, Vect b )
{
    a = a + b;

    return a;
}

Vect operator- ( Vect a, Vect b )
{
    Vect c = make_vector ( a.x - b.x, a.y - b.y );

    return c;
}

Vect operator* ( float scalaire, Vect a )
{
    Vect c = make_vector ( scalaire * a.x, scalaire * a.y );

    return c;
}

Vect operator* ( Vect a, float scalaire ) 
{
    Vect c = make_vector ( scalaire * a.x, scalaire * a.y );

    return c;
}

Vect operator/ ( Vect a, float scalaire ) 
{
    Vect c = make_vector ( a.x / scalaire, a.y / scalaire );

    return c;
}

float norme ( Vect v ) // Retourne la norme d'un vecteur
{
    return sqrt ( v.x * v.x + v.y * v.y );
}

float distance_vect ( Vect a, Vect b )
{
    return norme ( make_vector ( a.x - b.x, a.y - b.y ) );
}

float normalise ( Vect & v ) // Normalise un vecteur passé en paramètre et retourne sa norme
{
    float n = norme ( v );
    v.x = v.x / n;
    v.y = v.y / n;

    return n;
}

Vect vecteur_unitaire ( Vect v )
{
    float n = norme ( v );
    v.x = v.x / n;
    v.y = v.y / n;

    return v;
}

Vect normale (Vect a, Vect b) 
{
    Vect u = {b.x - a.x, b.y - a.y};
    Vect n = {u.y, -u.x};

    return n;
}

Vect unitaire (Vect a)
{
    float n = norme (a);
    Vect b;
    b.x = a.x / n;
    b.y = a.y / n;

    return b;
}

float produit_scalaire (Vect a, Vect b)
{
    float c;
    c = a.x * b.x + a.y * b.y;

    return c;
}

/*--------------------FONCTION----------------------*/
/* Cette partie sert à avoir une droite formant un angle droit avec les mur inclinés afin de détecter les colisions */
struct Fonction
{
    float ax;
    float b;
};

Fonction equation_droite (Vect a, Vect b)
{
    float equation = (b.y - a.y) / (b.x - a.x);
    float cste = a.y - equation * a.x;
    Fonction fct;
    fct.ax = equation;
    fct.b = cste;

    return fct;
}

Fonction oppoose_reciproque (Fonction f, Vect a) // Renvoie -f⁻¹(x) d'une fonction donée passant par un point précis, on effecutera donc une translation.
{
    Fonction g;
    g.ax = -1 / f.ax;
    g.b = -g.ax * a.x + a.y;

    return g;
}

/* -----------------------PARTICLE----------------------- */

struct Particle
{
    Vect pos;
    Vect vit;
    Vect force;
    float masse;
    Vect a;
};

void collision_fenetre ( Particle & p, int DIMW, int FRICTION )
{
    if ( p.pos.x <= 0 )
    {
        p.vit.x = -p.vit.x;
        p.vit = p.vit * FRICTION;
        p.pos.x = 1;
    }
    if ( p.pos.y <= 0 )
    {
        p.vit.y = -p.vit.y;
        p.vit = p.vit * FRICTION;
        p.pos.y = 1;
    }
    if ( p.pos.x >= DIMW )
    {
        p.vit.x = -p.vit.x;
        p.vit = p.vit * FRICTION;
        p.pos.x = DIMW - 1;
    }
    if ( p.pos.y >= DIMW )
    {
        p.vit.y = -p.vit.y;
        p.vit = p.vit * FRICTION;
        p.pos.y = DIMW - 1;
    }
}

void update_particule ( Particle & p )
{
    float t    = 0.2;
    Vect a = p.force / p.masse;
    p.vit = p.vit + a * t;
    p.pos = p.pos + p.vit * t;
    p.force = VECTEUR_NUL;
    // F = m.a -> a = F/m

    collision_fenetre ( p, DIMW, 1 ); // 1 pour pas de friction
}

struct Mur
{
    Vect mini; // Position
    Vect maxi; // Position
    float largeur_im;
    float hauteur_im;
};

Mur init_Mur (Vect mini, Vect maxi)
{
    Mur m;

    m.mini = mini;
    m.maxi = maxi;
    m.hauteur_im = valeur_absolue (m.mini.y - m.maxi.y);
    m.largeur_im = valeur_absolue (m.mini.x - m.maxi.x);

    return m;
}

void draw_Mur (Mur m, Image im)
{
    image_draw (im, m.mini.x, m.mini.y, m.largeur_im, m.hauteur_im);
}

struct Mur_incline // Ce sera des triangles 
{
    Vect a;
    Vect b;
    Vect c;
};

Mur_incline init_Mur_incline (Vect a, Vect b, Vect c)
{
    Mur_incline m;
    m.a = a;
    m.b = b;
    m.c = c;

    return m;
}

void draw_Mur_incline (Mur_incline m, Image im)
{
    color (222,184,135);
    triangleFill (m.a.x, m.a.y, m.b.x, m.b.y, m.c.x, m.c.y);
}


struct Mur_destructible
{
    Mur m;
    double force; // Force nécessaire pour détruire le mur
    bool detruit;
};

Mur_destructible init_Mur_destructible ( Vect mini, Vect maxi, double force ) // mur_dest pour Mur Destructible
{
    Mur_destructible mur_dest;
    mur_dest.m =  init_Mur (mini, maxi);
    mur_dest.force = force;
    mur_dest.detruit = false;

    return mur_dest;
}

void draw_mur_destructible ( Mur_destructible mur_dest, Image im )
{
    if (mur_dest.detruit == false)
        draw_Mur (mur_dest.m, im);
}

struct Balle
{
    Particle balle;
    Vect pos_im;
    int rayon;
    bool touche;
    bool duree;
    float temps;
    int compteur_de_coup;
    Vect tcheck_point;
};



void init_Balle (Balle & b, Vect pos)
{
    b.balle.pos   = pos;
    b.pos_im = {b.balle.pos.x - b.rayon, b.balle.pos.y - b.rayon};
    b.balle.masse = 10;
    b.balle.force = VECTEUR_NUL;
    b.balle.vit   = VECTEUR_NUL;
    b.tcheck_point = b.balle.pos;
    b.rayon = 10;
    b.temps = 0;
    b.touche = false;
    b.duree = false;
    b.compteur_de_coup = 0;
}

void draw_Balle (Balle b, Image im)
{
    image_draw (im, b.pos_im.x, b.pos_im.y, b.rayon * 2, b.rayon * 2);
}

void add_force_balle ( Balle & b ) // Permet de faire bouger la balle en fonction du temps que l'on appuie sur la souris
{
    int mouse_x = 0;
    int mouse_y = 0;

    int coef_power = 1000; 
    // Ci dessous deux conditions permettant de savoir le temps que l'on a appuyer sur le bouton gauche de la souris et d'appliquer une force à la balle selon ce temps
    // De plus la force sera automatiquement appliquer si le temps où l'on reste appuyé sur ce bouton dépasse les 3 secondes
    if ( norme (b.balle.vit) == 0 )
    {
        if ( isMousePressed ( SDL_BUTTON_LEFT ) && b.touche == false)
        {
            b.temps = elapsedTime ();
            b.touche = true;
            b.duree = true;
            b.compteur_de_coup ++;
        }
        if ( (!isMousePressed ( SDL_BUTTON_LEFT ) && b.touche == true) || ( (elapsedTime() - b.temps) > 3 && b.duree == true) )
        {
            float power = elapsedTime () - b.temps;
            mousePos ( mouse_x, mouse_y );
            Vect force = {float (mouse_x),float (mouse_y)};
            b.balle.force = vecteur_unitaire (force - b.balle.pos) * power * coef_power;
            b.touche = false;
            b.duree = false;
        }
    }
    
}

void update_Balle ( Balle & b )
{
    add_force_balle ( b );
    update_particule ( b.balle );
    b.pos_im = {b.balle.pos.x - b.rayon, b.balle.pos.y - b.rayon};
    b.balle.vit = b.balle.vit * 0.998; // 0.998 représente le frotement avec la surface , ici "l'herbe"
    if ( norme (b.balle.vit) < 1 )
    {   
        b.balle.vit = VECTEUR_NUL;
    }   
}

struct Trou_noir
{
    Particle p;
    Vect pos_im;
    int rayon;
    int rayon_attraction;
};

Trou_noir init_Trou_noir ( Vect pos, int rayon, int rayon_attraction )
{
    Trou_noir t_n;

    t_n.p.masse = puissance_entiere ( 10, 13 ) + puissance_entiere (9, 15);
    t_n.rayon = rayon;
    t_n.p.pos = pos;
    t_n.pos_im = { pos.x - t_n.rayon, pos.y - t_n.rayon };
    t_n.rayon_attraction = rayon_attraction;

    return t_n;
}

void draw_Trou_noir ( Trou_noir t_n, Image im )
{
    image_draw ( im, t_n.pos_im.x, t_n.pos_im.y,t_n.rayon * 2, t_n.rayon * 2 );
    color ( 255, 0, 0 );
    circle ( t_n.p.pos.x, t_n.p.pos.y, t_n.rayon_attraction );
}

struct Trou
{
    Vect pos;
    int rayon;
};

Trou init_Trou (Vect pos, int rayon)
{
    Trou t;
    t.pos = pos;
    t.rayon = rayon;

    return t;
}

void draw_Trou (Trou t)
{
    color (0,0,0);
    circleFill (t.pos.x, t.pos.y, t.rayon);
}

struct Cale_balle // Permet de stoper la balle et à pour rôle de tcheckpoint, le but étant de passer par tous ces objets
{
    Vect pos;
    int rayon;
    bool use;
};

Cale_balle init_Calle_balle ( Vect pos, int rayon )
{
    Cale_balle c;
    c.pos = pos;
    c.rayon = rayon;
    c.use = false;

    return c;
}

void draw_Cale_balle (Cale_balle c)
{
    color (255, 255, 255);
    if (c.use == false)
        circleFill (c.pos.x, c.pos.y, c.rayon);
}

struct Drapeau
{
    Vect pos_barre; // La barre sera une ligne
    Vect drapeau1; // Le drapeau sera un triangle
    Vect drapeau2;
    Vect pos_trou;
    int rayon_trou;
};

Drapeau init_Drapeau (Vect pos) // Ce point sera la réference pour placer le drapeaux, tous les autres points "suivront" en fonction de ce point
{
    Drapeau d;
    d.rayon_trou = 15;
    d.pos_trou = pos;
    d.pos_barre = {pos.x, pos.y + 100};
    d.drapeau1 = {d.pos_barre.x - 50, d.pos_barre.y - 20};
    d.drapeau2 = {d.pos_barre.x, d.pos_barre.y - 40};

    return d;
}

void draw_Drapeau (Drapeau d)
{
    color (0,0,0);
    circleFill (d.pos_trou.x, d.pos_trou.y, d.rayon_trou);
    color (222,184,135);
    line (d.pos_trou.x, d.pos_trou.y, d.pos_barre.x, d.pos_barre.y);
    color (255,0,0);
    triangleFill (d.pos_barre.x, d.pos_barre.y, d.drapeau1.x, d.drapeau1.y, d.drapeau2.x, d.drapeau2.y);
}

struct Menu_jeu
{
    Vect pos_im1;
    Vect pos_im2;
    Vect pos_im3;

    Image im1;
    Image im2;
    Image im3;
};

void init_Menu (Menu_jeu & m, Vect pos_im1, Vect pos_im2, Vect pos_im3)
{
    m.pos_im1 = pos_im1;
    m.pos_im2 = pos_im2;
    m.pos_im3 = pos_im3;

}

struct World
{
    Image fond_im;
    /* -------------------------------------- */
    Balle b;
    Image balle_im;
    /* -------------------------------------- */
    Trou_noir t_n_tab [MAX_TROU_NOIR];
    Image trou_noir_im;
    int trou_noir_nb;
    /* -------------------------------------- */
    Mur mur_tab [MAX_MUR];
    Image mur_im;
    int mur_nb;
    /* -------------------------------------- */
    Mur_incline mur_incline_tab [MAX_TAB];
    Image mur_incline_im;
    int mur_incline_nb;
    /* -------------------------------------- */
    Mur_destructible mur_dest_tab [MAX_MUR];
    Image mur_dest_im;
    int mur_dest_nb;
    /* -------------------------------------- */
    Trou trou_tab [MAX_TAB];
    int trou_nb;
    /* -------------------------------------- */
    Cale_balle cale_tab [MAX_TAB];
    int cale_nb;
    /* -------------------------------------- */
    Drapeau arrivee;
    int compteur_de_coup;
    /* -------------------------------------- */
    Menu_jeu m;
    int menu;
    bool choix;
};

/* ----------------------------------------------------------------------------- Procédure -----------------------------------------------------------------------------*/
/* ---------- Permetant l'ajout d'objet composant la structure World tout en incrémentant le tableau dans lequel sont contenu ces objets ( Mur, trou noirs etc ) ---------- */


void ajoute_mur_world (World & w, Mur m)
{
    int indice = w.mur_nb;
    w.mur_tab [indice] = m;
    w.mur_nb ++;
}

void ajoute_mur_incline_world (World & w, Mur_incline m)
{
    int indice = w.mur_incline_nb;
    w.mur_incline_tab [indice] = m;
    w.mur_incline_nb ++;
}

void ajoute_mur_dest_word (World & w, Mur_destructible m_d)
{
    int indice = w.mur_dest_nb;
    w.mur_dest_tab [indice] = m_d;
    w.mur_dest_nb ++;
}

void ajoute_trou_noir_world (World & w, Trou_noir t_n)
{
    int indice = w.trou_noir_nb;
    w.t_n_tab [indice] = t_n;
    w.trou_noir_nb ++;
}

void ajoute_trou_world (World & w, Trou t)
{
    int indice = w.trou_nb;
    w.trou_tab [indice] = t;
    w.trou_nb ++;
}

void ajoute_Cale_balle (World & w, Cale_balle c)
{
    int indice = w.cale_nb;
    w.cale_tab [indice] = c;
    w.cale_nb ++;
}

/* ------------------------------------------------------------ Fonction / Procédure ------------------------------------------------------------*/
/* ---------- gérant les intéractions entre les différents objets constituant la structure World ( Rebond, Attraction etc ) ---------- */

// Renvoie true si la balle percute une image par le haut ou par le bas, false sinon
bool percussion_mur_horizontal (Vect pos_balle, Vect pos_min, Vect pos_max, int rayon)
{
    if (pos_balle.x + rayon > pos_min.x  && pos_balle.x - rayon < pos_max.x)
    {
        if (pos_balle.y + rayon + 2 >= pos_min.y && pos_balle.y - rayon - 2 <= pos_max.y) // Decalage de 1 pixel afin de differencier la percussion x et y
        {
            return true;
        }
    }

    return false;
}

// Renvoie true si la balle percute une image par la droite ou par la gauche, false sinon
bool percussion_mur_veticale (Vect pos_balle, Vect pos_min, Vect pos_max, int rayon)
{
    if (pos_balle.y + rayon > pos_min.y && pos_balle.y - rayon < pos_max.y)
    {
        if (pos_balle.x + rayon + 2 >= pos_min.x && pos_balle.x - rayon - 2 <= pos_max.x) // Decalage de 1 pixel afin de differencier la percussion x et y
        {
            return true;
        }
    }

    return false;
}

// Renvoie true si la balle percute un mur incliné, false sinon
bool percussion_mur (Vect pos_balle, Vect a, Vect b, float rayon)
{
    Fonction f = equation_droite (a, b);
    Fonction borne_min = oppoose_reciproque (f, a);
    Fonction borne_max = oppoose_reciproque (f, b);
    if (pos_balle.y + rayon < borne_min.ax * pos_balle.x + borne_min.b && pos_balle.y + rayon > borne_max.ax * pos_balle.x + borne_max.b 
        && pos_balle.y + rayon > f.ax * pos_balle.x + f.b && pos_balle.y - rayon < f.ax * pos_balle.x + f.b)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

// Attire la balle vers le centre du trou noir lorsque cette dernière est dans le rayon d'action ( rayon dans lequele le trou noir exerce une force ) du trou noir
void attraction_trou_noir ( World & w, int indice )
{ 
    Vect unitaire = vecteur_unitaire ( w.t_n_tab [indice].p.pos - w.b.balle.pos );
    float m1 = w.t_n_tab [indice].p.masse;
    float m2 = w.b.balle.masse;
    float d = distance_vect ( w.t_n_tab [indice].p.pos, w.b.balle.pos );
    float d2 = puissance_entiere ( d, 2 ); // d2 = Distance séparant la deux objet ( Bug avec vrai formule où la distance est au carré )
    if ( d >= w.t_n_tab [indice].rayon && d <= w.t_n_tab [indice].rayon_attraction )
    {
        w.b.balle.force = unitaire * ( G * ( m1 * m2 ) * ( 1 / d2 ) ); // Force de gravité
        w.b.balle.vit = w.b.balle.vit * 0.995;
    }
    else if ( d <= w.t_n_tab [indice].rayon ) // Si la balle est très proche du centre du trou noir, on ne réduit pas la distance séparant la balle et le trou noir pour éviter une division par 0
    {
        w.b.balle.force = unitaire * G * ( ( m1 * m2 ) * ( 1 / w.t_n_tab [indice].rayon * w.t_n_tab [indice].rayon ) ); // Force de gravité
        w.b.balle.vit = w.b.balle.vit * 0.995;
    }  
}

// Stop la balle si elle passe dessus et sert de tcheckpoint si l'on tombe dans un trou ou un trou noir
void stop_balle (World & w, int indice)
{
    float dist = distance_vect (w.b.balle.pos, w.cale_tab [indice].pos);
    if ( (dist - w.cale_tab [indice].rayon - w.b.rayon) < 0 && w.cale_tab [indice].use == false)
    {
        w.b.balle.vit = VECTEUR_NUL;
        w.b.balle.pos = w.cale_tab [indice].pos;
        w.cale_tab [indice].use = true;
        w.b.tcheck_point = w.cale_tab [indice].pos;
    }
}

// Renvoie true si la balle a atteint le drapeau, false sinon
bool partie_gagnee (World w)
{
    if ( (distance_vect (w.b.balle.pos, w.arrivee.pos_trou) - w.arrivee.rayon_trou - w.b.rayon) < 0)
    {
        return true;
    }
}

// Permet de faire réaparaitre la balle au dernier tcheckpoint touché
void repop_tcheck_point (World & w)
{
    w.b.balle.pos = w.b.tcheck_point;
    w.b.balle.force = VECTEUR_NUL;
    w.b.balle.vit   = VECTEUR_NUL;
    for ( int i = 0; i < w.mur_dest_nb; i++ )
    {
        w.mur_dest_tab [i].detruit = false;
    }
}

// Init le menu et charge toutes les images necessaire au jeu
void init_menu_et_image_World (World & w)
{
    w.menu = 0;
    w.choix = false;
    init_Menu (w.m, {250, 700}, {250, 500}, {250, 300});
    w.fond_im = image ("data/fond_golf.jpg");
    w.m.im1 = image ("data/im1.jpg");
    w.m.im2 = image ("data/Bouton2.png");
    w.m.im3 = image ("data/nouvellepartie.png");
    w.balle_im = image ("data/balle_golf.png");
    w.mur_dest_im = image ("data/mur_brique_fissure.jpg");
    w.trou_noir_im = image ("data/trou_noir.png");
    w.mur_im = image ("data/mur_brique.jpg");
}

// Initialise le parcour 1
void init_World_1 (World & w)
{  
    w.mur_dest_nb = 0;
    w.mur_nb = 0;
    w.mur_incline_nb = 0;
    w.trou_noir_nb = 0;
    w.trou_nb = 0;
    w.cale_nb = 0;

    init_Balle ( w.b, {DIMW - 50, 20} );

    ajoute_mur_world (w, init_Mur ( {0, 100}, {150, 150} ) );
    ajoute_mur_world (w, init_Mur ( {300, 150}, {DIMW, 200} ) );
    ajoute_mur_world (w, init_Mur ({150, 250}, {300, 300} ) );
    ajoute_mur_world (w, init_Mur ({300, 200}, {450, 750} ) );
    ajoute_mur_world (w, init_Mur ({0, 400}, {150, 450} ) );
    ajoute_mur_world (w, init_Mur ({150, 550}, {300, 600} ) );
    ajoute_mur_world (w, init_Mur ({450, 650}, {700, 750}));
    ajoute_mur_world (w, init_Mur ({600, 400}, {900, 500}));


    ajoute_mur_incline_world (w, init_Mur_incline ({750, 900}, {900, 750}, {900, 900} ) );
    ajoute_mur_incline_world (w, init_Mur_incline ({900, 600}, {750, 500}, {900, 500} ) );
    ajoute_mur_incline_world (w, init_Mur_incline ({600, 650}, {450, 550}, {450, 650} ) );
    ajoute_mur_incline_world (w, init_Mur_incline ({450, 400}, {600, 200}, {450, 200} ) );

    

    ajoute_mur_dest_word (w, init_Mur_destructible ({150, 600}, {200, 750}, 11 ) );
    ajoute_mur_dest_word (w, init_Mur_destructible ( {100, 0}, {150, 100}, 11) );

    ajoute_trou_noir_world (w, init_Trou_noir ( {375, 75}, 50, 100) );

    ajoute_trou_world (w, init_Trou ({50, 50}, 25) );
    ajoute_trou_world (w, init_Trou ({250, 650}, 25) );
    ajoute_trou_world (w, init_Trou ({250, 700}, 25) );
    
    ajoute_Cale_balle (w, init_Calle_balle ({75, 225}, 15) );
    ajoute_Cale_balle (w, init_Calle_balle ({100, 875}, 15) );

    w.arrivee = init_Drapeau ({825,250});
}

// Initialise le parcour 2
void init_World_2 (World & w)
{
    w.mur_dest_nb = 0;
    w.mur_nb = 0;
    w.mur_incline_nb = 0;
    w.trou_noir_nb = 0;
    w.trou_nb = 0;
    w.cale_nb = 0;

    init_Balle (w.b, {450, 50});
    ajoute_mur_world (w, init_Mur ({350, 0}, {400, 450} ) );
    ajoute_mur_world (w, init_Mur ({500, 0}, {550, 200} ) );
    ajoute_mur_world (w, init_Mur ({400, 400}, {700, 450} ) );
    ajoute_mur_world (w, init_Mur ({650, 150}, {700, 400} ) );
    ajoute_mur_world (w, init_Mur ({150, 400}, {350 ,400} ) );
    ajoute_mur_world (w, init_Mur ({150, 250}, {350, 300} ) );

    ajoute_mur_dest_word (w, init_Mur_destructible ({700, 400}, {900, 450}, 11));
    ajoute_mur_dest_word (w, init_Mur_destructible ({700, 700}, {900, 750}, 13));

    ajoute_mur_incline_world (w, init_Mur_incline ( {450, 400}, {400, 350}, {400, 400}) );
    ajoute_mur_incline_world (w, init_Mur_incline ( {600, 400}, {650, 350}, {650, 400}) );
    ajoute_mur_incline_world (w, init_Mur_incline ( {550, 50}, {700, 0}, {550, 0}) );
    ajoute_mur_incline_world (w, init_Mur_incline ( {150, 550}, {0, 450}, {0, 550}) );
    ajoute_mur_incline_world (w, init_Mur_incline ( {0, 150}, {100, 0}, {0, 0}) );

    ajoute_trou_world (w, init_Trou ({800, 825}, 75));
    ajoute_trou_world (w, init_Trou ({200, 350}, 50));
    ajoute_trou_world (w, init_Trou ({300, 350}, 50));

    ajoute_trou_noir_world (w, init_Trou_noir ( {500, 750}, 100, 200) );
    ajoute_trou_noir_world (w, init_Trou_noir ( {300, 750}, 100, 200) );
    ajoute_trou_noir_world (w, init_Trou_noir ( {100, 750}, 100, 200) );

    ajoute_Cale_balle (w, init_Calle_balle ({800, 150}, 15));
    ajoute_Cale_balle (w, init_Calle_balle ({650, 550}, 15));


    w.arrivee = init_Drapeau ({300,50});
}

// Permet de réinitialiser les objets détruits (Mur destructible) ou déclenchés (stop balle)
void nouvelle_partie (World & w)
{
    for ( int i = 0; i < w.mur_dest_nb; i++ )
    {
        w.mur_dest_tab [i].detruit = false;
    }   
    
    for (int i = 0; i < w.cale_nb; i++)
    {
        w.cale_tab [i].use = false;
    }
    if (w.menu == 1)
    {
        init_Balle (w.b, {DIMW - 50, 20});
    }
    if (w.menu == 2)
    {
        init_Balle (w.b, {450, 50});
    }
    
}

void draw_World ( World  w )
{
    if (w.menu == 0)
    {
        image_draw (w.fond_im, 0, 0, DIMW, DIMW);
        image_draw (w.m.im1, w.m.pos_im1.x, w.m.pos_im1.y, 400, 100);
        image_draw (w.m.im2, w.m.pos_im2.x, w.m.pos_im2.y, 400, 100);
    }
    else if (w.menu == 5)
    {
        image_draw (w.fond_im, 0, 0, DIMW, DIMW);
        image_draw (w.m.im3, w.m.pos_im3.x, w.m.pos_im3.y, 400, 100);
    }
    else
    {
        image_draw ( w.fond_im, 0, 0, DIMW, DIMW );
        for ( int i = 0; i < w.mur_nb; i++ )
            draw_Mur (w.mur_tab [i], w.mur_im);

        for ( int i = 0; i < w.mur_dest_nb; i++ )
            draw_mur_destructible (w.mur_dest_tab [i],w.mur_dest_im);

        for ( int i = 0; i < w.trou_noir_nb; i++ )
            draw_Trou_noir ( w.t_n_tab [i], w.trou_noir_im );

        for (int i = 0; i < w.trou_nb; i++)
            draw_Trou (w.trou_tab [i]);

        for (int i = 0; i < w.cale_nb; i++)
            draw_Cale_balle (w.cale_tab [i]);

        for (int i = 0; i < w.mur_incline_nb; i++)
            draw_Mur_incline (w.mur_incline_tab [i], w.mur_incline_im);
        
        draw_Balle ( w.b, w.balle_im );
        draw_Drapeau (w.arrivee);
    }
    if (partie_gagnee (w))
    {
        fontSize (80);
        color (0, 0, 0);
        print (DIMW / 2 - 400, DIMW / 2 - 40, "Vous fait le parcour en :");
        print (DIMW / 2 - 400, DIMW / 2 - 130, w.b.compteur_de_coup);
        print (DIMW / 2 - 400, DIMW / 2 - 220, "coups");
    } 
}

void update_World ( World & w )
{
    int x, y;
    float temps = 0;
    if (w.menu == 0)
    {
        
        mousePos (x, y);
        if (x > w.m.pos_im1.x && x < (w.m.pos_im1.x + largeur) && y > w.m.pos_im1.y && y < (w.m.pos_im1.y + largeur) && isMousePressed (SDL_BUTTON_LEFT))
        {   
            temps = elapsedTime ();
            w.menu = 1;
        }
        else if (x > w.m.pos_im2.x && x < (w.m.pos_im2.x + largeur) && y > w.m.pos_im2.y && y < (w.m.pos_im2.y + largeur) && isMousePressed (SDL_BUTTON_LEFT))
        {   
            temps = elapsedTime ();
            w.menu = 2;
        }

    }
    else
    {
        if (elapsedTime () - temps > 2) // Permet d'éviter à la balle de bouger lorsque l'on choisis le parcour dans le menu
            update_Balle ( w.b );
        for ( int i = 0; i < w.mur_nb; i++ )
        {
            if ( percussion_mur_veticale ( w.b.balle.pos, w.mur_tab [i].mini, w.mur_tab [i].maxi, w.b.rayon ) )
            {
                w.b.balle.vit.x = -w.b.balle.vit.x;
                update_Balle ( w.b );
            }
            if ( percussion_mur_horizontal (w.b.balle.pos, w.mur_tab [i].mini, w.mur_tab [i].maxi, w.b.rayon ) )
            {
                w.b.balle.vit.y = -w.b.balle.vit.y;
                update_Balle ( w.b );
            }
        }
        
        for ( int i = 0; i < w.mur_dest_nb; i++ )
        {
            if ( w.mur_dest_tab [i].detruit == false)
            {
                if ( percussion_mur_veticale ( w.b.balle.pos, w.mur_dest_tab [i].m.mini, w.mur_dest_tab [i].m.maxi, w.b.rayon) && norme ( w.b.balle.vit ) > w.mur_dest_tab [i].force)
                {
                    w.mur_dest_tab [i].detruit = true;
                }
                else if ( percussion_mur_veticale (w.b.balle.pos, w.mur_dest_tab [i].m.mini, w.mur_dest_tab [i].m.maxi, w.b.rayon) )
                {
                    w.b.balle.vit.x = -w.b.balle.vit.x;
                    update_Balle ( w.b );
                }
                if ( percussion_mur_horizontal ( w.b.balle.pos, w.mur_dest_tab [i].m.mini, w.mur_dest_tab [i].m.maxi, w.b.rayon) && norme ( w.b.balle.vit ) > w.mur_dest_tab [i].force )
                {
                    w.mur_dest_tab [i].detruit = true;
                }
                else if ( percussion_mur_horizontal ( w.b.balle.pos, w.mur_dest_tab [i].m.mini, w.mur_dest_tab [i].m.maxi, w.b.rayon ) )
                {
                    w.b.balle.vit.y = -w.b.balle.vit.y;
                    update_Balle ( w.b );
                }
            }
        }

        for (int i = 0; i < w.mur_incline_nb; i++)
        {
            Vect mini = w.mur_incline_tab [i].a;
            Vect maxi = w.mur_incline_tab [i].b;
            if (percussion_mur (w.b.balle.pos, mini, maxi, w.b.rayon))
            {
                /* --------------------- */
                Vect C = w.b.balle.pos;
                Vect CD = w.b.balle.vit;
                Vect CD_2nd = CD * (-1);
                Vect u = normale (maxi, mini);
                Vect n = unitaire (u);
                Vect CD_prime = 2 * n * produit_scalaire (CD_2nd, n) - CD_2nd;
                /* Ce bloc de code permet de gérer les percussion sur les murs inclinés (non alignés avec les axes), 
                tous ces vecteurs permettent donc d'appliquer cette formule qui nous permet de déterminer le vecteur suite au rebond */
                w.b.balle.vit = CD_prime;
            }
        }

        for ( int i = 0; i < w.trou_noir_nb; i++ ) // Si nous "tombons" dans un trou noirs, nous réaparaisson au dernier tcheckpoint (le départ si aucun tcheckpoint validé)
        {
            attraction_trou_noir ( w, i );
            if (norme (w.b.balle.vit) == 0 && distance_vect (w.b.balle.pos, w.t_n_tab [i].p.pos) < w.t_n_tab [i].rayon_attraction)
            {
                print (DIMW/2, DIMW/2, "Perdu, recommencez");
                repop_tcheck_point (w); 
            }
        }    

        for (int i = 0; i < w.trou_nb; i++)
        {
            float dist = distance_vect (w.trou_tab [i].pos, w.b.balle.pos);
            if ( (dist - w.b.rayon - w.trou_tab [i].rayon) < 0 )
            {
                repop_tcheck_point (w);
            }
        }
        if (partie_gagnee (w)) // Si la partie est gagné nous retournons dans le menu du jeu
        {
            w.b.balle.vit = VECTEUR_NUL;
            w.menu = 0;
            w.choix = false;
        }

        for (int i = 0; i < w.cale_nb; i++)
            stop_balle (w, i);
    }
}


int main ( int argc, char * argv [] )
{
    bool stop = false;
	winInit ("Find the way", DIMW, DIMW);

    World w;
    init_menu_et_image_World (w);
    float temps = elapsedTime ();
	while ( stop == false )
    {
        winClear ();
        draw_World (w);
        update_World (w);
        if (w.menu == 1 && w.choix == false)
        {
            init_World_1 (w);
            w.choix = true;
        }
        else if (w.menu == 2 && w.choix == false)
        {
            init_World_2 (w);
            w.choix = true;
        }
        stop = winDisplay ();
        temps = elapsedTime ();
    }

    winQuit ();
	return EXIT_SUCCESS;
}

