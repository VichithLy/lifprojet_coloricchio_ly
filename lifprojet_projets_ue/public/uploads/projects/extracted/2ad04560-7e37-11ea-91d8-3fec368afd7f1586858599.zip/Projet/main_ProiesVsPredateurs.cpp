/*                                                                   Règles

- Les proies mangent l'herbe dans leur voisinage ou sous elles.
- Une seule proie peut se nourrir par case d'herbe. Une fois mangée, l'herbe a un temps de repousse.
- Les prédateurs mangent les proies dans leur voisinage.
- Un seul prédateur peut se nourrir par proie. Une fois mangée, la proie est considérée comme déjà prise.
- Un prédateur ou une proie ne peut se nourrir qu'une fois par jour.
- Si deux proies ou deux prédateurs de sexe opposé sont adjacents et qu'il y a une case libre dans le voisinage de la femelle, un petit naît.
- Une femelle ne peut faire qu'un enfant par jour.
- Après une mise à bat, une femelle doit attendre 1 tour avant de pouvoir s'accoupler de nouveau.
- Deux animaux ne peuvent s'accoupler que s'ils sont adultes.
- Les animaux de la première génération naissent à la limite de l'âge adulte.
- La limite de l'âge adulte correspond à 1/5 de leur durée de vie.
- Une proie ou un prédateur peut mourir par :
                - manque de nourriture durant trop longtemps;
                - manque d'eau pendant trop longtemps;
                - vieillesse;
                - maladie.
- Le sexe est déterminé aléatoirement de façon équitable à la naissance.
- Il y a une certaine probabilité de naître malade, en fonction de la taille de la grille.
- Avoir au moins un parent malade augmente grandement la probabilité que l'enfant soit malade.
- Chaque animal malade dans l'entourage augmente les chances d'être contaminé si l'animal est malade depuis au moins 1 jour.
- Un prédateur qui mange une proie malade risque la contamination.
- Un animal contaminé risque de mourir après un jour.
- Un animal contaminé a une chance de guérir.
- Plus l'animal est contaminé depuis longtemps, moins il a chance de guérir et plus il risque la mort.
- Les proies se déplacent de façon à s'éloigner de tous les prédateurs et éviter le contact direct.
- Les proies se déplacent de façon à éviter le contact direct avec leurs congénères malades.
- Les prédateurs se déplacent de façon à se rapprocher de la proie la plus proche.
- La rivière est générée aléatoirement avec un nombre de gués dépendant de sa taille.
- Les animaux peuvent traverser la rivière aux gués.
- Les animaux peuvent boire s'ils ont dans leur voisinage une case d'eau ou un gué.
- Les animaux ne peuvent pas naître sur un gué.
- Il fait beau à l'initialisation.
- Chaque jour le temps est choisi aléatoirement.
- Chaque jour de pluie descend la soif des animaux.
*/

#include <Grapic.h>
#include <ctime>
using namespace grapic;
using namespace std;

const int DIMW = 500;
const int DELAY=1000;           // en ms

struct Individu
{
    int type_individu;  // 0 herbe   #  1 proie   #  2 predateur   #  3 eau   #  4 gué   #  5 proie/gué   #  6 prédateur/gué
    int duree_vie;  // nombre de jours avant de mourir de vieillesse
    int duree_jeune;  // nombre de jours sans manger avant de mourir
    bool femelle;
    bool pleine;   // false si peut s'accoupler
    bool a_bouge; // true s'il s'est déjà déplacé
    bool herbe_mangee;  // true si l'herbe a été mangée
    int duree_pousse;   // nombre de jours avant que l'herbe ne repousse
    bool vivant;
    int duree_soif;  // nombre de jours sans boire avant de mourir
    int duree_maladie;  // -1 si non malade, 0 si il vient d'être contaminé
};

struct Ecosysteme
{
    Individu grille[50][50];        // 50 : taille maximale autorisée
    int nbproies;
    int nbpredateurs;
    int dx;   // largeur de la grille
    int dy;   // hauteur de la grille
    Image Herbe;
    Image Terre;
    Image LapinMale;
    Image LapinFemelle;
    Image LoupMale;
    Image LoupFemelle;
    Image Eau;
    Image Gue;
    Image Malade;
    Image Pluie;
    Image Pluie2;
    Image Pluie3;
    Image Moins;
    Image Plus;
    int nbeau;
    int nbgue;
    int jour;
    int heure;
    int temps;  // -1 pluie 0 soleil
    bool jeu_en_cours;
    int DUREE_VIE_PROIE;
    int DUREE_VIE_PREDATEUR;
    int MAX_JEUNE_PROIE;
    int MAX_JEUNE_PREDATEUR;
    int DUREE_POUSSE_HERBE;
    int MAX_SOIF;
    int CHANCE_MALADIE;    // Entre 1 et 5 pour éviter des problèmes arithmétiques !  Augmente l'apparition de maladies et leur dangerosité.
    int CHANCE_PLUIE;   // en pourcentages
    int EAU_PLUIE;    // Descend la soif
};

void init_images(Ecosysteme &e)   // On initie toutes les images au début du programme, une seule fois !
{
    e.Herbe=image("/data/ProiesVsPredateurs/Herbe.jpg");
    e.Terre=image("/data/ProiesVsPredateurs/Terre.jpg");
    e.LoupMale=image("/data/ProiesVsPredateurs/LoupMale.png");
    e.LoupFemelle=image("/data/ProiesVsPredateurs/LoupFemelle.png");
    e.LapinMale=image("/data/ProiesVsPredateurs/LapinMale.png");
    e.LapinFemelle=image("/data/ProiesVsPredateurs/LapinFemelle.png");
    e.Eau=image("/data/ProiesVsPredateurs/Eau.jpg");
    e.Gue=image("/data/ProiesVsPredateurs/Gue.png");
    e.Malade=image("/data/ProiesVsPredateurs/Malade.png");
    e.Pluie=image("/data/ProiesVsPredateurs/Pluie.png");
    e.Pluie2=image("/data/ProiesVsPredateurs/Pluie2.png");
    e.Pluie3=image("/data/ProiesVsPredateurs/Pluie3.png");
    e.Moins=image("/data/ProiesVsPredateurs/Moins.png");
    e.Plus=image("/data/ProiesVsPredateurs/Plus.png");
}

void init(Ecosysteme &e)   // Fonction initialisant le jeu à 0, peut être appelée plusieurs fois
{
    int i, j;
    e.nbeau=0;
    e.nbgue=0;
    e.jour=0;
    e.heure=0;
    e.temps=0;
    for (i=0;i<e.dy;i++)
    {
        for (j=0;j<e.dx;j++)
        {
            e.grille[i][j].type_individu=0;
            e.grille[i][j].duree_pousse=0;
            e.grille[i][j].herbe_mangee=false;
        }
    }
}

