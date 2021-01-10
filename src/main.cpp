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

//****************************************************************************\n

int projection(vector<Point>& v_Point)
/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    Use an official projection tool (UTM30) to project all points of the MNT \n
*\ \n
*\  example\n
*\ \n
*\    a coordinate union representing Copenhagen: 55d N, 12d E \n
*\    Give 285015.76325880236 East, 5542944.018361305 North in UTM30\n
*\ \n
*\  Author:\n
*\ \n
*\    Stephane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Parameters:\n
*\ \n
*\    Input, vector<Point>& v_Point, the vector of all points of the MNT.\n
*\ \n
*/ 
{  /*les variables pour la projection*/
    PJ_CONTEXT *C;
    PJ *P;
    PJ* P_for_GIS;
    PJ_COORD a, b;


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

		//the order of coordinates is longitude, latitude, and values are expressed in degrees. */
        a = proj_coord (v_Point[i].p_longi, v_Point[i].p_lat, 0, 0);

        /* transform to UTM zone 30 */
        b = proj_trans (P, PJ_FWD, a);

        v_Point[i].p_x = b.enu.e;
        v_Point[i].p_y = b.enu.n;

    }
    cout << "projecting completed" <<endl;
        /* Clean up */
    proj_destroy (P);
    proj_context_destroy (C); /* may be omitted in the single threaded case */
    return 0;
}

//****************************************************************************

void setup_relatif_coordinate(vector<Point>& v_Point, const int& xsize, int& ysize)

/** \n
*\**************************************************************************** \n
*\ \n
*\  Purpose: \n
*\ \n
*\    Set up relatifs coordinates of all points. whe search the minimal square which containt all points \n
*\	  In the same time we calculate numbers of pixels (width, height) that we will use to represent the image,  \n
*\ \n
*\    we know the whith = xsize   ==>   resolution = xsize/amplitude_of_x \n
*\    we find 	height  = ysize = resolution * amplitude_of_y \n
*\ \n
*\  Author: \n
*\  \n
*\    Stephane NGNEPIEPAYE WEMBE \n
*\ \n
*\  Parameters: \n
*\ \n
*\    Input, vector<Point>& v_Point, the vector of all points of the MNT. \n
*\	  Input, const int& xsize, the whith of the image \n
*\	  Input, int& ysize, the height of the image \n
*\ \n
*/ 
{

    float minElement_x = (*std::min_element(v_Point.begin(), v_Point.end(), compx)).p_x;
    float maxElement_x = (*std::max_element(v_Point.begin(), v_Point.end(), compx)).p_x;
    float minElement_y = (*std::min_element(v_Point.begin(), v_Point.end(), compy)).p_y;
    float maxElement_y = (*std::max_element(v_Point.begin(), v_Point.end(), compy)).p_y;

    float amplitude_valeur_x = maxElement_x - minElement_x;
    float amplitude_valeur_y = maxElement_y - minElement_y;

    float resolution = xsize/amplitude_valeur_x;
    ysize = resolution * amplitude_valeur_y;

    cout << "start setup_relatif_coordinate" <<endl;
    for(std::size_t i = 0; i < v_Point.size(); ++i) {

        v_Point[i].p_x_relatif =v_Point[i].p_x - minElement_x;
        v_Point[i].p_y_relatif = v_Point[i].p_y - minElement_y;
    }
    cout << "setup_relatif_coordinate completed" <<endl;
}



//----------------------------------- Main -----------------------------------

int main(int argc, char *argv[])
{
    int xsize=800;  // defaut value of the whidth
    int ysize=0;
    string file_name = "../doc/datalonglat.txt"; // defaut localisation of data file
    string texte_de_fin = "la taille de l'image est ";
    vector<Point> v_Point;
    Matrix_image matrix;

    //  Extraction of entering parameter : name of data file and the whidth of the image to setup
	if (argc == 3)
    {
        file_name = argv[1];
        xsize = atoi(argv[2]);       
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


    readdata(file_name, v_Point);
    projection(v_Point);
    setup_relatif_coordinate(v_Point, xsize, ysize);
    init_Matrix_image(matrix, xsize, ysize);
    setup_index_pixel(v_Point,matrix);
    setup_value_pixel(matrix, v_Point);
    //set_shadow(matrix, 45, 315, 0.00000026);  //mise en l'ombrage


    cout<<texte_de_fin<< xsize<<"*"<<ysize<<endl;
    //
    //generation of an ASCII file
    pgma_write ( "../doc/MNT_ASCII.PGM", matrix);
    ppma_write ( "../doc/MNT_ASCII.PPM", matrix);
    //
    //generation of an ASCII file
    pgmb_write ( "../doc/MNT_BINAIRE.PGM", matrix);
    ppmb_write ( "../doc/MNT_BINAIRE.PPM", matrix);

    // On desalloue la memoire allouee dans la methode create_maze lors de la creation de notre Labyrinthe
    for (int i=0; i<matrix.ysize; i++)
        delete [] matrix.tab_pixel[i];
    delete [] matrix.tab_pixel;

    return EXIT_SUCCESS;
}