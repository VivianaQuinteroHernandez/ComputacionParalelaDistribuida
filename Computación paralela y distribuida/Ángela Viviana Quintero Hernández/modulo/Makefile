GCC = gcc-11
FLAGS = -ansi -pedantic -Wall 
CFLAGS = -lm -lpthread -fopenmp 
THEPROGS=MM1c MM1f MMPosix MM1cOMP MM1fOMP

PROGS: MM1c MM1f MMPosix MM1cOMP MM1fOMP

MM1c:
	$(GCC) $(FLAGS) modulo.c -c
	$(GCC) $(FLAGS) $@.c -c
	$(GCC) $(FLAGS) $@.c modulo.o -o $@

MM1cOMP:
	$(GCC) $(FLAGS) module.c -c -D_POSIX_C_SOURCE=199309L $(CFLAGS)
	$(GCC) $(FLAGS) $@.c -c $(CFLAGS)
	$(GCC) $(FLAGS) module.o $@.o -o $@ $(CFLAGS)

MM1fOMP:
	$(GCC) $(FLAGS) module.c -c -D_POSIX_C_SOURCE=199309L $(CFLAGS)
	$(GCC) $(FLAGS) $@.c -c $(CFLAGS)
	$(GCC) $(FLAGS) module.o $@.o -o $@ $(CFLAGS)

MM1f:
	$(GCC) $(FLAGS) modulo.c -c
	$(GCC) $(FLAGS) $@.c -c
	$(GCC) $(FLAGS) $@.c modulo.o -o $@

MMPosix:
	$(GCC) $(FLAGS) modulo.c -c $(CFLAGS)
	$(GCC) $(FLAGS) $@.c -c $(CFLAGS)
	$(GCC) $(FLAGS) $@.c modulo.o -o $@ $(CFLAGS)

clean:
	$(RM) $(PROGS) *.o
	
