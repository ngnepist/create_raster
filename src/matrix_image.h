#ifndef __MATRIX_IMAGE_H__
#define __MATRIX_IMAGE_H__

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include "point_MNT.h"
#include "pixel.h"

using namespace std;

struct Matrix_image {
     Pixel **tab_pixel;
     //int **nb_point_pixel;
     int xsize;
     int ysize;
};

bool compx(const Point& p1, const Point& p2);
bool compy(const Point& p1, const Point& p2);
bool compz(const Point& p1, const Point& p2);
void readdata(const string& file_name, vector<Point>& v_Point);
void init_Matrix_image(Matrix_image& matrix, int xsize, int ysize);
void set_shadow(Matrix_image& matrix, float Altitude, float Azimuth, float cellsize);

#endif