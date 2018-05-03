CC = gcc
CFLAGS = -Wall -O2

mountain: mountain.c fcyc2.c clock.c
	$(CC) $(CFLAGS) -o mountain mountain.c fcyc2.c clock.c 

mountain.s: mountain.c fcyc2.c clock.c
	$(CC) $(CFLAGS) -S mountain.c fcyc2.c clock.c 

clean:
	rm -f mountain *.s *.o *~


