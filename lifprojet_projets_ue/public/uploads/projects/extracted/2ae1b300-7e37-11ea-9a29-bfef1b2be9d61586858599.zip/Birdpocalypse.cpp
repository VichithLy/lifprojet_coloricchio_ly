#include <grapic.h>
#include <math.h>
using namespace grapic;

const int DIMWX=500, DIMWY=500, MAXPART=40, NBOBS=5, TAILLEOBS=50;
const int POSITION=30, ESPACEY=200, ESPACEMINX=200, ESPACEALEAX=100;
const int RAYONOISEAU=20, RAYONBONUS=20, RAYONBALLE=15;
const int MAXTIMEBONUS=20;
const float FRICTION=1.01;

struct Complex
{
    float x,y;
};

typedef Complex Vec2;
typedef Complex Point;

Complex makeComplex(float x,float y)
{
    Complex c;
    c.x=x;
    c.y=y;
    return c;
}

Complex makeComplexExp(float r,float theta)
{
    Complex c;
    c.x=r*cos(theta);
    c.y=r*sin(theta);
    return c;
}

Complex operator+(Complex c1,Complex c2)
{
    Complex c;
    c.x=c1.x+c2.x;
    c.y=c1.y+c2.y;
    return c;
}

void operator+=(Complex&c1,Complex c2)
{
    c1=c1+c2;
}

Complex operator-(Complex c1,Complex c2)
{
    Complex c;
    c.x=c1.x-c2.x;
    c.y=c1.y-c2.y;
    return c;
}

Complex operator*(float lambda,Complex c1)
{
    Complex c;
    c.x=lambda*c1.x;
    c.y=lambda*c1.y;
    return c;
}

Complex operator*(Complex c1,float lambda)
{
    Complex c;
    c.x=lambda*c1.x;
    c.y=lambda*c1.y;
    return c;
}

void operator*=(Complex&c1,float lambda)
{
    c1=c1*lambda;
}

Complex operator/(Complex c1,float lambda)
{
    Complex c;
    c.x=c1.x/lambda;
    c.y=c1.y/lambda;
    return c;
}

struct Particle
{
    Point p; //position
    Vec2 s; //speed
    Vec2 f; //force
    float m; //mass
};

struct Obstacle
{
    Point coinsBlocHaut[2]; //représente 2 coins opposés de la partie haute de l'obstacle
    Point coinsBlocBas[2]; // représente 2 coins opposés de la partie basse de l'obstacle
};

struct World
{
    Image oiseau;
    Particle bird;
    Obstacle obs[NBOBS];
    int score;
    bool perdu;
    float bonusTime;//temps restant dans le jeu bonus. S'il vaut -1 dans le jeu principal c'est qu'on peut placer un nouveau bonus
    Point bonus;//position du bonus
    Particle parts[MAXPART];//tableau de balles pour le jeu bonus
    int nb_part;//nombre de balles
};

void partForceGrav(Particle&part)//réinitialise la force d'une particle à celle de la gravité
{
    part.f=makeComplex(0,-9.81*part.m);
}


void partDraw(Particle part)
{
    circleFill(part.p.x, part.p.y, RAYONBALLE);
}

void initWorld(World&w)
{
    w.bird.p = makeComplex(10, DIMWY/2);
    w.bird.m = 5;
    w.bird.s = makeComplex(50, 0);
    partForceGrav(w.bird);
    w.nb_part = 0;
    w.score = 0;
    w.perdu = false;
    w.bonusTime = -1; //bonusTime=-1 voudra dire que le bonus n'est pas placé
    w.bonus = makeComplex(0,0);
    w.oiseau = image("../data/bird.png");
}

