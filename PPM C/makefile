SRC = driver.cpp Circle.cpp Header.cpp Image.cpp Quadrilateral.cpp Shape.cpp Triangle.cpp
OBJ = driver.o Circle.o Header.o Image.o Quadrilateral.o Shape.o Triangle.o
PROG = driver

$(PROG) : $(OBJ)
	g++ $(OBJ) -o $(PROG) -Wall -lm -g

$(OBJ) : $(SRC)


clean:
	rm *.o driver
