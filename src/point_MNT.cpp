#include "point_MNT.h"
#include <iostream>

using namespace std;

//****************************************************************************

Point::Point(float lat, float longi,float level) : p_lat(lat), p_longi(longi), p_level(level)
{
/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    defaut constructor of a point of the MNT knowing the lattitude, the longitude and the level \n
*\ \n
*\  Author:\n
*\ \n
*\    stephane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Parameters:\n
*\ \n
*\    Input, float lat, the lattitude of the point\n
*\ \n
*\   Input, float longi, the longitude of the point \n
*\ \n
*\    Input, float level, the altitude of the point \n
*\ \n
*/

}

//****************************************************************************

Point::~Point(){

/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    desconstroctor of the point\n
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
  // Nothing to destroy.
}

//****************************************************************************

istream& operator>>(std::istream& stream, Point& p){

/** \n
*\****************************************************************************\n
*\ \n
*\  Purpose:\n
*\ \n
*\    surcharge de l'operateur de lecture\n
*\ \n
*\  Author:\n
*\ \n
*\    stephane NGNEPIEPAYE WEMBE\n
*\ \n
*\  Parameters:\n
*\ \n
*\    Input, std::istream& stream, a pointer to the file.\n
*\    \n
*\    Input, Point& p, point which will containt the reading data.\n
*\ \n

*/
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