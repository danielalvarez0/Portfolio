CC = g++
CFLAGS = -c -g -Og -Wall -Werror -ansi -pedantic
OBJ = boosttest.o LFSR.o
DEPS = 
LIBS =
EXE = boosttest

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)




%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(OBJ) $(EXE)