void riviere(Ecosysteme &e)  // Fonction créant de façon aléatoire une rivière
{
    int i,j,i2,j2,k,l,direction=0,repetitionVerticale=0,repetitionHorizontale=0;
    // On choisit aléatoirement un point de départ :
    i=rand()%(e.dy-2)+1;
    j=rand()%((e.dx-2)/2)+1;
    if (i<e.dy/2)
        direction=1; // Selon le point de départ, la rivière ira vers le haut ou le bas (de façon à avoir une rivière suffisamment grande)
    e.grille[i][j].type_individu=3;   // Cette case est déclarée comme étant une case de rivière
    e.nbeau++;
    do
    {
        if (direction==0)       // vers le haut
        {
            if (repetitionHorizontale==2)    // S'il y a déjà eu 2 décalages vers la droite, on décale vers le haut de façon à avancer en diagonale
                i2=i-1;
            else if (repetitionVerticale==2)   // Au contraire s'il y a déjà eu 2 décalages vers le haut, on décale à droite
                i2=i;
            else
                i2=i-rand()%2;  // Sinon on tire aléatoirement la position : soit i-1, soit i
            if (i2==i)  // Si on tire i : on va à droite
            {
                j2=j+1;
                repetitionHorizontale++;
                repetitionVerticale=0;
            }
            else  // Sinon on monte
            {
                j2=j;
                repetitionVerticale++;
                repetitionHorizontale=0;
            }
        }
        else                // vers le bas
        {
            if (repetitionHorizontale==2)
                i2=i+1;
            else if (repetitionVerticale==2)
                i2=i;
            else
                i2=i+rand()%2;
            if (i2==i)
            {
                j2=j+1;
                repetitionHorizontale++;
                repetitionVerticale=0;
            }
            else
            {
                j2=j;
                repetitionVerticale++;
                repetitionHorizontale=0;
            }
        }
        e.grille[i2][j2].type_individu=3;
        e.nbeau++;
        i=i2;
        j=j2;
    } while (i!=0 && i!=e.dy-1 && j!=e.dx-1);  // On continue tant qu'on n'a pas dépassé une extrémité
    e.nbeau--;  // On supprime une case d'eau, correspondant à celle ajoutée hors-grille
    e.nbgue=e.nbeau/4;  // On fera au moins un gué pour 4 cases de rivière
    for (i=0;i<e.nbgue;i++)  // Tant qu'on n'a pas dépassé le nombre minimal de gué
    {
        do  // on tire une case aléatoire parmi celles de rivières
        {
            i2=rand()%(e.dy-2)+1;
            j2=rand()%(e.dx-2)+1;
        } while (e.grille[i2][j2].type_individu!=3);
        // On vérifie si cette case est collée à un gué ou traversable directement (qu'il ne s'agit pas d'un coude de rivière ne parmettant pas d'atteindre l'autre rive)
        if (e.grille[i2-1][j2].type_individu==4 || e.grille[i2+1][j2].type_individu==4 || e.grille[i2][j2-1].type_individu==4 || e.grille[i2][j2+1].type_individu==4
            || (e.grille[i2-1][j2].type_individu==0 && e.grille[i2+1][j2].type_individu==0) || (e.grille[i2][j2-1].type_individu==0 && e.grille[i2][j2+1].type_individu==0))
            e.grille[i2][j2].type_individu=4;  // Si c'est le cas, on en fait un gué
        else  // Sinon, on en fait un gué et on cherche une deuxième case autour pour en faire un gué permettant ainsi de traverser la rivière
        {
            e.grille[i2][j2].type_individu=4;
            do
            {
                k=i2-rand()%3+1;
                l=j2-rand()%3+1;
            } while (e.grille[k][l].type_individu!=3 || (abs(k-i2)+abs(l-j2))!=1);
            e.grille[k][l].type_individu=4;
            i++; // On a une incrémentation supplémentaire : on peut donc avoir plus de gués que nbgue, le nombre minimal.
        }
    }
}

void etat_initial(Ecosysteme &e)  // Initialise les proies et les prédateurs sur la grille
{
    int i,l,c,m;
    for (i=0;i<e.nbproies;i++)
    {
        do
        {
            l=rand()%(e.dy-2)+1;
            c=rand()%(e.dx-2)+1;
        } while (e.grille[l][c].type_individu!=0);
        e.grille[l][c].type_individu=1;
        e.grille[l][c].femelle=rand()%2;
        e.grille[l][c].pleine=false;
        e.grille[l][c].duree_jeune=0;
        e.grille[l][c].duree_vie=e.DUREE_VIE_PROIE/5;   // On les rend "adultes", soit âgés d'1/5 de leur durée de vie, pour permettre leur reproduction
        e.grille[l][c].a_bouge=false;
        e.grille[l][c].vivant=true;
        e.grille[l][c].duree_soif=0;
        m=rand()%(e.dx*e.dy/e.CHANCE_MALADIE);  // Ils sont un pourcentage de chance d'apparaître malade, ce pourcentage étant faible et dépendant de la taille de la grille et de CHANCE_MALADIE
        if (m==0)
            e.grille[l][c].duree_maladie=0;
        else
            e.grille[l][c].duree_maladie=-1;
    }
    for (i=0;i<e.nbpredateurs;i++)
    {
        do
        {
            l=rand()%(e.dy-2)+1;
            c=rand()%(e.dx-2)+1;
        } while (e.grille[l][c].type_individu!=0);
        e.grille[l][c].type_individu=2;
        e.grille[l][c].femelle=rand()%2;
        e.grille[l][c].pleine=false;
        e.grille[l][c].duree_jeune=0;
        e.grille[l][c].duree_vie=e.DUREE_VIE_PREDATEUR/5;
        e.grille[l][c].a_bouge=false;
        e.grille[l][c].vivant=true;
        e.grille[l][c].duree_soif=0;
        if (m==0)
            e.grille[l][c].duree_maladie=0;
        else
            e.grille[l][c].duree_maladie=-1;
    }
}

