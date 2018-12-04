#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  Eigen::Vector3d light = this->p;
  Eigen::Vector3d point_to_light = light - q;
  d = point_to_light/(point_to_light.norm());
  max_t = point_to_light.norm();
}
