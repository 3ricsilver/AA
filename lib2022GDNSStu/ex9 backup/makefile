# ListeS

LIBS=
all:	ex09	dnslib.o

dnslib.o:	../ndnslib/dnslib.h	../ndnslib/dnslib.c
	echo "Compilation de ListeSimple"
	cc -c ../ndnslib/dnslib.c	

ex09:	ex09.c	dnslib.o
	echo "Compilation de client"
	cc  -o ex09	ex09.c dnslib.o	$(LIBS)

