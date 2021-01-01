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



bool compx(const Point& p1, const Point& p2){
    return p1.p_x<p2.p_x;
}

bool compy(const Point& p1, const Point& p2){
    return p1.p_y<p2.p_y;
}

bool compz(const Point& p1, const Point& p2){
    return p1.p_level < p2.p_level;
}

void readdata(const string& file_name, vector<Point>& v_Point){

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

void init_Matrix_image(Matrix_image& matrix, int xsize, int ysize){
   // int i;

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

void set_shadow(Matrix_image& matrix, float Altitude, float Azimuth, float cellsize){


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