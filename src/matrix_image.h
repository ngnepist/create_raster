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

//****************************************************************************

struct Matrix_image

/** \n
*\****************************************************************************\n 
*\ \n
*\  Purpose: \n
*\ \n
*\    Containt all pixels of the image \n
*\ \n
*\  Author: \n
*\  \n
*\    Stephane NGNEPIEPAYE WEMBE \n
*\ \n
*\  Parameters: \n
*\ \n
*\    Element1, Pixel **tab_pixel, table of pixels. \n
*\ \n
*\    Element2, int xsize, whidth of the image (number of pixels on the whidth). \n
*\ \n
*\    Element3, int ysize, heigth of the image (number of pixels on the heigth). \n
*\ \n
*/
{
     Pixel **tab_pixel;
     int xsize;
     int ysize;
};


bool compx(const Point& p1, const Point& p2);


bool compy(const Point& p1, const Point& p2);


bool compz(const Point& p1, const Point& p2);


void readdata(const string& file_name, vector<Point>& v_Point);


void init_Matrix_image(Matrix_image& matrix, int xsize, int ysize);


void setup_index_pixel(vector<Point>& v_Point, Matrix_image& matrix);


void setup_value_pixel(Matrix_image& matrix, vector<Point>& v_Point);


void set_shadow(Matrix_image& matrix, float Altitude, float Azimuth, float cellsize);


#endif