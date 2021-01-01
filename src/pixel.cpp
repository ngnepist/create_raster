#include "pixel.h"
#include <iostream>
#include <math.h>

using namespace std;

Pixel::Pixel()
{
  p_val = 0;
}

Pixel::~Pixel()
{
  // Nothing to destroy.
}

void Pixel::set_val(float val){

  p_f = (p_nb_point * p_f + abs(val))/(p_nb_point + 1);
  p_val = (unsigned int)(floor(255*p_f));
  set_rgb_val();

  
}

void Pixel::set_rgb_val(){
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

/*
double round(double value) {
     return floor(value + 0.5);
}
*/
