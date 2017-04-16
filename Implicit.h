#include <Eigen/Core>

using namespace Eigen;

class Implicit
{
 public:

  virtual double f_value(Vector3f p);
  virtual Vector3f f_ngrad(Vector3f p);
};
