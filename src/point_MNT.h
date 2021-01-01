#ifndef __POINT_MNT_H__
#define __POINT_MNT_H__

#include <cstdlib>
#include <fstream>
class Point
{
  public:
  	    Point(float east, float north,float level);
        ~Point();

        friend std::istream& operator>>(std::istream& stream, Point& p);
        float p_lat,p_longi,p_x,p_y,p_x_relatif, p_y_relatif,p_i,p_j,p_level;
};
#endif