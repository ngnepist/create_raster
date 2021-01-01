#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include "proj.h"
#include "point_MNT.h"
#include "matrix_image.h"
#include "pgm_io.h"
#include "ppm_io.h"

using namespace std;


int projection(vector<Point>& v_Point){
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
    for(std::size_t i = 0; i < v_Point.size(); ++i) {
        //std::cout << v[i] << "\n";

        /* a coordinate union representing Copenhagen: 55d N, 12d E    */
        /* Given that we have used proj_normalize_for_visualization(), the order of*/
        /* coordinates is longitude, latitude, and values are expressed in degrees. */
        //a = proj_coord (longi, lat, 0, 0);
        a = proj_coord (v_Point[i].p_longi, v_Point[i].p_lat, 0, 0);

        /* transform to UTM zone 32, then back to geographical */
        b = proj_trans (P, PJ_FWD, a);
        //printf ("easting: %.3f, northing: %.3f\n", b.enu.e, b.enu.n);
        //b = proj_trans (P, PJ_INV, b);
        //printf ("longitude: %g, latitude: %g\n", b.lp.lam, b.lp.phi);
        v_Point[i].p_x = b.enu.e;
        v_Point[i].p_y = b.enu.n;
        //printf ("easting: %.3f, northing: %.3f\n", v_Pixel[i].p_x, v_Pixel[i].p_y);
    }
    ///printf ("easting: %.3f, northing: %.3f\n", b.enu.e, b.enu.n);
    cout << "projecting completed" <<endl;
        /* Clean up */
    proj_destroy (P);
    proj_context_destroy (C); /* may be omitted in the single threaded case */
    return 0;

}


void setup_relatif_coordinate(vector<Point>& v_Point){

    float minElement_x = (*std::min_element(v_Point.begin(), v_Point.end(), compx)).p_x;
    float minElement_y = (*std::min_element(v_Point.begin(), v_Point.end(), compy)).p_y;

    for(std::size_t i = 0; i < v_Point.size(); ++i) {
        //std::cout << v[i] << "\n";

        v_Point[i].p_x_relatif =v_Point[i].p_x - minElement_x;
        v_Point[i].p_y_relatif = v_Point[i].p_y - minElement_y;
        //printf ("x_relatif: %.3f, y_relatif: %.3f\n", v_Pixel[i].p_x_relatif, v_Pixel[i].p_y_relatif);
    }

}


void setup_index_pixel(vector<Point>& v_Point, Matrix_image& matrix){

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
        //std::cout << v[i] << "\n";

        v_Point[i].p_i = floor(v_Point[i].p_x_relatif / peroide_x);
        v_Point[i].p_j = floor(v_Point[i].p_y_relatif / peroide_y);
        if (v_Point[i].p_j == matrix.ysize){
            v_Point[i].p_j = matrix.ysize - 1 ;
        }
        if (v_Point[i].p_i == matrix.xsize){
            v_Point[i].p_i = matrix.xsize - 1; 
        }
       // printf ("i: %.3f, j: %.3f\n", v_Pixel[i].p_i, v_Pixel[i].p_j);
    }
    cout << "setup_index_pixel completed" <<endl;

}


void setup_value_pixel(Matrix_image& matrix, vector<Point>& v_Point){

    int i, j;
    float val;
    //vector<Point> v_Point_to_print;

    float minElement_z = (*std::min_element(v_Point.begin(), v_Point.end(), compz)).p_level;
    float maxElement_z = (*std::max_element(v_Point.begin(), v_Point.end(), compz)).p_level;

    cout << "start normalisation of pixel values" <<endl;

    for(std::size_t k = 0; k < v_Point.size(); ++k) {
        //std::cout << v[i] << "\n";

        //cout << "running please wait i = "<<i<<", j = "<<j<<endl;

        //f = (v_Point[k].p_level-minElement_z)/(maxElement_z-minElement_z);
        //v_Point[k].p_level = (int) (255 * f) ;

        v_Point[k].p_level = (v_Point[k].p_level-minElement_z)/(maxElement_z-minElement_z);

    }

    cout << "normalisation of pixel values finish" <<endl;

    cout << "start setup_value_pixel" <<endl;
            
    for(std::size_t k = 0; k < v_Point.size(); ++k) {
        //std::cout << v[i] << "\n";

        //cout <<"k = "<< v_Pixel.size() - k <<endl;

        i = v_Point[k].p_i;
        j = v_Point[k].p_j;

        cout << "running please wait i = "<<i<<", j = "<<j<<endl;

        val = abs (v_Point[k].p_level);
        matrix.tab_pixel[j][i].set_val (val);

    }
    cout << "setup_value_pixel completed" <<endl;

    return;

}


//---------------Main------------------
int main(int argc, char *argv[])
{
    int xsize=800;
    int ysize=753;
    string file_name = "../doc/datalonglat.txt";
    string texte_de_fin = "la taille de l'image est ";
    vector<Point> v_Point;
    Matrix_image matrix;


    if (argc == 4){
        file_name = argv[1];
        xsize = atoi(argv[2]);
        ysize = atoi(argv[3]);
    }
    else if (argc == 3)
    {
        file_name = argv[1];
        xsize = atoi(argv[2]);
        ysize = xsize;        
    }
    else if (argc == 2)
    {
        file_name = argv[1];
        texte_de_fin = "pas de parametres de taille: donc la taille de l'image est ";
    }
    else
    {
        texte_de_fin = "pas de parametres de taille: donc la taille de l'image est ";
    }

    init_Matrix_image(matrix, xsize, ysize);
    //readdata("../doc/datalonglat.txt", v_Pixel);
    readdata(file_name, v_Point);
    projection(v_Point);
    setup_relatif_coordinate(v_Point);
    setup_index_pixel(v_Point,matrix);
    setup_value_pixel(matrix, v_Point);
    //set_shadow(matrix, 45, 315, 0.00000026);


    cout<<texte_de_fin<< xsize<<"*"<<ysize<<endl;
    //
    //generation of an ASCII file
    pgma_write ( "../doc/MNT1.PGM", matrix);
    ppma_write ( "../doc/MNT2.PPM", matrix);
    //
    //generation of an ASCII file
    pgmb_write ( "../doc/MNT3.PGM", matrix);
    ppmb_write ( "../doc/MNT4.PPM", matrix);

    //pgma_write_test ("../doc/datalonglat.PGM");
    //pgm_write_test ("../doc/datalonglat1.PGM");

    // On desalloue la memoire allouee dans la methode create_maze lors de la creation de notre Labyrinthe
    for (int i=0; i<matrix.ysize; i++)
        delete [] matrix.tab_pixel[i];
    delete [] matrix.tab_pixel;

    return EXIT_SUCCESS;
}