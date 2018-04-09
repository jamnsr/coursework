/*************************
* Jamal Nasser
* PPM image manipulator written in C
* Spring 2017
*************************/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

/* Two Structs */
typedef struct{
    char magic[3];
    int height, width, maxVal;
}header_t;

typedef struct{
  unsigned char r, g, b;
}pixel_t;

/* Function Prototypes */
void readHeader(header_t*, FILE*);
void readImage(header_t*, pixel_t **, FILE*);
void chooseTransform(header_t *, pixel_t **, FILE*);
void printP6Image(header_t*, pixel_t **, FILE*);
void grayScaleImage(header_t *, pixel_t **, FILE*);
void flipImage(header_t *, pixel_t **, FILE*);
void rotateLeft(header_t * , pixel_t **, FILE*);
void rotateRight(header_t *, pixel_t **, FILE*);
void color2Negative(header_t*, pixel_t **, FILE*);
void reprint(header_t*, pixel_t**, FILE*);



#endif