void draw(Ecosysteme &e, int &animation, Menu Plus, Menu Moins, Menu Jour)
{
    int i, j;
    int TailleCase=DIMW/std::max(e.dx,e.dy);  // On adapte la taille des cases à leur nombre
    int TailleMenu=DIMW/10;
    for (i=0;i<e.dy;i++)
    {
        for (j=0;j<e.dx;j++)
        {
            if (e.grille[i][j].herbe_mangee==false)
                image_draw(e.Herbe,j*TailleCase,(e.dy-1-i)*TailleCase,TailleCase,TailleCase);
            else
                image_draw(e.Terre,j*TailleCase,(e.dy-1-i)*TailleCase,TailleCase,TailleCase);
            if (e.grille[i][j].type_individu==3)
                image_draw(e.Eau,j*TailleCase,(e.dy-1-i)*TailleCase,TailleCase,TailleCase);
            if (e.grille[i][j].type_individu==4 || e.grille[i][j].type_individu==5 || e.grille[i][j].type_individu==6)
                image_draw(e.Gue,j*TailleCase,(e.dy-1-i)*TailleCase,TailleCase,TailleCase);
            if (e.grille[i][j].type_individu==1 || e.grille[i][j].type_individu==5)
            {
                if (e.grille[i][j].femelle==true)
                    image_draw(e.LapinFemelle,j*TailleCase,(e.dy-1-i)*TailleCase,TailleCase,TailleCase);
                else
                    image_draw(e.LapinMale,j*TailleCase,(e.dy-1-i)*TailleCase,TailleCase,TailleCase);
                if (e.grille[i][j].duree_maladie!=-1)
                    image_draw(e.Malade,j*TailleCase,(e.dy-1-i)*TailleCase,TailleCase,TailleCase);
            }
            else if (e.grille[i][j].type_individu==2 || e.grille[i][j].type_individu==6)
            {
                if (e.grille[i][j].femelle==true)
                    image_draw(e.LoupFemelle,j*TailleCase,(e.dy-1-i)*TailleCase,TailleCase,TailleCase);
                else
                    image_draw(e.LoupMale,j*TailleCase,(e.dy-1-i)*TailleCase,TailleCase,TailleCase);
                if (e.grille[i][j].duree_maladie!=-1)
                    image_draw(e.Malade,j*TailleCase,(e.dy-1-i)*TailleCase,TailleCase,TailleCase);
            }
            color (0,0,0);
            rectangle(j*TailleCase,(e.dy-1-i)*TailleCase,(j+1)*TailleCase,(e.dy-i)*TailleCase);
            if (i==0 || i==e.dy-1 || j==0 || j==e.dx-1)
            {
                color (0,0,0);
                rectangleFill(j*TailleCase,(e.dy-1-i)*TailleCase,(j+1)*TailleCase,(e.dy-i)*TailleCase);
            }
        }
    }
    // On dessine ensuite les différents menus
    for (i=0;i<9;i++)
        rectangle(DIMW+75,1+i*TailleMenu,DIMW+225,(i+1)*TailleMenu+1);
    rectangle(DIMW+25,9.2*TailleMenu,DIMW+275,9.8*DIMW/10);
    fontSize(16);
    print(DIMW+60,9.25*TailleMenu,"JOUR");
    print(DIMW+110,9.25*TailleMenu,e.jour);
    print(DIMW+150,9.25*TailleMenu,e.heure);
    print(DIMW+170,9.25*TailleMenu,": 00");
    fontSize(13);
    print(DIMW+115,8.5*TailleMenu,"DUREE VIE");
    print(DIMW+120,8.05*TailleMenu,"PROIE :");
    print(DIMW+170,8.05*TailleMenu,e.DUREE_VIE_PROIE);
    print(DIMW+115,7.5*TailleMenu,"DUREE VIE");
    print(DIMW+100,7.05*TailleMenu,"PREDATEUR :");
    print(DIMW+185,7.05*TailleMenu,e.DUREE_VIE_PREDATEUR);
    print(DIMW+130,6.5*TailleMenu,"JEUNE");
    print(DIMW+120,6.05*TailleMenu,"PROIE :");
    print(DIMW+170,6.05*TailleMenu,e.MAX_JEUNE_PROIE);
    print(DIMW+130,5.5*TailleMenu,"JEUNE");
    print(DIMW+100,5.05*TailleMenu,"PREDATEUR :");
    print(DIMW+185,5.05*TailleMenu,e.MAX_JEUNE_PREDATEUR);
    print(DIMW+80,4.4*TailleMenu,"DESHYDRATATION :");
    print(DIMW+205,4.4*TailleMenu,e.MAX_SOIF);
    print(DIMW+100,3.5*TailleMenu,"DUREE REPOUSSE");
    print(DIMW+120,3.05*TailleMenu,"HERBE :");
    print(DIMW+170,3.05*TailleMenu,e.DUREE_POUSSE_HERBE);
    print(DIMW+120,2.5*TailleMenu,"PUISSANCE");
    print(DIMW+110,2.05*TailleMenu,"MALADIES :");
    print(DIMW+190,2.05*TailleMenu,e.CHANCE_MALADIE);
    print(DIMW+130,1.5*TailleMenu,"CHANCE");
    print(DIMW+120,1.05*TailleMenu,"PLUIE :");
    print(DIMW+170,1.05*TailleMenu,e.CHANCE_PLUIE);
    print(DIMW+120,0.5*TailleMenu,"QUANTITE");
    print(DIMW+110,0.05*TailleMenu,"PLUIE :");
    print(DIMW+170,0.05*TailleMenu,e.EAU_PLUIE);
    menu_draw(Moins,DIMW+25,1,DIMW+75,9*TailleMenu);
    menu_draw(Plus,DIMW+225,1,DIMW+275,9*TailleMenu);
    menu_draw(Jour,DIMW+225,9.2*TailleMenu,DIMW+275,9.8*TailleMenu-1);
    image_draw(e.Plus,DIMW+225+0.2*TailleMenu,9.2*TailleMenu,0.6*TailleMenu,0.6*TailleMenu);
    for (i=0;i<9;i++)
    {
        image_draw(e.Moins,DIMW+25,1+i*TailleMenu,50,TailleMenu);
        image_draw(e.Plus,DIMW+225,1+i*TailleMenu,50,TailleMenu);
    }
    if (e.temps==-1) // On dessine "l'animation" de pluie s'il pleut
    {
        // Selon la variable animation, comprise entre 1 et 3, l'image sera différente
        if (animation==1)
            image_draw(e.Pluie,TailleCase,TailleCase,(e.dx-2)*TailleCase,(e.dy-2)*TailleCase);
        else if (animation==2)
            image_draw(e.Pluie2,TailleCase,TailleCase,(e.dx-2)*TailleCase,(e.dy-2)*TailleCase);
        else
        {
            image_draw(e.Pluie3,TailleCase,TailleCase,(e.dx-2)*TailleCase,(e.dy-2)*TailleCase);
            animation=0;
        }
        animation++; // On incrémente animation pour donner une impression d'animation quand la fonction est rappelée
    }
}

void cherche_case(Ecosysteme &e, int &i, int &j, int type)  // Cherche autour des coordonnées "i" "j" s'il y a une case de type "type"
{
    int k,l,tabk[8],tabl[8],n=0,r;
    for (k=i-1;k<i+2;k++)
    {
        for (l=j-1;l<j+2;l++)
        {
            if (k>0 && k<e.dy-1 && l>0 && l<e.dx-1)
            {
                if ((e.grille[k][l].type_individu==0 && type==0) || (type==1 && (e.grille[k][l].type_individu==1 || e.grille[k][l].type_individu==5) && e.grille[k][l].vivant==true)
                      || (type==-1 && e.grille[k][l].type_individu<2 && e.grille[k][l].herbe_mangee==false) || (type==3 && (e.grille[k][l].type_individu>2)))
                {
                    tabk[n]=k;  // On rempli les tableaux de coordonnées avec les coordonnées correspondant aux cases recherchées
                    tabl[n]=l;
                    n++;
                }
            }
        }
    }
    if (n>0)  // Si on a trouvé une case, on en choisit une aléatoirement
    {
        r=rand()%n;
        i=tabk[r];
        j=tabl[r];
    }
}

int valeur_Position_Proie(Ecosysteme &e, int i, int j)  // Fonction qui recherche la meilleur position pour une proie
{
    int k,l,valeur=0;
    for (k=1;k<e.dy-1;k++)
    {
        for (l=1;l<e.dx-1;l++)
        {
            if (e.grille[k][l].type_individu==2 || e.grille[k][l].type_individu==6)
            {
                if (abs(i-k)+abs(j-l)==1 || (abs(i-k)==1 && abs(j-l)==1))  // Si un prédateur est dans l'entourage immédiat
                    valeur-=100;  // très mauvaise position, la proie risque d'être dévorée
                else
                    valeur+=abs(i-k)+abs(j-l);  // sinon, la valeur de la position augmente avec la distance au prédateur
            }
            // La présence d'une proie malade dans les environs est également une menace sérieuse
            if ((abs(i-k)+abs(j-l)==1 || abs(i-k)==1 && abs(j-l)==1) && e.grille[i][j].duree_maladie==-1 && e.grille[k][l].duree_maladie!=-1 && (e.grille[k][l].type_individu==1 || e.grille[k][l].type_individu==5))
                valeur-=20;
        }
    }
    return valeur;  // Plus la valeur est haute, moins la proie est menacée
}

int Distance_Proie_La_Plus_Proche(Ecosysteme &e, int i, int j)  // Fonction renvoyant la distance entre le prédateur et la proie la plus proche
{
    int k,l,valeur=5000;  // On initialise la valeur de façon a être forcément supérieure à la distance
    for (k=1;k<e.dy-1;k++)
    {
        for (l=1;l<e.dx-1;l++)
        {
            if (e.grille[k][l].type_individu==1)
            {
                if (abs(i-k)+abs(j-l)<valeur)  // Si la distance est plus petite que la valeur actuelle, on récupère cette distance
                    valeur=abs(i-k)+abs(j-l);
            }
        }
    }
    return valeur;  // On retourne la distance à la proie la plus proche
}