void initObstacles(World&w) //crée des obstacles à des distances aléatoires et des hauteurs aléatoires selon les constantes définies
{
    int xmin, xmax, ymin, ymax; //xmin et xmax désigne les x entre lesquels est l'obstacle, ymin et ymax désigne l'espace entre l'obstacle du haut et du bas
    xmin = 1000; // le 1er obstacle est à 1000 du début
    xmax = xmin + TAILLEOBS;
    ymin = rand()%(DIMWY-ESPACEY);//la hauteur du bas de l'espace entre les obstacles
    ymax = ymin+ESPACEY;
    w.obs[0].coinsBlocHaut[0] = makeComplex(xmin, DIMWY);
    w.obs[0].coinsBlocHaut[1] = makeComplex(xmax, ymax);
    w.obs[0].coinsBlocBas[0] = makeComplex(xmin, 0);
    w.obs[0].coinsBlocBas[1] = makeComplex(xmax, ymin);
    for(int i=1; i<NBOBS; i++)
    {
        xmin = rand()%ESPACEALEAX+ESPACEMINX + w.obs[i-1].coinsBlocBas[1].x;
        xmax = xmin + TAILLEOBS;
        ymin = rand()%(2*ESPACEY) + w.obs[i-1].coinsBlocBas[1].y-ESPACEY;
        if(ymin<0)
        {
            ymin=0;
        }
        if(ymin>DIMWY-ESPACEY)
        {
            ymin=DIMWY-ESPACEY;
        }
        ymax = ymin+ESPACEY;
        w.obs[i].coinsBlocHaut[0] = makeComplex(xmin, DIMWY);
        w.obs[i].coinsBlocHaut[1] = makeComplex(xmax, ymax);
        w.obs[i].coinsBlocBas[0] = makeComplex(xmin, 0);
        w.obs[i].coinsBlocBas[1] = makeComplex(xmax, ymin);
    }
}

void nouvelObstacle(World&w)
{
    int xmin, xmax, ymin, ymax;
    xmin = rand()%ESPACEALEAX+ESPACEMINX + w.obs[NBOBS-2].coinsBlocBas[1].x;
    xmax = xmin + TAILLEOBS;
    ymin = rand()%(2*ESPACEY) + w.obs[NBOBS-2].coinsBlocBas[1].y-ESPACEY;
    if(ymin<0)
    {
        ymin=0;
    }
    if(ymin>DIMWY-ESPACEY)
    {
        ymin=DIMWY-ESPACEY;
    }
    ymax = ymin+ESPACEY;
    w.obs[NBOBS-1].coinsBlocHaut[0] = makeComplex(xmin, DIMWY);
    w.obs[NBOBS-1].coinsBlocHaut[1] = makeComplex(xmax, ymax);
    w.obs[NBOBS-1].coinsBlocBas[0] = makeComplex(xmin, 0);
    w.obs[NBOBS-1].coinsBlocBas[1] = makeComplex(xmax, ymin);
    if(w.bonusTime==-1)
    {
        if(rand()%10==0)
        {
            w.bonus = makeComplex(xmin+0.5*TAILLEOBS, ymin+0.5*ESPACEY);
            w.bonusTime = 0;
        }
    }
}

void drawFlap(World w)
{
    int x0 = w.bird.p.x-POSITION; // x0 permettra de faire un décalage, pour "scroller" le monde
    color(200,0,0);
    //circleFill(w.bird.p.x-x0, w.bird.p.y, RAYONOISEAU); //affichage de l'oiseau rond
    image_draw(w.oiseau, w.bird.p.x-x0-RAYONOISEAU, w.bird.p.y-RAYONOISEAU, 2*RAYONOISEAU,2*RAYONOISEAU); // affichage de l'oiseau image
    color(0,200,0);
    for(int i=0; i<NBOBS; i++) //affichage des obstacles
    {
        rectangleFill(w.obs[i].coinsBlocBas[0].x-x0, w.obs[i].coinsBlocBas[0].y, w.obs[i].coinsBlocBas[1].x-x0, w.obs[i].coinsBlocBas[1].y);
        rectangleFill(w.obs[i].coinsBlocHaut[0].x-x0, w.obs[i].coinsBlocHaut[0].y, w.obs[i].coinsBlocHaut[1].x-x0, w.obs[i].coinsBlocHaut[1].y);
    }
    color(0,200,200);
    circleFill(w.bonus.x-x0, w.bonus.y, 20);
    color(0,0,200);
    fontSize(30);
    print(10,DIMWY-40,"Score :");
    print(110,DIMWY-40,w.score);
}

bool collisionOiseauObstacle(World w) //vérifie si l'oiseau touche un mur
{
    if(w.bird.p.x+20>w.obs[0].coinsBlocBas[0].x && w.bird.p.x-20<w.obs[0].coinsBlocBas[1].x) //vérifie si l'oiseau est entre les x où il peut toucher l'obstacle
    {
        if(w.bird.p.y-20<w.obs[0].coinsBlocBas[1].y || w.bird.p.y+20>w.obs[0].coinsBlocHaut[1].y) //vérifie si l'oiseau est en dehors des y qui représente l'espace vide entre les obstacles
        {
            return true;
        }
    }
    return false;
}

