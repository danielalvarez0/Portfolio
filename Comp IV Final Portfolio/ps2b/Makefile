CC = g++
CFLAGS = -c -g -Og -Wall -Werror -ansi -pedantic
OBJ = PhotoMagic.o LFSR.o
DEPS = 
LIBS =  -lsfml-graphics -lsfml-window -lsfml-system
EXE = PhotoMagic

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)




%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(OBJ) $(EXE)
