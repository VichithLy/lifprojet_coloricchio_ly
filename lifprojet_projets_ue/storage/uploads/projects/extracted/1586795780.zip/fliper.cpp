/*jonathan BRESSAT - p1802864*/
#include <Grapic.h>
#include <time.h>
using namespace grapic;


/**constante :*/
const int DIMWX = 500;
const int DIMWY = 750;
const int MAXT = 10;
const float PENTE = 0.4;

/**structure :*/
struct couleur{
    unsigned char r,g,b;
};

struct comp{
    float x;
    float y;
};

struct particle{
    comp p;
    comp v;
    comp f;
    float r;
    float m;
    bool morte;
    bool lancer;
};

struct bumper{
    comp p;
    float f;
    couleur c;
    float r;
};

struct activator{
    comp p;
    couleur c;
    float r;
    int type;
};

struct flip{
    float angle;
    float v;
    comp p;
    float l;
};

struct launcher{
    float f;
    float Max;
};

struct world{
    int score;
    int multiplicateur;
    bool defaite;
    int vie;
    particle boule[MAXT];
    int np;
    bumper bump[MAXT];
    int nb;
    activator a[MAXT];//les activateurs ne sont pas encore utilisé ils pourront servire a faire des circuits ou a donner des bonus/malus au joueur
    int na;
    flip fd,fg;
    launcher l;
    float dt;
};

/**operateur et fonction de base sur les complexe*/
comp operator+(comp a, comp b)
{
    comp c;
    c.x=a.x+b.x;
    c.y=a.y+b.y;
    return c;
}

comp operator-(comp a, comp b)
{
    comp c;
    c.x=a.x-b.x;
    c.y=a.y-b.y;
    return c;
}

comp operator*(float y, comp a)
{
    comp c;
    c.x=a.x*y;
    c.y=a.y*y;
    return c;
}

comp operator*(comp a,comp b)
{
    comp c;
    c.x=a.x*b.x-a.y*b.y;
    c.y=a.x*b.y+b.x*a.y;
    return c;
}

comp MkComp(float x,float y)
{
    comp a;
    a.x=x;
    a.y=y;
    return a;
}

couleur MkCouleur(int r,int g,int b)
{
    couleur c;
    c.r=r;
    c.g=g;
    c.b=b;
    return c;
}

float distance(comp a,comp b){
    return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}

comp direction(comp a,comp b){
    return a-b;
}

float norme(comp a){
    return sqrt(a.x*a.x+a.y*a.y);
}

float DegToRad(float angle){
    return 0.0175*angle;
}


/** 1 initialisation*/
void PartInit(particle &part,comp vitesse,comp position,float masse, float rayon)
{
    part.p=position;
    part.m=masse;
    part.v=vitesse;
    part.r=rayon;
    part.morte=false;
    part.lancer=true;
}

void BumpInit(bumper &b)
{
    b.c.r=255;
    b.c.g=0;
    b.c.b=200;
    b.r=45.0;
    b.p=MkComp(irand(b.r,DIMWX-b.r-50),irand(b.r+225,DIMWY-b.r-30));
    b.f=0.008;
}

void BumpGauche(bumper &b)
{
    b.c.b=255;
    b.c.g=b.c.r=0;
    b.r=65.0;
    b.f=0.007;
    b.p=MkComp(-30,70+b.r);
}

void BumpDroite(bumper &b)
{
    b.c.b=255;
    b.c.g=b.c.r=0;
    b.r=65.0;
    b.f=0.007;
    b.p=MkComp(DIMWX-(85+b.r),70+b.r);
}

void PartAddForce(particle &p,float dt)
{
    float g=9.81*PENTE;
    p.f=MkComp(0,-(g*p.m*dt));
}

void FlipInit(flip &f , bool sens)//true pour droite et false pour gauche
 {
     f.l=115;
     f.angle=-20;
     f.v=0;
     if(sens){ f.p=MkComp(DIMWX-205,100);}
     else{ f.p=MkComp(25,100);}
 }

void init(world &w)
{
    int i;
    w.score = 0;
    w.vie = 3;
    w.np=1;
    w.nb=5;
    w.defaite=false;
    w.dt=0.0005;
    w.l.f=0.00;
    w.l.Max=2;
    for(i=0;i<w.np;i++){
        PartInit(w.boule[i], MkComp(0,0), MkComp(DIMWX,75), 1.0, 15);
        PartAddForce(w.boule[i],w.dt);
    }
    BumpGauche(w.bump[0]);
    BumpDroite(w.bump[1]);
    w.bump[2].c=MkCouleur(255,0,0);
    w.bump[2].f=0.01;
    w.bump[2].r=45.0;
    w.bump[2].p=MkComp(DIMWX-76,275);
    for(i=3;i<w.nb;i++){
        BumpInit(w.bump[i]);
    }
    FlipInit(w.fd,true);
    FlipInit(w.fg,false);

}