void mouvement(Ecosysteme &e, int i, int j, int i2, int j2)  // Effectue le déplacement d'une proie ou d'un prédateur
{
    if (i!=i2 || j!=j2)  // On vérifie que l'animal s'est déplacé et n'est pas simplement resté à son emplacement
    {
        if (e.grille[i2][j2].type_individu==0)  // Si la destination est une case d'herbe
        {
            if (e.grille[i][j].type_individu==5 || e.grille[i][j].type_individu==1)  // Si l'animal est une proie
                e.grille[i2][j2].type_individu=1;
            else if (e.grille[i][j].type_individu==6 || e.grille[i][j].type_individu==2)  // Si c'est un prédateur
                e.grille[i2][j2].type_individu=2;
        }
        else if (e.grille[i2][j2].type_individu==4)  // Si la destination est un gué
        {
            if (e.grille[i][j].type_individu==5 || e.grille[i][j].type_individu==1)
                e.grille[i2][j2].type_individu=5;
            else if (e.grille[i][j].type_individu==6 || e.grille[i][j].type_individu==2)
                e.grille[i2][j2].type_individu=6;
        }
        // On modifie les propriétés de la case d'arrivée
        e.grille[i2][j2].femelle=e.grille[i][j].femelle;
        e.grille[i2][j2].duree_jeune=e.grille[i][j].duree_jeune;
        e.grille[i2][j2].duree_vie=e.grille[i][j].duree_vie;
        e.grille[i2][j2].duree_soif=e.grille[i][j].duree_soif;
        e.grille[i2][j2].duree_maladie=e.grille[i][j].duree_maladie;
        e.grille[i2][j2].pleine=e.grille[i][j].pleine;
        e.grille[i2][j2].vivant=true;
        // On modifie le type de la case de départ
        if (e.grille[i][j].type_individu==5 || e.grille[i][j].type_individu==6)
            e.grille[i][j].type_individu=4;
        else
            e.grille[i][j].type_individu=0;
    }
    e.grille[i2][j2].a_bouge=true;  // L'animal n'a plus la possibilité de bouger ce tour-ci
}

void meilleur_Mouvement_Proie(Ecosysteme &e, int i, int j, int &k, int &l)  // Algorithme re recherche du meilleur mouvement des proies
{
    int i2,j2,valeurFils,valeurNoeud=-50000;  // On initialise valeurNoeud à un minimum inatteignable
    for (i2=i-1;i2<i+2;i2++) // On parcours le voisinage immédiat
    {
        for (j2=j-1;j2<j+2;j2++)
        {
            // On vérifie que le mouvement est possible (d'une case sur le côté ou en haut, que la case est libre et est dans la grille)
            if (((abs(i-i2)+abs(j-j2)==1 && (e.grille[i2][j2].type_individu==0 || e.grille[i2][j2].type_individu==4)) || (i==i2 && j==j2)) && i2>0 && i2<e.dy-1 && j2>0 && j2<e.dx-1)
            {
                Ecosysteme e2=e; // On créé une copie de l'Ecosysteme
                mouvement(e2,i,j,i2,j2);  // On fait le mouvement
                valeurFils=valeur_Position_Proie(e2,i2,j2);  // On récupère la valeur de la position de la proie
                if (valeurFils>valeurNoeud) // On garde la plus grande valeur et les coordonnées correspondantes
                {
                    valeurNoeud=valeurFils;
                    k=i2;
                    l=j2;
                }
            }
        }
    }
}

void meilleur_Mouvement_Predateur(Ecosysteme &e, int i, int j, int &k, int &l)  // Algorithme re recherche du meilleur mouvement des prédateurs
{
    int i2,j2,valeurFils,valeurNoeud=50000;  // On initialise valeurNoeud à un maximum inatteignable
    for (i2=i-1;i2<i+2;i2++)  // On parcours le voisinage immédiat
    {
        for (j2=j-1;j2<j+2;j2++)
        {
            // On vérifie que le mouvement est possible (d'une case sur le côté ou en haut, que la case est libre et est dans la grille)
            if (((abs(i-i2)+abs(j-j2)==1 && (e.grille[i2][j2].type_individu==0 || e.grille[i2][j2].type_individu==4)) || (i==i2 && j==j2)) && i2>0 && i2<e.dy-1 && j2>0 && j2<e.dx-1)
            {
                Ecosysteme e2=e; // On créé une copie de l'Ecosysteme
                mouvement(e2,i,j,i2,j2); // On fait le mouvement
                valeurFils=Distance_Proie_La_Plus_Proche(e2,i2,j2); // On récupère la valeur de la distance entre le prédateur et la proie la plus proche
                if (valeurFils<valeurNoeud)  // On garde la valeur la plus basse et les coordonnées correspondantes
                {
                    valeurNoeud=valeurFils;
                    k=i2;
                    l=j2;
                }
            }
        }
    }
}

bool Deplacements_Finis(Ecosysteme &e, int type) // Vérifie que tous les animaux ont effectué leur meilleur mouvement (proies si type==1, prédateurs si type==2)
{
    int i,j;
    for (i=1;i<e.dy-1;i++)
    {
        for (j=1;j<e.dx-1;j++)
        {
            if ((((e.grille[i][j].type_individu==1 || e.grille[i][j].type_individu==5) && type==1) || ((e.grille[i][j].type_individu==2 || e.grille[i][j].type_individu==6) && type==2)) && e.grille[i][j].a_bouge==false)
                return false;
        }
    }
    return true;
}

void mouvements_random(Ecosysteme &e)  // Fait se déplacer dans un ordre aléatoire les prédateurs puis les proies
{
    int i,j,k,l;
    do
    {
        i=rand()%(e.dy-2)+1;
        j=rand()%(e.dx-2)+1;
        if ((e.grille[i][j].type_individu==2 || e.grille[i][j].type_individu==6) && e.grille[i][j].a_bouge==false)
        {
            meilleur_Mouvement_Predateur(e,i,j,k,l);
            mouvement(e,i,j,k,l);
        }
    } while (Deplacements_Finis(e,2)==false);
    do
    {
        i=rand()%(e.dy-2)+1;
        j=rand()%(e.dx-2)+1;
        if ((e.grille[i][j].type_individu==1 || e.grille[i][j].type_individu==5) && e.grille[i][j].a_bouge==false)
        {
            meilleur_Mouvement_Proie(e,i,j,k,l);
            mouvement(e,i,j,k,l);
        }
    } while (Deplacements_Finis(e,1)==false);
}

bool meme_espece(Ecosysteme &e, int i, int j, int k, int l)  // Renvoie true si deux cases ([i][j] et [k][l]) sont des individus de la même espèce
{
    if ((e.grille[i][j].type_individu==1 || e.grille[i][j].type_individu==5) && (e.grille[k][l].type_individu==1 || e.grille[k][l].type_individu==5))
        return true;
    if ((e.grille[i][j].type_individu==2 || e.grille[i][j].type_individu==6) && (e.grille[k][l].type_individu==2 || e.grille[k][l].type_individu==6))
        return true;
    return false;
}

bool adulte(Ecosysteme &e, int i, int j)  // Renvoie true si la case [i][j] contient un individu adulte
{
    if (e.grille[i][j].type_individu==1 || e.grille[i][j].type_individu==5)
    {
        if (e.grille[i][j].duree_vie>(e.DUREE_VIE_PROIE/5))
            return true;
    }
    else if (e.grille[i][j].type_individu==2 || e.grille[i][j].type_individu==6)
    {
        if (e.grille[i][j].duree_vie>(e.DUREE_VIE_PREDATEUR/5))
            return true;
    }
    return false;
}

