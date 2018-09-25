all: ksamp.o
	 gcc ksamp.o -o ksamp

ksamp.o: ksamp.c
		 gcc -c ksamp.c -o ksamp.o

clean: 
	  rm ksamp.o ksamp