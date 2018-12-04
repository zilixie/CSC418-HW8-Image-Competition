#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  Eigen::Vector3d out;
  out = in - 2*(in.dot(n))*n;
  return out;
}
