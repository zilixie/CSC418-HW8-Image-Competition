#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
        const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  t = 0;
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d n_ = this->normal;

  Eigen::Vector3d p = this->point;
  Eigen::Vector3d a = p - e;

  double product = ((-1) * n_).dot(a);
  double cos_theta = product/(a.norm()*n_.norm());

  Eigen::Vector3d h = cos_theta * a.norm() * (-1) * n_;

  double cos_beta = d.dot(h)/(d.norm() * h.norm());
  double t_ = (h.norm()/cos_beta)/d.norm();
  t = t_;
  n = n_;

  if (t==std::numeric_limits<double>::infinity()) {
    return false;
  }
  if ((t < min_t) || (isnan(t))){
    return false;
  }
  return true;

}

