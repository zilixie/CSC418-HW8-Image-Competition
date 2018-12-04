#include "Triangle.h"
#include "Ray.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <vector>

Eigen::Vector3d cross_product(double *v1, double *v2)
{
  Eigen::Vector3d cross;
  cross.x()= (v1[1]*v2[2])-(v1[2]*v2[1]);
  cross.y() = (v1[2]*v2[0])-(v1[0]*v2[2]);
  cross.z() = (v1[0]*v2[1])-(v1[1]*v2[0]);
  return cross;
}

bool Triangle::intersect(
        const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d p0 = std::get<0>(this->corners);
  Eigen::Vector3d p1 = std::get<1>(this->corners);
  Eigen::Vector3d p2 = std::get<2>(this->corners);

  Eigen::Vector3d e_to_p0 = p0 - e;
  Eigen::Vector3d e_to_p1 = p1 - e;
  Eigen::Vector3d e_to_p2 = p2 - e;

  double aa = e_to_p0.x();
  double dd = e_to_p1.x();
  double gg = e_to_p2.x();
  double jj = d.x();

  double bb = e_to_p0.y();
  double ee = e_to_p1.y();
  double hh = e_to_p2.y();
  double kk = d.y();

  double cc = e_to_p0.z();
  double ff = e_to_p1.z();
  double ii = e_to_p2.z();
  double ll = d.z();

  // check if point in triangle
  int num =3;
  std::vector<double> x(num);
  //x = row_reduce(A, A.size());

  double M = aa*(ee*ii-hh*ff)+bb*(gg*ff-dd*ii)+cc*(dd*hh-ee*gg);
  x[0] = (jj*(ee*ii-hh*ff)+kk*(gg*ff-dd*ii)+ll*(dd*hh-ee*gg))/M;
  x[1] = (ii*(aa*kk-jj*bb)+hh*(jj*cc-aa*ll)+gg*(bb*ll-kk*cc))/M;
  x[2] = (-1)*(ff*(aa*kk-jj*bb)+ee*(jj*cc-aa*ll)+dd*(bb*ll-kk*cc))/M;

  //find the point
  double vector1[3];
  double vector2[3];

  vector1[0] = p1.x() - p0.x();
  vector1[1] = p1.y() - p0.y();
  vector1[2] = p1.z() - p0.z();

  vector2[0] = p2.x() - p0.x();
  vector2[1] = p2.y() - p0.y();
  vector2[2] = p2.z() - p0.z();

  Eigen::Vector3d normal = cross_product(vector1, vector2);

  for (int i=0; i<num; i++) {
    if (x[i] < 0) {
      return false;
    }
  }

  if (normal.dot(d) < 0) {
    n = normal/normal.norm();
  }
  else {
    n = -normal/normal.norm();
  }

  double cos_theta = abs(d.dot(n)/(d.norm()*n.norm()));
  double distance = abs(n.dot(e_to_p0));
  t = (distance/cos_theta)/d.norm();

  if (t < min_t) {
    return false;
  }
  return true;
}
