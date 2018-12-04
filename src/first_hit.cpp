#include "first_hit.h"
#include <algorithm>
#include <vector>
#include <limits>
#include "perlin_noise.h"

bool first_hit(
        const Ray & ray,
        const double min_t,
        const std::vector< std::shared_ptr<Object> > & objects,
        int & hit_id,
        double & t,
        Eigen::Vector3d & n)
{
    int hit_id_list [(int) objects.size()];
    double t_list [(int) objects.size()];
    Eigen::Vector3d normal_list [(int) objects.size()];
    Eigen::Vector3d normal;

    const int N = sizeof(t_list) / sizeof(double);

    for (int i=0; i<objects.size(); i++) {
        hit_id_list[i] = 0;
        t_list[i] = std::numeric_limits<double>::max();
    }

    bool intersect = false;
    for (int i=0; i<objects.size(); i++) {
        if (objects[i]->intersect(ray, min_t, t, n)) {

            intersect = true;
            normal = n;
            normal_list[i] = normal;
            hit_id_list[i] = i;
            t_list[i] = t;
        }
    }

    double min = *std::min_element(t_list, t_list + N);
    long index = std::distance(t_list, std::min_element(t_list, t_list + N));

    hit_id = hit_id_list[index];
    t = min;
    n = normal_list[index];

    if (intersect) {
        return true;
    }
    else {
        return false;
    }
}