void evolution_ecosysteme(Ecosysteme &e)  // Développe l'écosystème
{
    int i,j,i2,j2,k,l,m;
    e.jour++;  // On change le jour
    e.heure=0;  // On remet l'heure à 0
    m=1+rand()%100;  // On tire aléatoirement m, qui déterminera en fonction de CHANCE_PLUIE s'il va pleuvoir ou non
    if (m<e.CHANCE_PLUIE)
        e.temps=-1;
    else
        e.temps=0;
    Ecosysteme e2=e;  // On fait une copie de "e" pour faire toutes les modifications parallèlement
    for (i=1;i<e.dy-1;i++)  // On parcourt toutes les cases de la grille
    {
        for (j=1;j<e.dx-1;j++)
        {
            // S'il s'agit d'un animal
            if (e.grille[i][j].type_individu==1 || e.grille[i][j].type_individu==2 || e.grille[i][j].type_individu==5 || e.grille[i][j].type_individu==6)
            {
                if (e.grille[i][j].pleine==true)  // Si elle était pleine, on lui permet de s'accoupler au prochain tour
                {
                    e2.grille[i][j].pleine=false;
                }
                if (e.temps==-1 && e.grille[i][j].duree_soif!=-1) // S'il pleut et qu'il a soif, on diminue sa soif selon EAU_PLUIE
                {
                    e.grille[i][j].duree_soif-=e.EAU_PLUIE;
                    e2.grille[i][j].duree_soif-=e.EAU_PLUIE;
                    if (e.grille[i][j].duree_soif<-1)
                    {
                        e.grille[i][j].duree_soif=-1;
                        e2.grille[i][j].duree_soif=-1;
                    }
                }
                for (i2=i-1;i2<i+2;i2+=2)  // On regarde sur la colonne
                {
                    // On vérifie s'il peut s'accoupler
                    if (i2>0 && i2<e.dy-1 && meme_espece(e,i,j,i2,j)==true && adulte(e,i,j)==true && adulte(e,i2,j)==true && ((e.grille[i][j].femelle==false && e.grille[i2][j].femelle==true && e.grille[i2][j].pleine==false)
                                                             || (e.grille[i][j].femelle==true && e.grille[i2][j].femelle==false && e.grille[i][j].pleine==false)))
                    {
                        if (e.grille[i][j].femelle==true) // k et l prennent les coordonnées de la femelle du couple
                        {
                            k=i;
                            l=j;
                        }
                        else
                        {
                            k=i2;
                            l=j;
                        }
                        cherche_case(e2,k,l,0);  // on cherche une case libre autour de la femelle
                        if ((k!=i || l!=j) && (k!=i2 || l!=j)) // Si on en a trouvé une, on crée un nouvel individu
                        {
                            if (e.grille[i][j].femelle==false)
                            {
                                e.grille[i2][j].pleine=true;
                                e2.grille[i2][j].pleine=true;
                            }
                            else
                            {
                                e.grille[i][j].pleine=true;
                                e2.grille[i][j].pleine=true;
                            }
                            if (e.grille[i][j].type_individu==1 || e.grille[i][j].type_individu==5)
                            {
                                e2.grille[k][l].type_individu=1;
                                e2.nbproies++;
                            }
                            else if (e.grille[i][j].type_individu==2 || e.grille[i][j].type_individu==6)
                            {
                                e2.grille[k][l].type_individu=2;
                                e2.nbpredateurs++;
                            }
                            e2.grille[k][l].femelle=rand()%2;
                            e2.grille[k][l].duree_vie=0;
                            e2.grille[k][l].duree_jeune=0;
                            e2.grille[k][l].duree_soif=0;
                            e2.grille[k][l].a_bouge=false;
                            e2.grille[k][l].vivant=true;
                            e2.grille[k][l].pleine=false;
                            if (e.grille[i][j].duree_maladie!=-1 || e.grille[i2][j].duree_maladie!=-1)
                                m=rand()%(e.dx*e.dy/(e.CHANCE_MALADIE*10));
                            else
                                m=rand()%(e.dx*e.dy/e.CHANCE_MALADIE);
                            if (m==0)
                                e2.grille[k][l].duree_maladie=0;
                            else
                                e2.grille[k][l].duree_maladie=-1;
                        }
                    }
                }
                for (j2=j-1;j2<j+2;j2+=2)  // On fait de même sur la ligne
                {
                    if (j2>0 && j2<e.dx-1 && meme_espece(e,i,j,i,j2)==true && adulte(e,i,j)==true && adulte(e,i,j2)==true && ((e.grille[i][j].femelle==false && e.grille[i][j2].femelle==true && e.grille[i][j2].pleine==false)
                                                             || (e.grille[i][j].femelle==true && e.grille[i][j2].femelle==false && e.grille[i][j].pleine==false)))
                    {
                        if (e.grille[i][j].femelle==true)
                        {
                            k=i;
                            l=j;
                        }
                        else
                        {
                            k=i;
                            l=j2;
                        }
                        cherche_case(e2,k,l,0);
                        if ((k!=i || l!=j) && (k!=i || l!=j2))
                        {
                            if (e.grille[i][j].femelle==false)
                            {
                                e.grille[i][j2].pleine=true;
                                e2.grille[i][j2].pleine=true;
                            }
                            else
                            {
                                e.grille[i][j].pleine=true;
                                e2.grille[i][j].pleine=true;
                            }
                            if (e.grille[i][j].type_individu==1 || e.grille[i][j].type_individu==5)
                            {
                                e2.grille[k][l].type_individu=1;
                                e2.nbproies++;
                            }
                            else if (e.grille[i][j].type_individu==2 || e.grille[i][j].type_individu==6)
                            {
                                e2.grille[k][l].type_individu=2;
                                e2.nbpredateurs++;
                            }
                            e2.grille[k][l].femelle=rand()%2;
                            e2.grille[k][l].duree_vie=0;
                            e2.grille[k][l].duree_jeune=0;
                            e2.grille[k][l].duree_soif=0;
                            e2.grille[k][l].a_bouge=false;
                            e2.grille[k][l].vivant=true;
                            e2.grille[k][l].pleine=false;
                            if (e.grille[i][j].duree_maladie!=-1 || e.grille[i][j2].duree_maladie!=-1)
                                m=rand()%(e.dx*e.dy/(e.CHANCE_MALADIE*10));
                            else
                                m=rand()%(e.dx*e.dy/e.CHANCE_MALADIE);
                            if (m==0)
                                e2.grille[k][l].duree_maladie=0;
                            else
                                e2.grille[k][l].duree_maladie=-1;
                        }
                    }
                }
                if (e.grille[i][j].duree_soif!=-1) // Si l'animal a soif :
                {
                    if (e.grille[i][j].type_individu>4) // S'il est sur un gué il n'a plus soif
                    {
                        e.grille[i][j].duree_soif=-1;
                        e2.grille[i][j].duree_soif=-1;
                    }
                    else // Sinon on vérifie s'il a une case d'eau à côté de lui, auquel cas il n'a plus soif
                    {
                        k=i;l=j;
                        cherche_case(e,k,l,3);
                        if (k!=i || l!=j)
                        {
                            e.grille[i][j].duree_soif=-1;
                            e2.grille[i][j].duree_soif=-1;
                        }
                    }
                }
                if (e.grille[i][j].duree_maladie>1 && e.grille[i][j].vivant==true)  // S'il es malade et toujours vivant
                {
                    m=rand()%(1+e.grille[i][j].duree_maladie/2);       // Survit si m==0, meurt sinon
                    if (m==0)  // S'il survit
                    {
                        m=rand()%(1+e.grille[i][j].duree_maladie/2);        // Guérit si m==0, reste malade sinon
                        if (m==0)
                            e2.grille[i][j].duree_maladie=-1;
                    }
                    else // Sinon il meurt, on réinitialise la case
                    {
                        e.grille[i][j].vivant=false;
                        if (e.grille[i][j].type_individu==1 || e.grille[i][j].type_individu==5)
                            e2.nbproies--;
                        else
                            e2.nbpredateurs--;
                        if (e.grille[i][j].type_individu>4)
                            e2.grille[i][j].type_individu=4;
                        else
                            e2.grille[i][j].type_individu=0;
                    }
                }
            }
            if (e.grille[i][j].type_individu==1 || e.grille[i][j].type_individu==5)  // S'il s'agit d'une proie
            {
                if (e.grille[i][j].duree_jeune!=-1)  // Si elle a faim, On vérifie si elle peut manger, d'abord l'herbe sous-elle, puis autour d'elle
                {
                    if (e.grille[i][j].herbe_mangee==false)
                    {
                        e.grille[i][j].duree_jeune=-1;
                        e2.grille[i][j].duree_jeune=-1;
                        e.grille[i][j].herbe_mangee=true;
                        e2.grille[i][j].herbe_mangee=true;
                        e2.grille[i][j].duree_pousse=0;
                    }
                    else
                    {
                        k=i;l=j;
                        cherche_case(e,k,l,-1);
                        if (k!=i || l!=j)
                        {
                            e.grille[i][j].duree_jeune=-1;
                            e2.grille[i][j].duree_jeune=-1;
                            e.grille[k][l].herbe_mangee=true;
                            e2.grille[k][l].herbe_mangee=true;
                            e2.grille[k][l].duree_pousse=0;
                        }
                    }
                }
                if (e.grille[i][j].duree_maladie==-1) // Si elle n'est pas malade, on vérifie si elle attrape la maladie d'un individu proche
                {
                    for (k=i-1;k<i+2;k++)
                    {
                        for (l=j-1;l<j+2;l++)
                        {
                            if (e.grille[k][l].duree_maladie>0 && (e.grille[k][l].type_individu==1 || e.grille[k][l].type_individu==2 || e.grille[k][l].type_individu==5 || e.grille[k][l].type_individu==6))
                            {
                                m=rand()%(3*e.CHANCE_MALADIE);
                                if (m>0)
                                    e2.grille[i][j].duree_maladie=0;
                            }
                        }
                    }
                }
                // On vérifie les cas possibles de mort de la proie et, si l'un est atteint, on fait mourir la proie
                if ((e.grille[i][j].duree_jeune>=e.MAX_JEUNE_PROIE || e.grille[i][j].duree_vie>=e.DUREE_VIE_PROIE || e.grille[i][j].duree_soif>=e.MAX_SOIF ) && e.grille[i][j].vivant==true)
                {
                    if (e.grille[i][j].type_individu==1)
                        e2.grille[i][j].type_individu=0;
                    else
                        e2.grille[i][j].type_individu=4;
                    e.grille[i][j].vivant=false;
                    e2.nbproies--;
                }
                else // Sinon on incrémente ses paramètres
                {
                    e2.grille[i][j].duree_jeune++;
                    e2.grille[i][j].duree_vie++;
                    e2.grille[i][j].duree_soif++;
                    e2.grille[i][j].a_bouge=false;
                    if (e.grille[i][j].duree_maladie!=-1)
                        e2.grille[i][j].duree_maladie++;
                }
            }
            else if (e.grille[i][j].type_individu==2 || e.grille[i][j].type_individu==6)  // On fait de même avec les prédateurs
            {
                // Pour la faim, on vérifie autour s'il y a une proie encore vivante (un prédateur ne mangera pas de proie morte de maladie, faim ou autre, ou tuée par un autre prédateur)
                if (e.grille[i][j].duree_jeune!=-1)
                {
                    k=i;l=j;
                    cherche_case(e,k,l,1);
                    if (k!=i || l!=j)
                    {
                        e2.nbproies--;
                        if (e.grille[k][l].type_individu==1)
                            e2.grille[k][l].type_individu=0;
                        else
                            e2.grille[k][l].type_individu=4;
                        e.grille[i][j].duree_jeune=-1;
                        e2.grille[i][j].duree_jeune=-1;
                        e.grille[k][l].vivant=false;
                        if (e.grille[k][l].duree_maladie>0)
                        {
                            m=rand()%(3*e.CHANCE_MALADIE);
                            if (m>0)
                                e2.grille[i][j].duree_maladie=0;
                        }
                    }
                }
                if (e.grille[i][j].duree_maladie==-1)
                {
                    for (k=i-1;k<i+2;k++)
                    {
                        for (l=j-1;l<j+2;l++)
                        {
                            if (e.grille[k][l].duree_maladie>0 && (e.grille[k][l].type_individu==1 || e.grille[k][l].type_individu==2 || e.grille[k][l].type_individu==5 || e.grille[k][l].type_individu==6))
                            {
                                m=rand()%(3*e.CHANCE_MALADIE);
                                if (m>0)
                                    e2.grille[i][j].duree_maladie=0;
                            }
                        }
                    }
                }
                if (e.grille[i][j].duree_jeune>=e.MAX_JEUNE_PREDATEUR || e.grille[i][j].duree_vie>=e.DUREE_VIE_PREDATEUR || e.grille[i][j].duree_soif>=e.MAX_SOIF)
                {
                    if (e.grille[i][j].type_individu==2)
                        e2.grille[i][j].type_individu=0;
                    else
                        e2.grille[i][j].type_individu=4;
                    e2.nbpredateurs--;
                }
                e2.grille[i][j].duree_jeune++;
                e2.grille[i][j].duree_vie++;
                e2.grille[i][j].duree_soif++;
                e2.grille[i][j].a_bouge=false;
                if (e.grille[i][j].duree_maladie!=-1)
                    e2.grille[i][j].duree_maladie++;
            }
            if (e.grille[i][j].type_individu<3)  // S'il s'agit d'une case de terre (qu'il y ait un animal ou non dessus) on vérifie si l'herbe repousse ou non
            {
                if (e.grille[i][j].duree_pousse>=e.DUREE_POUSSE_HERBE)
                    e2.grille[i][j].herbe_mangee=false;
                e2.grille[i][j].duree_pousse++;
            }
        }
    }
    e=e2; // On récupère le nouvel Ecosysteme
}

