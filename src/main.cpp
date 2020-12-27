#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include "proj.h"
#include "pixel.h"
#include "pgma_io.h"

using namespace std;

struct Matrix_image {
     int *garray;
     int xsize;
     int ysize;
};


void readdata(const string& file_name, vector<Pixel>& v_Pixel)
{

    ifstream f(file_name);

    if(!f.is_open())
       cout << "Sorry! Open file failed." << endl;

    cout << "start reading" <<endl;
    while(!f.eof()) // eof: end of file
    { 
        Pixel *p = new Pixel(0,0,0);
        f >> *p;  // lecture du pixel

        if(f.eof()) // if end of file reached at this position...
        {
          delete p;
          break; // ...the reading is finish
        }
        v_Pixel.push_back(*p);
        //cout << p->p_lat << endl;
        //cout << p->p_longi << endl;
    }
    f.close();
    cout << "reading completed" <<endl;
}

int projection(vector<Pixel>& v_Pixel)
{
    /*les variables pour la projection*/
    PJ_CONTEXT *C;
    PJ *P;
    PJ* P_for_GIS;
    PJ_COORD a, b;

    /**
    *\ Methode principale, le main
    */

    C = proj_context_create();
    P = proj_create_crs_to_crs (C,
                            "EPSG:4326",
                            "+proj=utm +zone=30 +datum=WGS84", /* or EPSG:32632 */
                            NULL);

    if (0==P) {
        fprintf(stderr, "Oops P has a problem\n");
        return 1;
    }
        
    P_for_GIS = proj_normalize_for_visualization(C, P);
    if( 0 == P_for_GIS )  {
        fprintf(stderr, "Oops P_for_GIS has a problem\n");
        return 1;
    }
    proj_destroy(P);
    P = P_for_GIS;

    cout << "start projecting" <<endl;
    for(std::size_t i = 0; i < v_Pixel.size(); ++i) {
        //std::cout << v[i] << "\n";

        /* a coordinate union representing Copenhagen: 55d N, 12d E    */
        /* Given that we have used proj_normalize_for_visualization(), the order of*/
        /* coordinates is longitude, latitude, and values are expressed in degrees. */
        //a = proj_coord (longi, lat, 0, 0);
        a = proj_coord (v_Pixel[i].p_longi, v_Pixel[i].p_lat, 0, 0);

        /* transform to UTM zone 32, then back to geographical */
        b = proj_trans (P, PJ_FWD, a);
        //printf ("easting: %.3f, northing: %.3f\n", b.enu.e, b.enu.n);
        //b = proj_trans (P, PJ_INV, b);
        //printf ("longitude: %g, latitude: %g\n", b.lp.lam, b.lp.phi);
        v_Pixel[i].p_x = b.enu.e;
        v_Pixel[i].p_y = b.enu.n;
        //printf ("easting: %.3f, northing: %.3f\n", v_Pixel[i].p_x, v_Pixel[i].p_y);
    }
    cout << "projecting completed" <<endl;
        /* Clean up */
    proj_destroy (P);
    proj_context_destroy (C); /* may be omitted in the single threaded case */
    return 0;

}

bool compx(const Pixel& p1, const Pixel& p2){
    return p1.p_x<p2.p_x;
}

bool compy(const Pixel& p1, const Pixel& p2){
    return p1.p_y<p2.p_y;
}

double round(double value) {
     return floor(value + 0.5);
}

void setup_index_pixel(vector<Pixel>& v_Pixel, int xsize, int ysize){

    float minElement_x = (*std::min_element(v_Pixel.begin(), v_Pixel.end(), compx)).p_x;
    float maxElement_x = (*std::max_element(v_Pixel.begin(), v_Pixel.end(), compx)).p_x;
    float minElement_y = (*std::min_element(v_Pixel.begin(), v_Pixel.end(), compy)).p_y;
    float maxElement_y = (*std::max_element(v_Pixel.begin(), v_Pixel.end(), compy)).p_y;

    cout << "start setup_index_pixel" <<endl;
    for(std::size_t i = 0; i < v_Pixel.size(); ++i) {
        //std::cout << v[i] << "\n";

        v_Pixel[i].p_i =(int) (round((xsize - 0)*(v_Pixel[i].p_x - minElement_x)/(maxElement_x - minElement_x)));
        v_Pixel[i].p_j = (int) (round((ysize - 0)*(v_Pixel[i].p_y - minElement_y)/(maxElement_y - minElement_y)));
        printf ("i: %.3f, j: %.3f\n", v_Pixel[i].p_i, v_Pixel[i].p_j);
    }
    cout << "setup_index_pixel completed" <<endl;

}

void setup_value_pixel(Matrix_image& matrix, vector<Pixel>& v_Pixel){
    int i;
    int *indexg;
    int j;
    float S;
    vector<Pixel> v_Pixel_to_print;

    indexg = matrix.garray;


    cout << "start setup_value_pixel" <<endl;
    for ( j = 0; j < matrix.ysize; j++ )
    {
        for ( i = 0; i < matrix.xsize; i++ )
        {
            cout << "running please wait i = "<<i<<", j = "<<j<<endl;
            for(std::size_t k = 0; k < v_Pixel.size(); ++k) 
            {
                //std::cout << v[i] << "\n";
                if (v_Pixel[k].p_i == i && v_Pixel[k].p_j == j){
                    v_Pixel_to_print.push_back(v_Pixel[k]);
                }
            }

            if ((unsigned) (v_Pixel_to_print.size()) >= 1)
            {

                for(std::size_t k = 0; k < v_Pixel_to_print.size(); ++k) 
                {
                    //std::cout << v[i] << "\n";
                    S += v_Pixel_to_print[k].p_level;
                }
                S = S/(v_Pixel_to_print.size());

                *indexg = ( int ) (round(abs(S)));
 
                indexg = indexg + 1;
            }
            vector<Pixel>().swap(v_Pixel_to_print);
            S=0;
        }
    }
    cout << "setup_value_pixel completed" <<endl;

  return;
}

void init_Matrix_image(Matrix_image& matrix, int xsize, int ysize){
    int i;
    int *indexg;
    int j;

    matrix.garray = new int[xsize * ysize];
    matrix.xsize = xsize;
    matrix.ysize = ysize;

    indexg = matrix.garray;

    cout << "init_Matrix_image starting" <<endl;
    for ( i = 0; i < matrix.ysize; i++ )
    {
        for ( j = 0; j < matrix.xsize; j++ )
        {

            *indexg = 0;
 
            indexg = indexg + 1;
        }
    }
    cout << "init_Matrix_image completed" <<endl;
}



//---------------Main------------------
int main()
{
    int xsize=800;
    int ysize=753;
    vector<Pixel> v_Pixel;
    Matrix_image matrix;
    init_Matrix_image(matrix, xsize, ysize);
    readdata("../doc/datalonglat.txt", v_Pixel);
    projection(v_Pixel);
    setup_index_pixel(v_Pixel,matrix.xsize, matrix.ysize);
    setup_value_pixel(matrix, v_Pixel);


    cout<<"les choses peuvent donc commencer"<<endl;
    pgma_write ( "../doc/MNT.PGM", matrix.xsize, matrix.ysize, matrix.garray );

    //pgma_write_test ("../doc/datalonglat.PGM");
    delete [] matrix.garray;
    return EXIT_SUCCESS;
}