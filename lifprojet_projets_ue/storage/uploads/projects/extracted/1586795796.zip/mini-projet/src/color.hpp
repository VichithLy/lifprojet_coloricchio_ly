//
// Created by franklin on 26/04/19.
//

#ifndef LIFAMI_GAME_COLOR_HPP
#define LIFAMI_GAME_COLOR_HPP

struct Color
{
    unsigned char r, g, b;
};

Color make_color(unsigned char r, unsigned char g, unsigned char b);
Color operator+(Color c1, Color c2);

#endif //LIFAMI_GAME_COLOR_HPP
