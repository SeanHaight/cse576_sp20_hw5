#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#include <iostream>

#define M_PI 3.14159265358979323846

// HW1 #2.1
// Image& im: image to L1-normalize
void l1_normalize(Image& im)
  {
  
  for(int ch = 0; ch < im.c; ch ++){
    float sum = 0;
    for(int i = 0; i < im.w; i++)for(int j = 0; j< im.h; j++){
      sum = sum+im(i,j,ch);
    }

    for(int i = 0; i < im.w; i++)for(int j = 0; j< im.h; j++){
      im(i,j,ch) = im(i,j,ch)/sum;
    }
  }
  
  }

// HW1 #2.1
// int w: size of filter
// returns the filter Image of size WxW
Image make_box_filter(int w)
  {
  assert(w%2); // w needs to be odd
  
  // TODO: Implement the filter
  Image box_filter = Image(w,w,1);
  for(int i = 0; i < w; i++) for(int j = 0; j < w; j++){
    box_filter(i,j,0) = 1/((float) w*w);
  }
  return box_filter;
  }

// HW1 #2.2
// const Image&im: input image
// const Image& filter: filter to convolve with
// bool preserve: whether to preserve number of channels
// returns the convolved image
Image convolve_image(const Image& im, const Image& filter, bool preserve)
  {
  assert(filter.c==1);
  Image ret = Image(im.w, im.h, im.c);
  for(int i = 0; i < im.w; i++) for(int j = 0; j < im.h; j++)for(int ch = 0; ch < im.c; ch++){
    float sum = 0;
    for(int k = 0;  k < filter.w; k++)for(int l = 0; l < filter.h; l++){
      sum = sum + im.clamped_pixel(i - ((int) filter.w/2) + k,j - ((int) filter.h/2) + l,ch)*filter(k,l,0);
    }
    ret(i,j,ch) = sum;
  }

  // This is the case when we need to use the function clamped_pixel(x,y,c).
  // Otherwise you'll have to manually check whether the filter goes out of bounds
  //if (filter.w > 1){
  //  ret.save_image("output/ret_test");
  //}
  // TODO: Make sure you set the sizes of ret properly. Use ret=Image(w,h,c) to reset ret
  // TODO: Do the convolution operator

  // Make sure to return ret and not im. This is just a placeholder
  if (preserve) return ret;
  
  Image real_ret = Image(im.w,im.h, 1);
  for(int i = 0; i < im.w; i++) for(int j = 0; j < im.h; j++)for(int ch = 0; ch < im.c; ch++){
   real_ret(i,j,0) = real_ret(i,j,0) + ret(i,j,ch);
  }
  return real_ret;
  }

// HW1 #2.3
// returns basic 3x3 high-pass filter
Image make_highpass_filter()
  {
  Image highpass_filter = Image(3,3,1);
  highpass_filter(0,0,0) = 0;
  highpass_filter(1,0,0) = -1;
  highpass_filter(2,0,0) = 0;
  highpass_filter(0,1,0) = -1;
  highpass_filter(1,1,0) = 4;
  highpass_filter(2,1,0) = -1;
  highpass_filter(0,2,0) = 0;
  highpass_filter(1,2,0) = -1;
  highpass_filter(2,2,0) = 0;
  return highpass_filter;
  }

// HW1 #2.3
// returns basic 3x3 sharpen filter
Image make_sharpen_filter()
  {
  Image sharpen_filter = Image(3,3,1);
  sharpen_filter(0,0,0) = 0;
  sharpen_filter(1,0,0) = -1;
  sharpen_filter(2,0,0) = 0;
  sharpen_filter(0,1,0) = -1;
  sharpen_filter(1,1,0) = 5;
  sharpen_filter(2,1,0) = -1;
  sharpen_filter(0,2,0) = 0;
  sharpen_filter(1,2,0) = -1;
  sharpen_filter(2,2,0) = 0;
  return sharpen_filter;
  
  }

// HW1 #2.3
// returns basic 3x3 emboss filter
Image make_emboss_filter()
  {
  Image emboss_filter = Image(3,3,1);
  emboss_filter(0,0,0) = -2;
  emboss_filter(1,0,0) = -1;
  emboss_filter(2,0,0) = 0;
  emboss_filter(0,1,0) = -1;
  emboss_filter(1,1,0) = 1;
  emboss_filter(2,1,0) = 1;
  emboss_filter(0,2,0) = 0;
  emboss_filter(1,2,0) = 1;
  emboss_filter(2,2,0) = 2;
  return emboss_filter;
  
  }

// HW1 #2.4
// float sigma: sigma for the gaussian filter
// returns basic gaussian filter
Image make_gaussian_filter(float sigma)
  {
    int w = (int) (6*(sigma)) + 1;
    if (w%2 == 0) w = w + 1;
  // TODO: Implement the filter
  Image gaussian_filter = Image(w,w,1);
  for (int i = 0; i < w; i++) for(int j = 0; j < w; j++){
    float coeff = 1/(2*M_PI*sigma*sigma);
    float pow = -((i - w/2)*(i - w/2) + (j - w/2)*(j - w/2))/(2*sigma*sigma);
    gaussian_filter(i,j,0) = coeff*exp(pow);
  }
  l1_normalize(gaussian_filter);
  return gaussian_filter;
  
  }


// HW1 #3
// const Image& a: input image
// const Image& b: input image
// returns their sum
Image add_image(const Image& a, const Image& b)
  {
  assert(a.w==b.w && a.h==b.h && a.c==b.c); // assure images are the same size
  Image sum = Image(a.w, a.h, a.c);
  for(int i = 0; i < a.w; i++) for(int j = 0; j < a.h; j++)for(int ch = 0; ch < a.c; ch++){
   sum(i,j,ch) = a(i,j,ch) + b(i,j,ch);
  }
  
  return sum;
  }

