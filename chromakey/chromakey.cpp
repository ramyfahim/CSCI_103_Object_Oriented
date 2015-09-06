//--------------------------------------------------------
// File:     chromakey.cpp
//
// Author:   Ramy Fahim
//
//
// Usage:    chromakey colbert_gs.bmp campus1.bmp 80 meth1.bmp meth2.bmp
//
// Notes:
// This program performs the chroma key operation  on an input 
// using two different methods.
//
// Method 1 Utilize a user-defined distance threshold from the
//          chromakey value as a discriminator
//
// Method 2 Devise a method that to determine the chromakey mask
//          that doesn't require a user-input threshold
//
//--------------------------------------------------------

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "bmplib.h"

using namespace std;

// Image data array
unsigned char inputImage[SIZE][SIZE][RGB];
unsigned char bgrndImage[SIZE][SIZE][RGB];
unsigned char outputImage[SIZE][SIZE][RGB];
bool chromaMask[SIZE][SIZE];

// Prototypes
void method1(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE],
	     int threshold);

void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE]);

void replace(bool mask[][SIZE],
	     unsigned char inImage[][SIZE][RGB],
	     unsigned char bgImage[][SIZE][RGB],
	     unsigned char outImage[][SIZE][RGB]);

int main(int argc, char *argv[])
{
  double distance;
  double threshold;

  if(argc < 6){
    cout << "usage: program_name input.bmp background.bmp dist_threshold output1.bmp output2.bmp" << endl;
    return 0;
  }
	
  if(readRGBBMP(argv[1], inputImage) ){
    cout << "Error reading file: " << argv[1] << endl;
    exit(1);
  }

  if(readRGBBMP(argv[2], bgrndImage) ){
    cout << "Error reading file: " << argv[2] << endl;
    exit(1);
  }
  
  // Write code to convert the threshold (argv[3])
  //  from string format to a double and assign the 'threshold'
	threshold = atof(argv[3]);

  // Call Method 1 Function
	method1(inputImage, chromaMask, threshold);

  // Produce the output by calling replace()
	replace(chromaMask, inputImage, bgrndImage, outputImage);

  // Write the output image to a file using the filename argv[4]
  if (writeRGBBMP(argv[4], outputImage) ){
    cout << "Error writing file: " << argv[4] << endl;
    exit(1);
  }	

  // Call Method 2 Function
	method2(inputImage, chromaMask);

  // Produce the output by calling replace()
	replace(chromaMask, inputImage, bgrndImage, outputImage);

  // Write the output image to a file using the filename argv[5]
  if (writeRGBBMP(argv[5], outputImage) ){
    cout << "Error writing file: " << argv[5] << endl;
    exit(1);
  }	

  return 0;
}



// Use user-provided threshold for chroma-key distance
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'green'
void method1(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE],
	     int threshold)
{

//calculate average chroma-key value for red plane (top row)
int rr;
for (int i = 0; i < 255; i++) {
	int r = static_cast<int>(inImage[0][i][0]);
	rr += r;
}

double red = rr / 255;


//calculate average chroma-key value for green plane (top row)
int gg;
for (int i = 0; i < 255; i++) {
	int g = static_cast<int>(inImage[0][i][1]);
	gg += g;
}

double green = gg / 255;


//calculate average chroma-key value for blue plane (top row)
int bb;
for (int i = 0; i < 255; i++) {
	int b = static_cast<int>(inImage[0][i][2]);
	bb += b;
}

double blue = bb / 255;


//go through all pixels in image, calculate distance of pixels from average chroma-key value, and compare result to threshold
for (int i = 0; i < 256; i++) {
	for (int j = 0; j < 256; j++) {
		int pixelr = static_cast<int>(inImage[i][j][0]);
		int pixelg = static_cast<int>(inImage[i][j][1]);
		int pixelb = static_cast<int>(inImage[i][j][2]);
		double pixel = sqrt((pow((red - pixelr), 2)) + (pow((green - pixelg), 2)) + (pow((blue - pixelb), 2)));
		if ( pixel < threshold) {
			mask[i][j] = 0;
		}
		else {
			mask[i][j] = 1;
		}
	}
}
			


}