/** 2 update / mise a jour*/
void colliBump(world &w)//détecte les collisions avec les flip (petite barre
{
    comp d;
    for(int i=0;i<w.np;i++){
        for(int j=0; j<w.nb;j++){
            if(distance(w.boule[i].p,w.bump[j].p)-w.boule[i].r<=w.bump[j].r){
                d=direction(w.boule[i].p,w.bump[j].p);
                w.boule[i].v=frand(w.bump[j].f-0.002,w.bump[j].f+0.002)*d;
                w.score+=200;
            }
        }
    }
}

bool dessousSegment(comp a,comp b, particle &c)//a= extrémité gauche du segment / b= extrémité droite du segment  / c= boule a vérifier
{
        if((c.p.x+c.r>a.x&&c.p.x-c.r<b.x)   &&   (c.p.y+c.r>((b.y-a.y)/(b.x-a.x))*(c.p.x-a.x)+a.y)   &&   (c.p.y-c.r<=((b.y-a.y)/(b.x-a.x))*(c.p.x-a.x)+a.y)){
     /* si   la boule est entre a et b      et    la boule n'a pas déjà dépasser le segment          et    la boule passe au dessous du segment (équation de droite)*/
            c.p.y=(((b.y-a.y)/(b.x-a.x))*(c.p.x-a.x)+a.y)+c.r;
            return true;
        }
        else{
            return false;
        }
}

void collision(particle &boule, float angleDuMur,float vitesseDuMur)
{
    float V=sqrt(boule.v.x*boule.v.x+boule.v.y*boule.v.y);
    float angleFinal = angleDuMur+90 + atan(boule.v.y/boule.v.x);
    if(V<0.35){
        boule.v = (1+vitesseDuMur-vitesseDuMur*0.7)*MkComp( V*cos(DegToRad(angleFinal)) , V*sin(DegToRad(angleFinal)) );
    }
    else{
        boule.v = (0.3+vitesseDuMur)*MkComp( V*cos(DegToRad(angleFinal)) , V*sin(DegToRad(angleFinal)) );
    }
}

void colliFlip(world &w)
{
    comp exd,exg;
    comp forceF;
    exd=MkComp(w.fd.p.x-w.fd.l*cos(DegToRad(-w.fd.angle)),w.fd.p.y-w.fd.l*sin(DegToRad(-w.fd.angle)));//les coordonées de l'extrémité du flip de droite
    exg=MkComp(w.fg.p.x+w.fg.l*cos(DegToRad(w.fg.angle)),w.fg.p.y+w.fg.l*sin(DegToRad(w.fg.angle)));//les coordonées de l'extrémité du flip de gauche
    for(int i=0; i<w.np;i++){
        if(dessousSegment(w.fg.p,exg,w.boule[i])){
            collision(w.boule[i],w.fg.angle,w.fg.v);
        }
        else if(dessousSegment(exd,w.fd.p,w.boule[i])){
            collision(w.boule[i],-w.fd.angle,w.fd.v);
        }
    }
}

void PartUpdate(particle &p)
{
    if(!p.morte){
        if((p.p.x)>(DIMWX-p.r)||(p.p.x)<(p.r)){
            p.v.x=-p.v.x;
            p.v=0.5*p.v;
            if(p.p.x > DIMWX-p.r){
                p.p.x=DIMWX-p.r;
            }
            if(p.p.x<p.r){
                p.p.x=p.r;
            }
        }if((p.p.y)>(DIMWY-p.r-30)||(p.p.y)<(p.r)){
            p.v.y=-p.v.y;
            p.v=0.5*p.v;
            if(p.p.y > DIMWY-p.r-30){
                p.p.y=DIMWY-p.r-30;
            }
            if(p.p.y<p.r){
                p.p.y=p.r;
            }
        }
        if((p.v.x>0)&&(p.p.x<DIMWX-30)){
            if(p.p.x>DIMWX-p.r-30){
                p.v.x=-p.v.x;
                p.v=0.5*p.v;
                p.p.x=DIMWX-p.r-30;
            }
        }
       if((p.v.y>=0||p.v.x>=0)&&(distance(MkComp(DIMWX-100,DIMWY-130),p.p)+p.r>100)&&(p.p.x>DIMWX-100 && p.p.y>DIMWY-130)){
            float V=norme(p.v);
            float a=DegToRad(22.5);
            float ainit=DegToRad(90);
            if(p.p.y<=DIMWY-30-(100*(sqrt(2)/2))){
                p.v=MkComp(V*cos(ainit+a),V*sin(ainit+a));
            }
            if(p.p.y>DIMWY-30-(100*(sqrt(2)/2))){
                p.v=MkComp(V*cos(ainit+3.4*a),V*sin(ainit+3.4*a));
            }
        }
        p.p=p.p+p.v;
        p.v=(p.v+p.f);
    }
}

void tireboule(world &w,int n)
{
    if(isKeyPressed(SDLK_DOWN)){
        if(w.l.f<w.l.Max){
            w.l.f+=0.002;
        }
    }
    else{
        w.boule[n].v.y=w.l.f;
        if(w.l.f!=0.0){
            w.boule[n].lancer=true;
        }
        w.l.f=0.0;
    }
}

