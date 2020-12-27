#include "pixel.h"
#include <iostream>

using namespace std;
Pixel::Pixel(float lat, float longi,float level) : p_lat(lat), p_longi(longi), p_level(level)
{

}

Pixel::~Pixel()
{
  // Nothing to destroy.
}
istream& operator>>(std::istream& stream, Pixel& p)
{
  string s;
  // We use getline() with some custom delimiters
  getline(stream, s) >> p.p_lat;
  cout << s <<endl;
  getline(stream, s, ' ') >> p.p_longi;
  cout << s <<endl;
  getline(stream, s, ' ') >> p.p_level;
  cout << s <<endl;
  return stream; 
}