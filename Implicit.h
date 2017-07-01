#pragma once

#include <Eigen/Core>

using namespace Eigen;

class Implicit {

 public:

  virtual double f_value(Vector3d p) = 0;
  virtual Vector3d f_ngrad(Vector3d p) = 0;
};
