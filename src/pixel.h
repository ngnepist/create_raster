#ifndef __PIXEL_H__
#define __PIXEL_H__

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <cstdlib>
class Pixel
{
  public:
  	    Pixel();
        ~Pixel();
        void set_val(float val); 
        void set_rgb_val();

        float p_f =0; 
       	unsigned int p_val = 0;
       	unsigned int p_r = 0, p_g = 0, p_b = 0 ;
       	int p_nb_point = 0;
};
//double round(double value);
#endif