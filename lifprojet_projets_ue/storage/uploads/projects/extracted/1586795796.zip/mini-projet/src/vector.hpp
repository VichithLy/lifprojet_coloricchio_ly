//
// Created by franklin on 01/03/19.
//

#ifndef PARTICLE_VECTOR_HPP
#define PARTICLE_VECTOR_HPP

struct Vec2
{
    float x, y;
};

Vec2 make_vector(float x, float y);
Vec2 translate(Vec2 V, float dx, float dy);
Vec2 rotate(Vec2 V, float cx, float cy, float theta);
Vec2 scale(Vec2 V, float cx, float cy, float lambda);
Vec2 operator+(Vec2 a, int val);
Vec2 operator+(Vec2 a, Vec2 b);
Vec2 operator-(Vec2 a, float lambda);
Vec2 operator-(Vec2 a, Vec2 b);
Vec2 operator/(Vec2 a, float lambda);
Vec2 operator*(float lambda, Vec2 b);
Vec2 operator*(Vec2 b, float lambda);
Vec2 operator*(Vec2 a, Vec2 b);
Vec2 operator/(Vec2 a, Vec2 b);
bool operator==(Vec2 a, Vec2 b);
double get_distance(Vec2 a, Vec2 b);

#endif //PARTICLE_VECTOR_HPP
