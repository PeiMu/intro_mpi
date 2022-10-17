# learn mpi

## [An introduction to the Message Passing Interface (MPI) using C](http://condor.cc.ku.edu/~grobe/docs/intro-MPI-C.shtml)

### Makefile
```bash
make clean
make
make run EXE=[function name]
```

### compile separately
```bash
mpicc [C file] -o [Exe file]
```

#### run
```bash
mpirun -np [process num] [Exe file]
```
