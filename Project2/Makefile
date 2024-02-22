CFLAGS  = -std=gnu99 -Wall -pedantic -g
TARGETS = mytoolkit mytoolkit-o mytoolkit.x mytimeout mytimeout-o mytimeout.x 

default: $(TARGETS)




mytimeout: mytimeout.c
	gcc $(CFLAGS) -c mytimeout.c

mytimeout-o: mytimeout.c
	gcc $(CFLAGS) -o mytimeout.o mytimeout.c

mytimeout.x: mytimeout.c
	gcc $(CFLAGS) mytimeout.c -o mytimeout.x	

mytoolkit: mytoolkit.c
	gcc $(CFLAGS) -c mytoolkit.c

mytoolkit-o: mytoolkit.c
	gcc $(CFLAGS) -o mytoolkit.o mytoolkit.c

mytoolkit.x: mytoolkit.c
	gcc $(CFLAGS) mytoolkit.c -o mytoolkit.x	



clean:
	- rm -f *.o *.x *.cd