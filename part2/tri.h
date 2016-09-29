#pragma once
#include <algorithm>
#include <memory>
#include <iostream>
//#include <tuple>
#include <vector>
typedef struct point
{
    int id;
	float x;
	float y;
} VERTEX2D, *VERTEX2D_PTR;

typedef struct edge
{
	point v1;
	point v2;
} EDGE, *EDGE_PTR;

typedef struct triangle
{
    int id;
	point i1; // vertex index
	point i2;
	point i3;
    edge e1;
    edge e2;
    edge e3;

} TRIANGLE, *TRIANGLE_PTR;



