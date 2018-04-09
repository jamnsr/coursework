/*************************
* Jamal Nasser
* PPM image manipulator written in C
* Spring 2017
*************************/

#include <stdio.h>
#include "functions.h"
int main(int argc, char* argv[]){

int i;
FILE* ppmIn;
FILE* ppmOut;
header_t inputHeader;
header_t* inputHeaderP = &inputHeader;

  //Check for correct number of arguments.
  if ((argc != 3)){
    printf("Incorrect usage, use: executable, input file, output file.\n");
    return 3;
  }
  //Check if input file opens properly
  if ((ppmIn = fopen (argv[1], "r"))  ==  NULL ){
    printf("Can't open input file %s.\n", argv[1]);
    return 1;
  }
  //Check if output file opens properly
  if ((ppmOut = fopen (argv[2], "w"))  ==  NULL ){
    printf("Can't open output file %s.\n", argv[2]);
    return 2;
  }

  readHeader(inputHeaderP, ppmIn);

  //Dynamic Allocation of Memory for input image
  pixel_t** img = (pixel_t**)malloc(inputHeader.height * sizeof(pixel_t*));
  for(i = 0; i < inputHeader.height; i++){
    img[i] = (pixel_t*)malloc(inputHeader.width * sizeof(pixel_t));
  }

  //Call to readImage
  readImage(inputHeaderP, img, ppmIn);

  //Call to chooseTransform
  printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  printf("Thank you for using the Image Transformer!\n");
  printf("There are several transformations you can perform\n");
  printf("on the input image. Choose the number that corresponds to the\n");
  printf("transformation you wish to perform on the image!\n");
  printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
  chooseTransform(inputHeaderP, img, ppmOut);

  //Free Memory & Close Files
  fclose(ppmIn);
  fclose(ppmOut);
  free(img);

  return 0;

}
