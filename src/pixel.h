#ifndef __PIXEL_H__
#define __PIXEL_H__

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <cstdlib>

//****************************************************************************

class Pixel

/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    Class pixel, descripte the parameters of a pixel and it works\n
*\ \n
*\  Author:\n
*\ \n
*\    Stephane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Class variables:\n
*\ \n
*\    Element1, unsigned int p_val, is the value of the pixel, using for calculate gray scale color.\n
*\ \n
*\    Element2, float p_f, a number important for the calculation of RGB color.\n
*\ \n
*\    Element3, unsigned int p_r, p_g, p_b, RGB values for the setup of color.\n
*\ \n
*\    Element4, int p_nb_point, number of point which contribute to the calculation of the value of the pixel, we use it for the barycenter\n
*\ \n
*/
{
  public:
  	    Pixel();
        ~Pixel();
        void set_val(float val); 	//    Set the value of the pixel, this value helps for the choice of the color or the level of gray
        void set_rgb_val();			//    Set the color of the pixel using "short rainbow RGB" scale for conversion

        float p_f =0; 
       	unsigned int p_val = 0;
       	unsigned int p_r = 0, p_g = 0, p_b = 0 ;
       	int p_nb_point = 0;
};
#endif