void attendre(float temps) // La fonction attends "delay/1000" secondes
{
    while((float)clock()/CLOCKS_PER_SEC<(float)temps+DELAY/1000);
}

void init_joueur(Ecosysteme  &e) // On demande les paramètres de jeu au joueur
{
    cout<<"Nombre de lignes (compris entre 10 et 50) : "<<endl;
    do
    {
        cin>>e.dy;
        if (e.dy<10 || e.dy>50)
            cout<<"Entree incorrecte."<<endl;
    } while (e.dy<10 || e.dy>50);
    cout<<"Nombre de colonnes (compris entre 10 et 50) : "<<endl;
    do
    {
        cin>>e.dx;
        if (e.dx<10 || e.dx>50)
            cout<<"Entree incorrecte."<<endl;
    } while (e.dx<10 || e.dx>50);
    cout<<"Nombre de proies (compris entre 5 et "<<(e.dx-2)*(e.dy-2)/3<<") : "<<endl;
    do
    {
        cin>>e.nbproies;
        if (e.nbproies<5 || e.nbproies>(e.dx-2)*(e.dy-2)/3)
            cout<<"Entree incorrecte."<<endl;
    } while (e.nbproies<5 || e.nbproies>(e.dx-2)*(e.dy-2)/3);
    cout<<"Nombre de predateurs (compris entre 5 et "<<(e.dx-2)*(e.dy-2)/3<<") : "<<endl;
    do
    {
        cin>>e.nbpredateurs;
        if (e.nbpredateurs<5 || e.nbpredateurs>(e.dx-2)*(e.dy-2)/3)
            cout<<"Entree incorrecte."<<endl;
    } while (e.nbpredateurs<5 || e.nbpredateurs>(e.dx-2)*(e.dy-2)/3);
    cout<<"Duree de vie des proies (compris entre 5 et 25) : "<<endl;
    do
    {
        cin>>e.DUREE_VIE_PROIE;
        if (e.DUREE_VIE_PROIE<5 || e.DUREE_VIE_PROIE>25)
            cout<<"Entree incorrecte."<<endl;
    } while (e.DUREE_VIE_PROIE<5 || e.DUREE_VIE_PROIE>25);
    cout<<"Duree de vie des predateurs (compris entre 5 et 25) : "<<endl;
    do
    {
        cin>>e.DUREE_VIE_PREDATEUR;
        if (e.DUREE_VIE_PREDATEUR<5 || e.DUREE_VIE_PREDATEUR>25)
            cout<<"Entree incorrecte."<<endl;
    } while (e.DUREE_VIE_PREDATEUR<5 || e.DUREE_VIE_PREDATEUR>25);
    cout<<"Duree de jeune maximum des proies (compris entre 2 et 15) : "<<endl;
    do
    {
        cin>>e.MAX_JEUNE_PROIE;
        if (e.MAX_JEUNE_PROIE<2 || e.MAX_JEUNE_PROIE>15)
            cout<<"Entree incorrecte."<<endl;
    } while (e.MAX_JEUNE_PROIE<2 || e.MAX_JEUNE_PROIE>15);
    cout<<"Duree de jeune maximum des predateurs (compris entre 4 et 15) : "<<endl;
    do
    {
        cin>>e.MAX_JEUNE_PREDATEUR;
        if (e.MAX_JEUNE_PREDATEUR<4 || e.MAX_JEUNE_PREDATEUR>15)
            cout<<"Entree incorrecte."<<endl;
    } while (e.MAX_JEUNE_PREDATEUR<4 || e.MAX_JEUNE_PREDATEUR>15);
    cout<<"Duree de deshydration maximum (compris entre 3 et 10) : "<<endl;
    do
    {
        cin>>e.MAX_SOIF;
        if (e.MAX_SOIF<3 || e.MAX_SOIF>10)
            cout<<"Entree incorrecte."<<endl;
    } while (e.MAX_SOIF<3 || e.MAX_SOIF>10);
    cout<<"Duree de repousse de l'herbe (compris entre 1 et 10) : "<<endl;
    do
    {
        cin>>e.DUREE_POUSSE_HERBE;
        if (e.DUREE_POUSSE_HERBE<1 || e.DUREE_POUSSE_HERBE>10)
            cout<<"Entree incorrecte."<<endl;
    } while (e.DUREE_POUSSE_HERBE<1 || e.DUREE_POUSSE_HERBE>10);
    cout<<"Apparition et dangerosite des maladies (compris entre 1 et 5) : "<<endl;
    do
    {
        cin>>e.CHANCE_MALADIE;
        if (e.CHANCE_MALADIE<1 || e.CHANCE_MALADIE>5)
            cout<<"Entree incorrecte."<<endl;
    } while (e.CHANCE_MALADIE<1 || e.CHANCE_MALADIE>5);
    cout<<"Pourcentage de chance qu'il pleuve (compris entre 10 et 90) : "<<endl;
    do
    {
        cin>>e.CHANCE_PLUIE;
        if (e.CHANCE_PLUIE<10 || e.CHANCE_PLUIE>90)
            cout<<"Entree incorrecte."<<endl;
    } while (e.CHANCE_PLUIE<10 || e.CHANCE_PLUIE>90);
    cout<<"Baisse de la deshydratation par jour de pluie (compris entre 1 et 5) : "<<endl;
    do
    {
        cin>>e.EAU_PLUIE;
        if (e.EAU_PLUIE<1 || e.EAU_PLUIE>5)
            cout<<"Entree incorrecte."<<endl;
    } while (e.EAU_PLUIE<1 || e.EAU_PLUIE>5);
}

