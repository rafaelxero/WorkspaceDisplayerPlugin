/**
   @author Rafael Cisneros
*/

#include "Polygonizer.h"

Polygonizer::Polygonizer()
{
  ll = Vector3f(-3.0, -3.0, 0.0);
  ur = Vector3f( 3.0,  3.0, 8.0);
  nx = 8; ny = 8; nz = 8;

  std::cout << "Working" << std::endl;
}
