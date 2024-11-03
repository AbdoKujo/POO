#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <cmath>

using namespace std;

class Point
{
private:
    float p1;
    float p2;

public:
    Point(float x, float y) : p1(x), p2(y) {}
    void deplace(float x, float y);
    void affiche();
};

#endif
