# cphex\makefile ffffffff

LIBS=
all:	main	dnslib.o

dnslib.o:	../ndnslib/dnslib.h	../ndnslib/dnslib.c
	echo "Compilation de ListeSimple"
	cc -c ../ndnslib/dnslib.c	

main:	main.c	dnslib.o
	echo "Compilation de client"
	cc  -o main	main.c dnslib.o	$(LIBS)

