PROGRAM = TAT.o

OBJECTS = main.o read_input.o alloc_mem.o read_dump.o compute.o output.o error_exit.o

CC = gcc
CFLAGS = -O2 -std=c99

${PROGRAM} : ${OBJECTS}
	${CC} -o ${PROGRAM} ${OBJECTS} ${CFLAGS} -lm -fopenmp

main.o : mdtat.h
	${CC} -o main.o ${CFLAGS} -c main.c
read_input.o : mdtat.h
	${CC} -o read_input.o ${CFLAGS} -c read_input.c
alloc_mem.o : mdtat.h
	${CC} -o alloc_mem.o ${CFLAGS} -c alloc_mem.c
read_dump.o : mdtat.h
	${CC} -o read_dump.o ${CFLAGS} -c read_dump.c
compute.o : mdtat.h
	${CC} -o compute.o ${CFLAGS} -c compute.c -lm -fopenmp
output.o : mdtat.h
	${CC} -o output.o ${CFLAGS} -c output.c
error_exit.o : mdtat.h
	${CC} -o error_exit.o ${CFLAGS} -c error_exit.c

.PHONY: clean
clean:
	rm ${OBJECTS}
	rm ${PROGRAM}
