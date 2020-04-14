//
// Created by franklin on 26/04/19.
//

#include <iostream>
#include "color.hpp"

using namespace std;

Color make_color(unsigned char r, unsigned char g, unsigned char b)
{
    Color couleur;
    couleur.r = r;
    couleur.b = b;
    couleur.g = g;
    return couleur;
}

Color operator+(Color c1, Color c2)
{
    Color couleur;
    couleur.r = (c1.r + c2.r)%255;
    couleur.g = (c1.g + c2.g)%255;
    couleur.b = (c1.b + c2.b)%255;
    return couleur;
}