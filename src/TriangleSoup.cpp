#include "TriangleSoup.h"
#include "Ray.h"
// Hint
#include "first_hit.h"

bool TriangleSoup::intersect(
        const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  std::vector<std::shared_ptr<Object> > soup = this->triangles;
  int hit_id;
  if(first_hit(ray,min_t,soup,hit_id,t,n)) {
    return true;
  }

  return false;
}



