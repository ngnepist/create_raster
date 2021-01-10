#include "pixel.h"
#include <iostream>
#include <math.h>

using namespace std;

//****************************************************************************

Pixel::Pixel()
/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    defaut constructor of the pixel\n
*\ \n
*\  Author:\n
*\ \n
*\    stephane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Parameters:\n
*\ \n
*\    No parameter\n
*\ \n
*/
{
  p_val = 0;
}

//****************************************************************************

Pixel::~Pixel()

/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    desconstroctor of the pixel\n
*\ \n
*\  Author:\n
*\ \n
*\    stephane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Parameters:\n
*\ \n
*\    No parameter\n
*\ \n
*/
{
  // Nothing to destroy.
}

//****************************************************************************

void Pixel::set_val(float val)

/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    Set the value of the pixel, this value helps for the choice of the color or the level of gray\n
*\ \n
*\  Author:\n
*\ \n
*\    stephane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Parameters:\n
*\ \n
*\    Input, float val, the value of the value of the pixel depending of the altitude of the point corresponding \n
*\ \n
*/
{
  p_f = (p_nb_point * p_f + abs(val))/(p_nb_point + 1);
  p_val = (unsigned int)(floor(255*p_f));
  set_rgb_val();
}

//****************************************************************************

void Pixel::set_rgb_val()
/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    Set the color of the pixel using "short rainbow RGB" scale for conversion\n
*\ \n
*\  Author:\n
*\ \n
*\    stephane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Parameters:\n
*\ \n
*\    No parameter\n
*\ \n
*/
{
    /*plot short rainbow RGB*/
  float a=(p_f)/0.25; //invert and group
  unsigned int  X=floor(a);  //this is the integer part
  unsigned int  Y=floor(255*(a-X)); //fractional part from 0 to 255
  switch(X)
  {
    case 0: p_r=255;p_g=Y;p_b=0;break;
    case 1: p_r=255-Y;p_g=255;p_b=0;break;
    case 2: p_r=0;p_g=255;p_b=Y;break;
    case 3: p_r=0;p_g=255-Y;p_b=255;break;
    case 4: p_r=0;p_g=0;p_b=255;break;
  }
}
