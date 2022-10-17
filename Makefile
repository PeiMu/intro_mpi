### Makefile for MPI compile and run

ifndef VERBOSE
	QUIET := @
endif

CC:=mpicc
RUN:=mpirun
EXE?=hello

#COMMON_FLAGS:

PROC_NUM:=-np 4

all: default

default: hello.o helloWithId.o helloDiffTask.o basicCommu.o collectiveOperation.o

%.o: %.c
	@echo Compiling $*.c
	$(CC) -o $@ $< -lm

run: $(EXE).o
	@echo run $(EXE).o
	$(RUN) $(PROC_NUM) $(EXE).o

clean:
	$(QUIET)rm -f *.o
