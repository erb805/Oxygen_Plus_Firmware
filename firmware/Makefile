LIBS = -lpigpio -lpthread
CCFLAGS = 

SRC=$(wildcard *.c) $(wildcard drivers/*.c) 

run: $(SRC)
	gcc -o $@ $^ $(CFLAGS) $(CCFLAGS) $(LIBS)


