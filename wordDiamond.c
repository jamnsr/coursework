/* Jamal Nasser
	CPSC 1010
	Fall 2016
*/

#include <stdio.h>

int WIDTH = 40;

int main(void){
	int usrRows, column, row;
	int space = WIDTH;
	int rowLimit = WIDTH;
	int chars = 1;
	int passedMiddle = 0;

	char usrChar;
	printf("This program will print a character diamond.\n\n");
	printf("Enter a character: ");
	scanf("%c", &usrChar);

	//Make adjustments for edge cases in ASCII table
	if(usrChar >= 89)
		rowLimit = 126 - (usrChar-2);

	//Check if usrRows is even or out of range
	do{
		printf("Enter an odd number at least 1 but less than %d: ", rowLimit);
		scanf("%d", &usrRows);
	} while(usrRows % 2 == 0 || usrRows >= rowLimit);

	//Top half of diamond + middle row
	for(row = 1; row <= usrRows; row++){
		for(column = 1; column <= space; column++)
			printf(" ");

		space = passedMiddle ? space + 2 : space - 2;

		for(column = 1; column <= chars; column++){
			if(column > chars / 2 && chars > column){
				printf("%c", usrChar);
				usrChar--;
			}

			else if(column > chars / 2)
				printf("%c", usrChar);

			else{
				printf("%c", usrChar);
				usrChar++;
			}
		}

		chars = passedMiddle ? chars - 4 : chars + 4;

		printf("\n");

		//Variable offsets after we pass the middle line
		if(row == (usrRows/2)+1){
			chars -= 8;
			space += 4;
			passedMiddle = 1;
		}

	 }

	return 0;
}
