#include <Eigen/Core>
#include "random_direction.h"
#include "random.h"
#include <math.h>

Eigen::Vector3d random_direction(const Eigen::Vector3d & seed)
{
  const double pi = std::acos(-1);
  Eigen::Vector2d uv = random(seed);
  double theta = uv(0) * 2 * pi;
  double r =0;
  if (uv(1)>0.5) {
    r = (uv(1) - 1) * 2;
  }
  if (uv(1)<0.5) {
    r = (uv(1) * 2) - 1;
  }
  if (uv(1)==0.5) {
    r = 0;
  }
  double x = sqrt(1 - r*r) * cos(theta);
  double y = sqrt(1 - r*r) * sin(theta);
  double z = r;
  return Eigen::Vector3d(x,y,z);
}
