PROGRAM = TAT

OBJECTS = main.o read_input.o initial.o check_frame.o read_dump.o compute.o output.o

CC = gcc
CFLAGS = -Wall -std=c11 -D DEBUG
LDFLAGS = -lm -fopenmp

${PROGRAM} : ${OBJECTS}
	${CC} ${CFLAGS} -o ${PROGRAM} ${OBJECTS} ${LDFLAGS}

main.o : main.c mdtat.h
	${CC} ${CFLAGS} -o main.o -c main.c
read_input.o : read_input.c mdtat.h
	${CC} ${CFLAGS} -o read_input.o -c read_input.c
initial.o : initial.c mdtat.h
	${CC} ${CFLAGS} -o initial.o -c initial.c ${LDFLAGS}
check_frame.o : check_frame.c mdtat.h
	${CC} ${CFLAGS} -o check_frame.o -c check_frame.c
read_dump.o : read_dump.c mdtat.h
	${CC} ${CFLAGS} -o read_dump.o -c read_dump.c
compute.o : compute.c mdtat.h
	${CC} ${CFLAGS} -o compute.o -c compute.c ${LDFLAGS}
output.o :output.c mdtat.h
	${CC} ${CFLAGS} -o output.o -c output.c

.PHONY : clean
clean :
	rm ${OBJECTS}
	rm ${PROGRAM}