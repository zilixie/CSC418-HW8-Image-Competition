#include <Eigen/Core>
#include "random.h"
#include <cmath>

Eigen::Vector2d random(const Eigen::Vector3d & seed)
{
  Eigen::Vector3d v1 = Eigen::Vector3d(127.1,311.7,783.089);
  Eigen::Vector3d v2 = Eigen::Vector3d(269.5,183.3,173.542);

  Eigen::Vector2d S = Eigen::Vector2d(seed.dot(v1), seed.dot(v2));
  double x = sin(S(0))*43758.5453123;
  double y = sin(S(0))*43758.5453123;
  double output_x = x - floor(x);
  double output_y = y - floor(y);
  Eigen::Vector2d out = Eigen::Vector2d(output_x, output_y);
  return out;
}
