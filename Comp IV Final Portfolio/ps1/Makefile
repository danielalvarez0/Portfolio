CC = g++
CFLAGS = -c -g -Og -Wall -Werror -ansi -pedantic
OBJ = Sierpinski.o original.o
DEPS = 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
EXE = Sierpinski original

all: Sierpinski original

Sierpinski: Sierpinski.o
	$(CC) Sierpinski.o -o Sierpinski $(LIBS)

original: original.o
	$(CC) original.o -o original $(LIBS)

%.o: %.cpp %.hpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(OBJ) $(EXE)
