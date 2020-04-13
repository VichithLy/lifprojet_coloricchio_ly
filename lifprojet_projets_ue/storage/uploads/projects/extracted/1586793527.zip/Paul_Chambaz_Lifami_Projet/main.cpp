#include <Grapic.h>
#include <cmath>
#include <iostream>

using namespace grapic;
using namespace std;

const int width = 1280, height = 800; // dimension de la fenetre

// FONCTIONS GENERALES (fonctions personnelles que j'utilise pour travailler, plusieurs fonctions de grapic renommees)

void Background (int r, int g, int b) {
    backgroundColor(r, g, b);
}

void Background (int g) {
    backgroundColor(g, g, g);
}

void Fill (int r, int g, int b) {
    color(r, g, b);
}

void Fill (int g) {
    color(g, g, g);
}

void Rect (float x, float y, float w, float h) {
    rectangleFill(x, y, x+w, y+h);
}

void Ellipse (float x, float y, float r) {
    circleFill(x, y, r);
}

void Line (float x1, float y1, float x2, float y2) {
    line(x1, y1, x2, y2);
}

void Triangle (float x1, float y1, float x2, float y2, float x3, float y3) {
    triangleFill(x1, y1, x2, y2, x3, y3);
}

void Constrain (float &value, float minumum, float maximum) {
    value = (value>maximum) ? maximum : value;
    value = (value<minumum) ? minumum : value;
}

