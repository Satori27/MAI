CC = gcc
LIB = -shared -o
OBJ = -fPIC -c
static: libDyn1.so libDyn2.so
	${CC} static.c -L. -lDyn1 -o main1.1 -Wl,-rpath -Wl,.	
	${CC} static.c -L. -lDyn2 -o main1.2 -Wl,-rpath -Wl,. 
	${CC} dyn.c -L. -ldl -o main2 -Wl,-rpath -Wl,.	

libDyn1.so libDyn2.so: realization1.o realization2.o
	${CC} ${LIB} libDyn1.so realization1.o
	${CC} ${LIB} libDyn2.so realization2.o

realization1.o realization2.o: realization1.c realization2.c
	${CC} ${OBJ} realization1.c -o realization1.o
	${CC} ${OBJ} realization2.c -o realization2.o

remove:
	rm -rf *.o *.so main1.[12] main2
