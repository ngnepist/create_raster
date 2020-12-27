#ifndef __PIXEL_H__
#define __PIXEL_H__

#include <cstdlib>
#include <fstream>
class Pixel
{
  public:
  	    Pixel(float east, float north,float level);
        ~Pixel();

        friend std::istream& operator>>(std::istream& stream, Pixel& p);
        float p_lat,p_longi,p_x,p_y,p_i,p_j,p_level;
};
#endif