float norm(Vec2 vec)
{
    return sqrt(vec.x*vec.x+vec.y*vec.y);
}

bool bonusPris(World w) //vérifie si l'oiseau prends un bonus
{
    int distanceBonusOiseau = norm(w.bird.p-w.bonus);
    if(distanceBonusOiseau<=RAYONOISEAU+RAYONBONUS)
    {
        return true;
    }
    return false;
}

void updateFlap(World&w, float time)
{
    w.bird.s+=w.bird.f*time;
    if(isKeyPressed(SDLK_SPACE))
    {
        w.bird.s.y = 100;
    }
    w.bird.p+=w.bird.s*time;
    if(w.bird.p.y<RAYONOISEAU)
    {
        w.bird.p.y=RAYONOISEAU;
    }
    if(w.bird.p.y>DIMWY-RAYONOISEAU)
    {
        w.bird.p.y=DIMWY-RAYONOISEAU;
    }
    if(w.obs[0].coinsBlocBas[1].x<w.bird.p.x-POSITION) //si un obstacle est dépassé de POSITION px par l'oiseau (c'est à dire qu'il sort de l'écran), il est supprimé et un nouveau est créé
    {
        if(w.bonus.x<w.obs[0].coinsBlocBas[1].x) //si le bonus est derrière cet obstacle, on dis qu'on peut placer un nouveau bonus
        {
            w.bonusTime=-1;
        }
        for(int j=1; j<NBOBS; j++)
        {
            w.obs[j-1] = w.obs[j];
        }
        nouvelObstacle(w);
        w.score++;
    }
    w.perdu=collisionOiseauObstacle(w);
    if(bonusPris(w))
    {
        w.bonusTime=MAXTIMEBONUS;
        w.bonus=makeComplex(0,0);//on réinitialise la position du bonus pour éviter des problèmes plus tard
    }
}

Particle RandPart()//crée une balle au hasard
{
    Particle part;
    part.m=frand(1,5);//masse au hasard entre 1 et 5
    part.p=makeComplex(rand()%DIMWX,rand()%DIMWY);//position aléatoire dans la fenêtre
    part.s=makeComplex(frand(10,20),frand(10,20));//vitesse x et y au hasard entre 10 et 20
    partForceGrav(part);
    return part;
}

void initBonus(World&w)
{
    int parts=rand()%(MAXPART-15)+15;//nombre de balles à créer, minimum 15, maximum MAXPART
    w.nb_part=0;
    for(int i=0;i<parts;i++)
    {
        w.parts[i]=RandPart();
        w.nb_part++;
    }

}

void drawBonus(World w, Point bird)
{
    for(int i=0;i<w.nb_part;i++)
    {
        color(200,200,0);
        partDraw(w.parts[i]);
    }
    image_draw(w.oiseau, bird.x-RAYONOISEAU, bird.y-RAYONOISEAU, RAYONOISEAU*2, RAYONOISEAU*2);
    color(0,0,200);
    fontSize(30);
    print(10,DIMWY-40,"Score :");
    print(110,DIMWY-40,w.score);
    print(DIMWX-200, DIMWY-40, "Temps :");
    print(DIMWX-90, DIMWY-40, w.bonusTime);
}

