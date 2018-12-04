#include "viewing_ray.h"

void viewing_ray(
        const Camera & camera,
        const int i,
        const int j,
        const int width,
        const int height,
        Ray & ray)
{
    double l = -camera.width/2;
    double r = camera.width/2;
    double b = -camera.height/2;
    double t = camera.height/2;

    double u = l + (j + 0.5)*(r - l)/width;
    double v = t - (i + 0.5)*(t - b)/height;
    ray.origin = camera.e;
    ray.direction =  - camera.d*camera.w + u*camera.u + v*camera.v;
}

