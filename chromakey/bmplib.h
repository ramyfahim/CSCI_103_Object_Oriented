#ifndef BMPLIB_H
#define BMPLIB_H

#define SIZE 256
#define RGB 3

int readRGBBMP(char filename[], unsigned char inputImage[][SIZE][RGB]);
int writeRGBBMP(char filename[], unsigned char outputImage[][SIZE][RGB]);

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;

typedef struct { 
  BYTE    bfType1; 
  BYTE    bfType2; 
  DWORD   bfSize;
  WORD    bfReserved1; 
  WORD    bfReserved2; 
  DWORD   bfOffBits; 
  DWORD   biSize;          // size of structure, in bytes
  DWORD   biWidth;         // bitmap width, in pixels
  DWORD   biHeight;        // bitmap height, in pixels
  WORD    biPlanes;        // see below
  WORD    biBitCount;      // see below
  DWORD   biCompression;   // see below
  DWORD   biSizeImage;     // see below
  DWORD   biXPelsPerMeter; // see below
  DWORD   biYPelsPerMeter; // see below
  DWORD   biClrUsed;       // see below
  DWORD   biClrImportant;  // see below
} BITMAPFILEHEADER, *PBITMAPFILEHEADER; 

typedef struct {
  BYTE rgbBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
} RGBTRIPLE;

void write_hdr(BYTE *hdr, int *hdr_idx, DWORD data, DWORD size);

#endif
