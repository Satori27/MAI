Target = sort
CXX = g++
CFLAGS = -O2 -g -pedantic -std=c++17 -Wall -Wextra
LFLAGS = 
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
.SUFFIXES: .cpp .o

$(Target): $(OBJ)
	$(CXX) $(LFLAGS) -o $(Target) $(OBJ) 

%.o : %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(Target) *.o

