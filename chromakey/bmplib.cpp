#include <stdio.h>
#include <iostream>
#include "bmplib.h"

using namespace std;
using std::cout;
using std::cin;
using std::endl;
//#define BMP_BIG_ENDIAN
#define BYTE_SWAP(num) (((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000))

unsigned char tempImage[SIZE][SIZE][RGB];

int readRGBBMP(char filename[], unsigned char inputImage[][SIZE][RGB])
{
  BYTE type[2];
  int headersize = 0;

  int i,j,k;

  //BITMAPFILEHEADER bfh;

  /* file pointer */
  FILE *file;
	
  /* read input bmp into the data matrix */
  if (!(file=fopen(filename,"rb")))
	{
	  cout << "Cannot open file: " << filename <<endl;
	  return(1);
	}

  fread(type, sizeof(unsigned char), 0x2, file);
  if(type[0] != 'B' and type[1] != 'M'){
    cout << "Not a BMP file" << endl;
    return(1);
  }
  fseek(file, 8, SEEK_CUR);
  fread(&headersize, sizeof(DWORD), 1, file);
#ifdef BMP_BIG_ENDIAN
  headersize = BYTE_SWAP(headersize); 
#endif
  //cout << "Header size is " << headersize << endl;

  fseek(file, headersize, SEEK_SET);
  fread(tempImage, sizeof(BYTE), SIZE*SIZE*RGB, file);
  cout << (int)tempImage[0][0][0] << "," << (int)tempImage[0][0][1] << "," << (int)tempImage[0][0][2] << endl;
  fclose(file);

  for(i=0; i < SIZE; i++){
    for(j=0; j < SIZE; j++){
      for(k=0; k < RGB; k++){
	inputImage[SIZE-1-i][SIZE-1-j][RGB-1-k] = tempImage[i][j][k];
	//cerr << tempImage[i][j][k] << ",";
      }
    }
	//cerr << endl;
  }
  return 0;
}


int writeRGBBMP(char filename[], unsigned char outputImage[][SIZE][RGB])
{
  BYTE hdr[54];
  int hdr_idx = 0;

  int i,j,k;

  BITMAPFILEHEADER bfh;

  // file pointer
  FILE *file;
	
  bfh.bfType1 = 'B';
  bfh.bfType2 = 'M';
  bfh.bfSize = 0x36;
  bfh.bfReserved1 = 0x0;
  bfh.bfReserved2 = 0x0;
  bfh.bfOffBits = 0x36;
  
  bfh.biSize = 0x28;
  bfh.biWidth = SIZE;
  bfh.biHeight = SIZE;
  bfh.biPlanes = 1;
  bfh.biBitCount = 24;
  bfh.biCompression  = 0;
  bfh.biSizeImage = sizeof(RGBTRIPLE)*SIZE*SIZE;
  bfh.biXPelsPerMeter = 2400;
  bfh.biYPelsPerMeter = 2400;
  bfh.biClrUsed = 0;
  bfh.biClrImportant = 0;

  write_hdr(hdr, &hdr_idx, bfh.bfType1, sizeof(BYTE));
  write_hdr(hdr, &hdr_idx, bfh.bfType2, sizeof(BYTE));
  write_hdr(hdr, &hdr_idx, bfh.bfSize, sizeof(DWORD));
  write_hdr(hdr, &hdr_idx, bfh.bfReserved1, sizeof(WORD));
  write_hdr(hdr, &hdr_idx, bfh.bfReserved2, sizeof(WORD));
  write_hdr(hdr, &hdr_idx, bfh.bfOffBits, sizeof(DWORD));
  write_hdr(hdr, &hdr_idx, bfh.biSize, sizeof(DWORD));
  write_hdr(hdr, &hdr_idx, bfh.biWidth, sizeof(DWORD));
  write_hdr(hdr, &hdr_idx, bfh.biHeight, sizeof(DWORD));
  write_hdr(hdr, &hdr_idx, bfh.biPlanes, sizeof(WORD));
  write_hdr(hdr, &hdr_idx, bfh.biBitCount, sizeof(WORD));
  write_hdr(hdr, &hdr_idx, bfh.biCompression, sizeof(DWORD));
  write_hdr(hdr, &hdr_idx, bfh.biSizeImage, sizeof(DWORD));
  write_hdr(hdr, &hdr_idx, bfh.biXPelsPerMeter, sizeof(DWORD));
  write_hdr(hdr, &hdr_idx, bfh.biYPelsPerMeter, sizeof(DWORD));
  write_hdr(hdr, &hdr_idx, bfh.biClrUsed, sizeof(DWORD));
  write_hdr(hdr, &hdr_idx, bfh.biClrImportant, sizeof(DWORD));

  for(i=0; i < SIZE; i++){
    for(j=0; j < SIZE; j++){
      for(k=0; k < RGB; k++){
	tempImage[SIZE-1-i][SIZE-1-j][RGB-1-k] = outputImage[i][j][k];
      }
    }
  }

  // write result bmp file
  if (!(file=fopen(filename,"wb")))
    {
      cout << "Cannot open file: " << filename << endl;
      return(1);
    }
  fwrite(&hdr, sizeof(unsigned char), 0x36, file);
  fwrite(tempImage, sizeof(unsigned char), SIZE*SIZE*RGB, file);
  fclose(file);

  return 0;
}

void write_hdr(BYTE *hdr, int *hdr_idx, DWORD data, DWORD size)
{
  if(size == 1){
    hdr[*hdr_idx] = (BYTE) data;
    (*hdr_idx) += 1;
  }
  else if(size == 2){
    hdr[*hdr_idx] = (BYTE) (data & 0x00ff);
    (*hdr_idx) += 1;
    hdr[*hdr_idx] = (BYTE) ((data & 0xff00) >> 8);
    (*hdr_idx) += 1;
  }
  else if(size == 4){
    hdr[*hdr_idx] = (BYTE) (data & 0x000000ff);
    (*hdr_idx) += 1;
    hdr[*hdr_idx] = (BYTE) ((data & 0x0000ff00) >> 8);
    (*hdr_idx) += 1;
    hdr[*hdr_idx] = (BYTE) ((data & 0x00ff0000) >> 16);
    (*hdr_idx) += 1;
    hdr[*hdr_idx] = (BYTE) ((data & 0xff000000) >> 24);
    (*hdr_idx) += 1;
  }
  else {
    printf("Illegal size in write_hdr...consult your instructor\n"); 
  }
}