void regles() // On affiche les règles
{
    cout<<endl<<"\t\t\t\t\tREGLES"<<endl<<
    "- Les proies mangent l'herbe dans leur voisinage ou sous elles."<<endl<<
    "- Une seule proie peut se nourrir par case d'herbe. Une fois mangee, l'herbe a un temps de repousse."<<endl<<
    "- Les predateurs mangent les proies dans leur voisinage."<<endl<<
    "- Un seul predateur peut se nourrir par proie. Une fois mangee, la proie est consideree comme deja prise."<<endl<<
    "- Un predateur ou une proie ne peut se nourrir qu'une fois par jour."<<endl<<
    "- Si deux proies ou deux predateurs de sexe oppose sont adjacents et qu'il y a une case libre dans le voisinage de la femelle, un petit nait."<<endl<<
    "- Une femelle ne peut faire qu'un enfant par jour."<<endl<<
    "- Apres une mise a bat, une femelle doit attendre 1 tour avant de pouvoir s'accoupler de nouveau."<<endl<<
    "- Deux animaux ne peuvent s'accoupler que s'ils sont adultes."<<endl<<
    "- Les animaux de la premiere generation naissent a la limite de l'age adulte."<<endl<<
    "- La limite de l'age adulte correspond a 1/5 de leur duree de vie."<<endl<<
    "- Une proie ou un predateur peut mourir par :"<<endl<<
                "\t\t- manque de nourriture durant trop longtemps;"<<endl<<
                "\t\t- manque d'eau pendant trop longtemps;"<<endl<<
                "\t\t- vieillesse;"<<endl<<
                "\t\t- maladie."<<endl<<
    "- Le sexe est determine aleatoirement de facon equitable a la naissance."<<endl<<
    "- Il y a une certaine probabilite de naitre malade, en fonction de la taille de la grille."<<endl<<
    "- Avoir au moins un parent malade augmente grandement la probabilite que l'enfant soit malade."<<endl<<
    "- Chaque animal malade dans l'entourage augmente les chances d'etre contamine si l'animal est malade depuis au moins 1 jour."<<endl<<
    "- Un predateur qui mange une proie malade risque la contamination."<<endl<<
    "- Un animal contamine risque de mourir apres un jour."<<endl<<
    "- Un animal contamine a une chance de guerir."<<endl<<
    "- Plus l'animal est contamine depuis longtemps, moins il a chance de guerir et plus il risque la mort."<<endl<<
    "- Les proies se deplacent de facon a s'eloigner de tous les predateurs et eviter le contact direct."<<endl<<
    "- Les proies se deplacent de facon a eviter le contact direct avec leurs congeneres malades."<<endl<<
    "- Les predateurs se deplacent de facon a se rapprocher de la proie la plus proche."<<endl<<
    "- La riviere est generee aleatoirement avec un nombre de gues dependant de sa taille."<<endl<<
    "- Les animaux peuvent traverser la riviere aux gues."<<endl<<
    "- Les animaux peuvent boire s'ils ont dans leur voisinage une case d'eau ou un gue."<<endl<<
    "- Les animaux ne peuvent pas naitre sur un gue."<<endl<<
    "- Il fait beau a l'initialisation."<<endl<<
    "- Chaque jour le temps est choisi aleatoirement."<<endl<<
    "- Chaque jour de pluie descend la soif des animaux."<<endl<<
    "- La disparition d'une espece ou sa surpopulation (occupation de plus de 2/3 des cases) entrainera la defaite du joueur."<<endl<<endl<<endl;
}