float Map (float &value, float start1, float stop1, float start2, float stop2) {
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

float Random (float minimum, float maximum) {
    return frand(minimum, maximum);
}


// CONSTANTES

const float PI = 3.14159265;
const int MAX_TAILLE = 40; // taille max d'hexagones

// STRUCTURES

struct Vector {
    float x, y; // vecteur 2dim
};

struct Case {
    int nbProies, nbPredateurs; // le nombre de proies et de predateurs
    Image teteProie, tetePredateur; // les images associes
};

struct Ecosysteme {
    int ecoTaille; // taille de la grille d'hexagones
    Case ecosysteme[MAX_TAILLE][MAX_TAILLE]; // les cellules
    int indStEnd[MAX_TAILLE][2]; // parametre pour afficher les cellules en hexagones correctement
};

struct SimulEcosysteme {
    double nbProies, nbPredateurs; // le nombre de proies et de predateurs
    float alpha, beta, gamma, delta; // les parametres de la fonction
};

// FONCTIONS STRUCTURES

Vector newVector (float x, float y) {
    Vector n;
    n.x = x;
    n.y = y;
    return n; // initialise avec les entrees
}

Case newCase (int nbPro, int nbPre, Image tetPro, Image tetPre) {
    Case n;
    n.nbProies = nbPro;
    n.nbPredateurs = nbPre;
    n.teteProie = tetPro;
    n.tetePredateur = tetPre;
    return n; // initialise avec les entrees
}

Ecosysteme newEcosysteme (int taille) {
    Ecosysteme n;
    n.ecoTaille = taille * 2 + 1; // defini la taille total du tableau
     for (int i=0; i<n.ecoTaille; i++) { // calcul les limites pour chaque case
        n.indStEnd[i][0] = ((n.ecoTaille-1)/2-i > 0) ? (n.ecoTaille-1)/2-i : 0;
        n.indStEnd[i][1] = (3*(n.ecoTaille-1)/2-i < n.ecoTaille-1) ? 3*(n.ecoTaille-1)/2-i : n.ecoTaille-1;
    }
    Image teteProie = image("data/Projet/Chicken_Head.png"), tetePredateur = image("data/Projet/Fox_Head.png"); // charge les images
    for (int i=0; i<n.ecoTaille; i++) { // initialise chaque case avec de l'aleatoire
        for (int j=n.indStEnd[i][0]; j<=n.indStEnd[i][1]; j++) {
            n.ecosysteme[i][j] = newCase(irand(30, 50), irand(5, 15), teteProie, tetePredateur);
        }
    }
    return n; // initialise
}

SimulEcosysteme newSimulEcolsysteme (double nbProies, double nbPredateurs) {
    SimulEcosysteme n;
    n.nbProies = nbProies;
    n.nbPredateurs = nbPredateurs;
    n.alpha = .045;
    n.beta = .001;
    n.gamma = .025;
    n.delta = .0002;
    return n; // initialise avec les entrees et le parametre de TD
}

bool isInsideEcosysteme (Ecosysteme e, int i, int j) {
    return (i>=0 && i<e.ecoTaille && j>=e.indStEnd[i][0] && j<=e.indStEnd[i][1]); // renvoie si oui ou non l'index passe est hors de la grille
}

// FONCTIONS AFFICHAGE

Vector PointHex (float x, float y, float s, float i) {
    float angle = (i*60+30) * PI/180;
    return newVector(x + s*cos(angle), y+s*sin(angle)); // defini un point de l'hexagone en fonction de son index
}

void Hex (float x, float y, float s) {
    // dessine un hexagone a l'aide de 6 triangles
    for (int i=0; i<6; i++) {
        Vector a = PointHex(x, y, s, i);
        Vector b = PointHex(x, y, s, (i+1)%6);
        Triangle(x, y, a.x, a.y, b.x, b.y);
    }
}

Vector CoordToPos (int i, int j, float s) {
    return newVector(s*(sqrt(3)*j + sqrt(3)/2.*i), s*(3/2.*i)); // transforme les coordonnes de la grilles en coordonne d'affichage
}

void Display_Ecosysteme (Ecosysteme e, int sizeDisplay) {
    // affiche la grille
    for (int i=0; i<e.ecoTaille; i++) {
        for (int j=e.indStEnd[i][0]; j<=e.indStEnd[i][1]; j++) {
            // associe la taille de facon a ce que la case au centre du table soit en 0, 0
            Vector pos = CoordToPos(i - (e.ecoTaille-1)/2, j - (e.ecoTaille-1)/2, sizeDisplay);

            // affiche la case
            Fill(125, 145, 55);
            Hex(pos.x + width/2, pos.y + height/2, sizeDisplay);
            Fill(140, 160, 60);
            Hex(pos.x + width/2, pos.y + height/2, sizeDisplay-3);

            // affiche les images
            image_draw(e.ecosysteme[i][j].teteProie, pos.x+width/2 - sizeDisplay * .78, pos.y+height/2 - sizeDisplay * .2, sizeDisplay * .8, sizeDisplay * .8);
            image_draw(e.ecosysteme[i][j].tetePredateur, pos.x+width/2 - sizeDisplay * .0, pos.y+height/2 - sizeDisplay * .2, sizeDisplay * .8, sizeDisplay * .8);

            // affiche le nombre de proies predateurs
            fontSize(sizeDisplay*.4);
            color(10, 195, 175);
            print(pos.x+width/2 - sizeDisplay * .62, pos.y+height/2 - sizeDisplay * .6, e.ecosysteme[i][j].nbProies);
            color(255, 125, 0);
            print(pos.x+width/2 - sizeDisplay * -.15, pos.y+height/2 - sizeDisplay * .6, e.ecosysteme[i][j].nbPredateurs);


        }
    }
}

// FONCTIONS REGLES

void Update_Ecosysteme (Ecosysteme &e) {
    Ecosysteme e2 = e; // on effectue les modifications sur un double pour eviter tous conflits
    int voisins[6][2] = {{1, 0}, {0, 1}, {-1, 1}, {-1, 0}, {0, -1}, {1, -1}}; // valeurs des index des voisins sur une grille hexagonale
    for (int i=0; i<e.ecoTaille; i++) {
        for (int j=e.indStEnd[i][0]; j<=e.indStEnd[i][1]; j++) {

            // processus de reproduction
            e2.ecosysteme[i][j].nbProies *= frand(1.03, 1.07);
            e2.ecosysteme[i][j].nbProies *= frand(1.005, 1.015);
            e2.ecosysteme[i][j].nbProies += irand(2, 8);
            e2.ecosysteme[i][j].nbProies += irand(0, 2);

            // processus de chasse
            if (e.ecosysteme[i][j].nbPredateurs > 0) {
                float random = frand(1);
                if (random < e.ecosysteme[i][j].nbProies/e.ecosysteme[i][j].nbPredateurs) { // permet d'equilibrer les populations
                    // chasse reussi
                    e2.ecosysteme[i][j].nbProies *= .5;
                    e2.ecosysteme[i][j].nbPredateurs *= 1.8;
                } else {
                    // chasse rate
                    e2.ecosysteme[i][j].nbProies *= 1.8;
                    e2.ecosysteme[i][j].nbPredateurs *= .5;
                }
            }
            // processus chasse voisins
            for (int k=0; k<6; k++) {
                if (isInsideEcosysteme(e, i+voisins[k][0], j+voisins[k][1])) { // on utilise voisin pour trouver les 6 voisins de l'hexagone
                    if (e.ecosysteme[i][j].nbPredateurs > 0) {
                        float random = frand(1);
                        // chasse reussi
                        if (random < .16*e.ecosysteme[i+voisins[k][0]][j+voisins[k][1]].nbProies/e.ecosysteme[i][j].nbPredateurs) { // la chasse dans les voisins rapporte plus mais est plus couteuse et est plus dure
                            e2.ecosysteme[i+voisins[k][0]][j+voisins[k][1]].nbProies *= .3;
                            e2.ecosysteme[i][j].nbPredateurs *= 1.3;
                        } else {
                            // chasse rate
                            e2.ecosysteme[i+voisins[k][0]][j+voisins[k][1]].nbProies *= 1.1;
                        }
                    }
                }
            }


        }
    }

    for (int i=0; i<e.ecoTaille; i++) {
        for (int j=e.indStEnd[i][0]; j<=e.indStEnd[i][1]; j++) {
            // limite de taille (ex: plus d'herbe, de place, etc)
            e2.ecosysteme[i][j].nbProies = (e2.ecosysteme[i][j].nbProies > 200) ? 200 : e2.ecosysteme[i][j].nbProies;
            e2.ecosysteme[i][j].nbPredateurs = (e2.ecosysteme[i][j].nbPredateurs > 200) ? 200 : e2.ecosysteme[i][j].nbPredateurs;
        }
    }
    e = e2;
}

void conteurTotal (Ecosysteme e, int &nbProies, int &nbPredateurs) {
    nbProies = 0;
    nbPredateurs = 0;
    // conte le nombre de proies et de predateurs et le renvoie par adresse
    for (int i=0; i<e.ecoTaille; i++) {
        for (int j=e.indStEnd[i][0]; j<=e.indStEnd[i][1]; j++) {
            nbProies += e.ecosysteme[i][j].nbProies;
            nbPredateurs += e.ecosysteme[i][j].nbPredateurs;
        }
    }
}

void Simulation_Ecosysteme (SimulEcosysteme &e, double step) {
    // equations de la simulation
    SimulEcosysteme e2 = newSimulEcolsysteme(e.nbProies, e.nbPredateurs);
    e2.nbProies +=  step * (e.nbProies * (e.alpha - e.beta*e.nbPredateurs));
    e2.nbPredateurs += step * (-e.nbPredateurs * (e.gamma - e.delta*e.nbProies));
    e = e2;
}

int main (int , char** ) {
    bool stop = false;
    winInit("SimulNature", width, height);

    // permet de charger les images sur un joli fond bleu
    Background(45, 60, 110);
    winClear();
    winDisplay();

    srand(time(NULL)); // reintalise le hasard

    Ecosysteme e = newEcosysteme(5); // declaration de l'ecosysteme
    SimulEcosysteme eSimul = newSimulEcolsysteme(40, 10); // declaration de la simulation

    int nbProies = 0, nbPredateur = 0; // declaration du nombre de proies predateurs pour le conteur

    int t = 0; // declaration du temps

    // declaration des graphiques
    Plot plot;
    plot_setSize(plot, -1);

    Plot plotSimul;
    plot_setSize(plotSimul, -1);

    while(!stop) {
        Background(45, 60, 110);
        winClear();

        // UPDATE
        Update_Ecosysteme(e); // l'ecosysteme se met a jour
        conteurTotal(e, nbProies, nbPredateur); // l'ecosysteme est conte
        for (int i=0; i<100; i++) {
            Simulation_Ecosysteme(eSimul, 1); // la simulation se produit on fait plusieurs petite etapes pour etre plus proche de la realitee
        }

        // ajout des differentes courbes
        plot_add(plot, t, nbProies, 0);
        plot_add(plot, t, nbPredateur, 1);
        plot_add(plotSimul, t, eSimul.nbProies, 0);
        plot_add(plotSimul, t, eSimul.nbPredateurs, 1);

        t++; // le temps passe

        // DISPLAY
        Display_Ecosysteme(e, 45); // affiche l'ecosysteme
        // affiche les courbes
        Fill(255);
        plot_draw(plot, 30, 30, 300, 100, true);
        plot_draw(plotSimul, width-300, 30, width-30, 100, true);
        stop = winDisplay();
    }
    winQuit();
    return 0;
}
