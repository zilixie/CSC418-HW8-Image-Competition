#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include "perlin_noise.h"

bool raycolor(
  const Ray & ray,
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  int hit_id;
  double t;
  Eigen::Vector3d n;
  bool find_hit = first_hit(ray,min_t,objects,hit_id,t,n);
  if (find_hit) {
    rgb = blinn_phong_shading(ray,hit_id,t,n,objects,lights);

    if (num_recursive_calls < 3) {
      Eigen::Vector3d km = objects[hit_id]->material->km;
      Eigen::Vector3d in = ray.direction/(ray.direction).norm();
      Eigen::Vector3d out = reflect(in, n);
      Eigen::Vector3d queue_point = ray.origin + t * ray.direction;

      Ray reflect_ray;
      reflect_ray.origin = queue_point;
      reflect_ray.direction = out/out.norm();

      Eigen::Vector3d color (0,0,0);
      raycolor(reflect_ray, min_t/1000000, objects, lights, num_recursive_calls + 1, color);
      rgb = rgb + (color.array() * km.array()).matrix();
    }
    return true;
  }
  return false;

}
