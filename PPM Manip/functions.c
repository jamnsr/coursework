/*************************
* Jamal Nasser
* PPM image manipulator written in C
* Spring 2017
*************************/

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void readHeader(header_t* inHeader, FILE* inPPM){
  fscanf(inPPM, "%s %d%d%d ", inHeader->magic, &inHeader->width,
                                      &inHeader->height, &inHeader->maxVal);
}

//Loops through an image and reads it into memory
void readImage(header_t* inHeader, pixel_t** dpArray, FILE* inPPM){
  int i;
  int j;
  for (i = 0; i < inHeader->height; i++){
    for (j = 0; j < inHeader->width; j++){
      fscanf(inPPM, "%c%c%c", &dpArray[i][j].r, &dpArray[i][j].g,
                                                              &dpArray[i][j].b);
    }
  }

}
//Main Menu function for user
void chooseTransform(header_t * inHeader, pixel_t** dpArray, FILE* outPPM){
  int inNum;

  printf("1.\tGray Scale\n");
  printf("2.\tColor to Negative\n");
  printf("3.\tFlip the Image\n");
  printf("4.\tRotate Right\n");
  printf("5.\tRotate Left\n");
  printf("6.\tReprint\n");

  scanf("%d", &inNum);

  switch (inNum) {
    case 1:
            grayScaleImage(inHeader, dpArray, outPPM);
            break;
    case 2:
            color2Negative(inHeader, dpArray, outPPM);
            break;
    case 3:
            flipImage(inHeader, dpArray, outPPM);
            break;
    case 4:
            rotateRight(inHeader, dpArray, outPPM);
            break;
    case 5:
            rotateLeft(inHeader, dpArray, outPPM);
            break;
    case 6:
            reprint(inHeader, dpArray, outPPM);
            break;
    default:
            printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("You entered an incorrect number. Please choose the\n");
            printf("number that corresponds to the transformation you\n");
            printf("wish to perform on the image!\n");
            printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
            chooseTransform(inHeader, dpArray, outPPM);
            break;
  }
}

void printP6Image(header_t* inHeader, pixel_t** dpArray, FILE* outPPM){
  fprintf(outPPM, "%s\n%d %d %d\n", inHeader->magic, inHeader->width,
                                            inHeader->height, inHeader->maxVal);
  int i;
  int j;
  for (i = 0; i < inHeader->height; i++){
    for (j = 0; j < inHeader->width; j++){
      fprintf(outPPM, "%c%c%c", dpArray[i][j].r, dpArray[i][j].g,
                                                              dpArray[i][j].b);
    }
  }
}

//Convert image to grayscale
void grayScaleImage(header_t* inHeader, pixel_t** dpArray, FILE* outPPM){
  fprintf(outPPM, "%s\n%d %d %d\n", "P5", inHeader->width,
                                            inHeader->height, inHeader->maxVal);
  int i;
  int j;
  //Looping through the image and combining the R,G,B after multiplying each
  //value first by a constant.
  for (i = 0; i < inHeader->height; i++){
    for (j = 0; j < inHeader->width; j++){
      fprintf(outPPM, "%c", (char)((dpArray[i][j].r*.299) +
                              (dpArray[i][j].g*.587) + (dpArray[i][j].b*.114)));
    }
  }
}

//Flips the provided image vertically
void flipImage(header_t* inHeader, pixel_t** dpArray, FILE* outPPM){
  int i;
  int j;
  int k;
  int l;
  //Printing Header
  fprintf(outPPM, "%s\n%d %d %d\n", inHeader->magic, inHeader->width,
                                            inHeader->height, inHeader->maxVal);

  //Allocating memory for the flipped image
  pixel_t** fImg = (pixel_t**)malloc(inHeader->height * sizeof(pixel_t*));
  for(i = 0; i < inHeader->height; i++){
    fImg[i] = (pixel_t*)malloc(inHeader->width * sizeof(pixel_t));
  }
  //Looping through the end of the old image and the beginning of the new image
  for (i = 0, k = (inHeader->height)-1; i < inHeader->height; i++, k--){
    for (j = 0, l = 0; j < inHeader->width; j++, l++){
      fImg[i][j] = dpArray[k][l];
      fprintf(outPPM, "%c%c%c", fImg[i][j].r, fImg[i][j].g, fImg[i][j].b);
    }
  }
  free(fImg);
}

void rotateLeft(header_t* inHeader, pixel_t** dpArray, FILE* outPPM){
  int i;
  int j;
  int k;
  int l;
  //Swapping width and height
  int newHeight = inHeader->width;
  int newWidth = inHeader->height;
  //Printing Header
  fprintf(outPPM, "%s\n%d %d %d\n", inHeader->magic, newWidth, newHeight,
                                                              inHeader->maxVal);
  //Allocating memory for the left rotated image
  pixel_t** rRightImg = (pixel_t**)malloc(newHeight * sizeof(pixel_t*));
  for(i = 0; i < newHeight; i++){
    rRightImg[i] = (pixel_t*)malloc(newWidth * sizeof(pixel_t));
  }
  //Looping through the end of the old image and the beginning of the new image
  for (i = 0, l = (inHeader->width)-1; i < newHeight; i++, l--){
    for (j = 0, k = 0; j < newWidth; j++, k++){
      rRightImg[i][j] = dpArray[k][l];
      fprintf(outPPM, "%c%c%c", rRightImg[i][j].r, rRightImg[i][j].g,
                                                            rRightImg[i][j].b);
    }
  }
  free(rRightImg);
}

void rotateRight(header_t* inHeader, pixel_t** dpArray, FILE* outPPM){
  int i;
  int j;
  int k;
  int l;
  //Swapping width and height
  int newHeight = inHeader->width;
  int newWidth = inHeader->height;
  //Printing Header
  fprintf(outPPM, "%s\n%d %d %d\n", inHeader->magic, newWidth, newHeight,
                                                              inHeader->maxVal);
  //Allocating memory for the right rotated image
  pixel_t** rRightImg = (pixel_t**)malloc(newHeight * sizeof(pixel_t*));
  for(i = 0; i < newHeight; i++){
    rRightImg[i] = (pixel_t*)malloc(newWidth * sizeof(pixel_t));
  }
  //Looping through the end of the old image and the beginning of the new image
  for (i = 0, l = 0; i < newHeight; i++, l++){
    for (j = 0, k = (inHeader->height)-1; j < newWidth; j++, k--){
      rRightImg[i][j] = dpArray[k][l];
      fprintf(outPPM, "%c%c%c", rRightImg[i][j].r, rRightImg[i][j].g,
                                                            rRightImg[i][j].b);
    }
  }
  free(rRightImg);
}

//Converts colors of provided image
void color2Negative(header_t* inHeader, pixel_t** dpArray, FILE* outPPM){
  fprintf(outPPM, "%s\n%d %d %d\n", inHeader->magic, inHeader->width,
                                            inHeader->height, inHeader->maxVal);
  int i;
  int j;
  //Looping through the image and manipulating each pixel
  for (i = 0; i < inHeader->height; i++){
    for (j = 0; j < inHeader->width; j++){
      fprintf(outPPM, "%c%c%c", (char)(255-dpArray[i][j].r),
                    (char)(255-dpArray[i][j].g), (char)(255-dpArray[i][j].b));
    }
  }

}

void reprint(header_t* inHeader, pixel_t** dpArray, FILE* outPPM){
  printP6Image(inHeader, dpArray, outPPM);
}
