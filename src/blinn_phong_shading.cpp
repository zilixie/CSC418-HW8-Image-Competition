#include "blinn_phong_shading.h"
// Hint:
#include "random_direction.h"
#include "perlin_noise.h"
#include "first_hit.h"
#include <iostream>
#include <algorithm>


Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id,
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  Eigen::Matrix3d mb;
  mb << 0.04, 0, 0,
       0, 0.04, 0,
       0, 0, 0.04;
  Eigen::Matrix3d ms;
  ms << 0.2, 0, 0,
          0, 0.2, 0,
          0, 0, 0.2;
  Eigen::Matrix3d mt;
  mt << 0.03, 0, 0,
          0, 0.03, 0,
          0, 0, 0.03;
  Eigen::Matrix3d mp;
  mp << 0.03, 0, 0,
          0, 0.03, 0,
          0, 0, 0.03;

  Eigen::Vector3d query_point = ray.origin + t * ray.direction;
  double background_noise = perlin_noise(mb * query_point);
  double sphere_noise = perlin_noise(ms * query_point);
  double table_noise = perlin_noise(mt * query_point);
  double pink_noise = perlin_noise(mp * query_point);

  Eigen::Vector3d direction_query_point_to_light;

  double parametric_distance_t;
  Eigen::Vector3d L = Eigen::Vector3d(0,0,0);
  Eigen::Vector3d L_shadow = Eigen::Vector3d(0,0,0);
  Eigen::Vector3d ka = objects[hit_id]->material->ka;

  for (int j=0; j<lights.size(); j++) {
    Eigen::Vector3d i = lights[j]->I;
    lights[j]->direction(query_point, direction_query_point_to_light, parametric_distance_t);

    Eigen::Vector3d l = direction_query_point_to_light;

    Eigen::Vector3d v = (-1) * ray.direction/(ray.direction).norm();
    Eigen::Vector3d h = (v + l) / ((v + l).norm());

    Eigen::Vector3d kd = objects[hit_id]->material->kd;
    Eigen::Vector3d ks = objects[hit_id]->material->ks;

    double exp = objects[hit_id]->material->phong_exponent;
    if (hit_id == 1) {
      if (background_noise > 0.1) {
        kd = Eigen::Vector3d(0.65, 0.41, 0.16);
      }
      else {
        kd = Eigen::Vector3d(0.1, 0.1, 0.1);
      }
    }
    if (hit_id == 2) {
      if (background_noise > 0.1) {
        kd = Eigen::Vector3d(0.68, 0.85, 0.9);
      }
      else {
        kd = Eigen::Vector3d(0.37, 0.62, 0.63);
      }
    }

    if (hit_id == 5) {
      if (sphere_noise > 0.1) {
        kd = Eigen::Vector3d(0.68,1,0.18);
      }
      else {
        kd = kd;
      }
    }

    if (hit_id == 0) {
      if (((table_noise > -0.34) && (table_noise < -0.31)) ||
         ((table_noise > -0.28) && (table_noise < -0.25)) ||
         ((table_noise > -0.22) && (table_noise < -0.19)) ||
         ((table_noise > -0.16) && (table_noise < -0.13)) ||
         ((table_noise > -0.10) && (table_noise < -0.07)) ||
         ((table_noise > -0.04) && (table_noise < -0.01)) ||
         ((table_noise > 0.02) && (table_noise < 0.05)) ||
         ((table_noise > 0.08) && (table_noise < 0.11)) ||
         ((table_noise >= 0.14) && (table_noise < 0.17)) ||
         ((table_noise >= 0.20) && (table_noise < 0.23)))
         {
        kd = Eigen::Vector3d(0.3,0.3,0.3);
      }
      else {
        kd = kd;
      }
    }
    if (hit_id == 3) {
      if ((pink_noise > 0) && (pink_noise < 0.05)) {
        kd = Eigen::Vector3d(1.0,0.71,0.85);
      }
      else {
        kd = kd;
      }
    }

    Eigen::Vector3d diffuse = fmax(0, n.dot(l)) * (i.array() * kd.array()).matrix();
    Eigen::Vector3d specular = pow(fmax(0, n.dot(h)), exp) * (i.array() * ks.array()).matrix();

    Ray shadow_ray;
    int shadow_hit_id;
    double shadow_t;
    Eigen::Vector3d shadow_n;
    shadow_ray.origin = query_point;
    shadow_ray.direction = l;

    bool this_light_shadow_hit = first_hit(shadow_ray, 0.000001, objects, shadow_hit_id, shadow_t,shadow_n);

    if ((shadow_t < parametric_distance_t) && this_light_shadow_hit) {
      L = L + L_shadow;
    }
    else {
      L = L + diffuse + specular;
    }
  }
  return L + ka;
}
