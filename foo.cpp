/*
 * Compile with:
 * g++ -o foo foo.cpp Polygonizer.cpp -I/usr/include/eigen3
 *
 */

#include "Polygonizer.h"

class impl : public Implicit {

  double f_value(Vector3d p) {return 0.0;}
  Vector3d f_ngrad(Vector3d p) {return Vector3d(0.0, 0.0, 0.0);}
};

int main() {

  impl f;
  Polygonizer a(&f);
  return 0;
}
