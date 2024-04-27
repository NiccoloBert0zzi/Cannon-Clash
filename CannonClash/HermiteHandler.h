#pragma once
#include "Lib.h"
#include "Geometry.h"

#define PHI0(t)  (2.0f * pow(t, 3) - 3.0f * pow(t, 2) + 1.0f)
#define PHI1(t)  (pow(t, 3) - 2.0f * pow(t, 2) + t)
#define PSI0(t)  (-2.0f * pow(t, 3) + 3.0f * pow(t, 2))
#define PSI1(t)  (pow(t, 3) - pow(t, 2))

float dx(int i, float* t, float tens, float bias, float cont, Shape* shape);

float dy(int i, float* t, float tens, float bias, float cont, Shape* shape);

float DX(int i, float* t, Shape* d, Shape* p);

float DY(int i, float* t, Shape* d, Shape* p);