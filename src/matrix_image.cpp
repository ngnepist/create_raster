#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include "matrix_image.h"
#include "point_MNT.h"
#include "pixel.h"


//****************************************************************************

bool compx(const Point& p1, const Point& p2)

/** \n
*\**************************************************************************** \n
*\ \n
*\  Purpose: \n
*\ \n
*\    Compare two points using the x coordinate of points \n
*\ \n
*\  example \n
*\ \n
*\  P1(5, 2, 8) , P2(3, 7, 4)    ==>   P1 > P2 \n
*\ \n
*\  Author: \n
*\  \n
*\    Stephane NGNEPIEPAYE WEMBE \n
*\ \n
*\  Parameters: \n
*\ \n
*\    Input, const Point& p1, the first point to compare. \n
*\ \n
*\    Input, const Point& p2, the second point to compare. \n
*\ \n
*/
{
   return p1.p_x<p2.p_x;
}

//****************************************************************************

bool compy(const Point& p1, const Point& p2)

/** \n
*\**************************************************************************** \n
*\ \n
*\  Purpose: \n
*\ \n
*\    Compare two points using the y coordinate of points \n
*\ \n
*\  example \n
*\ \n
*\  P1(5, 2, 8) , P2(3, 7, 4)    ==>   P2 > P1 \n
*\ \n
*\  Author: \n
*\  \n
*\    Stephane NGNEPIEPAYE WEMBE \n
*\ \n
*\  Parameters: \n
*\ \n
*\    Input, const Point& p1, the first point to compare. \n
*\ \n
*\    Input, const Point& p2, the second point to compare. \n
*\ \n
*/
{
    return p1.p_y<p2.p_y;
}

//****************************************************************************

bool compz(const Point& p1, const Point& p2)

/** \n
*\**************************************************************************** \n
*\ \n
*\  Purpose: \n
*\ \n
*\    Compare two points using the z coordinate of points \n
*\ \n
*\  example \n
*\ \n
*\  P1(5, 2, 8) , P2(3, 7, 4)    ==>   P1 > P2 \n
*\ \n
*\  Author: \n
*\  \n
*\    Stephane NGNEPIEPAYE WEMBE \n
*\ \n
*\  Parameters: \n
*\ \n
*\    Input, const Point& p1, the first point to compare. \n
*\ \n
*\    Input, const Point& p2, the second point to compare. \n
*\ \n
*/
{
    return p1.p_level < p2.p_level;
}

//****************************************************************************

void readdata(const string& file_name, vector<Point>& v_Point)

/** \n
*\***************************************************************************** \n
*\ \n
*\  Purpose: \n
*\ \n
*\    Extract data of the MNT and put them inside a vector \n
*\ \n
*\  example \n
*\ \n
*\    48.19517461 -3.028930672 -117.281 \n
*\    48.19517496 -3.028923963 -117.469 \n
*\    48.1951753 -3.028917253 -117.527 \n
*\    48.19517564 -3.028910544 -117.506 \n
*\    48.19517738 -3.028964733 -116.976 \n
*\    ..... \n
*\ \n
*\  Author: \n
*\ \n
*\    Stephane NGNEPIEPAYE WEMBE \n
*\ \n
*\  Parameters: \n
*\ \n
*\    Input, const string& file_name, the name of the file containing data to extract. \n
*\ \n
*\    Input, vector<Point>& v_Point, the vector to fill. \n
*\ \n
*/
{
    ifstream f(file_name);

    if(!f.is_open())
    	cout << "Sorry! Open file failed." << endl;
    cout << "start reading" <<endl;
    while(!f.eof()) // eof: end of file
    { 
        Point *p = new Point(0,0,0);
        f >> *p;  // lecture du pixel

        if(f.eof()) // if end of file reached at this position...
        {
          delete p;
          break; // ...the reading is finish
        }
        v_Point.push_back(*p);
        cout <<"lecture de : "<< file_name << endl;
        //cout << p->p_longi << endl;
    }
    f.close();
    cout << "reading completed" <<endl;
}

//****************************************************************************

