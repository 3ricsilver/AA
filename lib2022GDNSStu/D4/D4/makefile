# ListeS

LIBS=
all:	main	dnslib.o

dnslib.o:	../ndnslib/dnslib.h	../ndnslib/dnslib.c
	echo "Compilation de ListeSimple"
	cc -c ../ndnslib/dnslib.c	

main:	main2.c	dnslib.o
	echo "Compilation de client"
	cc  -o main2	main2.c dnslib.o	$(LIBS)

