//
// Created by franklin on 11/04/19.
//

#ifndef LIFAMI_GAME_PARTICULE_HPP
#define LIFAMI_GAME_PARTICULE_HPP

#include "vector.hpp"

struct Particle
{
    Vec2 p;
    Vec2 v;
    Vec2 f;
    float m;
};

Particle create_particle(Vec2 p, Vec2 v, Vec2 f, float m);
void remove_force(Particle &P, Vec2 f);
void add_force(Particle &P, Vec2 f);
void PartUpdate(float dt, Particle &P);
void translate_part(Particle &P, Vec2 V, float dx, float dy);
void rotate_part(Particle &P, Vec2 V, float cx, float cy, float theta);
void scale_part(Particle &P, Vec2 V, float cx, float cy, float lambda);

#endif //LIFAMI_GAME_PARTICULE_HPP