void init_Matrix_image(Matrix_image& matrix, int xsize, int ysize)

/** \n
*\**************************************************************************** \n
*\ \n
*\  Purpose:\n
*\ \n
*\    Create a matrix of pixel and initialize these pixels \n
*\ \n
*\  Author: \n
*\  \n
*\    Stephane NGNEPIEPAYE WEMBE \n
*\ \n
*\  Parameters: \n
*\ \n
*\    Input, Matrix_image& matrix, matrix of pixels of the image \n
*\    Input, const int& xsize, the whith of the image (number of pixels on the whidth) \n
*\    Input, int& ysize, the height of the image (number of pixels on the heigth) \n
*\ \n
*/
{
    matrix.xsize = xsize;
    matrix.ysize = ysize;

    matrix.tab_pixel = new Pixel*[matrix.ysize];
    for (int i=0; i<matrix.ysize; i++)
        matrix.tab_pixel[i]= new Pixel[matrix.xsize];

    cout << "init_Matrix_image starting" <<endl;
    for ( int i = 0; i < matrix.ysize; i++ )
    {
        for ( int j = 0; j < matrix.xsize; j++ )
        {

            matrix.tab_pixel[i][j] = Pixel();
        }
    }
    cout << "init_Matrix_image completed" <<endl;
}

//****************************************************************************

void setup_index_pixel(vector<Point>& v_Point, Matrix_image& matrix)

/** \n
*\**************************************************************************** \n
*\ \n
*\  Purpose: \n
*\ \n
*\    Set up of index of pixel inside the pixel matrix of the image  \n
*\    for each element of list of point of the MNT we find which pixel corresponding to that point \n
*\ \n
*\  Author:\n
*\  \n
*\    Stephane NGNEPIEPAYE WEMBE \n
*\ \n
*\  Parameters: \n
*\ \n
*\    Input, vector<Point>& v_Point, the vector of all points of the MNT. \n
*\    Input, Matrix_image& matrix, the matrix which containt all pixel of the image to set up \n
*\ \n
*/
{

    float minElement_x = (*std::min_element(v_Point.begin(), v_Point.end(), compx)).p_x;
    float maxElement_x = (*std::max_element(v_Point.begin(), v_Point.end(), compx)).p_x;
    float minElement_y = (*std::min_element(v_Point.begin(), v_Point.end(), compy)).p_y;
    float maxElement_y = (*std::max_element(v_Point.begin(), v_Point.end(), compy)).p_y;

    float amplitude_valeur_x = maxElement_x - minElement_x;
    float amplitude_valeur_y = maxElement_y - minElement_y;

    float peroide_x = amplitude_valeur_x / matrix.xsize;
    float peroide_y = amplitude_valeur_y / matrix.ysize;

    cout << "start setup_index_pixel" <<endl;
    for(std::size_t i = 0; i < v_Point.size(); ++i) {

        v_Point[i].p_i = floor(v_Point[i].p_x_relatif / peroide_x);
        v_Point[i].p_j = floor(v_Point[i].p_y_relatif / peroide_y);
        if (v_Point[i].p_j == matrix.ysize){
            v_Point[i].p_j = matrix.ysize - 1 ;
        }
        if (v_Point[i].p_i == matrix.xsize){
            v_Point[i].p_i = matrix.xsize - 1; 
        }
    }
    cout << "setup_index_pixel completed" <<endl;
}

//****************************************************************************

void setup_value_pixel(Matrix_image& matrix, vector<Point>& v_Point)

