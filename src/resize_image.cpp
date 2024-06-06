#include <cmath>
#include "image.h"
#include <iostream>

using namespace std;

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the nearest neighbor to pixel (x,y,c)
float Image::pixel_nearest(float x, float y, int c) const
  {
  // Since you are inside class Image you can
  // use the member function pixel(a,b,c)
  int round_x = (int) x;
  int round_y = (int) y;

  if (x - round_x >= .5) round_x += 1;
  if (y - round_y >= .5) round_y += 1;
  // TODO: Your code here
  
  return clamped_pixel(round_x, round_y, c);
  }

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the bilinearly interpolated pixel (x,y,c)
float Image::pixel_bilinear(float x, float y, int c) const
  {
  // Since you are inside class Image you can
  // use the member function pixel(a,b,c)
  int left_x = (int) x;
  if (x < 0) left_x = left_x - 1;
  int right_x = left_x + 1;
  int up_y = (int) y;
  if (y < 0) up_y = up_y - 1;
  int down_y = up_y + 1;

  float sum = 0;
  sum = sum + clamped_pixel(left_x, up_y, c)*(right_x - x)*(down_y - y);
  sum = sum + clamped_pixel(right_x, up_y, c)*(x - left_x)*(down_y - y);
  sum = sum + clamped_pixel(left_x, down_y, c)*(right_x - x)*(y - up_y);
  sum = sum + clamped_pixel(right_x, down_y, c)*(x - left_x)*(y - up_y);

  // TODO: Your code here
  
  return sum;
  }

// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image nearest_resize(const Image& im, int w, int h)
  {
  Image ret(w,h,im.c);
  float x_rescale = w/((float) im.w);
  float y_rescale = h/((float) im.h);
  for (int i = 0; i < w; i ++) for (int j = 0; j < h; j++) for (int ch = 0; ch < im.c; ch ++){
      ret(i,j,ch) = im.pixel_nearest((i + .5)/x_rescale - .5, (j + .5)/y_rescale - .5, ch);
  }
  
  return ret;
  }


// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image bilinear_resize(const Image& im, int w, int h)
  {
  Image ret(w,h,im.c);
  float x_rescale = w/((float) im.w);
  float y_rescale = h/((float) im.h);
  for (int i = 0; i < w; i ++) for (int j = 0; j < h; j++) for (int ch = 0; ch < im.c; ch ++){
      ret(i,j,ch) = im.pixel_bilinear((i + .5)/x_rescale - .5, (j + .5)/y_rescale - .5, ch);
  }
  return ret;
  }