int main(int , char** )
{
    srand(time(NULL));
    struct Ecosysteme e;
    Menu Moins, Plus, Jour;
    menu_add(Moins," ");
    menu_add(Moins," ");
    menu_add(Moins," ");
    menu_add(Moins," ");
    menu_add(Moins," ");
    menu_add(Moins," ");
    menu_add(Moins," ");
    menu_add(Moins," ");
    menu_add(Moins," ");
    menu_setSelect(Moins,9);      // En-dessous de 0: bug.   Entre 0 et 8: sélectionne un menu.   9: "menu fantôme" grâce à modification de Grapic.  Au-dessus de 9: bug
    Plus=Moins;
    menu_add(Jour," ");
    menu_setSelect(Jour,1);
    e.jeu_en_cours=false;
    int animation=0;
    float temps;
    bool stop=false;
	winInit("Terrain de jeu de <Dieu>", DIMW+300, DIMW);
	init_images(e);
	backgroundColor( 200, 200, 200 );
    while( !stop )
    {
        if (e.jeu_en_cours==false)  // Si le jeu n'a pas commencé / a été fini
        {
            // On affiche une petite animation de début
            winClear();
            float i=0;
            do
            {
                winClear();
                fontSize(30);
                print(DIMW/2-20,DIMW-20-i,"BIENVENUE... <DIEU> !");
                winDisplay();
                i+=0.5;
            } while (i<DIMW/2);
            delay(1000);
            i=0;
            do
            {
                winClear();
                fontSize(30+i);
                print(DIMW/2-20-10*i,DIMW/2-20,"BIENVENUE... <DIEU> !");
                winDisplay();
                i++;
            } while (i<75);
            regles();
            fontSize(12);
            print(DIMW/2-60,DIMW/2-50,"Veuillez consulter le manuel d'utilisation pour <DIEU>, aussi appelé <console>.");
            winDisplay();
            // On demande les informations au joueur
            init_joueur(e);
            // On lance les différentes initialisations et le jeu
            init(e);
            riviere(e);
            etat_initial(e);
            winClear();
            draw(e,animation,Moins,Plus,Jour);
            winDisplay();
            e.jeu_en_cours=true;
            delay(DELAY);
        }
        else if (e.nbpredateurs>0 && e.nbproies>0) // Si le jeu est en cours et qu'il reste au moins une proie ET un prédateur
        {
            winClear();
            mouvements_random(e);  // On lance les déplacements
            draw(e,animation,Moins,Plus,Jour); // On dessine
            winDisplay();
            temps=(float)clock()/CLOCKS_PER_SEC;  // On récupère le temps d'exécution actuel en seconde
            attendre(temps); // On attends
            winClear();
            evolution_ecosysteme(e);  // On fait évoluer l'écosystème
            draw(e,animation,Moins,Plus,Jour);  // On dessine la nouvelle situation
            temps=(float)clock()/CLOCKS_PER_SEC;  // On récupère le nouveau temps d'exécution
            while (menu_select(Moins)==9 && menu_select(Plus)==9 && menu_select(Jour)==1 && e.heure!=24)  // Tant qu'on ne change pas de paramètre ou que ce n'est pas 24h
            {
                if ((float)clock()/CLOCKS_PER_SEC-temps>=0.5) // Toutes les demi-secondes depuis la récupèration de "temps" on incrémente e.heure et on récupère le nouveau temps d'exécution
                {
                    e.heure++;
                    temps=(float)clock()/CLOCKS_PER_SEC;
                }
                winClear();
                // On redessine les menus
                menu_draw(Moins,DIMW+25,1,DIMW+75,9*DIMW/10);
                menu_draw(Plus,DIMW+225,1,DIMW+275,9*DIMW/10);
                menu_draw(Jour,DIMW+225,9.2*DIMW/10,DIMW+275,9.8*DIMW/10-1);
                draw(e,animation,Moins,Plus,Jour);
                winDisplay();
                // On modifie le paramètre choisi
                switch (menu_select(Moins))
                {
                    case 0 : if (e.DUREE_VIE_PROIE>5) e.DUREE_VIE_PROIE--; else menu_setSelect(Moins,9); break;
                    case 1 : if (e.DUREE_VIE_PROIE>5) e.DUREE_VIE_PREDATEUR--; else menu_setSelect(Moins,9); break;
                    case 2 : if (e.MAX_JEUNE_PROIE>2) e.MAX_JEUNE_PROIE--; else menu_setSelect(Moins,9); break;
                    case 3 : if (e.MAX_JEUNE_PREDATEUR>4) e.MAX_JEUNE_PREDATEUR--; else menu_setSelect(Moins,9); break;
                    case 4 : if (e.MAX_SOIF>3) e.MAX_SOIF--; else menu_setSelect(Moins,9); break;
                    case 5 : if (e.DUREE_POUSSE_HERBE>1) e.DUREE_POUSSE_HERBE--; else menu_setSelect(Moins,9); break;
                    case 6 : if (e.CHANCE_MALADIE>1) e.CHANCE_MALADIE--; else menu_setSelect(Moins,9); break;
                    case 7 : if (e.CHANCE_PLUIE>10) e.CHANCE_PLUIE-=10; else menu_setSelect(Moins,9); break;
                    case 8 : if (e.EAU_PLUIE>1) e.EAU_PLUIE--; else menu_setSelect(Moins,9); break;
                    default : break;
                }
                // Si aucun paramètre du menu "Moins" n'a été choisi, on modifie celui choisi dans le menu "Plus"
                if (menu_select(Moins)==9)
                {
                    switch (menu_select(Plus))
                    {
                        case 0 : if (e.DUREE_VIE_PROIE<25) e.DUREE_VIE_PROIE++; else menu_setSelect(Plus,9); break;
                        case 1 : if (e.DUREE_VIE_PROIE<25) e.DUREE_VIE_PREDATEUR++; else menu_setSelect(Plus,9); break;
                        case 2 : if (e.MAX_JEUNE_PROIE<15) e.MAX_JEUNE_PROIE++; else menu_setSelect(Plus,9); break;
                        case 3 : if (e.MAX_JEUNE_PREDATEUR<15) e.MAX_JEUNE_PREDATEUR++; else menu_setSelect(Plus,9); break;
                        case 4 : if (e.MAX_SOIF<10) e.MAX_SOIF++; else menu_setSelect(Plus,9); break;
                        case 5 : if (e.DUREE_POUSSE_HERBE<10) e.DUREE_POUSSE_HERBE++; else menu_setSelect(Plus,9); break;
                        case 6 : if (e.CHANCE_MALADIE<5) e.CHANCE_MALADIE++; else menu_setSelect(Plus,9); break;
                        case 7 : if (e.CHANCE_PLUIE<90) e.CHANCE_PLUIE+=10; else menu_setSelect(Plus,9); break;
                        case 8 : if (e.EAU_PLUIE<5) e.EAU_PLUIE++; else menu_setSelect(Plus,9); break;
                        default : break;
                    }
                    // Si aucun paramètre n'a été choisi, on vérifie si le menu "Jour" a été choisi
                    if (menu_select(Plus)==9)
                    {
                        switch(menu_select(Jour))
                        {
                            case 0 : break;
                            default : break;
                        }
                    }
                }
            }
            winClear();
            draw(e,animation,Plus,Moins,Jour);
            // On remet les menu sur leur case fantôme
            menu_setSelect(Plus,9);
            menu_setSelect(Moins,9);
            menu_setSelect(Jour,1);
            // On vérifie si le joueur a perdu
            if (e.nbproies==0 || e.nbpredateurs==0 || e.nbproies>(e.dx-2)*(e.dy-2)*2/3 || e.nbpredateurs>(e.dx-2)*(e.dy-2)*2/3)
            {
                cout<<"Vous avez echoue. Vous ne meritez pas de vous faire appeler <DIEU> !"<<endl;
                e.jeu_en_cours=false;
            }
        }
        stop = winDisplay();
        delay(DELAY);
    }
    winQuit();
	return 0;
}
