/*************************
 *Jamal Nasser
 *CPSC 1020 Section 1, Sp17
 *jnasser
 *************************/
#include "Image.h"
#include <vector>

typedef struct {
  double x;
  double y;
} point_t;

int checkforTriangle(vector<Triangle> &tVec, int width, int height);
int checkforCircle(vector<Circle> &cVec, int width, int height);
int checkforQuadrilateral(vector<Quadrilateral> &qVec, int width, int height);

int main(int argc, char *argv[]){
   ofstream outPut(argv[2]);
   ifstream inPut(argv[1]);

   vector<Triangle> triVec;
   vector<Circle> cirVec;
   vector<Quadrilateral> quadVec;

   Image img;

   int width;
   int height;
   int i, j, k;

   point_t tempCord1;
   point_t tempCord2;
   point_t tempCord3;
   point_t tempCord4;

   int tempInt;

   string tempStr;

   //Checking for invalid execution
   if(argc != 3)
   {
     cout << "USAGE ERROR:  ./executable outPutFileName";
     exit(EXIT_FAILURE);
   }
   if(inPut.fail())
   {
     cout << argv[1] << " did not open successfully\n";
   }

   if(outPut.fail())
   {
     cout << argv[2] << " did not open successfully\n";
   }

   inPut >> width >> height;
   //Read in details from an input file made for the program
   while(!inPut.eof()){
     getline(inPut, tempStr);
     if(tempStr == "Triangle"){
       inPut >> tempCord1.x >> tempCord1.y;
       inPut >> tempCord2.x >> tempCord2.y;
       inPut >> tempCord3.x >> tempCord3.y;
       //Coordinates check
       if( (tempCord2.x > width)  ||
           (tempCord2.x > width)  ||
           (tempCord3.x > width)  ||
           (tempCord2.y > height) ||
           (tempCord2.y > height) ||
           (tempCord3.y > height) ){
         cout << "Error: Coordinates are out of bounds. Exiting..." << endl;
         exit(1);
       }
       triVec.push_back(Triangle(tempCord1.x, tempCord1.y, tempCord2.x,
                                tempCord2.y, tempCord3.x, tempCord3.y));
     }
     if(tempStr == "Circle"){
       inPut >> tempCord1.x >> tempCord1.y;
       inPut >> tempInt;
       if((tempCord1.x > width) || (tempCord1.y > height)){
         cout << "Error: Coordinates are out of bounds. Exiting..." << endl;
         exit(1);
       }
       cirVec.push_back(Circle(tempCord1.x, tempCord1.y, tempInt));
     }
     if(tempStr == "Quadrilateral"){
       inPut >> tempCord1.x >> tempCord1.y;
       inPut >> tempCord2.x >> tempCord2.y;
       inPut >> tempCord3.x >> tempCord3.y;
       inPut >> tempCord4.x >> tempCord4.y;
       if( (tempCord1.x > width)  ||
           (tempCord2.x > width)  ||
           (tempCord3.x > width)  ||
           (tempCord4.x > width)  ||
           (tempCord1.y > height) ||
           (tempCord2.y > height) ||
           (tempCord3.y > height) ||
           (tempCord4.y > height) ){
         cout << "Error: Coordinates are out of bounds. Exiting..." << endl;
         exit(1);
       }
       quadVec.push_back(Quadrilateral(tempCord1.x, tempCord1.y, tempCord2.x,
                                        tempCord2.y, tempCord3.x, tempCord3.y,
                                                  tempCord4.x, tempCord4.y));
     }
   }

   img.setHead(width, height, 255, "P6");
   img.printHead(outPut);
   img.setBG(120, 29, 55);

   for(i = 0; i < height; i++){
     for(j = 0; j < width; j++){
       //variables to help keep track of which shape is found at this point
       int triSwitch = 0;
       int quadSwitch = 0;
       int cirSwitch = 0;
       int resSwitch = 0;

       //Check for Triangle
       triSwitch = checkforTriangle(triVec, j, i);
       //Check for Circle
       cirSwitch = checkforCircle(cirVec, j, i);
       //Check for Quadrilateral
       quadSwitch = checkforQuadrilateral(quadVec, j, i);

       //Each shape is given a 'z-index' weight which dictates
       //if it will show up beneath or on top of another shape
       resSwitch = triSwitch + cirSwitch + quadSwitch;

       if (resSwitch == 1){
         quadVec.at(0).printSC(outPut);
       }
       else if (resSwitch >= 10){
         triVec.at(0).printSC(outPut);
       }
       else if ((resSwitch == 5) || (resSwitch == 6)){
         cirVec.at(0).printSC(outPut);
       }
       else{
         //If no shape found at this pixel, print background
         img.printBG(outPut);
       }

     }
   }

   inPut.close();
   outPut.close();

   return 0;
}


/*
---------------------------------------------------------------
The return value of each shape is used to handle the possibility
of multiple shapes stacking on top of each other
Each shape is given a 'z-index' weight which dictates
if it will show up beneath or on top of another shape
---------------------------------------------------------------
*/
int checkforTriangle(vector<Triangle> &tVec, int width, int height){
  int switchReturn = 0;
  for(int i = 0; i < tVec.size(); i++){
    if(tVec.at(i).checkPoint((double) width, (double) height)){
      //Triangles get the highest z-index, they are overlayed on all other shapes
      switchReturn = 10;
    }
  }
  return switchReturn;
}

int checkforCircle(vector<Circle> &cVec, int width, int height){
  int switchReturn = 0;
  for(int i = 0; i < cVec.size(); i++){
    if(cVec.at(i).checkPoint((double) width, (double) height)){
      //Circles get second highest z-index, they are overlayed on quadrilaterals
      switchReturn = 5;
    }
  }
  return switchReturn;
}

int checkforQuadrilateral(vector<Quadrilateral> &qVec, int width, int height){
  int switchReturn = 0;
  for(int i = 0; i < qVec.size(); i++){
    if(qVec.at(i).checkPoint((double) width, (double) height)){
      //Quadrilaterals are the lowest z-index, so they will be at the bottom
      switchReturn = 1;
    }
  }
  return switchReturn;
}