// HW1 #3
// const Image& a: input image
// const Image& b: input image
// returns their difference res=a-b
Image sub_image(const Image& a, const Image& b)
  {
  assert(a.w==b.w && a.h==b.h && a.c==b.c); // assure images are the same size
  Image diff = Image(a.w, a.h, a.c);
  for(int i = 0; i < a.w; i++) for(int j = 0; j < a.h; j++)for(int ch = 0; ch < a.c; ch++){
   diff(i,j,ch) = a(i,j,ch) - b(i,j,ch);
  }
  
  return diff;
  }

// HW1 #4.1
// returns basic GX filter
Image make_gx_filter()
  {
  Image GX_filter = Image(3,3,1);
  GX_filter(0,0,0) = -1;
  GX_filter(1,0,0) = 0;
  GX_filter(2,0,0) = 1;
  GX_filter(0,1,0) = -2;
  GX_filter(1,1,0) = 0;
  GX_filter(2,1,0) = 2;
  GX_filter(0,2,0) = -1;
  GX_filter(1,2,0) = 0;
  GX_filter(2,2,0) = 1;
  return GX_filter;
  
  }

// HW1 #4.1
// returns basic GY filter
Image make_gy_filter()
  {
  Image GY_filter = Image(3,3,1);
  GY_filter(0,0,0) = -1;
  GY_filter(1,0,0) = -2;
  GY_filter(2,0,0) = -1;
  GY_filter(0,1,0) = 0;
  GY_filter(1,1,0) = 0;
  GY_filter(2,1,0) = 0;
  GY_filter(0,2,0) = 1;
  GY_filter(1,2,0) = 2;
  GY_filter(2,2,0) = 1;
  return GY_filter;
  }

// HW1 #4.2
// Image& im: input image
void feature_normalize(Image& im)
  {
  assert(im.w*im.h); // assure we have non-empty image
  
  for(int ch = 0; ch < im.c; ch ++){
    //Loop through once, determine the minimum and the maximum
    float mini = im(0,0,ch);
    float maxi = im(0,0,ch);
    for(int i = 0; i < im.w; i ++)for(int j = 0; j < im.h; j ++){
      mini = min(mini, im(i,j,ch));
      maxi = max(maxi, im(i,j,ch));
    }
    float range = maxi - mini;
    float one_over_range = 0;
    if (range != 0) one_over_range = 1/range;
    for(int i = 0; i < im.w; i ++)for(int j = 0; j < im.h; j ++){
      im(i,j,ch) = (im(i,j,ch) - mini)/range;
    }
  }
  
  }


// Normalizes features across all channels
void feature_normalize_total(Image& im)
  {
  assert(im.w*im.h*im.c); // assure we have non-empty image
  
  int nc=im.c;
  im.c=1;im.w*=nc;
  
  feature_normalize(im);
  
  im.w/=nc;im.c=nc;
  
  }


// HW1 #4.3
// Image& im: input image
// return a pair of images of the same size
pair<Image,Image> sobel_image(const Image& im)
  {
  // TODO: Your code here
  //First we computer the images G_x and G_y. 
  Image G_x_filter = make_gx_filter();
  Image G_y_filter = make_gy_filter();
  Image G_x = convolve_image(im, G_x_filter, false);
  Image G_y = convolve_image(im, G_y_filter, false);

  Image Mag = Image(G_x.w, G_x.h, 1);
  Image Dir = Image(G_x.w, G_x.h, 1);
  for(int i = 0; i < Mag.w; i++) for(int j = 0; j < Mag.h; j++){
    Mag(i,j,0) = sqrt(G_x(i,j,0)*G_x(i,j,0) + G_y(i,j,0)*G_y(i,j,0));
    Dir(i,j,0) = atan2(G_y(i,j,0), G_x(i,j,0));
  }
  return {Mag,Dir};
  }


// HW1 #4.4
// const Image& im: input image
// returns the colorized Sobel image of the same size
Image colorize_sobel(const Image& im)
  {
  pair<Image,Image> res = sobel_image(im);
  Image mag = res.first;
  Image theta = res.second;

  feature_normalize(mag);
  feature_normalize(theta);
  Image im2 = im;
  rgb_to_hsv(im2);
  for(int i = 0; i < im2.w; i++) for(int j = 0; j < im2.h; j++){
    im2(i,j,2) = mag(i,j,0);
    im2(i,j,1) = theta(i,j,0)/(2*M_PI) + .5;
  }
  hsv_to_rgb(im2);
  // TODO: Your code here
  
  return im2;
  }


// HW1 #4.5
// const Image& im: input image
// float sigma1,sigma2: the two sigmas for bilateral filter
// returns the result of applying bilateral filtering to im
Image bilateral_filter(const Image& im, float sigma1, float sigma2)
  {
  Image bf=im;
  
  // TODO: Your bilateral code
  NOT_IMPLEMENTED();
  
  return bf;
  }



// HELPER MEMBER FXNS

void Image::feature_normalize(void) { ::feature_normalize(*this); }
void Image::feature_normalize_total(void) { ::feature_normalize_total(*this); }
void Image::l1_normalize(void) { ::l1_normalize(*this); }

Image operator-(const Image& a, const Image& b) { return sub_image(a,b); }
Image operator+(const Image& a, const Image& b) { return add_image(a,b); }