void monte(flip &f){
    if(f.angle<60){
        f.angle+=1;
        f.v=1;
    }
    else{
        f.v=0;
    }
}

void descend(flip &f){
    if(f.angle>-20){
        f.angle-=1;
        f.v=-1;
    }
    else{
        f.v=0;
    }
}

void update(world &w)
{
    int n=0;
    //if(w.defaite){
        if(isKeyPressed('r')){
            init(w);
        }
   // }
    else{
        for(int i=0; i<w.np;i++){
            if(w.boule[i].morte){
                n++;
            }
            else{
                if(w.boule[i].p.y<=w.boule[i].r){
                    if(w.boule[i].p.x+w.boule[i].r<=DIMWX-30){
                        w.boule[i].morte=true;
                    }
                    else{
                        w.boule[i].v.x=0;
                        w.boule[i].lancer=false;
                    }
                }
                if(w.boule[i].lancer==false){
                    tireboule(w,i);
                }
                PartUpdate(w.boule[i]);
            }

            if(n==w.np){
                w.vie--;
                w.np=1;
                PartInit(w.boule[0], MkComp(0,0), MkComp(DIMWX,75), 1.0, 15);
                PartAddForce(w.boule[0],w.dt);
            }
            if(w.vie==0){
                w.defaite=true;
            }
        }
        colliBump(w);
        colliFlip(w);
    }
    if(isKeyPressed(SDLK_LEFT)){
        monte(w.fg);
    }
    else{
        descend(w.fg);
    }
    if(isKeyPressed(SDLK_RIGHT)){
        monte(w.fd);
    }
    else{
        descend(w.fd);
    }
}
/** 3 Draw / affichage*/
void PartDraw(particle p)
{
    if(!p.morte){
        color(255,25,75);
        circleFill(p.p.x,p.p.y,p.r);
    }
}

void BumpDraw(bumper b)
{
    color(b.c.r,b.c.g,b.c.b);
    circleFill(b.p.x,b.p.y,b.r);
    color((b.c.r+255)/2,(b.c.g+255)/2,(b.c.b+255)/2);
    float x=b.r/sqrt(2);
    rectangleFill(b.p.x-x,b.p.y-x,b.p.x+x,b.p.y+x);
}

void FlipDraw(flip f,bool sens)
{
    color(255,0,0);
    comp ex;
    if(sens){
        ex=MkComp(f.p.x-f.l*cos(DegToRad(-f.angle)),f.p.y-f.l*sin(DegToRad(-f.angle)));
    }
    else{
        ex=MkComp(f.p.x+f.l*cos(DegToRad(f.angle)),f.p.y+f.l*sin(DegToRad(f.angle)));
    }
    line(f.p.x,f.p.y,ex.x,ex.y);
}

void AffBandeau(world w)
{
    color(255,0,0);
    print(DIMWX/2-25,DIMWY-30,w.score);
    print(30,DIMWY-30,w.vie);
}


void AffJauge(world w){
    for(int i=0;i<=(w.l.f*2);i++){
        if(i>0){
            color(255,0,0);
            rectangleFill(DIMWX-35,5*i,DIMWX-30,5*(i-1));
        }
    }
}
void draw(world w)
{
    if(!w.defaite){
        color(0,0,0);
        circleFill(DIMWX-100,DIMWY-130,100);
        rectangleFill(0,DIMWY-30,DIMWX-100,DIMWY-130);
        rectangleFill(0,0,DIMWX,DIMWY-130);
        color(255,255,255);
        line(DIMWX-2*w.boule[0].r-2,0,DIMWX-2*w.boule[0].r-2,DIMWY-125);
        int i;
        for(i=0;i<w.np;i++){
            PartDraw(w.boule[i]);
        }
        for(i=0;i<w.nb;i++){
            BumpDraw(w.bump[i]);
        }
        FlipDraw(w.fd,true);
        FlipDraw(w.fg,false);
        AffBandeau(w);
        AffJauge(w);
    }
    else{
        color(0,0,0);
        rectangleFill(0,0,DIMWX,DIMWY);
        color(255,255,255);
        print(DIMWX/2-130,DIMWY/2+25,"vous avez perdue rip en paix");
        print(DIMWX/2-55,DIMWY/2, "votre score :");
        print(DIMWX/2-30,DIMWY/2-25, w.score);
        print(DIMWX/2-70,DIMWY/2-50,"press 'r' to retry");
    }
}


/**main*/
int main(int , char** )
{
    srand(time(NULL));
    world dat;
    bool stop=false;
    winInit("Particles", DIMWX, DIMWY);
    setKeyRepeatMode(true);
    backgroundColor( 255,255,255 );
    init(dat);
    while( !stop ){
        winClear();
        draw(dat);
        update(dat);
        stop = winDisplay();
    }
    winQuit();
    return 0;
}

