#include "vector.hpp"
#include <math.h>

Vec2 make_vector(float x, float y)
{
    Vec2 V;
    V.x = x;
    V.y = y;
    return V;
}

//rappel : float est en degré
Vec2 make_vector_exp(float r, float theta)
{
    Vec2 V;
    V.x = r * cos(theta * M_PI/180);
    V.y = r * sin(theta * M_PI/180);
    return V;
}

bool operator==(Vec2 a, Vec2 b)
{
    if ((a.x == b.x) && (a.y == b.y))
    {
        return true;
    }
    return false;
}

Vec2 operator+(Vec2 a, int val)
{
    Vec2 V;
    V.x = a.x + val;
    V.y = a.y + val;
    return V;
}

Vec2 operator+(Vec2 a, Vec2 b)
{
    Vec2 V;
    V.x = a.x + b.x;
    V.y = a.y + b.y;
    return V;
}

Vec2 operator-(Vec2 a, Vec2 b)
{
    Vec2 V;
    V.x = a.x - b.x;
    V.y = a.y - b.y;
    return V;
}

Vec2 operator-(Vec2 a, float lambda)
{
    Vec2 V;
    V.x = a.x - lambda;
    V.y = a.y - lambda;
    return V;
}

Vec2 operator/(Vec2 a, float lambda)
{
    Vec2 V;
    V.x = a.x/lambda;
    V.y = a.y/lambda;
    return V;
}

Vec2 operator*(float lambda, Vec2 b)
{
    Vec2 V;
    V.x = lambda * b.x;
    V.y = lambda * b.y;
    return V;
}

Vec2 operator*(Vec2 b, float lambda)
{
    return lambda * b;
}

Vec2 operator*(Vec2 a, Vec2 b)
{
    Vec2 V;
    V.x = a.x*b.x - a.y * b.y;
    V.y = a.x*b.y + a.y * b.x;
    return V;
}

Vec2 operator/(Vec2 a, Vec2 b)
{
    Vec2 V;
    V.x = (a.x*b.x + a.y*b.y)/((b.x*b.x) + (b.y*b.y));
    V.y = (a.y*b.x - a.x*b.y)/((b.x*b.x) + (b.y*b.y));
    return V;
}

Vec2 translate(Vec2 V, float dx, float dy)
{
    return V + make_vector(dx, dy);
}

Vec2 rotate(Vec2 V, float cx, float cy, float theta_deg)
{
    Vec2 r = make_vector_exp(1, theta_deg);
    Vec2 t = make_vector(cx, cy);
    return (V - t)*r + t;
}

Vec2 scale(Vec2 p, float cx, float cy, float lambda)
{
    //translation pour décaler l'origine du repere en cx cy
    Vec2 a0 = translate(p, cx, cy);
    //homotétie
    Vec2 a1 = a0 * lambda;
    //translation inverse pour remettre dans le bon repère
    Vec2 a2 = translate(a1, -cx, -cy);
    return a2;
}

float norm(const Vec2 v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

float normalize(Vec2& v)
{
    float n = norm(v);
    v.x /= n;
    v.y /= n;
    return n;
}

double get_distance(Vec2 a, Vec2 b)
{
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}