void updateBonus(World&w, Point bird, float time)
{
    for(int i=0; i<w.nb_part; i++)
    {
        w.parts[i].s+=w.parts[i].f*time;
        w.parts[i].p+=w.parts[i].s*time;
        if(w.parts[i].p.y<0)
        {
            w.parts[i].p.y=-w.parts[i].p.y;
            w.parts[i].s.y=-w.parts[i].s.y;
            w.parts[i].s*=FRICTION;
        }
        if(w.parts[i].p.y>DIMWY)
        {
            w.parts[i].p.y=-w.parts[i].p.y+2*DIMWY;
            w.parts[i].s.y=-w.parts[i].s.y;
            w.parts[i].s*=FRICTION;
        }
        if(w.parts[i].p.x<0)
        {
            w.parts[i].p.x=-w.parts[i].p.x;
            w.parts[i].s.x=-w.parts[i].s.x;
            w.parts[i].s*=FRICTION;
        }
        if(w.parts[i].p.x>DIMWX)
        {
            w.parts[i].p.x=-w.parts[i].p.x+2*DIMWX;
            w.parts[i].s.x=-w.parts[i].s.x;
            w.parts[i].s*=FRICTION;
        }
        for(int j=i+1; j<w.nb_part; j++)//test des collisions avec toutes les autres particules, à partir de i+1 pour éviter de tester 2 fois les mêmes duos de particules
        {
            if(norm(w.parts[i].p-w.parts[j].p)<=2*RAYONBALLE)
            {
                float vitesse;
                Complex direction;
                vitesse = (norm(w.parts[i].s) + norm(w.parts[j].s))*FRICTION/2;
                direction = (w.parts[i].p - w.parts[j].p)/norm(w.parts[i].p - w.parts[j].p);
                w.parts[i].s = vitesse * direction;
                w.parts[j].s = -vitesse * direction;
            }
        }
        if(norm(bird-w.parts[i].p)<RAYONOISEAU+RAYONBALLE)
        {
            w.perdu=true;
        }
    }
}

int main(int,char**)
{
    srand(time(NULL));
    winInit("Birdpocalypse",DIMWX,DIMWY);
    //setKeyRepeatMode(true);
    backgroundColor(200,200,200);
    bool stop=false,restart=false;
    float previousTime, now;
    World w;
    int x0=0;
    Point mouse;int mouseX,mouseY; //permettra de savoir où se truve la souris pour le bonus
    int vitesseJeu=3; //la vitesse du jeu dépend du temps qui passe mais comme c'est un peu lent j'utilise ça pour l'accélérer
    while(!stop)
    {
        initWorld(w);
        initObstacles(w);
        previousTime = elapsedTime();
        restart=false;
        //w.bonusTime=MAXTIMEBONUS; //permet de tester le mini-jeu bonus directement
        while(!restart&&!stop)
        {
            winClear();
            if(w.bonusTime<=0)
            {
                now = elapsedTime();
                if(!w.perdu)
                {
                    updateFlap(w, (now-previousTime)*vitesseJeu);
                }
                drawFlap(w);
            }
            else
            {
                if(w.bonusTime==MAXTIMEBONUS)//si le bonus vient de commencer, on l'initialise
                {
                    initBonus(w);
                    mousePos(mouseX,mouseY);
                    mouse=makeComplex(mouseX,mouseY);
                    drawBonus(w, mouse);
                    print(20,DIMWY-200, "Le mini jeu bonus va commencer.");
                    print(20,DIMWY-250, "Préparer votre souris");
                    print(20,DIMWY-300, "Appuyer sur espace pour continuer.");
                    winDisplay();
                    delay(500);
                    pressSpace();
                    previousTime=elapsedTime()-0.001;//pour éviter un problème de bond temporel, on réactualise previousTime après la pause, et on le réduit légèrement pour être sur que le temps bonus soit bien réduit (sinon le bonus s'initie en boucle)
                }
                now = elapsedTime();
                if(!w.perdu)
                {
                    mousePos(mouseX,mouseY);
                    mouse=makeComplex(mouseX,mouseY);
                    updateBonus(w, mouse, (now-previousTime)*vitesseJeu);
                    w.bonusTime-=now-previousTime;
                }
                drawBonus(w, mouse);
                if(w.bonusTime<=0)//si le bonus vient de se terminer, on ajoute des points au score
                {
                    w.score+=20;
                    winClear();
                    drawFlap(w);
                    print(20,DIMWY-200, "Le jeu principal reprend.");
                    print(20,DIMWY-300, "Appuyer sur espace pour continuer.");
                    winDisplay();
                    //delay(500);
                    pressSpace();
                    now=elapsedTime();//pour éviter un bond temporel une fois que le jeu reprends
                }
            }
            if(w.perdu)
            {
                color(255,0,0);
                fontSize(80);
                print(DIMWX/2-100,DIMWY/2-50,"Perdu");
                fontSize(25);
                print(10,50, "Appuyer sur espace pour recommencer");
                winDisplay();
                delay(500);
                pressSpace();
                restart=true;
            }
            previousTime = now;
            stop=winDisplay();
        }
    }
    return 0;
}
