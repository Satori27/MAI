CXX = g++
CFLAGS = -Wall
LFLAGS =

# all: program

program : main.o func.o
	$(CXX) $(LFLAGS) -o program main.o func.o

main.o : main.cpp func.h
	$(CXX) $(CFLAGS) -c main.cpp

func.o : func.cpp func.h
	$(CXX) $(CFLAGS) -c func.cpp

clean :
	rm -rf *.o program