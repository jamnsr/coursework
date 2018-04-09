SRC = driver.c functions.c 
OBJ = driver.o functions.o 
PROG = driver

$(PROG) : $(OBJ)
	gcc $(OBJ) -o $(PROG) -Wall -lm -g

$(OBJ) : $(SRC)


clean: 
	rm *.o driver 
