CC = gcc
CFLAGS = -Wall --std=c99
OBJECTS = main.o cubeSolve.o cubeUtils.o vectors.o

cube_solver: $(OBJECTS)
	$(CC) $(CFLAGS) -o cube_solver $(OBJECTS)
main.o: main.c cubeSolve.h rubiksDefAssignments.h
	$(CC) $(CFLAGS) -c main.c -o main.o
cubeSolve.o: cubeSolve.c cubeSolve.h
	$(CC) $(CFLAGS) -c cubeSolve.c -o cubeSolve.o
cubeUtils.o: cubeUtils.c cubeUtils.h rubiksDef.h
	$(CC) $(CFLAGS) -c cubeUtils.c -o cubeUtils.o
vectors.o: vectors.c vectors.h
	$(CC) $(CFLAGS) -c vectors.c -o vectors.o
clean:
	rm $(OBJECTS) cube_solver
