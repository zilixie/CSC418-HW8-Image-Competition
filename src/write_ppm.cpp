#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
        const std::string & filename,
        const std::vector<unsigned char> & data,
        const int width,
        const int height,
        const int num_channels)
{
  assert(
          (num_channels == 3 || num_channels ==1 ) &&
          ".ppm only supports RGB or grayscale images");

  FILE *img_file;
  img_file = fopen(filename.c_str(),"wb");

  if (img_file == nullptr){
    perror("error: fail to create output file");
    exit(EXIT_FAILURE);
  }
  if (num_channels == 3) {
    fprintf(img_file,"P6\n");
  }
  else {
    fprintf(img_file,"P5\n");
  }
  fprintf(img_file,"%d %d\n",width,height);
  fprintf(img_file,"255\n");

  auto *img_data= const_cast<unsigned char*>(data.data());

  if (fwrite(img_data,1,width*height*num_channels,img_file) > 0) {
    fclose(img_file);
    return true;
  }
  else {
    return false;
  }
}
