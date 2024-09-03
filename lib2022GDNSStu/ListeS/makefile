#Files
EXEC=main

LIBS=
all:	main	dnslib.o

dnslib.o:	dnslib.h	dnslib.c
	echo "Compilation de ListeSimple"
	cc -c dnslib.c	

main:	main.c	dnslib.o
	echo "Compilation de client"
	cc  -o main	main.c dnslib.o	$(LIBS)
	
clean:
	rm -f *.o $(EXEC)

