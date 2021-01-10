#ifndef __POINT_MNT_H__
#define __POINT_MNT_H__

#include <cstdlib>
#include <fstream>

//****************************************************************************

class Point
/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    Class point, descripte the parameters of a point and it works\n
*\ \n
*\  Author:\n
*\ \n
*\    Stephane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Class variables:\n
*\ \n
*\    Element1, float p_lat,p_longi, p_level, is the lattitude and the longitude and the level of the point.\n
*\ \n
*\    Element2, float p_x,p_y, is the projected coordinate of the point.\n
*\ \n
*\    Element3, float p_x_relatif, p_y_relatif, the relatif coordinate the point.\n
*\ \n
*\    Element4, float p_i, p_j, is the index of the pixel associated for this point. in the image, this point will be represent by the pixel at the position p_i, p_j\n
*\ \n
*/
{
  public:
  	    Point(float east, float north,float level);
        ~Point();

        friend std::istream& operator>>(std::istream& stream, Point& p);
        float p_lat,p_longi,p_x,p_y,p_x_relatif, p_y_relatif,p_i,p_j,p_level;
};
#endif