// Devise a method to automatically come up with a threshold
//  for the chroma key determination
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'green'
void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE])  
{

//calculate average chroma-key value for red plane (top row)
int rr;
for (int i = 0; i < 255; i++) {
	int r = static_cast<int>(inImage[0][i][0]);
	rr += r;
}
double red = rr / 256;

//calculate standard deviation of top row of chroma-key pixels from precalculated average value (on red plane)
int rs;
for (int i = 0; i < 255; i++) {
	int r = pow(static_cast<int>((inImage[0][i][0]) - red), 2);
	rs += r;
}
double SDr = sqrt(rs/255);


//calculate average chroma-key value for green plane (top row)
int gg;
for (int i = 0; i < 255; i++) {
	int g = static_cast<int>(inImage[0][i][1]);
	gg += g;
}
double green = gg / 256;

//calculate standard deviation of top row of chroma-key pixels from precalculated average value (on green plane)
int gs;
for (int i = 0; i < 255; i++) {
	int g = pow(static_cast<int>((inImage[0][i][1]) - green), 2);
	gs += g;
}
double SDg = sqrt(gs/255);


//calculate average chroma-key value for blue plane (top row)
int bb;
for (int i = 0; i < 255; i++) {
	int b = static_cast<int>(inImage[0][i][2]);
	bb += b;
}
double blue = bb / 256;

//calculate standard deviation of top row of chroma-key pixels from precalculated average value (on blue plane)
int bs;
for (int i = 0; i < 255; i++) {
	int b = pow(static_cast<int>((inImage[0][i][2]) - blue), 2);
	bs += b;
}
double SDb = sqrt(bs/255);


//calculate threshold as its own distance using adjusted standard deviation values of each plane/color
double threshold = sqrt((pow((SDr*0.75), 2)) + (pow((SDg*0.75), 2)) + (pow((SDb*0.75), 2)));


//go through all pixels in image, calculate distance of pixels from average chroma-key value, and compare result to threshold
for (int i = 0; i < 256; i++) {
	for (int j = 0; j < 256; j++) {
		int pixelr = static_cast<int>(inImage[i][j][0]);
		int pixelg = static_cast<int>(inImage[i][j][1]);
		int pixelb = static_cast<int>(inImage[i][j][2]);
		double pixel = sqrt((pow((red - pixelr), 2)) + (pow((green - pixelg), 2)) + (pow((blue - pixelb), 2)));
		if ( pixel < threshold) {
			mask[i][j] = 0;
		}
		else {
			mask[i][j] = 1;
		}
	}

}
cout << threshold;
}

// If mask[i][j] = 1 use the input image pixel for the output image
// Else if mask[i][j] = 0 use the background image pixel
void replace(bool mask[SIZE][SIZE],
	     unsigned char inImage[SIZE][SIZE][RGB],
	     unsigned char bgImage[SIZE][SIZE][RGB],
	     unsigned char outImage[SIZE][SIZE][RGB])
{
  // Create the output image using the mask to determine
  //  whether to use the pixel from the Input or Background image

//go through all pixels. if mask pixel is 1 (meaning not chroma-key), use the input image. if mask pixel is 0 (meaning chroma-key), use the background image.
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			if (mask[i][j] == 1) {
				outImage[i][j][1] = inImage[i][j][1];
				outImage[i][j][2] = inImage[i][j][2];
				outImage[i][j][3] = inImage[i][j][3];
			}
			else if (mask[i][j] == 0) {
				outImage[i][j][1] = bgImage[i][j][1];
				outImage[i][j][2] = bgImage[i][j][2];
				outImage[i][j][3] = bgImage[i][j][3];
			}
		}
	}


}
