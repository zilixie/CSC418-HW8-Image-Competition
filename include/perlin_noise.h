#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include <vector>
#include <string>
#include <Eigen/Core>

double perlin_noise(
  const Eigen::Vector3d & seed);

#endif
