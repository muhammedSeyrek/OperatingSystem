
CC = mpicc
CFLAGS = -Wall -O2

TARGETS = hello myMpiRun

all: $(TARGETS)

hello: hello.o
	$(CC) $(CFLAGS) -o hello hello.o

my_mpirun: my_mpirun.o
	$(CC) $(CFLAGS) -o myMpiRun myMpiRun.o

hello.o: hello.c
	$(CC) $(CFLAGS) -c hello.c

my_mpirun.o: my_mpirun.c
	$(CC) $(CFLAGS) -c myMpiRun.c

clean:
	rm -f *.o $(TARGETS)

.PHONY: all clean

