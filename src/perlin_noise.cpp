#include <Eigen/Core>
#include "perlin_noise.h"
#include "random_direction.h"


double smooth_step(const double & f) {
  double y = (-2) * pow(f, 3) + 3* pow(f,2);
  return y;
}

double mix(const double & x, const double & y, const double & a) {
  double m = x*(1-a) + y*a;
  return m;
}

double perlin_noise(const Eigen::Vector3d & st)
{
  Eigen::Vector3d a = Eigen::Vector3d(floor(st(0)), floor(st(1)), floor(st(2)));
  Eigen::Vector3d b = Eigen::Vector3d(ceil(st(0)), floor(st(1)), floor(st(2)));
  Eigen::Vector3d c = Eigen::Vector3d(ceil(st(0)), ceil(st(1)), floor(st(2)));
  Eigen::Vector3d d = Eigen::Vector3d(floor(st(0)), ceil(st(1)), floor(st(2)));
  Eigen::Vector3d e = Eigen::Vector3d(floor(st(0)), floor(st(1)), ceil(st(2)));
  Eigen::Vector3d f = Eigen::Vector3d(ceil(st(0)), floor(st(1)), ceil(st(2)));
  Eigen::Vector3d g = Eigen::Vector3d(ceil(st(0)), ceil(st(1)), ceil(st(2)));
  Eigen::Vector3d h = Eigen::Vector3d(floor(st(0)), ceil(st(1)), ceil(st(2)));

  Eigen::Vector3d a_dir = random_direction(a);
  Eigen::Vector3d b_dir = random_direction(b);
  Eigen::Vector3d c_dir = random_direction(c);
  Eigen::Vector3d d_dir = random_direction(d);
  Eigen::Vector3d e_dir = random_direction(e);
  Eigen::Vector3d f_dir = random_direction(f);
  Eigen::Vector3d g_dir = random_direction(g);
  Eigen::Vector3d h_dir = random_direction(h);

  Eigen::Vector3d a_seed = st - a;
  Eigen::Vector3d b_seed = st - b;
  Eigen::Vector3d c_seed = st - c;
  Eigen::Vector3d d_seed = st - d;
  Eigen::Vector3d e_seed = st - e;
  Eigen::Vector3d f_seed = st - f;
  Eigen::Vector3d g_seed = st - g;
  Eigen::Vector3d h_seed = st - h;

  double dot_a = a_dir(0) * a_seed(0) + a_dir(1) * a_seed(1) + a_dir(2) * a_seed(2);
  double dot_b = b_dir(0) * b_seed(0) + b_dir(1) * b_seed(1) + b_dir(2) * b_seed(2);
  double dot_c = c_dir(0) * c_seed(0) + c_dir(1) * c_seed(1) + c_dir(2) * c_seed(2);
  double dot_d = d_dir(0) * d_seed(0) + d_dir(1) * d_seed(1) + d_dir(2) * d_seed(2);
  double dot_e = e_dir(0) * e_seed(0) + e_dir(1) * e_seed(1) + e_dir(2) * e_seed(2);
  double dot_f = f_dir(0) * f_seed(0) + f_dir(1) * f_seed(1) + f_dir(2) * f_seed(2);
  double dot_g = g_dir(0) * g_seed(0) + g_dir(1) * g_seed(1) + g_dir(2) * g_seed(2);
  double dot_h = h_dir(0) * h_seed(0) + h_dir(1) * h_seed(1) + h_dir(2) * h_seed(2);

  double alpha_x = smooth_step(a_seed(0));
  double alpha_y = smooth_step(a_seed(1));
  double alpha_z = smooth_step(a_seed(2));

  double ab = mix(dot_a, dot_b, alpha_x);
  double dc = mix(dot_d, dot_c, alpha_x);
  double ef = mix(dot_e, dot_f, alpha_x);
  double hg = mix(dot_h, dot_g, alpha_x);

  double abcd = mix(ab, dc, alpha_y);
  double efgh = mix(ef, hg, alpha_y);

  double abcdefgh = mix(abcd, efgh, alpha_z);

  return abcdefgh;
}
