/* Jamal Nasser (jnasser)
2310-01
Programming Assignment 2
Due: 3/18/18

This program takes in two numbers form stdin and multiplies
them using bitwise operators to simulate hardware multiplication.
It also prints out the steps taken along the way as well as a check.
*/


#include <stdio.h>
#include <stdlib.h>

void prt_bin( int value, int length ){
  int i;
  for( i=(length-1); i>=0; i--){
    if((value>>i)&1) 
        putchar('1'); 
    else 
        putchar('0');
  }
}

int check_lsb(int val){
  return val&1 ? 1 : 0;
}

void add(int* c, int* a, int* mq, int mdr){
  /*
    Concatenate all registers into tmp, add MDR
    shifted left by 8, store carry, update registers
  */
  int tmp = *mq;
  tmp |= (*a << 8);
  tmp |= (*c << 16);
  tmp = tmp + (mdr << 8);

  *c = tmp > 0xffff ? 1 : 0;
  *mq = (tmp & 0xff);
  *a = ((tmp>>8) & 0xff);

  return;
}

void shift_right(int* c, int* a, int* m){
  /*
    Concatenate all registers into tmp, shift right by 1, update all registers
  */
  int tmp = *m;   
  tmp |= (*a << 8);
  tmp |= (*c << 16);

  tmp >>= 1;

  *c = 0;
  *m = (tmp & 0xff);
  *a = ((tmp>>8) & 0xff);

  return;
}

void prt_reg(int* c, int* a, int* m){
  /*
    Print C:ACC:MQ in binary
  */
  prt_bin(*c, 1);
  putchar(' ');
  prt_bin(*a, 8);
  putchar(' ');
  prt_bin(*m, 8);
  putchar(' ');
  printf("\n");
  return;
}


int main(int argc, char **argv){
  int ACC = 0;
  int C = 0;

  int in_mdr, in_mq;
  printf("Enter multiplicand: ");
  scanf("%d", &in_mdr);
  printf("Enter multiplier: ");
  scanf("%d", &in_mq);

  if(in_mdr > 255 || in_mdr < 0 || in_mq > 255 || in_mq < 0){
    printf("Error: Input range is between 0 and 255.");
    exit(1);
  }

  int MDR = in_mdr;
  int MQ = in_mq;

  printf("\nmultiplicand: %d\n", MDR);
  printf("multiplier: %d\n\n", MQ);
  printf("c and acc set to 0\n");
  printf("mq set to multiplier    =  %d decimal and ", MQ);
  prt_bin(MQ, 8);
  printf(" binary\n");

  printf("mdr set to multiplicand =  %d decimal and ", MDR);
  prt_bin(MDR, 8);
  printf(" binary\n");


  for(int i = 0; i < 8; i++){
    printf("-------------------------------------------------------\n");
    printf("step %d:\t  ", i+1);
    prt_reg(&C, &ACC, &MQ);

    if(check_lsb(MQ)){
      add(&C, &ACC, &MQ, MDR);
      printf("\t+   ");
      prt_bin(MDR, 8);
      printf("        ^ add based on lsb=1");
    } else{
      printf("\t+   00000000        ^ no add based on lsb=0");
    }
    printf("\n\t  ----------\n\t  ");
    prt_reg(&C, &ACC, &MQ);
    printf("       >>                    shift right\n\t  ");
    shift_right(&C, &ACC, &MQ);
    prt_reg(&C, &ACC, &MQ);
  }
  printf("-------------------------------------------------------\n");
  printf("check:\t               binary    decimal\n");

  printf("\t\t     ");
  prt_bin(in_mdr, 8);
  printf("        %3d\n", in_mdr);

  printf("\t   x         ");
  prt_bin(in_mq, 8);
  printf("   x    %3d\n", in_mq);

  printf("\t     ----------------     ------\n");

  printf("\t     ");
  prt_bin(ACC, 8);
  prt_bin(MQ, 8);
  printf("      %5d\n", in_mdr*in_mq);


  return 0;
}
