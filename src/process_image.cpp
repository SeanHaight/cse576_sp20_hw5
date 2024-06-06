#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>

#include "image.h"

using namespace std;

// HW0 #3
// const Image& im: input image
// return the corresponding grayscale image
Image rgb_to_grayscale(const Image& im)
  {
  assert(im.c == 3); // only accept RGB images
  Image gray(im.w,im.h,1); // create a new grayscale image (note: 1 channel)
  
  // TODO: calculate the pixels of 'gray'
  for(int i = 0; i < im.w; i++){
    for (int j = 0; j < im.h; j++){
      gray(i,j,0) = .299*im(i,j,0) + .587*im(i,j,1) + .114*im(i,j,2);
    }
  }

  return gray;
  }



// Example function that changes the color of a grayscale image
Image grayscale_to_rgb(const Image& im, float r, float g, float b)
  {
  assert(im.c == 1);
  Image rgb(im.w,im.h,3);
  
  for(int q2=0;q2<im.h;q2++)for(int q1=0;q1<im.w;q1++)
    {
    rgb(q1,q2,0)=r*im(q1,q2);
    rgb(q1,q2,1)=g*im(q1,q2);
    rgb(q1,q2,2)=b*im(q1,q2);
    }
  
  return rgb;
  }




// HW0 #4
// Image& im: input image to be modified in-place
// int c: which channel to shift
// float v: how much to shift
void shift_image(Image& im, int c, float v)
  {
  assert(c>=0 && c<im.c); // needs to be a valid channel
  
  //shift all the pixels at the specified channel
  for(int i=0; i< im.w;i++)for(int j=0; j<im.h;j++)
    {
      im(i,j,c) += v;
    }
  }

// HW0 #8
// Image& im: input image to be modified in-place
// int c: which channel to scale
// float v: how much to scale
void scale_image(Image& im, int c, float v)
  {
  assert(c>=0 && c<im.c); // needs to be a valid channel
  
  for(int i=0; i< im.w;i++)for(int j=0; j<im.h;j++)
    {
      im(i,j,c) *= v;
    }  
  }


// HW0 #5
// Image& im: input image to be modified in-place
void clamp_image(Image& im)
  {
  //clamp all the pixels in all channel to be between 0 and 1
    for(int i=0; i< im.w;i++)for(int j=0; j<im.h;j++)for(int c=0; c<im.c;c++)
    {
      im(i,j,c) = min(max(im(i,j,c),(float)0),(float)1);
    }
  
  }

// These might be handy
float max(float a, float b, float c)
  {
  return max({a,b,c});
  }

float min(float a, float b, float c)
  {
  return min({a,b,c});
  }


// HW0 #6
// Image& im: input image to be modified in-place
void rgb_to_hsv(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // Convert all pixels from RGB format to HSV format
    for(int i = 0;i < im.w; i++)for(int j=0;j<im.h;j++){
      float R = im(i,j,0);
      float G = im(i,j,1);
      float B = im(i,j,2);

      //Compute V
      float  V = max(R,G,B);

      //Compute S
      float m = min(R,G,B);
      float C = V - m;
      float  S = 0; 
      if(V != 0){
        S = C/V;
      }

      //Compute H
      float Hp = 0;
      if(C != 0){
        if(V == R){
          Hp = (G - B)/C; 
        } else if (V == G){
          Hp = (B - R)/C + 2;
        } else {
          Hp = (R - G)/C + 4;
        }
      }
      float H = Hp/6;
      if(Hp < 0){
        H = Hp/6 + 1;
      }

      im(i,j,0) = H;
      im(i,j,1) = S;
      im(i,j,2) = V;
    }
  
  }

// HW0 #7
// Image& im: input image to be modified in-place
void hsv_to_rgb(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from HSV format to RGB format
  // Convert all pixels from RGB format to HSV format
    for(int i = 0;i < im.w; i++)for(int j=0;j<im.h;j++){
      float H = im(i,j,0);
      float S = im(i,j,1);
      float V = im(i,j,2);

      float C = V*S;
      float X = C * (1 - abs((fmod(6*H,  2) - 1)));
      float m = V - C;

      float R = C;
      float G = 0;
      float B = X;

      if (0 <= H && H < 1/(6.0f)){
        R = C;
        G = X;
        B = 0;

      } else if (1/(6.0f) <= H && H < 2/(6.0f)){
        R = X;
        G = C;
        B = 0;

      } else if (2/(6.0f) <= H && H < 3/(6.0f)){
        R = 0;
        G = C;
        B = X;

      } else if (3/(6.0f) <= H && H < 4/(6.0f)){
        R = 0;
        G = X;
        B = C;

      } else if (4/(6.0f) <= H && H < 5/(6.0f)){
        R = X;
        G = 0;
        B = C;

      }

      im(i,j,0) = R + m;
      im(i,j,1) = G + m;
      im(i,j,2) = B + m;
    }  
  }

// HW0 #9
// Image& im: input image to be modified in-place
void rgb_to_lch(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from RGB format to LCH format
  
  
  NOT_IMPLEMENTED();
  
  }

// HW0 #9
// Image& im: input image to be modified in-place
void lch_to_rgb(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from LCH format to RGB format
  
  NOT_IMPLEMENTED();
  
  }



// Implementation of member functions
void Image::clamp(void) { clamp_image(*this); }
void Image::shift(int c, float v) { shift_image(*this,c,v); }
void Image::scale(int c, float v) { scale_image(*this,c,v); }

void Image::HSVtoRGB(void) { hsv_to_rgb(*this); }
void Image::RGBtoHSV(void) { rgb_to_hsv(*this); }
void Image::LCHtoRGB(void) { lch_to_rgb(*this); }
void Image::RGBtoLCH(void) { rgb_to_lch(*this); }