/** \n
*\**************************************************************************** \n
*\ \n
*\  Purpose: \n
*\ \n
*\    Set up of the value of pixel inside the pixel matrix of the image  \n
*\ \n
*\  Author:\n
*\ \n
*\    Stephane NGNEPIEPAYE WEMBE \n
*\ \n
*\  Parameters:\n
*\ \n
*\    Input, vector<Point>& v_Point, the vector of all points of the MNT.\n
*\    Input, Matrix_image& matrix, the matrix which containt all pixel of the image to set up\n
*\ \n
*/
{
    int i, j;
    float val;

    float minElement_z = (*std::min_element(v_Point.begin(), v_Point.end(), compz)).p_level;
    float maxElement_z = (*std::max_element(v_Point.begin(), v_Point.end(), compz)).p_level;

    cout << "start normalisation of pixel values" <<endl;

    for(std::size_t k = 0; k < v_Point.size(); ++k) {

        v_Point[k].p_level = (v_Point[k].p_level-minElement_z)/(maxElement_z-minElement_z);

    }

    cout << "normalisation of pixel values finish" <<endl;

    cout << "start setup_value_pixel" <<endl;
            
    for(std::size_t k = 0; k < v_Point.size(); ++k) {

        i = v_Point[k].p_i;
        j = v_Point[k].p_j;

        cout << "running please wait i = "<<i<<", j = "<<j<<endl;

        val = abs (v_Point[k].p_level);
        matrix.tab_pixel[j][i].set_val (val);

    }
    cout << "setup_value_pixel completed" <<endl;

    return;
}


//****************************************************************************

void set_shadow(Matrix_image& matrix, float Altitude, float Azimuth, float cellsize)

/** \n
*\**************************************************************************** \n
*\ \n
*\  Purpose:\n
*\ \n
*\    mise de l'ombrage mais ne fonctionne pas encore \n
*\ \n
*\  Author:\n
*\  \n
*\    Stephane NGNEPIEPAYE WEMBE \n
*\ \n
*\  Parameters: \n
*\ \n
*\    Input, Matrix_image& matrix, matrix of pixels of the image \n
*\ \n
*/
{
    float a, b, c, d, f, g, h, ii;
    int n = 0, m =0;
    float Zenith_deg, Zenith_rad, Azimuth_math, Azimuth_rad, dz_dx, dz_dy, Slope_rad, Aspect_rad;

    float z_factor = 1;


    for ( int i = 0; i < matrix.ysize; i++ )
    {
        for ( int j = 0; j < matrix.xsize; j++ )
        {
            m = j-1;
            n = i-1;
            if (j-1 == -1){
                m = matrix.xsize - 1;
            }
            if (i-1 == -1){
                n = matrix.xsize - 1;
            }

            a = matrix.tab_pixel[(i+1)%matrix.ysize][(m)%matrix.xsize].p_f;
            b = matrix.tab_pixel[(i+1)%matrix.ysize][(j)%matrix.xsize].p_f;
            c = matrix.tab_pixel[(i+1)%matrix.ysize][(j+1)%matrix.xsize].p_f;
            d = matrix.tab_pixel[(i)%matrix.ysize][(m)%matrix.xsize].p_f;
            f = matrix.tab_pixel[(i)%matrix.ysize][(j+1)%matrix.xsize].p_f;
            g = matrix.tab_pixel[(n)%matrix.ysize][(m)%matrix.xsize].p_f;
            h = matrix.tab_pixel[(n)%matrix.ysize][(j)%matrix.xsize].p_f;
            ii = matrix.tab_pixel[(n)%matrix.ysize][(j+1)%matrix.xsize].p_f;

            //cout << "start setup_value_pixel" <<endl;

            Zenith_deg = 90 - Altitude;
            Zenith_rad = Zenith_deg * M_PI / 180.0;
            Azimuth_math = 360.0 - Azimuth + 90;
            Azimuth_rad = Azimuth_math * M_PI / 180.0;
            dz_dx = ((c + 2*f + ii) - (a + 2*d + g)) / (8 * cellsize);
            dz_dy = ((g + 2*h + ii) - (a + 2*b + c)) / (8 * cellsize);
            Slope_rad = atan ( z_factor * sqrt (dz_dx*dz_dx + dz_dy*dz_dy));
            Aspect_rad = atan2 (dz_dy, -dz_dx);
            Aspect_rad = 2 * M_PI + Aspect_rad;
            matrix.tab_pixel[i][j].p_f = (cos(Zenith_rad) * cos(Slope_rad)) + (sin(Zenith_rad) * sin(Slope_rad) * cos(Azimuth_rad - Aspect_rad));
            matrix.tab_pixel[i][j].set_rgb_val();

        }
    }
}