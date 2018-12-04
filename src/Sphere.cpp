#include "Sphere.h"
#include "Ray.h"
#include <Eigen/Geometry>

bool Sphere::intersect(
        const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d c_minus_e = this->center - ray.origin;
  Eigen::Vector3d c = this->center;

  double r = this->radius;
  double k_sq = pow(r, 2) - (c_minus_e).dot(c_minus_e) + pow((c_minus_e.dot(d))/(d.norm()), 2);
  double k = 0;

  if (k_sq > 0) {
    k = sqrt(k_sq);
  }
  else {
    return false;
  }

  Eigen::Vector3d intersection1 = ray.origin + d*(((c_minus_e).dot(d))/(d.norm()) - k)/d.norm();
  Eigen::Vector3d intersection2 = ray.origin + d*(((c_minus_e).dot(d))/(d.norm()) + k)/d.norm();

  double t1 = (((c_minus_e).dot(d))/(d.norm()) - k)/d.norm();
  double t2 = (((c_minus_e).dot(d))/(d.norm()) + k)/d.norm();

  t = t1;
  if (t < min_t) {
    return false;
  }
  if (t==std::numeric_limits<double>::infinity()) {
    return false;
  }
  if (isnan(t)) {
    return false;
  }

  Eigen::Vector3d c_intersection1 = intersection1 - ray.origin - c_minus_e;
  Eigen::Vector3d normal = c_intersection1/c_intersection1.norm();
  n = normal;
  return true;
}

