//
// Created by franklin on 11/04/19.
//

#include <iostream>
#include "particule.hpp"

using namespace std;

Particle create_particle(Vec2 p, Vec2 v, Vec2 f, float m)
{
    Particle Part;
    Part.p = p;
    Part.f = f;
    Part.v = v;
    Part.m = m;
    return Part;
}

void remove_force(Particle &P, Vec2 f)
{
    P.f = P.f - f;
}

void add_force(Particle &P, Vec2 f)
{
    P.f = P.f + f;
}

void PartUpdate(float dt, Particle &P)
{
    if (P.m > 0)
    {
        P.p = P.p + P.v * dt;
        P.v = P.v + (P.f / P.m) * dt;
        P.f = make_vector(0, 0);
    }
}

void translate_part(Particle &P, Vec2 V, float dx, float dy)
{
    P.p = translate(V, dx, dy);
}

void rotate_part(Particle &P, Vec2 V, float cx, float cy, float theta)
{
    P.p = rotate(V, cx, cy, theta);
}

void scale_part(Particle &P, Vec2 V, float cx, float cy, float lambda)
{
    P.p = scale(V, cx, cy, lambda);
}